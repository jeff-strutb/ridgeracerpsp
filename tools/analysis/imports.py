"""Imported system functions of the retail module -> config/us/imports.csv.

Walks .lib.stub (SceLibraryStubTable entries, entLen words each): library name, NID table and
stub table. Each stub in .sceStub.text is 8 bytes (`jr ra; nop` until the loader patches it).
Names come from the NID tables in PPSSPP's HLE sources (build/ext/ppsspp, pinned v1.20.4),
parsed from their `{0xNID, &Wrap..., "name", ...}` rows. A NID PPSSPP does not name is left
blank; never guess one.
Usage: python3 tools/analysis/imports.py
"""
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prx import Elf  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ROW = re.compile(r'\{\s*0[xX]([0-9A-Fa-f]{8})\s*,\s*[^,]*,\s*"([A-Za-z_][\w]*)"')


def ppsspp_names():
    names = {}
    for path in glob.glob(os.path.join(ROOT, 'build/ext/ppsspp/Core/HLE/*.cpp')):
        for nid, name in ROW.findall(open(path, errors='replace').read()):
            names.setdefault(int(nid, 16), name)
    return names


def cstr(e, a):
    out = b''
    while True:
        w = struct.pack('<I', e.word(a & ~3))
        for b in w[a & 3:]:
            if b == 0:
                return out.decode('latin1')
            out += bytes([b])
        a = (a & ~3) + 4


def main():
    e = Elf(open(os.path.join(ROOT, 'orig/us/BOOT.BIN'), 'rb').read())
    names = ppsspp_names()
    i = e.index('.lib.stub')
    a, end = e.addr(i), e.addr(i) + e.sh[i][5]
    rows = []
    while a < end:
        libname_p = e.word(a)
        w1 = e.word(a + 4)
        w2 = e.word(a + 8)
        ent_len = w2 & 0xff
        stub_count = w2 >> 16
        nid_p, stub_p = e.word(a + 12), e.word(a + 16)
        lib = cstr(e, libname_p) if libname_p else ''
        for k in range(stub_count):
            nid = e.word(nid_p + 4 * k)
            rows.append((stub_p + 8 * k, lib, nid, names.get(nid, '')))
        a += 4 * ent_len
        del w1
    dst = os.path.join(ROOT, 'config/us/imports.csv')
    with open(dst, 'w') as f:
        f.write('stub,library,nid,name\n')
        for s, lib, nid, nm in sorted(rows):
            f.write(f'0x{s:06x},{lib},0x{nid:08x},{nm}\n')
    named = sum(1 for r in rows if r[3])
    print(f'{len(rows)} imports from {len({r[1] for r in rows})} libraries; {named} named from {len(names)} PPSSPP NIDs -> {dst}')


if __name__ == '__main__':
    main()
