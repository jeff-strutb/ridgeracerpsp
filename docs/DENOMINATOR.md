# Denominator

`tools/denominator.py` prints how much of the USA `BOOT.BIN` is game code, and how
much of that the `@implements` / `@draft` tags under `src/` cover. Every number
comes from the tools below; this page explains them and does not replace them.

```sh
./setup.sh                              # extract and verify the references
python3 tools/denominator.py            # the table
```

## Pipeline

| Step | Tool | Output |
|---|---|---|
| Reference gate | `tools/refcheck.py` | refuses a wrong MD5; every tool reads the binary through it |
| ELF/PRX + relocations | `tools/analysis/prx.py` | sections, SCE relocations with targets |
| Instruction decoder | `tools/analysis/allegrex.py` | decoding from the opcode table inside the toolchain's own `psp-objdump` |
| Function map | `tools/analysis/funcmap.py` | `config/us/funcs.csv` |
| Fence and objects | `tools/analysis/libfence.py` | `config/us/libfuncs.csv`, `tus.csv`, `fence.csv` |
| LO16 recovery | `tools/analysis/hilo.py` | LO16 targets that relocations alone leave open |
| Listing | `tools/rrdis.py 0xADDR` | annotated retail listing |

Every tool has a `--selftest` that plants a fault and must catch it.
`funcmap.py --check` and `libfence.py --check` rebuild their CSVs and compare them
with the committed CSVs.

## Functions (`funcs.csv`)

A start is known by at least one kind of evidence, listed in the `evidence` column:

- `fde`: the `pc_begin` of a live `.eh_frame` FDE. Its size comes from `pc_range`
  and is exact.
- `after-fde`: the word after an FDE range. There is never padding between FDE
  ranges.
- `jal` (a relocated call), `hilo` (a relocated address taken), `data:SEC` (a
  relocated pointer in a data section). Words that belong to jump tables are
  excluded: 111 tables are found by their code shape and bounded by their
  `sltiu`.
- `entry` (`module_start`), `stub` (import stubs, counted from `.lib.stub`), and
  `section`.
- `libsym`: a symbol of a library object whose code fingerprints at exactly one
  address, where that address is already a start.
- `reach`: the first non-zero word after the reachable code of a non-FDE
  function. Calibration: in all 3,965 FDE functions, every word is reachable from
  the entry or a landing pad. So code that a function cannot reach is not part of
  that function.

The `end` column records how each function's end is known: `fde`, `stub`, `reach`
(after the last reachable word), `next-start` or `section-end`. Checks: every
`jr ra` lies inside a function, no word is unreachable from its function's start,
and no `jal` lands inside an FDE body.

## Classes (`fence.csv`)

**library**: any one of:
- `fingerprint`: the function lies wholly inside a code section of a reference
  library object from psp-gcc 1.3.1 or 1.7.1 (`crt0/crtbegin/crtend`, `libgcc`,
  `libc`, `libm`, `libstdc++`, `libsupc++`). The match is exact after masking
  relocated fields, uses the same relocation types, and occurs at exactly one
  address, which must be a function start.
- `crt`: `.init`/`.fini`, proven to be the concatenation of `crti`, `crtbegin`,
  `crtend` and `crtn`.
- `stub`: an SCE import stub.

**game**: any one of:
- `rtti`: a virtual method of a class whose RTTI name no reference library
  defines.
- `vtref`: code that addresses such a class's vtable (constructors and
  destructors).
- `object`: a non-library function in the same object as an `rtti` or `vtref`
  function.

**unknown**: everything else. Unknown code is outside both the numerator and the
denominator. A library `.text` fingerprint inside a game object is a conflict and
is classed unknown. One such case exists: `gmtime_r` at 0x59188.

"Same object" means the same CIE group. `libfence.py` tests that each CIE is one
linked object:
- identical CIEs repeat 182 and 76 times, so the linker merged none;
- group ranges are disjoint and in order;
- no group holds two `.ctors` or two `.dtors` functions;
- LSDAs follow the group order;
- the 262 groups do not outnumber the 493 `.comment` idents.

An object's extent is taken from its first FDE to its last FDE. Code between
groups goes in `gap` rows in `tus.csv`, with its owner unknown.

## Tags

Tags have the form `@implements 0xADDR us NAME` and `@draft 0xADDR us NAME`. The
tool counts game functions as tagged implements, tagged draft, or untagged, with
their bytes. It also reports:
- tags on library or unknown functions;
- tags whose address is not a function start;
- addresses tagged more than once;
- tags for other regions;
- malformed tags.

A tag is a claim. The tool counts it but does not check it; certification belongs
to the grader.

## Not settled by analysis

- **Unknown code before the library tail.** The first library `.text`
  fingerprint is libm `s_atan` at 0x11b514; no library fingerprint lies below it.
  If every object before that address was a command-line object (the game's own),
  the unknown code there would be game. That holds only if no unidentified archive
  (for example a Sony SDK library) was linked earlier. Nothing in the binary
  proves that, so this code stays unknown. `libfence.py` prints the counts on each
  side of that address.
- **Library members not identified.** Some members in the library tail do not
  fingerprint, because the game shipped psp-1.5.1 libraries and the references
  are 1.3.1 and 1.7.1. Other members are SDK libraries that have no reference
  here.
- **Namespaces.** Some classes counted as game sit in namespaces that may be
  middleware rather than Ridge Racer code (`swg`, `stx`, `An`, `Ng`). "Game" here
  means "not a toolchain library".
- **LO16 targets.** Of the 2,908 LO16 relocations not paired with a HI16,
  `hilo.py` recovers 2,674 by data flow. The rest have only their low half.
- **Possible missed function starts.** Four non-FDE functions contain a `j` to
  code right after a terminator, which could mark a function reached only by a
  tail jump. These are left whole.
