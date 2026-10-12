#!/usr/bin/env python3
"""M2 image gate: build BOOT.BIN from the claims and diff it against retail. Must be 0 bytes.

For every `@implements` in the sources graded (filed sources by default):
  * compile it (tools/score.py's pinned compiler and flags, objects rebuilt every run),
  * place the function's bytes at its retail address; refuse a size change or an overlap,
  * write every relocated field from the RESOLVED target (score.Resolver): an address for
    f_/D_/tagged/library symbols; for literal/constant/jump-table data, the retail target,
    accepted only after the resolver has proved the contents equal,
  * regenerate that function's entries in the SCE type-A relocation table (.rel.text) in the
    object's own order, at the positions retail's entries for that range occupy.
Everything unclaimed is filled from the original. The result is written to
build/image/BOOT.BIN (or BOOT.BIN.FAILED) and compared byte for byte.

    python3 tools/image.py                  # filed sources: src/ outside src/control/
    python3 tools/image.py --control        # self-test: also place the control set's EXACT functions
    python3 tools/image.py FILE...          # only these sources
Exit 0 = identical; 1 = differs or a claim cannot be placed; 2 = sources changed during the run.
"""
import glob
import hashlib
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'analysis'))
import score  # noqa: E402
import rrdis  # noqa: E402
from prx import Elf, R_26, R_HI16, R_LO16, SHT_PRXREL  # noqa: E402

R_32 = 2


def sources(argv):
    if [a for a in argv if not a.startswith('--')]:
        return [os.path.abspath(a) for a in argv if not a.startswith('--')]
    out = []
    for ext in ('c', 'cpp'):
        out += glob.glob(os.path.join(ROOT, f'src/**/*.{ext}'), recursive=True)
    if '--control' not in argv:
        out = [p for p in out if '/src/control/' not in p]
    return sorted(out)


def digest(paths):
    h = hashlib.sha256()
    for p in paths:
        h.update(open(p, 'rb').read())
    return h.hexdigest()


def main(argv):
    srcs = sources(argv)
    before = digest(srcs)
    c = rrdis.load()
    e = c['e']
    img = bytearray(e.d)
    seg = [p[2] for p in e.ph]

    def seg_of(addr):
        return max(k for k, base in enumerate(seg) if addr >= base)

    def file_off(addr):
        for s in e.sh:
            if s[1] == 1 and s[2] & 2 and s[3] <= addr < s[3] + s[5]:
                return s[4] + addr - s[3]
        raise KeyError(hex(addr))

    # retail .rel.text entries: position -> address
    rti = e.index('.rel.text')
    rts = e.sh[rti]
    assert rts[1] == SHT_PRXREL
    positions = {}
    for k, o in enumerate(range(rts[4], rts[4] + rts[5], 8)):
        off, info = struct.unpack_from('<II', e.d, o)
        positions.setdefault(seg[(info >> 8) & 0xff] + off, []).append(k)

    claimed, problems, placed_n = [], [], 0
    for src in srcs:
        rel = os.path.relpath(src, ROOT)
        obj = Elf(open(score.compile_obj(src, score.DEFAULT_CC, '-O2 -G0'), 'rb').read())  # adds per-file @cflags
        syms = obj.symbols()
        tg = score.tags(src, claims_only=True)
        if '/src/control/' in src:  # self-test: only what the grader rates EXACT
            exact = {a for a, _, st, _ in score.score(src, score.DEFAULT_CC, '-O2 -G0', False) if st == 'EXACT'}
            tg = [(a, n) for a, n in tg if a in exact]
        plc, n2a, found = score.locate(obj, syms, tg)
        for addr, name in tg:
            if addr not in found:
                problems.append(f'{rel}: 0x{addr:06x} {name}: no such function in the object')
        res = score.Resolver(obj, syms, n2a, plc, c['rel'], e)
        for text, cstart, size, addr in plc:
            tdata = obj.data(text)
            orels = sorted(obj.object_rels(text))
            start, osize = rrdis.func_at(addr)
            if start != addr or size != osize:
                problems.append(f'{rel}: 0x{addr:06x}: size {size} vs retail {osize}; cannot place for M2')
                continue
            if any(a < addr + size and addr < b for a, b in claimed):
                problems.append(f'{rel}: 0x{addr:06x}: overlaps another claim')
                continue
            claimed.append((addr, addr + size))
            body = bytearray(tdata[cstart:cstart + size])
            mine = [r for r in orels if cstart <= r[0] < cstart + size]
            for off, rtype, si in mine:
                tgt = res.target(text, off, rtype, si)
                rr = c['rel'].get(addr + off - cstart)
                if tgt[0] == 'addr':
                    t = tgt[1]
                elif tgt[0] == 'data' and res.match(tgt, rr)[0] is None:
                    t = res.match(tgt, rr)[1]  # contents proved equal: the retail literal is this literal
                else:
                    problems.append(f'{rel}: 0x{addr + off - cstart:06x}: reference cannot be resolved ({tgt[-1]})')
                    continue
                base = seg[seg_of(t)] if rtype != R_26 else 0
                v = t - base
                p = off - cstart
                w = struct.unpack_from('<I', body, p)[0]
                if rtype == R_26:
                    w = (w & 0xfc000000) | ((t >> 2) & 0x03ffffff)
                elif rtype == R_HI16:
                    w = (w & 0xffff0000) | (((v + 0x8000) >> 16) & 0xffff)
                elif rtype == R_LO16:
                    w = (w & 0xffff0000) | (v & 0xffff)
                elif rtype == R_32:
                    w = v & 0xffffffff
                struct.pack_into('<I', body, p, w)
                # regenerate the type-A entry at the table position retail uses for this address
                at = addr + p
                slots = positions.get(at)
                if not slots:
                    problems.append(f'{rel}: 0x{at:06x}: relocation where retail has none')
                    continue
                ofsbase = seg_of(at)
                info = rtype | (ofsbase << 8) | ((seg_of(t) if rtype != R_26 else 0) << 16)
                struct.pack_into('<II', img, rts[4] + 8 * slots[0], at - seg[ofsbase], info)
            o = file_off(addr)
            img[o:o + size] = body
            placed_n += 1
    if digest(srcs) != before:
        print('image: sources changed during the run; nothing to report')
        return 2
    os.makedirs(os.path.join(ROOT, 'build/image'), exist_ok=True)
    ok = not problems and bytes(img) == e.d
    out = os.path.join(ROOT, 'build/image', 'BOOT.BIN' if ok else 'BOOT.BIN.FAILED')
    open(out, 'wb').write(img)
    ndiff = sum(1 for a, b in zip(img, e.d) if a != b)
    for p in problems:
        print('  ' + p)
    print(f'image: {placed_n} functions placed from {len(srcs)} sources; {ndiff} differing bytes; '
          f'{len(problems)} problem(s) -> {os.path.relpath(out, ROOT)}')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
