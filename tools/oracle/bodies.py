#!/usr/bin/env python3
"""Candidate bodies for the case replay (tools/oracle/cases.py): every @draft, wherever it fits.

The M1 image (m1image.py) can only place a draft that fits its retail slot, has no jump table of
its own and refers to nothing but provably-retail data, because the image is the game. The case
replay runs one function at a time, so a body may live anywhere:

  * a body that fits goes in its retail slot (padded with nop), as in the M1 image;
  * a larger one goes into the annex, VRAM from 0x04100000 (the replay draws nothing, the
    interpreter runs code there, and j / jal stay in the same 256 MB segment), and the slot
    gets a jump to it (`j annex; nop`), so callers and recursion reach it;
  * read-only data of the draft's own object that is not provably retail's (a jump table, a
    string or a constant at a moved offset) is copied into the annex once per object, its own
    R_MIPS_32 words (jump-table entries) resolved, and the body's references point there;
  * a reference into writable data that is not retail's cannot be given a meaning: refused.

    python3 tools/oracle/bodies.py [--identity]      writes build/oracle/cases/bodies.spec

Spec lines: "OFFSET SLOTSIZE RETKIND HEXBODY LOADADDR" per function, "DATA ADDR HEX" per annexed
section. --identity: every draft's retail bytes in its slot (for recording and the identity check).
"""
import glob
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'analysis'))
import a5  # noqa: E402
import m1image  # noqa: E402
import rrdis  # noqa: E402
import score  # noqa: E402
from prx import put_lo, Elf, R_26, R_HI16, R_LO16  # noqa: E402

BASE = 0x08804000
ANNEX = 0x04100000
ANNEX_END = 0x04200000
R_32 = 2
NOP = b'\0\0\0\0'


class Annex:
    def __init__(self):
        self.at = ANNEX

    def take(self, n):
        a = (self.at + 15) & ~15
        if a + n > ANNEX_END:
            raise SystemExit('bodies: annex full')
        self.at = a + n
        return a


def drafts():
    """{src: [(addr, name)]} for every @draft outside src/control/."""
    out = {}
    for src in sorted(glob.glob(os.path.join(ROOT, 'src/**/*.c*'), recursive=True)):
        if '/src/control/' in src:
            continue
        d = [(int(a, 16), n) for a, n in m1image.DRAFT.findall(open(src).read())]
        if d:
            out[src] = d
    return out


def build(identity=False):
    c = rrdis.load()
    e = c['e']
    w = a5.watched()
    retail = open(os.path.join(ROOT, 'orig/us/BOOT.BIN'), 'rb').read()
    textsec = next(s for s in e.sh if s[1] == 1 and s[2] & 4)
    lines, data, refused = [], [], []
    annex = Annex()
    for src, ds in drafts().items():
        if identity:
            for addr, name in ds:
                start, osize = rrdis.func_at(addr)
                if start != addr:
                    continue
                fo = next(s[4] + addr - s[3] for s in e.sh if s[1] == 1 and s[2] & 2 and s[3] <= addr < s[3] + s[5])
                # retail bytes as loaded: relocations applied (absolute for base 0x08804000)
                lines.append((addr, osize, w.get(addr, ('', '', 'int'))[2], None, BASE + addr))
            continue
        obj = Elf(open(score.compile_obj(src, score.DEFAULT_CC, '-O2 -G0'), 'rb').read())
        syms = obj.symbols()
        plc, n2a, _ = score.locate(obj, syms, score.tags(src))
        res = score.Resolver(obj, syms, n2a, plc, c['rel'], e)
        secaddr = {}  # annexed read-only section -> address
        for addr, name in ds:
            p = next((x for x in plc if x[3] == addr), None)
            start, osize = rrdis.func_at(addr)
            if p is None or start != addr:
                refused.append(f'0x{addr:06x} {name}: not found or not a function start'); continue
            text, cstart, size, _ = p
            load = BASE + addr if size <= osize else annex.take(size)
            body = bytearray(obj.data(text)[cstart:cstart + size])
            why = None

            def here(t):
                # a target in retail space that is inside this draft's own body is in the candidate
                return load + (t - addr) if addr <= t < addr + size else BASE + t

            def section(sec):
                if sec not in secaddr:
                    nm = obj.names[sec]
                    if not nm.startswith(('.rodata', '.gnu.linkonce.r')):
                        return None
                    blob = bytearray(obj.data(sec))
                    a = annex.take(max(len(blob), 4))
                    secaddr[sec] = a
                    for off, rt, si in obj.object_rels(sec):
                        if rt != R_32:
                            continue
                        t = res.target(sec, off, rt, si)
                        if t[0] == 'addr':
                            struct.pack_into('<I', blob, off, here(t[1]))
                        elif t[0] == 'data' and t[1] == sec:
                            struct.pack_into('<I', blob, off, a + t[2])
                        else:
                            return None
                    data.append((a, bytes(blob)))
                return secaddr[sec]

            for off, rtype, si in sorted(r for r in obj.object_rels(text) if cstart <= r[0] < cstart + size):
                tgt = res.target(text, off, rtype, si)
                if tgt[0] == 'addr':
                    a = here(tgt[1])
                elif tgt[0] == 'data':
                    rr = c['rel'].get(addr + off - cstart)
                    t = res.match(tgt, rr)[1] if res.match(tgt, rr)[0] is None else m1image.by_content(res, tgt, c['rel'], addr, osize)
                    if t is not None and not any(r[1] == R_32 for r in obj.object_rels(tgt[1])):
                        a = BASE + t
                    else:
                        sa = section(tgt[1])
                        if sa is None:
                            why = f'reference at +0x{off - cstart:x} into writable or unresolvable data'; break
                        a = sa + tgt[2]
                else:
                    why = tgt[1]; break
                q = off - cstart
                wd = struct.unpack_from('<I', body, q)[0]
                if rtype == R_26:
                    if (a & 0xF0000000) != (load & 0xF0000000):
                        why = 'jump across a 256 MB segment'; break
                    wd = (wd & 0xfc000000) | ((a >> 2) & 0x03ffffff)
                elif rtype == R_HI16:
                    wd = (wd & 0xffff0000) | (((a + 0x8000) >> 16) & 0xffff)
                elif rtype == R_LO16:
                    wd = put_lo(wd, a)
                elif rtype == R_32:
                    wd = a & 0xffffffff
                struct.pack_into('<I', body, q, wd)
            if why:
                refused.append(f'0x{addr:06x} {name}: {why}'); continue
            if load == BASE + addr:
                body += NOP * ((osize - size) // 4)
            lines.append((addr, osize, w.get(addr, ('', '', 'int'))[2], bytes(body), load))
    return lines, data, refused


def write(identity=False):
    lines, data, refused = build(identity)
    out = os.path.join(ROOT, 'build/oracle/cases', 'identity.spec' if identity else 'bodies.spec')
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, 'w') as f:
        for a, blob in data:
            f.write(f'DATA {a:x} {blob.hex()}\n')
        for addr, osize, rk, body, load in lines:
            # identity: the replay takes the slot's own bytes from memory ("-")
            f.write(f'{addr:x} {osize} {rk} {body.hex() if body is not None else "-"} {load:x}\n')
    return out, [x[0] for x in lines], refused


if __name__ == '__main__':
    out, fns, refused = write('--identity' in sys.argv)
    annexed = sum(1 for line in open(out) if not line.startswith('DATA') and int(line.split()[4], 16) < BASE)
    print(f'bodies: {len(fns)} drafts ({annexed} in the annex), {len(refused)} refused -> {os.path.relpath(out, ROOT)}')
    for r in refused:
        print('  refused ' + r)
