#!/usr/bin/env python3
"""Behaviour (T3) by inputs and outputs: record each function's real calls once, validate any time.

A function is behaviour-exact when the same inputs give the same outputs. So:

  record   play a script once on retail with rrbox --rr-record. At calls of each placed draft the
           original body runs as normal and one case is kept per distinct input: the entry
           registers, every byte the call read before writing it (callees included: its inputs),
           and at the return every byte it changed outside its own stack frame and its registers
           (its outputs). Calls with a system call, an interrupt or a thread switch inside cannot be
           replayed and are not recorded. Up to --per-fn distinct cases per function (default 200).
  validate boot rrbox once (no game is played), and for each case write its inputs into RAM, set
           its registers, run the candidate's body (retail's callees) to its return, and compare:
           the case's output bytes, nothing else changed outside its own frame, v0 / v1 / f0 as the
           declared return type uses them, sp, $s0-$s8, $f20-$f31. A system call, an invalid jump or
           no return within the budget DIFFERS. Reads of bytes the original never read are reported
           beside the verdict (the case cannot speak for them).

    python3 tools/oracle/cases.py record [SCRIPT...] [--per-fn N]
    python3 tools/oracle/cases.py validate [ADDR...] [--no-ledger]
    python3 tools/oracle/cases.py identity [ADDR...]       candidate = retail's own body: all PASS

Cases live in build/oracle/cases/<script>/<offset>.cases. Verdicts go to config/us/t3_live.csv
(evidence cases:SCRIPTS; coverage = the candidate's instructions run over all cases).
"""
import glob
import os
import shutil
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import a5  # noqa: E402
import a7  # noqa: E402
import lock  # noqa: E402
import snap  # noqa: E402

CASES = os.path.join(ROOT, 'build/oracle/cases')


def rrbox(args, frames, script=None, memstick=None):
    stage = os.path.join(CASES, 'stage')
    shutil.rmtree(stage, ignore_errors=True)
    os.makedirs(os.path.join(stage, 'memstick'))
    if memstick:
        shutil.rmtree(os.path.join(stage, 'memstick'))
        shutil.copytree(memstick, os.path.join(stage, 'memstick'))
    shutil.copyfile(a7.RETAIL, os.path.join(stage, 'BOOT.elf'))
    env = dict(os.environ, RRBOX_EPOCH=a7.EPOCH, TZ='UTC', RRBOX_MEMSTICK=os.path.join(stage, 'memstick'))
    cmd = [a7.BOX, os.path.join(stage, 'BOOT.elf'), '-m', a7.ISO, '-i', '--graphics=software', f'--rr-frames={frames}']
    if script:
        cmd.append(f'--rr-script={script}')
    p = subprocess.run(cmd + args, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True, errors='replace')
    if p.returncode:
        raise SystemExit(f'rrbox failed ({p.returncode}): {p.stderr[-400:]}')


def record(scripts, per_fn):
    sp, fns = lock.spec(identity=True)
    for s in scripts:
        name = os.path.splitext(os.path.basename(s))[0]
        d = os.path.join(CASES, name)
        shutil.rmtree(d, ignore_errors=True)
        os.makedirs(d)
        t = time.time()
        rrbox([f'--rr-record={sp}:{d}:{per_fn}'], a7.frames_of(s), s)
        n = sum(1 for line in open(os.path.join(d, 'record.log')) if line.startswith('CASE'))
        k = len(glob.glob(os.path.join(d, '*.cases')))
        print(f'cases: {name}: {n} cases for {k} functions in {time.time() - t:.0f} s -> {os.path.relpath(d, ROOT)}')


def validate(addrs, identity, ledger):
    w = a5.watched()
    sp, fns = lock.spec(identity, set(addrs) if addrs else None)
    dirs = sorted(d for d in glob.glob(os.path.join(CASES, '*')) if os.path.isdir(d) and d != os.path.join(CASES, 'stage'))
    res = {a: {'pass': 0, 'diff': 0, 'first': None, 'unrec': 0, 'exec': set(), 'words': 0, 'scripts': []} for a in fns}
    t = time.time()
    for d in dirs:
        if not any(os.path.exists(os.path.join(d, f'{a:06x}.cases')) for a in fns):
            continue
        log = os.path.join(d, 'replay.log')
        rrbox([f'--rr-replay={sp}:{d}:{log}'], 2)
        name = os.path.basename(d)
        for line in open(log):
            tk = line.split(' ', 3)
            if tk[0] == 'NOCASES':
                continue
            a = int(tk[1], 16)
            r = res[a]
            if tk[0] == 'COV':
                words, n = int(tk[2]), int(tk[3].split()[0])
                miss = {int(x, 16) for x in tk[3].split()[1:]}
                r['words'] = words
                r['exec'] |= {a + 4 * k for k in range(words)} - miss
                continue
            if name not in r['scripts']:
                r['scripts'].append(name)
            if ' | reads ' in line:
                r['unrec'] += 1
            if tk[0] == 'PASS':
                r['pass'] += 1
            else:
                r['diff'] += 1
                if r['first'] is None:
                    r['first'] = f'{name} call {tk[2]}: {tk[3].strip()}'
    took = time.time() - t
    n = {'PASS': 0, 'DIFFERS': 0, 'NO CASES': 0}
    rows = a5.read_ledger()
    import datetime
    import hashlib
    for a in sorted(res):
        r = res[a]
        cases = r['pass'] + r['diff']
        v = 'DIFFERS' if r['diff'] else ('PASS' if r['pass'] else 'NO CASES')
        n[v] += 1
        if v == 'NO CASES':
            continue
        name = w[a][1] if a in w else '?'
        print(f'{v:8s} 0x{a:06x} {name:28s} {r["pass"]}/{cases} cases'
              + (f'; first: {r["first"]}' if r['first'] else '')
              + (f'; {r["unrec"]} cases read bytes the original did not' if r['unrec'] else '')
              + f'; coverage {len(r["exec"])}/{r["words"]}')
        if ledger and not identity:
            src = a5.source_of(a, name)
            rows[f'0x{a:06x}'] = dict(zip(a5.LEDGER_FIELDS, (
                f'0x{a:06x}', name, w[a][0], 'PASS' if v == 'PASS' else 'DIFFERS', r['pass'] if v == 'PASS' else 0,
                f'{len(r["exec"])}/{r["words"]}', os.path.relpath(src, ROOT),
                hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16], datetime.date.today().isoformat(),
                'cases:' + '+'.join(r['scripts']))))
    if ledger and not identity:
        a5.write_ledger(rows)
    print(f'cases: {n["PASS"]} pass, {n["DIFFERS"]} differ, {n["NO CASES"]} without cases; replay took {took:.1f} s')


def main():
    args = [x for x in sys.argv[1:] if not x.startswith('--')]
    opt = lambda k, d: sys.argv[sys.argv.index(k) + 1] if k in sys.argv else d
    if not args:
        raise SystemExit(__doc__)
    if args[0] == 'record':
        per = opt('--per-fn', '200')
        scripts = [snap.script_path(x) for x in args[1:] if x != per] or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
        record(scripts, int(per))
    elif args[0] in ('validate', 'identity'):
        validate([int(x, 16) for x in args[1:]], args[0] == 'identity', '--no-ledger' not in sys.argv)
    else:
        raise SystemExit(__doc__)


if __name__ == '__main__':
    sys.exit(main())
