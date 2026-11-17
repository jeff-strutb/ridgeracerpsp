#!/usr/bin/env python3
"""Retail and compiled side by side for one tagged function.

    tools/sbs.py FILE 0xADDR [--blind] [--all] [--no-cache]

Output, in this order:
  1. The grader's verdict for the function (tools/score.py), with its first difference.
  2. Frame: the stack frame size (the prologue's `addiu sp,sp,-N`) and the saved-register set
     (stores of s0-s8/ra and $f20-$f31 to the stack before the first branch or call), retail
     and compiled.
  3. The earliest differing instruction by position.
  4. The listing, aligned by difflib on per-instruction keys.  Relocated fields are masked on
     both sides before keys are made; relocations are shown as retail target and compiled
     symbol+addend.  Marks: blank = equal, ~ = equal except register choice, ! = differs,
     R = relocation type differs, < or > = present on one side only.

--blind makes the keys register-blind: the register fields named by the instruction's operand
letters (GPR, FPR and VFPU registers) are masked too, so a line that differs only in register
choice is treated as equal for alignment and for the earliest difference.  Fix the frame
first, then the structure (--blind), then the registers (default).

Without --all, only the lines around differences are listed (3 lines of context).
"""
import argparse
import difflib
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import score                    # noqa: E402
from allegrex import decode     # noqa: E402

GPR_FIELDS = {'s': (21, 0x1f), 'b': (21, 0x1f), 'r': (21, 0x1f), 'v': (21, 0x1f),
              't': (16, 0x1f), 'w': (16, 0x1f), 'd': (11, 0x1f),
              'D': (6, 0x1f), 'S': (11, 0x1f), 'V': (11, 0x1f), 'T': (16, 0x1f)}
VFPU_FIELDS = {'d': [(0, 0x7f)], 'x': [(0, 0x7f)], 'v': [(0, 0x7f)], 's': [(8, 0x7f)],
               't': [(16, 0x7f)], 'm': [(16, 0x1f), (0, 0x3)], 'n': [(16, 0x1f), (0, 0x1)]}
SAVED_GPR = set(range(16, 24)) | {30, 31}
GPR_NAMES = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4',
             't5', 't6', 't7', 's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9',
             'k0', 'k1', 'gp', 'sp', 's8', 'ra']


def reg_mask(word):
    """Bits of word that name registers, from the decoded entry's operand letters."""
    i = decode(word)
    if not i.op:
        return 0
    a, m, k = i.op['args'], 0, 0
    while k < len(a):
        c = a[k]
        if c == '?' and k + 1 < len(a):
            L = a[k + 1]
            if L in VFPU_FIELDS and k + 2 < len(a) and a[k + 2].isdigit():
                for sh, mk in VFPU_FIELDS[L]:
                    m |= mk << sh
                k += 3
                continue
            k += 2
            continue
        if c in GPR_FIELDS:
            sh, mk = GPR_FIELDS[c]
            m |= mk << sh
        k += 1
    return m


def frame(words):
    """(frame size or None, {register name: stack offset}) from the prologue."""
    size, saved = None, {}
    for w in words:
        i = decode(w)
        if i.name == 'addiu' and i.rs == 29 and i.rt == 29 and size is None and i.imm < 0:
            size = -i.imm
        elif i.name == 'sw' and i.rs == 29 and i.rt in SAVED_GPR:
            saved.setdefault(GPR_NAMES[i.rt], i.imm)
        elif i.name == 'swc1' and i.rs == 29 and 20 <= i.rt <= 31:
            saved.setdefault('$f%d' % i.rt, i.imm)
        if i.has_delay or i.is_jump:
            break
    return size, saved


class Side:
    def __init__(self, words, types, notes):
        self.words, self.types, self.notes = words, types, notes

    def key(self, k, blind):
        w, t = self.words[k], self.types[k]
        if t is not None:
            w &= ~score.FIELD.get(t, 0xffffffff) & 0xffffffff
        if blind:
            w &= ~reg_mask(w) & 0xffffffff
            return (decode(w).name, w, t)
        return (w, t)


def sides(g, u, tag, sym):
    p, obj = g.retail.p, u.obj
    f = g.retail.funcs[tag.addr]
    rw, rt, rn = [], [], []
    for k in range(f['size'] // 4):
        a = tag.addr + 4 * k
        rw.append(p.word(a))
        r = g.retail.reloc(a)
        if isinstance(r, list):
            rt.append(-1)
            rn.append('several relocations')
            continue
        rt.append(r.type_id if r else None)
        if r:
            t = g.retail.target(r)
            rn.append('%s %s' % (score.rname(r.type_id)[7:],
                                 'unknown' if t is None else name_of(g, t)))
        else:
            rn.append('')
    cw, ct, cn = [], [], []
    for k in range(sym.size // 4):
        o = sym.value + 4 * k
        cw.append(obj.word(sym.shndx, o))
        rl = obj.relat.get((sym.shndx, o), [])
        ct.append(rl[0].type if len(rl) == 1 else (None if not rl else -1))
        if rl:
            r = rl[0]
            nm = r.sym.name or obj.secs[r.sym.shndx].name
            cn.append('%s %s%+#x%s' % (score.rname(r.type)[7:], nm, r.addend or 0,
                                        '' if r.type != 6 or r.paired else ' (lo only)'))
        else:
            cn.append('')
    return Side(rw, rt, rn), Side(cw, ct, cn)


def name_of(g, t):
    f = g.retail.funcs.get(t)
    if f is not None:
        return 'func_%06x' % t
    s = g.retail.p.section_at(t)
    return '%#08x (%s)' % (t, s.name if s else '?')


def line(side, k, addr):
    if k is None:
        return ''
    w = side.words[k]
    txt = decode(w, addr).text().strip()
    n = side.notes[k]
    return '%08x  %-30s %s' % (w, txt[:30], ('; ' + n) if n else '')


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('file')
    ap.add_argument('addr')
    ap.add_argument('--blind', action='store_true', help='register-blind keys')
    ap.add_argument('--all', action='store_true', help='list every line')
    ap.add_argument('--no-cache', action='store_true')
    a = ap.parse_args(argv)
    t0 = time.time()
    addr = int(a.addr, 16)
    tree = score.Tree(use_cache=not a.no_cache)
    g = score.Grader(tree)
    u = tree.unit(a.file)
    tags = [t for t in u.tags if t.addr == addr and t.region == 'us']
    if not tags:
        print('no tag for %#08x in %s' % (addr, a.file))
        return 2
    tag = tags[0]
    r = g.grade(u, tag)
    g.finalize([r])
    print(score.fmt(r))
    if r['verdict'] == 'MISSING':
        return 1
    sym, _ = u.claim[tag]
    R, C = sides(g, u, tag, sym)
    fr, fc = frame(R.words), frame(C.words)
    print('frame    retail %-6s compiled %-6s %s' % (fr[0], fc[0], '' if fr[0] == fc[0] else '<- differs'))
    print('saved    retail %s' % ' '.join('%s@%d' % kv for kv in sorted(fr[1].items(), key=lambda x: x[1])))
    print('         compiled %s %s' % (' '.join('%s@%d' % kv for kv in sorted(fc[1].items(), key=lambda x: x[1])),
                                       '' if fr[1] == fc[1] else '<- differs'))
    print('size     retail %d, compiled %d words' % (len(R.words), len(C.words)))
    rk = [R.key(k, a.blind) for k in range(len(R.words))]
    ck = [C.key(k, a.blind) for k in range(len(C.words))]
    first = next((k for k in range(min(len(rk), len(ck))) if rk[k] != ck[k]),
                 None if len(rk) == len(ck) else min(len(rk), len(ck)))
    mode = 'structure (register-blind)' if a.blind else 'exact'
    if first is None:
        print('earliest %s difference: none' % mode)
    else:
        print('earliest %s difference: word %d (%#08x)' % (mode, first, addr + 4 * first))
    rows = []
    sm = difflib.SequenceMatcher(None, rk, ck, autojunk=False)
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        n = max(i2 - i1, j2 - j1)
        for d in range(n):
            i = i1 + d if i1 + d < i2 else None
            j = j1 + d if j1 + d < j2 else None
            if op == 'equal':
                mark = '~' if (R.key(i, False) != C.key(j, False)) else ' '
            elif i is None:
                mark = '>'
            elif j is None:
                mark = '<'
            elif R.types[i] != C.types[j]:
                mark = 'R'
            elif R.key(i, True) == C.key(j, True):
                mark = '~'
            else:
                mark = '!'
            rows.append((mark, i, j))
    show = set(range(len(rows))) if a.all else set()
    if not a.all:
        for k, (m, _, _) in enumerate(rows):
            if m != ' ' and not (a.blind and m == '~'):
                show.update(range(max(0, k - 3), min(len(rows), k + 4)))
    prev = -1
    for k, (m, i, j) in enumerate(rows):
        if k not in show:
            continue
        if prev >= 0 and k != prev + 1:
            print('   ...')
        prev = k
        ia = '%4d' % i if i is not None else '    '
        print('%s %s %-70s | %s' % (m, ia, line(R, i, addr + 4 * (i or 0)),
                                    line(C, j, addr + 4 * (j or 0))))
    if not show:
        print('(listing identical%s; --all to print it)' % (' up to registers' if a.blind else ''))
    print('== %.2f s (%s)' % (time.time() - t0, 'compiled' if tree.times['compiled'] else 'cached'))
    return 0 if r['verdict'] == 'EXACT' else 1


if __name__ == '__main__':
    sys.exit(main())
