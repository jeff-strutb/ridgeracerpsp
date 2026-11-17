#!/usr/bin/env python3
"""Recover the target of a LO16 whose high half no relocation records.

prx.py pairs every HI16 with the next LO16 in file order; any other LO16
(the compiler reused a `lui` register for several %lo uses) is left with
target None.  This module runs a forward data-flow analysis over each
function of config/us/funcs.csv: the abstract state maps a GPR to the HI16
`lui` that last wrote it, when every path agrees; any other write, a call
(caller-saved registers), or disagreement between paths removes it.  Delay
slots execute before the transfer; a likely branch's slot only on the taken
edge.

    from hilo import recover
    targets = recover(prx, funcs)   # {LO16 addr: (target, lui addr)}

Validation (selftest): the same analysis is run on LO16s whose target the
relocations already prove ('pair'); where the analysis gives a value it
must equal the proven one.  The low half is the instruction's own field,
so agreement tests the high half, which takes few distinct values in this
binary: it is a check on wiring, not proof for each recovered LO16.  A
planted fault (a lui no longer replaces an older value) must produce
disagreements.
"""
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE)]
from prx import Prx         # noqa: E402
from allegrex import decode  # noqa: E402
import funcmap              # noqa: E402

CALLER_SAVED = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31}
CLOBBER_CALLS = True
LUI_OVERWRITES = True


def _step(p, a, st, his):
    """Apply the instruction at a to state st (reg -> lui addr), in place."""
    i = decode(p.word(a), a)
    if a in his and i.name == 'lui':
        if LUI_OVERWRITES:
            st[i.rt] = a
        else:
            st.setdefault(i.rt, a)
        return i
    for r in i.writes:
        st.pop(r, None)
    return i


def _meet(x, y):
    return {r: v for r, v in x.items() if y.get(r) == v}


def analyse(p, f, his, tables):
    """{addr: state before addr} for the reachable words of function f."""
    lo, hi = f['addr'], f['addr'] + f['size']
    IN, SLOT, work = {}, {}, []

    def join(a, st):
        if not lo <= a < hi:
            return
        if a not in IN:
            IN[a] = dict(st)
            work.append(a)
        else:
            m = _meet(IN[a], st)
            if m != IN[a]:
                IN[a] = m
                work.append(a)
    for e in [lo] + list(f.get('pads', [])):
        join(e, {})
    while work:
        a = work.pop()
        st = dict(IN[a])
        i = _step(p, a, st, his)
        if not i.has_delay:
            join(a + 4, st)
            continue
        SLOT[a + 4] = dict(st) if a + 4 not in SLOT else _meet(SLOT[a + 4], st)
        s2 = dict(st)
        _step(p, a + 4, s2, his)
        if i.is_call and CLOBBER_CALLS:
            for r in CALLER_SAVED:
                s2.pop(r, None)
        if i.is_branch:
            join(i.target, s2)
            if not i.unconditional:
                join(a + 8, st if i.likely else s2)
        elif i.name == 'j':
            join(i.target, s2)
        elif i.name == 'jr':
            for _, t in tables.get(a, {}).get('entries', []):
                join(t, s2)
        else:                               # jal / jalr: the call returns
            join(a + 8, s2)
    out = dict(IN)
    for a, st in SLOT.items():
        out[a] = st if a not in out else _meet(out[a], st)
    return out


def recover(p, funcs, which=None):
    """{lo16 addr: (target, lui addr)} for LO16s with which(reloc) true
    (default: those prx.py left without a target)."""
    which = which or (lambda r: r.target is None)
    his = {r.addr: r for r in p.relocs if r.type_id == 5}
    tables = {t['jr']: t for t in funcmap.jump_tables(p, p.section('.text'))}
    los = sorted(r.addr for r in p.relocs if r.type_id == 6 and which(r))
    out = {}
    starts = [f['addr'] for f in funcs]
    import bisect
    byf = {}
    for a in los:
        k = bisect.bisect_right(starts, a) - 1
        byf.setdefault(k, []).append(a)
    for k, addrs in byf.items():
        f = funcs[k]
        before = analyse(p, f, his, tables)
        for a in addrs:
            st = before.get(a)
            if st is None:
                continue
            i = decode(p.word(a), a)
            h = st.get(i.rs)
            if h is None:
                continue
            hr = his[h]
            lo_r = [r for r in p.reloc_at(a) if r.type_id == 6][0]
            if hr.addrbase != lo_r.addrbase:
                continue
            base = p.segments[hr.addrbase].vaddr
            out[a] = (base + ((p.word(h) & 0xffff) << 16) + lo_r.lo, h)
    return out


def selftest():
    global LUI_OVERWRITES
    p = Prx.from_ref('us')
    F = funcmap.load()
    fails = []
    paired = {r.addr: r.target for r in p.relocs if r.type_id == 6 and r.how == 'pair'}
    got = recover(p, F, which=lambda r: r.how == 'pair')
    agree = sum(1 for a, (t, _) in got.items() if paired[a] == t)
    print(f'known answers: {len(paired)} paired LO16; analysis gives {len(got)}, agrees on {agree}')
    if agree != len(got) or not got:
        fails.append(f'{len(got) - agree} disagreements on paired LO16')
    rec = recover(p, F)
    total = sum(1 for r in p.relocs if r.type_id == 6 and r.target is None)
    end = p.image_end()
    oob = [a for a, (t, _) in rec.items() if not 0 <= t <= end]
    print(f'unpaired LO16: {total}; recovered {len(rec)}; outside image {len(oob)}')
    if oob:
        fails.append(f'{len(oob)} recovered targets outside the image')
    LUI_OVERWRITES = False
    try:
        got2 = recover(p, F, which=lambda r: r.how == 'pair')
    finally:
        LUI_OVERWRITES = True
    bad2 = sum(1 for a, (t, _) in got2.items() if paired[a] != t)
    print(f'planted: a lui no longer replaces an older lui value -> {bad2} disagreements')
    if not bad2:
        fails.append('planted lui-overwrite fault not detected')
    for x in fails:
        print('FAIL', x)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


if __name__ == '__main__':
    if sys.argv[1:] == ['--selftest']:
        sys.exit(selftest())
    p = Prx.from_ref('us')
    rec = recover(p, funcmap.load())
    for a in sorted(rec):
        print(f'{a:#08x} -> {rec[a][0]:#08x} (lui {rec[a][1]:#x})')
