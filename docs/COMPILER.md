# Compiler

Reference: the USA BOOT.BIN (MD5 e87ea7c17004cd13945664152608140c). Its `.comment` names
`GCC: (GNU) 3.3.3+allegrex-2.2.1-psp-1.5.1` (493 times). That build is not available; psp-gcc
1.3.1 and 1.7.1 are.

## Pinned

| | |
|---|---|
| Compiler | psp-gcc **1.3.1** (`3.3.3+allegrex-2.2.1-psp-1.3.1`), with Allegrex integer conditional moves turned off (`1.3.1-nocmov`, made by `tools/toolchains/nocmov.py`) |
| Assembler | GNU as `2.14+allegrex-vfpu-2.2.1-psp-1.3.1 20030612` (from the 1.3.1 tarball) |
| Default flags | `-O2` |
| Implied by the 1.3.1 specs | `-G 0 -march=allegrex -mtune=allegrex -mno-ulsw`; gas gets `-EL -O2 -g0 -mabi=eabi` |
| C++ | cc1plus defaults (exceptions and RTTI on) |
| C | no `-fexceptions` |

`cc.py` uses this by default: `python3 tools/toolchains/cc.py FILE` compiles FILE with
`1.3.1-nocmov -O2` plus the file's own `@cflags`.

## Control set results (60 functions, `src/control/CONTROL.md`)

The control set was chosen by a fixed rule from the source text alone, without looking at any
score (`tools/toolchains/pick_control.py`). It covers 5 modules, C and C++, three size classes,
and 20 functions that use `?:`. Scores are from `ctlscore.py --control src/control/CONTROL.md`.

| Compiler | Flags | EXACT |
|---|---|---|
| 1.3.1 stock | `-O2` | 52/60 |
| 1.3.1 stock | `-O2 -fno-if-conversion` | 49/60 |
| **1.3.1-nocmov** | **`-O2`** | **60/60** |
| 1.7.1 stock | `-O2` | 47/60 (7 fail to assemble: `swr`) |
| 1.7.1 stock | `-O2 -mno-ulsw` | 52/60 |
| 1.7.1 stock | `-O2 -mno-ulsw -fno-if-conversion` | 49/60 |
| 1.7.1-nocmov | `-O2 -mno-ulsw` | 60/60 |
| 1.3.1-nocmov | `-O1` | 13/60 |
| 1.3.1-nocmov | `-Os` | 27/60 |
| 1.3.1-nocmov | `-O3` | 12/60 |

`-O2` was the only level put forward as a candidate. `-O1`, `-Os` and `-O3` were run afterwards
only to confirm that no other level also fits. None does.

The control set cannot tell 1.3.1 and 1.7.1 apart, since both no-cmov builds score 60/60. The
whole tree can.

## Whole tree (every tag in src/, 281 files)

| Setup | `@implements` EXACT | DIFFERS | `@draft` EXACT |
|---|---|---|---|
| 1.3.1-nocmov `-O2` | 4755 of 4767 | 12 | 4 of 865 |
| 1.7.1-nocmov `-O2 -mno-ulsw` | 4751 of 4767 | 16 | 4 of 865 |

These counts include 10 functions the first run reported MISSING: a scorer naming bug, now
fixed and rescored, all EXACT under 1.3.1-nocmov. The 12 DIFFERS under 1.3.1 are all in the old
`src/control/batch*.c` files, which are not real translation units. Every `@implements` in a
real TU (4713/4713) is EXACT under the pinned setup.

**1.3.1 over 1.7.1.** Four functions separate the two compilers, and all four go the same way:
EXACT under 1.3.1, DIFFERS under 1.7.1. No function goes the other way.

| Address | Function | File | 1.7.1 first difference |
|---|---|---|---|
| 0x0e8d78 | f_0e8d78 | src/sequence/RallyXCar.cpp | word 6: retail `bltzl v0` (04420001), 1.7.1 `negu` |
| 0x08f1fc | f_08f1fc | src/sound/DjCheck.cpp | word 10: same |
| 0x069f28 | f_069f28 | src/system/SwgPlayer.cpp | word 26: same idiom |
| 0x092ec0 | f_092ec0 | src/sound/RaceVoice.cpp | word 11: register allocation |

Three of the four are the absolute-value idiom. Retail and 1.3.1 write it as
`bltzl r,+1; negu r,r` (branch-likely). 1.7.1 writes it differently. This fits the version
strings: retail and 1.3.1 are both `allegrex-2.2.1`, and 1.7.1 is `allegrex-2.2.2`.

## Conditional moves

**Fact.** Retail `.text` has 0 `movz`/`movn` in 375,023 words. Stock 1.3.1 and stock 1.7.1 at
`-O2` both emit them: 13 of the control set's 39 files contain them, and 8 control functions
differ because of them.

**Where they come from** (RTL dumps, `-da`, stock 1.3.1, all 13 files). Every register
`if_then_else:SI` first appears in pass `ce1` or `ce2`, the if-conversion passes. None comes
from expansion (`00.rtl`) or from `ce3`.

**No option turns them off.** The `target_switches` table in each cc1 (read from the binary) has
only the documented `-m` switches plus `debug`, `debuga` to `debugg` and `debugi`, and every
one of those has mask 0. That matches GCC 3.3.3 `config/mips/mips.h` in references, where all
`MASK_DEBUG_*` are 0. The only option that touches the producing passes is `-fno-if-conversion`.
It removes the moves but also removes if-conversion's other rewrites (store-flag, min/max),
which retail does have. The score drops to 49/60: 4 functions that were EXACT now differ, and only 1 is
fixed.

**Why the compiler emits them.** In both cc1 binaries, `movsicc` and the `*mips.md` movz/movn
define_insns are enabled by `ISA_HAS_CONDMOVE || mips_arch == 6`. The second arm is the Allegrex
addition (`ISA_HAS_INT_CONDMOVE`). Stock GCC 3.3.3 `mips.h`, as in references, defines it as 0.
Allegrex is MIPS II, so the first arm is false for it. The test is compiled into two places:

1. `init_all_optabs` stores `CODE_FOR_movsicc` into `movcc_gen_code[SImode]`, which is what
   lets if-conversion emit a conditional move. `init_optabs` has already set every entry to
   CODE_FOR_nothing (0x231 in 1.3.1).
2. `recog_3` and `recog_4` accept the integer movz/movn patterns (insn codes 342, 343, 345 and
   346 in 1.3.1), which combine can match directly.

**What reproduces retail.** A cc1/cc1plus in which that Allegrex arm is false, which is a GCC
3.3.3 built with `ISA_HAS_INT_CONDMOVE 0`. `nocmov.py` makes the change in a copy of each binary:
it NOPs the two optab stores (movsicc, movdicc) and turns the four `cmp $6` guards in recog into
`cmp $-1`. The sites are found by symbol and insn name, not by fixed address. The same six
changes apply to 1.3.1 and to 1.7.1.

| | 1.3.1 cc1 | 1.3.1 cc1plus | 1.7.1 cc1 | 1.7.1 cc1plus |
|---|---|---|---|---|
| sha256 before (16) | 1ee49eca0c5d0d24 | 54731121c6ba9023 | 837c7613c953d75b | 8011b6481bb229a6 |
| sha256 after (16) | abcf8f48a344d5cf | ff2693aed3d7081c | 2f0384b5941b6c87 | fc568c5d495fb126 |

**First attempt, and why it was wrong.** The first version of `nocmov.py` removed only the
optab store. It scored 59/60. In f_1116e0 (`return badch(ch) ? 0x8000000a : 0`), the
19.combine dump shows combine merging the store-flag mask (`negu; and`, which retail has word
for word) into an `if_then_else` that the define_insn `*mips.md:11389` (code 342) accepts. The
recog guards were added for that reason. With them the control set is 60/60, and no compiled
output in the whole tree contains movz/movn.

**Control functions that use `?:`** (movz/movn counts are in the stock build):

| Address | Function | 1.3.1 stock: movz/movn, result | 1.3.1 `-fno-if-conversion` | 1.3.1-nocmov | 1.7.1 stock `-mno-ulsw`: movz/movn, result | 1.7.1 `-fno-if-conversion` | 1.7.1-nocmov |
|---|---|---|---|---|---|---|---|
| 0x0a9134 | f_0a9134 | 0, EXACT | DIFFERS | EXACT | 0, EXACT | DIFFERS | EXACT |
| 0x0c2c44 | f_0c2c44 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x0c1b80 | f_0c1b80 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x0c23d8 | f_0c23d8 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x0c28e4 | f_0c28e4 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x093680 | f_093680 | 0, EXACT | DIFFERS | EXACT | 0, EXACT | DIFFERS | EXACT |
| 0x003830 | f_003830 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x003860 | f_003860 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x004864 | f_004864 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x09666c | f_09666c | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x0ca1a8 | f_0ca1a8 | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x0f6f2c | f_0f6f2c | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x0954ac | f_0954ac | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x095624 | f_095624 | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x112b70 | f_112b70 | 1, DIFFERS | EXACT | EXACT | 1, DIFFERS | EXACT | EXACT |
| 0x1116e0 | f_1116e0 | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x0838e4 | Queue<Rec16>::Last | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x08c21c | CMovieArena::GetAligned | 1, DIFFERS | DIFFERS | EXACT | 1, DIFFERS | DIFFERS | EXACT |
| 0x064d8c | f_064d8c | 0, EXACT | EXACT | EXACT | 0, EXACT | EXACT | EXACT |
| 0x067788 | f_067788 | 0, EXACT | DIFFERS | EXACT | 0, EXACT | DIFFERS | EXACT |

No control function regresses: all 52 that are EXACT under stock 1.3.1 stay EXACT under
1.3.1-nocmov.

## Default flags: evidence

- **`-O2`.** It is the a-priori candidate (the PSP SDK convention, `-O2 -G0`), and it is the
  only level that fits: 60/60, against 13 for `-O1`, 27 for `-Os` and 12 for `-O3`. The tree's
  own per-file exceptions all turn off `-O2` passes (`-fno-schedule-insns2`,
  `-fno-cse-skip-blocks`).
- **`-G 0`.** Set by the specs (`%{!G:-G 0}`). Retail's `.sbss` is size 0 and it has no `.sdata`.
  `.rel.text` has only R_MIPS_26, HI16 and LO16 relocations, and no GPREL16.
- **`-mno-ulsw`.** Retail has 0 `lwl`/`lwr`/`swl`/`swr`. The 1.3.1 specs add `-mno-ulsw`
  unless `-mulsw` is given. 1.7.1's specs dropped that line and 1.7.1 emits `swr` by default:
  7 control files fail to assemble with the only available gas, which rejects
  `swr` on allegrex. 1.7.1 therefore needs `-mno-ulsw` given explicitly to match retail.
- **C without `-fexceptions`.** None of the 398 tagged C functions in real TUs (outside CarMatrix.c) is
  covered by an FDE in retail `.eh_frame` (3,977 FDEs). CarMatrix.c is the exception (see below).
- **math-errno on.** 131 of retail's 153 `sqrt.s` are followed by the errno self-compare
  (`c.eq.s f,f`). So the default leaves `-fmath-errno` on, and `-fno-math-errno` is a per-file
  exception.

## Per-file exceptions (`@cflags`)

Each file's `@implements` functions were scored with and without its `@cflags`. The results are
identical under 1.3.1-nocmov and 1.7.1-nocmov.

| File | Flag | With | Without | Verdict |
|---|---|---|---|---|
| src/race/CarEventDispatch.cpp | `-fno-schedule-insns2` | 2/2 | 0/2 | needed |
| src/race/RaceRandom.c | `-fno-cse-skip-blocks` | 11/11 | 10/11 | needed |
| src/sound/SoundMath.c | `-fno-math-errno` | 16/16 | 15/16 | needed |
| src/system/MathFunc.cpp | `-fno-math-errno` | 12/12 | 10/12 | needed |
| src/system/Vector.c | `-fno-math-errno` | 37/37 | 35/37 | needed |
| src/race/CarMatrix.c | `-fno-math-errno` | 27/27 | 27/27 | not decided: no scored code changes |
| src/race/CourseAreas.cpp | `-fno-math-errno` | 12/12 | 12/12 | not decided |
| src/sound/Sound3D.cpp | `-fno-math-errno` | 6/6 | 6/6 | not decided |
| src/system/VectorInline.c | `-fno-math-errno` | 64/64 | 64/64 | not decided |
| src/control/batch5.c | `-fexceptions` | 6/11 | 4/11 | supported, but the file is not a real TU |

## Tooling and timing

- The compilers run on the compile host. `RRPSP_CC_HOST` (user@host) and `RRPSP_CC_KEY` (key
  path) must be set; nothing about the host is in tracked files. Everything there lives under
  `~/rrpsp/`. Run `python3 tools/toolchains/cc.py --setup` once: it checks both tarballs by
  sha256 (1.3.1 `788b6d2c…ea2e2e`, 1.7.1 `55d4267b…2f3484`), unpacks them, and builds the
  `-nocmov` variants.
- 1.7.1 packaging. Its driver ships only as `psp/bin/gcc`, which cannot find its own headers
  from there, so setup copies it to `bin/psp-gcc`. Its `as`, `ld` and the other binutils are
  empty files, so both compilers use the 1.3.1 assembler.
- Round trip, measured from the Mac, with a new SSH connection and no cache:
  - 2,967-byte file: 0.33 s
  - 5,637-byte file: 0.28 s
  - SwgPlayer.cpp (572,518 bytes, the largest in the tree): 1.93 s

  With the SSH connection already open and no cache: 0.09 s for the small files and 1.66 s for
  SwgPlayer.cpp. A cached hit takes 0.04–0.05 s. The target was well under 12 s cold.
- `ctlscore.py` is temporary. It does not check relocation targets, and it takes each
  function's length from the compiled symbol. It was shown able to fail:
  - `--selftest` flips one unrelocated word in every EXACT function, and each then DIFFERS.
  - A copy of `src/sequence/FadeColourState.c` under build/ with `D_1d5a80 = 1` changed to
    `= 2` in f_0e9e08 only: that function goes from EXACT to DIFFERS at word 1 (retail
    24040001, compiled 24040002). The other 7 functions stay EXACT.

## Not settled by the evidence

1. **The real 1.5.1.** Retail was built with psp-1.5.1, which is not available. `1.3.1-nocmov`
   reproduces every real-TU `@implements`, but whether 1.5.1 lacked Allegrex conditional moves
   through its build configuration or some other way is not known. Nothing here shows a
   difference between 1.5.1 and 1.3.1-nocmov. That is not the same as showing there is none.
2. **The assembler.** Only gas 2.14 from 1.3.1 is available. Gas fills delay slots and
   expands macros, so a different retail gas could matter. No disagreement has been seen.
3. **pspspecs.** Both drivers warn that `/usr/local/psp/devkit/lib/pspspecs` (an SDK file) is
   missing. Its contents, and whether it changes any compile-time option, are unknown.
4. **`-fno-math-errno` in CarMatrix.c, CourseAreas.cpp, Sound3D.cpp and VectorInline.c.** The
   scored code is the same with or without it, so the evidence does not decide whether these
   files really had it.
5. **CarMatrix.c and `.eh_frame`.** 19 of its 27 functions are covered by retail FDEs, but a C
   file without `-fexceptions` emits none. It may have been C++ or built with `-fexceptions`.
   `.text` does not show the difference, and this scorer does not read `.eh_frame`.
6. **`src/control/batch*.c`.** These are the older compiler-identification files. 12 of their
   `@implements` DIFFER under every setup tried, and they were not part of this control set.
   They are probably transcription problems, not a compiler question, but that has not been
   checked.
