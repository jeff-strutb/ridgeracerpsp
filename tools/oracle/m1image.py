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
Drafts listed in build/oracle/m1_exclude.txt are left out (tools/oracle/isolate.py).
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
    # Drafts tools/oracle/isolate.py found to diverge from retail first: left out, so they do not
    # change game state under every later watched call. Lines: ADDR REASON.
    excluded = {}
    xf = os.path.join(ROOT, 'build/oracle/m1_exclude.txt')
    if os.path.exists(xf):
        for line in open(xf):
            if line.strip():
                a, _, why = line.strip().partition(' ')
                excluded[int(a, 16)] = why
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
            if addr in excluded:
                refused.append(f'0x{addr:06x} {name}: excluded (build/oracle/m1_exclude.txt: {excluded[addr]})'); continue
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
                    t = res.match(tgt, rr)[1] if res.match(tgt, rr)[0] is None else by_content(res, tgt, c['rel'], addr, osize)
                    if t is None:
                        refused.append(f'0x{addr:06x} {name}: data reference at +0x{off - cstart:x} not provably retail\'s'); ok = False; break
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
    fixed = repair_hi16(e, seg, rts, bytes(open(os.path.join(ROOT, 'build/image/BOOT.BIN'), 'rb').read()), img)
    out = os.path.join(ROOT, 'build/image/BOOT.M1.BIN')
    open(out, 'wb').write(img)
    open(os.path.join(ROOT, 'build/image/m1_placed.txt'), 'w').write(''.join(f'{a:x} {z}\n' for a, z in placed))
    for r in refused:
        print('  refused ' + r)
    print(f'm1image: {len(placed)} draft bodies placed in their slots, {len(refused)} refused, '
          f'{fixed} HI16 entries outside them pre-resolved -> {os.path.relpath(out, ROOT)}')


def by_content(res, tgt, rel, addr, osize):
    """Retail target for a draft's data reference whose position differs from retail's
    (scheduling moved it), proved by content: of every data target retail's own relocations
    inside this function's range refer to, exactly one may hold the same bytes (the same
    Resolver.check the positional proof uses). None if none or more than one does.
    Oracle placement only: T4 grading (tools/score.py) stays positional."""
    e = res.e
    code = [(e.sh[i][3], e.sh[i][3] + e.sh[i][5]) for i in range(len(e.sh)) if e.sh[i][2] & 4]
    cands = set()
    for a in range(addr, addr + osize, 4):
        rr = rel.get(a)
        # Only retail's own paired HI16/LO16 targets (not the LO16 'alts' guesses), and only data.
        if rr and rr['type'] in (R_HI16, R_LO16) and rr['target'] is not None \
                and not any(lo <= rr['target'] < hi for lo, hi in code):
            cands.add(rr['target'])
    ok = [x for x in sorted(cands) if res.check(tgt, x) is None]
    return ok[0] if len(ok) == 1 else None


def repair_hi16(e, seg, rts, old, img):
    """The loader (PPSSPP ElfReader, like the PSP's) completes each HI16 with the low half of the
    NEXT LO16 or R_MIPS_16 entry in the table, skipping every other type, and retail's table often
    pairs a HI16 with a LO16 in another function. Setting a placed slot's entries to R_MIPS_NONE
    can therefore re-pair a HI16 outside the slot with a LO16 of the other sign, and its upper half
    comes out 0x10000 off (first seen as f_04d68c passing 0x08a5500c for 0x08a4500c). Every HI16
    whose loaded value changes is written as retail's absolute value for BASE and set to NONE."""
    def table(buf):
        ents = []
        for o in range(rts[4], rts[4] + rts[5], 8):
            off, info = struct.unpack_from('<II', buf, o)
            ents.append((o, seg[(info >> 8) & 0xff] + off, info))
        return ents

    def word(buf, at):
        fo = next(s[4] + at - s[3] for s in e.sh if s[1] == 1 and s[3] <= at < s[3] + s[5])
        return struct.unpack_from('<I', buf, fo)[0], fo

    def loaded_hi(buf, ents, r):
        o, at, info = ents[r]
        op = word(buf, at)[0]
        rel = (info >> 16) & 0xff
        cur = ((op & 0xffff) << 16) + BASE + (seg[rel] if rel < len(seg) else 0)
        for t in range(r + 1, len(ents)):
            tt = ents[t][2] & 0xf
            if tt in (R_LO16, 1):  # R_MIPS_16 is taken as the partner too
                lo = word(buf, ents[t][1])[0] & 0xffff
                cur += lo - 0x10000 if lo & 0x8000 else lo
                break
        return ((cur + 0x8000) >> 16) & 0xffff

    before, after = table(old), table(img)
    n = 0
    for r, (o, at, info) in enumerate(after):
        if info & 0xf != R_HI16:
            continue
        want = loaded_hi(old, before, r)
        if loaded_hi(img, after, r) != want:
            w, fo = word(img, at)
            struct.pack_into('<I', img, fo, (w & 0xffff0000) | want)
            struct.pack_into('<I', img, o + 4, info & ~0xff)  # R_MIPS_NONE: already absolute
            n += 1
    return n


if __name__ == '__main__':
    main()
