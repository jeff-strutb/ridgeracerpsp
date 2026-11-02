#!/usr/bin/env python3
"""Find the drafts that make the M1 image diverge from retail, one at a time, and leave them out.

A5 runs every placed draft in one image, so the first draft that behaves differently changes game
state, and every watched call after it (byte-exact functions included) may then differ too. This
loop makes the A5 verdicts trustworthy:

  1. build the M1 image (tools/oracle/m1image.py), leaving out build/oracle/m1_exclude.txt;
  2. run A5 on SCRIPT;
  3. walk retail's and the candidate's call logs together to the first record that differs.
     An entry record that differs (or a different call where retail made another) blames the
     innermost watched call still open on that thread in retail, the caller that computed it; a
     return that differs (the writes, the registers its return type uses, a clobbered callee-saved
     register; never the cycle count) blames that function, the innermost to change anything;
  4. a blamed placed draft is appended to the exclude list, and the loop repeats. Anything else
     (a byte-exact function blamed, a call outside any watched function) stops the loop: that
     needs reading by hand.

    python3 tools/oracle/isolate.py SCRIPT [--max N]
"""
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
import a5  # noqa: E402
import a7  # noqa: E402

EXCLUDE = os.path.join(ROOT, 'build/oracle/m1_exclude.txt')


def fields(line):
    t = line.split()
    return t[0], int(t[1], 16), int(t[2]), dict(x.split('=', 1) for x in t[3:])


def same_return(rk, r, c):
    keys = ['writes', 'hash', 'clobbered'] + {'void': [], 'int': ['v0'], 'wide': ['v0', 'v1'], 'float': ['f0']}[rk]
    return next((k for k in keys if r.get(k) != c.get(k)), None)


def first_divergence(retail, candidate, w):
    """(blamed address or None, description) at the first differing record, or None if none."""
    stack = {}   # thread -> [func, ...] open in retail
    thread = {}  # (func, call) -> thread
    with open(retail) as fr, open(candidate) as fc:
        for n, (lr, lc) in enumerate(zip(fr, fc), 1):
            kr, ar, cr, vr = fields(lr)
            kc, ac, cc, vc = fields(lc)
            if kr == 'E':
                t = vr['t']
                if (kc, ac, cc) != (kr, ar, cr) or vr != vc:
                    st = stack.get(t, [])
                    return (st[-1] if st else None,
                            f'line {n}: retail {lr.strip()[:90]} / candidate {lc.strip()[:90]}')
                thread[(ar, cr)] = t
                stack.setdefault(t, []).append(ar)
                continue
            t = thread.pop((ar, cr), None)
            if (kc, ac, cc) != (kr, ar, cr):
                st = stack.get(t, [])
                return (st[-2] if len(st) > 1 else None, f'line {n}: retail returns from f_{ar:06x}, candidate has {lc.strip()[:90]}')
            why = same_return(w[ar][2] if ar in w else 'int', vr, vc)
            if why:
                return ar, f'line {n}: f_{ar:06x} call {cr} return differs in {why}: {vr.get(why)} vs {vc.get(why)}'
            if t is not None and stack.get(t) and stack[t][-1] == ar:
                stack[t].pop()
    return None


def main():
    script = os.path.abspath(sys.argv[1])
    cap = int(sys.argv[sys.argv.index('--max') + 1]) if '--max' in sys.argv else 50
    name = os.path.splitext(os.path.basename(script))[0]
    w = a5.watched()
    for it in range(cap):
        out = subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/oracle/m1image.py')],
                             capture_output=True, text=True).stdout.splitlines()
        placed = {int(l.split()[0], 16) for l in open(os.path.join(ROOT, 'build/image/m1_placed.txt'))}
        res = subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/oracle/a5.py'), script],
                             capture_output=True, text=True).stdout.splitlines()
        print(f'[{it}] {out[-1] if out else "m1image: no output"} | {res[-1] if res else "a5: no output"}', flush=True)
        d = first_divergence(os.path.join(a7.OUT, f'{name}.retail.calls'),
                             os.path.join(a7.OUT, f'{name}.candidate.calls'), w)
        if d is None:
            print(f'{name}: call logs agree to the end of the shorter one')
            return 0
        blamed, why = d
        if blamed is not None and blamed in placed and w.get(blamed, ('',))[0] == 'draft':
            print(f'    exclude f_{blamed:06x}: {why}', flush=True)
            with open(EXCLUDE, 'a') as f:
                f.write(f'{blamed:06x} {name}: {why}\n')
            continue
        print(f'    stop: blamed {"f_%06x" % blamed if blamed is not None else "no watched function"} '
              f'({w.get(blamed, ("unwatched",))[0] if blamed is not None else "-"}): {why}')
        return 1
    print(f'stopped after {cap} rounds')
    return 1


if __name__ == '__main__':
    sys.exit(main())
