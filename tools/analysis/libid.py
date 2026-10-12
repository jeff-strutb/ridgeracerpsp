"""Identify library functions in the retail module by fingerprint -> config/us/libfuncs.csv.

Every function symbol in the libraries shipped with psp-gcc 1.3.1 and 1.7.1 (newlib libc/libm,
libstdc++, libsupc++, libgcc, crt0/crt*) is reduced to its words with relocated fields masked
(prx.relmask). A retail function from config/us/funcs.csv is identified when its masked words
are IDENTICAL to a library function's (same length, same relocation types at the same words)
AND that fingerprint occurs at exactly one retail address. Generic shapes (empty functions,
trivial destructors, ctor stubs) recur across game code and are therefore never claimed.

Exact identity only: a library function that changed between SDK versions is not claimed here.
Usage: python3 tools/analysis/libid.py
"""
import csv
import glob
import os
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(__file__))
from prx import Elf, relmask  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ARCHIVES = ['psp/lib/libc.a', 'psp/lib/libm.a', 'psp/lib/libstdc++.a', 'psp/lib/libsupc++.a',
            'lib/gcc-lib/psp/*/libgcc.a', 'psp/lib/crt0.o', 'lib/gcc-lib/psp/*/crt*.o']


def ar_members(blob):
    assert blob[:8] == b'!<arch>\n'
    o, names = 8, b''
    while o < len(blob):
        hdr = blob[o:o + 60]
        name = hdr[:16].decode().strip()
        size = int(hdr[48:58])
        body = blob[o + 60:o + 60 + size]
        if name == '//':
            names = body
        elif name not in ('/', '/SYM64/'):
            if name.startswith('/') and name[1:].isdigit():
                k = int(name[1:])
                name = names[k:names.index(b'/\n', k)].decode()
            yield name.rstrip('/'), body
        o += 60 + size + (size & 1)


def fingerprints(obj_bytes):
    """{masked-bytes: name} for each sized function symbol in every exec section of an object."""
    e = Elf(obj_bytes)
    out = {}
    syms = e.symbols()
    for i, s in enumerate(e.sh):
        if not (s[2] & 4) or s[1] != 1:  # SHF_EXECINSTR, PROGBITS
            continue
        data = e.data(i)
        rel = {o // 4: t for o, t, _ in e.object_rels(i)}
        words = [relmask(struct.unpack_from('<I', data, k)[0], rel.get(k // 4, 0)) for k in range(0, len(data) - 3, 4)]
        types = [rel.get(k, 0) for k in range(len(words))]
        for sym in syms:
            if sym['shndx'] == i and sym['type'] == 2 and sym['size'] >= 8:
                a, b = sym['value'] // 4, (sym['value'] + sym['size']) // 4
                out[(tuple(words[a:b]), tuple(types[a:b]))] = sym['name']
    return out


def library_index():
    idx = {}
    for ver in ('1.3.1', '1.7.1'):
        base = os.path.join(ROOT, 'build/toolchains', f'psp-gcc-{ver}')
        for pat in ARCHIVES:
            for path in glob.glob(os.path.join(base, pat)):
                lib = os.path.basename(path)
                blob = open(path, 'rb').read()
                members = ar_members(blob) if blob[:8] == b'!<arch>\n' else [(lib, blob)]
                for mname, body in members:
                    if body[:4] != b'\x7fELF':
                        continue
                    for key, fname in fingerprints(body).items():
                        idx.setdefault(key, (lib, mname, fname, ver))
    return idx


def main():
    idx = library_index()
    e = Elf(open(os.path.join(ROOT, 'orig/us/BOOT.BIN'), 'rb').read())
    rel = {r['at']: r['type'] for r in e.prx_rels()}
    funcs = [(int(r['addr'], 16), int(r['size'])) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))]
    seen = {}
    for a, z in funcs:
        words = tuple(relmask(e.word(p), rel.get(p, 0)) for p in range(a, a + z, 4))
        types = tuple(rel.get(p, 0) for p in range(a, a + z, 4))
        if (words, types) in idx:
            seen.setdefault((words, types), []).append((a, z))
    rows = sorted((v[0][0], v[0][1]) + idx[k] for k, v in seen.items() if len(v) == 1)
    dst = os.path.join(ROOT, 'config/us/libfuncs.csv')
    with open(dst, 'w') as f:
        f.write('addr,size,library,member,symbol,sdk\n')
        for a, z, lib, mem, fn, ver in rows:
            f.write(f'0x{a:06x},{z},{lib},{mem},{fn},{ver}\n')
    by = {}
    for a, z, lib, *_ in rows:
        n, b = by.get(lib, (0, 0))
        by[lib] = (n + 1, b + z)
    print(f'{len(idx)} library fingerprints; {len(rows)} retail functions identified ({sum(z for _, z, *_ in rows)} B) -> {dst}')
    for lib, (n, b) in sorted(by.items(), key=lambda kv: -kv[1][1]):
        print(f'  {lib:16s} {n:5d} fns {b:8d} B')


if __name__ == '__main__':
    main()
