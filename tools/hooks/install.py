#!/usr/bin/env python3
"""Install (or remove) this folder's hooks for the checkout you run it in.

    python3 tools/hooks/install.py              install for this worktree only
    python3 tools/hooks/install.py --uninstall  restore what was there before
    python3 tools/hooks/install.py --status     show what is configured

Installing sets core.hooksPath to this folder in the worktree's own config
(git config --worktree), which needs extensions.worktreeConfig; other worktrees and the main
checkout are not touched.  If that extension is off, it refuses rather than write the shared
repository config.  The previous value is kept in rrpsp.hooks.previous and restored by
--uninstall.  The hooks need RRPSP_CC_HOST and RRPSP_CC_KEY in the committing shell; without
them the pre-commit hook refuses any commit that stages a tagged source.
"""
import os
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
HOOKS = ('pre-commit', 'commit-msg')


def git(*a, check=True):
    p = subprocess.run(['git', '-C', str(HERE)] + list(a), capture_output=True, text=True)
    if check and p.returncode:
        sys.exit('install: git %s: %s' % (' '.join(a), p.stderr.strip()))
    return p.stdout.strip(), p.returncode


def main(argv):
    wt, _ = git('config', '--type=bool', '--get', 'extensions.worktreeConfig', check=False)
    top, _ = git('rev-parse', '--show-toplevel')
    cur, rc = git('config', '--worktree', '--get', 'core.hooksPath', check=False)
    if '--status' in argv:
        print('worktree %s\ncore.hooksPath (worktree) %s' % (top, cur if rc == 0 else '(unset)'))
        eff, _ = git('config', '--get', 'core.hooksPath', check=False)
        print('core.hooksPath (effective) %s' % (eff or '(unset)'))
        return 0
    if wt != 'true':
        sys.exit('install: extensions.worktreeConfig is off; refusing to set core.hooksPath in '
                 'the shared repository config')
    if '--uninstall' in argv:
        prev, prc = git('config', '--worktree', '--get', 'rrpsp.hooks.previous', check=False)
        if prc:
            sys.exit('install: nothing recorded to restore')
        if prev == '(unset)':
            git('config', '--worktree', '--unset', 'core.hooksPath', check=False)
        else:
            git('config', '--worktree', 'core.hooksPath', prev)
        git('config', '--worktree', '--unset', 'rrpsp.hooks.previous')
        print('install: restored core.hooksPath for %s to %s' % (top, prev))
        return 0
    for h in HOOKS:
        os.chmod(HERE / h, 0o755)
    if cur != str(HERE):
        git('config', '--worktree', 'rrpsp.hooks.previous', cur if rc == 0 else '(unset)')
    git('config', '--worktree', 'core.hooksPath', str(HERE))
    print('install: core.hooksPath for %s = %s (was %s)' % (top, HERE, cur if rc == 0 else 'unset'))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
