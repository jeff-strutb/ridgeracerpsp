"""First-cut function map for the retail module -> config/us/funcs.csv.

Entries come from evidence only:
  fde   an .eh_frame FDE (exact start and size)
  jal   the target of a relocated `jal`
  pro   an `addiu sp,sp,-N` directly after a `jr ra` + delay slot (and any zero padding), inside a
        range no FDE covers. Catches static functions reached only by fallthrough-adjacent layout.
  ptr   an R_MIPS_32 word in .data/.rodata/.ctors/.dtors/.lib.ent/.rodata.sce* pointing into .text
        (vtable slots, callbacks, ctor lists). Pointers that land inside an FDE range are
        jump-table targets, not entries, and are ignored.
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
    for r in e.prx_rels():
        t = r['target']
        if t is None or not lo <= t < hi:
            continue
        if r['type'] == R_26 and r['at'] < e.addr(e.index('.lib.ent.top')) and e.word(r['at']) >> 26 == 3:
            ev.setdefault(t, set()).add('jal')
        elif r['type'] == R_32 and not (lo <= r['at'] < hi) and not in_fde(t):
            if e.names[[i for i, s in enumerate(e.sh) if s[3] <= r['at'] < s[3] + s[5] and s[2] & 2][-1]] != '.eh_frame':
                ev.setdefault(t, set()).add('ptr')
    # prologue split: only where no FDE gives an exact extent
    for p in range(lo, hi - 8, 4):
        if e.word(p) != 0x03e00008:  # jr ra
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
