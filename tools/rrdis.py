#!/usr/bin/env python3
"""Annotated listing of one retail function.

  python3 tools/rrdis.py 0x1e000            # by address (any address inside the function)
Needs build/asm/us.objdump (psp-objdump -d of orig/us/BOOT.BIN) and config/us/funcs.csv.
Relocated operands are annotated with their resolved target: f_<addr> (function),
D_<addr> (data, with section) and a string preview for .rodata strings.
"""
import bisect
import csv
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'analysis'))
from prx import Elf  # noqa: E402

_cache = {}


def load():
    if _cache:
        return _cache
    e = Elf(open(os.path.join(ROOT, 'orig/us/BOOT.BIN'), 'rb').read())
    rel = {r['at']: r for r in e.prx_rels()}
    funcs = [(int(r['addr'], 16), int(r['size'])) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))]
    lines = {}
    pat = re.compile(r'^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$')
    for ln in open(os.path.join(ROOT, 'build/asm/us.objdump')):
        m = pat.match(ln)
        if m:
            lines[int(m.group(1), 16)] = (int(m.group(2), 16), m.group(3).replace('\t', ' '))
    _cache.update(e=e, rel=rel, funcs=funcs, starts=[a for a, _ in funcs], lines=lines)
    return _cache


def section_of(e, a):
    for i, s in enumerate(e.sh):
        if s[2] & 2 and s[3] <= a < s[3] + max(s[5], 1) and e.names[i]:
            return e.names[i]
    return '?'


def describe(a):
    c = load()
    e, starts = c['e'], c['starts']
    k = bisect.bisect_right(starts, a) - 1
    if k >= 0 and starts[k] == a:
        return f'f_{a:06x}'
    sec = section_of(e, a)
    s = f'D_{a:06x}[{sec}]'
    if sec == '.rodata':
        try:
            i = e.index('.rodata')
            off = a - e.addr(i)
            raw = e.data(i)[off:off + 48]
            txt = raw.split(b'\0')[0]
            if len(txt) >= 2 and all(32 <= ch < 127 for ch in txt):
                s += ' "' + txt.decode() + '"'
        except ValueError:
            pass
    return s


def func_at(a):
    c = load()
    k = bisect.bisect_right(c['starts'], a) - 1
    if k < 0 or not c['funcs'][k][0] <= a < sum(c['funcs'][k]):
        raise SystemExit(f'0x{a:x} is not inside any mapped function')
    return c['funcs'][k]


def listing(a):
    c = load()
    start, size = func_at(a)
    out = [f'# f_{start:06x}  size {size}']
    for p in range(start, start + size, 4):
        w, txt = c['lines'].get(p, (0, '?'))
        note = ''
        r = c['rel'].get(p)
        if r and r['target'] is not None:
            note = '  ; ' + {2: 'R32', 4: 'R26', 5: 'HI', 6: 'LO'}[r['type']] + ' ' + describe(r['target'])
        out.append(f'{p:06x}: {w:08x}  {txt}{note}')
    return '\n'.join(out)


if __name__ == '__main__':
    for arg in sys.argv[1:]:
        print(listing(int(arg, 16)))
