#!/usr/bin/env python3
"""T4 grader: compile source files with the pinned compiler and grade every tagged function.

    tools/score.py FILE... [--json] [--quiet] [--no-cache]
    tools/score.py --control            the functions listed in src/control/CONTROL.md
    tools/score.py --tree               every source file under src/

Each tag (`@implements 0xADDR us NAME` or `@draft ...`, the first word of a line inside a
comment) gets one verdict:

  EXACT    all of the checks below pass.
  DIFFERS  the compiled size differs from funcs.csv, or a word differs after masking the
           relocated fields, or the relocation types at some word differ.
  BADREF   size, words and relocation types all equal, but at least one relocation resolves to
           something other than retail's target, or cannot be proved to resolve to it.
  MISSING  nothing to compare: the file does not compile, the tag's name matches no function
           symbol (or matches one another tag already claims), or ADDR is not a function start.

WHAT IS COMPARED, per function (retail = the USA BOOT.BIN through refcheck/prx.py):

  1. Size: the compiled function symbol's st_size equals the size in config/us/funcs.csv.
  2. Every word of the function, with the relocated field masked on each side by that side's
     own relocation (R_MIPS_32 whole word, R_MIPS_26 low 26 bits, HI16/LO16 low 16 bits).
  3. The relocation type at every word: the same type on both sides, or none on both.
  4. Every relocation's target.  Retail's target comes from prx.py (j26, word, HI16/LO16 pair)
     or, for a LO16 whose high half no relocation records, from hilo.py's data flow.  A LO16
     that hilo.py cannot recover is unprovable.  The compiled target is the relocation's
     symbol plus its REL addend (see Obj), resolved as follows:
       - local code (a section or local symbol in an executable section): the function symbol
         of this object that contains the offset, which must be tagged in this file; its
         address plus the offset into it.
       - a symbol that names an address: the address of the tag that resolves to it (a tag in
         this file, else in any real file); else a plain C name f_XXXXXX or D_XXXXXX, a C++
         free function _Z<n>f_XXXXXX..., or a C++ variable whose innermost name is D_XXXXXX;
         else a library symbol in config/us/libfuncs.csv (one address); else an import whose
         SHA-1 NID (first four bytes, little-endian) is the NID of exactly one retail stub.
         A C++ method named f_XXXXXX is not taken as naming its own address (an override is
         often named after the base slot it fills), so a method must be tagged.
       - object data (a local symbol or section symbol in a data section, or a global data
         symbol defined in this object or in another real file's object that names no
         address): the item holding the target must have byte-identical contents at retail's
         target.  The item is the defined data symbol that covers the offset (st_size); in a
         mergeable section, the constant entry (entsize) or the string through its NUL;
         otherwise the bytes up to the next place anything in the object refers to.  Relocated
         words inside the item must carry the same relocation type at the same offset in
         retail (and retail none elsewhere in the range), and their targets are resolved and
         compared by these same rules, recursively.  So a jump table's entries must point at
         the corresponding instructions, and a vtable's slots at the same functions.  .bss
         items (no contents) must land in retail .bss.  Each object item maps to one retail
         address in a run; two different addresses is BADREF.
     A target that none of these rules resolves is unprovable, and the function is BADREF.

WHAT IS NOT COMPARED: .eh_frame and .gcc_except_table (unwind and exception tables; retail's
are not matched against the compiled ones), .pdr, .mdebug, .reginfo, .comment, .ctors/.dtors
entries, the contents of data a function does not refer to, the contents of data that a
symbol names by address (D_XXXXXX: the address is checked, not the bytes), the contents of
data defined only in a file that is not a real translation unit, and the bytes of the PRX's
own relocation table.  The compile cache in build/cc-cache is trusted (cc.py keys it by
compiler, flags, source and header bytes); --no-cache recompiles everything.

Real translation units are the files under src/ outside src/control/.  src/control/batch*.c
duplicate addresses of real files and are graded only when named.

Needs RRPSP_CC_HOST and RRPSP_CC_KEY (tools/toolchains/cc.py) and ./setup.sh's orig/.
"""
import argparse
import csv
import hashlib
import json
import os
import re
import struct
import sys
import time
from collections import namedtuple
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools' / 'analysis'),
                str(ROOT / 'tools' / 'toolchains')]
import cc                      # noqa: E402

SRC = ROOT / 'src'
SOURCE_SUFFIXES = ('.c', '.cc', '.cpp', '.cxx')

# ------------------------------------------------------------------ tags

TAG_LINE = re.compile(r'^[ \t]*(?:/\*+)?[ \t]*\**[ \t]*@(implements|draft)\b(.*)$')
TAG_FORM = re.compile(r'[ \t]+0x([0-9a-fA-F]+)[ \t]+(\w+)[ \t]+(\S+?)(?=\s|\*/|$)')
TAG_ANY = re.compile(r'@(implements|draft)\b')
WHAT = re.compile(r'WHAT IT DOES:\s*[^\s*/]')

Tag = namedtuple('Tag', 'kind addr region name path line what')


def comments(text):
    """(start, end) of every /* */ and // comment, skipping string and char literals."""
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            out.append((i, j))
            i = j
        elif c == '/' and text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            out.append((i, j))
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c and text[j] != '\n':
                j += 2 if text[j] == '\\' else 1
            i = j + 1
        else:
            i += 1
    return out


def relpath(path):
    p = Path(path).resolve()
    try:
        return str(p.relative_to(ROOT))
    except ValueError:
        return str(p)


def parse_tags(path, text=None):
    """(tags, problems) for one source file.  A tag is '@implements' or '@draft' as the first
    word of a line inside a comment, followed by 0xADDR REGION NAME.  Its WHAT IT DOES
    paragraph is the text after it up to the next tag or the end of the comment.  Any other
    occurrence of the tag words is a problem."""
    if text is None:
        text = Path(path).read_text(encoding='latin-1')
    rel = relpath(path)
    tags, problems, inside = [], [], set()
    for s, e in comments(text):
        found, pos = [], s
        for line in text[s:e].split('\n'):
            m = TAG_LINE.match(line)
            if m:
                found.append((pos + m.start(1) - 1, m))
            pos += len(line) + 1
        for k, (off, m) in enumerate(found):
            inside.add(off)
            lineno = text.count('\n', 0, off) + 1
            f = TAG_FORM.match(m.group(2))
            if not f:
                problems.append((rel, lineno, 'malformed tag: ' + m.group(0).strip()))
                continue
            nxt = found[k + 1][0] if k + 1 < len(found) else e
            tags.append(Tag(m.group(1), int(f.group(1), 16), f.group(2), f.group(3), rel,
                            lineno, bool(WHAT.search(text[off:nxt]))))
    for m in TAG_ANY.finditer(text):
        if m.start() not in inside:
            problems.append((rel, text.count('\n', 0, m.start()) + 1,
                             'tag word not at the start of a comment line'))
    return tags, problems


def is_real(path, src=SRC):
    """A real translation unit: a source file under src (default <repo>/src) but not under
    its control/ folder."""
    try:
        rel = Path(path).resolve().relative_to(Path(src).resolve())
    except ValueError:
        return False
    return len(rel.parts) > 1 and rel.parts[0] != 'control' and rel.suffix in SOURCE_SUFFIXES


def source_files(root=SRC):
    return sorted(p for p in Path(root).rglob('*') if p.is_file() and p.suffix in SOURCE_SUFFIXES)


# ------------------------------------------------------------------ ELF relocatable objects

SHT_SYMTAB, SHT_RELA, SHT_NOBITS, SHT_REL = 2, 4, 8, 9
SHF_ALLOC, SHF_EXEC, SHF_MERGE, SHF_STRINGS = 0x2, 0x4, 0x10, 0x20
STT_NOTYPE, STT_OBJECT, STT_FUNC, STT_SECTION = 0, 1, 2, 3
STB_LOCAL = 0
SHN_UNDEF, SHN_COMMON = 0, 0xfff2
R_NAMES = {2: 'R_MIPS_32', 4: 'R_MIPS_26', 5: 'R_MIPS_HI16', 6: 'R_MIPS_LO16'}
FIELD = {2: 0xffffffff, 4: 0x03ffffff, 5: 0xffff, 6: 0xffff}

Sec = namedtuple('Sec', 'index name type flags off size link info align entsize')
Sym = namedtuple('Sym', 'index name value size bind type shndx')


def sext16(v):
    v &= 0xffff
    return v - 0x10000 if v & 0x8000 else v


def rname(t):
    return R_NAMES.get(t, 'R_MIPS_%s' % t) if t is not None else 'none'


class Rel:
    __slots__ = ('sec', 'off', 'sym', 'type', 'addend', 'paired')

    def __init__(self, sec, off, sym, typ):
        self.sec, self.off, self.sym, self.type = sec, off, sym, typ
        self.addend, self.paired = None, False


class Obj:
    """An ELF32 little-endian MIPS relocatable object as GNU as 2.14 writes it (REL only).

    REL addends, computed as GNU ld computes them for MIPS:
      R_MIPS_32    the stored word (signed)
      R_MIPS_26    the stored 26-bit field shifted left by 2
      R_MIPS_HI16  (hi << 16) + sext(lo), lo the field of the next R_MIPS_LO16 against the same
                   symbol in the same relocation section (ld's mips_elf_next_relocation)
      R_MIPS_LO16  the addend of the HI16 that took it as partner (paired); otherwise
                   sext(field), which fixes only the low 16 bits (paired False)."""

    def __init__(self, data):
        d = self.data = bytes(data)
        if d[:4] != b'\x7fELF' or d[4] != 1 or d[5] != 1:
            raise ValueError('not an ELF32 little-endian file')
        if struct.unpack_from('<H', d, 16)[0] != 1:
            raise ValueError('not a relocatable object')
        shoff, = struct.unpack_from('<I', d, 0x20)
        shes, shn, shstr = struct.unpack_from('<HHH', d, 0x2e)
        raw = [struct.unpack_from('<10I', d, shoff + i * shes) for i in range(shn)]
        so = raw[shstr][4]

        def cstr(o):
            return d[o:d.index(b'\0', o)].decode('latin-1')
        self.secs = [Sec(i, cstr(so + r[0]), r[1], r[2], r[4], r[5], r[6], r[7], r[8], r[9])
                     for i, r in enumerate(raw)]
        st = [s for s in self.secs if s.type == SHT_SYMTAB]
        if len(st) != 1:
            raise ValueError('expected one symbol table, found %d' % len(st))
        st = st[0]
        stro = self.secs[st.link].off
        self.syms = []
        for i in range(st.size // 16):
            nm, val, size, info, _o, shndx = struct.unpack_from('<IIIBBH', d, st.off + i * 16)
            name = '' if (info & 0xf) == STT_SECTION else cstr(stro + nm)
            self.syms.append(Sym(i, name, val, size, info >> 4, info & 0xf, shndx))
        self.rels = {}
        for s in self.secs:
            if s.type == SHT_RELA:
                raise ValueError('RELA section %s: GNU as writes REL for MIPS' % s.name)
            if s.type == SHT_REL:
                rl = []
                for k in range(s.size // 8):
                    off, info = struct.unpack_from('<II', d, s.off + k * 8)
                    rl.append(Rel(s.info, off, self.syms[info >> 8], info & 0xff))
                self._addends(rl)
                self.rels.setdefault(s.info, []).extend(rl)
        self.relat = {}
        for rl in self.rels.values():
            for r in rl:
                self.relat.setdefault((r.sec, r.off), []).append(r)
        self._bounds = {}

    def defined(self, sym):
        return 0 < sym.shndx < len(self.secs)

    def is_code(self, shndx):
        return bool(self.secs[shndx].flags & SHF_EXEC)

    def word(self, sec, off):
        return struct.unpack_from('<I', self.data, self.secs[sec].off + off)[0]

    def bytes_of(self, sec, off, n):
        s = self.secs[sec]
        if s.type == SHT_NOBITS:
            return bytes(n)
        return self.data[s.off + off:s.off + off + n]

    def _addends(self, rl):
        for r in rl:
            w = self.word(r.sec, r.off)
            if r.type == 2:
                r.addend = w - (1 << 32) if w & 0x80000000 else w
            elif r.type == 4:
                r.addend = (w & 0x3ffffff) << 2
            elif r.type == 6:
                r.addend = sext16(w)
        for k, r in enumerate(rl):
            if r.type != 5:
                continue
            lo = next((x for x in rl[k + 1:] if x.type == 6 and x.sym is r.sym), None)
            if lo is None:
                continue
            ahl = ((self.word(r.sec, r.off) & 0xffff) << 16) + sext16(self.word(lo.sec, lo.off))
            r.addend, r.paired = ahl, True
            lo.addend, lo.paired = ahl, True

    def functions(self):
        return [s for s in self.syms if s.type == STT_FUNC and self.defined(s)]

    def bounds(self, sec):
        """Sorted offsets in data section sec where an item may start: 0, the section end,
        every defined symbol, and every offset any relocation of this object targets (a
        LO16 without a partner is left out: only its low half is known)."""
        if sec not in self._bounds:
            b = {0, self.secs[sec].size}
            for s in self.syms:
                if s.shndx == sec:
                    b.add(s.value)
            for rl in self.rels.values():
                for r in rl:
                    if r.sym.shndx == sec and not (r.type == 6 and not r.paired):
                        b.add(r.sym.value + r.addend)
            self._bounds[sec] = sorted(x for x in b if 0 <= x <= self.secs[sec].size)
        return self._bounds[sec]

    def item(self, sec, off):
        """(start, end) of the data item holding offset off of section sec."""
        s = self.secs[sec]
        for y in self.syms:
            if (y.shndx == sec and y.type in (STT_OBJECT, STT_NOTYPE) and y.size
                    and y.value <= off < y.value + y.size):
                return y.value, y.value + y.size
        if s.flags & SHF_MERGE and s.entsize:
            if s.flags & SHF_STRINGS:
                d = self.bytes_of(sec, 0, s.size)
                st = off
                while st > 0 and d[st - 1] != 0:
                    st -= 1
                e = d.index(b'\0', off) + 1 if b'\0' in d[off:] else s.size
                return st, e
            st = off - off % s.entsize
            return st, st + s.entsize
        b = self.bounds(sec)
        import bisect
        k = bisect.bisect_right(b, off) - 1
        if k < 0 or k + 1 >= len(b):
            return None
        return b[k], b[k + 1]


def resolve_symbol(obj, name):
    """Tag names are not always the exact symbol (some are unmangled or truncated, and
    _GLOBAL__I_ lacks its suffix).  Exact match, else the unique function symbol starting
    with the name, else the unique one containing it.  _GLOBAL__I_/_GLOBAL__D_ symbols embed
    another function's name, so they are candidates only when the tag names one.
    Returns (Sym, how) or (None, why)."""
    funcs = obj.functions()
    ex = [s for s in funcs if s.name == name]
    if len(ex) == 1:
        return ex[0], 'exact'
    if len(ex) > 1:
        return None, 'several function symbols named %s' % name
    pool = [s for s in funcs if name.startswith('_GLOBAL__') or not s.name.startswith('_GLOBAL__')]
    for how, pred in (('prefix', lambda s: s.name.startswith(name)),
                      ('substring', lambda s: name in s.name)):
        c = [s for s in pool if pred(s)]
        if len(c) == 1:
            return c[0], how
        if len(c) > 1:
            return None, 'ambiguous %s match: %s' % (how, ', '.join(sorted(s.name for s in c)))
    return None, 'no function symbol matches'


# ------------------------------------------------------------------ names that give an address

PLAIN = re.compile(r'^([fD])_([0-9a-f]{6})$')


def _ids(s, i):
    """Parse <len><id> components from s[i:]; return (list of ids, index after)."""
    ids = []
    while i < len(s) and s[i].isdigit():
        j = i
        while j < len(s) and s[j].isdigit():
            j += 1
        n = int(s[i:j])
        ids.append(s[j:j + n])
        i = j + n
    return ids, i


def name_address(name):
    """Address a symbol's own name gives, or None: plain C f_XXXXXX / D_XXXXXX; a C++ free
    function _Z<n>f_XXXXXX<params>; a C++ variable (nothing follows the name in the mangling)
    whose innermost name is D_XXXXXX.  A C++ method's name is not used: 205 of the 488 tagged
    methods named f_XXXXXX are tagged at another address (overrides are named after the slot
    they fill), so a method needs a tag."""
    m = PLAIN.match(name)
    if m:
        return int(m.group(2), 16)
    if name.startswith('_ZN'):
        i = 3
        while i < len(name) and name[i] in 'rVK':
            i += 1
        ids, j = _ids(name, i)
        if ids and name[j:] == 'E':
            m = PLAIN.match(ids[-1])
            if m and m.group(1) == 'D':
                return int(m.group(2), 16)
        return None
    if name.startswith('_Z'):
        ids, j = _ids(name, 2)
        if len(ids) == 1:
            m = PLAIN.match(ids[0])
            if m and (m.group(1) == 'f') == (j < len(name)):
                return int(m.group(2), 16)
    return None


def load_libsyms():
    out = {}
    with open(ROOT / 'config' / 'us' / 'libfuncs.csv') as fh:
        for row in csv.DictReader(fh):
            for s in filter(None, row['symbol'].split(';')):
                out.setdefault(s, set()).add(int(row['addr'], 16))
    return out


# ------------------------------------------------------------------ retail

class Retail:
    """The USA BOOT.BIN with its relocation targets.  LO16 targets that prx.py leaves open
    come from hilo.recover(), cached in build/retail-facts/ under a hash of every input the
    recovery reads (the tools' sources, funcs.csv, the opcode table and the MD5-checked
    binary), so a change to any of them recomputes it."""

    def __init__(self):
        from prx import Prx
        import funcmap
        self.p = Prx.from_ref('us')
        self.funcs = {f['addr']: f for f in funcmap.load()}
        self.lo16 = self._lo16(funcmap)
        self.stub_nid = self._stubs()

    def _lo16(self, funcmap):
        h = hashlib.sha256(hashlib.md5(self.p.data).digest())
        for f in ('tools/analysis/prx.py', 'tools/analysis/hilo.py', 'tools/analysis/funcmap.py',
                  'tools/analysis/allegrex.py', 'tools/analysis/ehframe.py',
                  'config/us/funcs.csv', 'build/allegrex_ops.json'):
            h.update(f.encode() + b'\0' + (ROOT / f).read_bytes())
        path = ROOT / 'build' / 'retail-facts' / ('lo16-%s.json' % h.hexdigest()[:24])
        if path.is_file():
            return {int(k): v for k, v in json.loads(path.read_text()).items()}
        import hilo
        rec = hilo.recover(self.p, funcmap.load())
        out = {a: t for a, (t, _) in rec.items()}
        path.parent.mkdir(parents=True, exist_ok=True)
        tmp = path.with_suffix('.tmp%d' % os.getpid())
        tmp.write_text(json.dumps({str(k): v for k, v in out.items()}))
        os.replace(tmp, path)
        return out

    def _stubs(self):
        p = self.p
        s = p.section('.lib.stub')
        out = {}
        for a in range(s.addr, s.end, 20):
            _name, _v, attr, nids, stubs = (p.word(a + 4 * k) for k in range(5))
            for k in range(attr >> 16):
                out.setdefault(p.word(nids + 4 * k), []).append(stubs + 8 * k)
        return out

    def reloc(self, addr):
        rs = self.p.reloc_at(addr)
        return rs[0] if len(rs) == 1 else (None if not rs else rs)

    def target(self, r):
        if r.target is not None:
            return r.target
        return self.lo16.get(r.addr)

    def segbase(self, target):
        for g in self.p.segments:
            if g.vaddr <= target < g.vaddr + g.memsz:
                return g.vaddr
        return None


def nid_of(name):
    return struct.unpack('<I', hashlib.sha1(name.encode()).digest()[:4])[0]


# ------------------------------------------------------------------ compiled files

class Unit:
    """One compiled source file: its object, its tags and which symbol each tag claims."""

    def __init__(self, path, res, text, src=SRC):
        self.path = Path(path)
        self.rel = relpath(path)
        self.real = is_real(path, src)
        self.res = res
        self.tags, self.problems = parse_tags(path, text)
        self.obj = None
        self.error = None
        self.claim = {}         # tag -> (Sym or None, how)
        self.sym_addr = {}      # sym index -> tag address
        if isinstance(res, str):
            self.error = res
            return
        self.obj = Obj(Path(res['o']).read_bytes())
        taken = {}
        for t in self.tags:
            s, how = resolve_symbol(self.obj, t.name)
            self.claim[t] = (s, how)
            if s is not None:
                taken.setdefault(s.index, []).append(t)
        for idx, ts in taken.items():
            if len({t.addr for t in ts}) > 1:
                for t in ts:
                    self.claim[t] = (None, 'symbol %s is claimed by tags at %s' % (
                        self.obj.syms[idx].name, ', '.join('%#08x' % x.addr for x in ts)))
            else:
                self.sym_addr[idx] = ts[0].addr


class Tree:
    """Compiles files through cc.py (pinned compiler, content cache) and keeps the cross-file
    facts the resolver needs: tagged function symbols of every real file, and global data
    symbols defined by real files."""

    def __init__(self, src=SRC, ver=None, use_cache=True, jobs=8):
        self.src = Path(src)
        self.ver = ver or cc.DEFAULT_CC
        self.use_cache = use_cache
        self.jobs = jobs
        self.units = {}
        self._index = None
        self.times = {'compile': 0.0, 'cached': 0, 'compiled': 0}

    def unit(self, path):
        path = Path(path).resolve()
        if path not in self.units:
            self.compile_many([path])
        return self.units[path]

    def compile_many(self, paths):
        todo = [Path(p).resolve() for p in paths if Path(p).resolve() not in self.units]
        if not todo:
            return
        t0 = time.time()

        def job(p):
            t = time.time()
            try:
                r = cc.compile_file(str(p), self.ver, use_cache=self.use_cache)
            except RuntimeError as e:
                return p, str(e).strip() or 'compile failed'
            # The object must be the one this call wrote: cc.py deletes the old output first,
            # so an older file here means a stale object.
            if os.path.getmtime(r['o']) < t - 1:
                return p, 'object %s is older than this compile (stale)' % r['o']
            return p, r
        with ThreadPoolExecutor(self.jobs) as ex:
            for p, r in ex.map(job, todo):
                self.units[p] = Unit(p, r, p.read_text(encoding='latin-1'), self.src)
                if isinstance(r, dict):
                    self.times['cached' if r['cached'] else 'compiled'] += 1
        self.times['compile'] += time.time() - t0

    def index(self):
        if self._index is None:
            files = [p for p in source_files(self.src) if is_real(p, self.src)]
            self.compile_many(files)
            funcs, data = {}, {}
            for p in files:
                u = self.units[p.resolve()]
                if u.obj is None:
                    continue
                for idx, a in u.sym_addr.items():
                    funcs.setdefault(u.obj.syms[idx].name, set()).add(a)
                for s in u.obj.syms:
                    if (s.bind != STB_LOCAL and u.obj.defined(s) and not u.obj.is_code(s.shndx)
                            and s.type in (STT_OBJECT, STT_NOTYPE)
                            and u.obj.secs[s.shndx].flags & SHF_ALLOC):
                        data.setdefault(s.name, []).append((u, s))
            self._index = (funcs, data)
        return self._index


# ------------------------------------------------------------------ grading

Target = namedtuple('Target', 'kind addr unit sec off how')   # kind: addr | data | none


class Grader:
    def __init__(self, tree=None, retail=None):
        self.tree = tree or Tree()
        self.retail = retail or Retail()
        self.libsyms = load_libsyms()
        import libsyms
        self.libsyms2 = libsyms.load()
        self.use_libsyms = True
        self.items = {}            # (unit rel, sec, start) -> (retail base, reason or None)
        self.conflicts = set()     # item keys two references placed at different addresses
        self.used, self.used_items = set(), set()
        self.collect, self.pending = None, []

    # -- compiled target of one relocation
    def resolve(self, u, sym, addend):
        obj = u.obj
        if sym.type == STT_SECTION or (sym.bind == STB_LOCAL and obj.defined(sym)):
            off = sym.value + addend
            if obj.is_code(sym.shndx):
                for f in obj.functions():
                    if f.shndx == sym.shndx and f.value <= off < f.value + f.size:
                        if f.index in u.sym_addr:
                            return Target('addr', u.sym_addr[f.index] + off - f.value, None,
                                          None, None, 'local code in %s' % f.name)
                        return Target('none', None, None, None, None,
                                      'local code target %s+%#x is in untagged %s' % (
                                          obj.secs[sym.shndx].name, off, f.name))
                return Target('none', None, None, None, None, 'local code target %s+%#x is in '
                              'no function' % (obj.secs[sym.shndx].name, off))
            return Target('data', None, u, sym.shndx, off, 'object data %s+%#x' % (
                obj.secs[sym.shndx].name, off))
        name = sym.name
        cands = []
        if sym.index in u.sym_addr:
            cands.append((u.sym_addr[sym.index], 'tag in this file'))
        else:
            funcs, data = self.tree.index()
            if name in funcs:
                if len(funcs[name]) > 1:
                    return Target('none', None, None, None, None, '%s is tagged at %s' % (
                        name, ', '.join('%#08x' % a for a in sorted(funcs[name]))))
                cands.append((next(iter(funcs[name])), 'tag'))
        na = name_address(name)
        if na is not None:
            if cands and cands[0][0] != na and PLAIN.match(name):
                return Target('none', None, None, None, None, '%s is tagged at %#08x' % (
                    name, cands[0][0]))
            if not cands:
                cands.append((na, 'name'))
        if not cands and name in self.libsyms and len(self.libsyms[name]) == 1:
            cands.append((next(iter(self.libsyms[name])), 'library symbol'))
        if (not cands and self.use_libsyms and sym.shndx == SHN_UNDEF
                and name in self.libsyms2):
            cands.append((self.libsyms2[name], 'libsyms'))
        if not cands and sym.shndx == SHN_UNDEF:
            stubs = self.retail.stub_nid.get(nid_of(name), [])
            if len(stubs) == 1:
                cands.append((stubs[0], 'import NID %08x' % nid_of(name)))
        if cands:
            return Target('addr', cands[0][0] + addend, None, None, None, '%s (%s)' % (
                name, cands[0][1]))
        if obj.defined(sym) and not obj.is_code(sym.shndx):
            return Target('data', None, u, sym.shndx, sym.value + addend, 'data %s' % name)
        if sym.shndx == SHN_UNDEF:
            _, data = self.tree.index()
            if name in data:
                du, ds = data[name][0]
                return Target('data', None, du, ds.shndx, ds.value + addend,
                              'data %s defined in %s' % (name, du.rel))
        return Target('none', None, None, None, None, 'no address for %s' % name)

    # -- one relocation: compiled target against retail target
    def check(self, u, rel, rtarget, depth=0):
        """None if the compiled relocation provably resolves to rtarget, else a reason."""
        if rtarget is None:
            return 'retail target unknown (LO16 high half not recovered)'
        t = self.resolve(u, rel.sym, rel.addend)
        if t.kind == 'none':
            if (self.collect is not None and rel.sym.shndx == SHN_UNDEF
                    and rel.sym.name in self.collect):
                # Collection mode (tools/analysis/libsyms.py): record where retail points
                # this reference instead of failing it.  Such a function is PENDING, never
                # EXACT.
                self.pending.append((rel.sym.name, rtarget - rel.addend, rel.type))
                return None
            return 'unprovable: ' + t.how
        if t.kind == 'addr':
            self.used.add(t.how.split('(')[-1].split(' ')[0].rstrip(')')
                          if t.how.endswith(')') else 'local-code')
            if t.addr == rtarget:
                return None
            return 'compiled %s -> %#08x, retail -> %#08x' % (t.how, t.addr, rtarget)
        self.used.add('data')
        return self.check_item(t.unit, t.sec, t.off, rtarget, t.how, depth)

    def check_item(self, u, sec, off, rtarget, how, depth):
        obj, p = u.obj, self.retail.p
        it = obj.item(sec, off)
        if it is None:
            return 'unprovable: %s: no item at that offset' % how
        start, end = it
        base = rtarget - (off - start)
        key = (u.rel, sec, start)
        self.used_items.add(key)
        if key in self.items:
            b, reason = self.items[key]
            if b != base:
                self.conflicts.add(key)
                return '%s: item %s+%#x is at %#08x for another reference, here %#08x' % (
                    how, obj.secs[sec].name, start, b, base)
            return reason
        self.items[key] = (base, None)          # a cycle back here is consistent so far
        reason = self._item(u, sec, start, end, base, how, depth)
        self.items[key] = (base, reason)
        return reason

    def _item(self, u, sec, start, end, base, how, depth):
        obj, p = u.obj, self.retail.p
        n = end - start
        rs = p.section_at(base)
        where = '%s (%s+%#x, %d bytes, retail %#08x)' % (how, obj.secs[sec].name, start, n, base)
        if rs is None or base + n > rs.end:
            return 'data %s: not inside one retail section' % where
        if obj.secs[sec].type == SHT_NOBITS:
            return None if rs.type == SHT_NOBITS else 'data %s: .bss item, retail %s' % (
                where, rs.name)
        if rs.type == SHT_NOBITS:
            return 'data %s: retail target is in %s (no contents)' % (where, rs.name)
        ob = bytearray(obj.bytes_of(sec, start, n))
        rb = bytearray(p.read(base, n))
        orel = [r for r in obj.rels.get(sec, []) if start <= r.off < end]
        rrel = p.relocs_in(base, base + n)
        omap = {r.off - start: r for r in orel}
        rmap = {r.addr - base: r for r in rrel}
        if len(omap) != len(orel):
            return 'data %s: two relocations on one word' % where
        for k in sorted(set(omap) | set(rmap)):
            ot = omap[k].type if k in omap else None
            rt = rmap[k].type_id if k in rmap else None
            if ot != rt:
                return 'data %s: relocation at +%#x compiled %s, retail %s' % (
                    where, k, rname(ot), rname(rt))
            m = FIELD[ot]
            for buf in (ob, rb):
                w = struct.unpack_from('<I', buf, k)[0] & ~m & 0xffffffff
                struct.pack_into('<I', buf, k, w)
        if ob != rb:
            i = next(i for i in range(n) if ob[i] != rb[i])
            return 'data %s: byte +%#x compiled %02x, retail %02x' % (where, i, ob[i], rb[i])
        for k in sorted(omap):
            why = self.check(u, omap[k], self.retail.target(rmap[k]), depth + 1)
            if why:
                return 'data %s: word +%#x: %s' % (where, k, why)
        return None

    # -- one function
    def grade(self, u, tag):
        self.used, self.used_items = set(), set()
        self.pending = []
        res = {'addr': tag.addr, 'name': tag.name, 'kind': tag.kind, 'file': u.rel,
               'line': tag.line, 'real': u.real}
        f = self.retail.funcs.get(tag.addr)
        if u.obj is None:
            return dict(res, verdict='MISSING', detail='compile failed: ' +
                        (u.error.splitlines()[-1] if u.error else ''))
        if f is None:
            return dict(res, verdict='MISSING', detail='%#08x is not a function start in '
                        'funcs.csv' % tag.addr)
        sym, how = u.claim[tag]
        if sym is None:
            return dict(res, verdict='MISSING', detail=how)
        obj = u.obj
        res.update(symbol=sym.name, match=how, size=sym.size, retail_size=f['size'],
                   section=obj.secs[sym.shndx].name)
        n = min(sym.size, f['size']) // 4
        refs = []
        for i in range(n):
            ra, co = tag.addr + 4 * i, sym.value + 4 * i
            rw, cw = self.retail.p.word(ra), obj.word(sym.shndx, co)
            rr = self.retail.reloc(ra)
            cr = obj.relat.get((sym.shndx, co), [])
            if isinstance(rr, list) or len(cr) > 1:
                return dict(res, verdict='DIFFERS', word=i, retail=rw, compiled=cw,
                            detail='word %d: more than one relocation on the word' % i)
            cr = cr[0] if cr else None
            rt = rr.type_id if rr else None
            ct = cr.type if cr else None
            if rt != ct:
                return dict(res, verdict='DIFFERS', word=i, retail=rw, compiled=cw,
                            detail='word %d: relocation retail %s, compiled %s' % (
                                i, rname(rt), rname(ct)))
            m = FIELD.get(ct, 0) if ct is not None else 0
            if ct is not None and ct not in FIELD:
                return dict(res, verdict='DIFFERS', word=i, retail=rw, compiled=cw,
                            detail='word %d: relocation type %s' % (i, ct))
            if (rw & ~m) != (cw & ~m):
                return dict(res, verdict='DIFFERS', word=i, retail=rw, compiled=cw,
                            detail='word %d: retail %08x, compiled %08x' % (i, rw, cw))
            if cr:
                refs.append((i, cr, rr))
        if sym.size != f['size']:
            return dict(res, verdict='DIFFERS', word=n, detail='size: retail %d, compiled %d' % (
                f['size'], sym.size))
        out = []
        for i, cr, rr in refs:
            rtarget = self.retail.target(rr)
            why = self.check(u, cr, rtarget)
            if why:
                comp = []
                for k, c, _ in refs:
                    t = self.resolve(u, c.sym, c.addend)
                    comp.append((k, c.type, t.addr if t.kind == 'addr' else None))
                return dict(res, verdict='BADREF', word=i, compiled_refs=comp,
                            detail='word %d %s: %s' % (i, rname(cr.type), why))
            out.append((i, cr.type, rtarget))
        res['refs'] = out
        res['rules'] = sorted(self.used)
        res['items'] = sorted(self.used_items)
        if self.pending:
            return dict(res, verdict='PENDING', pending=list(self.pending),
                        detail='otherwise EXACT; %d references collected' % len(self.pending))
        return dict(res, verdict='EXACT', detail='%d words, %d relocations' % (n, len(out)))

    def finalize(self, results):
        """After a run: an EXACT function that relied on an object data item which another
        reference placed at a different retail address becomes BADREF."""
        for r in results:
            if r['verdict'] == 'EXACT':
                bad = [k for k in r.get('items', []) if tuple(k) in self.conflicts]
                if bad:
                    k = bad[0]
                    r['verdict'] = 'BADREF'
                    r['detail'] = 'data item %s section %d+%#x is placed at two retail addresses' % (
                        k[0], k[1], k[2])
        return results

    def grade_unit(self, u, which=None):
        out = []
        for t in u.tags:
            if t.region != 'us':
                continue
            if which is not None and t.addr not in which:
                continue
            out.append(self.grade(u, t))
        return out


def control_list(md=ROOT / 'src' / 'control' / 'CONTROL.md'):
    rows = []
    for line in open(md):
        m = re.match(r'\|\s*\d+\s*\|\s*`?([^|`]+?)`?\s*\|\s*`?0x([0-9a-fA-F]+)`?\s*\|', line)
        if m:
            rows.append((m.group(1), int(m.group(2), 16)))
    return rows


def disasm(word, addr):
    from allegrex import decode
    return decode(word, addr).text().strip()


def fmt(r):
    s = '%-8s 0x%06x %-44s %s  [%s]' % (r['verdict'], r['addr'], r['name'][:44], r['detail'],
                                        r['file'])
    if r['verdict'] == 'DIFFERS' and 'retail' in r:
        a = r['addr'] + 4 * r['word']
        s += '\n           retail   %08x  %s\n           compiled %08x  %s' % (
            r['retail'], disasm(r['retail'], a), r['compiled'], disasm(r['compiled'], a))
    return s


def summary(results):
    c = {}
    for r in results:
        k = (r['kind'], r['real'])
        c.setdefault(k, {}).setdefault(r['verdict'], 0)
        c[k][r['verdict']] += 1
    return c


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('files', nargs='*')
    ap.add_argument('--control', action='store_true', help='grade the CONTROL.md functions')
    ap.add_argument('--tree', action='store_true', help='grade every source file under src/')
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--quiet', action='store_true', help='print only non-EXACT and totals')
    ap.add_argument('--no-cache', action='store_true')
    a = ap.parse_args(argv)
    t0 = time.time()
    tree = Tree(use_cache=not a.no_cache)
    g = Grader(tree)
    jobs = []
    if a.control:
        groups = {}
        for f, addr in control_list():
            groups.setdefault(f, set()).add(addr)
        jobs = [(ROOT / f, w) for f, w in sorted(groups.items())]
    if a.tree:
        jobs += [(p, None) for p in source_files()]
    jobs += [(Path(f), None) for f in a.files]
    if not jobs:
        ap.error('give files, --control or --tree')
    tree.compile_many([p for p, _ in jobs])
    results = []
    for p, which in jobs:
        u = tree.unit(p)
        for pr in u.problems:
            sys.stderr.write('%s:%d: %s\n' % pr)
        results += g.grade_unit(u, which)
    g.finalize(results)
    el = time.time() - t0
    if a.json:
        for r in results:
            for k in ('refs', 'items', 'compiled_refs'):
                r.pop(k, None)
        json.dump({'results': results, 'seconds': round(el, 2), 'compile': tree.times},
                  sys.stdout, indent=1)
        print()
    else:
        for r in results:
            if not a.quiet or r['verdict'] != 'EXACT':
                print(fmt(r))
        for (kind, real), c in sorted(summary(results).items()):
            tot = sum(c.values())
            print('== %-10s %-9s %d/%d EXACT  (%s)' % (
                kind, 'real' if real else 'not-real', c.get('EXACT', 0), tot,
                ', '.join('%s %d' % kv for kv in sorted(c.items()))))
        print('== %.2f s (%d compiled, %d cached)' % (el, tree.times['compiled'],
                                                     tree.times['cached']))
    bad = sum(1 for r in results if r['kind'] == 'implements' and r['verdict'] != 'EXACT')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
