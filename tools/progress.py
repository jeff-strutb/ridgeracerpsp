#!/usr/bin/env python3
"""Tier counts, from the tools only.

    tools/progress.py [--json] [--no-cache]

Runs the image gate (tools/image.py, which grades with tools/score.py) and counts every
function of config/us/funcs.csv by its class in config/us/fence.csv:

  T4  an @implements tag in a real file, EXACT, and placed by a GREEN image gate.  While the
      gate is red no function is T4 (M2 is all-or-nothing); the count of EXACT functions the
      red gate placed is printed beside it.
  T3  none.  T3 needs an oracle that certifies same behaviour, and no such tool exists, so
      the count is 0 by construction, not by measurement.
  T2  tagged (@implements or @draft in a real file) but not T4.
  T1  not tagged in any real file.

Tags in src/control/batch*.c are not counted (those files are not real translation units).
Two populations are printed: the proven-game class, and the code classed unknown that lies
before the first identified library function (the lowest libfuncs.csv fingerprint in .text),
whose place in the denominator the owner has not ruled on.
"""
import argparse
import csv
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import score                    # noqa: E402
import image                    # noqa: E402

CFG = score.ROOT / 'config' / 'us'


def rows(name):
    with open(CFG / name) as fh:
        return list(csv.DictReader(fh))


def first_library_fingerprint():
    return min(int(r['addr'], 16) for r in rows('libfuncs.csv')
               if r['how'] == 'fingerprint' and r['section'] == '.text')


def compute(gate):
    fence = {int(r['addr'], 16): (int(r['size']), r['class']) for r in rows('fence.csv')}
    funcs = {int(r['addr'], 16): int(r['size']) for r in rows('funcs.csv')}
    if set(fence) != set(funcs) or any(fence[a][0] != funcs[a] for a in funcs):
        raise SystemExit('progress: fence.csv and funcs.csv disagree')
    tagged = set()
    for p in score.source_files():
        if score.is_real(p):
            for t in score.parse_tags(p)[0]:
                if t.region == 'us':
                    tagged.add(t.addr)
    placed = set(gate['placed_addrs'])
    green = gate['green']
    cut = first_library_fingerprint()
    pops = {'game': lambda a, c: c == 'game',
            'unknown<%#08x' % cut: lambda a, c: c == 'unknown' and a < cut}
    out = {}
    for name, pred in pops.items():
        t = {k: [0, 0] for k in ('T4', 'T3', 'T2', 'T1', 'placed-by-red-gate')}
        for a, (size, c) in fence.items():
            if not pred(a, c):
                continue
            if a in placed and green:
                tier = 'T4'
            elif a in tagged:
                tier = 'T2'
            else:
                tier = 'T1'
            t[tier][0] += 1
            t[tier][1] += size
            if a in placed and not green:
                t['placed-by-red-gate'][0] += 1
                t['placed-by-red-gate'][1] += size
        out[name] = t
    return out, cut


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--no-cache', action='store_true')
    a = ap.parse_args(argv)
    gate = image.run(a.no_cache)
    tiers, cut = compute(gate)
    if a.json:
        json.dump({'gate_green': gate['green'], 'gate_fails': gate['fails'], 'tiers': tiers},
                  sys.stdout, indent=1)
        print()
        return 0
    print('image gate: %s (%d placed of %d @implements in real files)' % (
        'GREEN' if gate['green'] else 'RED', gate['placed'], gate['implements']))
    for f in gate['fails']:
        print('  gate FAIL:', f)
    for name, t in tiers.items():
        tot_n = sum(v[0] for k, v in t.items() if k != 'placed-by-red-gate')
        tot_b = sum(v[1] for k, v in t.items() if k != 'placed-by-red-gate')
        print()
        print('%-22s %10s %12s' % (name, 'functions', 'bytes'))
        for k in ('T4', 'T3', 'T2', 'T1'):
            print('%-22s %10d %12d' % (k, t[k][0], t[k][1]))
        print('%-22s %10d %12d' % ('total', tot_n, tot_b))
        if not gate['green']:
            print('%-22s %10d %12d   (EXACT and byte-identical in the image, not T4 while '
                  'the gate is red)' % ('  placed, gate red', *t['placed-by-red-gate']))
    print()
    print('T3 is 0: no oracle exists that certifies same behaviour.')
    print('T4 needs a green image gate.' if not gate['green'] else '')
    return 0


if __name__ == '__main__':
    sys.exit(main())
