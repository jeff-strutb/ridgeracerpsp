#!/usr/bin/env python3
"""Compile one source file with a pinned psp-gcc and score every tagged function against retail.

  python3 tools/score.py src/x.c [--cc 1.3.1-nocmov] [--flags "-O2 -G0"] [-v]

Default compiler is the reconstructed 1.3.1-nocmov (tools/toolchains/mk_nocmov.py).
.cpp/.cc files go through cc1plus with -fexceptions added.
A file may add flags with a comment `/* @cflags: -fexceptions */` (per-TU flags differ in retail).

A function is tagged with a comment on the line(s) above it:
    /* @implements 0x01e000 us Name */
where Name is the C symbol (or a substring of the C++ mangled symbol).

Scoring: words are compared with the relocated field masked on BOTH sides, and the relocation
TYPE at each word must agree. Call targets are compared when the callee is itself tagged
or named f_<addr>. A function is EXACT only if every word, type and known target agrees.
"""
import argparse
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'analysis'))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from prx import Elf, relmask, R_26  # noqa: E402
import rrdis as rdis  # noqa: E402

TAG = re.compile(r'@implements\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)')


def compile_obj(src, cc, flags):
    rel = os.path.relpath(os.path.abspath(src), ROOT)
    out = os.path.join('build', 'score', f'{cc}', re.sub(r'[/.]', '_', rel))
    os.makedirs(os.path.join(ROOT, os.path.dirname(out)), exist_ok=True)
    for ext in ('.s', '.o'):
        try:
            os.remove(os.path.join(ROOT, out + ext))
        except FileNotFoundError:
            pass
    tc = f'build/toolchains/psp-gcc-{cc}'
    cc1 = 'cc1plus' if src.endswith(('.cpp', '.cc')) else 'cc1'
    asm = 'build/toolchains/psp-gcc-1.3.1/bin/psp-as'  # 1.7.1 ships no assembler
    inc = f'-Iinclude -I{tc}/lib/gcc-lib/psp/*/include'
    extra = re.search(r'@cflags:([^*\n]*)', open(os.path.join(ROOT, rel)).read())
    if extra:
        flags += ' ' + extra.group(1).strip()  # per-file flags, like the original per-TU build
    if cc1 == 'cc1plus' and '-fexceptions' not in flags:
        flags += ' -fexceptions'  # retail C++ has .eh_frame/.gcc_except_table; EH edges change scheduling
    cmd = (f'cd {ROOT} && {tc}/lib/gcc-lib/psp/*/{cc1} -quiet {inc} {flags} {rel} -o {out}.s && '
           f'{asm} -G0 {out}.s -o {out}.o')
    p = subprocess.run([os.path.join(ROOT, 'tools/toolchains/lima.sh'), 'sh', '-c', cmd],
                       capture_output=True, text=True)
    if p.returncode != 0:
        sys.stderr.write(p.stdout + p.stderr)
        raise SystemExit('compile failed')
    return os.path.join(ROOT, out + '.o')


def tags(src):
    return [(int(a, 16), n) for a, n in TAG.findall(open(src).read())]


def score(src, cc, flags, verbose):
    obj = Elf(open(compile_obj(src, cc, flags), 'rb').read())
    syms = obj.symbols()
    tg = tags(src)
    name_to_addr = {n: a for a, n in tg}
    text = obj.index('.text')
    tdata = obj.data(text)
    orel = {o: (t, s) for o, t, s in obj.object_rels(text)}
    fsyms = sorted([s for s in syms if s['shndx'] == text and s['type'] == 2], key=lambda s: s['value'])
    c = rdis.load()
    e = c['e']
    results = []
    for addr, name in tg:
        cand = [s for s in fsyms if s['name'] == name] or [s for s in fsyms if name in s['name']]
        if not cand:
            results.append((addr, name, 'MISSING', '')); continue
        s = cand[0]
        k = fsyms.index(s)
        size = s['size'] or ((fsyms[k + 1]['value'] if k + 1 < len(fsyms) else len(tdata)) - s['value'])
        start, osize = rdis.func_at(addr)
        if start != addr:
            results.append((addr, name, 'BADADDR', f'0x{addr:x} is inside f_{start:06x}')); continue
        n = max(size, osize) // 4
        first, diffs = None, 0
        for i in range(n):
            pa, pc = addr + 4 * i, s['value'] + 4 * i
            ow = e.word(pa) if i < osize // 4 else None
            cw = struct.unpack_from('<I', tdata, pc)[0] if i < size // 4 else None
            orr = c['rel'].get(pa)
            ot = orr['type'] if orr else 0
            ct, csym = orel.get(pc, (0, None))
            ok = ow is not None and cw is not None and ot == ct and relmask(ow, ot) == relmask(cw, ct)
            if ok and ot == R_26 and csym is not None:
                callee = syms[csym]['name']
                want = name_to_addr.get(callee)
                if want is None and re.fullmatch(r'f_[0-9a-f]{6}', callee):
                    want = int(callee[2:], 16)
                if want is not None and orr['target'] != want:
                    ok = False
            if not ok:
                diffs += 1
                if first is None:
                    first = i
        if diffs == 0:
            results.append((addr, name, 'EXACT', f'{osize}B'))
        else:
            results.append((addr, name, 'DIFF', f'{diffs}/{n} words differ, first at +0x{4 * first:x}; size {size} vs {osize}'))
        if verbose and diffs:
            for i in range(n):
                pa, pc = addr + 4 * i, s['value'] + 4 * i
                ow = e.word(pa) if i < osize // 4 else None
                cw = struct.unpack_from('<I', tdata, pc)[0] if i < size // 4 else None
                otxt = c['lines'].get(pa, (0, ''))[1] if ow is not None else ''
                print(f'  +{4 * i:04x}  {ow if ow is None else format(ow, "08x")}  {cw if cw is None else format(cw, "08x")}  {otxt}')
    return results


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('src', nargs='+')
    ap.add_argument('--cc', default='1.3.1-nocmov')
    ap.add_argument('--flags', default='-O2 -G0')
    ap.add_argument('-v', action='store_true')
    a = ap.parse_args()
    exact = total = 0
    for src in a.src:
        for addr, name, st, msg in score(src, a.cc, a.flags, a.v):
            total += 1
            exact += st == 'EXACT'
            print(f'{st:7s} 0x{addr:06x} {name:28s} {msg}')
    print(f'{exact}/{total} exact  (cc {a.cc}, flags "{a.flags}")')


if __name__ == '__main__':
    main()
