#!/usr/bin/env python3
"""Compile one source file with a pinned psp-gcc and score every tagged function against retail.

  python3 tools/score.py src/x.c [--cc 1.3.1-nocmov] [--flags "-O2 -G0"] [-v]

Default compiler is the reconstructed 1.3.1-nocmov (tools/toolchains/mk_nocmov.py).
.cpp/.cc files go through cc1plus with -fexceptions added.
A file may add flags with a comment `/* @cflags: -fexceptions */` (per-TU flags differ in retail).

A function is tagged with a comment on the line(s) above it:
    /* @implements 0x01e000 us Name */   a claim: the bytes diff clean (the image gate places it)
    /* @draft 0x01e000 us Name */        a transcription still in progress (graded, never placed)
where Name is the C symbol (or a substring of the C++ mangled symbol).

Scoring (T4): words are compared with the relocated field masked on BOTH sides, the relocation
TYPE at each word must agree, and every relocation must resolve to the same thing as retail's
(see Resolver: addresses for f_/D_/tagged symbols, contents for literals, constants and jump
tables). EXACT = every word, type and reference agrees. BADREF = the bytes agree but some
reference does not (wrong global, wrong string, unresolvable symbol).
"""
import argparse
import csv
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

DEFAULT_CC = '1.3.1-nocmov'
TAG = re.compile(r'@(?:implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)')
CLAIM = re.compile(r'@implements\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)')


def compile_obj(src, cc, flags):
    rel = os.path.relpath(os.path.abspath(src), ROOT)
    out = os.path.join('build', 'score', f'{cc}', re.sub(r'[/.]', '_', rel))
    os.makedirs(os.path.join(ROOT, os.path.dirname(out)), exist_ok=True)
    tc = f'build/toolchains/psp-gcc-{cc}'
    is_cpp = src.endswith(('.cpp', '.cc'))
    asm = 'build/toolchains/psp-gcc-1.3.1/bin/psp-as'  # 1.7.1 ships no assembler
    extra = re.search(r'@cflags:([^*\n]*)', open(os.path.join(ROOT, rel)).read())
    if extra:
        flags += ' ' + extra.group(1).strip()  # per-file flags, like the original per-TU build
    if is_cpp and '-fexceptions' not in flags:
        flags += ' -fexceptions'  # retail C++ has .eh_frame/.gcc_except_table; EH edges change scheduling
    # Compile through the toolchain's own driver, as the original build did: it supplies
    # -march=allegrex -mtune=allegrex -mno-ulsw, the platform defines and the system include
    # paths that a bare cc1 call lacks. Stale outputs are removed inside the VM in the same
    # command (deleting them from the host first left the VM briefly unable to recreate them).
    driver = f'{tc}/bin/psp-g++' if is_cpp else f'{tc}/bin/psp-gcc'
    if not os.path.exists(os.path.join(ROOT, driver)):  # the 1.7.1 tarball keeps it in psp/bin
        driver = f'{tc}/psp/bin/c++' if is_cpp else f'{tc}/psp/bin/gcc'
    # Several sessions may compile the same file at once: each writes its own temporaries and
    # renames them into place (atomic), so no reader ever sees another run's half-written object.
    tmp = f'{out}.{os.getpid()}'
    cmd = (f'cd {ROOT} && rm -f {tmp}.s {tmp}.o && {driver} -S -Iinclude {flags} {rel} -o {tmp}.s && '
           f'{asm} -G0 {tmp}.s -o {tmp}.o && mv -f {tmp}.s {out}.s && mv -f {tmp}.o {out}.o')
    p = subprocess.run([os.path.join(ROOT, 'tools/toolchains/lima.sh'), 'sh', '-c', cmd],
                       capture_output=True, text=True, errors='replace')  # the VM's stderr is not always UTF-8
    if p.returncode != 0:
        subprocess.run([os.path.join(ROOT, 'tools/toolchains/lima.sh'), 'sh', '-c', f'cd {ROOT} && rm -f {tmp}.s {tmp}.o'])
        sys.stderr.write(p.stdout + p.stderr)
        raise SystemExit('compile failed')
    return os.path.join(ROOT, out + '.o')


def tags(src, claims_only=False):
    """(addr, name) for every @implements and @draft tag; claims_only=True: @implements only."""
    return [(int(a, 16), n) for a, n in (CLAIM if claims_only else TAG).findall(open(src).read())]


def locate(obj, syms, tg):
    """Find each tagged function in the compiled object, in whichever executable section holds
    it: .text, or a .gnu.linkonce.t.* section (inline methods emitted out of line, compiler
    generated constructors and destructors). Returns (placed, name_to_addr, found) where placed
    is [(sec, cstart, size, retail_addr)] and found maps retail_addr -> symbol."""
    execs = {i for i, sh in enumerate(obj.sh) if sh[1] == 1 and sh[2] & 4}
    fsyms = sorted([x for x in syms if x['shndx'] in execs and x['type'] == 2], key=lambda x: (x['shndx'], x['value']))
    n2a = {n: a for a, n in tg}
    placed, found = [], {}
    for addr, name in tg:
        cand = [x for x in fsyms if x['name'] == name] or [x for x in fsyms if name in x['name']]
        if not cand:
            continue
        x = cand[0]
        if not x['size']:
            later = [y['value'] for y in fsyms if y['shndx'] == x['shndx'] and y['value'] > x['value']]
            x = dict(x, size=(min(later) if later else len(obj.data(x['shndx']))) - x['value'])
        placed.append((x['shndx'], x['value'], x['size'], addr))
        found[addr] = x
        n2a.setdefault(x['name'], addr)
    return placed, n2a, found


DATA_SECTIONS = ('.rodata', '.data', '.bss', '.sdata', '.sbss', '.gnu.linkonce.r', '.gnu.linkonce.d', '.gnu.linkonce.b')

NAMED = re.compile(r'(?<![A-Za-z_])[fD]_([0-9a-f]{6})(?![0-9a-f])')  # also inside a C++ mangled name
MANGLED = re.compile(r'(?<![0-9])8[fD]_([0-9a-f]{6})')  # <length 8><identifier> in a mangled name


def named_addr(name):
    """The address in an f_XXXXXX / D_XXXXXX name, plain or inside a C++ mangled name, else None.
    In `_Z8f_118a54ff` the parameter codes `ff` follow the address directly; there the mangled
    length prefix (8) is what delimits the identifier."""
    m = NAMED.search(name) or MANGLED.search(name)
    return int(m.group(1), 16) if m else None


def _libsyms():
    """Names with known retail addresses: proven names, the C++ vtables, typeinfo and type names
    (config/us/rtti.csv), identified library functions and imported system calls."""
    out = {}
    for fn, key, col in (('symbols.csv', 'name', 'addr'), ('rtti.csv', 'name', 'addr'), ('libfuncs.csv', 'symbol', 'addr'),
                         ('imports.csv', 'name', 'stub')):
        path = os.path.join(ROOT, 'config/us', fn)
        if os.path.exists(path):
            for r in csv.DictReader(open(path)):
                if r[key]:
                    out.setdefault(r[key], int(r[col], 16))
    return out


LIBSYMS = _libsyms()


class Resolver:
    """Resolve each relocated word of the candidate object to what it refers to, and check it
    against the retail relocation at the same word (T4: every relocation resolves the same).

    Object-side targets:
      f_XXXXXX / D_XXXXXX symbols (defined or not), or a tagged name  -> retail address + addend
      a library symbol (config/us/libfuncs.csv) or an imported system
      call (config/us/imports.csv, by its PPSSPP name)                 -> its retail address
      a label/function inside a tagged function of this object         -> mapped retail address
      a C++ vtable/typeinfo/type name (config/us/rtti.csv)              -> its retail address
      a local data section (.rodata*, .data, .bss, .gnu.linkonce.r/d/b) -> CONTENT: the bytes
          the candidate refers to must equal the retail bytes at the retail target; words of
          that data carrying R_32 relocations (jump tables) must resolve the same, recursively.
      anything else                                                     -> UNRESOLVED (fails)
    """

    def __init__(self, obj, syms, name_to_addr, placed, retail_rel, e):
        self.obj, self.syms, self.n2a, self.placed, self.rrel, self.e = obj, syms, name_to_addr, placed, retail_rel, e
        self.rels = {}
        for i in range(len(obj.sh)):
            r = obj.object_rels(i)
            if r:
                self.rels[i] = r

    def addend(self, sec, off, rtype):
        """Implicit addend of the REL entry at sec+off (HI16/LO16 combined as AHL)."""
        w = struct.unpack_from('<I', self.obj.data(sec), off)[0]
        if rtype == 2:
            return w
        if rtype == R_26:
            return (w & 0x03ffffff) << 2
        rl = self.rels[sec]
        k = next(j for j, r in enumerate(rl) if r[0] == off)
        sym = rl[k][2]
        lo16 = lambda x: struct.unpack('<h', struct.pack('<H', x & 0xffff))[0]  # noqa: E731
        if rtype == 5:  # HI16: pair with the next LO16 on the same symbol
            lo = next((r for r in rl[k + 1:] if r[1] == 6 and r[2] == sym), None)
            low = lo16(struct.unpack_from('<I', self.obj.data(sec), lo[0])[0]) if lo else 0
            return ((w & 0xffff) << 16) + low
        if rtype == 6:  # LO16: take the upper half from the preceding HI16 on the same symbol
            hi = next((r for r in reversed(rl[:k]) if r[1] == 5 and r[2] == sym), None)
            high = (struct.unpack_from('<I', self.obj.data(sec), hi[0])[0] & 0xffff) << 16 if hi else 0
            return high + lo16(w)
        return 0

    def target(self, sec, off, rtype, symidx):
        """('addr', a) | ('data', secidx, offset) | ('unresolved', why)."""
        s = self.syms[symidx]
        add = self.addend(sec, off, rtype)
        m = named_addr(s['name'])
        if s['name'] in LIBSYMS:
            return ('addr', LIBSYMS[s['name']] + add)
        if s['name'] in self.n2a:
            return ('addr', self.n2a[s['name']] + add)
        if m is not None:
            return ('addr', m + add)
        if s['shndx'] and s['shndx'] < len(self.obj.sh):
            nm = self.obj.names[s['shndx']]
            val = s['value'] + add
            if self.obj.sh[s['shndx']][2] & 4:  # executable: .text or .gnu.linkonce.t.*
                for psec, cstart, csize, raddr in self.placed:
                    if psec == s["shndx"] and cstart <= val < cstart + csize:
                        return ('addr', raddr + val - cstart)
                return ('unresolved', f'{nm}+0x{val:x} is outside every tagged function')
            if nm.startswith(DATA_SECTIONS):
                return ('data', s['shndx'], val)
        return ('unresolved', f'symbol {s["name"] or "?"}')

    def match(self, tgt, rr):
        """(None, retail target) if the candidate reference agrees with retail relocation rr
        (a LO16 may agree through any of its alternative HI16s), else (reason, None)."""
        if rr is None:
            return ('relocation where retail has none', None)
        why = self.check(tgt, rr['target'])
        if why is None:
            return (None, rr['target'])
        for alt in rr.get('alts', [])[1:]:
            if self.check(tgt, alt) is None:
                return (None, alt)
        return (why, None)

    def check(self, tgt, retail_target, depth=0):
        """None if the candidate reference matches the retail one, else a reason string."""
        kind = tgt[0]
        if kind == 'unresolved':
            return tgt[1]
        if retail_target is None:
            return 'retail target unknown (unpaired LO16)'
        if kind == 'addr':
            return None if tgt[1] == retail_target else f'refers to 0x{tgt[1]:x}, retail 0x{retail_target:x}'
        _, sec, val = tgt
        nm = self.obj.names[sec]
        sh = self.obj.sh[sec]
        if sh[1] == 8:  # NOBITS: compare only that both are bss
            bi = self.e.index('.bss')
            ok = self.e.addr(bi) <= retail_target < self.e.addr(bi) + self.e.sh[bi][5]
            return None if ok else 'candidate .bss, retail not .bss'
        data = self.obj.data(sec)
        if 'str' in nm:
            n = data.index(b'\0', val) + 1 - val
        elif 'cst' in nm:
            n = int(re.search(r'cst(\d+)', nm).group(1))
        else:
            n = min(len(data) - val, 64)
        relmap = {r[0]: r for r in self.rels.get(sec, [])}
        for k in range(0, n, 4 if n % 4 == 0 and val % 4 == 0 else 1):
            if (val + k) in relmap and depth < 2:
                _, rt, si = relmap[val + k]
                rr = self.rrel.get(retail_target + k)
                why = self.check(self.target(sec, val + k, rt, si), rr['target'] if rr else None, depth + 1)
                if why:
                    return f'data word +{k}: {why}'
            elif k % 4 == 0 and n - k >= 4 and n % 4 == 0 and val % 4 == 0:
                cw = data[val + k:val + k + 4]
                try:
                    rw = struct.pack('<I', self.e.word(retail_target + k))
                except KeyError:
                    return f'retail 0x{retail_target + k:x} is not loaded data'
                if cw != rw:
                    return f'data at +{k} differs ({cw.hex()} vs {rw.hex()})'
            else:
                cb = data[val + k]
                rb = struct.pack('<I', self.e.word((retail_target + k) & ~3))[(retail_target + k) & 3]
                if cb != rb:
                    return f'data byte +{k} differs'
        return None


def score(src, cc, flags, verbose):
    obj = Elf(open(compile_obj(src, cc, flags), 'rb').read())
    syms = obj.symbols()
    tg = tags(src)
    c = rdis.load()
    e = c['e']
    placed, name_to_addr, found = locate(obj, syms, tg)
    res = Resolver(obj, syms, name_to_addr, placed, c['rel'], e)
    results = []
    for addr, name in tg:
        if addr not in found:
            results.append((addr, name, 'MISSING', '')); continue
        s = found[addr]
        size = s['size']
        text = s['shndx']
        tdata = obj.data(text)
        orel = {o: (t, si) for o, t, si in obj.object_rels(text)}
        start, osize = rdis.func_at(addr)
        if start != addr:
            results.append((addr, name, 'BADADDR', f'0x{addr:x} is inside f_{start:06x}')); continue
        n = max(size, osize) // 4
        first, diffs, refbad = None, 0, []
        for i in range(n):
            pa, pc = addr + 4 * i, s['value'] + 4 * i
            ow = e.word(pa) if i < osize // 4 else None
            cw = struct.unpack_from('<I', tdata, pc)[0] if i < size // 4 else None
            orr = c['rel'].get(pa)
            ot = orr['type'] if orr else 0
            ct, csym = orel.get(pc, (0, None))
            ok = ow is not None and cw is not None and ot == ct and relmask(ow, ot) == relmask(cw, ct)
            if ok and ct and csym is not None:
                why = res.match(res.target(text, pc, ct, csym), orr)[0]
                if why:
                    ok = False
                    refbad.append(f'+0x{4 * i:x}: {why}')
            if not ok:
                diffs += 1
                if first is None:
                    first = i
        if diffs == 0:
            results.append((addr, name, 'EXACT', f'{osize}B'))
        elif refbad and diffs == len(refbad):
            results.append((addr, name, 'BADREF', f'bytes match but {len(refbad)} reference(s) differ: ' + '; '.join(refbad[:3])))
        else:
            results.append((addr, name, 'DIFF', f'{diffs}/{n} words differ, first at +0x{4 * first:x}; size {size} vs {osize}'
                            + (f'; bad refs: ' + '; '.join(refbad[:2]) if refbad else '')))
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
    ap.add_argument('--cc', default=DEFAULT_CC)
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
