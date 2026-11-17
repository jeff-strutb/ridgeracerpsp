#!/usr/bin/env python3
"""Every gate in one run, each with its time.

    tools/validate.py [--no-cache] [--skip-faults] [--faults-only]

Gates, in order (exit status 1 if any is red):
  reference    tools/refcheck.py: the six reference executables have their recorded MD5s.
  tags         every tag in a real file is well formed and has a WHAT IT DOES paragraph, and
               no address is tagged twice outside src/control/ (tools/hooks/hookcheck.py).
  attribution  no tracked file, and no commit message on this branch since main, carries
               AI-attribution text (the hooks' patterns).
  libsyms      config/us/libsyms.csv is what tools/analysis/libsyms.py builds now (--check).
  compiler     the control set (src/control/CONTROL.md, 60 functions): every function's size,
               words and relocation types equal retail's (no DIFFERS, no MISSING), which is
               what pins the compiler.  How many are also EXACT (references proven) is printed.
  image        tools/image.py, the M2 gate over every real file.
  tiers        tools/progress.py's table, from the image gate's result.
  faults       planted faults, each of which must be caught by the gate meant to catch it:
                 1 a global moved by 4 bytes in an EXACT function     score BADREF, image red
                 2 one character of a string literal changed          score BADREF, image red
                 3 a float constant changed                           score BADREF, image red
                 4 two same-shaped callees swapped                    score BADREF, image red
                 5 a stale object left in build/ (fault 1's copy with the good object at its
                   output path): the gate recompiles and is red; and, with the compile step
                   made to leave the stale object in place, the freshness check reports it
                 6 a function removed from the placed set              image red (count)
                 7 a non-EXACT @implements staged for commit           pre-commit refuses
                 8 a library call site pointed at another library function: libsyms refuses
                   the symbol (tools/analysis/libsyms.py --selftest)
                 + commit-msg refuses an attribution trailer; the tags check flags a missing
                   WHAT IT DOES and an address tagged twice
               Planted copies live under build/plant/; src/ and the git index are not touched
               (fault 7 stages into a temporary index through GIT_INDEX_FILE).  Each fault is
               shown against a baseline that is green for the same scope.

Needs RRPSP_CC_HOST, RRPSP_CC_KEY and ./setup.sh.
"""
import argparse
import os
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE / 'hooks')]
import score                    # noqa: E402
import image                    # noqa: E402
import progress                 # noqa: E402
import hookcheck                # noqa: E402
import cc                       # noqa: E402

ROOT = score.ROOT
PLANT = ROOT / 'build' / 'plant'

FAULTS = [
    ('global moved by 4 bytes', 'src/sequence/FadeColourState.c', 0x0e9e08,
     'D_1d5a80 = 1;', '(&D_1d5a80)[1] = 1;'),
    ('string literal changed by one character', 'src/sound/RadioCommon.cpp', 0x10abd0,
     'CheckPlayCh Failed!', 'CheckPlayCh Failed?'),
    ('float constant changed', 'src/race/SpeedUnit.c', 0x06b714, '1.609344f', '1.609345f'),
    ('same-shaped callees swapped', 'src/race/FadeSequence.cpp', 0x0ff7f0,
     'f_100bbc();\n    f_0e9eb4();', 'f_0e9eb4();\n    f_100bbc();'),
]


def plant(tag, rel, addr, old, new):
    """Copy rel to build/plant/<tag>/rel with the first `old` after the tag of addr replaced."""
    text = (ROOT / rel).read_text(encoding='latin-1')
    at = text.index('@implements 0x%06x ' % addr)
    k = text.index(old, at)
    dst = PLANT / tag / rel
    dst.parent.mkdir(parents=True, exist_ok=True)
    dst.write_text(text[:k] + new + text[k + len(old):], encoding='latin-1')
    return dst


def grade_one(path, addr, tree=None):
    tree = tree or score.Tree()
    g = score.Grader(tree)
    u = tree.unit(path)
    r = [x for x in g.grade_unit(u) if x['addr'] == addr]
    g.finalize(r)
    return r[0] if r else None


class Run:
    def __init__(self):
        self.rows = []

    def gate(self, name, fn):
        t = time.time()
        try:
            ok, note = fn()
        except SystemExit as e:
            ok, note = False, 'exited %s' % e.code
        el = time.time() - t
        self.rows.append((name, ok, el, note))
        print('%-12s %-5s %6.2f s  %s' % (name, 'GREEN' if ok else 'RED', el, note), flush=True)
        return ok


def g_reference():
    p = subprocess.run([sys.executable, str(ROOT / 'tools' / 'refcheck.py')], capture_output=True,
                       text=True)
    return p.returncode == 0, '%d files checked' % p.stdout.count('ok ')


def g_tags():
    real = [p for p in score.source_files() if score.is_real(p)]
    probs = hookcheck.tag_problems(score.SRC, real)
    for x in probs[:20]:
        print('    ' + x)
    n = sum(len(score.parse_tags(p)[0]) for p in real)
    return not probs, '%d tags in %d real files, %d problems' % (n, len(real), len(probs))


def g_attribution():
    files = subprocess.run(['git', '-C', str(ROOT), 'ls-files', '-z'], capture_output=True
                           ).stdout.split(b'\0')
    bad = []
    for f in filter(None, files):
        p = ROOT / f.decode()
        if p.is_file():
            for n, what, line in hookcheck.attribution(p.read_text(encoding='utf-8', errors='replace')):
                bad.append('%s:%d: %s' % (f.decode(), n, what))
    base = subprocess.run(['git', '-C', str(ROOT), 'merge-base', 'HEAD', 'main'],
                          capture_output=True, text=True).stdout.strip()
    msgs = subprocess.run(['git', '-C', str(ROOT), 'log', '--format=%H%x00%B%x01',
                           '%s..HEAD' % base], capture_output=True, text=True).stdout if base else ''
    nmsg = 0
    for m in filter(str.strip, msgs.split('\x01')):
        h, _, body = m.strip().partition('\0')
        nmsg += 1
        for n, what, line in hookcheck.attribution(body):
            bad.append('commit %s line %d: %s' % (h[:10], n, what))
    for b in bad[:20]:
        print('    ' + b)
    return not bad, '%d tracked files, %d commit messages since main, %d hits' % (
        len(files) - 1, nmsg, len(bad))


def g_libsyms():
    p = subprocess.run([sys.executable, str(ROOT / 'tools' / 'analysis' / 'libsyms.py'),
                        '--check'], capture_output=True, text=True)
    return p.returncode == 0, (p.stdout.strip().splitlines() or ['no output'])[-1]


def g_compiler():
    tree = score.Tree()
    g = score.Grader(tree)
    groups = {}
    for f, a in score.control_list():
        groups.setdefault(f, set()).add(a)
    res = []
    for f, w in sorted(groups.items()):
        res += g.grade_unit(tree.unit(ROOT / f), w)
    g.finalize(res)
    c = {}
    for r in res:
        c[r['verdict']] = c.get(r['verdict'], 0) + 1
    words = c.get('EXACT', 0) + c.get('BADREF', 0)
    for r in res:
        if r['verdict'] in ('DIFFERS', 'MISSING'):
            print('    ' + score.fmt(r))
    return words == len(res) == 60, '%d/%d words equal; EXACT %d, BADREF %d' % (
        words, len(res), c.get('EXACT', 0), c.get('BADREF', 0))


STATE = {}


def g_image(no_cache):
    res = image.run(no_cache)
    STATE['gate'] = res
    for f in res['fails']:
        print('    FAIL ' + f)
    return res['green'], '%d of %d @implements placed; compile %.2f s (%d compiled, %d cached)' % (
        res['placed'], res['implements'], res['seconds']['compile'], res['compiled'], res['cached'])


def g_tiers():
    tiers, cut = progress.compute(STATE['gate'])
    names = list(tiers)
    t = tiers[names[0]]
    print('    proven game: ' + '  '.join('%s %d fn %d B' % (k, v[0], v[1]) for k, v in t.items()
                                         if k != 'placed-by-red-gate'))
    u = tiers[names[1]]
    print('    information only: unknown before %#08x: %d fn, tagged %d, EXACT and placed %d' % (
        cut, sum(v[0] for k, v in u.items() if k != 'placed-by-red-gate'),
        u['T2'][0] + u['T4'][0], u['placed-by-red-gate'][0] + u['T4'][0]))
    return True, 'from the image gate (%s)' % ('green' if STATE['gate']['green'] else 'red: T4 is 0')


def faults():
    """Return [(name, caught, evidence)]."""
    out = []
    if PLANT.exists():
        shutil.rmtree(PLANT)
    tree = score.Tree()
    files = [rel for _, rel, _, _, _ in FAULTS]
    base = image.run(only=files)
    out.append(('baseline: score and image on the four files', base['green'] and
                all(r['verdict'] == 'EXACT' for r in base['results'] if r['addr'] in
                    {a for _, _, a, _, _ in FAULTS}),
                'image %s, %d/%d EXACT' % ('GREEN' if base['green'] else 'RED',
                                         sum(r['verdict'] == 'EXACT' for r in base['results']),
                                         len(base['results']))))
    copies = {}
    for k, (name, rel, addr, old, new) in enumerate(FAULTS, 1):
        cp = plant('f%d' % k, rel, addr, old, new)
        copies[k] = cp
        r = grade_one(cp, addr, tree)
        im = image.run(replace=[(str(ROOT / rel), str(cp))], only=[rel])
        caught = r['verdict'] == 'BADREF' and not im['green']
        ev = 'score %s: %s | image %s: %s' % (r['verdict'], r['detail'][:160],
                                              'GREEN' if im['green'] else 'RED',
                                              '; '.join(im['fails'])[:160])
        if k == 1:
            # The byte comparison on its own: the faulty function forced into the image with
            # its compiled targets, as a grader that missed the fault would place it.
            fo = image.run(replace=[(str(ROOT / rel), str(cp))], only=[rel], force=[addr])
            byte = any('bytes differ' in f for f in fo['fails'])
            caught = caught and byte and not fo['green']
            ev += ' | forced into the image: %s' % '; '.join(
                f for f in fo['fails'] if 'differ' in f)[:160]
        out.append(('%d %s (%s %#08x)' % (k, name, rel, addr), caught, ev))
    # 5: a stale object.  (a) The good object of the real file is put at the output path of
    # fault 1's copy, newer than the source; the gate must recompile and still be red.
    cp = copies[1]
    good = Path(cc.compile_file(str(ROOT / FAULTS[0][1]))['o'])
    _, stale_o = cc.outputs_for(os.path.relpath(cp, ROOT), cc.DEFAULT_CC)
    shutil.copyfile(good, stale_o)
    r = grade_one(cp, FAULTS[0][2])
    im = image.run(replace=[(str(ROOT / FAULTS[0][1]), str(cp))], only=[FAULTS[0][1]])
    a_ok = r['verdict'] == 'BADREF' and not im['green']
    # (b) The compile step is made to return without writing, leaving the stale object (an hour
    # old) in place: the freshness check must refuse it.
    shutil.copyfile(good, stale_o)
    old = time.time() - 3600
    os.utime(stale_o, (old, old))
    real_compile = cc.compile_file

    def lazy(src, ver=None, *a, **k):
        if Path(src).resolve() == cp.resolve():
            s, o = cc.outputs_for(os.path.relpath(src, ROOT), ver or cc.DEFAULT_CC)
            return dict(s=s, o=o, flags=[], cached=True, seconds=0.0)
        return real_compile(src, ver, *a, **k)
    cc.compile_file = lazy
    try:
        r2 = grade_one(cp, FAULTS[0][2])
    finally:
        cc.compile_file = real_compile
    b_ok = r2['verdict'] == 'MISSING' and 'stale' in r2['detail']
    out.append(('5 stale object left in build/', a_ok and b_ok,
                '(a) good object at the output path: score %s, image %s | (b) compile step '
                'leaves it: score %s: %s' % (r['verdict'], 'GREEN' if im['green'] else 'RED',
                                             r2['verdict'], r2['detail'][:120])))
    # 6: one EXACT function left out of the placed set.
    im = image.run(drop=[FAULTS[0][2]], only=[FAULTS[0][1]])
    out.append(('6 function removed from the placed set (%#08x)' % FAULTS[0][2], not im['green'],
                'image %s: %s' % ('GREEN' if im['green'] else 'RED', '; '.join(im['fails']))))
    # 7: pre-commit with fault 1's copy staged over the real file in a temporary index.
    out.append(hook_fault(copies[1]))
    # 8: libsyms refuses a symbol with one call site pointed at another library function.
    p = subprocess.run([sys.executable, str(ROOT / 'tools' / 'analysis' / 'libsyms.py'),
                        '--selftest'], capture_output=True, text=True)
    lines = p.stdout.strip().splitlines()
    out.append(('8 library call site pointed at another library function', p.returncode == 0,
                ' | '.join(l for l in lines if 'after' in l or 'other rows' in l)[:240]))
    # commit-msg and tag checks.
    with tempfile.NamedTemporaryFile('w', suffix='.msg', delete=False) as fh:
        fh.write('Change something\n\nCo-' + 'Authored-By: Cl' + 'aude <noreply@anthr' +
                 'opic.com>\n')
    rc = hookcheck.commit_msg(fh.name)
    os.unlink(fh.name)
    out.append(('commit-msg with an attribution trailer', rc == 1, 'exit %d' % rc))
    nw = PLANT / 'nowhat' / 'src' / 'x' / 'NoWhat.c'
    nw.parent.mkdir(parents=True)
    nw.write_text('/* @implements 0x0e9e08 us f_0e9e08 */\nvoid f_0e9e08(void) {}\n')
    dup = PLANT / 'nowhat' / 'src' / 'x' / 'Dup.c'
    dup.write_text('/* @implements 0x0e9e08 us f_0e9e08\n   WHAT IT DOES: x. */\n')
    pr = hookcheck.tag_problems(PLANT / 'nowhat' / 'src')
    out.append(('tags: missing WHAT IT DOES and an address tagged twice',
                any('WHAT IT DOES' in x for x in pr) and any('tagged 2 times' in x for x in pr),
                '; '.join(pr)[:200]))
    shutil.rmtree(PLANT)
    return out


def hook_fault(copy):
    rel = FAULTS[0][1]
    real_index = subprocess.run(['git', '-C', str(ROOT), 'rev-parse', '--git-path', 'index'],
                                capture_output=True, text=True).stdout.strip()
    real_index = Path(real_index) if os.path.isabs(real_index) else ROOT / real_index
    with tempfile.TemporaryDirectory() as td:
        idx = Path(td) / 'index'
        shutil.copyfile(real_index, idx)
        env = dict(os.environ, GIT_INDEX_FILE=str(idx))
        blob = subprocess.run(['git', '-C', str(ROOT), 'hash-object', '-w', str(copy)],
                              capture_output=True, text=True, check=True).stdout.strip()
        subprocess.run(['git', '-C', str(ROOT), 'update-index', '--cacheinfo',
                        '100644,%s,%s' % (blob, rel)], env=env, check=True)
        p = subprocess.run([sys.executable, str(HERE / 'hooks' / 'pre-commit')], env=env,
                           capture_output=True, text=True, cwd=str(ROOT))
    msg = p.stderr.strip().splitlines()
    caught = p.returncode != 0 and any('0x0e9e08' in m and 'BADREF' in m for m in msg)
    return ('7 pre-commit with a non-EXACT @implements staged (%s)' % rel, caught,
            'exit %d: %s' % (p.returncode, ' | '.join(msg)[:240]))


def g_faults():
    res = faults()
    for name, ok, ev in res:
        print('    %-6s %s\n           %s' % ('caught' if ok else 'MISSED', name, ev))
    st = subprocess.run(['git', '-C', str(ROOT), 'status', '--porcelain', '--', 'src', 'config'],
                        capture_output=True, text=True).stdout
    if st:
        print('    src/ or config/ changed:\n' + st)
    return all(ok for _, ok, _ in res) and not st, '%d/%d caught; src/ and config/ unchanged' % (
        sum(ok for _, ok, _ in res), len(res))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--no-cache', action='store_true')
    ap.add_argument('--skip-faults', action='store_true')
    ap.add_argument('--faults-only', action='store_true')
    a = ap.parse_args(argv)
    t0 = time.time()
    run = Run()
    if not a.faults_only:
        run.gate('reference', g_reference)
        run.gate('tags', g_tags)
        run.gate('attribution', g_attribution)
        run.gate('libsyms', g_libsyms)
        run.gate('compiler', g_compiler)
        if run.gate('image', lambda: g_image(a.no_cache)) or 'gate' in STATE:
            run.gate('tiers', g_tiers)
    if not a.skip_faults:
        run.gate('faults', g_faults)
    red = [n for n, ok, _, _ in run.rows if not ok]
    print('validate: %s in %.2f s%s' % ('GREEN' if not red else 'RED', time.time() - t0,
                                        '' if not red else ' (red: %s)' % ', '.join(red)))
    return 1 if red else 0


if __name__ == '__main__':
    sys.exit(main())
