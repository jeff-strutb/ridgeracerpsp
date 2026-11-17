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
    python3 tools/oracle/snap.py test ADDR... [--window N] [--script SCRIPT] [--whole] [--keep]

`test` replaces only the named function's code (retail everywhere else), so what it reports is that
function's behaviour, and records it in config/us/t3_live.csv (evidence snap:SCRIPT@FROM-TO; a
DIFFERS too, so no older PASS outlives it). --whole patches every placed draft, as the M1 image
does, and records nothing.
    python3 tools/oracle/snap.py check SCRIPT FRAME            determinism and empty-patch identity

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


def make(script, every):
    script = script_path(script)
    d = snapdir(script)
    if os.path.exists(os.path.join(d, 'index.json')):
        print(f'snap: {os.path.relpath(d, ROOT)} already made')
        return d
    os.makedirs(d, exist_ok=True)
    frames = a7.frames_of(script)
    saves = list(range(every, frames, every))
    _, wr, _ = watch_files(d)
    calls, trace = os.path.join(d, 'full.calls'), os.path.join(d, 'trace')
    a5.run(a7.RETAIL, script, trace, wr, calls, extra=[f'--rr-save-at={",".join(map(str, saves))}:{d}'])
    # index: the frame each watched function is first entered in (frame f ends at tick[f])
    ticks = [int(line.split()[1]) for line in open(trace) if line.strip()]
    first = {}
    with open(calls, 'rb') as f:
        for line in f:
            if line[:2] == b'E ':
                t = line.split()
                if t[1] not in first:
                    first[t[1]] = int(t[-1][3:])
    import bisect
    index = {k.decode(): bisect.bisect_left(ticks, tk) for k, tk in first.items()}
    os.remove(calls)
    if os.path.exists(calls + '.cov'):
        os.remove(calls + '.cov')
    missing = [f for f in saves if not os.path.exists(os.path.join(d, f'frame_{f:05d}.meta'))]
    if missing:
        raise SystemExit(f'snap: snapshots missing for frames {missing[:5]}...')
    json.dump({'every': every, 'saves': saves, 'first': index}, open(os.path.join(d, 'index.json'), 'w'))
    print(f'snap: {len(saves)} snapshots, {len(index)} functions indexed -> {os.path.relpath(d, ROOT)}')
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


def pick(addr, script=None):
    """(script, snapshot frame, first-call frame) for the earliest first call of `addr`."""
    best = None
    for s in ([script_path(script)] if script else sorted(os.path.join(SCRIPTS, f) for f in os.listdir(SCRIPTS))):
        idx = os.path.join(snapdir(s), 'index.json')
        if not os.path.exists(idx):
            continue
        ix = json.load(open(idx))
        f = ix['first'].get(f'{addr:06x}')
        if f is None:
            continue
        snaps = [x for x in ix['saves'] if x < f]
        if snaps and (best is None or f - snaps[-1] < best[2] - best[1]):
            best = (s, snaps[-1], f)
    return best


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


def test(addrs, window, script, whole=False, keep=False):
    w = a5.watched()
    full = patch_file()
    for addr in addrs:
        patch, words = (full, None) if whole else only(full, [addr])
        if words == 0:
            print(f'0x{addr:06x}: not placed in the M1 image (or identical to retail): nothing to test')
            continue
        p = pick(addr, script)
        if p is None:
            print(f'0x{addr:06x}: no snapshot before its first call (run `snap.py make SCRIPT` for a script that calls it)')
            continue
        s, frame, first = p
        end = first + window
        rt, rc = from_snapshot(s, frame, end)
        ct, cc = from_snapshot(s, frame, end, patch, (rt, rc))
        bad, n = first_diff(rt, ct)
        v = verdicts(w, rc, cc)
        kind, name = w[addr][0], w[addr][1]
        name_s = os.path.splitext(os.path.basename(s))[0]
        print(f'0x{addr:06x} {name} ({kind}): {name_s} from snapshot {frame}, first called in frame {first}, '
              f'compared to frame {end}')
        print(f'  RAM: ' + ('identical on every frame' if bad is None else f'first differs at frame {bad}'))
        print(f'  calls: {v[addr][0]} {v[addr][1]}')
        cov = next((x.split() for x in open(cc + '.cov') if x.startswith(f'{addr:06x} ')), None) if os.path.exists(cc + '.cov') else None
        if cov:
            print(f'  coverage: {cov[2]}/{cov[1]} instructions executed')
        if not whole and cov:
            # the ledger row (a5.write_ledger): this function alone was replaced, so the verdict is
            # its own; a DIFFERS is recorded too, so an older PASS cannot outlive it
            verdict = v[addr][0] if bad is None or v[addr][0] != 'PASS' else 'DIFFERS'
            calls = int(v[addr][1].split()[0]) if verdict == 'PASS' else 0
            src = a5.source_of(addr, name)
            rows = a5.read_ledger()
            rows[f'0x{addr:06x}'] = dict(zip(a5.LEDGER_FIELDS, (
                f'0x{addr:06x}', name, kind, verdict, calls, f'{cov[2]}/{cov[1]}', os.path.relpath(src, ROOT),
                hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16], __import__('datetime').date.today().isoformat(),
                f'snap:{name_s}@{frame}-{end}')))
            a5.write_ledger(rows)
            print(f'  ledger: {verdict} recorded (config/us/t3_live.csv)')
        if not keep:
            for f in (rc, cc):
                os.remove(f)  # call logs run to GBs; traces and coverage are kept
        others = sorted((a for a, x in v.items() if x[0] == 'DIFFERS' and a != addr))
        if others:
            print(f'  other functions differing in this window: ' + ', '.join(f'0x{a:06x}' for a in others[:12])
                  + (' ...' if len(others) > 12 else ''))


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
        test([int(a, 16) for a in args[1:] if a != opt('--window', None) and a != opt('--script', None)],
             int(opt('--window', 120)), opt('--script', None), '--whole' in sys.argv, '--keep' in sys.argv)
    elif args[0] == 'check':
        check(args[1], int(args[2]))
    else:
        raise SystemExit(__doc__)


if __name__ == '__main__':
    sys.exit(main())
