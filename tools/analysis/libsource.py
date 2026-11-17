#!/usr/bin/env python3
"""Prove library symbols from the GCC 3.3.3 source: reproduce the reference object, then
compare the retail-compiler build with retail.

    libsource.py                 reproduce every unit, prove its symbols, print the result
    libsource.py --selftest      a one-token source change and a different flag set must each
                                 fail to reproduce the reference object

Source: gcc-core-3.3.3.tar.bz2 and gcc-g++-3.3.3.tar.bz2 from ftp.gnu.org, kept untracked in
the main checkout's references/ and checked by sha256 (SHA256 below), unpacked under
build/gcc-src/.  No script from the tarballs is run: the one generated header the libgcc units
need (tconfig.h) is written by this module from what gcc/mkconfig.sh would write.

A unit is one library object: a source file, its preprocessor definitions and flags, and the
reference archive member it must reproduce.

  Admission.  The unit is compiled with STOCK psp-gcc 1.3.1 (cc.py --cc 1.3.1, no pinned
  defaults, no @cflags) and must reproduce the reference member of psp-gcc-1.3.1.tar.gz
  exactly: the same allocated sections; in each, the same bytes with relocated fields masked,
  and relocations of the same type at the same offsets against the same symbol name (or the
  same section) with the same addend.  Only an admitted unit is used further.
  Proof.  The same unit is compiled with the pinned 1.3.1-nocmov.  A symbol is proven at a
  retail address when the retail bytes there equal that build's copy (relocated fields
  masked, relocation types equal) and every relocation's retail target is proven in turn: a
  function or data symbol of an admitted unit by this same proof, recursively; a symbol of
  libfuncs.csv or an accepted libsyms.csv row (exact/cmov) by address; local data by its
  bytes.  Anything else fails the proof.

Flags (from the GCC 3.3.3 makefiles; see docs/GATES.md):
  libgcc fp-bit units (gcc/Makefile.in LIBGCC2_CFLAGS, gcc/mklibgcc.in, mips/t-elf):
    -O2 -DIN_GCC -DCROSS_COMPILE -DIN_LIBGCC2 -D__GCC_FLOAT_NOT_NEEDED -G 0
    -DFINE_GRAINED_LIBRARIES -DL_<name>, source dp-bit.c (a copy of config/fp-bit.c).
    No -g: the reference objects carry no debug sections.  The warning flags, -isystem
    ./include and @inhibit_libc@ do not reach these sources' code (fp-bit includes no system
    header) and are left out.
    Include path -I. -I$(srcdir) -I$(srcdir)/config -I$(srcdir)/../include, with tconfig.h
    for a mipsel ELF target (config.gcc: tm_file mips/mips.h mips/elf.h; configure.in adds
    defaults.h and puts ansidecl.h first).
  libsupc++ units (libstdc++-v3/libsupc++/Makefile.am, top-level CXXFLAGS -g -O2):
    -g -O2 -fno-implicit-templates.  No -ffunction-sections (the reference tinfo.o has one
    .text) and no PIC flag (its relocations are absolute HI16/LO16).  Include order
    -I gcc -I include, the build tree's include/ (generated: c++config.h and the std headers,
    which the compiler's installed copies stand in for), -I libsupc++.
The sources are flattened: every #include that resolves in the source tree is replaced by
the file's text (with # line markers), exactly as the preprocessor would read it; includes
that the build tree's include/ supplies are left for the compiler.  cc.py can only send files
it finds next to a source, so this is how the headers reach the compile host.
"""
import hashlib
import json
import re
import struct
import sys
import tarfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE), str(HERE.parent / 'toolchains')]
ROOT = HERE.parent.parent
REFS = Path('/Users/jeffreywilbur/projects/strutb/ridgeracerpsp/references')
SHA256 = {
    'gcc-core-3.3.3.tar.bz2': 'a4bf992ca719711a77d09b84fc496bbe6fcecb8feac996c2e6e102d3cbbe15eb',
    'gcc-g++-3.3.3.tar.bz2': '5b82243239d4a400cfe94ac9b27a008c510aa55c574b2df1f6e95b45d6a70bc4',
}
SRC = ROOT / 'build' / 'gcc-src'
GCC = SRC / 'gcc-3.3.3'
STAGE = ROOT / 'build' / 'libsrc'

LIBGCC_FLAGS = ['-O2', '-DIN_GCC', '-DCROSS_COMPILE', '-DIN_LIBGCC2', '-D__GCC_FLOAT_NOT_NEEDED',
                '-G', '0', '-DFINE_GRAINED_LIBRARIES']
SUPCXX_FLAGS = ['-g', '-O2', '-fno-implicit-templates']
# Headers the build tree's include/ provides (libstdc++-v3/include/Makefile.am: c++config.h is
# generated, cstddef is a std header); the compiler's installed copies stand in for them.
BUILD_INCLUDE = {'bits/c++config.h', 'cstddef'}

UNITS = {
    '_ge_df': dict(lib='libgcc.a', member='_ge_df.o', src='gcc/config/fp-bit.c', lang='c',
                   flags=LIBGCC_FLAGS + ['-DL_ge_df'], syms=['__gedf2']),
    '_lt_df': dict(lib='libgcc.a', member='_lt_df.o', src='gcc/config/fp-bit.c', lang='c',
                   flags=LIBGCC_FLAGS + ['-DL_lt_df'], syms=['__ltdf2']),
    '_df_to_sf': dict(lib='libgcc.a', member='_df_to_sf.o', src='gcc/config/fp-bit.c',
                      lang='c', flags=LIBGCC_FLAGS + ['-DL_df_to_sf'], syms=['__truncdfsf2']),
    'tinfo': dict(lib='libsupc++.a', member='tinfo.o', src='libstdc++-v3/libsupc++/tinfo.cc',
                  lang='c++', flags=SUPCXX_FLAGS),
}

TCONFIG = '''#ifdef IN_GCC
/* Provide three core typedefs used by everything, if we are compiling
   GCC.  These used to be found in rtl.h and tree.h, but this is no
   longer practical.  Providing these here rather that system.h allows
   the typedefs to be used everywhere within GCC. */
struct rtx_def;
typedef struct rtx_def *rtx;
struct rtvec_def;
typedef struct rtvec_def *rtvec;
union tree_node;
typedef union tree_node *tree;
#endif
#define GTY(x)
#ifdef IN_GCC
# include "ansidecl.h"
# include "mips/mips.h"
# include "mips/elf.h"
# include "defaults.h"
#endif
'''


def unpack():
    if (GCC / 'gcc' / 'config' / 'fp-bit.c').is_file() and \
            (GCC / 'libstdc++-v3' / 'libsupc++' / 'tinfo.cc').is_file():
        return
    for name, want in SHA256.items():
        data = (REFS / name).read_bytes()
        got = hashlib.sha256(data).hexdigest()
        if got != want:
            raise SystemExit('libsource: %s: sha256 %s, expected %s' % (name, got, want))
    SRC.mkdir(parents=True, exist_ok=True)
    for name in SHA256:
        with tarfile.open(REFS / name, 'r:bz2') as tf:
            tf.extractall(SRC, filter='data')


INC = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"]', re.M)


def flatten(path, idirs, seen_stack=()):
    """Text of path with every include that resolves in the source tree inlined."""
    path = Path(path)
    if path in seen_stack:
        raise SystemExit('libsource: include cycle at %s' % path)
    lines = path.read_text(encoding='latin-1').split('\n')
    out = ['# 1 "%s"' % path.relative_to(SRC) if SRC in path.parents else '# 1 "%s"' % path.name]
    for n, line in enumerate(lines, 1):
        m = INC.match(line)
        if not m:
            out.append(line)
            continue
        kind, name = m.group(1), m.group(2)
        cands = ([path.parent] if kind == '"' else []) + list(idirs)
        hit = None
        for d in cands:
            if d == 'BUILD':
                if name in BUILD_INCLUDE:
                    break
                continue
            if (Path(d) / name).is_file():
                hit = Path(d) / name
                break
        if hit is None:
            if name not in BUILD_INCLUDE:
                raise SystemExit('libsource: %s:%d: %s resolves nowhere' % (path, n, name))
            out.append(line)
            continue
        out.append(flatten(hit, idirs, seen_stack + (path,)))
        out.append('# %d "%s"' % (n + 1, path.relative_to(SRC) if SRC in path.parents
                                    else path.name))
    return '\n'.join(out)


def stage(name, unit, text_edit=None):
    """Write the flattened unit under build/libsrc/ and return its path."""
    unpack()
    d = STAGE / name
    d.mkdir(parents=True, exist_ok=True)
    if unit['lang'] == 'c':
        (d / 'tconfig.h').write_text(TCONFIG)
        (d / 'dp-bit.c').write_text((GCC / unit['src']).read_text(encoding='latin-1'))
        g = GCC / 'gcc'
        idirs = [d, g, g / 'config', GCC / 'include']
        text = flatten(d / 'dp-bit.c', idirs)
        out = d / (name + '.c')
    else:
        idirs = [GCC / 'gcc', GCC / 'include', 'BUILD', GCC / 'libstdc++-v3' / 'libsupc++']
        text = flatten(GCC / unit['src'], idirs)
        out = d / (name + '.cc')
    if text_edit:
        text = text_edit(text)
    out.write_text(text, encoding='latin-1')
    return out


def reference_obj(unit):
    import io
    import libarchive as la
    import score
    raw = (la.REFS / 'psp-gcc-1.3.1.tar.gz').read_bytes()
    with tarfile.open(fileobj=io.BytesIO(raw), mode='r:gz') as tf:
        for m in tf.getmembers():
            if m.name.endswith('/' + unit['lib']):
                for mn, md in la.ar_members(tf.extractfile(m).read()):
                    if mn == unit['member']:
                        return score.Obj(md)
    raise SystemExit('libsource: no %s(%s) in psp-gcc-1.3.1' % (unit['lib'], unit['member']))


def compile_unit(path, ver, flags):
    import cc
    import score
    r = cc.compile_file(str(path), ver, flags, use_defaults=False, use_file_flags=False)
    return score.Obj(Path(r['o']).read_bytes())


def alloc_sections(o):
    import score
    return {s.name: s for s in o.secs if s.flags & score.SHF_ALLOC and s.size}


def same_object(a, b):
    """None if objects a and b have the same allocated sections with the same masked bytes and
    the same relocations (offset, type, symbol name or section name, addend); else why."""
    import score
    sa, sb = alloc_sections(a), alloc_sections(b)
    if set(sa) != set(sb):
        return 'sections differ: only built %s; only reference %s' % (
            sorted(set(sa) - set(sb))[:4], sorted(set(sb) - set(sa))[:4])
    for name in sorted(sa):
        x, y = sa[name], sb[name]
        if x.size != y.size or x.type != y.type:
            return '%s: size %d against %d' % (name, x.size, y.size)

        def rels(o, s):
            out = {}
            for r in o.rels.get(s.index, []):
                tgt = r.sym.name or ('[%s]' % o.secs[r.sym.shndx].name)
                out[r.off] = (r.type, tgt, r.addend)
            return out
        ra, rb = rels(a, x), rels(b, y)
        if ra != rb:
            k = min(k for k in set(ra) | set(rb) if ra.get(k) != rb.get(k))
            return '%s+%#x: relocation built %s, reference %s' % (name, k, ra.get(k), rb.get(k))
        ba, bb = bytearray(a.bytes_of(x.index, 0, x.size)), bytearray(b.bytes_of(y.index, 0,
                                                                                  y.size))
        for off, (t, _, _) in ra.items():
            m = score.FIELD.get(t, 0xffffffff)
            for buf in (ba, bb):
                w = struct.unpack_from('<I', buf, off)[0] & ~m & 0xffffffff
                struct.pack_into('<I', buf, off, w)
        if ba != bb:
            k = next(i for i in range(len(ba)) if ba[i] != bb[i])
            return '%s+%#x: byte built %02x, reference %02x' % (name, k, ba[k], bb[k])
    return None


class SourceProver:
    """Proves symbols at retail addresses against the nocmov builds of admitted units."""

    def __init__(self, objs, accepted):
        import funcmap
        import score
        from prx import Prx
        self.score = score
        self.p = Prx.from_ref('us')
        self.funcs = {f['addr']: f for f in funcmap.load()}
        self.objs = objs                      # unit name -> Obj (nocmov build)
        self.defs = {}
        for un, o in objs.items():
            for s in o.syms:
                if s.name and o.defined(s) and s.type != score.STT_SECTION and \
                        s.bind != score.STB_LOCAL:
                    self.defs.setdefault(s.name, (un, o, s))
        self.accepted = accepted              # name -> address (libfuncs + libsyms exact/cmov)
        self.memo = {}

    def prove(self, name, addr):
        if name not in self.defs:
            return 'no admitted unit defines %s' % name
        un, o, s = self.defs[name]
        return self.symbol(o, s, addr)

    def symbol(self, o, s, addr):
        key = (id(o), s.index, addr)
        if key in self.memo:
            return self.memo[key]
        self.memo[key] = None                 # a cycle back here is consistent so far
        why = self._symbol(o, s, addr)
        self.memo[key] = why
        return why

    def _symbol(self, o, s, addr):
        sc, p = self.score, self.p
        code = o.is_code(s.shndx)
        if code:
            f = self.funcs.get(addr)
            if f is None:
                return '%s: %#08x is not a function start' % (s.name, addr)
            if f['size'] != s.size:
                return '%s: retail %d bytes, built %d' % (s.name, f['size'], s.size)
        return self.span(o, s.shndx, s.value, s.size, addr, s.name)

    def span(self, o, sec, start, n, addr, label):
        sc, p = self.score, self.p
        rs = p.section_at(addr)
        if rs is None or addr + n > rs.end or rs.type == sc.SHT_NOBITS:
            return '%s: retail %#08x has no %d bytes of contents' % (label, addr, n)
        ob = bytearray(o.bytes_of(sec, start, n))
        rb = bytearray(p.read(addr, n))
        orl = {r.off - start: r for r in o.rels.get(sec, []) if start <= r.off < start + n}
        rrl = {r.addr - addr: r for r in p.relocs_in(addr, addr + n)}
        for k in sorted(set(orl) | set(rrl)):
            ot = orl[k].type if k in orl else None
            rt = rrl[k].type_id if k in rrl else None
            if ot != rt:
                return '%s+%#x: relocation built %s, retail %s' % (label, k, ot, rt)
            m = sc.FIELD[ot]
            for buf in (ob, rb):
                w = struct.unpack_from('<I', buf, k)[0] & ~m & 0xffffffff
                struct.pack_into('<I', buf, k, w)
        if ob != rb:
            k = next(i for i in range(n) if ob[i] != rb[i])
            return '%s+%#x: byte built %02x, retail %02x' % (label, k, ob[k], rb[k])
        for k in sorted(orl):
            r = orl[k]
            t = rrl[k].target
            if t is None:
                import hilo  # noqa: F401  (retail LO16 recovery is in score.Retail)
                t = self.lo16().get(rrl[k].addr)
            if t is None:
                return '%s+%#x: retail target unknown' % (label, k)
            why = self.target(o, r, t)
            if why:
                return '%s+%#x: %s' % (label, k, why)
        return None

    _lo = None

    def lo16(self):
        if SourceProver._lo is None:
            import score
            SourceProver._lo = score.Retail().lo16
        return SourceProver._lo

    def target(self, o, r, t):
        sc = self.score
        sym = r.sym
        if sym.type == sc.STT_SECTION or (sym.bind == sc.STB_LOCAL and o.defined(sym)):
            off = sym.value + r.addend
            if o.is_code(sym.shndx):
                for f in o.functions():
                    if f.shndx == sym.shndx and f.value <= off < f.value + f.size:
                        return self.symbol(o, f, t - (off - f.value))
                return 'local code %#x in no function' % off
            it = o.item(sym.shndx, off)
            if it is None:
                return 'local data %#x: no item' % off
            return self.span(o, sym.shndx, it[0], it[1] - it[0], t - (off - it[0]),
                             '%s+%#x' % (o.secs[sym.shndx].name, it[0]))
        name = sym.name
        if name in self.accepted:
            a = self.accepted[name] + r.addend
            return None if a == t else '%s at %#08x, retail %#08x' % (name, a, t)
        if o.defined(sym):
            return self.symbol(o, sym, t - r.addend)
        if name in self.defs:
            _, o2, s2 = self.defs[name]
            return self.symbol(o2, s2, t - r.addend)
        return 'no proof for %s' % name


def accepted_addresses(rows=None):
    """libfuncs.csv symbols at one address, plus libsyms rows accepted as exact or cmov (from
    rows when given, else from the committed CSV).  'source' rows are not used here: a source
    proof rests only on proofs that do not themselves need one."""
    import score
    import libsyms
    acc = {}
    for n, addrs in score.load_libsyms().items():
        if len(addrs) == 1:
            acc[n] = next(iter(addrs))
    if rows is None:
        acc.update(libsyms.load(kinds=('exact', 'cmov')))
    else:
        acc.update({r['symbol']: int(r['address'], 16) for r in rows
                    if r['accepted'] == 'yes' and r['match'] in ('exact', 'cmov')})
    return acc


def build_all(units=UNITS, edit=None, flags_override=None):
    """{unit: dict(admitted, why, ref, flags, path)} and {unit: nocmov Obj}."""
    res, objs = {}, {}
    for name, u in units.items():
        flags = list(flags_override.get(name, u['flags']) if flags_override else u['flags'])
        path = stage(name, u, edit.get(name) if edit else None)
        ref = reference_obj(u)
        stock = compile_unit(path, '1.3.1', flags)
        why = same_object(stock, ref)
        res[name] = dict(admitted=why is None, why=why or '', flags=' '.join(flags),
                         source=u['src'], ref='psp-gcc-1.3.1 %s(%s)' % (u['lib'], u['member']))
        if why is None:
            objs[name] = compile_unit(path, '1.3.1-nocmov', flags)
    return res, objs


def prove_rows(rows):
    """Give refused libsyms rows (no disagreeing site) a source proof where an admitted unit
    defines the symbol.  Returns (rows, unit results)."""
    res, objs = build_all()
    sp = SourceProver(objs, accepted_addresses(rows))
    owner = {}
    for un, o in objs.items():
        for s in o.syms:
            if s.name and o.defined(s) and s.bind != 0:
                owner.setdefault(s.name, un)
    for r in rows:
        r.setdefault('source', '')
        r.setdefault('flags', '')
        r.setdefault('reproduced', '')
        if r['accepted'] == 'yes' or int(r['disagreeing']):
            continue
        un = owner.get(r['symbol'])
        if un is None:
            continue
        why = sp.prove(r['symbol'], int(r['address'], 16))
        r['source'] = res[un]['source']
        r['flags'] = res[un]['flags']
        r['reproduced'] = res[un]['ref']
        if why is None:
            r.update(match='source', accepted='yes', reference='GCC 3.3.3 source, 1.3.1-nocmov',
                     reason='')
        else:
            r['reason'] = (r['reason'] + ' | source build: ' + why)[:400]
    for un, x in res.items():
        if not x['admitted']:
            for r in rows:
                if r['symbol'] in UNITS[un].get('syms', ()) and r['accepted'] != 'yes':
                    r.update(source=x['source'], flags=x['flags'], reproduced='no: ' + x['ref'])
                    r['reason'] = (r['reason'] + ' | source: stock 1.3.1 does not reproduce '
                                   + x['ref'] + ': ' + x['why'])[:400]
    return rows, res, sp


def selftest():
    """Two planted faults on an admitted unit (_df_to_sf, __truncdfsf2), each must stop its
    admission: a one-token source change (`sffrac |= 1` becomes `sffrac |= 2`, the sticky
    bit) and a different flag set (-O1 for -O2)."""
    u = {'_df_to_sf': UNITS['_df_to_sf']}
    base, _ = build_all(u)
    ok = base['_df_to_sf']['admitted']
    print('selftest: baseline _df_to_sf admitted: %s %s' % (ok, base['_df_to_sf']['why']))

    def edit(t):
        k = t.index('#if defined(L_df_to_sf)')
        j = t.index('sffrac |= 1;', k)
        return t[:j] + 'sffrac |= 2;' + t[j + len('sffrac |= 1;'):]
    a, _ = build_all(u, edit={'_df_to_sf': edit})
    print('selftest: one token changed: admitted %s (%s)' % (a['_df_to_sf']['admitted'],
                                                            a['_df_to_sf']['why']))
    fl = [x if x != '-O2' else '-O1' for x in UNITS['_df_to_sf']['flags']]
    b, _ = build_all(u, flags_override={'_df_to_sf': fl})
    print('selftest: -O1 for -O2: admitted %s (%s)' % (b['_df_to_sf']['admitted'],
                                                       b['_df_to_sf']['why']))
    stage('_df_to_sf', UNITS['_df_to_sf'])     # leave the staged copy as admitted
    good = ok and not a['_df_to_sf']['admitted'] and not b['_df_to_sf']['admitted']
    print('selftest:', 'PASS' if good else 'FAIL')
    return 0 if good else 1


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    res, objs = build_all()
    for un, x in res.items():
        print('%-10s %-9s %s %s  [%s; %s]' % (un, 'ADMITTED' if x['admitted'] else 'REFUSED',
                                              x['source'], x['why'], x['flags'], x['ref']))
    sp = SourceProver(objs, accepted_addresses())
    want = json.loads(argv[1]) if len(argv) > 1 else {}
    for name, addr in want.items():
        print(name, hex(addr), sp.prove(name, addr) or 'PROVEN')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
