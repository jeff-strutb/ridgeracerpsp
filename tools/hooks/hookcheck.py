#!/usr/bin/env python3
"""Checks behind the git hooks in this folder; validate.py runs them on the tree too.

    attribution(text)            lines that credit an AI tool (see PATTERNS)
    tag_problems(src, check)     tags without a WHAT IT DOES paragraph (in the files `check`),
                                 malformed tags, and addresses tagged twice outside control/
    grade(src, files)            score.py verdicts for the @implements tags in `files`, with
                                 the tree under `src` as the cross-file index
    pre_commit() / commit_msg(path)   the hooks themselves

The pre-commit hook grades what is STAGED, not the working tree: it writes the index's copy of
src/ and include/ (and of any other staged source) to build/hook/stage/ and compiles that.
It fails closed: without RRPSP_CC_HOST and RRPSP_CC_KEY it refuses, since it cannot grade.

The attribution patterns are assembled from pieces so that this file does not match them.
"""
import re
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / 'tools'))

_AI = (r'(?:cl' r'aude|anthr' r'opic|open' r'ai|chat' r'gpt|gpt-?\d|co' r'pilot|gem' r'ini'
       r'|\ba' r'i\b|\bl' r'lm\b|language model)')
PATTERNS = [
    ('co-author trailer naming an AI tool',
     re.compile(r'co' r'-?auth' r'ored-?by\s*:.*' + _AI, re.I)),
    ('"generated with/by" an AI tool',
     re.compile(r'gener' r'ated\s+(?:with|by|using)\s+\[?(?:an?\s+)?' + _AI, re.I)),
    ('authorship credited to an AI tool',
     re.compile(r'(?:writ' r'ten|author' r'ed|creat' r'ed|produc' r'ed)\s+(?:by|with)\s+'
                r'(?:an?\s+)?' + _AI, re.I)),
    ('assisted-by-AI phrase', re.compile(_AI + r'[- ]assi' r'sted', re.I)),
    ('help from an AI tool',
     re.compile(r'with\s+(?:the\s+)?(?:help|assistance)\s+(?:of|from)\s+(?:an?\s+)?' + _AI, re.I)),
    ('robot-emoji attribution', re.compile('\U0001F916')),
    ('AI vendor link or address', re.compile(r'cl' r'aude\.(?:ai|com)/|@anthr' r'opic\.com', re.I)),
]
STAGE = ROOT / 'build' / 'hook' / 'stage'


def attribution(text):
    out = []
    for n, line in enumerate(text.splitlines(), 1):
        for what, rx in PATTERNS:
            if rx.search(line):
                out.append((n, what, line.strip()[:120]))
                break
    return out


def tag_problems(src, check=None, extra=()):
    """Problems with the tags of the tree under src (plus the files `extra`): malformed tags
    and tags without WHAT IT DOES in the files `check` (all files when None), and every
    address tagged twice in files outside src/control/ (extra files count as outside)."""
    import score
    src = Path(src)
    probs, seen = [], {}
    check = None if check is None else {Path(p).resolve() for p in check}
    extra = [Path(e).resolve() for e in extra]
    for p in list(score.source_files(src)) + extra:
        tags, pr = score.parse_tags(p)
        mine = check is None or p.resolve() in check
        if mine:
            probs += ['%s:%d: %s' % x for x in pr]
            probs += ['%s:%d: @%s %#08x has no WHAT IT DOES paragraph' % (
                t.path, t.line, t.kind, t.addr) for t in tags if not t.what]
        if score.is_real(p, src) or p in extra:
            for t in tags:
                seen.setdefault(t.addr, []).append('%s:%d' % (t.path, t.line))
    for a, w in sorted(seen.items()):
        if len(w) > 1:
            probs.append('%#08x is tagged %d times outside control/: %s' % (a, len(w), ', '.join(w)))
    return probs


def grade(src, files):
    import score
    tree = score.Tree(src=src)
    g = score.Grader(tree)
    tree.compile_many(files)
    res = []
    for p in files:
        u = tree.unit(p)
        res += [r for r in g.grade_unit(u) if r['kind'] == 'implements']
    g.finalize(res)
    return res


def git(*args, inp=None):
    p = subprocess.run(['git', '-C', str(ROOT)] + list(args), input=inp, capture_output=True)
    if p.returncode:
        raise SystemExit('hook: git %s failed: %s' % (' '.join(args), p.stderr.decode()))
    return p.stdout


def staged_paths():
    out = git('diff', '--cached', '--name-only', '-z', '--diff-filter=ACMR')
    return [x.decode() for x in out.split(b'\0') if x]


def staged_added_lines():
    """{path: text of the added lines} of the staged diff."""
    out = git('diff', '--cached', '-U0', '--no-color', '--no-ext-diff').decode('utf-8', 'replace')
    added, cur = {}, None
    for line in out.splitlines():
        if line.startswith('+++ '):
            cur = line[6:] if line.startswith('+++ b/') else None
        elif line.startswith('+') and cur is not None:
            added.setdefault(cur, []).append(line[1:])
    return {k: '\n'.join(v) for k, v in added.items()}


def mirror(extra):
    """Write the index's copy of src/, include/ and the paths in extra under STAGE."""
    if STAGE.exists():
        shutil.rmtree(STAGE)
    STAGE.mkdir(parents=True)
    names = [x for x in git('ls-files', '-z', '--', 'src', 'include').split(b'\0') if x]
    names += [e.encode() for e in extra]
    git('checkout-index', '-f', '-z', '--stdin', '--prefix=%s/' % STAGE, inp=b'\0'.join(names))


def pre_commit():
    import os
    import score
    refuse = []
    for path, text in staged_added_lines().items():
        for n, what, line in attribution(text):
            refuse.append('%s: added line %d: %s: %s' % (path, n, what, line))
    staged = staged_paths()
    sources = [s for s in staged if s.endswith(score.SOURCE_SUFFIXES)]
    tagged = []
    for s in sources:
        blob = git('show', ':' + s).decode('latin-1')
        if score.TAG_ANY.search(blob):
            tagged.append(s)
    if tagged:
        mirror([s for s in tagged if not s.startswith(('src/', 'include/'))])
        staged_files = [STAGE / s for s in tagged]
        outside = [STAGE / s for s in tagged if not s.startswith('src/')]
        for pr in tag_problems(STAGE / 'src', staged_files, outside):
            refuse.append(pr.replace(str(STAGE.relative_to(ROOT)) + '/', ''))
        if not (os.environ.get('RRPSP_CC_HOST') and os.environ.get('RRPSP_CC_KEY')):
            refuse.append('cannot grade %d staged tagged source(s): set RRPSP_CC_HOST and '
                          'RRPSP_CC_KEY' % len(tagged))
        else:
            for r in grade(STAGE / 'src', staged_files):
                if r['verdict'] != 'EXACT':
                    refuse.append('%s:%d: @implements %#08x %s is %s: %s' % (
                        r['file'].replace(str(STAGE.relative_to(ROOT)) + '/', ''), r['line'],
                        r['addr'], r['name'], r['verdict'], r['detail'][:200]))
    if refuse:
        sys.stderr.write('pre-commit: REFUSED\n' + ''.join('  %s\n' % x for x in refuse))
        return 1
    if tagged:
        sys.stderr.write('pre-commit: %d staged tagged source(s): every @implements EXACT, '
                         'every tag explained, no address tagged twice\n' % len(tagged))
    return 0


def commit_msg(path):
    text = '\n'.join(l for l in Path(path).read_text(encoding='utf-8', errors='replace')
                     .splitlines() if not l.startswith('#'))
    bad = attribution(text)
    if bad:
        sys.stderr.write('commit-msg: REFUSED: attribution in the commit message\n' +
                         ''.join('  line %d: %s: %s\n' % b for b in bad))
        return 1
    return 0
