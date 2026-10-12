#!/usr/bin/env python3
"""Claims: one worker per object file at a time, and commits that touch only what it owns.

Several matching sessions share one working tree. Each takes a claim on an object file (a row of
config/us/tus.csv) before writing a line, and may then write and commit only source files whose
tagged addresses all lie inside object files it holds. A claim lapses after 90 minutes unless
renewed, so a stopped session cannot hold an object file for ever.

Claims live in the repository's git directory (shared by every worktree, never committed);
every read-modify-write of them, and every commit made through this tool, is serialised by one
file lock, so two sessions never race on the claims or on git's index.

    python3 tools/claim.py take TU --who NAME [--minutes 90]
    python3 tools/claim.py renew TU --who NAME
    python3 tools/claim.py drop TU --who NAME
    python3 tools/claim.py list
    python3 tools/claim.py commit --who NAME -m MESSAGE PATH...

`commit` refuses unless every PATH is under src/ (outside src/control/) and every tag in it lies
in an object file NAME holds live; it then commits exactly those paths (`git commit --only`),
whatever else is staged, so sessions never sweep up each other's work. A PATH that no longer
exists is committed as a removal, judged by the tags it held in the last commit.
"""
import argparse
import csv
import fcntl
import json
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TAG = re.compile(r'@(?:implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+(\S+)')


def gitdir():
    d = subprocess.run(['git', '-C', ROOT, 'rev-parse', '--git-common-dir'], capture_output=True, text=True).stdout.strip()
    return d if os.path.isabs(d) else os.path.join(ROOT, d)


STORE = os.path.join(gitdir(), 'rr-claims.json')
LOCK = os.path.join(gitdir(), 'rr-claims.lock')


def tus():
    return {int(r['tu']): (int(r['start'], 16), int(r['end'], 16), r['class'])
            for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/tus.csv')))}


def tu_of(addr, table):
    return next((k for k, (s, e, _) in table.items() if s <= addr < e), None)


class Locked:
    def __enter__(self):
        self.f = open(LOCK, 'a+')
        fcntl.flock(self.f, fcntl.LOCK_EX)
        self.claims = json.load(open(STORE)) if os.path.exists(STORE) else {}
        now = time.time()
        self.claims = {k: v for k, v in self.claims.items() if v['until'] > now}
        return self

    def save(self):
        tmp = STORE + '.tmp'
        json.dump(self.claims, open(tmp, 'w'), indent=1, sort_keys=True)
        os.replace(tmp, STORE)

    def __exit__(self, *a):
        fcntl.flock(self.f, fcntl.LOCK_UN)
        self.f.close()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('op', choices=['take', 'renew', 'drop', 'list', 'commit'])
    ap.add_argument('tu', nargs='?')
    ap.add_argument('paths', nargs='*')
    ap.add_argument('--who')
    ap.add_argument('--minutes', type=float, default=90)
    ap.add_argument('-m', dest='msg')
    a = ap.parse_args()
    table = tus()
    if a.op != 'list' and not a.who:
        raise SystemExit('--who NAME is required')
    with Locked() as L:
        if a.op == 'list':
            for k, v in sorted(L.claims.items(), key=lambda x: int(x[0])):
                s, e, cls = table[int(k)]
                print(f'TU {k:>4s} 0x{s:06x}..0x{e:06x} {cls:8s} {v["who"]:12s} {int((v["until"] - time.time()) / 60)} min left')
            return 0
        if a.op == 'commit':
            paths = ([a.tu] if a.tu else []) + a.paths
            if not paths or not a.msg:
                raise SystemExit('commit needs -m MESSAGE and at least one path')
            mine = {int(k) for k, v in L.claims.items() if v['who'] == a.who}
            bad = []
            for p in paths:
                rel = os.path.relpath(os.path.abspath(p), ROOT)
                if not rel.startswith('src/') or rel.startswith('src/control/'):
                    bad.append(f'{rel}: only source files under src/ (outside src/control/) are committed this way')
                    continue
                full = os.path.join(ROOT, rel)
                if os.path.exists(full):
                    text = open(full).read()
                else:  # a removal: judged by what the file held when last committed
                    text = subprocess.run(['git', '-C', ROOT, 'show', 'HEAD:' + rel], capture_output=True, text=True).stdout
                for addr, name in TAG.findall(text):
                    t = tu_of(int(addr, 16), table)
                    if t not in mine:
                        bad.append(f'{rel}: 0x{int(addr, 16):06x} {name} is in object file {t}, which {a.who} does not hold')
            if bad:
                print('\n'.join(bad))
                return 1
            rels = [os.path.relpath(os.path.abspath(p), ROOT) for p in paths]
            here = [r for r in rels if os.path.exists(os.path.join(ROOT, r))]
            gone = [r for r in rels if r not in here]
            if here:
                subprocess.run(['git', '-C', ROOT, 'add', '--'] + here, check=True)
            if gone:  # removals, whether or not already removed from the index
                subprocess.run(['git', '-C', ROOT, 'rm', '-q', '--cached', '--ignore-unmatch', '--'] + gone, check=True)
            r = subprocess.run(['git', '-C', ROOT, 'commit', '-q', '--only', '-m', a.msg, '--'] + rels)
            if r.returncode == 0:
                for k in mine:  # a commit renews every claim its author holds
                    L.claims[str(k)]['until'] = time.time() + a.minutes * 60
                L.save()
            return r.returncode
        k = str(int(a.tu, 0))
        if int(k) not in table:
            raise SystemExit(f'no object file {k} in config/us/tus.csv')
        held = L.claims.get(k)
        if a.op == 'take':
            if held and held['who'] != a.who:
                print(f'TU {k} is held by {held["who"]} for {int((held["until"] - time.time()) / 60)} more minutes')
                return 1
            if table[int(k)][2] != 'game':
                print(f'TU {k} is {table[int(k)][2]}, not game code')
                return 1
            L.claims[k] = {'who': a.who, 'until': time.time() + a.minutes * 60}
        elif a.op == 'renew':
            if not held or held['who'] != a.who:
                print(f'{a.who} does not hold TU {k}')
                return 1
            held['until'] = time.time() + a.minutes * 60
        elif a.op == 'drop':
            if held and held['who'] == a.who:
                del L.claims[k]
        L.save()
        print(f'{a.op} TU {k}: ok')
    return 0


if __name__ == '__main__':
    sys.exit(main())
