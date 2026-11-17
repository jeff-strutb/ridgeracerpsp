#!/usr/bin/env python3
"""Snapshot start: test a function from a saved point just before it runs, not from power-on.

A full A5 run replays every script from a blank memory stick, so a function first called at frame
5,000 is only reached if every draft on the way there behaves exactly as retail does. Here retail is
run once per script with rrbox saving the whole machine every N frames (--rr-save-at), and an index
records the frame each watched function is first called in. Testing a function then:

  1. picks the last snapshot before that frame;
  2. runs retail from it (rrbox --rr-start: the machine is loaded at the end of the first frame,
     the script continues from the snapshot's frame with its buttons as they were held);
  3. runs the candidate from the same snapshot with the M1 image's code written into RAM
     (--rr-patch: every .text word in which the loaded M1 image differs from loaded retail);
  4. compares the two the way A5 and A7 do: each watched call's entry, writes and return, and every
     frame's RAM hash outside code and stacks; time is held equal at every watched boundary.

Both runs start from one machine state, so the comparison does not depend on how faithfully a
loaded snapshot reproduces a straight run, only on rrbox being deterministic (checked by `check`).

    python3 tools/oracle/snap.py make SCRIPT [--every N]       snapshots and index (once per script)
    python3 tools/oracle/snap.py test ADDR... [--window N|end] [--script S1,S2] [--whole] [--keep]

`test` replaces only the named function's code (retail everywhere else), so what it reports is that
function's behaviour, in every script that calls it (PASS only if all pass; coverage is the union),
and records it in config/us/t3_live.csv (evidence snap:SCRIPT@FROM-TO; a
DIFFERS too, so no older PASS outlives it). --whole patches every placed draft, as the M1 image
does, and records nothing.
    python3 tools/oracle/snap.py check SCRIPT FRAME            determinism and empty-patch identity

A script with a '# base NAME' line plays NAME's inputs up to some frame: `make` reuses NAME's
snapshots before that frame and plays only from the last of them.

Snapshots live in build/oracle/snapshots/<script>-<key>/ (key: retail image, script, rrbox binary):
frame_NNNNN.state / .meta / .memstick/, index.json (watched function -> first frame), trace.
"""
import csv
import hashlib
import json
import os
import shutil
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
import a5  # noqa: E402
import a7  # noqa: E402

SNAPS = os.path.join(ROOT, 'build/oracle/snapshots')
RAM_BASE = 0x08800000
SCRIPTS = os.path.join(ROOT, 'tools/oracle/scripts')


def script_path(s):
    return s if os.path.exists(s) else os.path.join(SCRIPTS, s if s.endswith('.txt') else s + '.txt')


def snapdir(script):
    name = os.path.splitext(os.path.basename(script))[0]
    key = hashlib.sha256(b''.join(open(f, 'rb').read() for f in (a7.RETAIL, script, a7.BOX))).hexdigest()[:24]
    return os.path.join(SNAPS, f'{name}-{key}')


def watch_files(d):
    """Retail's watch list (map sizes) and the candidate's (placed drafts' compiled sizes), as A5."""
    w = a5.watched()
    mapsz = {int(r['addr'], 16): int(r['size']) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))}
    sizes = dict(mapsz)
    placed = os.path.join(ROOT, 'build/image/m1_placed.txt')
    for line in open(placed) if os.path.exists(placed) else []:
        a, z = line.split()
        sizes[int(a, 16)] = int(z)
    wr, wc = os.path.join(d, 'watch_retail.txt'), os.path.join(d, 'watch.txt')
    open(wr, 'w').write(''.join(f'{a:x} {mapsz[a]}\n' for a in sorted(w)))
    open(wc, 'w').write(''.join(f'{a:x} {sizes[a]}\n' for a in sorted(w)))
    return w, wr, wc


def inputs(script):
    """{frame: line} of a script's input lines (comments and the frame count left out)."""
    out = {}
    for line in open(script):
        t = line.split()
        if t and not line.startswith('#'):
            out[int(t[0])] = ' '.join(t[1:])
    return out


def base_of(script):
    """The script named on a '# base NAME' line: this script plays the same inputs up to some
    frame, so that script's snapshots before it are this script's too."""
    for line in open(script):
        if line.startswith('# base '):
            return script_path(line.split()[2])
    return None


def make(script, every):
    script = script_path(script)
    d = snapdir(script)
    if os.path.exists(os.path.join(d, 'index.json')):
        print(f'snap: {os.path.relpath(d, ROOT)} already made')
        return d
    os.makedirs(d, exist_ok=True)
    frames = a7.frames_of(script)
    _, wr, _ = watch_files(d)
    calls, trace = os.path.join(d, 'full.calls'), os.path.join(d, 'trace')
    base, start, kept = base_of(script), None, {}
    if base:
        bd = make(base, every)
        bix = json.load(open(os.path.join(bd, 'index.json')))
        ri, si = inputs(base), inputs(script)
        # the first frame whose held buttons differ: a snapshot at the end of an earlier frame
        # is the same machine in both scripts
        div = min([f for f in set(ri) | set(si) if ri.get(f) != si.get(f)] or [frames])
        earlier = [f for f in bix['saves'] if f < div]
        if not earlier:
            raise SystemExit(f'snap: {os.path.basename(script)} differs from its base before its first snapshot')
        start = earlier[-1]
        for f in earlier:
            src = os.path.join(bd, f'frame_{f:05d}')
            dst = os.path.join(d, f'frame_{f:05d}')
            for ext in ('.state', '.meta'):
                if not os.path.exists(dst + ext):
                    os.link(src + ext, dst + ext)
            if not os.path.exists(dst + '.memstick'):
                shutil.copytree(src + '.memstick', dst + '.memstick')
        kept = {k: v for k, v in bix['first'].items() if v <= start}
    saves = [f for f in range(every, frames, every) if start is None or f > start]
    extra = [f'--rr-save-at={",".join(map(str, saves))}:{d}'] if saves else []
    if start is not None:
        snap = os.path.join(d, f'frame_{start:05d}')
        a5.run(a7.RETAIL, script, trace, wr, calls, extra=extra + [f'--rr-start={snap}'], memstick=snap + '.memstick')
    else:
        a5.run(a7.RETAIL, script, trace, wr, calls, extra=extra)
    # index: the frame each watched function is first entered in (frame f ends at its trace tick)
    tr = [line.split() for line in open(trace) if line.strip()]
    ticks, fnums = [int(t[1]) for t in tr], [int(t[0]) for t in tr]
    first = {}
    with open(calls, 'rb') as f:
        for line in f:
            if line[:2] == b'E ':
                t = line.split()
                if t[1] not in first:
                    first[t[1]] = int(t[-1][3:])
    import bisect
    index = {k.decode(): fnums[min(bisect.bisect_left(ticks, tk), len(fnums) - 1)] for k, tk in first.items()}
    index.update(kept)  # first called before the run's start: the base script's frame
    os.remove(calls)
    if os.path.exists(calls + '.cov'):
        os.remove(calls + '.cov')
    allsaves = sorted(int(f[6:11]) for f in os.listdir(d) if f.startswith('frame_') and f.endswith('.meta'))
    missing = [f for f in saves if f not in allsaves]
    if missing:
        raise SystemExit(f'snap: snapshots missing for frames {missing[:5]}...')
    json.dump({'every': every, 'saves': allsaves, 'first': index, 'base': os.path.basename(base) if base else None,
               'start': start}, open(os.path.join(d, 'index.json'), 'w'))
    print(f'snap: {len(allsaves)} snapshots ({len(saves)} new' + (f', from {os.path.basename(base)} frame {start}' if base else '')
          + f'), {len(index)} functions indexed -> {os.path.relpath(d, ROOT)}')
    return d


def dump_text(exe, out):
    """User RAM of `exe` loaded and run for one frame (code is static from then on)."""
    stage = os.path.join(SNAPS, 'stage-dump')
    shutil.rmtree(stage, ignore_errors=True)
    os.makedirs(os.path.join(stage, 'memstick'))
    shutil.copyfile(exe, os.path.join(stage, 'BOOT.elf'))
    env = dict(os.environ, RRBOX_EPOCH=a7.EPOCH, TZ='UTC', RRBOX_MEMSTICK=os.path.join(stage, 'memstick'))
    subprocess.run([a7.BOX, os.path.join(stage, 'BOOT.elf'), '-m', a7.ISO, '-i', '--graphics=software',
                    '--rr-frames=1', '--rr-dump-frame=0', f'--rr-dump={out}'], env=env,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=120)
    return open(out, 'rb').read()


def patch_file():
    """The candidate's code as RAM writes: every .text word where the loaded M1 image differs
    from loaded retail, in runs. Cached per M1 image."""
    m1 = os.path.join(ROOT, 'build/image/BOOT.M1.BIN')
    key = hashlib.sha256(open(m1, 'rb').read() + open(a7.RETAIL, 'rb').read()).hexdigest()[:24]
    out = os.path.join(SNAPS, f'patch-{key}.txt')
    if os.path.exists(out):
        return out
    os.makedirs(SNAPS, exist_ok=True)
    r = dump_text(a7.RETAIL, os.path.join(SNAPS, 'dump-r.ram'))
    c = dump_text(m1, os.path.join(SNAPS, 'dump-c.ram'))
    lo, hi = a7.TEXT_RAM
    runs, start = [], None
    for a in range(lo, hi + 4, 4):
        o = a - RAM_BASE
        diff = a < hi and r[o:o + 4] != c[o:o + 4]
        if diff and start is None:
            start = a
        elif not diff and start is not None:
            runs.append((start, a))
            start = None
    # outside .text the two loaded images must agree: drafts reference retail's own data
    lo_o, hi_o = lo - RAM_BASE, hi - RAM_BASE
    other = sum(1 for k in range(0, len(r), 4) if not lo_o <= k < hi_o and r[k:k + 4] != c[k:k + 4])
    for f in ('dump-r.ram', 'dump-c.ram'):
        for x in (f, f + '.scratch'):
            p = os.path.join(SNAPS, x)
            if os.path.exists(p):
                os.remove(p)
    if other:
        raise SystemExit(f'snap: the loaded M1 image differs from retail in {other} words outside .text')
    tmp = out + '.tmp'
    # pieces of at most 4 KB: rrbox reads a patch line into a 64 KB buffer
    open(tmp, 'w').write(''.join(f'{a:08x} {c[a - RAM_BASE:min(a + 4096, e) - RAM_BASE].hex()}\n'
                                 for s, e in runs for a in range(s, e, 4096)))
    os.replace(tmp, out)
    words = sum(e - s for s, e in runs) // 4
    print(f'snap: patch of {words} code words in {len(runs)} runs -> {os.path.relpath(out, ROOT)}')
    return out


def short_script(script, end, d):
    body = [line for line in open(script) if not line.startswith('# frames')]
    p = os.path.join(d, f'upto_{end:05d}.txt')
    open(p, 'w').write(f'# frames {end}\n' + ''.join(body))
    return p


def from_snapshot(script, frame, end, patch=None, ref=None, tag=None):
    """Run from snapshot `frame` to frame `end`: retail (patch None) or the candidate. Returns
    (trace, calls) paths. A candidate run is given retail's run for the time lockstep and stops
    at the first frame whose RAM differs from it."""
    d = snapdir(script)
    _, wr, wc = watch_files(d)
    run_dir = os.path.join(d, 'runs')
    os.makedirs(run_dir, exist_ok=True)
    side = tag or ('candidate' if patch else 'retail')
    trace, calls = os.path.join(run_dir, f'{frame}-{end}.{side}.trace'), os.path.join(run_dir, f'{frame}-{end}.{side}.calls')
    snap = os.path.join(d, f'frame_{frame:05d}')
    extra = [f'--rr-start={snap}'] + ([f'--rr-patch={patch}'] if patch else [])
    ref_trace = open(ref[0]).read().split('\n') if ref else None
    cap = max(2 * os.path.getsize(ref[1]), 2**30) if ref else None
    a5.run(a7.RETAIL, short_script(script, end, run_dir), trace, wc if patch else wr, calls,
           ref[1] if ref else None, cap, ref_trace, extra=extra, memstick=snap + '.memstick')
    return trace, calls


def first_diff(tr, tc):
    a = [x for x in open(tr).read().split('\n') if x]
    b = [x for x in open(tc).read().split('\n') if x]
    k = next((i for i, (x, y) in enumerate(zip(a, b)) if x.split()[:3] != y.split()[:3]), None)
    if k is None and len(a) != len(b):
        k = min(len(a), len(b))
    return (int(a[k].split()[0]) if k < len(a) else int(b[k].split()[0])) if k is not None else None, len(a)


def verdicts(w, rcalls, ccalls, only=None):
    keys = {b'%06x' % a: v[3] for a, v in w.items()}
    sr, sc = a5.summarise(rcalls, keys), a5.summarise(ccalls, keys)
    out = {}
    for a in (only or w):
        r, c = sr.get(a), sc.get(a)
        nr, nc = (r[0] if r else 0), (c[0] if c else 0)
        if nr != nc:
            out[a] = ('DIFFERS', f'{nr} calls in retail, {nc} in candidate')
        elif not nr:
            out[a] = ('UNCOVERED', '')
        else:
            fields = {'void': [1], 'int': [1, 2], 'wide': [1, 2, 3], 'float': [1, 4]}[w[a][2]]
            bad = [('entry/writes', 'v0', 'v1', 'f0')[x - 1] for x in fields if r[x] != c[x]]
            if bad:
                out[a] = ('DIFFERS', 'calls differ in ' + ', '.join(bad))
            elif c[5]:
                out[a] = ('DIFFERS', f'callee-saved registers clobbered in {c[5]} calls')
            else:
                out[a] = ('PASS', f'{nr} calls')
    return out


def picks(addr, scripts=None):
    """[(script, snapshot frame, first-call frame)]: for each script with snapshots (or each named
    one) whose run calls `addr`, the last snapshot before its first call."""
    out = []
    names = [script_path(x) for x in scripts] if scripts else sorted(os.path.join(SCRIPTS, f) for f in os.listdir(SCRIPTS))
    for s in names:
        idx = os.path.join(snapdir(s), 'index.json')
        if not os.path.exists(idx):
            continue
        ix = json.load(open(idx))
        f = ix['first'].get(f'{addr:06x}')
        snaps = [x for x in ix['saves'] if f is not None and x < f]
        if snaps:
            out.append((s, snaps[-1], f))
    return out


def only(patch, addrs):
    """The part of `patch` inside the given functions (retail's ranges): the candidate is then
    retail with just those functions replaced, so a difference is theirs."""
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    import rrdis
    ranges = [(RAM_BASE + 0x4000 + a, RAM_BASE + 0x4000 + a + rrdis.func_at(a)[1]) for a in addrs]
    out = patch + '.' + '_'.join(f'{a:06x}' for a in addrs)
    lines = []
    for line in open(patch):
        at, hx = line.split()
        at = int(at, 16)
        for lo, hi in ranges:
            s, e = max(at, lo), min(at + len(hx) // 2, hi)
            if s < e:
                lines.append(f'{s:08x} {hx[2 * (s - at):2 * (e - at)]}\n')
    open(out, 'w').write(''.join(lines))
    return out, sum(len(x.split()[1]) // 8 for x in lines)


def test(addrs, window, scripts, whole=False, keep=False):
    """Test each function in every script that calls it (or the named ones). The verdict is PASS
    only if every script passes; coverage is the union of the words executed in all of them."""
    w = a5.watched()
    full = patch_file()
    for addr in addrs:
        patch, words = (full, None) if whole else only(full, [addr])
        if words == 0:
            print(f'0x{addr:06x}: not placed in the M1 image (or identical to retail): nothing to test')
            continue
        runs = picks(addr, scripts)
        if not runs:
            print(f'0x{addr:06x}: no snapshot before its first call (run `snap.py make SCRIPT` for a script that calls it)')
            continue
        kind, name = w[addr][0], w[addr][1]
        print(f'0x{addr:06x} {name} ({kind})')
        verdict, calls, executed, total, evidence = 'PASS', 0, set(), None, []
        for s, frame, first in runs:
            end = a7.frames_of(s) - 1 if window == 'end' else min(first + int(window), a7.frames_of(s) - 1)
            rt, rc = from_snapshot(s, frame, end)
            ct, cc = from_snapshot(s, frame, end, patch, (rt, rc))
            bad, n = first_diff(rt, ct)
            v = verdicts(w, rc, cc)
            name_s = os.path.splitext(os.path.basename(s))[0]
            ok = v[addr][0] == 'PASS' and bad is None
            cov = next((x.split() for x in open(cc + '.cov') if x.startswith(f'{addr:06x} ')), None) if os.path.exists(cc + '.cov') else None
            line = (f'  {name_s} from snapshot {frame} (first call {first}) to {end}: {v[addr][0]} {v[addr][1]}; RAM '
                    + ('identical' if bad is None else f'differs from frame {bad}'))
            if cov:
                total = int(cov[1])
                miss = {int(x, 16) for x in cov[3:]}
                executed |= {addr + 4 * k for k in range(total)} - miss
                line += f'; {cov[2]}/{cov[1]} executed'
            print(line)
            others = sorted((a for a, x in v.items() if x[0] == 'DIFFERS' and a != addr))
            if others:
                print(f'    other functions differing: ' + ', '.join(f'0x{a:06x}' for a in others[:12]) + (' ...' if len(others) > 12 else ''))
            if not ok:
                verdict = 'DIFFERS'
            calls += int(v[addr][1].split()[0]) if v[addr][0] == 'PASS' else 0
            evidence.append(f'{name_s}@{frame}-{end}')
            if not keep:
                for f in (rc, cc):
                    os.remove(f)  # call logs run to GBs; traces and coverage are kept
        cov_s = f'{len(executed)}/{total}' if total else '0/0'
        print(f'  overall: {verdict}, {calls} calls, {cov_s} instructions executed over {len(runs)} script(s)')
        if not whole and total:
            # the ledger row (a5.write_ledger): this function alone was replaced, so the verdict is
            # its own; a DIFFERS is recorded too, so an older PASS cannot outlive it
            src = a5.source_of(addr, name)
            rows = a5.read_ledger()
            rows[f'0x{addr:06x}'] = dict(zip(a5.LEDGER_FIELDS, (
                f'0x{addr:06x}', name, kind, verdict, calls if verdict == 'PASS' else 0, cov_s, os.path.relpath(src, ROOT),
                hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16], __import__('datetime').date.today().isoformat(),
                'snap:' + '+'.join(evidence))))
            a5.write_ledger(rows)
            print(f'  ledger: {verdict} recorded (config/us/t3_live.csv)')


def check(script, frame):
    """Determinism and identity: retail from the snapshot twice, and the candidate with an empty
    patch, must agree on every frame and every call."""
    script = script_path(script)
    w = a5.watched()
    end = frame + 120
    r1 = from_snapshot(script, frame, end, tag='retail')
    r2 = from_snapshot(script, frame, end, tag='retail2')
    empty = os.path.join(SNAPS, 'patch-empty.txt')
    open(empty, 'w').write('')
    e = from_snapshot(script, frame, end, patch=empty, ref=r1, tag='empty')
    for name, other in (('retail twice', r2), ('empty patch', e)):
        bad, n = first_diff(r1[0], other[0])
        v = verdicts(w, r1[1], other[1])
        diff = [a for a, x in v.items() if x[0] == 'DIFFERS']
        called = sum(1 for x in v.values() if x[0] != 'UNCOVERED')
        print(f'{name}: {n} frames, RAM ' + ('identical' if bad is None else f'differs at frame {bad}')
              + f'; {called} functions called, {len(diff)} differ' + (f' ({", ".join("0x%06x" % a for a in diff[:8])})' if diff else ''))


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    opt = lambda k, d: sys.argv[sys.argv.index(k) + 1] if k in sys.argv else d
    if not args:
        raise SystemExit(__doc__)
    if args[0] == 'make':
        make(args[1], int(opt('--every', 250)))
    elif args[0] == 'test':
        sc = opt('--script', None)
        test([int(a, 16) for a in args[1:] if a != opt('--window', None) and a != sc],
             opt('--window', '120'), sc.split(',') if sc else None, '--whole' in sys.argv, '--keep' in sys.argv)
    elif args[0] == 'check':
        check(args[1], int(args[2]))
    else:
        raise SystemExit(__doc__)


if __name__ == '__main__':
    sys.exit(main())
