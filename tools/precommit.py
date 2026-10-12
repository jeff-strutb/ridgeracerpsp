#!/usr/bin/env python3
"""Filing rules for decompiled functions, checked on the staged tree (pre-commit hook).

Refuses a commit that:
  1. adds an `@implements` or `@draft 0xADDR us Name` in src/ (outside src/control/) whose
     own comment block (the /* ... */ holding the tag) has no `WHAT IT DOES:` paragraph;
  2. adds a source file under src/ (outside src/control/) named for an address or a batch
     (slice*, batch*, part*, f_XXXXXX*, 0x*): functions are filed into the translation unit
     they came from, at the moment they are matched;
  3. leaves any retail address claimed by two @implements anywhere in src/.
src/control/ is the compiler-identification control set and is exempt from 1 and 2.

    python3 tools/precommit.py          # staged tree (the hook)
    python3 tools/precommit.py --all    # the working tree: tracked and untracked sources
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TAG = re.compile(r'@(?:implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+(\S+)')
BATCH = re.compile(r'^(?:slice|batch|part|chunk|f_[0-9a-f]{6}|0x[0-9a-f]+|[0-9a-f]{6,})', re.I)
SRC_EXT = ('.c', '.cpp', '.cc', '.h', '.hpp', '.s', '.S')


def git(*a):
    return subprocess.run(['git', '-C', ROOT] + list(a), capture_output=True).stdout


def main():
    every = '--all' in sys.argv
    if every:
        paths = [p for p in (git('ls-files', '-z') + git('ls-files', '-z', '--others', '--exclude-standard')).decode().split('\0') if p]
        added = set(paths)
        read = lambda p: open(os.path.join(ROOT, p), 'rb').read()  # noqa: E731
    else:
        paths = [p for p in git('ls-files', '-z', '--cached').decode().split('\0') if p]
        added = {p for p in git('diff', '--cached', '--name-only', '--diff-filter=A', '-z').decode().split('\0') if p}
        read = lambda p: git('show', ':' + p)  # noqa: E731
    changed = set(paths) if every else {p for p in git('diff', '--cached', '--name-only', '--diff-filter=ACMR', '-z').decode().split('\0') if p}
    problems, claims = [], {}
    for p in paths:
        if not p.startswith('src/') or not p.endswith(SRC_EXT):
            continue
        control = p.startswith('src/control/')
        text = read(p).decode('utf-8', 'replace')
        lines = text.splitlines()
        for i, line in enumerate(lines):
            m = TAG.search(line)
            if not m:
                continue
            addr = int(m.group(1), 16)
            claims.setdefault(addr, []).append(f'{p}:{i + 1}')
            if p in changed and not control:
                a = max((k for k in range(i + 1) if '/*' in lines[k]), default=i)
                b = min((k for k in range(i, len(lines)) if '*/' in lines[k]), default=i)
                if not any('WHAT IT DOES:' in x for x in lines[a:b + 1]):
                    problems.append(f'{p}:{i + 1}: 0x{addr:06x}: its comment has no WHAT IT DOES: paragraph')
        if p in added and not control and BATCH.match(os.path.basename(p)):
            problems.append(f'{p}: new file named for an address or batch; file the function into its translation unit')
    for addr, where in sorted(claims.items()):
        if len(where) > 1:
            problems.append(f'0x{addr:06x} is claimed {len(where)} times: ' + ', '.join(where))
    for x in problems:
        print(x)
    if problems:
        print(f'precommit: {len(problems)} problem(s)', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
