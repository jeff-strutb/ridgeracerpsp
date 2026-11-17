#!/usr/bin/env python3
"""Temporary control-set scorer: compiled words vs retail words, relocated fields masked.

TEMPORARY. This exists only to pin the compiler and flags on the control set. It is replaced
by the real per-function grader, built on the full relocation reader. It does NOT check
relocation targets: a call or address load that points at the wrong symbol still scores EXACT
here. What it does check, per tagged function:

  * every instruction word, after masking the relocated field of each word on each side by
    that side's own relocations (retail: .rel.text of BOOT.BIN, type 0x700000a0 entries;
    object: its own SHT_REL section for the function's section). Masks: R_MIPS_32 whole word,
    R_MIPS_26 low 26 bits, R_MIPS_HI16 / LO16 / GPREL16 low 16 bits; any other type masks the
    whole word and is reported.
  * that both sides carry the same relocation type at the same word (or none on both).

The length compared is the compiled function's symbol size. A retail function longer than
the compiled one is not detected here (the real grader takes lengths from the function map).

Result per function: EXACT, or DIFFERS with the first differing word (offset, retail word,
compiled word), or MISSING (no such symbol in the object). Tag names are matched to object
symbols exactly, else by a unique prefix, else by a unique substring (reported when used).

Usage:
    ctlscore.py [--cc VER] [--no-defaults] FILE [FLAG ...]   score every tagged function in FILE
    ctlscore.py [--cc VER] --control src/control/CONTROL.md [-- FLAG ...]
    ctlscore.py ... --selftest     also flip one unrelocated instruction word in each EXACT
                                   function's compiled bytes and show that it then DIFFERS

Needs RRPSP_CC_HOST and RRPSP_CC_KEY (see cc.py). The retail executable is read from
$RRPSP_BOOT, else build/retail/BOOT.BIN, which is extracted from the USA ISO in the references
folder on first use and checked against its MD5.
"""
import argparse
import hashlib
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cc  # noqa: E402

BOOT_MD5 = 'e87ea7c17004cd13945664152608140c'
ISO_NAME = 'Ridge Racer (USA) (En,Fr,De,Es,It).iso'
TAG_RE = re.compile(r'/\*\s*@(implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+(\S+)')
MASKS = {2: 0xffffffff, 4: 0x03ffffff, 5: 0xffff, 6: 0xffff, 7: 0xffff}


# ---------------------------------------------------------------- ELF reading

def sections(d):
    shoff, = struct.unpack_from('<I', d, 0x20)
    shnum, shstrndx = struct.unpack_from('<HH', d, 0x30)
    sh = [struct.unpack_from('<10I', d, shoff + i * 40) for i in range(shnum)]
    stroff = sh[shstrndx][4]
    out = []
    for s in sh:
        name = d[stroff + s[0]:d.index(b'\0', stroff + s[0])].decode()
        out.append(dict(name=name, type=s[1], addr=s[3], off=s[4], size=s[5], link=s[6],
                        info=s[7], entsize=s[9]))
    return out


class Retail:
    def __init__(self, path):
        d = open(path, 'rb').read()
        if hashlib.md5(d).hexdigest() != BOOT_MD5:
            raise SystemExit('%s: MD5 is not the USA BOOT.BIN (%s)' % (path, BOOT_MD5))
        etype, = struct.unpack_from('<H', d, 0x10)
        assert etype == 0xFFA0, 'not a PSP relocatable module'
        phoff, = struct.unpack_from('<I', d, 0x1c)
        phnum, = struct.unpack_from('<H', d, 0x2c)
        self.segs = [struct.unpack_from('<8I', d, phoff + i * 32) for i in range(phnum)]
        secs = sections(d)
        self.text = next(s for s in secs if s['name'] == '.text')
        self.d = d
        self.rel = {}
        for s in secs:
            if s['type'] == 0x700000a0 and secs[s['info']]['name'] == '.text':
                for i in range(0, s['size'], 8):
                    off, info = struct.unpack_from('<II', d, s['off'] + i)
                    seg = (info >> 8) & 0xff
                    vaddr = self.segs[seg][2] + off
                    self.rel[vaddr] = info & 0xff

    def word(self, vaddr):
        t = self.text
        if not (t['addr'] <= vaddr < t['addr'] + t['size']):
            return None
        return struct.unpack_from('<I', self.d, t['off'] + vaddr - t['addr'])[0]


class Obj:
    def __init__(self, path):
        d = open(path, 'rb').read()
        self.d = d
        self.secs = sections(d)
        symtab = next(s for s in self.secs if s['type'] == 2)
        strtab = self.secs[symtab['link']]
        self.funcs = {}
        for i in range(0, symtab['size'], 16):
            nm, val, size, info, other, shndx = struct.unpack_from('<IIIBBH', d, symtab['off'] + i)
            if info & 0xf == 2 and 0 < shndx < len(self.secs):
                name = d[strtab['off'] + nm:d.index(b'\0', strtab['off'] + nm)].decode()
                self.funcs[name] = (shndx, val, size)
        self.rels = {}
        for s in self.secs:
            if s['type'] == 9:
                r = self.rels.setdefault(s['info'], {})
                for i in range(0, s['size'], 8):
                    off, info = struct.unpack_from('<II', d, s['off'] + i)
                    r[off] = info & 0xff

    def resolve(self, name):
        """Tag names are not always the exact symbol (some are unmangled or truncated, and
        _GLOBAL__I_ lacks its suffix). Exact match, else the unique symbol starting with the
        name, else the unique symbol containing it. Returns (symbol, how) or (None, why)."""
        if name in self.funcs:
            return name, 'exact'
        for how, pred in (('prefix', lambda s: s.startswith(name)), ('substring', lambda s: name in s)):
            c = [s for s in self.funcs if pred(s)]
            if len(c) == 1:
                return c[0], how
            if len(c) > 1:
                return None, 'ambiguous %s match: %s' % (how, ', '.join(sorted(c)))
        return None, 'no function symbol matches'

    def func(self, sym):
        shndx, val, size = self.funcs[sym]
        s = self.secs[shndx]
        words = [struct.unpack_from('<I', self.d, s['off'] + val + i)[0] for i in range(0, size, 4)]
        rel = self.rels.get(shndx, {})
        types = [rel.get(val + i) for i in range(0, size, 4)]
        return words, types


# ---------------------------------------------------------------- scoring

def masked(w, t):
    return w if t is None else w & ~MASKS.get(t, 0xffffffff) & 0xffffffff


def compare(retail, addr, words, types):
    """None if EXACT, else (index, why, retail word, compiled word)."""
    for i, (w, t) in enumerate(zip(words, types)):
        va = addr + 4 * i
        rw = retail.word(va)
        if rw is None:
            return (i, 'outside retail .text', 0, w)
        rt = retail.rel.get(va)
        if rt != t:
            return (i, 'relocation type retail %s, compiled %s' % (rt, t), rw, w)
        if t is not None and t not in MASKS:
            return (i, 'unknown relocation type %d' % t, rw, w)
        if masked(rw, rt) != masked(w, t):
            return (i, 'word', rw, w)
    return None


def plant(words, types):
    """Copy of words with one unrelocated instruction changed (its rt field, bits 16-20, is
    xored with 1), or None if every word is relocated."""
    for i, t in enumerate(types):
        if t is None and words[i] != 0:
            w = list(words)
            w[i] ^= 1 << 16
            return i, w
    return None


def tags_in(path):
    text = open(path, encoding='latin-1').read()
    return [(k, int(a, 16), n) for k, a, n in TAG_RE.findall(text)]


def control_list(md):
    """Rows of the control table: | n | file | 0xADDR | name | ... """
    out = []
    for line in open(md):
        m = re.match(r'\|\s*\d+\s*\|\s*`?([^|`]+?)`?\s*\|\s*`?0x([0-9a-fA-F]+)`?\s*\|\s*`?([^|`]+?)`?\s*\|', line)
        if m:
            out.append((m.group(1), int(m.group(2), 16), m.group(3)))
    return out


def boot_path():
    p = os.environ.get('RRPSP_BOOT') or os.path.join(cc.BUILD, 'retail', 'BOOT.BIN')
    if not os.path.exists(p):
        iso = os.path.join(cc.references_dir(), ISO_NAME)
        tmp = os.path.join(cc.BUILD, 'retail', 'x')
        os.makedirs(tmp, exist_ok=True)
        subprocess.run(['bsdtar', '-xf', iso, '-C', tmp, 'PSP_GAME/SYSDIR/BOOT.BIN'], check=True)
        os.replace(os.path.join(tmp, 'PSP_GAME', 'SYSDIR', 'BOOT.BIN'), p)
    return p


def score(retail, src, wanted, ver, flags, use_defaults, selftest, out):
    """wanted: list of (addr, name). Returns list of (addr, name, status, detail)."""
    try:
        r = cc.compile_file(src, ver, flags, use_defaults)
    except RuntimeError as e:
        return [(a, n, 'NOCOMPILE', str(e).strip().splitlines()[-1] if str(e).strip() else '')
                for a, n in wanted], None
    obj = Obj(r['o'])
    res = []
    for addr, name in wanted:
        sym, how = obj.resolve(name)
        if sym is None:
            res.append((addr, name, 'MISSING', how))
            continue
        words, types = obj.func(sym)
        via = '' if how == 'exact' else ' (symbol %s, %s match)' % (sym, how)
        ncm = sum(1 for w in words if w >> 26 == 0 and w & 0x3f in (0x0a, 0x0b))
        if ncm:
            via += ' [compiled movz/movn: %d]' % ncm
        c = compare(retail, addr, words, types)
        if c is None:
            st, det = 'EXACT', '%d words%s' % (len(words), via)
            if selftest:
                p = plant(words, types)
                if p is None:
                    det += '; selftest: no unrelocated word to plant'
                else:
                    i, w2 = p
                    c2 = compare(retail, addr, w2, types)
                    det += '; selftest: word %d %08x->%08x gives %s' % (
                        i, words[i], w2[i], 'EXACT (CHECK FAILED)' if c2 is None else
                        'DIFFERS at word %d' % c2[0])
                    if c2 is None:
                        st = 'SELFTEST-FAILED'
        else:
            i, why, rw, cw = c
            st = 'DIFFERS'
            det = 'word %d of %d (0x%06x): %s; retail %08x, compiled %08x%s' % (
                i, len(words), addr + 4 * i, why, rw, cw, via)
        res.append((addr, name, st, det))
    return res, r


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--cc', choices=sorted(cc.COMPILERS), default=None)
    ap.add_argument('--no-defaults', action='store_true')
    ap.add_argument('--control', help='score the functions listed in this CONTROL.md')
    ap.add_argument('--implements-only', action='store_true')
    ap.add_argument('--selftest', action='store_true')
    ap.add_argument('--quiet', action='store_true', help='summary only')
    ap.add_argument('src', nargs='?')
    ap.add_argument('flags', nargs=argparse.REMAINDER)
    a = ap.parse_args()
    retail = Retail(boot_path())
    jobs = []  # (src, [(addr, name)])
    if a.control:
        groups = {}
        for f, addr, name in control_list(a.control):
            groups.setdefault(f, []).append((addr, name))
        jobs = [(os.path.join(cc.REPO, f), w) for f, w in groups.items()]
        flags = ([a.src] if a.src else []) + a.flags
    else:
        if not a.src:
            ap.error('give a source file or --control')
        tags = tags_in(a.src)
        if a.implements_only:
            tags = [t for t in tags if t[0] == 'implements']
        jobs = [(a.src, [(addr, n) for _, addr, n in tags])]
        flags = a.flags
    total = {}
    n = 0
    for src, wanted in jobs:
        res, r = score(retail, src, wanted, a.cc, flags, not a.no_defaults, a.selftest, sys.stdout)
        rel = os.path.relpath(os.path.abspath(src), cc.REPO)
        for addr, name, st, det in res:
            n += 1
            total[st] = total.get(st, 0) + 1
            if not a.quiet:
                print('%-8s 0x%06x %-40s %s  [%s]' % (st, addr, name, det, rel))
    ver = a.cc or cc.DEFAULT_CC
    fl = (list(cc.DEFAULT_FLAGS) if not a.no_defaults else []) + flags
    print('== %s %s: %d/%d EXACT  (%s)' % (ver, ' '.join(fl) or '(no flags)', total.get('EXACT', 0),
                                          n, ', '.join('%s %d' % kv for kv in sorted(total.items()))))
    sys.exit(0 if total.get('SELFTEST-FAILED', 0) == 0 else 1)


if __name__ == '__main__':
    main()
