#!/usr/bin/env python3
"""Reference library objects from the psp-gcc tarballs, as code blobs.

    from libarchive import load_blobs
    blobs = load_blobs()          # list[Blob], MD5-checked tarballs

Blob: one code section (SHF_EXECINSTR, non-empty) of one object member:
    tarball   'psp-gcc-1.3.1' | 'psp-gcc-1.7.1'
    lib       archive or object path inside the tarball (e.g. 'psp/lib/libc.a')
    member    archive member name ('' for a bare .o)
    section   section name ('.text', '.gnu.linkonce.t.X', '.init', '.fini')
    words     list of u32
    rtypes    {word index: relocation type} for relocations in that section
    syms      [(offset, size, name, bind)] for STT_FUNC / STT_NOTYPE symbols
              defined in the section (size 0 for symbols without size)

Fingerprinting (shared by funcmap.py and libfence.py):

    sigs = fingerprint(prx, blobs)   # {signature: (retail hit addresses, [Blob])}

A signature is the blob's words with relocated fields masked (R_MIPS_26: low
26 bits, HI16/LO16: low 16, R_MIPS_32: all 32) paired with the relocation
type at each word; a retail address hits when the retail words, masked by
the retail relocations, give the same signature.  .init/.fini pieces and
one-word blobs are not fingerprinted.

Libraries read: crt0.o, crti.o, crtn.o, crtbegin.o, crtend.o, libgcc.a,
libc.a, libm.a, libstdc++.a, libsupc++.a.  libg.a is skipped: it is a byte
copy of libc.a in both tarballs (checked by load_blobs()).
"""
import hashlib
import struct
import tarfile
import os
from collections import namedtuple
from pathlib import Path

REFS = Path(os.environ.get('RR_REFS', '/Users/jeffreywilbur/projects/strutb/ridgeracerpsp/references'))
TARBALLS = {
    'psp-gcc-1.3.1': '79792a94c8b37be3832fda5dcb30b601',
    'psp-gcc-1.7.1': '58c2e990bfee7e30f863a13e1b30b6aa',
}
WANT = ('crt0.o', 'crti.o', 'crtn.o', 'crtbegin.o', 'crtend.o', 'libgcc.a', 'libc.a',
        'libm.a', 'libstdc++.a', 'libsupc++.a')

Blob = namedtuple('Blob', 'tarball lib member section words rtypes syms')


def ar_members(b):
    if b[:8] != b'!<arch>\n':
        raise ValueError('not an ar archive')
    o, names = 8, None
    while o < len(b):
        h = b[o:o + 60]
        name = h[:16].decode().strip()
        size = int(h[48:58])
        data = b[o + 60:o + 60 + size]
        if name == '//':
            names = data
        elif name not in ('/', '/SYM64/'):
            if name.startswith('/') and names is not None:
                k = int(name[1:])
                name = names[k:names.index(b'\n', k)].decode()
            yield name.rstrip('/'), data
        o += 60 + size + (size & 1)


def object_blobs(d):
    """(section, words, rtypes, syms) for each code section of a REL ELF."""
    if d[:4] != b'\x7fELF' or struct.unpack_from('<H', d, 16)[0] != 1:
        raise ValueError('not a relocatable ELF')
    shoff, = struct.unpack_from('<I', d, 0x20)
    shes, shn, shstr = struct.unpack_from('<HHH', d, 0x2e)
    sh = [struct.unpack_from('<10I', d, shoff + i * shes) for i in range(shn)]
    so = sh[shstr][4]

    def nm(o, base=so):
        return d[base + o:d.index(b'\0', base + o)].decode()
    code = {i for i, s in enumerate(sh) if s[2] & 4 and s[5] and s[1] == 1}
    rt = {i: {} for i in code}
    syms = {i: [] for i in code}
    for s in sh:
        if s[1] == 9 and s[7] in code:          # SHT_REL for a code section
            for k in range(s[5] // 8):
                off, info = struct.unpack_from('<II', d, s[4] + k * 8)
                rt[s[7]][off // 4] = info & 0xff
        if s[1] == 2:                           # SHT_SYMTAB
            st = sh[s[6]][4]
            for k in range(s[5] // 16):
                n, v, sz, inf, _o, shx = struct.unpack_from('<IIIBBH', d, s[4] + k * 16)
                if shx in code and (inf & 0xf) in (0, 2) and n:
                    syms[shx].append((v, sz, nm(n, st), inf >> 4))
    out = []
    for i in sorted(code):
        s = sh[i]
        words = list(struct.unpack_from(f'<{s[5] // 4}I', d, s[4]))
        out.append((nm(s[0]), words, rt[i], sorted(syms[i])))
    return out


def load_blobs():
    blobs = []
    for tb, md5 in TARBALLS.items():
        path = REFS / f'{tb}.tar.gz'
        raw = path.read_bytes()
        got = hashlib.md5(raw).hexdigest()
        if got != md5:
            raise SystemExit(f'libarchive: {path}: MD5 {got}, expected {md5}')
        import io
        with tarfile.open(fileobj=io.BytesIO(raw), mode='r:gz') as tf:
            files = {m.name.lstrip('./'): m for m in tf.getmembers() if m.isfile()}
            libc = libg = None
            for name, m in sorted(files.items()):
                base = name.rsplit('/', 1)[-1]
                if base == 'libg.a':
                    libg = tf.extractfile(m).read()
                if base not in WANT:
                    continue
                data = tf.extractfile(m).read()
                if base == 'libc.a':
                    libc = data
                mems = list(ar_members(data)) if base.endswith('.a') else [('', data)]
                for mname, md in mems:
                    if md[:4] != b'\x7fELF':
                        continue
                    for sec, words, rtypes, syms in object_blobs(md):
                        blobs.append(Blob(tb, name, mname, sec, words, rtypes, syms))
            if libg is not None and libg != libc:
                raise SystemExit(f'libarchive: {tb}: libg.a differs from libc.a')
    return blobs


MASK = {2: 0, 4: 0xfc000000, 5: 0xffff0000, 6: 0xffff0000}


def masked(w, ty):
    return (w & MASK[ty] if ty else w, ty)


def blob_key(b, k):
    return masked(b.words[k], b.rtypes.get(k, 0))


def retail_words(p):
    R = {}
    for name in ('.init', '.text', '.fini'):
        s = p.section(name)
        for a in range(s.addr, s.end, 4):
            ty = 0
            for r in p.reloc_at(a):
                if r.type_id in MASK:
                    ty = r.type_id
            R[a] = masked(p.word(a), ty)
    return R


def fingerprint(p, blobs, R=None):
    from collections import defaultdict
    R = R or retail_words(p)
    idx = defaultdict(list)
    for a in R:
        if a + 4 in R:
            idx[(R[a], R[a + 4])].append(a)
    sigs = {}
    for b in blobs:
        if b.section in ('.init', '.fini') or len(b.words) < 2:
            continue
        sig = tuple(blob_key(b, k) for k in range(len(b.words)))
        if sig in sigs:
            sigs[sig][1].append(b)
            continue
        cand = idx.get((sig[0], sig[1]), [])
        hits = [a for a in cand if all(R.get(a + 4 * k) == sig[k] for k in range(len(sig)))]
        sigs[sig] = (hits, [b])
    return sigs
