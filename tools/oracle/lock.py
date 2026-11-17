#!/usr/bin/env python3
"""Per-call lockstep: test every placed draft on the exact inputs it gets in play.

At each real call of a tested function rrbox (--rr-lockstep) runs the original body, keeps its
outputs, rolls memory and registers back to the entry, runs the candidate's body for that slot
from the same state, and compares: every byte either changed outside its own stack frame, the
return registers its declared type uses, sp and the callee-saved registers ($s0-$s8,
$f20-$f31). Then the original's results are put back and the game carries on as retail. So each
call is an independent input/output test of one function: no draft's verdict depends on any
other draft, and the game never leaves retail's path.

A call is skipped (not tested) when the original makes a system call, is interrupted, or the
thread switches inside it: those inputs cannot be replayed to the candidate. A candidate that
makes a system call or does not return within its budget DIFFERS.

    python3 tools/oracle/lock.py run [SCRIPT...] [--per-fn N] [--only ADDR,...] [--no-ledger]
    python3 tools/oracle/lock.py identity [SCRIPT...]     candidate = retail's own bytes: all PASS

Scripts default to every tools/oracle/scripts/*.txt. With snapshots made (tools/oracle/snap.py
make) a script starts from its snapshot just before the first call of the --only functions.
Verdicts go to config/us/t3_live.csv with evidence lock:SCRIPTS, coverage the union over scripts.
"""
import csv
import datetime
import glob
import hashlib
import json
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import a5  # noqa: E402
import a7  # noqa: E402
import snap  # noqa: E402
import rrdis  # noqa: E402

OUT = os.path.join(ROOT, 'build/oracle/lock')
RAM_BASE = 0x08800000
MODULE = 0x08804000


def loaded(exe, tag):
    """User RAM with `exe` loaded (one frame), cached per image."""
    key = hashlib.sha256(open(exe, 'rb').read() + open(a7.BOX, 'rb').read()).hexdigest()[:24]
    p = os.path.join(OUT, f'{tag}-{key}.ram')
    if not os.path.exists(p):
        os.makedirs(OUT, exist_ok=True)
        snap.dump_text(exe, p + '.tmp')
        os.replace(p + '.tmp', p)
        if os.path.exists(p + '.tmp.scratch'):
            os.remove(p + '.tmp.scratch')
    return open(p, 'rb').read()


def spec(identity=False, only=None):
    """The lockstep spec: one line per placed draft whose loaded body differs from retail's."""
    w = a5.watched()
    r = loaded(a7.RETAIL, 'retail')
    c = r if identity else loaded(os.path.join(ROOT, 'build/image/BOOT.M1.BIN'), 'm1')
    placed = [int(line.split()[0], 16) for line in open(os.path.join(ROOT, 'build/image/m1_placed.txt'))]
    lines, fns = [], []
    for a in placed:
        if only and a not in only:
            continue
        size = rrdis.func_at(a)[1]
        o = MODULE + a - RAM_BASE
        body = c[o:o + size]
        if not identity and body == r[o:o + size]:
            continue  # byte-identical to retail once loaded: nothing to test
        rk = w[a][2] if a in w else 'int'
        lines.append(f'{a:x} {size} {rk} {body.hex()}\n')
        fns.append(a)
    p = os.path.join(OUT, 'identity.spec' if identity else 'm1.spec')
    os.makedirs(OUT, exist_ok=True)
    open(p, 'w').write(''.join(lines))
    return p, fns


def run_script(script, spec_path, per_fn, start=None):
    """rrbox on retail with the lockstep on; returns (log, cov) paths."""
    name = os.path.splitext(os.path.basename(script))[0]
    log, cov = os.path.join(OUT, f'{name}.lock'), os.path.join(OUT, f'{name}.cov')
    empty = os.path.join(OUT, 'nowatch.txt')
    open(empty, 'w').write('')
    extra = [f'--rr-lockstep={spec_path}:{log}:{cov}']
    if per_fn:
        extra.append(f'--rr-lockstep-per-fn={per_fn}')
    ms = None
    if start:
        extra.append(f'--rr-start={start}')
        ms = start + '.memstick'
    for p in (log, cov):
        if os.path.exists(p):
            os.remove(p)
    a5.run(a7.RETAIL, script, os.path.join(OUT, f'{name}.trace'), empty, os.path.join(OUT, f'{name}.calls'),
           extra=extra, memstick=ms)
    return log, cov


def summarise(results, fns):
    """{addr: dict} over all scripts: tested, pass, first diff, skips, coverage union."""
    out = {a: {'calls': 0, 'tested': 0, 'pass': 0, 'diff': None, 'ndiff': 0, 'skip': {}, 'exec': set(), 'words': 0}
           for a in fns}
    for name, (log, cov) in results.items():
        if os.path.exists(log):
            for line in open(log):
                t = line.split(' ', 3)
                a = int(t[1], 16)
                if a not in out:
                    continue
                if t[0] == 'PASS':
                    out[a]['pass'] += 1
                elif t[0] == 'DIFF':
                    out[a]['ndiff'] += 1
                    if out[a]['diff'] is None:
                        out[a]['diff'] = f'{name} call {t[2]}: {t[3].strip()}'
                elif t[0] == 'SKIP':
                    why = t[3].strip()
                    out[a]['skip'][why] = out[a]['skip'].get(why, 0) + 1
        if os.path.exists(cov):
            for line in open(cov):
                t = line.split()
                a = int(t[0], 16)
                if a not in out:
                    continue
                words = int(t[1])
                miss = {int(x, 16) for x in t[5:]}
                out[a]['words'] = words
                out[a]['calls'] += int(t[3])
                out[a]['tested'] += int(t[4])
                out[a]['exec'] |= {a + 4 * k for k in range(words)} - miss
    return out


def record(s, w, evidence):
    rows = a5.read_ledger()
    today = datetime.date.today().isoformat()
    for a, v in s.items():
        kind, name = w[a][0], w[a][1]
        verdict = 'DIFFERS' if v['ndiff'] else ('PASS' if v['pass'] else 'UNCOVERED')
        src = a5.source_of(a, name)
        rows[f'0x{a:06x}'] = dict(zip(a5.LEDGER_FIELDS, (
            f'0x{a:06x}', name, kind, verdict, v['pass'] if verdict == 'PASS' else 0,
            f'{len(v["exec"])}/{v["words"]}', os.path.relpath(src, ROOT),
            hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16], today, evidence)))
    a5.write_ledger(rows)


def report(s, w):
    n = {'PASS': 0, 'DIFFERS': 0, 'UNCOVERED': 0}
    for a in sorted(s):
        v = s[a]
        verdict = 'DIFFERS' if v['ndiff'] else ('PASS' if v['pass'] else 'UNCOVERED')
        n[verdict] += 1
        skips = sum(v['skip'].values())
        detail = (f'{v["pass"]} pass' + (f', {v["ndiff"]} differ ({v["diff"]})' if v['ndiff'] else '')
                  + (f', {skips} skipped ({"; ".join(f"{k} x{c}" for k, c in v["skip"].items())})' if skips else '')
                  + f'; coverage {len(v["exec"])}/{v["words"]}; {v["calls"]} calls seen')
        print(f'{verdict:9s} 0x{a:06x} {w[a][1] if a in w else "?":28s} {detail}')
    print(f'lock: {n["PASS"]} pass, {n["DIFFERS"]} differ, {n["UNCOVERED"]} not tested')


def main():
    args = [x for x in sys.argv[1:] if not x.startswith('--')]
    opt = lambda k: sys.argv[sys.argv.index(k) + 1] if k in sys.argv else None
    if not args or args[0] not in ('run', 'identity'):
        raise SystemExit(__doc__)
    identity = args[0] == 'identity'
    only = {int(x, 16) for x in opt('--only').split(',')} if opt('--only') else None
    skip_vals = {opt('--per-fn'), opt('--only')}
    scripts = [snap.script_path(x) for x in args[1:] if x not in skip_vals] or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
    per_fn = int(opt('--per-fn')) if opt('--per-fn') else 0
    w = a5.watched()
    sp, fns = spec(identity, only)
    print(f'lock: {len(fns)} functions under test' + (' (identity: retail bytes)' if identity else ''))
    results = {}
    for s in scripts:
        start = None
        if only:
            ps = [p for a in only for p in snap.picks(a, [s])]
            if ps:
                frame = min(p[1] for p in ps)
                start = os.path.join(snap.snapdir(s), f'frame_{frame:05d}')
        name = os.path.splitext(os.path.basename(s))[0]
        results[name] = run_script(s, sp, per_fn, start)
    s = summarise(results, fns)
    report(s, w)
    if not identity and '--no-ledger' not in sys.argv:
        record({a: v for a, v in s.items() if v['tested'] or v['calls']}, w, 'lock:' + '+'.join(results))
        print('lock: verdicts recorded in config/us/t3_live.csv')


if __name__ == '__main__':
    sys.exit(main())
