#!/usr/bin/env python3
"""Rule 0: the reference is checked, not remembered. Run at the start of every session.

Checks orig/us/BOOT.BIN against its recorded MD5 and refuses to continue otherwise. With
--eboot it also decrypts orig/<region>/EBOOT.BIN (build/ext/pspdecrypt, pinned) and proves the
signed executable carries exactly BOOT.BIN, i.e. the reference is the program the PSP runs.
Measured 2026-10-12: identical for US, EU and JP.

    python3 tools/refcheck.py [--eboot]
"""
import hashlib
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REF = {'us': 'e87ea7c17004cd13945664152608140c', 'eu': '4eaa1ff90e56f5ff1521e4e59597e9f2',
       'jp': '524c500adbe299a546e03ad40ada5a56'}


def md5(path):
    return hashlib.md5(open(path, 'rb').read()).hexdigest()


def main():
    bad = 0
    for r, want in REF.items():
        p = os.path.join(ROOT, 'orig', r, 'BOOT.BIN')
        if not os.path.exists(p):
            print(f'{r}: orig/{r}/BOOT.BIN missing (run ./setup.sh)')
            bad += r == 'us'
            continue
        got = md5(p)
        ok = got == want
        bad += (not ok) and r == 'us'
        line = f'{r}: BOOT.BIN {"OK" if ok else "WRONG " + got}'
        if '--eboot' in sys.argv:
            tool = os.path.join(ROOT, 'build/ext/pspdecrypt/pspdecrypt')
            out = os.path.join(ROOT, 'build/decrypt', f'{r}.EBOOT.dec')
            os.makedirs(os.path.dirname(out), exist_ok=True)
            subprocess.run([tool, '-o', out, os.path.join(ROOT, 'orig', r, 'EBOOT.BIN')], capture_output=True)
            same = os.path.exists(out) and md5(out) == got
            bad += not same
            line += f'; decrypted EBOOT.BIN {"== BOOT.BIN" if same else "DIFFERS"}'
        print(line)
    if bad:
        print('refcheck: FAILED; do not grade or build against this corpus')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
