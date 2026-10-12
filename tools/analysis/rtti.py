#!/usr/bin/env python3
"""C++ run-time type information in the retail module -> config/us/rtti.csv (addr,name).

Every polymorphic class leaves three objects that the compiler names, and the scorer needs
their retail addresses to resolve references from code (vtable stores in constructors,
typeinfo in exception tables):
  _ZTS<T>  the type's mangled name, a string in .rodata;
  _ZTI<T>  its typeinfo: {vptr of a __cxxabiv1 typeinfo class + 8, pointer to _ZTS<T>, ...};
  _ZTV<T>  its vtable: {0 (offset to top), pointer to _ZTI<T>, virtual functions...}.
They are found by that structure alone (relocated words), not by guessing. The three
__cxxabiv1 typeinfo vtables are named by the shape of the typeinfo objects that use them:
a pointer to another typeinfo at +8 is single inheritance (__si_), an integer pair is
__vmi_, neither is a class without bases. Only typeinfo objects whose vptr at least five
others share are kept (a lone {pointer, name-like string} pair is not typeinfo). A vtable that is not unique (construction vtables,
or a pointer table that also starts 0, &_ZTI) is left out.

    python3 tools/analysis/rtti.py
"""
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prx import Elf, R_32  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TYPENAME = re.compile(rb'^(?:N|[0-9]|S|P|K|St)[A-Za-z0-9_]*$')


def cstring(e, a):
    s = b''
    while len(s) < 256:
        w = e.word(a & ~3)
        b = (w >> (8 * (a & 3))) & 0xff
        if b == 0:
            return s
        s += bytes([b])
        a += 1
    return None


def main():
    e = Elf(open(os.path.join(ROOT, 'orig/us/BOOT.BIN'), 'rb').read())
    r32 = {r['at']: r['target'] for r in e.prx_rels() if r['type'] == R_32 and r['target'] is not None}
    ti = e.index('.text')
    tlo, thi = e.addr(ti), e.addr(ti) + len(e.data(ti))
    zti = {}
    for at, t in r32.items():
        if tlo <= t < thi or (at - 4) not in r32:
            continue
        try:
            s = cstring(e, t)
        except KeyError:
            continue
        if s and TYPENAME.match(s) and not tlo <= r32[at - 4] < thi:
            zti[at - 4] = (s.decode(), t)
    # the real typeinfo vptrs are shared by many objects; a pointer pair that only looks like
    # {vptr, name} uses a "vptr" nothing else uses
    use = collections.Counter(r32[a] for a in zti)
    zti = {a: v for a, v in zti.items() if use[r32[a]] >= 5}
    out = {}
    kinds = collections.defaultdict(collections.Counter)
    for a, (name, s) in zti.items():
        out[s] = '_ZTS' + name
        out[a] = '_ZTI' + name
        nxt = r32.get(a + 8)
        kinds[r32[a]]['si' if nxt in zti else ('vmi' if (a + 8) not in r32 and (a + 12) not in r32 and
                                                 0 < e.word(a + 12) < 64 and (a + 16) in r32 and r32[a + 16] in zti
                                                 else 'class')] += 1
    vt = collections.defaultdict(list)
    for at, t in r32.items():
        if t in zti and (at - 4) not in r32 and e.word(at - 4) == 0 and at - 4 not in zti:
            vt[t].append(at - 4)
    for t, vs in vt.items():
        if len(vs) == 1:
            out[vs[0]] = '_ZTV' + zti[t][0]
    abi = {'class': '_ZTVN10__cxxabiv117__class_type_infoE', 'si': '_ZTVN10__cxxabiv120__si_class_type_infoE',
           'vmi': '_ZTVN10__cxxabiv121__vmi_class_type_infoE'}
    for vptr, c in kinds.items():
        out[vptr - 8] = abi[c.most_common(1)[0][0]]
    dst = os.path.join(ROOT, 'config/us/rtti.csv')
    with open(dst, 'w') as f:
        f.write('addr,name\n')
        for a in sorted(out):
            f.write(f'0x{a:06x},{out[a]}\n')
    print(f'{len(zti)} typeinfo objects, {sum(1 for v in out.values() if v.startswith("_ZTV") and "cxxabiv1" not in v)} vtables, '
          f'{len(kinds)} typeinfo classes {dict((hex(k - 8), dict(v)) for k, v in kinds.items())} -> {os.path.relpath(dst, ROOT)}')


if __name__ == '__main__':
    main()
