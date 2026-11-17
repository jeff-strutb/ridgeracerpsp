#!/usr/bin/env python3
"""M2 image gate: rebuild the USA BOOT.BIN from retail plus every EXACT @implements function.

    tools/image.py [--json] [--no-cache] [--replace SRC=COPY ...] [--plant-drop 0xADDR ...]

Steps:
  1. Compile every real translation unit (src/ outside src/control/) through cc.py with the
     pinned compiler (content cache; --no-cache recompiles) and grade every @implements tag in
     them with tools/score.py (one Grader for the whole run, so an object data item must map
     to one retail address across all functions).
  2. Start from the retail file bytes.  For each EXACT function, take its compiled bytes from
     the object, write every relocated field from the resolved target (the target's segment
     base is subtracted, as in retail's relocations: R_MIPS_26 (v >> 2), HI16 (v + 0x8000) >> 16,
     LO16 v & 0xffff, R_MIPS_32 v), and write the result at the function's file offset.
  3. Compare the whole file with retail.

--files SRC... limits the gate to those real files (their @implements are the count to meet);
the full gate is the one without it.

Exit status 1 (gate red) on any of:
  - a differing byte anywhere in the file;
  - a placed function that is not EXACT, or whose compiled size differs from funcs.csv;
  - two placed functions that overlap;
  - fewer functions placed than @implements tags in real files, or none placed.
Exit status 2 when the reference fails its MD5 check or RRPSP_CC_HOST/RRPSP_CC_KEY are unset
(a compile that fails for any other reason makes its functions MISSING, so the gate is red).

--replace SRC=COPY grades COPY (a file inside the repository, for example under build/) in
place of the real file SRC.  --plant-drop 0xADDR leaves that function out of the placed set;
--plant-force 0xADDR places it although it is not EXACT.  These exist to prove the gate fails;
docs/GATES.md records the demonstrations.

Prints the compile time, how many files were compiled or served from the cache, and the
total time.  Not compared: see tools/score.py (.eh_frame, .gcc_except_table, data contents a
function does not refer to, the relocation table itself).
"""
import argparse
import hashlib
import json
import struct
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import score                    # noqa: E402


def field(typ, target, segbase, word):
    v = (target - segbase) & 0xffffffff
    if typ == 2:
        return v
    if typ == 4:
        return (word & ~0x3ffffff) | ((v >> 2) & 0x3ffffff)
    if typ == 5:
        return (word & ~0xffff) | (((v + 0x8000) >> 16) & 0xffff)
    if typ == 6:
        return (word & ~0xffff) | (v & 0xffff)
    raise ValueError('relocation type %d' % typ)


def run(no_cache=False, replace=(), drop=(), force=(), only=None, jobs=8):
    t0 = time.time()
    retail = score.Retail()
    tree = score.Tree(use_cache=not no_cache, jobs=jobs)
    g = score.Grader(tree, retail)
    repl = {(score.ROOT / a).resolve(): (score.ROOT / b).resolve() for a, b in replace}
    real = [p.resolve() for p in score.source_files() if score.is_real(p)]
    files = [repl.get(p, p) for p in real]
    # The index (tags of real files) must see the replacement, not the original.
    tree.compile_many(files)
    idx_files = files

    tree._index = tree.build_index(idx_files)
    t_compile = time.time() - t0
    results, problems = [], []
    scope = None if not only else {repl.get((score.ROOT / x).resolve(), (score.ROOT / x).resolve())
                                   for x in only}
    for p in files:
        if scope is not None and p not in scope:
            continue
        u = tree.units[p]
        problems += u.problems
        for t in u.tags:
            if t.kind == 'implements' and t.region == 'us':
                results.append(g.grade(u, t))
    g.finalize(results)
    t_grade = time.time() - t0 - t_compile

    p = retail.p
    img = bytearray(p.data)
    fails = []
    n_impl = len(results)
    placed = []
    drop, force = set(drop), set(force)
    for r in results:
        if (r['verdict'] == 'EXACT' or r['addr'] in force) and r['addr'] not in drop:
            placed.append(r)
    spans = []
    for r in placed:
        # A placed function must be EXACT with the funcs.csv size; checked again here, at the
        # point of use, rather than trusted from the selection above.
        f = retail.funcs.get(r['addr'])
        if r['verdict'] != 'EXACT':
            fails.append('placed %#08x is %s' % (r['addr'], r['verdict']))
        if 'symbol' not in r:
            continue
        if f is None or r['size'] != f['size']:
            fails.append('placed %#08x: size %d, funcs.csv %s' % (
                r['addr'], r['size'], f and f['size']))
            continue
        u = tree.units[Path(score.ROOT / r['file']).resolve()]
        sym = next(s for s in u.obj.syms if s.name == r['symbol'] and s.type == score.STT_FUNC
                   and u.obj.defined(s))
        code = bytearray(u.obj.bytes_of(sym.shndx, sym.value, sym.size))
        # A forced (non-EXACT) function has no proven targets; its fields are written from
        # the compiled side's own resolved addresses where it has them.
        for k, typ, target in r['refs'] if 'refs' in r else r.get('compiled_refs', []):
            if target is None:
                continue
            w = struct.unpack_from('<I', code, 4 * k)[0]
            base = retail.segbase(target)
            if base is None:
                fails.append('%#08x word %d: target %#08x is in no segment' % (r['addr'], k, target))
                continue
            struct.pack_into('<I', code, 4 * k, field(typ, target, base, w))
        off = p._file_off(r['addr'])
        if p._file_off(r['addr'] + sym.size - 1) != off + sym.size - 1:
            fails.append('%#08x: crosses a segment boundary' % r['addr'])
            continue
        img[off:off + sym.size] = code
        spans.append((r['addr'], r['addr'] + sym.size, r))
    spans.sort(key=lambda s: s[0])
    for (a0, e0, r0), (a1, e1, r1) in zip(spans, spans[1:]):
        if a1 < e0:
            fails.append('overlap: %#08x-%#08x (%s) and %#08x-%#08x (%s)' % (
                a0, e0, r0['file'], a1, e1, r1['file']))
    if len(img) != len(p.data):
        fails.append('image size %d, retail %d' % (len(img), len(p.data)))
    diff = [i for i in range(len(p.data)) if img[i] != p.data[i]] if img != p.data else []
    if diff:
        def owner(fo):
            for a, e, r in spans:
                o = p._file_off(a)
                if o <= fo < o + (e - a):
                    return '%#08x %s' % (r['addr'], r['file'])
            return '?'
        fails.append('%d bytes differ from retail; first at file offset %#x (in %s)' % (
            len(diff), diff[0], owner(diff[0])))
    n_placed = len(spans)
    if n_placed == 0:
        fails.append('no function placed')
    if n_placed < n_impl:
        fails.append('%d functions placed, %d @implements tags in %s' % (
            n_placed, n_impl, 'the given files' if only else 'real files'))
    not_exact = [r for r in results if r['verdict'] != 'EXACT']
    return {
        'green': not fails, 'fails': fails, 'placed': n_placed, 'implements': n_impl,
        'placed_bytes': sum(e - a for a, e, _ in spans),
        'not_exact': not_exact, 'results': results, 'problems': problems,
        'image_md5': hashlib.md5(bytes(img)).hexdigest(), 'retail_md5': hashlib.md5(p.data).hexdigest(),
        'compiled': tree.times['compiled'], 'cached': tree.times['cached'],
        'seconds': {'compile': round(t_compile, 2), 'grade': round(t_grade, 2),
                    'total': round(time.time() - t0, 2)},
        'placed_addrs': sorted(a for a, _, _ in spans),
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--no-cache', action='store_true')
    ap.add_argument('--replace', action='append', default=[], metavar='SRC=COPY')
    ap.add_argument('--plant-drop', action='append', default=[], metavar='0xADDR')
    ap.add_argument('--plant-force', action='append', default=[], metavar='0xADDR',
                    help='place this function even if it is not EXACT (fields left as compiled '
                         'when it has no resolved references)')
    ap.add_argument('--list', action='store_true', help='list every @implements that is not EXACT')
    ap.add_argument('--files', nargs='+', metavar='SRC',
                    help='gate only these real files: their @implements are the count to meet '
                         '(the cross-file index still covers every real file)')
    a = ap.parse_args(argv)
    res = run(a.no_cache, [x.split('=', 1) for x in a.replace],
              [int(x, 16) for x in a.plant_drop], [int(x, 16) for x in a.plant_force], a.files)
    if a.json:
        out = dict(res)
        out.pop('results')
        out['not_exact'] = [{k: v for k, v in r.items()
                             if k not in ('refs', 'items', 'compiled_refs', 'methods')}
                            for r in res['not_exact']]
        json.dump(out, sys.stdout, indent=1)
        print()
    else:
        if a.list:
            for r in res['not_exact']:
                print(score.fmt(r))
        c = {}
        for r in res['results']:
            c[r['verdict']] = c.get(r['verdict'], 0) + 1
        print('@implements in %s: %d (%s)' % ('the given files' if a.files else 'real files',res['implements'], ', '.join(
            '%s %d' % kv for kv in sorted(c.items()))))
        print('placed: %d functions, %d bytes' % (res['placed'], res['placed_bytes']))
        print('image md5 %s, retail %s' % (res['image_md5'], res['retail_md5']))
        print('time: compile %.2f s (%d compiled, %d cached), grade %.2f s, total %.2f s' % (
            res['seconds']['compile'], res['compiled'], res['cached'], res['seconds']['grade'],
            res['seconds']['total']))
        for f in res['fails']:
            print('FAIL', f)
        print('image gate:', 'GREEN' if res['green'] else 'RED')
    return 0 if res['green'] else 1


if __name__ == '__main__':
    sys.exit(main())
