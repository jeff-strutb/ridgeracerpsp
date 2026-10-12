"""Translation-unit map of the retail module -> config/us/tus.csv.

Evidence (measured 2026-10-12, see docs/decomp/TU-MAP.md):
  * .eh_frame holds one CIE per C++ object compiled with exceptions, followed by that object's
    FDEs. The 262 CIE groups never overlap and are in strictly increasing address order, so
    each group's [min pc, max pc+range) is one object's .text ("eh" rows).
  * Code between groups belongs to objects without EH tables (C, asm, SCE/newlib/libgcc
    library members): "gap" rows, to be split further by data-reference order.
  * .comment has one ident per linked object, in link order (493 in all).
Each row also records the span of .data/.bss its code references; objects lay out their
data in the same order as their text, so those spans must be increasing too (checked).
Classification (column `class`), from config/us/libfuncs.csv (tools/analysis/libid.py):
  lib:<name>  >= 30% of the row's bytes (and >= 64 B) are library functions identified by
              exact fingerprint; or, iterated to a fixed point, a row with any evidence for
              <name> next to a lib:<name> row, or a row with no evidence between two lib:<name> rows.
  unknown     unidentified rows after the first library row: the linker places libraries
              after the game objects, so these are probably library code not yet fingerprinted
              (e.g. 0x163544/0x163a94 are libgcc __udivdi3/__umoddi3 built by 1.5.1).
  game        unidentified rows before the first library row.
libc and libm together are reported as lib:newlib.
Exact fingerprints under-count: retail's libraries were built by the 1.5.1 compiler (no
conditional moves), so many library functions differ slightly from the shipped 1.3.1/1.7.1 ones.
Usage: python3 tools/analysis/tumap.py
"""
import bisect
import csv
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prx import Elf  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def eh_groups(e):
    i = e.index('.eh_frame')
    b = e.data(i)
    groups, o = [], 0
    while o < len(b):
        length, = struct.unpack_from('<I', b, o)
        if length == 0:
            break
        cid, = struct.unpack_from('<I', b, o + 4)
        if cid == 0:
            groups.append([])
        else:
            pc, rng = struct.unpack_from('<II', b, o + 8)
            if pc:
                groups[-1].append((pc, rng))
        o += 4 + length
    return groups


def build(path):
    e = Elf(open(path, 'rb').read())
    ti = e.index('.text')
    lo, hi = e.addr(ti), e.addr(ti) + len(e.data(ti))
    spans = []
    for g in eh_groups(e):
        spans.append((min(a for a, _ in g), max(a + r for a, r in g), len(g)))
    assert all(spans[k][1] <= spans[k + 1][0] for k in range(len(spans) - 1)), 'EH groups overlap or are out of order'
    rows, cur = [], lo
    for a, b, n in spans:
        if a > cur:
            rows.append(['gap', cur, a, 0])
        rows.append(['eh', a, b, n])
        cur = b
    if cur < hi:
        rows.append(['gap', cur, hi, 0])
    funcs = sorted(int(r['addr'], 16) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv'))))
    starts = [r[1] for r in rows]
    # data references per row (.data and .bss only: .rodata may hold merged constants)
    di, bi = e.index('.data'), e.index('.bss')
    dlo, dhi = e.addr(di), e.addr(bi) + e.sh[bi][5]
    refs = [[] for _ in rows]
    for r in e.prx_rels():
        if r['type'] in (5, 6) and r['target'] is not None and lo <= r['at'] < hi and dlo <= r['target'] < dhi:
            refs[bisect.bisect_right(starts, r['at']) - 1].append(r['target'])
    out = []
    for k, (kind, a, b, n) in enumerate(rows):
        nf = bisect.bisect_left(funcs, b) - bisect.bisect_left(funcs, a)
        d = refs[k]
        out.append(dict(tu=k, kind=kind, start=a, end=b, fdes=n, funcs=nf,
                        data_lo=min(d) if d else None, data_hi=max(d) if d else None, data_refs=len(d)))
    return out


def classify(rows):
    path = os.path.join(ROOT, 'config/us/libfuncs.csv')
    starts = [r['start'] for r in rows]
    ev = [{} for _ in rows]
    if os.path.exists(path):
        for x in csv.DictReader(open(path)):
            k = bisect.bisect_right(starts, int(x['addr'], 16)) - 1
            lib = x['library'].replace('.a', '').replace('.o', '')
            ev[k][lib] = ev[k].get(lib, 0) + int(x['size'])
    cls = [None] * len(rows)
    for k, r in enumerate(rows):
        if ev[k]:
            lib, b = max(ev[k].items(), key=lambda kv: kv[1])
            if b >= 64 and sum(ev[k].values()) >= 0.3 * (r['end'] - r['start']):
                if set(ev[k]) <= {'libc', 'libm'}:
                    lib, b = 'newlib', sum(ev[k].values())
                cls[k] = 'lib:' + (lib if b >= 0.7 * sum(ev[k].values()) else 'mixed')
    changed = True
    while changed:
        changed = False
        for k in range(len(rows)):
            if cls[k]:
                continue
            nb = [cls[j] for j in (k - 1, k + 1) if 0 <= j < len(rows) and cls[j] and cls[j] != 'lib:mixed']
            if ev[k] and any(c[4:] in ev[k] for c in nb):
                cls[k] = next(c for c in nb if c[4:] in ev[k]); changed = True
            elif not ev[k] and len(nb) == 2 and nb[0] == nb[1]:
                cls[k] = nb[0]; changed = True
    first_lib = next(k for k, c in enumerate(cls) if c)
    for k, r in enumerate(rows):
        r['class'] = cls[k] or ('game' if k < first_lib else 'unknown')
        r['lib_bytes'] = sum(ev[k].values())


def main():
    rows = build(os.path.join(ROOT, 'orig/us/BOOT.BIN'))
    classify(rows)
    dst = os.path.join(ROOT, 'config/us/tus.csv')
    with open(dst, 'w') as f:
        f.write('tu,kind,class,start,end,bytes,funcs,fdes,lib_bytes,data_lo,data_hi,data_refs\n')
        for r in rows:
            h = lambda v: '' if v is None else f'0x{v:06x}'  # noqa: E731
            f.write(f"{r['tu']},{r['kind']},{r['class']},0x{r['start']:06x},0x{r['end']:06x},{r['end'] - r['start']},"
                    f"{r['funcs']},{r['fdes']},{r['lib_bytes']},{h(r['data_lo'])},{h(r['data_hi'])},{r['data_refs']}\n")
    eh = [r for r in rows if r['kind'] == 'eh']
    gap = [r for r in rows if r['kind'] == 'gap']
    print(f"{len(eh)} EH objects ({sum(r['end'] - r['start'] for r in eh)} B, {sum(r['funcs'] for r in eh)} fns), "
          f"{len(gap)} gaps ({sum(r['end'] - r['start'] for r in gap)} B, {sum(r['funcs'] for r in gap)} fns) -> {dst}")
    by = {}
    for r in rows:
        n, b, f = by.get(r['class'], (0, 0, 0))
        by[r['class']] = (n + 1, b + r['end'] - r['start'], f + r['funcs'])
    for c, (n, b, f) in sorted(by.items(), key=lambda kv: -kv[1][1]):
        print(f'  {c:14s} {n:4d} rows {b:9d} B {f:6d} fns')
    # data-order check: for consecutive EH objects that both touch .data/.bss, is the data in the same order?
    withd = [r for r in eh if r['data_refs']]
    inorder = sum(1 for x, y in zip(withd, withd[1:]) if x['data_lo'] <= y['data_lo'])
    print(f'data order agrees with text order for {inorder}/{len(withd) - 1} consecutive EH objects with data refs')


if __name__ == '__main__':
    main()
