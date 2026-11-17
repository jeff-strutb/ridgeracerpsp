#!/usr/bin/env python3
"""Recover the target of a LO16 whose high half no relocation records.

prx.py pairs every HI16 with the next LO16 in file order; any other LO16
(the compiler reused a `lui` register for several %lo uses) is left with
target None.  This module runs a forward data-flow analysis over each
function of config/us/funcs.csv: the abstract state maps a GPR to the HI16
`lui`s that may have last written it, when every path agrees on the value
they load (the same immediate and the same relocation base segment); any
other write, a call (caller-saved registers), or paths that disagree on the
value remove it.  Paths are joined on the value, not on which `lui` wrote
it: a loop that reloads the same high half with a second `lui` (0x0d3b2c:
`lui v1,0xa` before the loop and again in the back edge's delay slot) keeps
it.  (Joining on the `lui` address, as this module first did, lost those.)
A `move rd,rs` gives rd exactly rs's value (0x0010b8: `move s2,s1`).
Landing pads (from the FDE's LSDA call-site table) are entered only by the
unwinder from a call whose return address minus one lies in one of the pad's
call-site ranges; the callee-saved registers s0-s8 then hold what they held
after that call's delay slot, so a pad's state is the meet of those, s0-s8
only.  (Pads used to be left unanalysed.)  A call to a function that never
returns (NORETURN_SYMBOLS, located by an exact reference copy) does not fall
through to the next word.  Delay
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
JOIN_BY_VALUE = True
COPY_MOVES = True
PAD_STATES = True
NORETURN = True
# Functions that never return to their caller, by their GCC 3.3.3 source.  _Unwind_Resume
# (gcc/unwind.inc) ends in abort() or in uw_install_context, which leaves through
# __builtin_eh_return to the handler.  Each is located in retail as the one function start
# whose words (relocated fields masked) and relocation types equal its reference copy.
NORETURN_SYMBOLS = ('_Unwind_Resume',)
CALLEE_SAVED = set(range(16, 24)) | {30}


def _step(p, a, st, his):
    """Apply the instruction at a to state st (reg -> lui addr), in place."""
    i = decode(p.word(a), a)
    if a in his and i.name == 'lui':
        if LUI_OVERWRITES:
            st[i.rt] = frozenset([a])
        else:
            st.setdefault(i.rt, frozenset([a]))
        return i
    if COPY_MOVES and i.name == 'move' and i.op['args'] == 'd,s':
        v = st.get(i.rs)                # move rd,rs: rd takes exactly rs's value
        st.pop(i.rd, None)
        if v is not None and i.rd:
            st[i.rd] = v
        return i
    for r in i.writes:
        st.pop(r, None)
    return i


def _meet(x, y, value=None):
    """Registers both states agree on.  With value (lui addr -> its loaded value) two
    different luis that load the same value agree, and the result keeps both."""
    out = {}
    for r, v in x.items():
        w = y.get(r)
        if w is None:
            continue
        if w == v:
            out[r] = v
        elif value is not None and len({value(h) for h in v | w}) == 1:
            out[r] = v | w
    return out


def analyse(p, f, his, tables):
    """{addr: state before addr} for the reachable words of function f."""
    lo, hi = f['addr'], f['addr'] + f['size']
    IN, SLOT, work = {}, {}, []

    def value(h):
        return (p.word(h) & 0xffff, his[h].addrbase)
    vf = value if JOIN_BY_VALUE else None

    def _m(x, y):
        return _meet(x, y, vf)

    def join(a, st):
        if not lo <= a < hi:
            return
        if a not in IN:
            IN[a] = dict(st)
            work.append(a)
        else:
            m = _m(IN[a], st)
            if m != IN[a]:
                IN[a] = m
                work.append(a)
    join(lo, {})
    sites = f.get('callsites', []) if PAD_STATES else []
    while work:
        a = work.pop()
        st = dict(IN[a])
        i = _step(p, a, st, his)
        if not i.has_delay:
            join(a + 4, st)
            continue
        SLOT[a + 4] = dict(st) if a + 4 not in SLOT else _m(SLOT[a + 4], st)
        s2 = dict(st)
        _step(p, a + 4, s2, his)
        if i.is_call:
            # A landing pad is entered only by the unwinder, from a call whose return
            # address minus one lies in one of the pad's call-site ranges (the personality
            # routine's lookup).  The callee-saved registers then hold what they held after
            # the call's delay slot; nothing else is known.
            for s0, e0, pad in sites:
                if s0 <= a + 7 < e0:
                    join(pad, {r: v for r, v in s2.items() if r in CALLEE_SAVED})
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
        elif not (i.name == 'jal' and i.target in f.get('noreturn', ())):
            join(a + 8, s2)                 # jal / jalr: the call returns
    out = dict(IN)
    for a, st in SLOT.items():
        out[a] = st if a not in out else _m(out[a], st)
    return out


def call_sites(p, fde):
    """[(start, end, landing pad)] module addresses from an FDE's LSDA call-site table, for
    entries with a landing pad.  The layout is the one ehframe.landing_pads reads (GCC 3.3:
    LPStart omitted, TType 0xff or absptr with a uleb offset, uleb128 call sites)."""
    from ehframe import uleb
    if fde.lsda is None or fde.start is None:
        return []
    d = p.read(fde.lsda, 4096)
    if d[0] != 0xff:
        raise ValueError(f'LSDA {fde.lsda:#x}: LPStart encoding {d[0]:#x}')
    q = 2
    if d[1] != 0xff:
        _off, q = uleb(d, 2)
    if d[q] != 0x01:
        raise ValueError(f'LSDA {fde.lsda:#x}: call-site encoding {d[q]:#x}')
    n, q = uleb(d, q + 1)
    end, out = q + n, []
    while q < end:
        s, q = uleb(d, q)
        ln, q = uleb(d, q)
        lp, q = uleb(d, q)
        _a, q = uleb(d, q)
        if lp:
            out.append((fde.start + s, fde.start + s + ln, fde.start + lp))
    return out


def noreturn_addresses(p, funcs):
    """Retail addresses of NORETURN_SYMBOLS: for each, the single function start whose masked
    words and relocation types equal a reference copy of the symbol (libarchive.py)."""
    from libarchive import load_blobs, blob_key, masked
    starts = {f['addr']: f['size'] for f in funcs}
    out = set()
    blobs = load_blobs()
    for name in NORETURN_SYMBOLS:
        hits = set()
        for b in blobs:
            for off, size, nm, _ in b.syms:
                if nm != name or not size:
                    continue
                sig = [blob_key(b, off // 4 + k) for k in range(size // 4)]
                for a, n in starts.items():
                    if n != size:
                        continue
                    ok = True
                    for k in range(size // 4):
                        ty = 0
                        for r in p.reloc_at(a + 4 * k):
                            ty = r.type_id
                        if masked(p.word(a + 4 * k), ty) != sig[k]:
                            ok = False
                            break
                    if ok:
                        hits.add(a)
        if len(hits) != 1:
            raise ValueError(f'{name}: {len(hits)} retail copies')
        out |= hits
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
    from ehframe import parse
    fdes = {x.start: x for x in parse(p)[1] if x.start is not None}
    nor = noreturn_addresses(p, funcs) if NORETURN else set()
    for k, addrs in byf.items():
        f = dict(funcs[k])
        if f['addr'] in fdes:
            f['callsites'] = call_sites(p, fdes[f['addr']])
        f['noreturn'] = nor
        before = analyse(p, f, his, tables)
        for a in addrs:
            st = before.get(a)
            if st is None:
                continue
            i = decode(p.word(a), a)
            hs = st.get(i.rs)
            if hs is None:
                continue
            h = min(hs)
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
    # Known answer for the value join: the LO16 at 0x0d3b5c (function 0x0d3b2c, word 12)
    # uses v1, loaded by `lui v1,0xa` at 0x0d3b34 before the loop and again at 0x0d3b84 in the
    # back edge's delay slot.  Its high half is the one the paired LO16 at 0x0d3b38 proves,
    # and its low half equals that LO16's, so its target is that pair's target.
    global JOIN_BY_VALUE, COPY_MOVES, PAD_STATES, NORETURN
    want = p.reloc_at(0x0d3b38)[0].target
    same_lo = p.reloc_at(0x0d3b38)[0].lo == p.reloc_at(0x0d3b5c)[0].lo
    JOIN_BY_VALUE = COPY_MOVES = PAD_STATES = NORETURN = False
    try:
        old = recover(p, F)
    finally:
        JOIN_BY_VALUE = COPY_MOVES = PAD_STATES = NORETURN = True
    print(f'0x0d3b5c (0x0d3b2c word 12): want {want:#x}; join by lui address gives '
          f'{old.get(0x0d3b5c, (None,))[0]}; join by value gives '
          f'{hex(rec[0x0d3b5c][0]) if 0x0d3b5c in rec else None}')
    if not same_lo or rec.get(0x0d3b5c, (None,))[0] != want:
        fails.append('0x0d3b5c not recovered as %#x by the value join' % want)
    if 0x0d3b5c in old:
        fails.append('the address join recovers 0x0d3b5c: the known answer does not test the fix')
    # Copies and landing pads.  0x001120 reads through s2, a copy (move s2,s1) of the high
    # half the pair at 0x0010f8 proves; 0x005e6c is in the landing pad of 0x005d88, entered
    # from the call at 0x005e04 with s1 holding the high half the pair at 0x005dcc proves.
    # Both have their pair's low half, so their targets are their pair's.
    COPY_MOVES = PAD_STATES = NORETURN = False
    try:
        old2 = recover(p, F)
    finally:
        COPY_MOVES = PAD_STATES = NORETURN = True
    # 0x0752cc (0x075224): its pad's state was emptied by the fall-through of the call to
    # _Unwind_Resume just before it; the pair at 0x075268 proves its high half.
    NORETURN = False
    try:
        old3 = recover(p, F)
    finally:
        NORETURN = True
    print(f'_Unwind_Resume located at {sorted(hex(a) for a in noreturn_addresses(p, F))}')
    pr = p.reloc_at(0x075268)[0]
    got = rec.get(0x0752cc, (None,))[0]
    print(f'0x0752cc: want {pr.target:#x} (pair 0x75268); calls returning '
          f'{old3.get(0x0752cc, (None,))[0]}; now {hex(got) if got is not None else None}')
    if got != pr.target or 0x0752cc in old3 or p.reloc_at(0x0752cc)[0].lo != pr.lo:
        fails.append('0x0752cc known answer')
    changed3 = [a for a in old3 if a not in rec or rec[a][0] != old3[a][0]]
    print(f'without no-return calls: {len(old3)}; with: {len(rec)}; changed: {len(changed3)}')
    if changed3:
        fails.append(f'{len(changed3)} targets changed by the no-return rule')
    for a, pair in ((0x001120, 0x0010f8), (0x005e6c, 0x005dcc)):
        pr = p.reloc_at(pair)[0]
        want2 = pr.target
        got = rec.get(a, (None,))[0]
        print(f'{a:#08x}: want {want2:#x} (pair {pair:#x}); before copies/pads '
              f'{old2.get(a, (None,))[0]}; now {hex(got) if got is not None else None}')
        if got != want2 or p.reloc_at(a)[0].lo != pr.lo:
            fails.append(f'{a:#x} not recovered as {want2:#x}')
        if a in old2:
            fails.append(f'{a:#x} was already recovered: the known answer does not test the fix')
    changed2 = [a for a in old2 if a not in rec or rec[a][0] != old2[a][0]]
    print(f'without copies and pads: {len(old2)} recovered; with: {len(rec)}; '
          f'earlier targets lost or changed: {len(changed2)}')
    if changed2:
        fails.append(f'{len(changed2)} targets recovered without copies/pads changed')
    changed = [a for a in old if a not in rec or rec[a][0] != old[a][0]]
    print(f'join by lui address: {len(old)} recovered; by value: {len(rec)}; '
          f'earlier targets lost or changed: {len(changed)}')
    if changed:
        fails.append(f'{len(changed)} targets recovered by the address join changed')
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
