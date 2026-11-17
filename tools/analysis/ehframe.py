#!/usr/bin/env python3
""".eh_frame parser for the PSP module.

    from ehframe import parse
    cies, fdes = parse(prx)

CIE: addr, length, aug ('zP', 'zPL' or ''), personality (module address or None)
FDE: addr, cie (index into cies), start, size, lsda (address or None)
     start is None for a dead FDE: pc_begin stored as 0 with no relocation,
     which the linker leaves for a function whose section it discarded
     (a duplicate .gnu.linkonce copy).

Every pointer field read here (personality, pc_begin, LSDA) must carry an
R_MIPS_32 relocation, and the FDE's CIE pointer must point at a parsed CIE;
parse() raises otherwise.  Pointer encodings are checked to be absptr
(augmentation data P byte 0x00, no 'R'), which is what this binary uses.
"""
import struct
from collections import namedtuple

CIE = namedtuple('CIE', 'addr length aug personality')
FDE = namedtuple('FDE', 'addr cie start size lsda')


def uleb(d, o):
    v = s = 0
    while True:
        b = d[o]
        o += 1
        v |= (b & 0x7f) << s
        s += 7
        if not b & 0x80:
            return v, o


def parse(prx):
    sec = prx.section('.eh_frame')
    d = prx.read(sec.addr, sec.size)
    cies, fdes, cie_at = [], [], {}

    def reloc_word(off, dead_ok=False):
        a = sec.addr + off
        rs = [r for r in prx.reloc_at(a) if r.type_id == 2]
        if not rs and dead_ok and prx.word(a) == 0:
            return None
        if len(rs) != 1:
            raise ValueError(f'.eh_frame pointer at {a:#x} has no R_MIPS_32')
        return rs[0].target

    o = 0
    while o < len(d):
        ln, = struct.unpack_from('<I', d, o)
        if ln == 0:                      # zero terminator (crtend.o)
            break
        cid, = struct.unpack_from('<I', d, o + 4)
        body = o + 8
        if cid == 0:
            aug_end = d.index(b'\0', o + 9)
            aug = d[o + 9:aug_end].decode()
            q = aug_end + 1
            _ca, q = uleb(d, q)
            _da, q = uleb(d, q)          # sleb, value unused
            q += 1                        # return-address column (1 byte, v1)
            pers = None
            if aug.startswith('z'):
                _alen, q = uleb(d, q)
                for ch in aug[1:]:
                    if ch == 'P':
                        if d[q] != 0:
                            raise ValueError(f'CIE {sec.addr + o:#x}: personality encoding {d[q]:#x}')
                        pers = reloc_word(q + 1)
                        q += 5
                    elif ch == 'L':
                        if d[q] != 0:
                            raise ValueError(f'CIE {sec.addr + o:#x}: LSDA encoding {d[q]:#x}')
                        q += 1
                    else:
                        raise ValueError(f'CIE {sec.addr + o:#x}: augmentation {aug!r}')
            elif aug:
                raise ValueError(f'CIE {sec.addr + o:#x}: augmentation {aug!r}')
            cie_at[o] = len(cies)
            cies.append(CIE(sec.addr + o, ln, aug, pers))
        else:
            ci = cie_at.get(o + 4 - cid)
            if ci is None:
                raise ValueError(f'FDE {sec.addr + o:#x}: CIE pointer to no CIE')
            start = reloc_word(body, dead_ok=True)
            size, = struct.unpack_from('<I', d, body + 4)
            lsda = None
            if cies[ci].aug.startswith('z'):
                alen, q = uleb(d, body + 8)
                if 'L' in cies[ci].aug:
                    if alen != 4:
                        raise ValueError(f'FDE {sec.addr + o:#x}: LSDA length {alen}')
                    lsda = reloc_word(q, dead_ok=True)   # 0 = no LSDA
            fdes.append(FDE(sec.addr + o, ci, start, size, lsda))
        o += 4 + ln
    return cies, fdes


def landing_pads(prx, fde):
    """Landing-pad addresses from an FDE's LSDA (.gcc_except_table).

    GCC 3.3 layout: LPStart encoding (0xff = omitted, so LPStart is the
    function start), TType encoding (0xff = none, else a uleb offset
    follows), call-site encoding (must be 0x01, uleb128), call-site table
    length, then (start, length, landing pad, action) uleb quadruples.
    """
    if fde.lsda is None or fde.start is None:
        return []
    d = prx.read(fde.lsda, 4096)
    if d[0] != 0xff:
        raise ValueError(f'LSDA {fde.lsda:#x}: LPStart encoding {d[0]:#x}')
    q = 1
    tt = d[q]
    q += 1
    if tt != 0xff:
        if tt != 0x00:
            raise ValueError(f'LSDA {fde.lsda:#x}: TType encoding {tt:#x}')
        _off, q = uleb(d, q)
    if d[q] != 0x01:
        raise ValueError(f'LSDA {fde.lsda:#x}: call-site encoding {d[q]:#x}')
    n, q = uleb(d, q + 1)
    end, pads = q + n, []
    while q < end:
        _s, q = uleb(d, q)
        _l, q = uleb(d, q)
        lp, q = uleb(d, q)
        _a, q = uleb(d, q)
        if lp:
            if lp >= fde.size:
                raise ValueError(f'LSDA {fde.lsda:#x}: landing pad {lp:#x} outside function')
            pads.append(fde.start + lp)
    if q != end:
        raise ValueError(f'LSDA {fde.lsda:#x}: call-site table overrun')
    return sorted(set(pads))
