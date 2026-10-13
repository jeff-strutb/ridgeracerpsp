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
    # Each script has its own stage directory, so scripts run in parallel; retail and candidate
    # of one script still use the same staged path (it is written into emulated RAM).
    stage = os.path.join(a7.OUT, 'stage', os.path.splitext(os.path.basename(script))[0])
    staged = os.path.join(stage, 'BOOT.elf')
    os.makedirs(stage, exist_ok=True)
    shutil.copyfile(exe, staged)
    ms = os.path.join(stage, 'memstick')
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


def summarise(path):
    """One streaming pass over a call log: {func: [calls, base, v0, v1, f0, clobbered]}.

    base digests, call by call in return order (calls never returned last, in entry order), the
    entry record and the call's writes and write hash; v0, v1 and f0 digest those return
    registers separately, so the comparison can pick them by the function's return type. Two
    logs agree on a function exactly when records()/compare() would find every call equal."""
    out, open_calls = {}, {}
    new = lambda: [0, hashlib.blake2b(digest_size=16), hashlib.blake2b(digest_size=16),
                   hashlib.blake2b(digest_size=16), hashlib.blake2b(digest_size=16), 0]
    with open(path, 'rb') as f:
        for line in f:
            if line[0] == 69:  # 'E': remember the entry record until the call returns
                k, _, rest = line.partition(b' ')[2].partition(b' ')
                call, _, entry = rest.partition(b' ')
                open_calls[(k, call)] = entry.rstrip(b'\n')
                continue
            t = line.split()  # R func call v0= v1= f0= writes= hash= clobbered= cyc=
            entry = open_calls.pop((t[1], t[2]), b'')
            d = out.get(t[1]) or out.setdefault(t[1], new())
            d[0] += 1
            d[1].update(entry + b'|' + t[6] + b'|' + t[7] + b';')
            d[2].update(t[3] + b';')
            d[3].update(t[4] + b';')
            d[4].update(t[5] + b';')
            if t[8] != b'clobbered=000':
                d[5] += 1
    for (k, call), entry in open_calls.items():
        d = out.get(k) or out.setdefault(k, new())
        d[0] += 1
        d[1].update(entry + b'|NORET;')
    return {int(k, 16): [d[0]] + [h.hexdigest() for h in d[1:5]] + [d[5]] for k, d in out.items()}


def script_pair(s, m1, watch, watch_retail):
    """Run one script on retail (or reuse the cached retail run) and on the candidate, and
    summarise both call logs. Runs in its own process, one per script."""
    name = os.path.splitext(os.path.basename(s))[0]
    files = {side: (os.path.join(a7.OUT, f'{name}.{side}.trace'), os.path.join(a7.OUT, f'{name}.{side}.calls'))
             for side in ('retail', 'candidate')}
    # A retail run depends only on the executable, the script, the watched addresses and rrbox.
    key = hashlib.sha256(b''.join(open(f, 'rb').read() for f in (a7.RETAIL, s, watch_retail, a7.BOX))).hexdigest()[:24]
    cached = os.path.join(ROOT, 'build/oracle/retail-cache', key)
    tr_, ca_ = files['retail']
    if not (os.path.exists(cached + '.trace') and os.path.exists(cached + '.calls') and os.path.exists(cached + '.sum')):
        run(a7.RETAIL, s, tr_, watch_retail, ca_)
        os.makedirs(os.path.dirname(cached), exist_ok=True)
        open(cached + '.sum.tmp', 'w').write(repr(summarise(ca_)))
        for src, dst in ((tr_, cached + '.trace'), (ca_, cached + '.calls'), (cached + '.sum.tmp', cached + '.sum')):
            if src != cached + '.sum.tmp':
                shutil.copyfile(src, dst + '.tmp')
                src = dst + '.tmp'
            os.replace(src, dst)
    # the candidate run reads retail's call log for the time lockstep; the cached copy serves
    run(m1, s, files['candidate'][0], watch, files['candidate'][1], cached + '.calls')
    tr = open(cached + '.trace').read().split('\n')
    tc = open(files['candidate'][0]).read().split('\n')
    first = next((k for k, (x, y) in enumerate(zip(tr, tc)) if x != y), None)
    if first is None and len(tr) != len(tc):
        first = min(len(tr), len(tc))
    cov = [line.split() for line in open(files['candidate'][1] + '.cov')]
    files['retail'] = (cached + '.trace', cached + '.calls')
    return name, first, len(tr) - 1, eval(open(cached + '.sum').read()), summarise(files['candidate'][1]), cov, files


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


DETAIL = False


def main():
    w = watched()
    global DETAIL
    DETAIL = '--detail' in sys.argv
    scripts = [os.path.abspath(s) for s in sys.argv[1:] if not s.startswith('--')] or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
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
    # Retail's watch list uses the map's sizes (placed draft sizes only matter for the candidate's
    # coverage), so a retail run stays cacheable while drafts change.
    mapsz = {int(r['addr'], 16): int(r['size']) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))}
    watch_retail = os.path.join(a7.OUT, 'watch_retail.txt')
    open(watch_retail, 'w').write(''.join(f'{a:x} {mapsz[a]}\n' for a in sorted(w)))
    missed = {a: None for a in w}  # words never executed in any script (intersection over scripts)
    verdict = {a: ['UNCOVERED', 0, ''] for a in w}
    a7_bad = 0
    from concurrent.futures import ProcessPoolExecutor
    with ProcessPoolExecutor(len(scripts) or 1) as ex:
        results = list(ex.map(script_pair, scripts, [m1] * len(scripts), [watch] * len(scripts),
                              [watch_retail] * len(scripts)))
    for name, first, nframes, sr, sc, cov, files in results:
        if first is not None:
            a7_bad += 1
            print(f'A7 DIFFERS  {name}: first at frame {first}')
        else:
            print(f'A7 IDENTICAL {name}: {nframes} frames')
        for t in cov:
            a, miss = int(t[0], 16), {int(x, 16) for x in t[3:]}
            missed[a] = miss if missed[a] is None else missed[a] & miss
        for a in w:
            v = verdict[a]
            if v[0] == 'DIFFERS':
                continue
            r, c = sr.get(a), sc.get(a)
            nr, nc = (r[0] if r else 0), (c[0] if c else 0)
            if nr != nc:
                v[0], v[2] = 'DIFFERS', f'{name}: {nr} calls in retail, {nc} in candidate'
                continue
            if not nr:
                continue
            rk = w[a][2]
            fields = {'void': [1], 'int': [1, 2], 'wide': [1, 2, 3], 'float': [1, 4]}[rk]
            bad = [('entry/writes', 'v0', 'v1', 'f0')[x - 1] for x in fields if r[x] != c[x]]
            if bad:
                v[0], v[2] = 'DIFFERS', f'{name}: calls differ in {", ".join(bad)} (rerun with --detail for the call)'
            elif c[5]:
                v[0], v[2] = 'DIFFERS', f'{name}: callee-saved registers clobbered in {c[5]} calls'
            else:
                v[0] = 'PASS'
                v[1] += nr
            if v[0] == 'DIFFERS' and DETAIL:
                cr, cc = records(files['retail'][1]).get(a, []), records(files['candidate'][1]).get(a, [])
                for n, ((er, xr), (ec, xc)) in enumerate(zip(cr, cc)):
                    why = 'entry differs' if er != ec else compare(rk, xr, xc)
                    if why:
                        v[2] = f'{name} call {n}: {why}'
                        break
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
