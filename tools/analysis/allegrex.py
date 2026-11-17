#!/usr/bin/env python3
"""Allegrex instruction decoder driven by the toolchain's own opcode table.

The table (build/allegrex_ops.json) is extracted by mkopcodes.py from the
psp-objdump shipped in psp-gcc-1.3.1; ./setup.sh builds it.  Matching follows
libopcodes print_insn_mips: start at the first entry with the word's major
opcode, take the first entry that is not a macro (pinfo 0xffffffff), whose
(word & mask) == match, and whose membership intersects the 'allegrex'
arch's ISA mask (read from mips_arch_choices) or carries the Allegrex CPU
bit 0x10000000 (the membership of every VFPU entry, and only Allegrex has a
VFPU).

    from allegrex import decode
    i = decode(word, addr)
    i.name, i.args, i.text()        # 'addiu', 'sp,sp,-32'
    i.writes / i.reads              # GPR numbers, from the entry's pinfo flags
    i.is_branch, i.is_jump, i.likely, i.target, i.is_call, i.is_return

Operand letters follow libopcodes 2.16 for the integer, FPU and branch
forms.  VFPU operands ('?' letters) are printed from the encoding fields
(vd bits 0-6, vs 8-14, vt 16-22; lv.s/sv.s vt bits 16-20 + bits 0-1<<5;
lv.q/sv.q vt bits 16-20 + bit 0<<5) and named with the binary's own
vfpu_*reg_names tables; an operand whose name in that table is empty is
printed raw as ?<letter>=<value> and counted in Insn.raw_operands.  The
vpfx operands, vrot code and vf2in scale are always printed raw.
"""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
TABLE = ROOT / 'build' / 'allegrex_ops.json'
INSN_MACRO = 0xffffffff
INSN_ALLEGREX = 0x10000000
# pinfo bits (binutils include/opcode/mips.h of this vintage)
WRITE_GPR_D, WRITE_GPR_T, WRITE_GPR_31 = 0x1, 0x2, 0x4
READ_GPR_S, READ_GPR_T = 0x40, 0x80
UNCOND_BRANCH_DELAY, COND_BRANCH_DELAY, COND_BRANCH_LIKELY = 0x20000, 0x40000, 0x80000

_T = None


def table():
    global _T
    if _T is None:
        if not TABLE.is_file():
            raise SystemExit(f'allegrex: {TABLE} missing (run ./setup.sh)')
        t = json.loads(TABLE.read_text())
        isa = t['arch']['allegrex']['isa']
        ops = [o for o in t['opcodes']]
        first = {}
        for k, o in enumerate(ops):
            first.setdefault(o['match'] >> 26, k)
        _T = {'ops': ops, 'first': first, 'isa': isa, 'names': t['names']}
    return _T


def sext16(v):
    v &= 0xffff
    return v - 0x10000 if v & 0x8000 else v


VREG_TABLES = {'0': 'vfpu_sreg_names', '1': 'vfpu_vpreg_names', '2': 'vfpu_vtreg_names',
               '3': 'vfpu_vqreg_names', '5': 'vfpu_mpreg_names', '6': 'vfpu_mtreg_names',
               '7': 'vfpu_mqreg_names'}


class Insn:
    __slots__ = ('addr', 'word', 'op', 'name', 'args', 'raw_operands')

    def __init__(self, addr, word, op):
        self.addr, self.word, self.op = addr, word, op
        self.name = op['name'] if op else None
        self.raw_operands = 0
        self.args = self._format() if op else f'.word 0x{word:08x}'

    # -- fields ----------------------------------------------------------
    @property
    def rs(self):
        return (self.word >> 21) & 31

    @property
    def rt(self):
        return (self.word >> 16) & 31

    @property
    def rd(self):
        return (self.word >> 11) & 31

    @property
    def imm(self):
        return sext16(self.word)

    @property
    def pinfo(self):
        return self.op['pinfo'] if self.op else 0

    # -- control flow ----------------------------------------------------
    @property
    def is_branch(self):     # conditional or unconditional PC-relative
        return bool(self.op) and 'p' in self.op['args'].split(',')

    @property
    def is_jump(self):       # j / jal / jr / jalr
        return bool(self.op) and self.name in ('j', 'jal', 'jr', 'jalr')

    @property
    def has_delay(self):
        return bool(self.pinfo & (UNCOND_BRANCH_DELAY | COND_BRANCH_DELAY | COND_BRANCH_LIKELY))

    @property
    def likely(self):
        return bool(self.pinfo & COND_BRANCH_LIKELY)

    @property
    def unconditional(self):
        return bool(self.pinfo & UNCOND_BRANCH_DELAY)

    @property
    def is_call(self):
        return self.name in ('jal', 'jalr', 'bal')

    @property
    def is_return(self):
        return self.name == 'jr' and self.rs == 31

    @property
    def target(self):
        if self.is_branch:
            return self.addr + 4 + (self.imm << 2)
        if self.name in ('j', 'jal'):
            return ((self.addr + 4) & 0xf0000000) | ((self.word & 0x3ffffff) << 2)
        return None

    # -- data flow (GPRs) ------------------------------------------------
    @property
    def writes(self):
        p, w = self.pinfo, set()
        if p & WRITE_GPR_D:
            w.add(self.rd)
        if p & WRITE_GPR_T:
            w.add(self.rt)
        if p & WRITE_GPR_31:
            w.add(31)
        w.discard(0)
        return w

    @property
    def reads(self):
        p, r = self.pinfo, set()
        if p & READ_GPR_S:
            r.add(self.rs)
        if p & READ_GPR_T:
            r.add(self.rt)
        return r

    # -- text ------------------------------------------------------------
    def _format(self):
        T = table()
        gpr = T['names']['mips_gpr_names_oldabi']
        fpr = T['names']['mips_fpr_names_numeric']
        w, a = self.word, self.op['args']
        if a.startswith('?0'):          # vpfxs/vpfxt/vpfxd: one raw 20-bit field
            self.raw_operands += 1
            return f'?pfx=0x{w & 0xfffff:05x}'
        out, i = [], 0
        while i < len(a):
            c = a[i]
            if c in ',()':
                out.append(c)
            elif c in 'sbrv':
                out.append(gpr[(w >> 21) & 31])
            elif c in 'tw':
                out.append(gpr[(w >> 16) & 31])
            elif c == 'd':
                out.append(gpr[(w >> 11) & 31])
            elif c == 'z':
                out.append(gpr[0])
            elif c == '<':
                out.append(str((w >> 6) & 31))
            elif c in 'iu':
                out.append(f'0x{w & 0xffff:x}')
            elif c in 'jo':
                out.append(str(sext16(w)))
            elif c == 'p':
                out.append(f'0x{self.addr + 4 + (sext16(w) << 2):x}')
            elif c == 'a':
                out.append(f'0x{((self.addr + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2):x}')
            elif c == 'B':
                out.append(f'0x{(w >> 6) & 0xfffff:x}')
            elif c == 'D':
                out.append(fpr[(w >> 6) & 31])
            elif c in 'SV':
                out.append(fpr[(w >> 11) & 31])
            elif c == 'T':
                out.append(fpr[(w >> 16) & 31])
            elif c == '?':
                i, s = self._vfpu(a, i + 1)
                out.append(s)
                continue
            else:
                out.append(f'<{c}>')
                self.raw_operands += 1
            i += 1
        return ''.join(out)

    def _vfpu(self, a, i):
        T, w = table(), self.word
        L = a[i]
        if L in 'dxvstmn':
            size = a[i + 1]
            nxt = i + 3
            if L in 'dxv':
                reg = w & 0x7f
            elif L == 's':
                reg = (w >> 8) & 0x7f
            elif L == 't':
                reg = (w >> 16) & 0x7f
            elif L == 'm':
                reg = ((w >> 16) & 0x1f) | ((w & 3) << 5)
            else:
                reg = ((w >> 16) & 0x1f) | ((w & 1) << 5)
            names = T['names'].get(VREG_TABLES.get(size, ''), [])
            if reg < len(names) and names[reg]:
                return nxt, names[reg]
            self.raw_operands += 1
            return nxt, f'?{L}={reg}'
        if L == 'o':
            return i + 1, str(sext16(w & 0xfffc))
        if L == 'a':
            k = (w >> 16) & 31
            cn = T['names']['vfpu_const_names']
            if k < len(cn) and cn[k]:
                return i + 1, cn[k]
            self.raw_operands += 1
            return i + 1, f'?a={k}'
        self.raw_operands += 1
        if L in 'bw':
            return i + 1, f'?{L}={(w >> 16) & 31}'
        return i + 1, f'?{L}=0x{w:08x}'

    def text(self):
        return f'{self.name:10s} {self.args}' if self.op else self.args


def decode(word, addr=0):
    T = table()
    ops, isa = T['ops'], T['isa']
    for o in ops[T['first'].get(word >> 26, len(ops)):]:
        if o['pinfo'] == INSN_MACRO or (word & o['mask']) != o['match']:
            continue
        if (o['membership'] & isa) or (o['membership'] & INSN_ALLEGREX):
            return Insn(addr, word, o)
    return Insn(addr, word, None)


# Known answers: standard MIPS encodings whose meaning does not depend on
# this table (MIPS32 architecture manual field layouts).
KNOWN = [
    (0x03e00008, 0, 'jr', 'ra'),
    (0x27bdfff0, 0, 'addiu', 'sp,sp,-16'),
    (0x00000000, 0, 'nop', ''),
    (0x8fbf001c, 0, 'lw', 'ra,28(sp)'),
    (0x0c000010, 0x100, 'jal', '0x40'),
    (0x1440fffe, 0x200, 'bnez', 'v0,0x1fc'),
    (0x3c010002, 0, 'lui', 'at,0x2'),
    (0x00851021, 0, 'addu', 'v0,a0,a1'),
    (0x46020800, 0, 'add.s', '$f0,$f1,$f2'),
    (0x7c041420, 0, 'seb', 'v0,a0'),
]


def selftest():
    sys_path_setup()
    from prx import Prx
    fails = []
    for w, a, name, args in KNOWN:
        i = decode(w, a)
        if (i.name, i.args) != (name, args):
            fails.append(f'{w:#010x}: got {i.name} {i.args}, want {name} {args}')
    p = Prx.from_ref('us')
    und = raw = 0
    for s in p.sections:
        if s.execinstr:
            for a in range(s.addr, s.end, 4):
                i = decode(p.word(a), a)
                und += i.op is None
                raw += i.raw_operands
    print(f'reference code: {und} undecoded words, {raw} raw VFPU operands')
    if und:
        fails.append(f'{und} undecoded words')
    # Planted fault: corrupt the addiu entry's match; known answers must fail.
    T = table()
    e = next(o for o in T['ops'] if o['name'] == 'addiu')
    keep = e['match']
    e['match'] ^= 1 << 26
    bad = sum(1 for w, a, n, x in KNOWN if (decode(w, a).name, decode(w, a).args) != (n, x))
    e['match'] = keep
    print(f'planted corrupt addiu entry: {bad} known answers wrong')
    if not bad:
        fails.append('planted table fault not detected')
    for f in fails:
        print('FAIL', f)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


def sys_path_setup():
    import sys
    here = Path(__file__).resolve().parent
    for d in (str(here), str(here.parent)):
        if d not in sys.path:
            sys.path.insert(0, d)


if __name__ == '__main__':
    import sys
    if sys.argv[1:] == ['--selftest']:
        sys.exit(selftest())
    for w in sys.argv[1:]:
        print(decode(int(w, 16)).text())
