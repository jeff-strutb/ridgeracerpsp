#!/usr/bin/env python3
"""Compile one C/C++ source with a psp-gcc on the compile host and bring back its .s and .o.

The two compilers (psp-gcc 1.3.1 and 1.7.1) are 32-bit Intel Linux programs, so they run on a
Linux host reached over SSH. The host and key come from the environment, never from tracked
files:

    RRPSP_CC_HOST   user@host of the compile host
    RRPSP_CC_KEY    path to the SSH private key for it
    RRPSP_REFERENCES  (optional) the references folder holding the toolchain tarballs; default
                    <main checkout>/references

Everything on the host lives under ~/rrpsp/ (toolchains in ~/rrpsp/tc/<version>/, transient
job folders in ~/rrpsp/work/, removed after each job).

Usage:
    cc.py --setup                         copy, verify (sha256) and unpack both toolchains,
                                          and build their -nocmov variants (nocmov.py)
    cc.py [--cc VER] [--no-cache] SRC [FLAG ...]
    cc.py --close                         stop the shared SSH connection

Flags: the command-line flags, then any `/* @cflags: ... */` in the file, are appended to the
pinned defaults (docs/COMPILER.md). `--no-defaults` drops the pinned defaults and
`--no-file-flags` ignores the file's @cflags. Outputs go to
build/cc/<ver>/<path under repo, extension dropped>.{s,o}; both are deleted before anything
else, so a failed compile never leaves a stale result. Results are cached in build/cc-cache/
by a hash of the compiler identity, the flags, the source path and bytes, and the bytes of
every repo header it includes (found by following #include "..." and <...> that resolve under
include/ or next to the file).
"""
import argparse
import hashlib
import io
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import tarfile
import time

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
BUILD = os.path.join(REPO, 'build')
REMOTE_ROOT = 'rrpsp'  # relative to the remote home directory

# Each compiler: its tarball (verified by sha256), the driver inside the unpacked tree, and
# extra -B prefixes. The 1.7.1 tarball ships its driver only as psp/bin/gcc, which cannot find
# its own headers from there, so setup copies it to bin/psp-gcc (the layout 1.3.1 ships); its
# assembler files are empty, so both compilers use the 1.3.1 GNU as 2.14 (the only assembler
# available).
COMPILERS = {
    '1.3.1': {
        'tarball': 'psp-gcc-1.3.1.tar.gz',
        'sha256': '788b6d2c0ed920da6b1e5a350d23dd7ea05820526e23f9b5b967b3b238ea2e2e',
        'driver': 'tc/1.3.1/bin/psp-gcc',
        'prefixes': ['tc/1.3.1/psp/bin/'],
    },
    '1.7.1': {
        'tarball': 'psp-gcc-1.7.1.tar.gz',
        'sha256': '55d4267b1d74855157501d5fd61ed31b68d961a737306b5831b582a2d58f3484',
        'driver': 'tc/1.7.1/bin/psp-gcc',
        'prefixes': ['tc/1.3.1/psp/bin/'],
    },
}
# Variants without integer conditional moves: a copy of the tree whose cc1 and cc1plus have
# had the movsicc optab entry removed by nocmov.py (see its docstring and docs/COMPILER.md).
for _v in ('1.3.1', '1.7.1'):
    COMPILERS[_v + '-nocmov'] = dict(COMPILERS[_v], base=_v, patch='nocmov.py',
                                     driver='tc/%s-nocmov/bin/psp-gcc' % _v)

# Pinned compiler and default flags (docs/COMPILER.md says why).
DEFAULT_CC = '1.3.1-nocmov'
DEFAULT_FLAGS = ['-O2']

CFLAGS_RE = re.compile(r'/\*\s*@cflags:\s*(.*?)\s*\*/')
INCLUDE_RE = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"]', re.M)
CACHE_VERSION = '1'


def die(msg):
    sys.stderr.write('cc.py: %s\n' % msg)
    sys.exit(2)


def host_and_key():
    host = os.environ.get('RRPSP_CC_HOST')
    key = os.environ.get('RRPSP_CC_KEY')
    if not host or not key:
        die('set RRPSP_CC_HOST (user@host) and RRPSP_CC_KEY (key path)')
    return host, os.path.expanduser(key)


def ssh_base():
    host, key = host_and_key()
    # One shared connection (ControlMaster) reused by every call; it closes itself 120 s after
    # the last use, or at once with --close. The socket lives in /tmp because macOS limits
    # socket paths to 104 bytes.
    return ['ssh', '-i', key, '-o', 'IdentitiesOnly=yes', '-o', 'BatchMode=yes',
            '-o', 'ConnectTimeout=10', '-o', 'ServerAliveInterval=5',
            '-o', 'ServerAliveCountMax=3', '-o', 'ControlMaster=auto',
            '-o', 'ControlPath=/tmp/rrpsp-cm-%C', '-o', 'ControlPersist=120', host]


def ssh(cmd, data=None, timeout=120):
    p = subprocess.run(ssh_base() + [cmd], input=data, capture_output=True, timeout=timeout)
    return p.returncode, p.stdout, p.stderr


def references_dir():
    env = os.environ.get('RRPSP_REFERENCES')
    if env:
        return env
    common = subprocess.run(['git', '-C', REPO, 'rev-parse', '--path-format=absolute',
                             '--git-common-dir'], capture_output=True, text=True).stdout.strip()
    return os.path.join(os.path.dirname(common), 'references')


def setup():
    refs = references_dir()
    host, key = host_and_key()
    rc, _, err = ssh('mkdir -p ~/%s/dist ~/%s/work' % (REMOTE_ROOT, REMOTE_ROOT))
    if rc:
        die(err.decode())
    for ver, c in COMPILERS.items():
        if 'base' in c:
            continue
        local = os.path.join(refs, c['tarball'])
        h = hashlib.sha256(open(local, 'rb').read()).hexdigest()
        if h != c['sha256']:
            die('%s: sha256 %s, expected %s' % (local, h, c['sha256']))
        e = ' '.join(shlex.quote(x) for x in ssh_base()[:-1])
        subprocess.run(['rsync', '-a', '-e', e, local, '%s:%s/dist/' % (host, REMOTE_ROOT)],
                       check=True, timeout=300)
    script = r'''set -e
cd ~/%(root)s
%(checks)s
for v in 1.3.1 1.7.1; do rm -rf tc/$v; mkdir -p tc/$v; tar -xzf dist/psp-gcc-$v.tar.gz -C tc/$v; done
mkdir -p tc/1.7.1/bin && cp tc/1.7.1/psp/bin/gcc tc/1.7.1/bin/psp-gcc
for v in 1.3.1 1.7.1; do
  rm -rf tc/$v-nocmov; cp -a tc/$v tc/$v-nocmov
  for c in cc1 cc1plus; do
    L=$(echo tc/$v/lib/gcc-lib/psp/*); N=$(echo tc/$v-nocmov/lib/gcc-lib/psp/*)
    python3 -I dist/nocmov.py $L/$c $N/$c
  done
done
for v in 1.3.1 1.7.1; do
  L=$(echo tc/$v/lib/gcc-lib/psp/*)
  echo "$v cc1:     $($L/cc1 --version </dev/null 2>&1 | head -1)"
  echo "$v cc1plus: $($L/cc1plus --version </dev/null 2>&1 | head -1)"
  echo "$v driver:  $(tc/$v/bin/psp-gcc --version 2>/dev/null | head -1)"
done
echo "as:         $(tc/1.3.1/psp/bin/as --version | head -1)"
''' % {'root': REMOTE_ROOT,
       'checks': '\n'.join('echo "%s  dist/%s" | sha256sum -c -' % (c['sha256'], c['tarball'])
                           for c in COMPILERS.values() if 'base' not in c)}
    e = ' '.join(shlex.quote(x) for x in ssh_base()[:-1])
    subprocess.run(['rsync', '-a', '-e', e, os.path.join(os.path.dirname(__file__), 'nocmov.py'),
                    '%s:%s/dist/' % (host, REMOTE_ROOT)], check=True, timeout=60)
    rc, out, err = ssh(script, timeout=300)
    sys.stdout.write(out.decode())
    if rc:
        die(err.decode())


def local_includes(path, seen):
    """Repo files reached from path by #include, resolved next to the including file, then
    under include/. System headers belong to the compiler (covered by its identity)."""
    try:
        text = open(path, encoding='latin-1').read()
    except OSError:
        return
    for kind, name in INCLUDE_RE.findall(text):
        cands = ([os.path.join(os.path.dirname(path), name)] if kind == '"' else []) + \
                [os.path.join(REPO, 'include', name)]
        for c in cands:
            c = os.path.normpath(c)
            if os.path.isfile(c):
                if c not in seen:
                    seen.add(c)
                    local_includes(c, seen)
                break


def file_flags(src_text):
    flags = []
    for m in CFLAGS_RE.finditer(src_text):
        flags += shlex.split(m.group(1))
    return flags


def outputs_for(src_rel, ver):
    base = os.path.join(BUILD, 'cc', ver, os.path.splitext(src_rel)[0])
    return base + '.s', base + '.o'


def compile_file(src, ver=None, flags=(), use_defaults=True, use_cache=True, verbose=False,
                 use_file_flags=True):
    """Compile src; return dict(s=path, o=path, flags=[...], cached=bool, seconds=float).
    Raises RuntimeError with the compiler's messages on failure."""
    t0 = time.time()
    ver = ver or DEFAULT_CC
    if ver not in COMPILERS:
        raise RuntimeError('unknown compiler %r (have %s)' % (ver, ', '.join(COMPILERS)))
    src = os.path.abspath(src)
    src_rel = os.path.relpath(src, REPO)
    if src_rel.startswith('..'):
        raise RuntimeError('%s is outside the repository' % src)
    s_out, o_out = outputs_for(src_rel, ver)
    for p in (s_out, o_out):
        if os.path.exists(p):
            os.remove(p)
    os.makedirs(os.path.dirname(s_out), exist_ok=True)

    text = open(src, encoding='latin-1').read()
    all_flags = ((list(DEFAULT_FLAGS) if use_defaults else []) + list(flags) +
                 (file_flags(text) if use_file_flags else []))
    headers = set()
    local_includes(src, headers)
    files = [src] + sorted(headers)

    h = hashlib.sha256()
    h.update(('v%s\0%s\0%s\0' % (CACHE_VERSION, ver, COMPILERS[ver]['sha256'])).encode())
    if 'patch' in COMPILERS[ver]:
        h.update(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                   COMPILERS[ver]['patch']), 'rb').read())
    h.update(('\0'.join(all_flags) + '\0\0').encode())
    for f in files:
        h.update(os.path.relpath(f, REPO).encode() + b'\0')
        h.update(hashlib.sha256(open(f, 'rb').read()).digest())
    key = h.hexdigest()
    cdir = os.path.join(BUILD, 'cc-cache', key[:2], key)

    if use_cache and os.path.isfile(os.path.join(cdir, 'out.o')):
        shutil.copyfile(os.path.join(cdir, 'out.s'), s_out)
        shutil.copyfile(os.path.join(cdir, 'out.o'), o_out)
        return dict(s=s_out, o=o_out, flags=all_flags, cached=True, seconds=time.time() - t0)

    buf = io.BytesIO()
    with tarfile.open(fileobj=buf, mode='w') as tf:
        for f in files:
            tf.add(f, arcname=os.path.relpath(f, REPO))
    c = COMPILERS[ver]
    q = shlex.quote
    bflags = ' '.join('-B"$R"/%s' % q(p) for p in c['prefixes'])
    fl = ' '.join(q(x) for x in all_flags)
    script = r'''R=~/%(root)s
J=$(mktemp -d "$R"/work/job.XXXXXX) || exit 3
cd "$J" && tar -xf - || exit 3
mkdir out
{ "$R"/%(drv)s %(B)s -Iinclude %(fl)s -S %(src)s -o out/out.s &&
  "$R"/%(drv)s %(B)s %(fl)s -c out/out.s -o out/out.o; echo $? > out/rc; } > out/log 2>&1
tar -cf - -C out .
cd / && rm -rf "$J"
''' % {'root': REMOTE_ROOT, 'drv': c['driver'], 'B': bflags, 'fl': fl, 'src': q(src_rel)}
    if verbose:
        sys.stderr.write(script)
    rc, out, err = ssh(script, data=buf.getvalue())
    if rc:
        raise RuntimeError('remote job failed (ssh rc %d): %s' % (rc, err.decode(errors='replace')))
    res = {}
    with tarfile.open(fileobj=io.BytesIO(out), mode='r') as tf:
        for m in tf.getmembers():
            if m.isfile():
                res[os.path.basename(m.name)] = tf.extractfile(m).read()
    log = res.get('log', b'').decode(errors='replace')
    if res.get('rc', b'1').strip() != b'0' or 'out.o' not in res or 'out.s' not in res:
        raise RuntimeError('compile failed:\n' + log)
    if log.strip() and verbose:
        sys.stderr.write(log)
    tmp = cdir + '.tmp%d' % os.getpid()
    os.makedirs(tmp, exist_ok=True)
    for n in ('out.s', 'out.o', 'log'):
        open(os.path.join(tmp, n), 'wb').write(res.get(n, b''))
    json.dump(dict(src=src_rel, ver=ver, flags=all_flags,
                   headers=[os.path.relpath(f, REPO) for f in files[1:]]),
              open(os.path.join(tmp, 'meta.json'), 'w'), indent=1)
    if os.path.isdir(cdir):
        shutil.rmtree(cdir)
    os.replace(tmp, cdir)
    open(s_out, 'wb').write(res['out.s'])
    open(o_out, 'wb').write(res['out.o'])
    return dict(s=s_out, o=o_out, flags=all_flags, cached=False, seconds=time.time() - t0)


def close():
    host, _ = host_and_key()
    subprocess.run(ssh_base()[:-1] + ['-O', 'exit', host], capture_output=True, timeout=30)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--setup', action='store_true')
    ap.add_argument('--close', action='store_true')
    ap.add_argument('--cc', choices=sorted(COMPILERS), default=None)
    ap.add_argument('--no-cache', action='store_true')
    ap.add_argument('--no-defaults', action='store_true')
    ap.add_argument('--no-file-flags', action='store_true', help='ignore @cflags in the file')
    ap.add_argument('-v', '--verbose', action='store_true')
    ap.add_argument('src', nargs='?')
    ap.add_argument('flags', nargs=argparse.REMAINDER)
    a = ap.parse_args()
    if a.setup:
        setup()
        return
    if a.close:
        close()
        return
    if not a.src:
        ap.error('give a source file')
    try:
        r = compile_file(a.src, a.cc, a.flags, not a.no_defaults, not a.no_cache, a.verbose,
                         not a.no_file_flags)
    except RuntimeError as e:
        sys.stderr.write(str(e) + '\n')
        sys.exit(1)
    print('%s\n%s\n%s %s, %s, %.2f s' % (r['s'], r['o'], a.cc or DEFAULT_CC, ' '.join(r['flags']),
                                         'cached' if r['cached'] else 'compiled', r['seconds']))


if __name__ == '__main__':
    main()
