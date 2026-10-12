#!/usr/bin/env python3
"""Build the M1 oracle image: the M2 image plus every @draft body placed in its own slot.

Only for the oracle (rrbox), which always loads the module at 0x08804000:
  * starts from build/image/BOOT.BIN (tools/image.py must pass first);
  * each @draft function whose compiled body fits in the retail function's range is written
    there, with its relocations resolved to ABSOLUTE addresses for base 0x08804000, the rest of
    the range filled with nop, and retail's relocation entries inside the range set to
    R_MIPS_NONE (the loader skips them; the table keeps its length, so nothing else moves);
  * a body larger than its slot, or one with its own jump table, is refused (not placeable
    without moving code), as is any reference the resolver cannot prove.
Output: build/image/BOOT.M1.BIN, and build/image/m1_placed.txt (address and compiled size of
each placed draft: the size A5 measures instruction coverage over).

    python3 tools/oracle/m1image.py
"""
import glob
import os
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'analysis'))
import score  # noqa: E402
import rrdis  # noqa: E402
from prx import put_lo, Elf, R_26, R_HI16, R_LO16, SHT_PRXREL  # noqa: E402

BASE = 0x08804000
R_32 = 2
DRAFT = score.re.compile(r'@draft\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)')


def main():
    if subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/image.py')]).returncode != 0:
        raise SystemExit('m1image: the M2 image does not build; fix that first')
    c = rrdis.load()
    e = c['e']
    img = bytearray(open(os.path.join(ROOT, 'build/image/BOOT.BIN'), 'rb').read())
    seg = [p[2] for p in e.ph]
    rti = e.index('.rel.text')
    rts = e.sh[rti]
    assert rts[1] == SHT_PRXREL
    placed, refused = [], []
    srcs = sorted(glob.glob(os.path.join(ROOT, 'src/**/*.c'), recursive=True) +
                  glob.glob(os.path.join(ROOT, 'src/**/*.cpp'), recursive=True))
    srcs = [p for p in srcs if '/src/control/' not in p]
    for src in srcs:
        drafts = [(int(a, 16), n) for a, n in DRAFT.findall(open(src).read())]
        if not drafts:
            continue
        obj = Elf(open(score.compile_obj(src, score.DEFAULT_CC, '-O2 -G0'), 'rb').read())
        syms = obj.symbols()
        plc, n2a, found = score.locate(obj, syms, score.tags(src))
        res = score.Resolver(obj, syms, n2a, plc, c['rel'], e)
        for addr, name in drafts:
            p = next((x for x in plc if x[3] == addr), None)
            start, osize = rrdis.func_at(addr)
            if p is None or start != addr:
                refused.append(f'0x{addr:06x} {name}: not found or not a function start'); continue
            text, cstart, size, _ = p
            tdata = obj.data(text)
            orels = sorted(obj.object_rels(text))
            if size > osize:
                refused.append(f'0x{addr:06x} {name}: {size} B does not fit the {osize} B slot'); continue
            body = bytearray(tdata[cstart:cstart + size]) + bytes(osize - size)
            ok = True
            for off, rtype, si in [r for r in orels if cstart <= r[0] < cstart + size]:
                tgt = res.target(text, off, rtype, si)
                if tgt[0] == 'addr':
                    t = tgt[1]
                elif tgt[0] == 'data':
                    rr = c['rel'].get(addr + off - cstart)
                    if res.match(tgt, rr)[0] is not None:
                        refused.append(f'0x{addr:06x} {name}: data reference at +0x{off - cstart:x} not provably retail\'s'); ok = False; break
                    t = res.match(tgt, rr)[1]
                    if obj.names[tgt[1]].startswith('.rodata') and any(r[1] == R_32 for r in obj.object_rels(tgt[1])):
                        refused.append(f'0x{addr:06x} {name}: has a jump table; not placeable in place'); ok = False; break
                else:
                    refused.append(f'0x{addr:06x} {name}: {tgt[1]}'); ok = False; break
                a = BASE + t
                q = off - cstart
                w = struct.unpack_from('<I', body, q)[0]
                if rtype == R_26:
                    w = (w & 0xfc000000) | ((a >> 2) & 0x03ffffff)
                elif rtype == R_HI16:
                    w = (w & 0xffff0000) | (((a + 0x8000) >> 16) & 0xffff)
                elif rtype == R_LO16:
                    w = put_lo(w, a)
                elif rtype == R_32:
                    w = a & 0xffffffff
                struct.pack_into('<I', body, q, w)
            if not ok:
                continue
            fo = next(s[4] + addr - s[3] for s in e.sh if s[1] == 1 and s[2] & 2 and s[3] <= addr < s[3] + s[5])
            img[fo:fo + osize] = body
            for k, o in enumerate(range(rts[4], rts[4] + rts[5], 8)):
                off, info = struct.unpack_from('<II', img, o)
                at = seg[(info >> 8) & 0xff] + off
                if addr <= at < addr + osize:
                    struct.pack_into('<I', img, o + 4, info & ~0xff)  # R_MIPS_NONE
            placed.append((addr, size))
    out = os.path.join(ROOT, 'build/image/BOOT.M1.BIN')
    open(out, 'wb').write(img)
    open(os.path.join(ROOT, 'build/image/m1_placed.txt'), 'w').write(''.join(f'{a:x} {z}\n' for a, z in placed))
    for r in refused:
        print('  refused ' + r)
    print(f'm1image: {len(placed)} draft bodies placed in their slots, {len(refused)} refused -> {os.path.relpath(out, ROOT)}')


if __name__ == '__main__':
    main()
