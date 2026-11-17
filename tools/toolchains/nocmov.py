#!/usr/bin/env python3
"""Make a copy of a psp-gcc cc1/cc1plus in which Allegrex has no integer conditional move.

Runs on the compile host (plain python3, no dependencies): nocmov.py IN OUT

What it changes (docs/COMPILER.md has the evidence). In these Allegrex builds of GCC 3.3.3 the
machine description makes movz/movn available when
    ISA_HAS_CONDMOVE (MIPS IV/32/64; false for Allegrex, which is MIPS II)
    || ISA_HAS_INT_CONDMOVE (compiled as mips_arch == PROCESSOR_ALLEGREX, the psp patch;
                             stock GCC 3.3.3 defines it as 0)
That condition is compiled into two places, and both are needed:
  1. init_all_optabs: `movcc_gen_code[SImode] = CODE_FOR_movsicc` (and the DImode twin),
     which lets if-conversion (ce1/ce2) emit conditional moves;
  2. recog: the integer movz/movn define_insns (`*mips.md` patterns printing mov%B4/mov%b4 on
     general registers), which combine can match directly (seen: insn 59 of
     StreamChannels.c.19.combine became `*mips.md:11389` with the optab entry removed).
The tool makes the Allegrex arm false at exactly those sites and nowhere else:
  1. the 10-byte store `movl $CODE_FOR_mov{si,di}cc, movcc_gen_code+4*mode` becomes NOPs
     (init_optabs has already set every entry to CODE_FOR_nothing);
  2. in recog_*, each `cmp $0x6,%reg` on a just-loaded mips_arch that guards a return of one
     of those insn codes gets its immediate changed to 0xff (-1, no processor), so the
     pattern is unrecognised for Allegrex. The MIPS IV arm of these guards is left as it was.
The optab stores are shared with the MIPS IV arm, so they go entirely; that arm is never
taken for Allegrex. The result is what a GCC 3.3.3 built with ISA_HAS_INT_CONDMOVE 0 for
Allegrex would do.
All sites are found by symbol and insn_data name, never by fixed address; any surprise (no
site for a code, a site not shaped as expected) stops the tool without writing.
"""
import hashlib
import re
import struct
import sys

MODES = {'movsicc': 4, 'movdicc': 5}   # GCC 3.3 machmode.def: VOID, BI, QI, HI, SI, DI
INSN_DATA_SIZE = 20                    # struct insn_data: name, output, genfun, operand, 4 chars
PROCESSOR_ALLEGREX = 6                 # the value init_all_optabs and recog compare mips_arch with


def main():
    src, dst = sys.argv[1], sys.argv[2]
    d = bytearray(open(src, 'rb').read())
    assert d[:4] == b'\x7fELF' and d[4] == 1 and d[5] == 1, 'not an ELF32 little-endian file'
    shoff, = struct.unpack_from('<I', d, 0x20)
    shnum, = struct.unpack_from('<H', d, 0x30)
    sh = [struct.unpack_from('<10I', d, shoff + i * 40) for i in range(shnum)]
    phoff, = struct.unpack_from('<I', d, 0x1c)
    phnum, = struct.unpack_from('<H', d, 0x2c)
    ph = [struct.unpack_from('<8I', d, phoff + i * 32) for i in range(phnum)]

    def off(va):
        for p in ph:
            if p[0] == 1 and p[2] <= va < p[2] + p[4]:
                return p[1] + va - p[2]
        raise SystemExit('address %#x not in a loaded segment' % va)

    def cstr(va):
        o = off(va)
        return bytes(d[o:d.index(b'\0', o)]).decode('latin-1')

    syms, funcs = {}, set()
    for s in sh:
        if s[1] == 2:  # SHT_SYMTAB
            strtab = sh[s[6]]
            for i in range(0, s[5], 16):
                nm, val, size, info = struct.unpack_from('<IIIB', d, s[4] + i)
                name = bytes(d[strtab[4] + nm:d.index(b'\0', strtab[4] + nm)]).decode('latin-1')
                if size:
                    syms[name] = (val, size)
                    if info & 0xf == 2:  # STT_FUNC
                        funcs.add(name)
    for need in ('insn_data', 'movcc_gen_code', 'init_all_optabs', 'mips_arch'):
        if need not in syms:
            raise SystemExit('symbol %s not found' % need)

    # insn codes: the two optab expanders, and the integer movz/movn define_insns.
    base, size = syms['insn_data']
    names, cmove = {}, []
    for i in range(size // INSN_DATA_SIZE):
        name, out, _, _, _, _, nalt, fmt = struct.unpack_from('<IIIIbbbb', d, off(base + i * INSN_DATA_SIZE))
        names[cstr(name)] = i
        if fmt == 2:  # INSN_OUTPUT_FORMAT_MULTI
            tpl = [cstr(struct.unpack_from('<I', d, off(out + 4 * k))[0]) for k in range(nalt)]
            if all(re.match(r'mov%[Bb]4\t', t) for t in tpl):
                cmove.append(i)
    log = []

    # 1. the optab stores
    fva, fsize = syms['init_all_optabs']
    fo = off(fva)
    for exp, mode in MODES.items():
        pat = b'\xc7\x05' + struct.pack('<II', syms['movcc_gen_code'][0] + 4 * mode, names[exp])
        hits = [i for i in range(fsize) if d.startswith(pat, fo + i)]
        if len(hits) != 1:
            raise SystemExit('%s: expected one optab store, found %d' % (exp, len(hits)))
        d[fo + hits[0]:fo + hits[0] + len(pat)] = b'\x90' * len(pat)
        log.append('init_all_optabs+%#x: removed movcc_gen_code[%d] = %d (%s)' % (hits[0], mode, names[exp], exp))

    # 2. recog guards. Load of mips_arch into eax (a1 addr) or another reg (8b /r addr), then
    # cmp $6 (83 f8+r 06), then within 40 bytes `mov $code,%edx|%eax` (ba|b8 code32).
    arch = struct.pack('<I', syms['mips_arch'][0])
    loads = [(b'\xa1' + arch, 0)] + [(b'\x8b' + bytes([0x05 | (r << 3)]) + arch, r) for r in range(8)]
    found = {c: 0 for c in cmove}
    for name, (va, sz) in sorted(syms.items()):
        if not name.startswith('recog') or name not in funcs:
            continue
        o = off(va)
        body = bytes(d[o:o + sz])
        for lpat, reg in loads:
            start = 0
            while True:
                i = body.find(lpat, start)
                if i < 0:
                    break
                start = i + 1
                j = i + len(lpat)
                if body[j:j + 3] != bytes([0x83, 0xf8 + reg, PROCESSOR_ALLEGREX]):
                    continue
                window = body[j + 3:j + 3 + 40]
                codes = [c for c in cmove
                         if (b'\xba' + struct.pack('<I', c)) in window
                         or (b'\xb8' + struct.pack('<I', c)) in window]
                if not codes:
                    continue
                if len(codes) != 1:
                    raise SystemExit('%s+%#x: guard near several codes %r' % (name, j, codes))
                d[o + j + 2] = 0xff
                found[codes[0]] += 1
                log.append('%s+%#x: cmp $6 -> cmp $-1 on mips_arch, guarding insn %d (%s)' % (
                    name, j, codes[0], [n for n, k in names.items() if k == codes[0]][0]))
    missing = [c for c, n in found.items() if n == 0]
    if missing or not cmove:
        raise SystemExit('no recog guard found for insn codes %r' % missing)
    open(dst, 'wb').write(d)
    print('%s -> %s: integer cmove insns %r; sha256 in %s out %s' % (
        src, dst, cmove, hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16],
        hashlib.sha256(bytes(d)).hexdigest()[:16]))
    for l in log:
        print('  ' + l)


if __name__ == '__main__':
    main()
