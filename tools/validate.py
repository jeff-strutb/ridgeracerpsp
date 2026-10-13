#!/usr/bin/env python3
"""Complete validation, every gate in one command. It must finish in under 5 minutes.

  1. precommit   filing rules over the whole tree (tools/precommit.py --all)
  2. progress    every source scored (tools/score.py, files in parallel); README block and map
  3. image       M2 gate: BOOT.BIN rebuilt from the claims, 0 differing bytes (tools/image.py)
  4. m1image     the M1 image: claims plus draft bodies (tools/oracle/m1image.py)
  5. a5          A5 and A7 on the M1 image, every script in parallel (tools/oracle/a5.py)

Compiled objects are cached by content (tools/score.py), so steps 3 and 4 reuse step 2's
compiles; retail's oracle runs are cached by executable, script, watched set and rrbox build.
The M2 result (steps 1 to 3) decides the exit code. A5 reports per-function verdicts into
config/us/t3_live.csv, where a draft earns T3; its differences are reported, not fatal, because
the M1 image contains unproven drafts by design.

    python3 tools/validate.py [--no-oracle]
Exit 0 = the M2 gates pass and the whole run took under 300 s; 1 = a gate failed; 3 = too slow.
"""
import os
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIMIT = 300
STEPS = [
    ('precommit', ['tools/precommit.py', '--all'], True),
    ('progress', ['tools/progress.py'], True),
    ('image', ['tools/image.py'], True),
    ('m1image', ['tools/oracle/m1image.py'], False),
    ('a5', ['tools/oracle/a5.py'], False),
]


def main():
    oracle = '--no-oracle' not in sys.argv
    t0 = time.time()
    failed = []
    for name, cmd, hard in STEPS:
        if not oracle and name in ('m1image', 'a5'):
            continue
        t = time.time()
        p = subprocess.run([sys.executable, *cmd], cwd=ROOT, capture_output=True, text=True)
        lines = [ln for ln in (p.stdout + p.stderr).splitlines() if ln.strip()]
        print(f'{name:10s} {time.time() - t:6.1f}s  rc={p.returncode}  {lines[-1] if lines else ""}', flush=True)
        if p.returncode:
            if hard:
                failed.append(name)
            if name == 'm1image':
                break  # nothing for A5 to run
    total = time.time() - t0
    print(f'total      {total:6.1f}s  (limit {LIMIT}s)  {"FAILED: " + ", ".join(failed) if failed else "M2 gates pass"}')
    if failed:
        return 1
    return 3 if total > LIMIT else 0


if __name__ == '__main__':
    sys.exit(main())
