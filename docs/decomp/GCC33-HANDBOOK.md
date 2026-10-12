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

## Driver

Compile through the toolchain's own driver (`psp-gcc` / `psp-g++ -S`), which `score.py` does. The driver adds `-march=allegrex -mtune=allegrex -mno-ulsw`, `-D__psp__ -D__SCE__ ...`, and the newlib include path. Calling `cc1` directly lacks them; the control-set results were the same both ways.

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
| A C++ `new T` with no landing pad, followed by a call on the new object | the constructor is inline and cannot throw; the call is a **separate statement** after `new` (`g = new T; g->Init();`). A call inside the constructor adds a cleanup that deletes the object. | main (0x0006b8) |
| Small struct: words zeroed except the fields then assigned, plus a redundant byte store | `memset(&s, 0, sizeof s)` expanded inline. The stores the following field assignments overwrite are deleted as dead, and a later `s.char_field = 0` survives. | f_0004a4 |
| `mov.s $f20,$f12` hoisted before a branch, with `f20` saved | the float is passed to a callee on the cold path | f_0fa640 |
| `move v0,v1` return; the error path sets `li v1,-1` | the status variable reused for the result: `ret = call(); if (ret != 0) return -1; ...; ret = expr; return ret;` | f_006094 |
| A signed `/1024` whose result stays in the dividend's register | in-place `x /= 1024;` before the use | f_006094 |
| A sub-struct's address in a saved register (`addiu s3,s0,128`) for later field stores | a pointer local: `T *sfo = &param.sfoParam;` | f_0061b0 |
| Blocks after a jump-table `jr` in a fixed order; cases equal to the default still in the table | write the cases in retail's block order and list the empty ones (`case 1: break;`) | f_006680 |
| Static destruction: one `beqz` guard per object, each vptr store in the next guard's slot | each derived class declares its own `virtual ~X() {}`. A non-virtual inline destructor lets cse merge guards; a base-only virtual destructor stores the base vtable | 0x006a58 |
| Member zeroing stores to +64 then +68 in a constructor | `head = tail = 0;` in the body. A mem-initializer list gives the reverse order | 0x006bbc |
| `sw v0,0(sp); lw v0,0(sp)` straight after a call | a `volatile` local: `volatile unsigned t = f(); seed = t;` | 0x0067b4 |
| A `_GLOBAL__D_` with an empty destruction branch | some static object has a non-trivial (even empty, user-declared) destructor; without one there is no `_GLOBAL__D_` | 0x006794 |
| Pointer-to-member constants copied from `.rodata` `{pfn, 0}` pairs through registers | `states[i] = &C::f;` assigned in the constructor body, before the plain pointer members | 0x006bbc |
| `move s2,s1` in the prologue; two registers holding one global's HI in a loop | an early `return 0` inside a do-while instead of `break` | 0x0010b8 |
| Byte flag stores interleaved with int and global stores; loads scheduled across them | declare the fields `bool` (own alias set), not `char` (alias set 0) | 0x0009b8 |
| One `li 1` register feeding an int global store and later byte stores | put the int store before the bool stores | 0x0009b8 |
| A global store kept after stores to other globals (not hoisted by sched2) | store through `this` in an inline method (`D.Reset()` doing `m60 = -1`) | 0x0009b8 |
| `lui a0; addiu a0; jal; move a1,v0` rather than `addiu a0` in the slot | the callee returns a value (a void prototype changes sched2 priorities) | 0x0009b8 |
| Virtual call loading the function pointer from the static vtable (`lw v1,%lo(_ZTV+8)`) | call on the global object itself (`D_1d8910[0].f()`); a load through the vptr means a local pointer was used | 0x0009b8, f_001154 |
| `bnez` with `move a0,zero` in the slot, then `li a0,1`, then a shared `jal` | separate calls in if/else; a ternary folds to `sltiu` | f_001154 |
| Branch on an `xori` result that is also stored to a field | `m14 = !first; if (!m14)` | f_001154 |
| Multiply scheduled after a call in a comparison | write the call first: `Hcount() - D > frames*286 - 5` | f_000fcc |
| `move v1,v0; move v0,zero; max v0,v1,v0` after a call | `int len = 0; ...; int r = f(); len = MAX(r, len); return len;` with a macro `MAX(a,b) ((a) > (b) ? (a) : (b))`. An inline function or `MAX(r, 0)` gives `move v1,zero; max v0,v0,v1` | f_003800 (and four siblings) |
| A running maximum folded into the accumulator's register | `len = MAX(new_expr, len);`, the new value first | f_004864 |
| `max v0,v0,s1` with the later call's result in v0 | `MAX(a, b)` with `a` the earlier result, held in a saved register | f_0039fc, f_003c58 |
| Independent stores emitted as "last statement first, then the rest in source order" | put the store wanted first as the last statement | f_005470 |
| The block after a table jump is not the first case, yet that case's constant is first in `.rodata` | the first case's body written twice (an early `case 9:` and an identical later case group); cross-jumping keeps the later copy | f_005554 |
| `jr ra; nop` with v0 left holding a loop's last `slti` result | the function falls off the end with no `return` (C); `return 0` adds `move v0,zero` | f_005a38 |
| A strength-reduced index giv `addu v0,v0,this` (this second) | index the array inside the loop (`m668[n]...; n++`), not a pointer set up before it | f_005c34 |
| `max` with the result in the first operand, plus a cross-jumped store | `if (a < x) a = x;` (ternary spellings swap the operands) | f_002108 |
| `beqzl` to the loop latch | the body wrapped in `if (p) { ... }`; `if (!p) continue;` inverts the branch | f_002574 |
| A sub-object field pointer kept in a callee-saved register | small inline methods on the sub-object (`ring.Empty()`, `Front()`, `Pop()`); plain field access folds the offset into `this` | f_001e34, f_001b3c, f_001ecc |
| Ring push: `lw tail` before the block copy, `sw tail+1` through a separate address, then `lbu`/`sw` of the same word | `e[tail++] = r; tail = (unsigned char)tail;` | f_001ecc |
| One struct copy versus two | a complete aggregate initialiser builds a temporary and copies it; a partial one clears first (a `sw zero` survives under halfword stores); `const T&` versus by value removes or adds a copy | f_002c50, f_001ecc |
| Signed `lh` with full-index addressing | short fields read into `int` locals, the array indexed directly (not through a pointer) | f_002410 |
| Loop counter and pointer allocated differently | one loop variable per loop | f_0030f4 |
| Two clock reads through one volatile stack slot | an inline helper `Now()` with a volatile local | f_002edc |
| A function placed after `_GLOBAL__I` | a non-static `inline` function emitted out of line (link once), defined before its caller | f_002edc |
| A small function after `_GLOBAL__D_`, called from static init | the compiler-generated constructor of a class whose base has an out-of-line constructor (a `.gnu.linkonce.t` function; tag it at its retail address) | 0x001554 |

**Callee prototypes are behaviour.** Declaring a void-called function as returning `int`, or giving a callee too few arguments, changes register allocation downstream (f_0f1aa0, f_08e0c8).

## Open residue (not understood; do not guess)

- **f_0922a0.** Retail returns through `v1` + `move v0,v1` and computes `2 - (x==0)` with `sltiu`/`li`/`subu`.
  - Holding the comparison in a variable gives the arithmetic, but with the result in `v0`.
  - Under nocmov, the inline form folds to `(x!=0)+1`.
- **f_0c644c.** Retail if-converts a `max` but keeps the branch for the upper clamp `if (i>3) i=3`. Eight spellings were tried under **stock** 1.3.1. Re-test under nocmov.
- **f_14df20** (C++ refcount dispose in an EH region). With `-fexceptions` plus a cleanup, 8 of 28 words still differ, all in the `blez` delay-slot fill. Re-test as `.cpp` under the current scorer.
- **f_07a838** (C++ constructor with a landing pad). Not yet transcribed as `.cpp`.

- **f_0004a4** (module loader, `src/system/main.cpp`). The frame, the option struct's layout and its initialisation pattern are solved: `memset` + `size` + `mpidtext` + `position = 0` after the `sprintf`. The control flow matches.
  - The remaining differences are three tie-breaks: the zero stores at +8/+12 swapped; `move s1,v0`/`move a0,v0` swapped; and after `sceKernelStartModule`, retail fills the `bltz` slot from the success path (`move a0,s1`), which leaves `sceIoClose`'s slot a `nop` (+4 B).
  - Eight source spellings (goto, nested ifs, if-assign, value-init, field stores, declaration orders) compile to the same RTL.
  - Next: diff the `sched2` and `dbr` dumps against retail's order.

## C++ objects in the scorer

- Vtables, typeinfo and type-name strings are resolved by address from `config/us/rtti.csv` (`tools/analysis/rtti.py`), so constructors and virtual calls on the static vtable grade EXACT.
- Inline methods emitted out of line, and compiler-generated constructors and destructors, live in `.gnu.linkonce.t.*` sections. Tag them like any function (Name = a substring of the mangled name). An object file's out-of-line D1/D0 destructors often sit after its `_GLOBAL__D_`.
- A constructor of another object file's class, called by name, needs a `config/us/symbols.csv` row; add it once a byte-exact caller proves the address.

## Map defects seen

Fixed in `tools/analysis/funcmap.py`: jump-table case labels taken for functions (f_006978), and back-to-back leaf functions merged (0x006018 + 0x006024, 0x0992fc + 0x099328, the three empty functions at 0x099354). Earlier: `config/us/funcs.csv` merged two functions when the second has no FDE, no `jal` and no pointer reference: 0x119dc8 + 0x119e38, and 0x12f1c4 + 0x12f264 (newlib `ratio` + `_mprec_log10`). The fix is a prologue (`addiu sp,sp,-N`) split after `jr ra` + slot.

## Library code

Newlib is statically linked (`ratio`, `_mprec_log10` at 0x12f1c4 to 0x12f2xx), so it can be matched from its own source.

## Tools

| Tool | Purpose |
|---|---|
| `python3 tools/rrdis.py 0xADDR` | Annotated retail listing. |
| `python3 tools/score.py FILE [--cc 1.3.1-nocmov\|1.3.1\|1.7.1] [--flags …] [-v]` | Score every `@implements` tag. EXACT needs the bytes, the relocation types and every reference's target or contents to agree; BADREF means the bytes agree but a reference does not. |
| `-da` | Per-pass RTL dumps: `tools/toolchains/lima.sh sh -c 'cd build/da && ../toolchains/psp-gcc-1.3.1-nocmov/lib/gcc-lib/psp/*/cc1 -quiet -O2 -G0 -da t.c'`. |
