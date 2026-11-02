#!/usr/bin/env python3
"""Find the memory that differs at one call's entry, and who wrote it.

When a byte-exact function behaves differently in the M1 image (isolate.py stops on it), some
memory it read differs, and the draft that changed it slipped past A5. This runs retail and the
current M1 image (build/image/BOOT.M1.BIN) on SCRIPT twice:

  1. with RRBOX_DUMPAT, dumping user RAM at the entry of call CALL of FUNC, and diffs the dumps
     outside .text and every thread's stack;
  2. with RRBOX_WADDR on the first differing byte, logging every write to it in each run with the
     innermost watched call it happened in.

    python3 tools/oracle/statediff.py SCRIPT FUNC CALL [--max N]
"""
import os
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
import a5  # noqa: E402
import a7  # noqa: E402

BASE = 0x08800000  # user RAM as dumped


def both(script, env, tmp):
    """Run retail then the M1 image on `script` with extra environment `env`; return the two
    call-log paths."""
    logs = []
    for side, exe, watch in (('r', a7.RETAIL, 'watch_retail.txt'), ('c', os.path.join(ROOT, 'build/image/BOOT.M1.BIN'), 'watch.txt')):
        calls = os.path.join(tmp, f'{side}.calls')
        e = {k: v.replace('{side}', side) for k, v in env.items()}
        old = {k: os.environ.get(k) for k in e}
        os.environ.update(e)
        try:
            a5.run(exe, script, os.path.join(tmp, f'{side}.trace'), os.path.join(a7.OUT, watch), calls,
                   logs[0] if logs else None, cap=1 << 30)
        finally:
            for k, v in old.items():
                if v is None:
                    os.environ.pop(k, None)
                else:
                    os.environ[k] = v
        logs.append(calls)
    return logs


def main():
    script, func, call = os.path.abspath(sys.argv[1]), int(sys.argv[2], 16), int(sys.argv[3])
    most = int(sys.argv[sys.argv.index('--max') + 1]) if '--max' in sys.argv else 8
    tmp = tempfile.mkdtemp(dir=os.path.join(ROOT, 'build/oracle'))
    both(script, {'RRBOX_DUMPAT': f'{func:x}:{call}:{tmp}/{{side}}.ram'}, tmp)
    r, c = (open(os.path.join(tmp, f'{s}.ram'), 'rb').read() for s in 'rc')
    # .text, and every thread's stack in either run: dead stack contents are not state
    skip = [a7.TEXT_RAM]
    for s in 'rc':
        for line in open(os.path.join(tmp, f'{s}.ram.stacks')):
            st, size = (int(x, 16) for x in line.split())
            skip.append((st, st + size))
    n = min(len(r), len(c))
    runs, start = [], None
    for i in range(n + 1):
        a = BASE + i
        same = i == n or r[i] == c[i] or any(lo <= a < hi for lo, hi in skip)
        if not same and start is None:
            start = i
        elif same and start is not None:
            runs.append((start, i))
            start = None
    print(f'{len(runs)} differing ranges at f_{func:06x} call {call} entry (outside .text)')
    for s, e in runs[:most]:
        print(f'  {BASE + s:08x}..{BASE + e:08x}  retail {r[s:min(e, s + 16)].hex()}  candidate {c[s:min(e, s + 16)].hex()}')
    if not runs:
        return 0
    addr = BASE + runs[0][0]
    rl, cl = both(script, {'RRBOX_WADDR': f'{addr:x}'}, tmp)
    for name, log in (('retail', rl), ('candidate', cl)):
        lines = [x for x in open(log) if x.startswith('A ')]
        print(f'writes to {addr:08x} in {name} ({len(lines)}):')
        for x in lines[-most:]:
            print('  ' + x.strip())
    subprocess.run(['rm', '-rf', tmp])
    return 0


if __name__ == '__main__':
    sys.exit(main())
