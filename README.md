# Ridge Racer (PSP): decompilation

**Started October 12, 2026.** The retail executable is mapped and its compiler is identified. A per-function grader compiles C with that compiler and compares it to the original bytes. On a random control set of 61 retail functions, 49 already compile to identical bytes.

No game function has been filed into the tree yet, so both milestones stand at zero (see [Current Status](#current-status)).

**Maintainer:** Jeffrey Wilbur, Strut B, LLC\
**Contact:** [retro@strutb.com](mailto:retro@strutb.com)

## Project Purpose

This is a decompilation of **Ridge Racer** (PSP, 2004/2005), held to the MAME standard:

- Every function is rewritten as readable C++ or C.
- Every function is documented with what it does.
- Every function is filed into the source file it came from.
- Every function is proven against the original.

There are two proofs. The source must compile under the original compiler to **byte-identical output**, and code that is not yet byte-exact must be **certified to behave exactly like the original**.

Progress is measured only by those two proofs. Playability is a consequence, never a reason to reorder the work.

## Game background

Namco shipped *Ridge Racer* as a PSP launch title: *Ridge Racers* in Japan in December 2004, then North America and Europe in 2005. All three regions run one program, `PSP_GAME/SYSDIR/BOOT.BIN`, which is an unencrypted ELF.

The binary keeps a great deal of its build:

- **The compiler.** The program is a relocatable PSP module that carries its **full relocation tables** (78,287 entries). Every reference from code to code or data is known exactly.
- **The build's object files.** A `.comment` ident survives for each of the **493 object files** in link order. They name the compiler: SCE's `GCC 3.3.3+allegrex-2.2.1-psp-1.5.1`.
- **The code.** The game is C++ with RTTI and exceptions. It has 3,977 exception-frame records that give exact function extents, and 154 surviving class names such as `Fj::C2DAnalogMeter`, `Car::CCarBufferPSP` and `RRBios::TextureManager`.
- **The libraries.** Sony's system libraries, newlib and GCC's runtime are linked in statically.

The USA and Europe executables differ by 5 bytes. The Japanese release is a separate, earlier build.

## The compiler

The exact SCE 1.5.1 toolchain is not public. The two neighbouring SCE builds that are public, psp-gcc 1.3.1 and 1.7.1 from decomp.me's compiler archive, produce identical instructions on every function tested.

Retail differs from both of them in exactly one way that has been found: it contains **no conditional moves** (`movz`/`movn`, integer or float) anywhere in its 375,000 instructions, while both public compilers emit them.

`tools/toolchains/mk_nocmov.py` rebuilds 1.3.1 with conditional moves switched off:

- Four optab stores become NOPs.
- Thirteen instruction-recogniser returns become "no match".
- Every patch site is located by disassembly and its original bytes are checked first.

That reconstruction, **psp-gcc-1.3.1-nocmov**, is the matching compiler. Selects that previously could not match now do so from their natural source, and nothing that matched before regressed.

The default flags are `-O2 -G0`. Some translation units were built with other flags, which a source file declares with `/* @cflags: … */`.

## Current Status

There are two milestones:

- **M1** counts functions whose code is certified to behave exactly like the original (T3), plus byte-exact ones (T4).
- **M2** counts byte-exact functions only.

| | Count |
|---|---|
| Functions mapped in `.text` | 7,440, covering 1,484,192 of 1,500,092 bytes. This includes library code not yet separated out. |
| Functions filed in `src/` | 0 |
| M1 (T3 + T4) | 0% |
| M2 (T4) | 0% |
| Compiler control set (`src/control/`) | 49 / 61 byte-exact |

The control set is 61 retail functions chosen at random and transcribed by hand. Its purpose is to identify the compiler and its flags, not to count toward the milestones; its sources are not filed into real translation units. The game-versus-library denominator is fixed in Phase 0 ([docs/PLAN.md](docs/PLAN.md)).

Query the tree. Do not trust a number in this file.

```bash
./setup.sh                                          # extract and MD5-check BOOT.BIN/EBOOT.BIN for US, EU, JP
python3 tools/analysis/funcmap.py                   # rebuild the function map -> config/us/funcs.csv
python3 tools/rrdis.py 0xADDR                       # annotated retail listing of one function
python3 tools/score.py src/control/batch1.c         # compile and grade every @implements in a file
python3 tools/score.py FILE --cc 1.3.1 -v           # same, stock compiler, word-by-word
```

T1 = a draft only; T2 = in the tree, not done; T3 = certified behaviour exact, not byte-exact; T4 = bytes diff clean, with every relocation resolving to the same target.

### How T3 will be verified

This is **not built yet** (Phase 1 of the plan). It will follow the Boss Rally and Top Gear Rally oracles.

The original program will run headless and deterministic on a pinned PPSSPP core, driven by input scripts covering every mode and course. Unicorn has no Allegrex or VFPU support, which is why PPSSPP is used.

- **A5, per function.** At every real call, the original body and the candidate run from identical state. Their memory, registers, FPU and VFPU state, and return values must agree. An unreached function is UNCOVERED, never passed.
- **A7, whole image.** The relinked program, with every certified body in place, runs every script in lockstep with the original. Every GE display list, every audio buffer and all of RAM must agree on every frame.

A7 exists because A5 alone was not enough on Boss Rally, where whole-image runs found some 25 real bugs that A5 had certified. Both gates must catch a planted bug before any T3 counts.

### How T4 is verified

`tools/score.py` compiles a file in the toolchain VM and compares every tagged function word for word with the retail bytes:

- Relocated fields are masked on both sides.
- The relocation type must agree at every word.
- Call targets must agree wherever the callee is known.

The whole-image gate (the rebuilt `BOOT.BIN` equal to retail, relocation tables included) is a Phase 0 deliverable.

### Architecture

    src/control/            compiler-identification control set (not real TUs)
    src/                    the decomp, filed by the original's translation units (from Phase 2)
    config/us/              function map and, later, ledgers
    tools/analysis/         ELF/PRX reader (SCE relocations) and the function mapper
    tools/rrdis.py          annotated listings
    tools/score.py          per-function grader
    tools/toolchains/       pinned compilers, Lima VM config, the nocmov builder
    docs/PLAN.md            the plan and the standard
    docs/decomp/            GCC33-HANDBOOK.md: what the work has learned, one rule per finding
    references/             the retail ISOs (you supply; not tracked)
    orig/                   executables extracted by setup.sh (not tracked)
    build/                  everything generated (not tracked)

### Building & Setup

Everything is staged inside the repo, and nothing is installed on the host.

- **`./setup.sh`** extracts `BOOT.BIN` and `EBOOT.BIN` for each region from your ISOs into `orig/` and checks their MD5s.
- **The compilers** are i386 Linux binaries.
  - They run in a small Debian VM managed by a pinned Lima (`tools/toolchains/lima.sh`), with only this repo shared into it.
  - Tarballs are pinned by SHA-256 in `tools/toolchains/SHA256SUMS`, and the steps are in [tools/toolchains/README.md](tools/toolchains/README.md).
  - `python3 tools/toolchains/mk_nocmov.py` builds the matching compiler.
- **Ghidra 12.1.3** with **ghidra-allegrex v21.4** loads `BOOT.BIN` as a PSP executable with its relocations. It is used for drafts.

### Reference ISOs (you supply; not tracked in git)

```
references/Ridge Racer (USA) (En,Fr,De,Es,It).iso                 the target
    MD5  ef89c58442f1c17ca3d060f0077d67b0     906,362,880 bytes   ULUS-10001
    BOOT.BIN MD5  e87ea7c17004cd13945664152608140c
references/Ridge Racer (Europe, Australia) (En,Fr,De,Es,It).iso    variant (5-byte delta)
    MD5  72fff94c5b048e63047e8eae0e2771ec     906,362,880 bytes   UCES-00002
    BOOT.BIN MD5  4eaa1ff90e56f5ff1521e4e59597e9f2
references/Ridge Racers (Japan).iso                                witness (earlier build)
    MD5  739ba19e712185bbbf1cd6ce4bbd859b     906,297,344 bytes   ULJS-00001
    BOOT.BIN MD5  524c500adbe299a546e03ad40ada5a56
```

`setup.sh` checks the `BOOT.BIN` MD5s and refuses any other image.

## More

- [docs/PLAN.md](docs/PLAN.md): the plan, the tiers and milestones, and the lessons carried over from Boss Rally / Top Gear Rally.
- [docs/decomp/GCC33-HANDBOOK.md](docs/decomp/GCC33-HANDBOOK.md): proven machine-code → source rules for this compiler, and the open residue.
- [tools/toolchains/README.md](tools/toolchains/README.md): the toolchain, the VM and the reconstructed compiler.
