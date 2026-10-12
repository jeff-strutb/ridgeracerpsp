"""First-cut function map for the retail module -> config/us/funcs.csv.

Entries come from evidence only:
  fde   an .eh_frame FDE (exact start and size)
  jal   the target of a relocated `jal`
  pro   an `addiu sp,sp,-N` directly after an unconditional `jr ra`/`j`/`b` + delay slot (and any zero padding), inside a
        range no FDE covers. Catches static functions reached only by fallthrough-adjacent layout.
  ptr   an R_MIPS_32 word in .data/.rodata/.ctors/.dtors/.lib.ent/.rodata.sce* pointing into .text
        (vtable slots, callbacks, ctor lists). Pointers that land inside an FDE range, and the
        words of a jump table (a table whose address is loaded by `lui`+`addiu`/`lw` shortly
        before a `jr` on a register other than ra), are case labels, not entries, and are ignored.
  tail  code directly after an FDE function's extent (past zero padding) that nothing else
        claims: the FDE proves the previous function ends there.
  split a function without an FDE ends after the delay slot of a `jr ra` or `j` that no earlier
        branch of the function jumps past; code after that (other than zero padding) is the
        next function (identical leaf functions laid out back to back, empty functions).
A function without an FDE ends at the next entry, less trailing alignment nops.
Usage: python3 tools/analysis/funcmap.py [orig/us/BOOT.BIN] [config/us/funcs.csv]
"""
import bisect
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prx import Elf, fde_functions, R_26, R_32  # noqa: E402


def is_jump(w):
    """True for any MIPS jump/branch (instructions that own a delay slot)."""
    op = w >> 26
    if op == 0:
        return (w & 0x3f) in (8, 9)  # jr, jalr
    if op == 1:
        return True  # regimm branches
    return op in (2, 3, 4, 5, 6, 7, 20, 21, 22, 23) or (op in (17, 18) and (w >> 21) & 31 == 8)


def branch_target(p, w):
    """Target of a PC-relative branch at p, or None."""
    op = w >> 26
    if op in (1, 4, 5, 6, 7, 20, 21, 22, 23) or (op in (17, 18) and (w >> 21) & 31 == 8):
        off = w & 0xffff
        return p + 4 + ((off - 0x10000 if off & 0x8000 else off) << 2)
    return None


def jump_tables(e, rels, lo, hi):
    """{table word address: case label} for every switch jump table. A table ends at the first
    word that is not a relocated pointer to code within 32 KB of the dispatching instruction."""
    words = {}
    lows = sorted((r['at'], r['target']) for r in rels if r['type'] == 6 and r['target'] is not None and lo <= r['at'] < hi)
    r32 = {r['at']: r['target'] for r in rels if r['type'] == R_32}
    for at, tgt in lows:
        # a jr through a register other than ra within the next 8 instructions
        if not any((e.word(at + 4 * k) & 0xfc1fffff) == 0x00000008 and (e.word(at + 4 * k) >> 21) & 31 != 31
                   for k in range(1, 9) if at + 4 * k < hi):
            continue
        a = tgt
        while a in r32 and r32[a] is not None and lo <= r32[a] < hi and abs(r32[a] - at) < 0x8000:
            words[a] = r32[a]
            a += 4
    return words


def split_leaves(e, a, size, labels):
    """Split a no-FDE range after a final `jr ra`/`j` (see the module notes): [(start, size)].
    `labels` are the jump-table case labels: a `jr` through a table reaches all of them."""
    out, start, far, p, end = [], a, a, a, a + size
    inside = [t for t in labels if a <= t < end]
    while p < end:
        w = e.word(p)
        t = branch_target(p, w)
        if t is not None:
            far = max(far, t)
        if (w & 0xfc1fffff) == 0x00000008 and (w >> 21) & 31 != 31 and inside:
            far = max(far, max(inside))
        if (w == 0x03e00008 or w >> 26 == 2) and far <= p + 4 and p + 8 < end:
            q = p + 8
            while q < end and e.word(q) == 0:
                q += 4
            if q < end:
                out.append((start, p + 8 - start))
                start = far = p = q
                continue
        p += 4
    out.append((start, end - start))
    return out


def build(path):
    e = Elf(open(path, 'rb').read())
    ti = e.index('.text')
    lo, hi = e.addr(ti), e.addr(ti) + len(e.data(ti))
    fde = {s: z for s, z, _ in fde_functions(e) if lo <= s < hi}
    starts = sorted(fde)
    ends = [s + fde[s] for s in starts]

    def in_fde(a):
        k = bisect.bisect_right(starts, a) - 1
        return k >= 0 and starts[k] < a < ends[k]

    ev = {s: {'fde'} for s in fde}
    rels = e.prx_rels()
    jt = jump_tables(e, rels, lo, hi)
    labels = sorted(set(jt.values()))
    for r in rels:
        t = r['target']
        if t is None or not lo <= t < hi:
            continue
        if r['type'] == R_26 and r['at'] < e.addr(e.index('.lib.ent.top')) and e.word(r['at']) >> 26 == 3:
            ev.setdefault(t, set()).add('jal')
        elif r['type'] == R_32 and not (lo <= r['at'] < hi) and not in_fde(t) and r['at'] not in jt:
            if e.names[[i for i, s in enumerate(e.sh) if s[3] <= r['at'] < s[3] + s[5] and s[2] & 2][-1]] != '.eh_frame':
                ev.setdefault(t, set()).add('ptr')
    # tail: code right after an FDE function (past any zero padding) that no other evidence
    # claims is a function of its own; an FDE gives its function's exact extent, so nothing
    # else can own those words (leaf functions without unwind info, reached only by pointer
    # or not at all)
    for st in starts:
        q = st + fde[st]
        while q < hi and e.word(q) == 0:
            q += 4
        if q < hi and q not in ev and not in_fde(q) and q not in fde:
            ev.setdefault(q, set()).add('tail')
    # prologue split: only where no FDE gives an exact extent
    for p in range(lo, hi - 8, 4):
        w = e.word(p)
        if not (w == 0x03e00008 or w >> 26 == 2 or w >> 16 == 0x1000):  # jr ra, j, b (beq zero,zero)
            continue
        q = p + 8
        while q < hi and e.word(q) == 0:
            q += 4
        if q < hi and (e.word(q) >> 16) == 0x27bd and e.word(q) & 0x8000 and q not in ev and not in_fde(q) and q not in fde:
            ev.setdefault(q, set()).add('pro')
    addrs = sorted(ev)
    rows = []
    for k, a in enumerate(addrs):
        if a in fde:
            size = fde[a]
        else:
            end = addrs[k + 1] if k + 1 < len(addrs) else hi
            # trailing zero words are alignment padding, except a nop in a jump's delay slot
            while end - 4 > a and e.word(end - 4) == 0 and not is_jump(e.word(end - 8)):
                end -= 4
            size = end - a
            for k2, (b, z) in enumerate(split_leaves(e, a, size, labels)):
                rows.append((b, z, '+'.join(sorted(ev[a])) if k2 == 0 else 'split'))
            continue
        rows.append((a, size, '+'.join(sorted(ev[a]))))
    return e, rows, (lo, hi)


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else 'orig/us/BOOT.BIN'
    dst = sys.argv[2] if len(sys.argv) > 2 else 'config/us/funcs.csv'
    e, rows, (lo, hi) = build(src)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    with open(dst, 'w') as f:
        f.write('addr,size,evidence\n')
        for a, z, ev in rows:
            f.write(f'0x{a:06x},{z},{ev}\n')
    covered = sum(z for _, z, _ in rows)
    overlaps = sum(1 for (a, z, _), (b, _, _) in zip(rows, rows[1:]) if a + z > b)
    print(f'{len(rows)} functions, {covered} of {hi - lo} .text bytes, {overlaps} overlaps -> {dst}')


if __name__ == '__main__':
    main()
