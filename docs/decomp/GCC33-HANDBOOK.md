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
| `xori vX,vX,K` + `beqz` for an equality test | an **inlined predicate** returning the comparison. A direct `if (x == K)` gives `li`+`beq`. | f_010ac4 (now in `WirelessBattleModeJob.cpp`) |
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
| `xori`+`beqz` on a global struct's field | an inline predicate method `bool IsStatus(int s) { return status == s; }` | f_007178 |
| A vptr load scheduled ahead of stores to a local object's fields | declare its byte field `bool` (`unsigned char` is alias set 0 and pins the load) | f_0074f8 |
| `addiu aX,vY,4` in a `beqz` slot, then `jal` with a `nop` slot, for a call on a sub-object | take the sub-object's address first: `Sub *sub = &l->m4; l->m453 = 1; if (sub->p) sub->f();` | f_0074f8 |
| A mode job's event loop | inline `Pop()` returning -1 when empty, testing `tail == head` (the other order swaps the `beq` operands); `while ((e = queue.Pop()) >= 0) ...;` | 0x006f34 |
| Another object file's constructor and destructor called with a landing pad | an inline wrapper `struct X { X() { f_07ab2c(this); } ~X() { f_07aba8(this); } };` | 0x0072b0 |
| Struct elements copied load/store, load/store, loads addressed from the global's base (`lw 2712(a1)`) | element-wise copies through an array member (`d[j][k].v[0] = s[j][k].v[0];`, `struct Tri { int v[3]; }`). A struct copy folds the base into the symbol; named fields let GCC reorder the loads | 0x0093d0 |
| Outer offset stepped by `addiu t3,t3,63` then `sll a2,t3,6`, inner `li 335`/`bgez` down-counter | a 2D array `T m[3][336]`; a 1D `[j*336+k]` steps by 4032 instead | 0x0093d0 |
| Two separate compares `li s0,1; beq v1,s0; li v0,2; beq v1,v0` | two separate `if (x == 1) return; if (x == 2) return;`. `x == 1 \|\| x == 2` or a two-case switch folds to `addiu -1; sltiu 2` | 0x008244 |
| `lw v0,layer` ... `move a0,v0` around a field store before a virtual call | read the object into a local first, then store, then call: `CLayer *l = G.layer; o.m28 = 0; l->v2(&o, 0);` | 0x012a30, 0x014754 |
| Retail keeps the main block as the fall-through after `bnez` | spell the other arm `else { g(...); return; }` with `g` again after the if | 0x0140c8 |
| One `li a2,1` shared by two conditional bool stores | hold the constant in a local: `bool one = 1; if (A) m512 = one; if (m512 && B) m500 = one;` | 0x0137e8 |
| `(x-1) < 6u`, then `beq 7`, then `beq 8` | an if-chain `if (x >= 1 && x <= 6) ... else if (x == 7) ... else if (x == 8)`; a switch gives `slti`/`blez` | 0x0137e8 |
| `new` of N bytes then `jal` to another class's constructor, no vptr store, cleanup calling `operator delete` | allocate a plain block whose inline constructor calls it: `(CReplay *)new CReplayBlock` | 0x013bac |
| String literals BADREF only by their order in `.rodata` | keep functions in retail address order even where a state table lists them otherwise | 0x013dc4, 0x013f34 |
| An inline `if (p) call` kept in line, not moved to the function's end | load the pointer into a pointer-typed local first (`void *q = t->p; if (q) t->f();`) so GCC's pointer prediction fires | f_00c4b4, f_00c9c8, f_00cdd0 |
| A queue push after a call uses v1, not v0 | the callee is declared to return `int` | f_00aee8, f_00ab18 |
| A table lookup that rematerialises the table address on both loop exits | a macro naming the global table directly, with an output-pointer local; an inline function taking the table keeps one register (and is not inlined when used twice) | f_00ca54 |
| Copy loops addressing a global from one base register reused across statements | a local pointer `T *g = &D_233f70;` | 0x00dd64 |
| Separate tests for 2 and 0x400000 instead of one `& 0x400002` | an inline predicate: `Trig(2) \|\| Trig(0x400000)` | f_00ab18 |
| The out-of-line target is a call block shared with another path, which falls through | `if (cond) goto update;` before the fall-through code; if/else, else-if and early return all give the opposite layout | f_00fe44 |
| `(x != 0) + 1` as `sltu`+`addiu` | the comparison held in a variable: `int h = x != 0; m = h + 1;` | f_010100 |
| A word updated in one read-modify-write (`lhu` low half, `addu` high, `and 0xffff8000`, `addu` low) | hand-packed arithmetic on a plain unsigned int: `w = (w & 0xffff) + (hi << 16); w = (w & 0xffff8000) + lo;` (bitfields give `or`/`sh` chains) | f_00e238 |
| A store kept before a global load even though it is overwritten later | read the global through a local pointer: `int *p = &D; m68 = 0; m360 = *p;` | 0x011ea4 |
| Adjacent words zeroed as base+`%lo` and `4(reg)` pairs | `memset` of each small array, defined in the file (word aligned) rather than `extern` | f_00e12c |
| `move aN,v0` after a call, the result kept in the argument's register | assign the result back into the variable passed in: `p = f(p);` (in an inline helper, the helper's own parameter) | f_0216e8, f_021750, f_0213a0 |
| An aligned width or-ed into its own register (`or a1,a1,v0`) | the plain variable first: `K \| (bw \| ((fbp >> 24) << 16))` | f_021798 |
| A null test with the zero case placed last and the other arm's increment hoisted | declare the argument a pointer and write `if (p == 0) {...} else {...}` | f_021798 |
| Byte stores of a constant 16-bit field using its low byte directly (`li 16`, not `li 272`) | `__attribute__((packed))` vertex structs written field by field (an alternative to the put16/put32 helper row above; source arrays stay unpacked) | f_02202c |
| A two-value pointer select whose constants are reused only up to the join | write the dependent statements in both arms; cross-jumping merges the tails. A ternary gives no reuse; `x = A; if (!c) x = B;` reuses across a later call too | f_02048c |
| A switch on `m & 0x7f` compiled as `slti v1,2` + `bnez` | the switch value a signed int; unsigned folds to `beqz` | f_02048c |
| `addu v1,s8,v1` (offset register first) | the offset declared `short` | f_02048c |
| An inline routine's output pointer kept in a saved register (`move s7,sp`, stores through it) | write through a reference parameter of an inline helper: `static inline void FindSelect(Name &out, ...) { out.Set(...); }` | f_014a4c, f_014b9c |
| A table record read in a loop, the size table's base hoisted and no stray hoisted address | the record in its own variable: `void *rec = t.Get(...); memcpy(dst, rec, size);` | f_014a4c |
| A lookup result stored to the stack and reloaded, then a second lookup into a slot | a `Name` type with a user copy constructor and a named-return `Find`: `Name n = Find(x); out = Find(n.a);` in an inline taking `Name &out` | f_014cf8 |
| A value copied T to P on the stack, then `bnez` on P's first word | the inner lookup returns a POD row (no copy constructor) and an inline takes it by value plus an out reference | f_015ed8 |
| Static init with one guard for all objects | the record has a user constructor and its arrays have POD elements; an element type with even an empty user constructor re-tests the guard | f_017868 |
| A store right after a constructor, addressed by its own symbol | a separate global object with an inline constructor, not a member | f_017868 |
| An `int` field read before a flag store, both before a destructor call | an early `if (!x) return 0;` rather than wrapping the body in `if (x) {...}` | f_017a20 |
| An object copy that leaves word 0 (the vptr) alone | a member type with an empty `operator=` (`struct VtPtr { void *p; VtPtr &operator=(const VtPtr&) { return *this; } };`); a shared word at +4 belongs to a base class, whose copy comes first | f_017e1c |
| An implicit `operator=` called instead of inlined | it inlines only up to 22 member statements per class level; split larger ones with an intermediate base or array members | f_017e1c |
| An 8-byte run of `lb` loads in a copy | a `char m[8]` array copied as a block; one `unsigned char` among `bool`s changes the load order | f_01808c, f_01833c |
| A byte store addressed from the object base (`sb 472(v0)`) | the field belongs to the outer class, not its sub-object | f_017c88 |
| `return 0` through v0 rather than a0 | one combined `if (!a \|\| !b) return 0;`; two early returns put it in a0 | f_01896c |
| A step function with a single exit `move v0,s2` | `int r = f(); if (r) {...} return r;`; a success branch written first gives retail's block order | f_01abf4, f_01bc5c |
| Byte stream writes and reads in retail's order | `Put8(int v) { *cur++ = v; }` with `Put32` built on it; `Get8() { return *cur++; }`; copy loops written as `*s->cur++ = x[i]` with the count and data pointer in locals | 0x01b... (CGameSaveData::Save) |
| A random index keeping the seed's register | `int idx = Rand() % 10;` in its own variable | f_0196cc |
| A class copy that stops before the tail padding (236 of 256 bytes) | the class is non-POD (`CInfo() {}`) and its 64-byte alignment comes from a member attribute, not the type | 0x023f30 |
| A non-polymorphic base placed at its alignment (+64) after the vptr | the `CKeyLinkList` layout: a 64-aligned member is not put into the base's tail padding | 0x023340 |
| `delete[]` with a built-in null check and a 64-byte cookie (count at -4) | the element type has a destructor; for a POD array the null check is an explicit `if` | 0x0233dc, 0x023e54 |
| A class constructor not inlined into static init | it is implicitly defined; declare it explicitly (`CKeyLinkList() {}`) | 0x023b6c |
| No null check on a derived-to-base pointer conversion | take the base address directly: `CLinkList *l = &D_23c240;` | 0x0234a4 |
| A BST search reloading `*link` each step | a link-only loop: `while (key != (*link)->key) link = ... ? &(*link)->m0 : &(*link)->m4;` | 0x023fe8, 0x0241a0 |
| An iterator stored to a stack slot that is never read back | a small iterator class with `operator!=(const&)` | 0x0240cc |
| A result in a saved register overwritten by the next call | one variable reused: `info = f(id); if (info) return 0; info = g(id);` | f_023038, f_022d00 |
| A parameter's register reused as a down-counter | the parameter itself reassigned (`n = (n + 7) >> 3`) | f_022f54 |
| Mipmap command words as induction registers stepped by 0x1000000 | `((0xa0 + lv) << 24)`; `(lv << 24) + 0xa0000000` shares the shift and nothing is reduced | f_0235ac |
| `bnezl`/`sll` in power-of-two and log2 helpers | `static inline` helpers with `break` | 0x023a20 |
| Two independent loop-entry moves in the wrong order | read the field into a local before the copy (`char *f = lookup(...); memcpy(dst, f, n);`). sched1/sched2 tie and keep insn order, and loop hoisting follows the order in the body | f_00ca54 |
| A 2D slot index with the -1 applied after the add | `int k = x - 1; int slot = c * 7 + k;`, before the arithmetic that follows | f_00c540 |
| A remainder in a saved register that also holds its quotient | `secs % 60`, not `secs - secs/60*60` | f_00c540 |
| A table entry's address formed right after a call, its load deferred past later calls | `const char **fmt = &T[f()]; ... sprintf(..., *fmt, ...)` | f_00c540 |
| A VFPU-only leaf ending `jr ra; nop` | end the `__asm__` with a local label `"1:"`; otherwise the assembler (reorder mode) moves the last instruction into the delay slot | f_01e028, f_01edb8 |
| An address computed right before each VFPU sequence | separate asm statements, each with its own address operand; one combined statement computes all addresses up front | f_01edfc, f_01ed64 |
| A float constant loaded with `lui` + `lv.s %lo` inside VFPU asm | a file-scope `static const float` through an `"m"` operand (a float argument as `"m"` gives the stack-slot form) | f_01e0ec |
| A constructor zeroing a 16-word element array with `bgez` and a biased pointer | an explicit loop in the body calling an inline `Clear()`; an element constructor gives a `bne -1` loop | 0x0201d4 |
| Sub-object first words zeroed before the constructor body | mem-initializers on member structs (`CResource() : m0(0) {}`); identity-matrix stores straight off `this` come from a macro (an inline method keeps a base register) | 0x0201d4 |
| Many float fields read from a header pointer and stored without reloads | read the header fields into locals first (aliasing forces reloads otherwise) | f_01dbc4 |
| A static string-pointer array whose strings follow a jump table in `.rodata` | a function-local static in its user; a file-scope array emits its strings last | f_01c1e4 |
| A replacement block placed out of line inside a loop | `if (cond) continue;` followed by the block | f_01d4b8 |
| Rows copied into a global, element 0 from the base and 1 to 3 through a row pointer, the source addressed flat | plain struct assignment per row: `D.p[i] = m->p[i];` | f_02b67c |
| In a copy followed by float updates, only the last row's overwritten word dropped as dead | copy all rows first, then `D.p[i].w = -D.p[i].y * d;` through field access | f_02b714 |
| A float temporary copied word by word, its fourth word stored as `sw zero` | an aggregate initialiser whose fourth member is `int`: `struct { float x, y, z; int w; } d = {-a, -b, -c, 0};` | 0x029524 |
| `lb` on flag fields (also f_02cf3c) | plain `char` fields (but `unsigned char` where they feed a stored `\|\|`; `bool` gives `lb` there) | 0x0293e4, 0x0292fc |
| The loop tail loads the next word, tests `>> 24`, copies it to the top register in the slot | `do { c = *p++; ... } while ((*p >> 24) != 11);` | 0x02b854 |
| Inline asm ending in a store keeps `jr ra; nop` | wrap it in `.set push` / `.set noreorder` / ... / `.set pop` (or end with a local label, above) | 0x028b3c, 0x028d94 |
| `vpfxt [x,x,x,x]` rejected by the assembler | write `.word 0xdd000000` | f_027de4 |
| `sqrt.s` with no errno call | the object file uses `/* @cflags: -fno-math-errno */` (`-ffast-math` breaks `x-x` and division) | f_027d70, f_027d8c |
| Float stores kept interleaved with loads of the source | a `float *` source; a source of the same struct type lets GCC assume no overlap and hoist the loads | f_028188, f_02889c |
| A switch tested `beq 1`, `beqz`, `beq 2`, default falling through | `switch` on an unsigned value with cases 0, 1, 2 and default (a signed switch gives `slti`) | f_026bc8 |
| An address or-ed in place into the pointer's own register | two steps: `d = (T *)info->vram; d = (T *)((unsigned)d \| 0x40000000);` | f_026bc8 |
| A loop pointer initialised before a guard (`move` before `bltz`) | an early `return` instead of wrapping the loop in `if` | f_024fb4 |
| Separate equality tests sharing one body, constants hoisted after the tests | `if (op == 1) c++; else if (op == 2) c++; else { c++; continue; }` | f_025364 |
| A null-tested table entry put out of line | test the array element directly (no pointer local) and store in each arm (the reverse of the pointer-local row) | f_025118, f_026948 |
| A chained zero assignment's store order | the leftmost element first, then the following statement, then the rest right to left | f_02822c |
| A data file open whose success path returns v0 directly | `if (fd >= 0) return fd; iprintf(...); return fd;` | f_027850, f_027a28 |
| Saved register pairs left unused around `long long` calls | hold the 64-bit results in `int` locals | f_02799c |
| A ring buffer with mixed this-based and ring-pointer addressing | loops read `head`/`tail` on the member directly; `At(i)`, `Pop()`, `Count()`, `Init()`, `Free()`, `Add()` are inline methods on the sub-object | f_032070, f_032780, f_0328b0 |
| A ring wrap with the size reloaded after the tail store | `if (i >= size) return i - size; return i;` | f_032138 |
| A pointer argument held in a register across setup | hold it in a local first: `char *out = m144; f(view->m288, out);` | 0x031cbc |
| A re-test of `a` in a two-arm condition | `if (a == 0 && b >= K) {...} else if (a == 1 && b >= L) {...}` | f_02ea2c |
| A float local copied to a field through integer registers (`lw`/`sw`) | the field and the local are a union with one float member (`union Angle { float a; };`); a one-float struct still uses FP registers | f_036600 |
| Both arms' constants loaded before a branch, stores merged into shared tails, `addiu v0,a0,16` in the slots | an inline helper that writes the words and returns `p + 4`, used as `return Helper(p, ...)` in every arm; test the flag negated for retail's fall-through | f_02dba8, f_02dcc8 |
| An 8-byte struct copy through one stack temporary, stored via a saved register holding the global | `T *m = &D; Rec r; ...; m->m0 = r;` | f_02c870 |
| Static init zeroing members in field order across two sub-objects | an explicit inline constructor on the outer class, and separate field-order statements in the sub-object's constructor (a chained assignment reverses the order) | f_02da28 |
| One block of stores reached from several returns, each loading its constant | separate `return White(out)` calls merged by cross-jumping | f_02cf3c |
| A small function after `_GLOBAL__D_`, called from static init | the compiler-generated constructor of a class whose base has an out-of-line constructor (a `.gnu.linkonce.t` function; tag it at its retail address) | 0x001554 |

**Callee prototypes are behaviour.** This includes the v0 versus v1 choice for later temporaries (f_01c2cc, f_01c648). Declaring a void-called function as returning `int`, or giving a callee too few arguments, changes register allocation downstream (f_0f1aa0, f_08e0c8).

## Understood, not yet proven byte-exact

- **`beqzl` with the not-found zero store in the slot, after a lookup.** Source: the field read after the lookup goes into a local before the copy, `char *f = f_0368e8(...); memcpy(D_24063c, f, D_1a211c[1]);`. Inline in the `memcpy` call, D_1a211c's address is built before the call and held in a saved register, and `dbr` then fills the branch from the found path. The lookup's own spelling does not matter. All four retail `beqzl` sites (f_010378, f_010b4c twice) now come out `beqzl`, but those functions still differ elsewhere. Single race lookups use plain `beqz` in retail too.
- C++ inline functions with two `return`s were not inlined here (emitted out of line).
- **A division by a variable set to a constant** (`div` by a register holding `li 32`, with the `break 7` check, not shifts): the divisor assigned to a local first (`int w = 32; pos / w`). Seen on 0x02e400 and 0x02e704, both still drafts.
- **Vertex pointer steps kept in one register** (`addiu v0,v0,5` between writes): the returned pointer stepped in place (`Vtx *q = f(); Vtx *v = q; q->...; q++;`). A float's bits loaded with `lw` after the preceding stores: `*(unsigned int *)&f` (a union lets the load move early). A constant spilled across a call: a `volatile` local. All three on parts of f_032c20, which is still a draft.

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

## Object file boundaries

`config/us/tus.csv` splits follow unwind info, not real object files. A C++ class's constructors and `Begin` often sit in the gap row before its first unwind-covered row, and its static init and out-of-line destructors in the gap row after. A worker matching a class claims the neighbouring rows it spills into.

## C++ objects in the scorer

- Vtables, typeinfo and type-name strings are resolved by address from `config/us/rtti.csv` (`tools/analysis/rtti.py`), so constructors and virtual calls on the static vtable grade EXACT.
- Inline methods emitted out of line, and compiler-generated constructors and destructors, live in `.gnu.linkonce.t.*` sections. Tag them like any function (Name = a substring of the mangled name). An object file's out-of-line D1/D0 destructors often sit after its `_GLOBAL__D_`.
- A constructor of another object file's class, called by name, needs a `config/us/symbols.csv` row; add it once a byte-exact caller proves the address.

## Data defined in a source file

A file-local constant named `D_XXXXXX` is resolved by address, like any `D_` name: the reference is proven to be retail's, and the M2 image keeps retail's bytes, but the constant's own contents are not compared. A full relink must check them (Vector.c, Transform.cpp: D_1a1914, D_1a1918, D_1a191c, D_1a1a80).

## Map defects seen

Fixed in `tools/analysis/funcmap.py`: leaf functions directly after an FDE function and claimed by nothing else (0x021cf8, 0x021d18; 328 in all), jump-table case labels taken for functions (f_006978), and back-to-back leaf functions merged (0x006018 + 0x006024, 0x0992fc + 0x099328, the three empty functions at 0x099354). Earlier: `config/us/funcs.csv` merged two functions when the second has no FDE, no `jal` and no pointer reference: 0x119dc8 + 0x119e38, and 0x12f1c4 + 0x12f264 (newlib `ratio` + `_mprec_log10`). The fix is a prologue (`addiu sp,sp,-N`) split after `jr ra` + slot.

## Library code

Newlib is statically linked (`ratio`, `_mprec_log10` at 0x12f1c4 to 0x12f2xx), so it can be matched from its own source.

## Searching statement orders

When only the order of independent statements is open, compile every permutation of the block as separate functions in ONE scratch file and compare the `.s` output, rather than one scorer run (about 10 s) per order. Record the winning order as a tie-break, not a rule. `mips` and `shared` are predefined macros under the PSP driver and cannot be identifiers.

## Tools

| Tool | Purpose |
|---|---|
| `python3 tools/rrdis.py 0xADDR` | Annotated retail listing. |
| `python3 tools/score.py FILE [--cc 1.3.1-nocmov\|1.3.1\|1.7.1] [--flags …] [-v]` | Score every `@implements` tag. EXACT needs the bytes, the relocation types and every reference's target or contents to agree; BADREF means the bytes agree but a reference does not. |
| `-da` | Per-pass RTL dumps: `tools/toolchains/lima.sh sh -c 'cd build/da && ../toolchains/psp-gcc-1.3.1-nocmov/lib/gcc-lib/psp/*/cc1 -quiet -O2 -G0 -da t.c'`. |
