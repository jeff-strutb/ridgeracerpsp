#!/usr/bin/env python3
"""A7, the whole-image behaviour gate: a candidate BOOT.BIN must behave exactly like retail.

Both executables are booted the same way in rrbox (PPSSPP v1.20.4 headless with
tools/oracle/ppsspp-rrbox.patch, built by tools/oracle/build.sh): from the host file, with the
retail US disc mounted for data, on the pure interpreter (the JIT patches its own markers into
emulated RAM), as the 32 MB launch hardware, Wi-Fi off, sound mixing and I/O on emulated time,
both clocks fixed (RRBOX_EPOCH, TZ=UTC), and an empty memory stick in the repo for every run
(RRBOX_MEMSTICK; PPSSPP's default is the host's ~/.ppsspp, which must never be touched). Ten one-minute runs of retail were identical.

For every input script in tools/oracle/scripts/ (or those named), each executable's per-frame
trace (emulated cycles + hash of all 24 MB of user RAM) is recorded, and the traces must agree
on every frame. The first differing frame is reported.

    python3 tools/oracle/a7.py [--image build/image/BOOT.BIN] [SCRIPT...]
Exit 0 = identical on every script; 1 = a script differs.
"""
import argparse
import glob
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BOX = os.path.join(ROOT, 'build/ext/ppsspp-build/PPSSPPHeadless')
ISO = os.path.join(ROOT, 'references/Ridge Racer (USA) (En,Fr,De,Es,It).iso')
RETAIL = os.path.join(ROOT, 'orig/us/BOOT.BIN')
OUT = os.path.join(ROOT, 'build/oracle/a7')
EPOCH = '1104537600'  # 2005-01-01 00:00:00 UTC


def frames_of(script):
    """A script's length: its `# frames N` header, else the last input frame + 600."""
    n, last = None, 0
    for line in open(script):
        t = line.split()
        if line.startswith('# frames') and len(t) >= 3:
            n = int(t[2])
        elif t and t[0].isdigit():
            last = max(last, int(t[0]))
    return n or last + 600


TEXT_RAM = (0x08804040, 0x089723fc)  # .text as loaded (module base 0x08804000, measured)


def run(exe, script, trace, skip_code=False):
    # PPSSPP decides what a file is by its extension, and a .BIN is taken for a raw disc image
    # (it then boots nothing at all), so the executable is staged as .elf. The launch path is
    # written into emulated RAM, so retail and candidate are staged at the SAME path, one run
    # after the other.
    staged = os.path.join(OUT, 'stage', 'BOOT.elf')
    os.makedirs(os.path.dirname(staged), exist_ok=True)
    with open(exe, 'rb') as src, open(staged, 'wb') as dst:
        dst.write(src.read())
    # every run starts from the same EMPTY memory stick inside the repo (never the host's ~/.ppsspp)
    ms = os.path.join(OUT, 'stage', 'memstick')
    shutil.rmtree(ms, ignore_errors=True)
    os.makedirs(ms)
    env = dict(os.environ, RRBOX_EPOCH=EPOCH, TZ='UTC', RRBOX_MEMSTICK=ms)
    cmd = [BOX, staged, '-m', ISO, '-i', '--graphics=software', f'--rr-frames={frames_of(script)}',
           f'--rr-script={script}', f'--rr-trace={trace}']
    if skip_code:
        cmd.append(f'--rr-hash-skip={TEXT_RAM[0]:x}:{TEXT_RAM[1]:x}')
    subprocess.run(cmd, env=env, capture_output=True)
    return [line.split() for line in open(trace)]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--image', default=os.path.join(ROOT, 'build/image/BOOT.BIN'))
    ap.add_argument('--m1', action='store_true',
                    help='leave the game code (.text) out of the RAM hash: for images whose T3 bodies differ in bytes')
    ap.add_argument('scripts', nargs='*')
    a = ap.parse_args()
    scripts = a.scripts or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
    if not os.path.exists(BOX):
        raise SystemExit('rrbox not built: run tools/oracle/build.sh')
    os.makedirs(OUT, exist_ok=True)
    bad = 0
    for s in scripts:
        name = os.path.splitext(os.path.basename(s))[0]
        r = run(RETAIL, s, os.path.join(OUT, f'{name}.retail.txt'), a.m1)
        c = run(os.path.abspath(a.image), s, os.path.join(OUT, f'{name}.candidate.txt'), a.m1)
        first = next((k for k, (x, y) in enumerate(zip(r, c)) if x != y), None)
        if first is None and len(r) != len(c):
            first = min(len(r), len(c))
        if first is None and r:
            print(f'IDENTICAL  {name}: {len(r)} frames')
        else:
            bad += 1
            why = 'trace lengths differ' if first >= min(len(r), len(c)) else \
                ('emulated time differs' if r[first][1] != c[first][1] else 'user RAM differs')
            print(f'DIFFERS    {name}: first at frame {first} ({why}); {len(r)} vs {len(c)} frames')
    print(f'a7: {len(scripts) - bad}/{len(scripts)} scripts identical')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
