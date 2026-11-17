#!/usr/bin/env python3
"""A5, the per-function behaviour gate, run together with A7 on the M1 image.

Retail and build/image/BOOT.M1.BIN (tools/oracle/m1image.py) are run in rrbox on every script with
every tagged function (@implements and @draft, outside src/control/) watched. For each watched
call rrbox logs (Core/RRBox.cpp):
  E  entry: call number, thread, a0-a3, t0-t1, f12-f15
  R  return: v0, v1, f0, the count and hash of every memory write the call made outside its own
     stack frame (callees included, its own thread only), and which of s0-s8 came back changed.
A function PASSES when it was called at least once and every call agrees with retail on: the
entry record; v0 (unless it returns void), v1 (64-bit returns) and f0 (float returns), from its
declared return type; the call's net effect on memory (rrbox hashes what each written byte ends
as, so store order and repeated stores do not count); and no callee-saved register clobbered. UNCOVERED = never
called by any script: not passed. Instruction coverage is measured on the candidate body (union
over scripts). The verdicts go to config/us/t3_live.csv with the source file's hash: a @draft is
T3 only while its row says PASS with full coverage and the hash still matches its source. A7 (--m1: code left out of the RAM hash) runs in the same
pass, so a candidate must also leave every frame's RAM identical.

Time-equalised lockstep: a T3 body may take a different number of CPU cycles, and game code
that reads the clock would then store different values. The candidate run is given retail's call
log (--rr-cycles-ref), and at each watched return rrbox sets emulated time to exactly where retail
was. Behaviour is compared with CPU time held equal at every function boundary; an interrupt
landing inside a T3 body at a different point still shows up as a difference.

    python3 tools/oracle/a5.py [--keep] [--detail] [SCRIPT...]

Disk use: one script's call log runs to several GB (the race script's retail log is 8 GB), so
nothing is kept that a later run cannot rebuild. Retail runs are written straight into
build/oracle/retail-cache as <script>-<key>, and caching a new key for a script evicts that
script's older keys. The candidate's logs in build/oracle/a7 are deleted once the verdicts are
written, unless --keep is given (tools/oracle/isolate.py needs both logs: --keep also links the
cached retail log there as <script>.retail.calls). A diverging candidate's log can be far longer
than retail's (7.6 GB against 256 MB on fault_loader_open), so a run refuses to start with less
than MIN_FREE_GB free.
"""
import csv
import datetime
import glob
import hashlib
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'oracle'))
import a7  # noqa: E402

CACHE = os.path.join(ROOT, 'build/oracle/retail-cache')
MIN_FREE_GB = 80  # a full run's peak: every candidate log at its cap (twice retail's), plus uncached retail

TAG = re.compile(r'@(implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)(?:.*?\*/)\s*\n([^\n{;]*?)\b\3\s*\(', re.S)


INT_ARGS = ('a0', 'a1', 'a2', 'a3', 't0', 't1')  # the argument registers rrbox logs, in order
FLOAT_ARGS = ('f12', 'f13', 'f14', 'f15')


def arg_keys(text, start, name):
    """The entry fields a function's declared parameters occupy (the parameter list opens at
    text[start]), or None when it cannot tell (a variadic function, a list it cannot split). A
    register the function takes no parameter in holds whatever earlier code left there, which is
    not behaviour. A member function's `this` takes a0."""
    depth, i = 0, start
    while i < len(text):
        depth += {'(': 1, ')': -1}.get(text[i], 0)
        if depth == 0:
            break
        i += 1
    params = text[start + 1:i].strip()
    if '...' in params or i >= len(text):
        return None
    ints, floats = int('::' in name and not name.startswith('_Z')), 0
    parts, depth, cur = [], 0, ''
    for ch in params:
        depth += {'(': 1, '<': 1, ')': -1, '>': -1}.get(ch, 0)
        if ch == ',' and depth == 0:
            parts.append(cur); cur = ''
        else:
            cur += ch
    parts.append(cur)
    for p in (x.strip() for x in parts):
        if not p or p == 'void':
            continue
        if re.search(r'\b(float|double)\b', p) and '*' not in p and '&' not in p:
            floats += 1
        elif re.search(r'long long|u64|s64', p) and '*' not in p:
            ints += (ints & 1) + 2  # a 64-bit value takes an aligned register pair
        else:
            ints += 1
    # parameters beyond the logged registers go on the stack or in registers rrbox does not log
    return frozenset(('t',) + INT_ARGS[:ints] + FLOAT_ARGS[:floats])


def source_name(tag):
    """The identifier a tag's definition is written with: the tag itself, or for a mangled C++ name
    the last component (`_ZN3Map10CExcelData4Find` -> Find; a constructor or destructor, C1/C2/D0..D2,
    -> its class name)."""
    if not tag.startswith('_Z'):
        tail = re.search(r'(\d+)([A-Za-z_]\w*)$', tag)  # a half-mangled tag: CLoadJob5Begin -> Begin
        if tail and len(tail.group(2)) == int(tail.group(1)) and tail.start() > 0:
            return tail.group(2)
        return tag
    names, k = [], 2 + (tag[2] == 'N')
    while tag[2] == 'N' and k < len(tag) and tag[k] in 'rVK':  # CV-qualifiers of a member function
        k += 1
    while k < len(tag):
        if tag[k].isdigit():
            n = re.match(r'\d+', tag[k:]).group()
            k += len(n)
            names.append(tag[k:k + int(n)])
            k += int(n)
        elif tag[k] == 'I':  # template arguments: skip to the matching E
            depth = 0
            while k < len(tag):
                if tag[k] == 'I':
                    depth += 1
                elif tag[k] == 'E':
                    depth -= 1
                    if depth == 0:
                        break
                elif tag[k].isdigit():  # a name inside the arguments: skip it whole
                    n = re.match(r'\d+', tag[k:]).group()
                    k += len(n) + int(n) - 1
                k += 1
            k += 1
        else:
            break
    return names[-1] if names else tag


def definition(text, start, name):
    """(return-type text, name as written, index of its '(') of the first definition of `name`
    after `start`, up to the end of the next function body, or None. A declaration (ending in ';')
    is skipped; tags stacked on one definition (a C1 and C2 constructor) all reach it."""
    stop = re.compile(r'\n\}(?!;)').search(text, start)  # a function's closing brace, not a struct's
    end = stop.end() if stop else len(text)
    for m in re.finditer(r'(~?(?:\w+::)*~?' + re.escape(name) + r')\s*\(', text[start:end]):
        paren = start + m.end() - 1
        depth, i = 0, paren
        while i < len(text):
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            if depth == 0:
                break
            i += 1
        after = re.match(r'[^;{]*', text[i + 1:]).group()
        if i + 1 + len(after) >= len(text) or text[i + 1 + len(after)] != '{':
            continue
        line = text.rfind('\n', 0, start + m.start()) + 1
        ret = text[line:start + m.start()].strip()
        if re.search(r'[;{}]', ret):
            ret = ''
        return ret, m.group(1), paren
    return None


def watched():
    """{addr: (kind, name, return-kind, entry fields compared)} for every tagged function outside
    src/control/; the entry fields are None (compare them all) when the parameters are unknown.

    Every tag is watched. Its signature is the first definition of the tagged name after the tag's
    comment (other declarations may sit in between); when none is found the function is still
    watched, its return taken as int and every entry field compared. (A single regex over comment
    and definition once let a tag it could not pair swallow the next one: 1,826 of 5,419 tags, and
    158 of 537 placed drafts, went unwatched.)"""
    out = {}
    for path in glob.glob(os.path.join(ROOT, 'src/**/*.c*'), recursive=True):
        if '/src/control/' in path:
            continue
        text = open(path).read()
        for m in re.finditer(r'@(implements|draft)\s+0x([0-9a-fA-F]+)\s+us\s+([A-Za-z_][\w:~]*)', text):
            kind, a, name = m.groups()
            rk, keys = 'int', None
            # compiler-generated functions with no definition in the source, and their fixed signatures
            if name.startswith('_GLOBAL__'):
                out[int(a, 16)] = (kind, name, 'void', frozenset({'t'}))
                continue
            if name.startswith('__static_initialization_and_destruction'):
                out[int(a, 16)] = (kind, name, 'void', frozenset({'t', 'a0', 'a1'}))
                continue
            end = text.find('*/', m.end())
            d = definition(text, end + 2, source_name(name)) if end >= 0 else None
            if d:
                ret, fn, paren = d
                bare = re.sub(r'\b(static|inline|extern|virtual|const|__attribute__\(\(.*?\)\))\s*', '', ret).strip()
                if not bare or '~' in fn:  # a constructor or destructor
                    rk = 'void'
                elif '*' in bare or '&' in bare:
                    rk = 'int'
                elif re.fullmatch(r'void', bare):
                    rk = 'void'
                elif re.search(r'\b(float|double)\b', bare):
                    rk = 'float'
                elif re.search(r'long long|u64|s64', bare):
                    rk = 'wide'
                keys = arg_keys(text, paren, fn)
            elif re.search(r'[CD][0-2]Ev$', name):  # an implicit constructor or destructor: this only
                rk, keys = 'void', frozenset({'t', 'a0'})
            out[int(a, 16)] = (kind, name, rk, keys)
    return out


def entry_fields(entry, keys):
    """An entry record (bytes, 't=... a0=... f15=... tk=...') reduced to the fields in `keys`, or
    with keys None to every field but tk (the emulated time at entry, which rrbox equalises)."""
    if keys is None:
        return b' '.join(f for f in entry.split() if not f.startswith(b'tk='))
    return b' '.join(f for f in entry.split() if f.split(b'=', 1)[0].decode() in keys)


def run(exe, script, trace, watch, calls, cycles_ref=None, cap=None, ref_trace=None, extra=(), memstick=None):
    """Run rrbox; with `cap` (bytes), stop it once the call log passes that size, and with
    `ref_trace` (retail's per-frame trace lines), stop it at the first frame whose RAM hash
    differs from retail's. Returns True if it was stopped."""
    # Each script has its own stage directory, so scripts run in parallel; retail and candidate
    # of one script still use the same staged path (it is written into emulated RAM).
    stage = os.path.join(a7.OUT, 'stage', os.path.splitext(os.path.basename(script))[0])
    staged = os.path.join(stage, 'BOOT.elf')
    os.makedirs(stage, exist_ok=True)
    shutil.copyfile(exe, staged)
    ms = os.path.join(stage, 'memstick')
    shutil.rmtree(ms, ignore_errors=True)
    if memstick:  # a snapshot's memory stick (tools/oracle/snap.py)
        shutil.copytree(memstick, ms)
    else:
        os.makedirs(ms)
    env = dict(os.environ, RRBOX_EPOCH=a7.EPOCH, TZ='UTC', RRBOX_MEMSTICK=ms)
    cmd = [a7.BOX, staged, '-m', a7.ISO, '-i', '--graphics=software', f'--rr-frames={a7.frames_of(script)}',
           f'--rr-script={script}', f'--rr-trace={trace}', f'--rr-watch={watch}', f'--rr-calls={calls}',
           f'--rr-hash-skip={a7.TEXT_RAM[0]:x}:{a7.TEXT_RAM[1]:x}']
    if cycles_ref:
        cmd.append(f'--rr-cycles-ref={cycles_ref}')
    cmd += list(extra)
    # A trace left by an earlier run would be read by the ref_trace check below before rrbox
    # rewrites it, and stop this run at once (isolate.py's second round got an empty call log).
    for f in (trace, calls):
        if os.path.exists(f):
            os.remove(f)
    p = subprocess.Popen(cmd, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    while p.poll() is None:
        try:
            p.wait(timeout=1)
        except subprocess.TimeoutExpired:
            if cap and os.path.exists(calls) and os.path.getsize(calls) > cap:
                p.kill()
                p.wait()
                return True
            if ref_trace and os.path.exists(trace):
                done = open(trace).read().split('\n')[:-1]  # complete lines only
                if any(x != y for x, y in zip(done, ref_trace)):
                    p.kill()
                    p.wait()
                    return True
    return False


def records(path):
    """{func: [(E fields, R fields), ...]} in call order."""
    out, open_calls = {}, {}
    for line in open(path):
        t = line.split()
        func, call = int(t[1], 16), int(t[2])
        kv = dict(x.split('=', 1) for x in t[3:])
        if t[0] == 'E':
            open_calls[(func, call)] = kv
        else:
            out.setdefault(func, []).append((open_calls.pop((func, call), {}), kv))
    for (func, call), kv in open_calls.items():  # entered, never returned within the run
        out.setdefault(func, []).append((kv, None))
    return out


def summarise(path, keys):
    """One streaming pass over a call log: {func: [calls, base, v0, v1, f0, clobbered]}.

    base digests, call by call in return order (calls never returned last, in entry order), the
    entry record and the call's write hash; v0, v1 and f0 digest those return
    registers separately, so the comparison can pick them by the function's return type. Two
    logs agree on a function exactly when records()/compare() would find every call equal."""
    out, open_calls = {}, {}
    new = lambda: [0, hashlib.blake2b(digest_size=16), hashlib.blake2b(digest_size=16),
                   hashlib.blake2b(digest_size=16), hashlib.blake2b(digest_size=16), 0]
    with open(path, 'rb') as f:
        for line in f:
            if line[0] == 69:  # 'E': remember the entry record until the call returns
                k, _, rest = line.partition(b' ')[2].partition(b' ')
                call, _, entry = rest.partition(b' ')
                open_calls[(k, call)] = entry.rstrip(b'\n')
                continue
            t = line.split()  # R func call v0= v1= f0= writes= hash= clobbered= cyc=
            if len(t) < 9:
                continue  # the last line of a log whose run was stopped at the cap
            entry = entry_fields(open_calls.pop((t[1], t[2]), b''), keys.get(t[1]))
            d = out.get(t[1]) or out.setdefault(t[1], new())
            d[0] += 1
            d[1].update(entry + b'|' + t[7] + b';')  # the write hash, not the count (t[6])
            d[2].update(t[3] + b';')
            d[3].update(t[4] + b';')
            d[4].update(t[5] + b';')
            if t[8] != b'clobbered=000':
                d[5] += 1
    for (k, call), entry in open_calls.items():
        d = out.get(k) or out.setdefault(k, new())
        d[0] += 1
        d[1].update(entry_fields(entry, keys.get(k)) + b'|NORET;')
    return {int(k, 16): [d[0]] + [h.hexdigest() for h in d[1:5]] + [d[5]] for k, d in out.items()}


def script_pair(s, m1, watch, watch_retail):
    """Run one script on retail (or reuse the cached retail run) and on the candidate, and
    summarise both call logs. Runs in its own process, one per script."""
    name = os.path.splitext(os.path.basename(s))[0]
    # the entry fields each function's parameters occupy (a5.watched); a retail summary is cached
    # per set of them, since a changed prototype changes what is compared
    keys = {b'%06x' % a: v[3] for a, v in watched().items()}
    spec = hashlib.sha256(repr(sorted((k, sorted(v) if v else None) for k, v in keys.items())).encode()).hexdigest()[:12]
    files = {side: (os.path.join(a7.OUT, f'{name}.{side}.trace'), os.path.join(a7.OUT, f'{name}.{side}.calls'))
             for side in ('retail', 'candidate')}
    # A retail run depends only on the executable, the script, the watched addresses and rrbox.
    key = hashlib.sha256(b''.join(open(f, 'rb').read() for f in (a7.RETAIL, s, watch_retail, a7.BOX))).hexdigest()[:24]
    cached = os.path.join(CACHE, f'{name}-{key}')
    if not (os.path.exists(cached + '.trace') and os.path.exists(cached + '.calls')):
        # written in place (no second copy in a7/), renamed only once complete
        os.makedirs(CACHE, exist_ok=True)
        tr_, ca_ = cached + '.trace.tmp', cached + '.calls.tmp'
        run(a7.RETAIL, s, tr_, watch_retail, ca_)
        for ext in ('.trace', '.calls'):
            os.replace(cached + ext + '.tmp', cached + ext)
        for junk in (ca_ + '.cov',):
            if os.path.exists(junk):
                os.remove(junk)
        evict(name, key)
    summ = f'{cached}.{spec}.sum'
    if not os.path.exists(summ):
        for old in glob.glob(cached + '.*.sum') + glob.glob(cached + '.sum'):
            os.remove(old)
        open(summ + '.tmp', 'w').write(repr(summarise(cached + '.calls', keys)))
        os.replace(summ + '.tmp', summ)
    # the candidate run reads retail's call log for the time lockstep; the cached copy serves
    # A candidate that diverges can log far more calls than retail (35 GB against 0.7 GB on
    # boot_attract) and fill the disk; past twice retail's log it has long since differed, so the
    # run is stopped there and the script reported as capped.
    cap = max(2 * os.path.getsize(cached + '.calls'), 2**30)
    # Once a frame's RAM differs from retail's, every later call runs on different state and its
    # verdict means nothing, so the candidate is stopped there (a diverging race run otherwise logs
    # to the cap, 21 GB, and takes most of the gate's time).
    tr = open(cached + '.trace').read().split('\n')
    capped = run(m1, s, files['candidate'][0], watch, files['candidate'][1], cached + '.calls', cap, tr)
    tc = open(files['candidate'][0]).read().split('\n')
    first = next((k for k, (x, y) in enumerate(zip(tr, tc)) if x != y), None)
    if first is None and len(tr) != len(tc):
        first = min(len(tr), len(tc))
    covf = files['candidate'][1] + '.cov'
    cov = [line.split() for line in open(covf)] if os.path.exists(covf) and not capped else []
    files['retail'] = (cached + '.trace', cached + '.calls')
    if capped and first is None:
        first = len(tc) - 1
    return name, first, len(tr) - 1, eval(open(summ).read()), summarise(files['candidate'][1], keys), cov, files, capped


def evict(name, key):
    """Remove the retail cache entries of script `name` other than `key`, and any entry in the old
    unprefixed layout (no run can hit those again)."""
    for p in glob.glob(os.path.join(CACHE, '*')):
        base = os.path.basename(p).split('.', 1)[0]
        old_layout = re.fullmatch(r'[0-9a-f]{24}', base)
        if old_layout or (base.startswith(name + '-') and base != f'{name}-{key}'
                          and re.fullmatch(r'[0-9a-f]{24}', base[len(name) + 1:])):
            try:
                os.remove(p)
            except FileNotFoundError:
                pass  # scripts run in parallel; another one removed it first


LEDGER = os.path.join(ROOT, 'config/us/t3_live.csv')
LEDGER_FIELDS = ('addr', 'name', 'kind', 'verdict', 'calls', 'coverage', 'source', 'source_sha', 'date', 'evidence')


def read_ledger():
    """{addr: row} of config/us/t3_live.csv; rows written before the evidence column have none."""
    if not os.path.exists(LEDGER):
        return {}
    return {r['addr']: {k: (r.get(k) or '') for k in LEDGER_FIELDS} for r in csv.DictReader(open(LEDGER))}


def write_ledger(rows):
    """Write {addr: row} sorted by address. evidence: 'a5' (a replay from power-on of every
    script with every placed draft) or 'snap:SCRIPT@FROM-TO' (tools/oracle/snap.py: retail with
    only this function's code replaced, from a snapshot)."""
    tmp = LEDGER + '.tmp'
    with open(tmp, 'w') as f:
        f.write(','.join(LEDGER_FIELDS) + '\n')
        for a in sorted(rows, key=lambda x: int(x, 16)):
            f.write(','.join(str(rows[a][k]) for k in LEDGER_FIELDS) + '\n')
    os.replace(tmp, LEDGER)


def source_of(a, name):
    return next(p for p in glob.glob(os.path.join(ROOT, 'src/**/*.c*'), recursive=True)
                if f'0x{a:06x} us {name}' in open(p).read())


def compare(rk, ret_r, ret_c):
    if ret_r is None or ret_c is None:
        return None if ret_r == ret_c else 'one side never returned'
    keys = ['hash'] + {'void': [], 'int': ['v0'], 'wide': ['v0', 'v1'], 'float': ['f0']}[rk]
    for k in keys:
        if ret_r.get(k) != ret_c.get(k):
            return f'{k} {ret_r.get(k)} vs {ret_c.get(k)}'
    if ret_c.get('clobbered', '000') != '000':
        return f'callee-saved registers clobbered ({ret_c["clobbered"]})'
    return None


DETAIL = False


def main():
    w = watched()
    global DETAIL
    DETAIL = '--detail' in sys.argv
    keep = '--keep' in sys.argv
    scripts = [os.path.abspath(s) for s in sys.argv[1:] if not s.startswith('--')] or sorted(glob.glob(os.path.join(ROOT, 'tools/oracle/scripts/*.txt')))
    os.makedirs(a7.OUT, exist_ok=True)
    free = shutil.disk_usage(a7.OUT).free / 2**30
    if free < MIN_FREE_GB:
        raise SystemExit(f'a5: only {free:.0f} GB free on the build volume, {MIN_FREE_GB} GB needed; not running')
    m1 = os.path.join(ROOT, 'build/image/BOOT.M1.BIN')
    if not os.path.exists(m1):
        raise SystemExit('build the M1 image first: python3 tools/oracle/m1image.py')
    os.makedirs(a7.OUT, exist_ok=True)
    watch = os.path.join(a7.OUT, 'watch.txt')
    sizes = {int(r['addr'], 16): int(r['size']) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))}
    placed = os.path.join(ROOT, 'build/image/m1_placed.txt')
    for line in open(placed) if os.path.exists(placed) else []:
        a, z = line.split()
        sizes[int(a, 16)] = int(z)  # a placed draft: its compiled body, not the padded slot
    open(watch, 'w').write(''.join(f'{a:x} {sizes[a]}\n' for a in sorted(w)))
    # Retail's watch list uses the map's sizes (placed draft sizes only matter for the candidate's
    # coverage), so a retail run stays cacheable while drafts change.
    mapsz = {int(r['addr'], 16): int(r['size']) for r in csv.DictReader(open(os.path.join(ROOT, 'config/us/funcs.csv')))}
    watch_retail = os.path.join(a7.OUT, 'watch_retail.txt')
    open(watch_retail, 'w').write(''.join(f'{a:x} {mapsz[a]}\n' for a in sorted(w)))
    missed = {a: None for a in w}  # words never executed in any script (intersection over scripts)
    verdict = {a: ['UNCOVERED', 0, ''] for a in w}
    a7_bad = 0
    from concurrent.futures import ProcessPoolExecutor
    with ProcessPoolExecutor(len(scripts) or 1) as ex:
        results = list(ex.map(script_pair, scripts, [m1] * len(scripts), [watch] * len(scripts),
                              [watch_retail] * len(scripts)))
    for name, first, nframes, sr, sc, cov, files, capped in results:
        if first is not None:
            a7_bad += 1
            print(f'A7 DIFFERS  {name}: first at frame {first}'
                  + (' (candidate stopped there)' if capped else ''))
        else:
            print(f'A7 IDENTICAL {name}: {nframes} frames')
        for t in cov:
            a, miss = int(t[0], 16), {int(x, 16) for x in t[3:]}
            missed[a] = miss if missed[a] is None else missed[a] & miss
        for a in w:
            v = verdict[a]
            if v[0] == 'DIFFERS':
                continue
            r, c = sr.get(a), sc.get(a)
            nr, nc = (r[0] if r else 0), (c[0] if c else 0)
            if nr != nc:
                v[0], v[2] = 'DIFFERS', f'{name}: {nr} calls in retail, {nc} in candidate'
                continue
            if not nr:
                continue
            rk = w[a][2]
            fields = {'void': [1], 'int': [1, 2], 'wide': [1, 2, 3], 'float': [1, 4]}[rk]
            bad = [('entry/writes', 'v0', 'v1', 'f0')[x - 1] for x in fields if r[x] != c[x]]
            if bad:
                v[0], v[2] = 'DIFFERS', f'{name}: calls differ in {", ".join(bad)} (rerun with --detail for the call)'
            elif c[5]:
                v[0], v[2] = 'DIFFERS', f'{name}: callee-saved registers clobbered in {c[5]} calls'
            else:
                v[0] = 'PASS'
                v[1] += nr
            if v[0] == 'DIFFERS' and DETAIL:
                cr, cc = records(files['retail'][1]).get(a, []), records(files['candidate'][1]).get(a, [])
                for n, ((er, xr), (ec, xc)) in enumerate(zip(cr, cc)):
                    ks = w[a][3]
                    same = all(er.get(k) == ec.get(k) for k in (ks or set(er) | set(ec)) if k != 'tk')
                    why = 'entry differs' if not same else compare(rk, xr, xc)
                    if why:
                        v[2] = f'{name} call {n}: {why}'
                        break
    old = read_ledger()
    rows = {}
    for a in sorted(w):
        kind, name, rk = w[a][:3]
        v = verdict[a]
        words = sizes[a] // 4
        miss = sorted(missed[a] or [])
        cov = f'{words - len(miss)}/{words}'
        detail = f'{v[1]} calls, coverage {cov}' if v[0] == 'PASS' else v[2]
        if v[0] == 'PASS' and miss:
            detail += ' (never ran: ' + ' '.join(f'{x:x}' for x in miss[:8]) + (' ...' if len(miss) > 8 else '') + ')'
        print(f'{v[0]:9s} 0x{a:06x} {name:24s} {kind:10s} {detail}')
        src = source_of(a, name)
        sha = hashlib.sha256(open(src, 'rb').read()).hexdigest()[:16]
        prev = old.get(f'0x{a:06x}')
        if prev and prev.get('evidence', '').startswith('snap:') and prev['source_sha'] == sha:
            # a snapshot test of this source (tools/oracle/snap.py) replaced only this function's
            # code; a replay from power-on also runs every other draft, so its row stands
            rows[prev['addr']] = prev
            continue
        rows[f'0x{a:06x}'] = dict(zip(LEDGER_FIELDS, (f'0x{a:06x}', name, kind, v[0], v[1], cov, os.path.relpath(src, ROOT),
                                                      sha, datetime.date.today().isoformat(), 'a5')))
    write_ledger(rows)
    n = {k: sum(1 for v in verdict.values() if v[0] == k) for k in ('PASS', 'DIFFERS', 'UNCOVERED')}
    for name, *_, files, capped in results:
        cand = files['candidate']
        link = os.path.join(a7.OUT, f'{name}.retail.calls')
        if os.path.lexists(link):
            os.remove(link)
        if keep:
            os.symlink(files['retail'][1], link)
        else:
            for p in (cand[0], cand[1], cand[1] + '.cov'):
                if os.path.exists(p):
                    os.remove(p)
    print(f"a5: {n['PASS']} pass, {n['DIFFERS']} differ, {n['UNCOVERED']} uncovered; A7 {len(scripts) - a7_bad}/{len(scripts)} identical")
    return 1 if (n['DIFFERS'] or a7_bad) else 0


if __name__ == '__main__':
    sys.exit(main())
