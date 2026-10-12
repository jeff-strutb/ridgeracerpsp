# GCC 3.3.3 (allegrex) matching handbook

This is the symptom → source table for SCE `psp-gcc 3.3.3+allegrex`.

- Every table row was proven byte-exact on the retail function named in its last column, and that function's EXACT transcription is in `src/`.
- Rows are added only after a byte-exact proof.
- The control set behind these rules is `src/control/batch1..6.c`.

## Compiler and flags

- **Compiler: `psp-gcc-1.3.1-nocmov`** (the scorer's default), built by `tools/toolchains/mk_nocmov.py` from the pinned 1.3.1 tarball.
  - Retail contains **zero** conditional moves (`movz`/`movn`/`movt`/`movf`, integer or FP) in 375k instructions.
  - Stock 1.3.1 and 1.7.1 both emit them for two-way selects; they enable them for `mips_arch == allegrex`.
  - The variant removes the four `mov*cc` optabs and makes `recog` reject the 13 conditional-move patterns.
  - This is a *reconstruction* of the retail 1.5.1 behaviour. Proven on f_0877a8: the natural `k = quick ? 1000000 : 30000000` gives retail's `sltiu`/`negu`/`and`/`addu` only under the variant.
  - On the 61-function control set, the variant has no regressions against stock, and the 120-file corpus compiles with 0 internal compiler errors.
- **1.3.1 vs 1.7.1:** identical instruction output on every control function and on 118 of 120 corpus files. The differences are `.ident`, `li` comments (host `HOST_WIDE_INT` width) and one 64-bit-constant `li` ordering.
- **Default flags: `-O2 -G0`.** `.sbss` is empty in retail.
  - `-O2` does **not** inline plain `static` functions; mark helpers `__inline__` (C) or `inline` (C++).
- **Flags vary per TU.** This has been proven twice:
  - f_0942f0 is EXACT only without `sched2` (`-O1`, or `-O2 -fno-schedule-insns2`).
  - The library wrapper at 0x119dc8 is EXACT only with `-frename-registers` (or `-O3`). In it, every short-lived value gets its own register.
  - Both flag sets break most other control functions, so they are per-TU flags.
- **C++ needs `cc1plus -fexceptions`, which `score.py` adds for `.cpp`.**
  - Calls inside an EH region end basic blocks, so `sched1` cannot hoist argument setup across them.
  - The same body as C mis-schedules: f_064454 is EXACT only as C++.
  - A trailing, unreached `jal _Unwind_Resume; nop` is the landing pad. `f_166df8` = `_Unwind_Resume`.
- **ABI: EABI32.**
  - There is no outgoing argument area. The minimal non-leaf frame is 16 bytes with `ra` at `0(sp)`.
  - Float arguments go in `$f12…` independently of the integer arguments.
  - `long long` varargs go in `t0`/`t1`.
- **VFPU:** GCC never emits VFPU instructions; every VFPU sequence is `__asm__`. A function made entirely of VFPU instructions with `jr ra; nop` is probably a hand-written `.S` file (0x028b3c).
- **Delay slots** are filled by GCC's `dbr` pass, not by the assembler.

## Symptom table

| Retail shows | Source shape | Proven on |
|---|---|---|
| `xori vX,vX,K` + `beqz` for an equality test | an **inlined predicate** returning the comparison. A direct `if (x == K)` gives `li`+`beq`. | f_010ac4 |
| A base register for a sub-struct, fields addressed from it, a field **reloaded** after an array store | an inlined method on the sub-object (`ring_push(&p->ring, v)`) | f_010ac4 |
| A struct copy through two pointer bases, the first store from the parent | an `__inline__` copy helper on the sub-objects (`*d = *s`) | f_0ec8b8 |
| `slti`+`sltiu x,x,1` (no `xori`) | the comparison **held in a variable**, then `(z == 0)`. Written inline, `fold` produces another form. | f_001014 |
| `sltiu`+`negu`+`and`+`addu` select between two constants | plain `c ? A : B`, **under the nocmov compiler** | f_0877a8 |
| 64-byte struct assignment as a 4-word × 4 copy loop | `*p = t;` | f_0a6d90 |
| `blez` guard + do-while with a strength-reduced pointer | plain `for (i = 0; i < q->n; i++) f(&arr[i]);` | f_01d934 |
| Inner loop of N as a down-counter (`li N-1` / `bgez`) | plain nested `for` | f_026efc |
| `bnez state` falling into case 0, then `beq state,1`, then the default | an `if`/`else if` chain. A `switch` puts case 0 last. | f_01dac0 |
| Stores to A before B from one value | the chained assignment `A = B = v` | f_024930 |
| Float zeros from one FPR (`mtc1 zero,$f1` + `swc1`) in ascending order | `m[15] = m[13] = … = m[1] = 0.0f;`. Separate statements give `sw $0`. | f_0cdf38 |
| An FP result written into a parameter's register after its last use, not hoisted across a call | an in-place reassignment of the parameter (`e = e - g;`) after its last use | f_0cdf38 |
| An unnamed `.rodata` float constant | write the **literal** (`105.0f`), never `extern float`; the extern form changes FP allocation | f_0f2eac |
| Byte stores through one strength-reduced pointer (`sb …,0..11(a3)`; one `addiu a3,a3,12`) | an inline helper taking `(base, const offset)`: `put32(d, 4, v)`. `put32(d+4, v)` makes a separate pointer giv. | f_022848 |
| `addu vX, base, off` (base first), then a field load | the element address in a pointer variable: `q = &e[mid]; q->key` | f_10aff0 |
| `jal` with a `nop` slot right after a branch whose slot holds `move a0,sN` | the callee takes that argument; a `void` prototype changes local-alloc | f_08e0c8 |
| A saved register loaded with the object in a `jalr` slot, before a virtual call that supplies an argument | the object read into a temporary first: `o = p->x8; f(o, p->vt->fn(p,0), 1)` | f_102cf0 |
| `lui` after a call uses `v1` although `v0` is free; `v0` untouched until `jr ra` | the callee's result is returned: `int r = f(…); …; return r;` | f_0b20d8 |
| Two independent stores at a block's end in the **reverse** of the listing order | write them in the opposite order (seen twice) | f_10dd2c, f_0f1aa0 |
| `j L` with `addiu a1,a1,K` in its slot, into a shared call block | separate `return Ctor(x)` per branch, merged by cross-jumping | f_064454 |
| `mov.s $f20,$f12` hoisted before a branch, with `f20` saved | the float is passed to a callee on the cold path | f_0fa640 |

**Callee prototypes are behaviour.** Declaring a void-called function as returning `int`, or giving a callee too few arguments, changes register allocation downstream (f_0f1aa0, f_08e0c8).

## Open residue (not understood; do not guess)

- **f_0922a0.** Retail returns through `v1` + `move v0,v1` and computes `2 - (x==0)` with `sltiu`/`li`/`subu`.
  - Holding the comparison in a variable gives the arithmetic, but with the result in `v0`.
  - Under nocmov, the inline form folds to `(x!=0)+1`.
- **f_0c644c.** Retail if-converts a `max` but keeps the branch for the upper clamp `if (i>3) i=3`. Eight spellings were tried under **stock** 1.3.1. Re-test under nocmov.
- **f_14df20** (C++ refcount dispose in an EH region). With `-fexceptions` plus a cleanup, 8 of 28 words still differ, all in the `blez` delay-slot fill. Re-test as `.cpp` under the current scorer.
- **f_07a838** (C++ constructor with a landing pad). Not yet transcribed as `.cpp`.

## Map defects seen

`config/us/funcs.csv` merges two functions when the second has no FDE, no `jal` and no pointer reference: 0x119dc8 + 0x119e38, and 0x12f1c4 + 0x12f264 (newlib `ratio` + `_mprec_log10`). The fix is a prologue (`addiu sp,sp,-N`) split after `jr ra` + slot.

## Library code

Newlib is statically linked (`ratio`, `_mprec_log10` at 0x12f1c4–0x12f2xx), so it can be matched from its own source.

## Tools

| Tool | Purpose |
|---|---|
| `python3 tools/rrdis.py 0xADDR` | Annotated retail listing. |
| `python3 tools/score.py FILE [--cc 1.3.1-nocmov\|1.3.1\|1.7.1] [--flags …] [-v]` | Score every `@implements` tag. |
| `-da` | Per-pass RTL dumps: `tools/toolchains/lima.sh sh -c 'cd build/da && ../toolchains/psp-gcc-1.3.1-nocmov/lib/gcc-lib/psp/*/cc1 -quiet -O2 -G0 -da t.c'`. |
