#!/usr/bin/env python3
"""The fence: library / game / unknown for every function and object.

    libfence.py              write config/us/libfuncs.csv, tus.csv and fence.csv
                             (fence.csv: class and evidence for every function)
    libfence.py --check      rebuild and compare with the committed CSVs
    libfence.py --selftest   prove the fingerprint and the classes catch planted faults

Inputs: the USA BOOT.BIN (via refcheck), config/us/funcs.csv, and the
library archives of psp-gcc-1.3.1 and psp-gcc-1.7.1 (libarchive.py).

LIBRARY (any one of):
  fingerprint  the function lies wholly inside a code section of a reference
               library object (crt0/crtbegin/crtend, libgcc, libc, libm,
               libstdc++, libsupc++) whose words match the retail words with
               relocated fields masked (R_MIPS_26: low 26 bits, HI16/LO16: low
               16, R_MIPS_32: all), with the same relocation type at every
               word, and whose masked pattern occurs at exactly one retail
               address, which is a funcs.csv start.  Patterns found at several
               addresses, or once but not at a function start, count for
               nothing.  A virtual-table reference from a game class does not
               make a library function game (e.g. __cxa_pure_virtual).
  crt          .init / .fini: proven to be exactly crti + crtbegin (+ crtend)
               + crtn concatenated, masked as above.
  stub         an SCE import stub (.sceStub.text, counted by .lib.stub): the
               linker builds these from SDK stub libraries; no game source.

GAME (any one of):
  rtti         the function is a virtual-table entry of a class whose RTTI
               name (typeinfo object: word -> a *_type_info vtable, word ->
               name string) is not defined by any reference library object.
  vtref        the function's code has a relocation into such a class's
               virtual table (constructors/destructors store the vptr).
  object       the function is not LIBRARY and lies in the same linked object
               as an rtti or vtref function.  "Same object" = the same CIE group: each
               CIE is one input .eh_frame section (182 and 76 byte-identical
               CIEs coexist, so the linker merged none), and the FDE pc ranges
               of each group are disjoint and in link order.  The object's
               extent is taken as first FDE start .. last FDE end.

Everything else is UNKNOWN.  A function that both fingerprints as a library
object's .text and sits in a game object is a conflict and is UNKNOWN; a
fingerprint of a .gnu.linkonce section (template code instantiated from
library headers inside a game object) stays LIBRARY.

Objects (tus.csv): one row per CIE group ('cie') and one per stretch of code
between groups ('gap': owner unknown, may hold several objects without
.eh_frame, or tails of neighbouring ones).
"""
import bisect
import csv
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE)]
from prx import Prx                 # noqa: E402
from ehframe import parse as parse_eh   # noqa: E402
from libarchive import load_blobs, fingerprint, retail_words, blob_key   # noqa: E402
import funcmap                      # noqa: E402

ROOT = HERE.parent.parent
LIBCSV = ROOT / 'config' / 'us' / 'libfuncs.csv'
TUCSV = ROOT / 'config' / 'us' / 'tus.csv'
FENCECSV = ROOT / 'config' / 'us' / 'fence.csv'


class FenceError(Exception):
    pass


def crt_proof(p, blobs):
    """True when .init/.fini are exactly the crt pieces concatenated (per tarball)."""
    order = {'.init': ['crti.o', 'crtbegin.o', 'crtend.o', 'crtn.o'],
             '.fini': ['crti.o', 'crtbegin.o', 'crtend.o', 'crtn.o']}
    R = retail_words(p)
    proofs = {}
    for sec, objs in order.items():
        s = p.section(sec)
        retail = [R[a] for a in range(s.addr, s.end, 4)]
        ok = []
        for tb in sorted({b.tarball for b in blobs}):
            seq = []
            for o in objs:
                for b in blobs:
                    if b.tarball == tb and b.section == sec and b.lib.endswith(o):
                        seq += [blob_key(b, k) for k in range(len(b.words))]
            if seq == retail:
                ok.append(tb)
        proofs[sec] = ok
    return proofs


def rtti(p, lib_type_names):
    """(classes, methods): non-library class names and {method addr: class}."""
    r32 = {r.addr: r.target for r in p.relocs if r.type_id == 2}
    code = [p.section(n) for n in ('.text',)]

    def in_code(a):
        return any(s.addr <= a < s.end for s in code)

    def cstr(a):
        s = p.section_at(a)
        if not s or s.name not in ('.rodata', '.data'):
            return None
        b = p.read(a, 256)
        z = b.find(b'\0')
        if z <= 0:
            return None
        t = b[:z]
        return t.decode() if re.fullmatch(rb'[A-Za-z0-9_]+', t) else None
    # typeinfo objects: [R32 -> X][R32 -> name]; the *_type_info vtables X are
    # the targets shared by such pairs whose names are mangled type names.
    cand = defaultdict(list)
    for a, t in r32.items():
        if a + 4 in r32:
            n = cstr(r32[a + 4])
            if n and re.match(r'^(N\d|\d|St|S[a-z])', n):
                cand[t].append((a, n))
    tivt = {t for t, v in cand.items() if len(v) >= 5}
    typeinfo = {a: n for t in tivt for a, n in cand[t]}
    classes = {a: n for a, n in typeinfo.items() if n not in lib_type_names}
    methods, vtables = {}, []
    for a, t in r32.items():
        if t in classes and (a - 4) not in r32:      # vtable: [offset][typeinfo][fn...]
            x = a + 4
            while x in r32 and in_code(r32[x]):
                methods.setdefault(r32[x], set()).add(classes[t])
                x += 4
            vtables.append((a - 4, x, classes[t]))
    return typeinfo, classes, methods, sorted(vtables)


def build(p, F, blobs, names_in_libs):
    sigs = fingerprint(p, blobs)
    starts = [f['addr'] for f in F]
    fidx = {f['addr']: k for k, f in enumerate(F)}
    lib = {}                                   # func addr -> dict
    ambiguous = Counter()
    sym_mismatch = []
    for sig, (hits, bs) in sigs.items():
        if len(hits) != 1:
            if hits:
                ambiguous['positions>1'] += 1
            continue
        a0 = hits[0]
        n = len(sig) * 4
        if a0 not in fidx:
            ambiguous['unanchored'] += 1     # unique, but not at a function start
            continue
        ids = sorted({(b.lib.rsplit('/', 1)[-1], b.member, b.section) for b in bs})
        tbs = sorted({b.tarball for b in bs})
        syms = {}
        for b in bs:
            for off, size, name, bind in b.syms:
                syms.setdefault(off, set()).add(name)
        for off in syms:
            if a0 + off not in fidx and off < n:
                sym_mismatch.append((a0 + off, sorted(syms[off])))
        k = bisect.bisect_left(starts, a0)
        while k < len(F) and F[k]['addr'] < a0 + n:
            f = F[k]
            if f['addr'] >= a0 and f['addr'] + f['size'] <= a0 + n:
                lib[f['addr']] = {'how': 'fingerprint', 'ids': ids, 'tarballs': tbs,
                                  'symbol': ';'.join(sorted(syms.get(f['addr'] - a0, ()))),
                                  'linkonce': all(i[2].startswith('.gnu.linkonce') for i in ids),
                                  'blob': (a0, n)}
            k += 1
    crt = crt_proof(p, blobs)
    for f in F:
        if f['section'] in ('.init', '.fini'):
            if not crt[f['section']]:
                raise FenceError(f"{f['section']} is not the crt concatenation")
            lib[f['addr']] = {'how': 'crt', 'ids': [('crti.o+crtbegin.o+crtend.o+crtn.o', '', f['section'])],
                              'tarballs': crt[f['section']], 'symbol': '', 'linkonce': False}
        elif 'stub' in f['evidence']:
            lib[f['addr']] = {'how': 'stub', 'ids': [(f['import'], '', '.sceStub.text')],
                              'tarballs': [], 'symbol': '', 'linkonce': False}
    typeinfo, classes, methods, vtables = rtti(p, names_in_libs)
    # vtref: code that addresses a game class's vtable (constructors and
    # destructors store the vptr); library code cannot name a game vtable.
    vstart = [v[0] for v in vtables]
    vtref = defaultdict(set)
    for r in p.relocs:
        if r.section != '.text' or r.target is None:
            continue
        k = bisect.bisect_right(vstart, r.target) - 1
        if k >= 0 and r.target < vtables[k][1]:
            j = bisect.bisect_right(starts, r.addr) - 1
            vtref[F[j]['addr']].add(vtables[k][2])
    # CIE groups
    cies, fdes = parse_eh(p)
    groups = defaultdict(list)
    for fd in fdes:
        groups[fd.cie].append(fd)
    ranges = []
    for ci in sorted(groups):
        live = [fd for fd in groups[ci] if fd.start is not None]
        if not live:
            raise FenceError(f'CIE {ci} has no live FDE')
        ranges.append((min(fd.start for fd in live), max(fd.start + fd.size for fd in live), ci))
    for a, b in zip(ranges, ranges[1:]):
        if a[1] > b[0]:
            raise FenceError('CIE group ranges overlap')
    rstarts = [r[0] for r in ranges]

    def group_of(a):
        k = bisect.bisect_right(rstarts, a) - 1
        return ranges[k][2] if k >= 0 and a < ranges[k][1] else None
    grp_rtti = defaultdict(set)
    for m in list(methods) + list(vtref):
        g = group_of(m)
        if g is not None and m not in lib:
            grp_rtti[g].add(m)
    cls = {}
    conflicts = []
    for f in F:
        a = f['addr']
        g = group_of(a)
        l = lib.get(a)
        game_ev = []
        if a in methods:
            game_ev.append('rtti:' + ','.join(sorted(methods[a])))
        if a in vtref:
            game_ev.append('vtref:' + ','.join(sorted(vtref[a])))
        if g is not None and grp_rtti.get(g):
            game_ev.append(f'object:cie{g}')
        obj_ev = [e for e in game_ev if e.startswith('object:')]
        if l and not obj_ev and any(e.startswith('vtref:') for e in game_ev):
            conflicts.append((a, l, game_ev))      # library code naming a game vtable
            cls[a] = ('unknown', {'conflict': game_ev})
        elif l and obj_ev and l['how'] == 'fingerprint' and not l['linkonce']:
            conflicts.append((a, l, game_ev))      # a library .text inside a game object
            cls[a] = ('unknown', {'conflict': game_ev})
        elif l:
            cls[a] = ('library', l)
        elif game_ev:
            cls[a] = ('game', game_ev)
        else:
            cls[a] = ('unknown', None)
    return {'cls': cls, 'lib': lib, 'sigs': sigs, 'ambiguous': ambiguous,
            'sym_mismatch': sym_mismatch, 'crt': crt, 'typeinfo': typeinfo,
            'classes': classes, 'methods': methods, 'vtref': vtref, 'vtables': vtables, 'ranges': ranges, 'cies': cies,
            'groups': groups, 'conflicts': conflicts, 'group_of': group_of}


def cie_tests(p, m):
    """Tests of 'one CIE = one linked object'.  Returns (lines, failures)."""
    cies, groups, ranges = m['cies'], m['groups'], m['ranges']
    out, bad = [], []
    _c, fdes = parse_eh(p)
    hi, back = -1, 0
    for fd in fdes:
        back += fd.cie < hi
        hi = max(hi, fd.cie)
    out.append(f'T1 FDEs pointing back past a later CIE: {back}')
    bad += ['T1'] if back else []
    raw = Counter(p.read(c.addr, c.length + 4) for c in cies)
    out.append(f'T2 CIEs {len(cies)}, distinct byte strings {len(raw)} '
               f'(repeats {sorted(raw.values(), reverse=True)}): identical CIEs were not merged')
    bad += ['T2'] if len(raw) == len(cies) and len(cies) > 3 else []
    ov = sum(1 for a, b in zip(ranges, ranges[1:]) if a[1] > b[0] or b[2] < a[2])
    out.append(f'T3 group pc ranges overlapping or out of CIE order: {ov}')
    bad += ['T3'] if ov else []
    for sec in ('.ctors', '.dtors'):
        tg = [r.target for r in p.relocs if r.section == sec and r.target is not None]
        per = Counter(m['group_of'](t) for t in tg)
        multi = {g: n for g, n in per.items() if g is not None and n > 1}
        out.append(f'T4 {sec}: {len(tg)} entries, {sum(1 for g in tg if m["group_of"](g) is not None)} '
                   f'inside a group, groups holding more than one: {len(multi)}')
        bad += ['T4' + sec] if multi else []
    ls = [(fd.lsda, fd.cie) for fd in fdes if fd.lsda is not None]
    lo = sum(1 for a, b in zip(ls, ls[1:]) if b[0] < a[0])
    out.append(f'T5 LSDAs out of FDE/CIE order: {lo}')
    bad += ['T5'] if lo else []
    cm = p.section('.comment')
    idents = [x for x in p.data[cm.offset:cm.offset + cm.size].split(b'\0') if x]
    internal = [k for k, x in enumerate(idents) if x.endswith(b'.internal')]
    out.append(f'T6 .comment idents {len(idents)} >= CIE groups {len(cies)}: '
               f'{len(idents) >= len(cies)}; .internal at ident positions {internal}')
    bad += ['T6'] if len(idents) < len(cies) else []
    return out, bad


def tu_rows(p, F, m):
    ranges, cies, groups = m['ranges'], m['cies'], m['groups']
    ctors = {r.target for r in p.relocs if r.section == '.ctors' and r.target is not None}
    dtors = {r.target for r in p.relocs if r.section == '.dtors' and r.target is not None}
    text = p.section('.text')
    bounds = []
    prev = text.addr
    for lo, hi, ci in ranges:
        if lo > prev:
            bounds.append((prev, lo, 'gap', None))
        bounds.append((lo, hi, 'cie', ci))
        prev = hi
    if prev < text.end:
        bounds.append((prev, text.end, 'gap', None))
    rows = []
    for lo, hi, kind, ci in bounds:
        fs = [f for f in F if lo <= f['addr'] < hi]
        c = Counter(m['cls'][f['addr']][0] for f in fs)
        libs = sorted({'%s(%s)' % (i[0], i[1]) if i[1] else i[0]
                       for f in fs if f['addr'] in m['lib'] for i in m['lib'][f['addr']]['ids']
                       if not i[2].startswith('.gnu.linkonce')})
        if c['game'] and not c['unknown'] and not c['library']:
            klass = 'game'
        elif c['library'] == len(fs):
            klass = 'library'
        elif c['game'] and not c['unknown']:
            klass = 'game'          # game object holding header-template library code
        elif c['library'] and not c['game'] and not c['unknown']:
            klass = 'library'
        else:
            klass = 'unknown' if not c['game'] else 'mixed'
        ev = []
        if kind == 'cie':
            fd = groups[ci]
            ev.append(f"cie{ci}:{cies[ci].aug or 'none'}:fde{sum(1 for x in fd if x.start is not None)}"
                      f"+dead{sum(1 for x in fd if x.start is None)}")
        nct = sum(1 for f in fs if f['addr'] in ctors)
        ndt = sum(1 for f in fs if f['addr'] in dtors)
        if nct:
            ev.append(f'ctors{nct}')
        if ndt:
            ev.append(f'dtors{ndt}')
        nr = sum(1 for f in fs if f['addr'] in m['methods'] and m['cls'][f['addr']][0] == 'game')
        if nr:
            ev.append(f'rtti{nr}')
        rows.append({'start': lo, 'end': hi, 'kind': kind, 'class': klass, 'funcs': len(fs),
                     'game': c['game'], 'library': c['library'], 'unknown': c['unknown'],
                     'evidence': ' '.join(ev), 'libs': ' '.join(libs)})
    for name in ('.init', '.fini', '.sceStub.text'):
        s = p.section(name)
        fs = [f for f in F if s.addr <= f['addr'] < s.end]
        rows.append({'start': s.addr, 'end': s.end, 'kind': 'section', 'class': 'library',
                     'funcs': len(fs), 'game': 0, 'library': len(fs), 'unknown': 0,
                     'evidence': 'crt-concatenation' if name != '.sceStub.text' else 'import-stubs',
                     'libs': ''})
    rows.sort(key=lambda r: r['start'])
    return rows


def fence_evidence(m, a):
    c, info = m['cls'][a]
    if c == 'library':
        return info['how']
    if c == 'game':
        return ' '.join(e.split(':')[0] for e in info)
    if info and 'conflict' in info:
        return 'conflict'
    return ''


def write(F, m, rows, libcsv=LIBCSV, tucsv=TUCSV, fencecsv=FENCECSV):
    with open(fencecsv, 'w', newline='') as fh:
        w = csv.writer(fh, lineterminator='\n')
        w.writerow(['addr', 'size', 'class', 'evidence'])
        for f in F:
            w.writerow([f"0x{f['addr']:06x}", f['size'], m['cls'][f['addr']][0],
                        fence_evidence(m, f['addr'])])
    with open(libcsv, 'w', newline='') as fh:
        w = csv.writer(fh, lineterminator='\n')
        w.writerow(['addr', 'size', 'how', 'object', 'section', 'symbol', 'tarballs'])
        for f in F:
            c, info = m['cls'][f['addr']]
            if c != 'library':
                continue
            ids = info['ids']
            w.writerow([f"0x{f['addr']:06x}", f['size'], info['how'],
                        ';'.join(f'{i[0]}({i[1]})' if i[1] else i[0] for i in ids),
                        ';'.join(sorted({i[2] for i in ids})), info['symbol'],
                        ';'.join(info['tarballs'])])
    with open(tucsv, 'w', newline='') as fh:
        w = csv.writer(fh, lineterminator='\n')
        w.writerow(['start', 'end', 'kind', 'class', 'funcs', 'game', 'library', 'unknown',
                    'evidence', 'libs'])
        for r in rows:
            w.writerow([f"0x{r['start']:06x}", f"0x{r['end']:06x}", r['kind'], r['class'],
                        r['funcs'], r['game'], r['library'], r['unknown'], r['evidence'], r['libs']])


def load_lib_type_names():
    """Every NUL-terminated string in reference library objects that looks
    like a mangled type name: a class whose typeinfo name is among these is
    not proven game."""
    import io
    import tarfile
    import hashlib
    from libarchive import REFS, TARBALLS, WANT, ar_members
    names = set()
    for tb, md5 in TARBALLS.items():
        raw = (REFS / f'{tb}.tar.gz').read_bytes()
        if hashlib.md5(raw).hexdigest() != md5:
            raise SystemExit(f'libfence: {tb} MD5 mismatch')
        with tarfile.open(fileobj=io.BytesIO(raw), mode='r:gz') as tf:
            for mi in tf.getmembers():
                base = mi.name.rsplit('/', 1)[-1]
                if not mi.isfile() or base not in WANT:
                    continue
                d = tf.extractfile(mi).read()
                for _n, md in (ar_members(d) if base.endswith('.a') else [('', d)]):
                    for s in re.findall(rb'[A-Za-z0-9_]{2,}', md):
                        names.add(s.decode())
    return names


def run():
    p = Prx.from_ref('us')
    F = funcmap.load()
    blobs = load_blobs()
    names = load_lib_type_names()
    m = build(p, F, blobs, names)
    rows = tu_rows(p, F, m)
    return p, F, blobs, names, m, rows


def report(p, F, m, rows):
    c = Counter(v[0] for v in m['cls'].values())
    b = Counter()
    for f in F:
        b[m['cls'][f['addr']][0]] += f['size']
    print('functions by class:', dict(c))
    print('bytes by class:    ', dict(b))
    hows = Counter(m['lib'][a]['how'] for a, v in m['cls'].items() if v[0] == 'library')
    print('library evidence:', dict(hows))
    print(f"crt proof: .init {m['crt']['.init']}, .fini {m['crt']['.fini']}")
    print(f"typeinfo objects {len(m['typeinfo'])}, non-library classes {len(m['classes'])}, "
          f"vtable methods {len(m['methods'])}")
    print(f"fingerprint patterns at >1 address (not counted): {m['ambiguous']['positions>1']}")
    print(f"unique patterns not at a function start (not counted): {m['ambiguous']['unanchored']}")
    print(f"library symbols not at a funcs.csv start: {len(m['sym_mismatch'])}")
    for a, s in m['sym_mismatch'][:10]:
        print(f'   {a:#x} {s}')
    print(f"conflicts (library .text fingerprint inside a game object): {len(m['conflicts'])}")
    for a, l, ev in m['conflicts'][:10]:
        print(f"   {a:#x} {l['ids']} {ev}")
    rc = Counter((r['kind'], r['class']) for r in rows)
    print('object rows:', dict(rc))
    lines, bad = cie_tests(p, m)
    print('one CIE = one object:', 'not refuted' if not bad else f'REFUTED by {bad}')
    for x in lines:
        print('  ' + x)


def selftest():
    p, F, blobs, names, m, rows = run()
    fails = []
    lines, bad = cie_tests(p, m)
    if bad:
        fails.append(f'CIE tests failed: {bad}')
    # Planted fault 0: merge two CIE groups' FDEs (as a CIE-merging linker
    # would); T4 or T3 must notice.
    gs = sorted(m['groups'])
    m0 = dict(m, ranges=[(m['ranges'][0][0], m['ranges'][-1][1], gs[0])])
    m0['group_of'] = lambda a: gs[0] if m0['ranges'][0][0] <= a < m0['ranges'][0][1] else None
    _l, bad0 = cie_tests(p, m0)
    print(f'planted: all groups merged into one -> failed tests {bad0}')
    if not bad0:
        fails.append('planted CIE merge not detected')
    if not (m['crt']['.init'] and m['crt']['.fini']):
        fails.append('crt concatenation not proven')
    n_lib = sum(1 for v in m['cls'].values() if v[0] == 'library')
    # Planted fault 1: make a library blob's pattern appear twice in retail by
    # duplicating a uniquely matched function's words over another function of
    # the same size; that fingerprint must stop counting.
    a0, n = next(v['blob'] for v in m['lib'].values() if v['how'] == 'fingerprint'
                 and v['blob'][1] >= 64 and not p.relocs_in(*v['blob'][:1], sum(v['blob'])))
    victim = next(f for f in F if f['addr'] < 0x100000 and f['size'] >= n
                  and not p.relocs_in(f['addr'], f['addr'] + n))
    data = bytearray(p.data)
    src = p._file_off(a0)
    dst = p._file_off(victim['addr'])
    data[dst:dst + n] = data[src:src + n]
    p2 = Prx(bytes(data))
    sig_before = sum(1 for s, (h, _) in m['sigs'].items() if len(h) == 1)
    sigs2 = fingerprint(p2, blobs)
    sig_after = sum(1 for s, (h, _) in sigs2.items() if len(h) == 1)
    print(f'planted duplicate of {a0:#x} at {victim["addr"]:#x}: unique patterns {sig_before} -> {sig_after}')
    if sig_after >= sig_before:
        fails.append('planted duplicate did not remove a unique match')
    # Planted fault 2: treat a game class name as a library type name; its
    # methods must stop being game.
    some = next(iter(m['classes'].values()))
    m2 = build(p, F, blobs, names | {some})
    g1 = sum(1 for v in m['cls'].values() if v[0] == 'game')
    g2 = sum(1 for v in m2['cls'].values() if v[0] == 'game')
    print(f'planted: class {some} declared library -> game functions {g1} -> {g2}')
    if g2 >= g1:
        fails.append('planted library class name did not reduce game')
    if n_lib == 0:
        fails.append('no library functions found')
    for f in fails:
        print('FAIL', f)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    p, F, blobs, names, m, rows = run()
    report(p, F, m, rows)
    if argv[1:] == ['--check']:
        a, b, c = (x.with_suffix('.check') for x in (LIBCSV, TUCSV, FENCECSV))
        write(F, m, rows, a, b, c)
        same = all(x.read_text() == y.read_text()
                   for x, y in ((a, LIBCSV), (b, TUCSV), (c, FENCECSV)))
        for x in (a, b, c):
            x.unlink()
        print('libfuncs.csv/tus.csv/fence.csv', 'match' if same else 'DIFFER from a fresh build')
        return 0 if same else 1
    write(F, m, rows)
    print('wrote config/us/libfuncs.csv, config/us/tus.csv, config/us/fence.csv')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
