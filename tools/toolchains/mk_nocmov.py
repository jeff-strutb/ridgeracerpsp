#!/usr/bin/env python3
"""Build psp-gcc-1.3.1-nocmov: psp-gcc 1.3.1 with conditional moves disabled.

Why: retail BOOT.BIN contains zero movz/movn/movt/movf (integer or FP) in 375k instructions,
while stock 1.3.1 and 1.7.1 emit them for two-way selects (stock enables them for
mips_arch == allegrex). GCC 3.3 reaches a conditional move two ways, and both are cut:
  1. init_all_optabs() stores the movsicc/movdicc/movsfcc/movdfcc insn codes (0x22d..0x230)
     into movcc_gen_code[]; those four stores become NOPs, so emit_conditional_move() and
     can_conditionally_move_p() see no pattern.
  2. if-conversion also builds (set x (if_then_else ...)) directly and asks recog(); every
     recog_N return site for a pattern whose template is mov%B/mov%b/mov%T/mov%t
     (insn codes 0x6f, 0x156..0x161) is changed to return -1 (no match).
If-conversion then falls back to the store-flag forms retail shows (sltiu/negu/and).

This is a RECONSTRUCTION of the retail compiler's behaviour (psp-1.5.1), validated only by the
control set in src/control. Sites are located by disassembly (host objdump), and every patch
checks the exact original bytes first.
Usage: python3 tools/toolchains/mk_nocmov.py
"""
import os
import re
import shutil
import struct
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, 'build/toolchains/psp-gcc-1.3.1')
DST = os.path.join(ROOT, 'build/toolchains/psp-gcc-1.3.1-nocmov')
CC1_DIR = 'lib/gcc-lib/psp/3.3.3+allegrex-2.2.1-psp-1.3.1'

OPTAB_CODES = (0x22d, 0x22e, 0x22f, 0x230)  # movsicc movdicc movsfcc movdfcc
CMOV_INSNS = (0x6f,) + tuple(range(0x156, 0x162))  # patterns emitting mov[zntf]


def vaddr_to_off(d, va):
    phoff, = struct.unpack_from('<I', d, 0x1c)
    phnum, = struct.unpack_from('<H', d, 0x2c)
    for i in range(phnum):
        t, off, vaddr, _, filesz, _, _, _ = struct.unpack_from('<8I', d, phoff + i * 32)
        if t == 1 and vaddr <= va < vaddr + filesz:
            return off + va - vaddr
    raise ValueError(f'0x{va:x} not in a loaded segment')


def sites(path):
    """(vaddr, kind, code) for every patch site, found by disassembling the binary."""
    dis = subprocess.run(['objdump', '-d', '--no-show-raw-insn', path], capture_output=True, text=True, check=True).stdout
    fn, out = None, []
    head = re.compile(r'^([0-9a-f]+) <([^>]+)>:')
    ins = re.compile(r'^\s*([0-9a-f]+):\s+movl\s+\$0x([0-9a-f]+), (%edx|0x[0-9a-f]+)')
    for line in dis.splitlines():
        m = head.match(line)
        if m:
            fn = m.group(2)
            continue
        m = ins.match(line)
        if not m or fn is None:
            continue
        va, code, dst = int(m.group(1), 16), int(m.group(2), 16), m.group(3)
        if fn == 'init_all_optabs' and code in OPTAB_CODES and dst != '%edx':
            out.append((va, 'optab', code))
        elif re.fullmatch(r'recog(_\d+)?', fn) and dst == '%edx' and code in CMOV_INSNS:
            out.append((va, 'recog', code))
    return out


def patch(path):
    d = bytearray(open(path, 'rb').read())
    found = sites(path)
    optab = sorted(c for _, k, c in found if k == 'optab')
    recog = sorted(c for _, k, c in found if k == 'recog')
    if optab != sorted(OPTAB_CODES) or recog != sorted(CMOV_INSNS):
        raise SystemExit(f'{path}: unexpected sites optab={[hex(c) for c in optab]} recog={[hex(c) for c in recog]}')
    for va, kind, code in found:
        o = vaddr_to_off(d, va)
        if kind == 'optab':  # c7 05 <addr32> <imm32>  ->  10 x nop
            if d[o:o + 2] != b'\xc7\x05' or d[o + 6:o + 10] != struct.pack('<I', code):
                raise SystemExit(f'{path}: bytes at 0x{va:x} are not movl $0x{code:x},mem')
            d[o:o + 10] = b'\x90' * 10
        else:  # ba <imm32>  ->  ba ff ff ff ff
            if d[o:o + 5] != b'\xba' + struct.pack('<I', code):
                raise SystemExit(f'{path}: bytes at 0x{va:x} are not movl $0x{code:x},%edx')
            d[o + 1:o + 5] = b'\xff\xff\xff\xff'
    open(path, 'wb').write(d)
    return len(optab), len(recog)


def main():
    if not os.path.isdir(SRC):
        raise SystemExit(f'{SRC} missing: unpack dist/psp-gcc-1.3.1.tar.gz there first')
    if os.path.isdir(DST):
        shutil.rmtree(DST)
    shutil.copytree(SRC, DST, symlinks=True)
    for name in ('cc1', 'cc1plus'):
        n_opt, n_rec = patch(os.path.join(DST, CC1_DIR, name))
        print(f'{name}: {n_opt} optab stores NOPed, {n_rec} recog returns set to -1')


if __name__ == '__main__':
    main()
