#!/usr/bin/env python3
"""Choose the compiler control set by a fixed rule and write src/control/CONTROL.md.

The rule uses only the source text, never a score, so it cannot be tuned to favour a compiler:

  1. Universe: every `@implements` tag in src/**/*.c and *.cpp, except the files already in
     src/control/ (their own header says they are not real translation units).
  2. Each function's body is the text from its tag to the next tag (or end of file), with
     comments, string and character literals removed; a tag with no code before the next tag
     (stacked tags, e.g. two constructor copies) takes the next tag's body. Its size is its count of non-blank code
     lines; size class S/M/L splits the universe at its tertiles.
     It is select-bearing when its body uses the ?: operator, directly or through a macro
     defined in the same file whose body uses ?:.
  3. Strata: (module = first folder under src/, language C or C++, size class). Within a
     stratum functions are ordered by sha256("<file>:<address>").
  4. First 20 select-bearing functions are taken round-robin over the strata (in sorted stratum
     order, one per stratum per round); then the set is filled to 60 round-robin over all strata.

Run: python3 tools/toolchains/pick_control.py  (rewrites src/control/CONTROL.md)
"""
import glob
import hashlib
import os
import re

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
TAG_RE = re.compile(r'/\*\s*@(implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+(\S+)')
TOTAL, SELECT_QUOTA = 60, 20


def strip(code):
    out = re.sub(r'/\*.*?\*/', ' ', code, flags=re.S)
    out = re.sub(r'//[^\n]*', ' ', out)
    out = re.sub(r'"(\\.|[^"\\\n])*"', '""', out)
    out = re.sub(r"'(\\.|[^'\\\n])*'", "''", out)
    return out


def functions():
    out = []
    for path in sorted(glob.glob(os.path.join(REPO, 'src', '**', '*.c'), recursive=True) +
                       glob.glob(os.path.join(REPO, 'src', '**', '*.cpp'), recursive=True)):
        rel = os.path.relpath(path, REPO)
        if rel.startswith(os.path.join('src', 'control') + os.sep):
            continue
        text = open(path, encoding='latin-1').read()
        clean = strip(text)
        sel_macros = set(m.group(1) for m in re.finditer(
            r'^[ \t]*#[ \t]*define[ \t]+(\w+)\(([^)]*)\)(.*(?:\\\n.*)*)', clean, re.M)
            if '?' in m.group(3))
        tags = list(TAG_RE.finditer(text))
        bodies = [strip(text[m.end():tags[i + 1].start() if i + 1 < len(tags) else len(text)])
                  for i, m in enumerate(tags)]
        for i, m in enumerate(tags):
            if m.group(1) != 'implements':
                continue
            j = i  # stacked tags with no code of their own share the next body
            while j + 1 < len(tags) and not any(l.strip() for l in bodies[j].splitlines()):
                j += 1
            body = bodies[j]
            lines = sum(1 for l in body.splitlines() if l.strip())
            sel = '?' in body or any(re.search(r'\b%s\s*\(' % re.escape(mc), body)
                                     for mc in sel_macros)
            out.append(dict(file=rel, addr=int(m.group(2), 16), name=m.group(3),
                            module=rel.split(os.sep)[1],
                            lang='C++' if path.endswith('.cpp') else 'C', lines=lines, sel=sel))
    return out


def main():
    fs = functions()
    sizes = sorted(f['lines'] for f in fs)
    t1, t2 = sizes[len(sizes) // 3], sizes[2 * len(sizes) // 3]
    for f in fs:
        f['size'] = 'S' if f['lines'] < t1 else ('M' if f['lines'] < t2 else 'L')
        f['key'] = hashlib.sha256(('%s:0x%06x' % (f['file'], f['addr'])).encode()).hexdigest()
    strata = {}
    for f in sorted(fs, key=lambda f: f['key']):
        strata.setdefault((f['module'], f['lang'], f['size']), []).append(f)
    order = sorted(strata)
    chosen, taken = [], set()

    def round_robin(limit, pred):
        while len(chosen) < limit:
            progress = False
            for s in order:
                if len(chosen) >= limit:
                    break
                for f in strata[s]:
                    if f['key'] not in taken and pred(f):
                        chosen.append(f)
                        taken.add(f['key'])
                        progress = True
                        break
            if not progress:
                break

    round_robin(SELECT_QUOTA, lambda f: f['sel'])
    round_robin(TOTAL, lambda f: True)
    chosen.sort(key=lambda f: (f['file'], f['addr']))

    lines = [
        '# Compiler control set',
        '',
        'Chosen by `tools/toolchains/pick_control.py` from source text only (no scores); its',
        'docstring states the rule. Universe: %d `@implements` functions outside src/control/;' % len(fs),
        'size tertile cut points: S < %d code lines <= M < %d <= L.' % (t1, t2),
        'Select-bearing (uses `?:`, directly or via a same-file macro): %d of %d chosen.' % (
            sum(f['sel'] for f in chosen), len(chosen)),
        '',
        'The sources are scored where they stand; nothing is copied or edited.',
        '',
        '| # | file | address | function | module | lang | size | select |',
        '|---|------|---------|----------|--------|------|------|--------|',
    ]
    for i, f in enumerate(chosen, 1):
        lines.append('| %d | %s | 0x%06x | %s | %s | %s | %s %d | %s |' % (
            i, f['file'], f['addr'], f['name'], f['module'], f['lang'], f['size'], f['lines'],
            'yes' if f['sel'] else ''))
    open(os.path.join(REPO, 'src', 'control', 'CONTROL.md'), 'w').write('\n'.join(lines) + '\n')
    print('%d chosen, %d select-bearing, universe %d' % (
        len(chosen), sum(f['sel'] for f in chosen), len(fs)))


if __name__ == '__main__':
    main()
