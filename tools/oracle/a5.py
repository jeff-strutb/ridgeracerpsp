#!/usr/bin/env python3
"""A5, the per-function behaviour gate, run together with A7 on the M1 image.

Retail and build/image/BOOT.M1.BIN (tools/oracle/m1image.py) are run in rrbox on every script with
every tagged function (@implements and @draft, outside src/control/) watched. For each watched
call rrbox logs (Core/RRBox.cpp):
  E  entry: call number, thread, a0-a3, t0-t1, f12-f15
  R  return: v0, v1, f0, the count and hash of every memory write the call made outside its own
     stack frame (callees included, its own thread only), and which of s0-s8 came back changed.
A function PASSES when it was called at least once and every call agrees with retail on: the
entry record; v0 (unless it returns void), v1 (64-bit returns) and f0 (float returns), from its
declared return type; the writes; and no callee-saved register clobbered. UNCOVERED = never
called by any script: not passed. Instruction coverage is measured on the candidate body (union
over scripts). The verdicts go to config/us/t3_live.csv with the source file's hash: a @draft is
T3 only while its row says PASS with full coverage and the hash still matches its source. A7 (--m1: code left out of the RAM hash) runs in the same
pass, so a candidate must also leave every frame's RAM identical.

Time-equalised lockstep: a T3 body may take a different number of CPU cycles, and game code
that reads the clock would then store different values. The candidate run is given retail's call
log (--rr-cycles-ref), and at each watched return rrbox sets emulated time to exactly where retail
was. Behaviour is compared with CPU time held equal at every function boundary; an interrupt
landing inside a T3 body at a different point still shows up as a difference.

    python3 tools/oracle/a5.py [SCRIPT...]
"""
import csv
import datetime
import glob
import hashlib
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
import a7  # noqa: E402

TAG = re.compile(r'@(implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)(?:.*?\*/)\s*\n([^\n{;]*?)\b\3\s*\(', re.S)


def watched():
    """{addr: (kind, name, return-kind)} for every tagged function outside src/control/."""
    out = {}
    for path in glob.glob(os.path.join(ROOT, 'src/**/*.c*'), recursive=True):
        if '/src/control/' in path:
            continue
        text = open(path).read()
        for kind, a, name, decl in TAG.findall(text):
            d = decl.strip()
            rk = 'void' if re.match(r'(static\s+)?void\b', d) else ('float' if re.search(r'\b(float|double)\b', d)
                 else ('wide' if re.search(r'long long|u64|s64', d) else 'int'))
            out[int(a, 16)] = (kind, name, rk)
    return out


def run(exe, script, trace, watch, calls, cycles_ref=None):
    staged = os.path.join(a7.OUT, 'stage', 'BOOT.elf')
    os.makedirs(os.path.dirname(staged), exist_ok=True)
    shutil.copyfile(exe, staged)
    ms = os.path.join(a7.OUT, 'stage', 'memstick')
    shutil.rmtree(ms, ignore_errors=True)
    os.makedirs(ms)
    env = dict(os.environ, RRBOX_EPOCH=a7.EPOCH, TZ='UTC', RRBOX_MEMSTICK=ms)
    cmd = [a7.BOX, staged, '-m', a7.ISO, '-i', '--graphics=software', f'--rr-frames={a7.frames_of(script)}',
           f'--rr-script={script}', f'--rr-trace={trace}', f'--rr-watch={watch}', f'--rr-calls={calls}',
           f'--rr-hash-skip={a7.TEXT_RAM[0]:x}:{a7.TEXT_RAM[1]:x}']
    if cycles_ref:
        cmd.append(f'--rr-cycles-ref={cycles_ref}')
    subprocess.run(cmd, env=env, capture_output=True)


def records(path):
    """{func: [(E fields, R fields), ...]} in call order."""
    out, open_calls = {}, {}
    for line in open(path):
        t = line.split()
        func, call = int(t[1], 16), int(t[2])
        kv = dict(x.split('=', 1) for x in t[3:])
        if t[0] == 'E':
            open_calls[(func, call)] = kv
        else:
            out.setdefault(func, []).append((open_calls.pop((func, call), {}), kv))
    for (func, call), kv in open_calls.items():  # entered, never returned within the run
        out.setdefault(func, []).append((kv, None))
    return out


def compare(rk, ret_r, ret_c):
    if ret_r is None or ret_c is None:
        return None if ret_r == ret_c else 'one side never returned'
    keys = ['writes', 'hash'] + {'void': [], 'int': ['v0'], 'wide': ['v0', 'v1'], 'float': ['f0']}[rk]
    for k in keys:
        if ret_r.get(k) != ret_c.get(k):
            return f'{k} {ret_r.get(k)} vs {ret_c.get(k)}'
    if ret_c.get('clobbered', '000') != '000':
        return f'callee-saved registers clobbered ({ret_c["clobbered"]})'
    return None


def main():
    w = watched()
    scripts = [os.path.abspath(s) for s in sys.argv[1:]] or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
    m1 = os.path.join(ROOT, 'build/image/BOOT.M1.BIN')
    if not os.path.exists(m1):
        raise SystemExit('build the M1 image first: python3 tools/oracle/m1image.py')
    os.makedirs(a7.OUT, exist_ok=True)
    watch = os.path.join(a7.OUT, 'watch.txt')
    sizes = {int(r['addr'], 16): int(r['size']) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))}
    placed = os.path.join(ROOT, 'build/image/m1_placed.txt')
    for line in open(placed) if os.path.exists(placed) else []:
        a, z = line.split()
        sizes[int(a, 16)] = int(z)  # a placed draft: its compiled body, not the padded slot
    open(watch, 'w').write(''.join(f'{a:x} {sizes[a]}\n' for a in sorted(w)))
    missed = {a: None for a in w}  # words never executed in any script (intersection over scripts)
    verdict = {a: ['UNCOVERED', 0, ''] for a in w}
    a7_bad = 0
    for s in scripts:
        name = os.path.splitext(os.path.basename(s))[0]
        files = {}
        for side, exe in (('retail', a7.RETAIL), ('candidate', m1)):
            files[side] = (os.path.join(a7.OUT, f'{name}.{side}.trace'), os.path.join(a7.OUT, f'{name}.{side}.calls'))
            run(exe, s, files[side][0], watch, files[side][1],
                files['retail'][1] if side == 'candidate' else None)
        tr = [l.split() for l in open(files['retail'][0])]
        tc = [l.split() for l in open(files['candidate'][0])]
        first = next((k for k, (x, y) in enumerate(zip(tr, tc)) if x != y), None)
        if first is not None or len(tr) != len(tc):
            a7_bad += 1
            print(f'A7 DIFFERS  {name}: first at frame {first if first is not None else min(len(tr), len(tc))}')
        else:
            print(f'A7 IDENTICAL {name}: {len(tr)} frames')
        for line in open(files['candidate'][1] + '.cov'):
            t = line.split()
            a, miss = int(t[0], 16), {int(x, 16) for x in t[3:]}
            missed[a] = miss if missed[a] is None else missed[a] & miss
        rr, rc = records(files['retail'][1]), records(files['candidate'][1])
        for a in w:
            cr, cc = rr.get(a, []), rc.get(a, [])
            v = verdict[a]
            if v[0] == 'DIFFERS':
                continue
            if len(cr) != len(cc):
                v[0], v[2] = 'DIFFERS', f'{name}: {len(cr)} calls in retail, {len(cc)} in candidate'
                continue
            for k, ((er, xr), (ec, xc)) in enumerate(zip(cr, cc)):
                why = 'entry differs' if er != ec else compare(w[a][2], xr, xc)
                if why:
                    v[0], v[2] = 'DIFFERS', f'{name} call {k}: {why}'
                    break
            else:
                if cr:
                    v[0] = 'PASS'
                    v[1] += len(cr)
    ledger = os.path.join(ROOT, 'config/us/t3_live.csv')
    rows = []
    for a in sorted(w):
        kind, name, rk = w[a]
        v = verdict[a]
        words = sizes[a] // 4
        miss = sorted(missed[a] or [])
        cov = f'{words - len(miss)}/{words}'
        detail = f'{v[1]} calls, coverage {cov}' if v[0] == 'PASS' else v[2]
        if v[0] == 'PASS' and miss:
            detail += ' (never ran: ' + ' '.join(f'{x:x}' for x in miss[:8]) + (' ...' if len(miss) > 8 else '') + ')'
        print(f'{v[0]:9s} 0x{a:06x} {name:24s} {kind:10s} {detail}')
        src = next(p for p in glob.glob(os.path.join(ROOT, 'src/**/*.c*'), recursive=True)
                   if f'0x{a:06x} us {name}' in open(p).read())
        rows.append((f'0x{a:06x}', name, kind, v[0], v[1], cov, os.path.relpath(src, ROOT),
                     hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16], datetime.date.today().isoformat()))
    with open(ledger, 'w') as f:
        f.write('addr,name,kind,verdict,calls,coverage,source,source_sha,date\n')
        for r in rows:
            f.write(','.join(str(x) for x in r) + '\n')
    n = {k: sum(1 for v in verdict.values() if v[0] == k) for k in ('PASS', 'DIFFERS', 'UNCOVERED')}
    print(f"a5: {n['PASS']} pass, {n['DIFFERS']} differ, {n['UNCOVERED']} uncovered; A7 {len(scripts) - a7_bad}/{len(scripts)} identical")
    return 1 if (n['DIFFERS'] or a7_bad) else 0


if __name__ == '__main__':
    sys.exit(main())
