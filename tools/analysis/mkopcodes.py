#!/usr/bin/env python3
"""Extract the Allegrex opcode table from the toolchain's own psp-objdump.

    mkopcodes.py PSP_GCC_1_3_1_TARBALL OUT.json

psp-gcc-1.3.1 ships bin/psp-objdump as an unstripped i386 ELF.  Its data
holds the libopcodes tables that objdump disassembles with:

    mips_builtin_opcodes      struct mips_opcode[1329], 24 bytes each:
                              name*, args*, match, mask, pinfo, membership
    mips_arch_choices         struct mips_arch_choice[], 36 bytes each:
                              name*, bfd_mach_valid, bfd_mach, processor, isa,
                              cp0_names*, cp0sel_names*, cp0sel_len, hwr_names*
    mips_gpr_names_oldabi, mips_fpr_names_32, vfpu_*_names, ...

Nothing is typed in by hand: names, masks, membership and the 'allegrex'
ISA mask all come from the binary, located through its symbol table.  The
tarball and the objdump inside it are MD5-checked.
"""
import hashlib
import io
import json
import struct
import sys
import tarfile

TARBALL_MD5 = '79792a94c8b37be3832fda5dcb30b601'
OBJDUMP_MD5 = 'c879a4b6b4767daf58d81d27c173561f'
MEMBER = './bin/psp-objdump'

NAME_TABLES = {  # symbol -> entries
    'mips_gpr_names_oldabi': 32, 'mips_fpr_names_numeric': 32,
    'vfpu_sreg_names': 128, 'vfpu_vpreg_names': 128, 'vfpu_vtreg_names': 128,
    'vfpu_vqreg_names': 128, 'vfpu_mpreg_names': 128, 'vfpu_mtreg_names': 128,
    'vfpu_mqreg_names': 128, 'vfpu_cond_names.2': 16, 'vfpu_const_names.3': 20,
    'pfx_cst_names.5': 8, 'pfx_swz_names.6': 4, 'pfx_sat_names.7': 4,
}


class Elf32:
    def __init__(self, d):
        self.d = d
        shoff, = struct.unpack_from('<I', d, 0x20)
        shes, shn, shstr = struct.unpack_from('<HHH', d, 0x2e)
        self.sh = [struct.unpack_from('<10I', d, shoff + i * shes) for i in range(shn)]
        st = [s for s in self.sh if s[1] == 2][0]
        strt = self.sh[st[6]][4]
        self.syms = {}
        for k in range(st[5] // 16):
            n, v, sz, _i, _o, _x = struct.unpack_from('<IIIBBH', d, st[4] + k * 16)
            self.syms[self.cstr_off(strt + n)] = (v, sz)

    def cstr_off(self, o):
        return self.d[o:self.d.index(b'\0', o)].decode()

    def off(self, va):
        for s in self.sh:
            if s[1] == 1 and s[3] and s[3] <= va < s[3] + s[5]:
                return s[4] + va - s[3]
        raise ValueError(f'{va:#x} not in a PROGBITS section')

    def u32(self, va):
        return struct.unpack_from('<I', self.d, self.off(va))[0]

    def cstr(self, va):
        return self.cstr_off(self.off(va)) if va else None


def extract(tarball):
    raw = open(tarball, 'rb').read()
    got = hashlib.md5(raw).hexdigest()
    if got != TARBALL_MD5:
        raise SystemExit(f'mkopcodes: {tarball}: MD5 {got}, expected {TARBALL_MD5}')
    with tarfile.open(fileobj=io.BytesIO(raw), mode='r:gz') as tf:
        d = tf.extractfile(MEMBER).read()
    got = hashlib.md5(d).hexdigest()
    if got != OBJDUMP_MD5:
        raise SystemExit(f'mkopcodes: {MEMBER}: MD5 {got}, expected {OBJDUMP_MD5}')
    e = Elf32(d)
    n = e.u32(e.syms['bfd_mips_num_builtin_opcodes'][0])
    base, size = e.syms['mips_builtin_opcodes']
    if size != n * 24:
        raise SystemExit(f'mkopcodes: table size {size} != {n} * 24')
    ops = []
    for i in range(n):
        f = [e.u32(base + i * 24 + 4 * k) for k in range(6)]
        ops.append({'name': e.cstr(f[0]), 'args': e.cstr(f[1]), 'match': f[2],
                    'mask': f[3], 'pinfo': f[4], 'membership': f[5]})
    base, size = e.syms['mips_arch_choices']
    arch = {}
    for i in range(size // 36):
        f = [e.u32(base + i * 36 + 4 * k) for k in range(9)]
        arch[e.cstr(f[0])] = {'processor': f[3], 'isa': f[4]}
    names = {}
    for sym, cnt in NAME_TABLES.items():
        va, sz = e.syms[sym]
        if sz != cnt * 4:
            raise SystemExit(f'mkopcodes: {sym} size {sz} != {cnt} * 4')
        names[sym.split('.')[0]] = [e.cstr(e.u32(va + 4 * k)) for k in range(cnt)]
    return {'source': f'psp-gcc-1.3.1 {MEMBER} md5 {OBJDUMP_MD5}',
            'opcodes': ops, 'arch': arch, 'names': names}


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    t = extract(sys.argv[1])
    with open(sys.argv[2], 'w') as f:
        json.dump(t, f, indent=0)
    print(f"mkopcodes: {len(t['opcodes'])} opcodes, allegrex arch {t['arch'].get('allegrex')}")
