#!/usr/bin/env python3
"""Annotated listing of one retail function from the USA BOOT.BIN.

    tools/rrdis.py 0xADDR          function starting at ADDR (funcs.csv)
    tools/rrdis.py --selftest      list every function; prove annotations hold

Each line: address, raw word, instruction (decoded with the toolchain's own
opcode table, tools/analysis/allegrex.py), and for a relocated word the
relocation: type and resolved target, with the target named as a function
(func_XXXXXX, plus the library symbol when libfuncs.csv knows it) or as
section+offset.  LO16 targets come from the relocation pair, else from the
data-flow recovery (hilo.py, marked 'df'), else are marked 'lo=...' only.
Branch targets inside the function are labelled; a jr through a jump table
lists its table.  VFPU immediates that the decoder prints raw are shown as
?x=value.
"""
import csv
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE / 'analysis')]
from prx import Prx          # noqa: E402
from allegrex import decode  # noqa: E402
import funcmap               # noqa: E402

ROOT = HERE.parent


def load_names():
    names = {}
    path = ROOT / 'config' / 'us' / 'libfuncs.csv'
    with open(path) as fh:
        for row in csv.DictReader(fh):
            a = int(row['addr'], 16)
            sym = row['symbol'].split(';')[0] if row['symbol'] else ''
            names[a] = sym or row['object']
    classes = {}
    with open(ROOT / 'config' / 'us' / 'fence.csv') as fh:
        for row in csv.DictReader(fh):
            classes[int(row['addr'], 16)] = (row['class'], row['evidence'])
    return names, classes


class Lister:
    def __init__(self, p=None, funcs=None):
        self.p = p or Prx.from_ref('us')
        self.funcs = funcs or funcmap.load()
        self.byaddr = {f['addr']: f for f in self.funcs}
        self.names, self.classes = load_names()
        self.tables = {t['jr']: t for t in funcmap.jump_tables(self.p, self.p.section('.text'))}
        self._df = None

    def df(self):
        if self._df is None:
            from hilo import recover
            self._df = recover(self.p, self.funcs)
        return self._df

    def name(self, t):
        if t in self.byaddr:
            n = self.names.get(t)
            return f'func_{t:06x}' + (f' <{n}>' if n else '')
        s = self.p.section_at(t)
        if s is None:
            return f'{t:#x} (outside image)'
        return f'{s.name}+{t - s.addr:#x}'

    def annotate(self, r, df):
        if r.type_id == 4:
            return f'R_MIPS_26 -> {self.name(r.target)}'
        if r.type_id in (5, 6):
            kind = '%hi' if r.type_id == 5 else '%lo'
            if r.target is not None:
                return f'{kind}({self.name(r.target)}) = {r.target:#x}'
            if r.addr in df:
                t, lui = df[r.addr]
                return f'{kind}({self.name(t)}) = {t:#x} [df: lui {lui:#x}]'
            return f'{kind}(?) lo={r.lo:#x} [high half not proven]'
        return f'R_MIPS_32 -> {self.name(r.target)}'

    def listing(self, addr):
        f = self.byaddr.get(addr)
        if f is None:
            k = max((g for g in self.funcs if g['addr'] <= addr), key=lambda g: g['addr'],
                    default=None)
            inside = f' (inside func_{k["addr"]:06x})' if k and addr < k['addr'] + k['size'] else ''
            raise SystemExit(f'rrdis: {addr:#x} is not a function start{inside}')
        p = self.p
        lo, hi = f['addr'], f['addr'] + f['size']
        df = self.df() if any(r.type_id == 6 and r.target is None
                              for r in p.relocs_in(lo, hi)) else {}
        labels = {}
        for a in range(lo, hi, 4):
            i = decode(p.word(a), a)
            t = i.target
            if t is not None and lo < t < hi and i.name not in ('jal',):
                labels[t] = f'.L{t:06x}'
        for t in self.tables.values():
            if lo <= t['jr'] < hi:
                for _, x in t['entries']:
                    labels[x] = f'.L{x:06x}'
        cls = self.classes.get(lo, ('?', ''))
        out = [f'# func_{lo:06x}  size {f["size"]}  section {f["section"]}  end:{f["end"]}  '
               f'start evidence: {",".join(sorted(f["evidence"]))}',
               f'# class: {cls[0]}' + (f' ({cls[1]})' if cls[1] else '')
               + (f'  library: {self.names[lo]}' if lo in self.names else '')]
        n_rel = 0
        for a in range(lo, hi, 4):
            if a in labels:
                out.append(f'{labels[a]}:')
            w = p.word(a)
            i = decode(w, a)
            text = i.text()
            if i.target is not None and i.target in labels and i.name != 'jal':
                text = text.replace(f'0x{i.target:x}', labels[i.target])
            notes = []
            for r in p.reloc_at(a):
                notes.append(self.annotate(r, df))
                n_rel += 1
            if a in self.tables:
                t = self.tables[a]
                notes.append(f"jump table {self.name(t['base'])}, {t['n']} entries")
            line = f'  {a:06x}: {w:08x}  {text}'
            if notes:
                line = f'{line:<56s} ; ' + '; '.join(notes)
            out.append(line)
        out.append(f'# {f["size"] // 4} words, {n_rel} relocations annotated')
        return out, n_rel


def selftest():
    L = Lister()
    fails = []
    total = ann = 0
    for f in L.funcs:
        lines, n = L.listing(f['addr'])
        want = len(L.p.relocs_in(f['addr'], f['addr'] + f['size']))
        total += want
        ann += n
        if n != want:
            fails.append(f"func_{f['addr']:06x}: {n} annotations for {want} relocations")
    print(f'listed {len(L.funcs)} functions; relocations {total}, annotated {ann}')
    # Known answer: the first .text function's HI16/LO16 pair (0x48/0x4c).
    lines, _ = L.listing(0x40)
    l48 = next(x for x in lines if x.startswith('  000048:'))
    t = L.p.reloc_at(0x48)[0].target
    if f'= {t:#x}' not in l48 or 'lui' not in l48:
        fails.append(f'known answer 0x48: {l48}')
    # Planted fault: drop the relocation index; annotations must go missing.
    keep = L.p._byaddr
    L.p._byaddr = {}
    try:
        _, n = L.listing(0x40)
    finally:
        L.p._byaddr = keep
    print(f'planted: relocation index emptied -> {n} annotations in func_000040')
    if n:
        fails.append('planted fault not visible')
    for x in fails[:10]:
        print('FAIL', x)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    if len(argv) != 2:
        raise SystemExit(__doc__)
    lines, _ = Lister().listing(int(argv[1], 16))
    print('\n'.join(lines))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
