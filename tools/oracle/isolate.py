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

    python3 tools/oracle/isolate.py SCRIPT [--max N] [--frames N]
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
    keys = ['hash', 'clobbered'] + {'void': [], 'int': ['v0'], 'wide': ['v0', 'v1'], 'float': ['f0']}[rk]
    return next((k for k in keys if r.get(k) != c.get(k)), None)


def records_by_thread(path):
    """Yield (thread, line number, kind, func, values, raw line) for every record of a call log. A
    return record carries no thread; it belongs to the thread its call was entered on."""
    thread = {}  # (func, call) -> thread
    with open(path) as f:
        for n, line in enumerate(f, 1):
            if len(line.split()) < 4:
                continue  # a log torn by the size cap
            k, a, c, v = fields(line)
            if k == 'E':
                t = v.pop('t')
                thread[(a, c)] = t
            else:
                t = thread.pop((a, c), None)
            yield t, n, k, a, v, line


def first_divergence(retail, candidate, w):
    """(blamed address or None, description) at the first differing record, or None if none.

    The logs are compared thread by thread. Which thread runs when is timing: a draft that takes a
    different number of cycles moves the next thread switch or interrupt, and then the two logs
    interleave differently without any thread behaving differently. Call numbers are left out for
    the same reason (they count a function's calls over all threads)."""
    import collections
    queues = ({}, {})       # per side: thread -> deque of records not yet matched
    stack = {}              # thread -> [func, ...] open in retail
    sides = (records_by_thread(retail), records_by_thread(candidate))
    live = [True, True]
    while any(live):
        for side in (0, 1):
            if not live[side]:
                continue
            rec = next(sides[side], None)
            if rec is None:
                live[side] = False
                continue
            t = rec[0]
            queues[side].setdefault(t, collections.deque()).append(rec)
            qr, qc = queues[0].get(t), queues[1].get(t)
            while qr and qc:
                _, n, kr, ar, vr, lr = qr.popleft()
                _, m, kc, ac, vc, lc = qc.popleft()
                st = stack.setdefault(t, [])
                where = f'thread {t}, retail line {n}, candidate line {m}'
                if kr == 'E':
                    ks = w[ar][3] if ar in w else None
                    # only the registers its parameters occupy (a5.arg_keys); never tk, the time at
                    # entry, which rrbox sets to retail's
                    vr = {k: x for k, x in vr.items() if k != 'tk' and (ks is None or k in ks)}
                    vc = {k: x for k, x in vc.items() if k != 'tk' and (ks is None or k in ks)}
                    if (kc, ac) != (kr, ar) or vr != vc:
                        return (st[-1] if st else None,
                                f'{where}: retail {lr.strip()[:90]} / candidate {lc.strip()[:90]}', list(st))
                    st.append(ar)
                    continue
                if (kc, ac) != (kr, ar):
                    return (st[-2] if len(st) > 1 else None,
                            f'{where}: retail returns from f_{ar:06x}, candidate has {lc.strip()[:90]}', list(st))
                why = same_return(w[ar][2] if ar in w else 'int', vr, vc)
                if why:
                    return ar, f'{where}: f_{ar:06x} return differs in {why}: {vr.get(why)} vs {vc.get(why)}', list(st)
                if st and st[-1] == ar:
                    st.pop()
    return None


def main():
    script = os.path.abspath(sys.argv[1])
    if '--frames' in sys.argv:
        # A long script whose first divergence comes early: run only its first N frames. The copy
        # keeps the script's name (stage directories and logs are named by it) under build/oracle.
        n = int(sys.argv[sys.argv.index('--frames') + 1])
        short = os.path.join(ROOT, 'build/oracle/short', os.path.basename(script))
        os.makedirs(os.path.dirname(short), exist_ok=True)
        body = [l for l in open(script) if not l.startswith('# frames')]
        open(short, 'w').write(f'# frames {n}\n' + ''.join(body))
        script = short
    cap = int(sys.argv[sys.argv.index('--max') + 1]) if '--max' in sys.argv else 50
    name = os.path.splitext(os.path.basename(script))[0]
    w = a5.watched()
    for it in range(cap):
        out = subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/oracle/m1image.py')],
                             capture_output=True, text=True).stdout.splitlines()
        placed = {int(l.split()[0], 16) for l in open(os.path.join(ROOT, 'build/image/m1_placed.txt'))}
        res = subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/oracle/a5.py'), '--keep', script],
                             capture_output=True, text=True).stdout.splitlines()
        print(f'[{it}] {out[-1] if out else "m1image: no output"} | {res[-1] if res else "a5: no output"}', flush=True)
        d = first_divergence(os.path.join(a7.OUT, f'{name}.retail.calls'),
                             os.path.join(a7.OUT, f'{name}.candidate.calls'), w)
        if d is None:
            print(f'{name}: call logs agree to the end of the shorter one')
            return 0
        blamed, why, open_ = d
        is_draft = lambda a: a is not None and a in placed and w.get(a, ('',))[0] == 'draft'  # noqa: E731
        if not is_draft(blamed):
            # Retail code (byte-exact, or a draft left out) behaved differently on equal arguments, so
            # something it read differs. When globals agree (tools/oracle/statediff.py) that is memory
            # it reached through a pointer into an enclosing frame, such as a draft caller's local
            # passed by address (an iterator, an output struct): blame the innermost placed draft still
            # open on that thread.
            outer = next((a for a in reversed(open_) if is_draft(a)), None)
            if outer is not None:
                why = f'(enclosing f_{blamed:06x}) ' + why if blamed is not None else why
                blamed = outer
        if is_draft(blamed):
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
