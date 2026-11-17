#!/usr/bin/env python3
"""Function map of the USA BOOT.BIN -> config/us/funcs.csv.

    funcmap.py              build, reconcile, write config/us/funcs.csv
    funcmap.py --check      rebuild and compare with the committed CSV
    funcmap.py --selftest   prove the reconciliation catches planted faults

Function starts are the union of:
  fde        pc_begin of a live .eh_frame FDE; size = pc_range (exact)
  after-fde  the first word after a live FDE range, or the first word of an
             executable section.  Live FDE ranges are proven to abut real
             code with no padding (no gap between FDE ranges is all zero),
             so the word after an FDE function begins another function.
  jal        target of a relocated jal
  hilo       target of a relocated HI16/LO16 pair (address taken in code)
  data:SEC   target of a relocated word in a data section SEC (vtables,
             .ctors/.dtors, callback tables), excluding jump-table words
  entry      module_start from .rodata.sceResident
  stub       one 8-byte import stub per function counted in .lib.stub

Jump tables: every `jr rX` (rX != ra) is matched against the shape
lui/addiu (HI16/LO16 pair -> base) ... addu ... lw rX,0(..) ... jr rX.  The
table runs from base over consecutive relocated words that point into .text,
up to the sltiu bound when one guards the jump, and never across another
table's base.  Those words are table words: never function starts.  Every
table entry must land inside the function holding its jr, or the build
fails.

  reach      first non-zero word after the reachable code of a non-FDE
             function whose remaining words are all unreachable (see
             split_unreachable for the calibration that justifies it)

A function ends where the next start begins (end=next-start), except an
FDE function, which ends at pc_begin + pc_range (end=fde), an import stub
(8 bytes, end=stub), and a function whose unreachable tail was split off
(end=reach: just after its last reachable word).

Reconciliation (printed, and kept in the report):
  * every `jr ra` lies inside exactly one function;
  * per function, words not reachable from its start by intraprocedural
    control flow (branches, jump tables, fall-through; calls return; `j`
    outside the function is a tail call) are listed as unexplained;
  * jal targets are never inside an FDE range except at its start.
"""
import bisect
import csv
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE)]
from prx import Prx                      # noqa: E402
from ehframe import parse as parse_eh, landing_pads    # noqa: E402
from allegrex import decode              # noqa: E402

ROOT = HERE.parent.parent
CSV = ROOT / 'config' / 'us' / 'funcs.csv'
CODE_SECTIONS = ('.init', '.text', '.fini', '.sceStub.text')


class FuncMapError(Exception):
    pass


def jump_tables(p, text):
    """Return list of dicts {jr, base, n, entries[]} for every jr rX, rX != ra."""
    found = []
    for a in range(text.addr, text.end, 4):
        i = decode(p.word(a), a)
        if i.name != 'jr' or i.rs == 31:
            continue
        lw = decode(p.word(a - 4), a - 4)
        ad = decode(p.word(a - 8), a - 8)
        if not (lw.name == 'lw' and lw.rt == i.rs and lw.imm == 0
                and ad.name == 'addu' and lw.rs == ad.rd):
            raise FuncMapError(f'jr {a:#x}: not the jump-table shape')
        base = None
        for k in range(3, 12):
            x = a - 4 * k
            j = decode(p.word(x), x)
            lo = [r for r in p.reloc_at(x) if r.type_id == 6 and r.how == 'pair']
            if lo and j.name == 'addiu' and j.rt in (ad.rs, ad.rt):
                base = lo[0].target
                break
        if base is None:
            raise FuncMapError(f'jr {a:#x}: no table base')
        bound = None
        for k in range(3, 30):
            x = a - 4 * k
            j = decode(p.word(x), x)
            if j.name == 'sltiu':
                bound = j.word & 0xffff
                break
        found.append({'jr': a, 'base': base, 'bound': bound})
    bases = {t['base'] for t in found}
    for t in found:
        ents, x = [], t['base']
        while t['bound'] is None or len(ents) < t['bound']:
            rl = [r for r in p.reloc_at(x) if r.type_id == 2]
            if not rl or (ents and x in bases):
                break
            tgt = rl[0].target
            if not (text.addr <= tgt < text.end):
                break
            ents.append((x, tgt))
            x += 4
        if t['bound'] is not None and len(ents) != t['bound']:
            raise FuncMapError(f"jr {t['jr']:#x}: {len(ents)} entries, bound {t['bound']}")
        t['entries'] = ents
        t['n'] = len(ents)
    return found


def lib_stubs(p):
    """(addr, libname) of every import stub, from the .lib.stub records."""
    s = p.section('.lib.stub')
    out = []
    for a in range(s.addr, s.end, 20):
        name_p, _ver, attr, _nids, stubs = (p.word(a + 4 * k) for k in range(5))
        if (attr & 0xff) != 5:
            raise FuncMapError(f'.lib.stub record {a:#x}: size {attr & 0xff} words')
        nfunc = attr >> 16
        name = p.read(name_p, 32).split(b'\0')[0].decode()
        out += [(stubs + 8 * k, name) for k in range(nfunc)]
    return out


def build(p):
    cies, fdes = parse_eh(p)
    secs = [p.section(n) for n in CODE_SECTIONS]
    text = p.section('.text')
    live = sorted((f for f in fdes if f.start is not None), key=lambda f: f.start)
    ev = defaultdict(set)
    fde_end = {}
    pads = {}
    for f in live:
        ev[f.start].add('fde')
        fde_end[f.start] = f.start + f.size
        pads[f.start] = landing_pads(p, f)
    for s in secs:
        if s.name != '.sceStub.text':
            ev[s.addr].add('after-fde' if s.name == '.text' else 'section')
    for f in live:
        e = f.start + f.size
        if e < text.end:
            ev[e].add('after-fde')

    tables = jump_tables(p, text)
    table_words = {x for t in tables for x, _ in t['entries']}

    def in_code(a):
        s = p.section_at(a)
        return s is not None and s.name in CODE_SECTIONS

    for r in p.relocs:
        if r.target is None or not in_code(r.target):
            continue
        if r.type_id == 4:
            if decode(p.word(r.addr), r.addr).name == 'jal':
                ev[r.target].add('jal')
        elif r.type_id == 5 or r.type_id == 6:
            if r.how == 'pair':
                ev[r.target].add('hilo')
        elif r.section != '.eh_frame' and r.addr not in table_words:
            if r.section == '.lib.stub':
                continue          # stub-table pointers; stubs come from lib_stubs
            ev[r.target].add('data:' + r.section)
    res = p.section('.rodata.sceResident')
    for r in p.relocs:
        if r.section == res.name and r.target == p.entry:
            ev[p.entry].add('entry')
    stubs = lib_stubs(p)
    stub_sec = p.section('.sceStub.text')
    if len(stubs) * 8 != stub_sec.size:
        raise FuncMapError(f'{len(stubs)} stubs != .sceStub.text size {stub_sec.size}')
    stub_lib = {}
    for a, lib in stubs:
        ev[a].add('stub')
        stub_lib[a] = lib

    starts = sorted(ev)
    for a in starts:
        if a % 4 or not in_code(a):
            raise FuncMapError(f'start {a:#x} not an aligned code address')
    funcs = []
    for k, a in enumerate(starts):
        sec = p.section_at(a)
        nxt = starts[k + 1] if k + 1 < len(starts) else sec.end
        nxt = min(nxt, sec.end)
        if a in fde_end:
            end, how = fde_end[a], 'fde'
            if end > nxt:
                raise FuncMapError(f'FDE {a:#x}-{end:#x} overlaps start {nxt:#x}')
        elif a in stub_lib:
            end, how = a + 8, 'stub'
        else:
            end, how = nxt, 'next-start' if nxt < sec.end else 'section-end'
        funcs.append({'addr': a, 'size': end - a, 'section': sec.name, 'evidence': ev[a],
                      'end': how, 'lib': stub_lib.get(a, ''), 'pads': pads.get(a, [])})
    funcs, padding = split_unreachable(p, funcs, {t['jr']: t for t in tables})
    # Every jump table entry must stay inside its jr's function.
    fstarts = [f['addr'] for f in funcs]
    for t in tables:
        f = funcs[bisect.bisect_right(fstarts, t['jr']) - 1]
        for _, tgt in t['entries']:
            if not (f['addr'] < tgt < f['addr'] + f['size']):
                raise FuncMapError(f"table {t['base']:#x} entry {tgt:#x} outside "
                                   f"function {f['addr']:#x}")
    # jal never lands inside an FDE range except at its start.
    fde_starts = [f.start for f in live]
    for r in p.relocs:
        if r.type_id == 4 and r.target is not None and 'jal' in ev.get(r.target, ()):
            k = bisect.bisect_right(fde_starts, r.target) - 1
            if k >= 0 and live[k].start < r.target < live[k].start + live[k].size:
                raise FuncMapError(f'jal into FDE body {r.target:#x}')
    return {'funcs': funcs, 'tables': tables, 'padding': padding,
            'live_fdes': live, 'dead_fdes':
            [f for f in fdes if f.start is None], 'cies': cies}


def reachable(p, f, tables_by_jr):
    """Set of word addresses reachable from f's start (and its landing pads)
    inside f."""
    lo, hi = f['addr'], f['addr'] + f['size']
    seen, work = set(), [lo] + f.get('pads', [])
    while work:
        a = work.pop()
        while lo <= a < hi and a not in seen:
            seen.add(a)
            i = decode(p.word(a), a)
            succ, stop = [], False
            if i.has_delay:
                seen.add(a + 4)
                if i.is_branch:
                    succ.append(i.target)
                    if i.unconditional:
                        stop = True
                elif i.name == 'j':
                    succ.append(i.target)
                    stop = True
                elif i.name == 'jr':
                    succ += [t for _, t in tables_by_jr.get(a, {}).get('entries', [])]
                    stop = True
                nxt = a + 8          # calls and conditional branches fall through
            else:
                nxt = a + 4
            work += [s for s in succ if lo <= s < hi]
            if stop:
                break
            a = nxt
    return seen


def split_unreachable(p, funcs, tby):
    """Split off code a function cannot reach.

    Calibration: in every live-FDE function (exact boundaries from the
    compiler) every word is reachable from the entry or a landing pad.  So
    when a non-FDE function's reachable words form a prefix [addr, X) and
    nothing in [X, end) is reachable, [X, end) is not part of it.  Leading
    zero words of that tail are padding (in no function); the first
    non-zero word starts a new function with evidence 'reach', which is
    examined the same way in turn.  A function whose unreachable words are
    not a single tail is left whole and reported by reconcile().
    """
    out, padding, work = [], [], list(funcs)
    work.reverse()
    while work:
        f = work.pop()
        out.append(f)
        if 'fde' in f['evidence'] or f['end'] == 'stub':
            continue
        r = reachable(p, f, tby)
        lo, hi = f['addr'], f['addr'] + f['size']
        x = lo
        while x in r:
            x += 4
        if x >= hi or any(a in r for a in range(x, hi, 4)):
            continue
        y = x
        while y < hi and p.word(y) == 0:
            y += 4
        f['size'], f['end'] = x - lo, 'reach'
        if y > x:
            padding.append((x, y))
        if y < hi:
            work.append({'addr': y, 'size': hi - y, 'section': f['section'],
                         'evidence': {'reach'}, 'end': 'next-start',
                         'lib': '', 'pads': []})
    return out, padding


def reconcile(p, m):
    funcs, tables = m['funcs'], m['tables']
    tby = {t['jr']: t for t in tables}
    fstarts = [f['addr'] for f in funcs]
    jrra = []
    for name in CODE_SECTIONS:
        s = p.section(name)
        jrra += [a for a in range(s.addr, s.end, 4) if p.word(a) == 0x03e00008]
    per = Counter()
    outside = []
    for a in jrra:
        k = bisect.bisect_right(fstarts, a) - 1
        f = funcs[k] if k >= 0 else None
        if f is None or not (f['addr'] <= a < f['addr'] + f['size']):
            outside.append(a)
        else:
            per[f['addr']] += 1
    unexplained = []
    for f in funcs:
        if f['end'] == 'stub':
            continue
        r = reachable(p, f, tby)
        dead = [a for a in range(f['addr'], f['addr'] + f['size'], 4) if a not in r]
        if dead:
            # group into runs
            run = [dead[0], dead[0]]
            for a in dead[1:]:
                if a == run[1] + 4:
                    run[1] = a
                else:
                    unexplained.append((f['addr'], run[0], run[1] + 4))
                    run = [a, a]
            unexplained.append((f['addr'], run[0], run[1] + 4))
    return {'jrra': jrra, 'outside': outside, 'per': per, 'unexplained': unexplained}


def write_csv(m, path=CSV):
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, 'w', newline='') as fh:
        w = csv.writer(fh, lineterminator='\n')
        w.writerow(['addr', 'size', 'section', 'end', 'evidence', 'import'])
        for f in m['funcs']:
            w.writerow([f'0x{f["addr"]:06x}', f['size'], f['section'], f['end'],
                        ';'.join(sorted(f['evidence'])), f['lib']])


def load(path=CSV):
    """Rows of funcs.csv as dicts with int addr/size and evidence as a set."""
    out = []
    with open(path) as fh:
        for row in csv.DictReader(fh):
            row['addr'] = int(row['addr'], 16)
            row['size'] = int(row['size'])
            row['evidence'] = set(row['evidence'].split(';')) if row['evidence'] else set()
            out.append(row)
    return out


def report(p, m, rc):
    funcs = m['funcs']
    print(f"functions: {len(funcs)}  bytes: {sum(f['size'] for f in funcs)}")
    c = Counter(f['end'] for f in funcs)
    print('end known by:', dict(c))
    only = Counter()
    for f in funcs:
        e = {x.split(':')[0] for x in f['evidence']}
        only['+'.join(sorted(e))] += 1
    print('start evidence combinations:')
    for k, v in only.most_common():
        print(f'  {v:6d} {k}')
    print(f"jump tables: {len(m['tables'])}, words {sum(t['n'] for t in m['tables'])}")
    print(f"padding (zero words in no function): {len(m['padding'])} runs, "
          f"{sum(b - a for a, b in m['padding'])} bytes")
    print(f"FDEs: {len(m['live_fdes'])} live, {len(m['dead_fdes'])} dead; CIEs {len(m['cies'])}")
    per = rc['per']
    print(f"jr ra: {len(rc['jrra'])} total, {len(rc['outside'])} outside any function")
    dist = Counter(per.get(f['addr'], 0) for f in funcs if f['end'] != 'stub')
    print('jr ra per function (non-stub):', sorted(dist.items()))
    nonfde = [f for f in funcs if 'fde' not in f['evidence'] and f['end'] != 'stub']
    distn = Counter(per.get(f['addr'], 0) for f in nonfde)
    print('jr ra per non-FDE function:', sorted(distn.items()))
    ub = sum(b - a for _, a, b in rc['unexplained'])
    nf = len({f for f, _, _ in rc['unexplained']})
    print(f"unexplained (unreachable from its function's start): {len(rc['unexplained'])} runs, "
          f"{ub} bytes, in {nf} functions")
    nz = [(f, a, b) for f, a, b in rc['unexplained']
          if any(p.word(x) for x in range(a, b, 4))]
    print(f"  of which contain non-zero words: {len(nz)} runs, {sum(b - a for _, a, b in nz)} bytes")
    jrra_unreach = sum(1 for f, a, b in rc['unexplained'] for x in range(a, b, 4)
                       if p.word(x) == 0x03e00008)
    print(f"  jr ra inside unreachable runs: {jrra_unreach}")
    return nz


def selftest():
    p = Prx.from_ref('us')
    m = build(p)
    rc = reconcile(p, m)
    fails = []
    if rc['outside']:
        fails.append(f"{len(rc['outside'])} jr ra outside functions")
    # Known answers from the brief: FDE coverage and count.
    cov = sum(f.size for f in m['live_fdes']) + sum(f.size for f in m['dead_fdes'])
    if cov != 1108012 or len(m['live_fdes']) + len(m['dead_fdes']) != 3977:
        fails.append(f'FDE coverage {cov} / count')
    # Planted fault 1: drop the jump-table filter, so table words become
    # starts; the table check must then fire.
    orig = jump_tables
    globals()['jump_tables'] = lambda p, t: [dict(t2, entries=[], n=0) for t2 in orig(p, t)]
    try:
        build(p)
        print('planted: tables ignored -> build accepted it')
        fails.append('ignoring jump tables was not detected')
    except FuncMapError as e:
        print(f'planted: tables ignored -> refused: {e}')
    finally:
        globals()['jump_tables'] = orig
    # Planted fault 2: merge a jal-only function into the non-FDE function
    # before it; reconcile() must report the merged-in code as unreachable.
    fl = m['funcs']
    k = next(k for k in range(1, len(fl)) if fl[k]['evidence'] == {'jal'}
             and 'fde' not in fl[k - 1]['evidence'] and fl[k - 1]['end'] == 'next-start')
    m2 = dict(m, funcs=fl[:k - 1] + [dict(fl[k - 1], size=fl[k - 1]['size'] + fl[k]['size'])]
              + fl[k + 1:])
    rc2 = reconcile(p, m2)
    print(f"planted: merged {fl[k]['addr']:#x} into {fl[k - 1]['addr']:#x} -> "
          f"{len(rc2['unexplained'])} unexplained runs")
    if not rc2['unexplained']:
        fails.append('planted merge not reported')
    # Planted fault 3: drop a function; its jr ra must show up as outside.
    k = next(k for k, f in enumerate(fl) if rc['per'].get(f['addr']))
    rc3 = reconcile(p, dict(m, funcs=fl[:k] + fl[k + 1:]))
    print(f"planted: dropped {fl[k]['addr']:#x} -> {len(rc3['outside'])} jr ra outside")
    if not rc3['outside']:
        fails.append('planted drop not reported')
    if rc['unexplained']:
        fails.append(f"{len(rc['unexplained'])} unexplained runs in the reference map")
    for f in fails:
        print('FAIL', f)
    print('selftest:', 'FAIL' if fails else 'PASS')
    return 1 if fails else 0


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    p = Prx.from_ref('us')
    m = build(p)
    rc = reconcile(p, m)
    report(p, m, rc)
    if argv[1:] == ['--check']:
        tmp = CSV.with_suffix('.check')
        write_csv(m, tmp)
        same = tmp.read_text() == CSV.read_text()
        tmp.unlink()
        print('funcs.csv', 'matches' if same else 'DIFFERS from a fresh build')
        return 0 if same else 1
    write_csv(m)
    print(f'wrote {CSV.relative_to(ROOT)}')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
