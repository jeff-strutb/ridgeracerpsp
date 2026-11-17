#!/usr/bin/env python3
"""Denominator of the decompilation: what there is to do, and what is tagged.

    tools/denominator.py [SRC_DIR]     table for src/ (default <repo>/src)
    tools/denominator.py --selftest    prove the tag checks catch planted faults

Classes come from config/us/fence.csv (built by tools/analysis/libfence.py;
see docs/DENOMINATOR.md).  Only 'game' is in the denominator; 'library' is
toolchain/SDK code and 'unknown' is neither proven, so both stay out of the
numerator and the denominator.

Tags are comments `@implements 0xADDR us NAME` (claimed byte-exact) and
`@draft 0xADDR us NAME` (differing), ADDR in the executable's own address
space.  The tool counts what is tagged; it does not judge any claim.
Reported problems: a tag whose address is not a function start in
config/us/funcs.csv, an address tagged more than once, tags for regions
other than 'us', and malformed tags.
"""
import csv
import re
import sys
import tempfile
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE / 'analysis')]
import refcheck              # noqa: E402

ROOT = HERE.parent
TAG = re.compile(r'@(implements|draft)\b(.*)')
FORM = re.compile(r'\s+(0x[0-9a-fA-F]+)\s+(\w+)\s+(\S+)')
SUFFIXES = {'.c', '.cc', '.cpp', '.cxx', '.h', '.hh', '.hpp', '.inc', '.s', '.S'}


def load_csv(name):
    with open(ROOT / 'config' / 'us' / name) as fh:
        return list(csv.DictReader(fh))


def load_fence():
    funcs = {int(r['addr'], 16): int(r['size']) for r in load_csv('funcs.csv')}
    fence = {}
    for r in load_csv('fence.csv'):
        a = int(r['addr'], 16)
        if funcs.get(a) != int(r['size']):
            raise SystemExit(f'denominator: fence.csv row {a:#x} does not match funcs.csv '
                             '(rerun tools/analysis/libfence.py)')
        fence[a] = (int(r['size']), r['class'])
    if set(fence) != set(funcs):
        raise SystemExit('denominator: fence.csv and funcs.csv list different functions')
    return fence


def scan_tags(src):
    tags, bad = [], []
    for path in sorted(Path(src).rglob('*')):
        if not path.is_file() or path.suffix not in SUFFIXES:
            continue
        for n, line in enumerate(path.read_text(errors='replace').splitlines(), 1):
            for m in TAG.finditer(line):
                f = FORM.match(m.group(2))
                where = f'{path.relative_to(src)}:{n}'
                if not f:
                    bad.append((where, line.strip()))
                    continue
                tags.append({'kind': m.group(1), 'addr': int(f.group(1), 16),
                             'region': f.group(2), 'name': f.group(3), 'where': where})
    return tags, bad


def compute(fence, tags):
    us = [t for t in tags if t['region'] == 'us']
    other = [t for t in tags if t['region'] != 'us']
    by_addr = defaultdict(list)
    for t in us:
        by_addr[t['addr']].append(t)
    not_start = [t for t in us if t['addr'] not in fence]
    twice = {a: ts for a, ts in by_addr.items() if len(ts) > 1}
    cls_n, cls_b = Counter(), Counter()
    for a, (size, c) in fence.items():
        cls_n[c] += 1
        cls_b[c] += size
    state_n, state_b = Counter(), Counter()
    outside = Counter()
    for a, (size, c) in fence.items():
        kinds = {t['kind'] for t in by_addr.get(a, [])}
        st = ('implements+draft' if len(kinds) > 1 else
              'implements' if kinds == {'implements'} else
              'draft' if kinds == {'draft'} else 'untagged')
        if c == 'game':
            state_n[st] += 1
            state_b[st] += size
        elif st != 'untagged':
            outside[(c, st)] += 1
    return {'cls_n': cls_n, 'cls_b': cls_b, 'state_n': state_n, 'state_b': state_b,
            'outside': outside, 'not_start': not_start, 'twice': twice, 'other': other,
            'ntags': len(tags)}


def report(r, bad):
    print('class      functions        bytes')
    for c in ('game', 'library', 'unknown'):
        print(f'{c:9s} {r["cls_n"][c]:10d} {r["cls_b"][c]:12d}')
    print(f'{"total":9s} {sum(r["cls_n"].values()):10d} {sum(r["cls_b"].values()):12d}')
    print()
    print('game functions by tag   functions        bytes')
    for s in ('implements', 'draft', 'implements+draft', 'untagged'):
        if s == 'implements+draft' and not r['state_n'][s]:
            continue
        print(f'  {s:20s} {r["state_n"][s]:10d} {r["state_b"][s]:12d}')
    print()
    print(f'tags read: {r["ntags"]}')
    for (c, s), n in sorted(r['outside'].items()):
        print(f'tagged {s} but class {c} (outside the denominator): {n}')
    print(f'tags whose address is not a function start: {len(r["not_start"])}')
    for t in r['not_start'][:50]:
        print(f'   {t["addr"]:#08x} @{t["kind"]} {t["name"]}  {t["where"]}')
    if len(r['not_start']) > 50:
        print(f'   ... {len(r["not_start"]) - 50} more')
    print(f'addresses tagged more than once: {len(r["twice"])}')
    for a, ts in sorted(r['twice'].items())[:50]:
        print(f'   {a:#08x} ' + ', '.join(f'@{t["kind"]} {t["where"]}' for t in ts))
    if r['other']:
        print(f'tags for other regions (not counted): {len(r["other"])}')
    if bad:
        print(f'malformed tags: {len(bad)}')
        for w, line in bad[:20]:
            print(f'   {w}: {line}')


def selftest():
    fence = load_fence()
    fails = []
    game = sorted(a for a, (s, c) in fence.items() if c == 'game')
    lib = next(a for a, (s, c) in fence.items() if c == 'library')
    with tempfile.TemporaryDirectory() as td:
        d = Path(td)
        (d / 'a.cpp').write_text(
            f'/* @implements {game[0]:#08x} us f_a */\n'
            f'/* @draft {game[1]:#08x} us f_b */\n'
            f'/* @implements {game[1]:#08x} us f_b_again */\n'     # planted: twice
            f'/* @implements {game[2] + 4:#08x} us f_mid */\n'     # planted: not a start
            f'/* @implements {lib:#08x} us f_lib */\n'             # planted: library
            f'/* @draft 0x1234 eu f_eu */\n'                      # planted: other region
            f'/* @implements nonsense */\n')                      # planted: malformed
        tags, bad = scan_tags(d)
        r = compute(fence, tags)
    checks = [
        (r['state_n']['implements'] == 1, 'one game implements'),
        (r['state_n']['implements+draft'] == 1, 'one game implements+draft'),
        (len(r['twice']) == 1 and game[1] in r['twice'], 'address tagged twice'),
        (len(r['not_start']) == 1 and r['not_start'][0]['addr'] == game[2] + 4, 'not a start'),
        (r['outside'][('library', 'implements')] == 1, 'library tag outside'),
        (len(r['other']) == 1, 'other region'),
        (len(bad) == 1, 'malformed'),
        (r['state_n']['untagged'] == len(game) - 2, 'untagged count'),
    ]
    for ok, what in checks:
        print(('ok   ' if ok else 'FAIL ') + what)
        if not ok:
            fails.append(what)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


def main(argv):
    refcheck.require('us', 'BOOT.BIN')
    if argv[1:] == ['--selftest']:
        return selftest()
    src = Path(argv[1]) if len(argv) > 1 else ROOT / 'src'
    fence = load_fence()
    tags, bad = scan_tags(src)
    r = compute(fence, tags)
    report(r, bad)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
