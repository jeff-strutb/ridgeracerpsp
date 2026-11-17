#!/usr/bin/env python3
"""Library symbols that config/us/libfuncs.csv does not identify, proven from two sides.

    libsyms.py              grade the tree, write config/us/libsyms.csv, list refused rows
    libsyms.py --check      rebuild and compare with the committed CSV
    libsyms.py --selftest   plant a call site of free that points at malloc and show free is
                            refused

The owner's rule: an unidentified library symbol's address is proven when BOTH
  (1) every reference to it, in functions that are otherwise EXACT, agrees on one retail
      address (sites; disagreeing must be 0), and
  (2) what retail has at that address closely matches the reference library's copy of the
      symbol (the psp-gcc 1.3.1 and 1.7.1 archives: crt*, libgcc, libc, libm, libstdc++,
      libsupc++).

Side (1) is collected by tools/score.py in collection mode: every @implements of every real
file is graded with references to reference-library symbols recorded instead of failed; a
function contributes only if everything else in it passes (verdict PENDING, never EXACT).
The address a site gives is retail's target minus the reference's addend.  libsyms.csv is
not used while collecting.

Side (2), "closely matches", for code (the retail function at the address, size from
funcs.csv, against each reference copy of the symbol; relocated fields masked, relocation
types compared):
  exact  every word and relocation type equal to a reference copy;
  cmov   equal outside one window, and inside it the words differ by exactly the
         conditional-move idiom that the retail compiler never emits (retail .text has no
         movz/movn): the reference's `li T,K` + `movz D,T,C` (or movn) is retail's
         `bnez C` (or beqz) + `li D,K`, where the branch skips exactly that li and the li is
         not in its delay slot; the remaining words of the window are the same multiset
         (moved by the delay-slot filler); and T is not read again before it is written or a
         call clobbers it.
  Refused: any other difference, a size difference, an address that is not a function
  start, and a retail function that is an exact copy of a DIFFERENT reference symbol and not
  of this one (for example 0x164c48, which call sites name __gedf2, is the reference
  __ltdf2 word for word; the two differ only in the value returned for NaN).
For data (the libsupc++ typeinfo vtables that a class typeinfo points at): the retail bytes at
the address, for the reference symbol's size, have relocations of the same type at the same
offsets and equal bytes elsewhere, and each relocated word's retail target closely matches
the reference's target symbol by these same rules (code by the code rule, data recursively).

Rows: symbol, kind (code/data), address, sites, disagreeing, match, reference, accepted,
reason.  tools/score.py resolves only rows with accepted = yes (rule 'libsyms').
"""
import csv
import io
import sys
import tarfile
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE)]
import libarchive as la      # noqa: E402
from allegrex import decode  # noqa: E402

ROOT = HERE.parent.parent
CSV = ROOT / 'config' / 'us' / 'libsyms.csv'
FIELDS = ['symbol', 'kind', 'address', 'sites', 'disagreeing', 'match', 'reference', 'accepted',
          'reason']
CALL_CLOBBERS = True


def masked(w, ty):
    return (w & la.MASK[ty], ty) if ty else (w, 0)


class Refs:
    """Every defined symbol of every reference library member, both tarballs."""

    def __init__(self):
        import score
        self.defs = {}            # name -> [(tarball, label, Obj, Sym)]
        for tb in la.TARBALLS:
            raw = (la.REFS / ('%s.tar.gz' % tb)).read_bytes()
            import hashlib
            if hashlib.md5(raw).hexdigest() != la.TARBALLS[tb]:
                raise SystemExit('libsyms: %s: MD5 mismatch' % tb)
            with tarfile.open(fileobj=io.BytesIO(raw), mode='r:gz') as tf:
                for m in sorted(tf.getmembers(), key=lambda m: m.name):
                    base = m.name.rsplit('/', 1)[-1]
                    if not m.isfile() or base not in la.WANT:
                        continue
                    data = tf.extractfile(m).read()
                    mems = list(la.ar_members(data)) if base.endswith('.a') else [('', data)]
                    for mn, md in mems:
                        if md[:4] != b'\x7fELF':
                            continue
                        o = score.Obj(md)
                        label = '%s(%s)' % (base, mn) if mn else base
                        for s in o.syms:
                            if s.name and o.defined(s) and s.type != score.STT_SECTION:
                                self.defs.setdefault(s.name, []).append((tb, label, o, s))
        self._sig = None

    def code_copies(self, name):
        out = []
        for tb, label, o, s in self.defs.get(name, []):
            if o.is_code(s.shndx) and s.size:
                out.append((tb, label, self.keys(o, s)))
        return out

    @staticmethod
    def keys(o, s):
        ks = []
        for k in range(s.size // 4):
            off = s.value + 4 * k
            rl = o.relat.get((s.shndx, off), [])
            ks.append(masked(o.word(s.shndx, off), rl[0].type if rl else 0))
        return ks

    def exact_names(self, keys):
        """Reference symbols with a code copy equal to keys."""
        if self._sig is None:
            self._sig = {}
            for name, ds in self.defs.items():
                for tb, label, o, s in ds:
                    if o.is_code(s.shndx) and s.size:
                        self._sig.setdefault(tuple(self.keys(o, s)), set()).add(name)
        return self._sig.get(tuple(keys), set())


def retail_keys(p, a, n):
    out = []
    for k in range(n):
        rl = p.reloc_at(a + 4 * k)
        out.append(masked(p.word(a + 4 * k), rl[0].type_id if rl else 0))
    return out


def cmov_window(R, C, base):
    """None if R (retail) and C (reference) differ only by the conditional-move idiom (see the
    module docstring); else a description of the difference."""
    if len(R) != len(C):
        return 'size retail %d words, reference %d' % (len(R), len(C))
    n = len(R)
    i = 0
    while i < n and R[i] == C[i]:
        i += 1
    e = n
    while e > i and R[e - 1] == C[e - 1]:
        e -= 1
    if i == n:
        return None
    rw, cw = R[i:e], C[i:e]
    ronly = list((Counter(rw) - Counter(cw)).elements())
    conly = list((Counter(cw) - Counter(rw)).elements())
    if len(ronly) != 2 or len(conly) != 2:
        return 'window words %d-%d: %d retail-only, %d reference-only words' % (
            i, e, len(ronly), len(conly))
    ci = [decode(w) for w, _ in conly]
    ri = [decode(w) for w, _ in ronly]
    cm = [x for x in ci if x.name in ('movz', 'movn')]
    cl = [x for x in ci if x.name == 'li']
    rb = [x for x in ri if x.name in ('bnez', 'beqz')]
    rl = [x for x in ri if x.name == 'li']
    if not (len(cm) == len(cl) == len(rb) == len(rl) == 1):
        return 'window words %d-%d: not the conditional-move idiom (%s / %s)' % (
            i, e, ', '.join(x.text() for x in ri), ', '.join(x.text() for x in ci))
    mv, li_c, br, li_r = cm[0], cl[0], rb[0], rl[0]
    D, T, Cr = mv.rd, mv.rs, mv.rt
    want_br = 'bnez' if mv.name == 'movz' else 'beqz'
    if not (li_c.rt == T and li_r.rt == D and li_c.imm == li_r.imm and br.name == want_br
            and br.rs == Cr):
        return 'window words %d-%d: registers or constant differ from the idiom' % (i, e)
    kb = next(k for k in range(i, e) if R[k] == ronly[[decode(w).name for w, _ in ronly]
                                                     .index(br.name)])
    kl = next(k for k in range(i, e) if R[k] == ronly[[decode(w).name for w, _ in ronly]
                                                     .index('li')])
    tgt = kb + 1 + decode(R[kb][0]).imm
    if not (kl > kb + 1 and tgt == kl + 1):
        return 'window words %d-%d: the branch does not skip exactly the li' % (i, e)
    km = next(k for k in range(i, e) if C[k] == conly[[decode(w).name for w, _ in conly]
                                                      .index(mv.name)])
    for k in range(km + 1, n):
        x = decode(C[k][0])
        if T in x.reads:
            return 'reference reads %s after the movz (word %d)' % (T, k)
        if T in x.writes or (CALL_CLOBBERS and x.is_call):
            break
    return None


def short(why):
    """One reason for several reference copies: the first, noting whether the others agree."""
    first = why[0]
    body = first.split(': ', 1)[-1]
    same = all(w.split(': ', 1)[-1] == body for w in why[1:])
    return (body if same else first + ' (other copies differ otherwise)')[:300]


class Prover:
    def __init__(self, p, funcs, refs):
        self.p, self.funcs, self.refs = p, funcs, refs
        self.memo = {}

    def code(self, a, name):
        """(match, reference, reason): match is 'exact', 'cmov' or None."""
        f = self.funcs.get(a)
        if f is None:
            return None, '', '%#08x is not a function start' % a
        R = retail_keys(self.p, a, f['size'] // 4)
        copies = self.refs.code_copies(name)
        if not copies:
            return None, '', 'no reference code copy of %s' % name
        for tb, label, C in copies:
            if C == R:
                return 'exact', '%s %s' % (tb, label), ''
        others = self.refs.exact_names(R) - {name}
        if others:
            return None, '', 'retail %#08x is an exact copy of %s, not of %s' % (
                a, ', '.join(sorted(others)), name)
        why = []
        for tb, label, C in copies:
            w = cmov_window(R, C, a)
            if w is None:
                return 'cmov', '%s %s' % (tb, label), ''
            why.append('%s: %s' % (tb, w))
        return None, '', short(why)

    def data(self, a, name, depth=0):
        key = (a, name)
        if key in self.memo:
            return self.memo[key]
        self.memo[key] = ('exact', 'in progress', '')
        res = self._data(a, name, depth)
        self.memo[key] = res
        return res

    def _data(self, a, name, depth):
        import score
        p = self.p
        why = []
        for tb, label, o, s in self.refs.defs.get(name, []):
            if o.is_code(s.shndx) or not s.size:
                continue
            n = s.size
            sec = p.section_at(a)
            if sec is None or a + n > sec.end or sec.type == score.SHT_NOBITS:
                why.append('%s: retail %#08x has no %d bytes of contents' % (tb, a, n))
                continue
            ob = bytearray(o.bytes_of(s.shndx, s.value, n))
            rb = bytearray(p.read(a, n))
            orl = {r.off - s.value: r for r in o.rels.get(s.shndx, [])
                   if s.value <= r.off < s.value + n}
            rrl = {r.addr - a: r for r in p.relocs_in(a, a + n)}
            if {k: r.type for k, r in orl.items()} != {k: r.type_id for k, r in rrl.items()}:
                why.append('%s: relocations differ' % tb)
                continue
            for k, r in orl.items():
                m = score.FIELD[r.type]
                for buf in (ob, rb):
                    w = int.from_bytes(buf[k:k + 4], 'little') & ~m & 0xffffffff
                    buf[k:k + 4] = w.to_bytes(4, 'little')
            if ob != rb:
                why.append('%s: bytes differ' % tb)
                continue
            bad = None
            for k in sorted(orl):
                r, rr = orl[k], rrl[k]
                t = rr.target
                tname = r.sym.name
                if not tname:
                    # A section symbol: compare the bytes it points at, up to the next NUL
                    # (string names) -- the only local data typeinfo refers to.
                    off = r.sym.value + r.addend
                    d = o.bytes_of(r.sym.shndx, 0, o.secs[r.sym.shndx].size)
                    e = d.index(b'\0', off) + 1 if b'\0' in d[off:] else len(d)
                    if p.read(t, e - off) != d[off:e]:
                        bad = 'word +%d: local data differs' % k
                        break
                    continue
                isdata = any(not oo.is_code(ss.shndx) for _, _, oo, ss in
                             self.refs.defs.get(tname, []))
                if isdata:
                    mt, _, w = self.data(t - r.addend, tname, depth + 1)
                else:
                    mt, _, w = self.code(t - r.addend, tname)
                if mt is None:
                    bad = 'word +%d -> %s: %s' % (k, tname[:60], w)
                    break
            if bad:
                why.append('%s: %s' % (tb, bad))
                continue
            return 'exact', '%s %s' % (tb, label), ''
        return None, '', short(why) if why else 'no reference data copy of %s' % name


def observe(replace=None):
    """{symbol: [(address, function address)]} from the tree in collection mode."""
    import score
    refs_names = Refs_names()
    tree = score.Tree()
    g = score.Grader(tree)
    g.use_libsyms = False
    g.collect = refs_names
    files = [p for p in score.source_files() if score.is_real(p)]
    if replace:
        files = [replace.get(f.resolve(), f) for f in files]
    tree.compile_many(files)
    obs = {}
    for f in files:
        u = tree.unit(f)
        for t in u.tags:
            if t.kind != 'implements' or t.region != 'us':
                continue
            r = g.grade(u, t)
            if r['verdict'] == 'PENDING':
                for name, a, _ in r['pending']:
                    obs.setdefault(name, []).append((a, t.addr))
    return obs


_REFS = None


def refs():
    global _REFS
    if _REFS is None:
        _REFS = Refs()
    return _REFS


def Refs_names():
    return set(refs().defs)


def build(obs):
    import funcmap
    from prx import Prx
    p = Prx.from_ref('us')
    funcs = {f['addr']: f for f in funcmap.load()}
    pr = Prover(p, funcs, refs())
    rows = []
    for name in sorted(obs):
        sites = obs[name]
        c = Counter(a for a, _ in sites)
        addr, n = c.most_common(1)[0]
        dis = len(sites) - n
        isdata = all(not o.is_code(s.shndx) for _, _, o, s in refs().defs[name])
        kind = 'data' if isdata else 'code'
        if dis:
            others = ', '.join('%#08x' % a for a in sorted(c) if a != addr)
            match, ref, reason = None, '', '%d site(s) point elsewhere (%s)' % (dis, others)
        elif isdata:
            match, ref, reason = pr.data(addr, name)
        else:
            match, ref, reason = pr.code(addr, name)
        rows.append({'symbol': name, 'kind': kind, 'address': '0x%06x' % addr,
                     'sites': len(sites), 'disagreeing': dis, 'match': match or '',
                     'reference': ref, 'accepted': 'yes' if match and not dis else 'no',
                     'reason': reason})
    return rows


def write(rows, path=CSV):
    with open(path, 'w', newline='') as fh:
        w = csv.DictWriter(fh, FIELDS, lineterminator='\n')
        w.writeheader()
        for r in rows:
            w.writerow(r)


def load(path=CSV):
    """{symbol: address} of the accepted rows."""
    if not Path(path).is_file():
        return {}
    with open(path) as fh:
        return {r['symbol']: int(r['address'], 16) for r in csv.DictReader(fh)
                if r['accepted'] == 'yes'}


def show(rows):
    for kind in ('code', 'data'):
        print('%s symbols:' % kind)
        for r in rows:
            if r['kind'] == kind:
                print('  %-3s %-44s %s sites %3d disagreeing %d %-5s %s %s' % (
                    r['accepted'], r['symbol'][:44], r['address'], r['sites'], r['disagreeing'],
                    r['match'] or '-', r['reference'], r['reason']))


def selftest():
    """Plant: one call site of free is made to point at malloc's retail address (as a call that
    the source names free but retail makes to malloc would).  free must then be refused with
    one disagreeing site, and every other row must be unchanged."""
    obs = observe()
    base = {r['symbol']: r for r in build(obs)}
    planted = {k: list(v) for k, v in obs.items()}
    m = int(base['malloc']['address'], 16)
    a, f = planted['free'][0]
    planted['free'][0] = (m, f)
    bad = {r['symbol']: r for r in build(planted)}
    others = [k for k in base if k != 'free' and base[k] != bad[k]]
    ok = (base['free']['accepted'] == 'yes' and bad['free']['accepted'] == 'no'
          and bad['free']['disagreeing'] == 1 and not others)
    print('selftest: free accepted before (%s sites at %s); planted: the site in %#08x now '
          'points at %#08x (malloc)' % (base['free']['sites'], base['free']['address'], f, m))
    print('selftest: free after: accepted %s, %s sites, %s disagreeing: %s' % (
        bad['free']['accepted'], bad['free']['sites'], bad['free']['disagreeing'],
        bad['free']['reason']))
    print('selftest: other rows changed: %d' % len(others))
    print('selftest:', 'PASS' if ok else 'FAIL')
    return 0 if ok else 1


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    rows = build(observe())
    if argv[1:] == ['--check']:
        with open(CSV) as fh:
            old = list(csv.DictReader(fh))
        new = [{k: str(v) for k, v in r.items()} for r in rows]
        print('libsyms --check:', 'same' if old == new else 'DIFFERS from the committed CSV')
        return 0 if old == new else 1
    write(rows)
    show(rows)
    print('wrote %s: %d rows, %d accepted' % (CSV.relative_to(ROOT), len(rows),
                                              sum(r['accepted'] == 'yes' for r in rows)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
