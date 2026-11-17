# Gates

The tier of every function is decided by these tools. This page says what each one checks,
what it does not check, and how each was shown able to fail. Counts are printed by the tools
(`tools/progress.py`, `tools/validate.py`); none are kept here.

```sh
./setup.sh                                   # references, opcode table
export RRPSP_CC_HOST=...  RRPSP_CC_KEY=...   # compile host (never in tracked files)
python3 tools/validate.py                    # every gate, with times
python3 tools/score.py FILE...               # grade the tagged functions in FILE
python3 tools/sbs.py FILE 0xADDR [--blind]   # side by side for one function
python3 tools/image.py [--list]              # the M2 gate
python3 tools/progress.py                    # tiers
python3 tools/hooks/install.py               # hooks for this worktree only
```

## Tiers

| Tier | Meaning | Decided by |
|---|---|---|
| T4 | `@implements` in a real file, EXACT, placed by a green image gate | `image.py` |
| T3 | certified same behaviour | no tool exists; always 0 |
| T2 | tagged (`@implements` or `@draft`) in a real file, not T4 | tags |
| T1 | not tagged in a real file | tags |

The denominator is **proven game only** (class `game` in `config/us/fence.csv`), by the owner's
ruling. `progress.py` prints that table as its headline. The unknown code before the first
library fingerprint is not in the denominator; it gets one information line.

Real files are the sources under `src/` outside `src/control/`. The `src/control/batch*.c`
files repeat addresses of real files and are not translation units; their tags are not
counted.

M2 is all-or-nothing: while the image gate is red, no function is T4. `progress.py` prints
beside T4 how many EXACT functions the red gate placed byte-identically.

## Tags

A tag is `@implements` or `@draft` as the first word of a line inside a comment, followed by
`0xADDR us NAME`. It may follow `/*` or stand on a later line of the same comment. Its WHAT IT
DOES paragraph is the text after it up to the next tag or the end of the comment. Any other
use of the tag words is reported as a problem. The earlier scorer only read tags directly after
`/*`, so it missed 8 `@implements` that sit on later comment lines.

A tag's NAME is matched to a function symbol of the compiled object: exact, else the unique
symbol starting with NAME, else the unique symbol containing it (`_GLOBAL__I_`/`_GLOBAL__D_`
only when NAME names one). Two tags at different addresses that match one symbol are both
MISSING.

## score.py: the grader

Verdicts per tagged function: EXACT, BADREF, DIFFERS, MISSING.

| Check | Fails as |
|---|---|
| the file compiles, the name matches a symbol, ADDR is a `funcs.csv` start | MISSING |
| compiled `st_size` equals the `funcs.csv` size | DIFFERS |
| every word equal with each side's relocated field masked | DIFFERS |
| the same relocation type at every word (or none on both) | DIFFERS |
| every relocation resolves to retail's target | BADREF |

Retail targets come from `prx.py` (j26, word, HI16/LO16 pair) and, for a LO16 whose high half
no relocation records, from `hilo.py`, cached in `build/retail-facts/` under a hash of every
input it reads. A LO16 that `hilo.py` cannot recover is unprovable.

Compiled targets are the relocation's symbol plus its REL addend, computed as GNU ld does for
MIPS (HI16 with the next LO16 against the same symbol). They resolve by these rules, in order:

1. **Local code** (a section or local symbol in an executable section): the object's function
   symbol that contains the offset, which must be tagged in this file, plus the offset into it.
   This covers branches by `j`, calls to static functions and jump-table entries.
2. **A tag**: the symbol is claimed by a tag in this file, else by a tag in any real file.
3. **The name**: plain C `f_XXXXXX` / `D_XXXXXX`; a C++ free function `_Z<n>f_XXXXXX...`; a C++
   variable whose innermost name is `D_XXXXXX`. A C++ **method** name is not an address: of the
   488 tagged methods named `f_XXXXXX`, 205 are tagged at another address (overrides are named
   after the slot they fill), so a method must be tagged.
4. **A library symbol** listed in `config/us/libfuncs.csv` at one address (a proven fingerprint).
5. **A proven library symbol** (rule `libsyms`, the owner's ruling): a row of
   `config/us/libsyms.csv` with `accepted = yes`. See below.
6. **An import**: an undefined symbol whose SHA-1 NID (the first four bytes of SHA-1 of the
   name, little-endian) is the NID of exactly one retail stub in `.lib.stub`. 131 of the 132
   `sce*` names used in the source hash to a stub NID.
7. **Object data** (local data, or a global data symbol defined in this object or in another
   real file's object that names no address): the item holding the target must have
   byte-identical contents at retail's target. The item is the data symbol covering the
   offset; in a mergeable section the constant entry or the string through its NUL; otherwise
   the bytes up to the next offset anything in the object refers to. Relocated words inside it
   must have the same type at the same offset in retail (and retail none elsewhere in the
   range), and their targets are checked by these same rules, recursively: jump-table entries
   must point at the corresponding instructions, vtable slots at the same functions, typeinfo
   at the same names and bases. A `.bss` item must land in retail `.bss`. Each object item
   maps to one retail address per run; two addresses make every function that relied on it
   BADREF.

8. **The method-name rule** (rule `method-name`, the owner's ruling): a C++ method that no tag
   in the file or any real file claims, and that no real file defines a body for, resolves to
   the address in its own name (`f_XXXXXX`) when that is a `funcs.csv` start. Each site's
   retail target must equal it exactly. If any site of the same symbol in the run points
   elsewhere, every function using that symbol is BADREF. It applies to data references
   (vtable slots) by the same test. A tagged method keeps its tag's address. One limit
   follows: a single-file `score.py` run sees only that file's sites, so the image gate's
   whole-tree run is the one that decides.

   A function that reuses an object data item already checked in the run also inherits what
   checking it recorded: the rules used, method-name symbols and collected references. Before
   this, a vtable slot's method-name site counted only for the first function that reached
   the vtable.

Rules 4 (`library`) and 6 (`import`) go beyond the brief's list and are not yet ruled on.
Rule 5 (`libsyms`) is the owner's ruling. `score.py --json` lists the rules each EXACT function
used (`rules`), so the functions that depend on each can be counted and set aside.

### Proven library symbols (`tools/analysis/libsyms.py`, `config/us/libsyms.csv`)

The owner's rule: the address of a library symbol that `libfuncs.csv` does not identify is
proven when both of these hold:
- every reference to it, in functions that are otherwise EXACT, agrees on one retail address;
- the retail function at that address closely matches the reference library's copy of the symbol.

The first side is collected by `score.py` in a collection mode. In it, references to
reference-library symbols are recorded instead of failed, and the function is PENDING, never
EXACT. `libsyms.csv` is not used while collecting.

**What "closely matches" means, from what actually differs.** For the symbols with call sites,
the retail function was compared word by word (relocated fields masked) with every reference
copy in psp-gcc 1.3.1 and 1.7.1 (site counts are in `config/us/libsyms.csv`):

| Symbol | Retail against reference |
|---|---|
| `_Unwind_Resume`, `operator delete`, `operator delete[]`, `free`, `malloc`, `iprintf`, `__cxa_call_unexpected` | identical to the 1.3.1 copy |
| `operator new` (`_Znwj`) | one difference: the reference's `li v0,1` + `movz s0,v0,a0` (size 0 becomes 1) is retail's `bnez a0` + `li s0,1`; the other words of that window are the same, reordered by the delay-slot filler |
| `__gedf2` | one word: the value returned for NaN. Retail 0x164c48 is word for word the reference `__ltdf2` (and `__eqdf2`, `__ledf2`, `__nedf2`, which share its body) |
| `__ltdf2` | the mirror image: retail 0x164bc0 is the reference `__gedf2`/`__gtdf2` |
| `__truncdfsf2` | 31 words against 30: the reference's store-flag `sltu`/`or` for the sticky bit is a branch in retail, with another register and one store moved |
| `__si_class_type_info::__do_dyncast` (a vtable slot) | 40 words against 39: the reference's `movn` is store-flag arithmetic (`sltu`/`negu`/`and`/`addiu`) in retail, and a `bne` becomes `bnel` |

Retail `.text` has no `movz`/`movn` (docs/COMPILER.md), so a reference copy that uses one cannot
appear in retail unchanged. The rule therefore accepts:
- **exact**: every word and relocation type equals a reference copy;
- **cmov**: equal outside one window, inside which the words differ by exactly the idiom
  `li T,K` + `movz D,T,C` (reference) for `bnez C` + `li D,K` (retail), or `movn`/`beqz`.
  The branch must skip exactly that `li`, which is not in its delay slot. The window's other
  words must be the same multiset. `T` must not be read after the `movz` before it is written
  or a call clobbers it.

It refuses everything else. That includes a retail function that is an exact copy of a
different reference symbol and not of this one; this is what refuses the `__gedf2`/`__ltdf2`
pair, which a count of equal words (33 of 34) would have accepted. The store-flag substitutes
in `__truncdfsf2` and `__do_dyncast` are compiler differences of the same family. They are not
the branch idiom, though, and nothing here proves them equivalent, so they are refused and
listed.

**Data.** A library data symbol is accepted on the same two sides. All references agree on one
address. The retail bytes there have the reference symbol's relocations (same type, same
offsets) and equal bytes elsewhere. Every relocated slot's retail target closely matches the
reference's target symbol (code by the code rule, data recursively). The two libsupc++
typeinfo vtables that class typeinfo points at, `__class_type_info` and
`__si_class_type_info`, agree at every site. Both are refused all the same, because
their `__do_dyncast` slot is refused (above). They are listed in the data part of the CSV.

### Source proofs (`tools/analysis/libsource.py`, match kind `source`)

The owner approved one download: the GCC 3.3.3 release source from the GNU project's server,
as its two parts. They are kept untracked in the main checkout's `references/` and checked by
sha256 before use:

| File | Bytes | sha256 |
|---|---:|---|
| `gcc-core-3.3.3.tar.bz2` | 11,553,433 | `a4bf992ca719711a77d09b84fc496bbe6fcecb8feac996c2e6e102d3cbbe15eb` |
| `gcc-g++-3.3.3.tar.bz2` | 2,074,860 | `5b82243239d4a400cfe94ac9b27a008c510aa55c574b2df1f6e95b45d6a70bc4` |

They are unpacked under `build/gcc-src/`. No script from them is run: the one generated header
the libgcc units need (`tconfig.h`) is written by `libsource.py` from what `gcc/mkconfig.sh`
writes.

A unit is first **admitted**: compiled with STOCK psp-gcc 1.3.1, it must reproduce the
reference archive's object exactly. That means the same allocated sections, the same bytes
with relocated fields masked, and the same relocations (offset, type, symbol, addend). Only
then is it compiled with the pinned 1.3.1-nocmov. A symbol is **proven** when that build
equals retail at the address all sites agree on, and every relocation target is proven in turn.

The flags were read from the makefiles and stated before compiling:
- libgcc's fp-bit units: from `LIBGCC2_CFLAGS`, `mklibgcc.in` and `mips/t-elf`. They are
  `-O2 -DIN_GCC -DCROSS_COMPILE -DIN_LIBGCC2 -D__GCC_FLOAT_NOT_NEEDED -G 0
  -DFINE_GRAINED_LIBRARIES -DL_<name>` on `dp-bit.c`. There is no `-g`, because the reference
  objects carry no debug sections. `tconfig.h` is the one for a mipsel ELF target.
- libsupc++: from `libsupc++/Makefile.am` and the top-level `CXXFLAGS`. They are
  `-g -O2 -fno-implicit-templates`. There are no section-splitting flags (the reference
  `tinfo.o` has one `.text`) and no PIC (its relocations are absolute).

Each source is flattened (every include that resolves in the source tree is inlined, with line
markers) so that `cc.py` can send it.

| Unit | Reference object | Admitted | Proven at retail |
|---|---|---|---|
| `tinfo.cc` | `libsupc++.a(tinfo.o)` | yes, exact | `__class_type_info` vtable 0x1b71a8, `__si_class_type_info` vtable 0x1b7178 (every slot, typeinfo and name) |
| `fp-bit.c -DL_df_to_sf` | `libgcc.a(_df_to_sf.o)` | yes, exact | `__truncdfsf2` 0x164f7c |
| `fp-bit.c -DL_ge_df` | `libgcc.a(_ge_df.o)` | **no** | not attempted |
| `fp-bit.c -DL_lt_df` | `libgcc.a(_lt_df.o)` | **no** | not attempted |

The store-flag differences that refused `__truncdfsf2` and `__do_dyncast` under the cmov rule
are what the retail compiler makes of the same source: the pinned compiler, given the admitted
source and flags, produces retail's words.

**`_ge_df`/`_lt_df` are not reproduced, so they stop there.** Stock 1.3.1 with the stated flags
gives a 96-byte stack frame where the reference objects have 112. Every other word is equal,
apart from the stack offsets that follow from the frame size (the saved `s0`/`ra` and the
`a2`/`a3` argument spill move by 16). The flags were not changed to find out why.

**`__gedf2`/`__ltdf2`, what the evidence says.** In the GCC 3.3.3 source (`gcc/config/fp-bit.c`)
the only difference between the two functions is the value returned when an operand is a NaN:
`__gedf2` returns -1 ("false, truth >= 0") and `__ltdf2` returns 1 ("false, truth < 0"). In
retail, 0x164c48, which the game source calls as `__gedf2`, is word for word the reference
`__ltdf2`; 0x164bc0, called as `__ltdf2`, is the reference `__gedf2`. So at every call site
retail calls the other comparison, and the game source writes each comparison the other way
round. The two forms agree except when an operand is a NaN. The sites are generated in
`docs/UNTAGGED.md` (section 3):

| Call | Function | Source line | Retail calls |
|---|---|---|---|
| 0x091fe8 | 0x091e9c | `src/sound/DjDetect.cpp:1363` `if (a < 0)` | `__gedf2` body |
| 0x09200c | 0x091e9c | `src/sound/DjDetect.cpp:1365` `if (!(a >= 15.0))` | `__ltdf2` body |
| 0x06acc8 | 0x06ac38 | `src/system/SwgPlayer.cpp:7041` `if (d - fl >= D_1a4d68)` | `__ltdf2` body |
| 0x06a008 | 0x069f28 | `src/system/SwgPlayer.cpp:7156` `if (d >= 0.0)` | `__ltdf2` body |

`src/` is not changed; the rows stay refused.

`libsource.py --selftest` takes the admitted `_df_to_sf` unit. Changing one token
(`sffrac |= 1` to `sffrac |= 2`) or building with `-O1` for `-O2` each stops it from being
admitted. `validate.py` runs it as fault 9.

`libsyms.py --selftest` plants one call site of `free` pointing at `malloc`'s address. `free`
is then refused with 1 disagreeing site, and no other row changes. `libsyms.py --check`
rebuilds the CSV and compares it; `validate.py` runs both.

## hilo.py's join

`hilo.py` used to join paths on which `lui` last wrote a register. A loop that reloads the same
high half with a second `lui` therefore lost it: in 0x0d3b2c the back edge's delay slot repeats
`lui v1,0xa`, so the LO16 at word 12 (0x0d3b5c) was unrecovered. It now joins on the loaded
value (the same immediate and the same base segment). Its self-test checks 0x0d3b5c against
the proven pair at 0x0d3b38: the address join misses it, and the value join gives 0x254330. It
also checks that no target the address join recovered changes. Recovered LO16s go from 2,674
to 2,799 of 2,908, with none changed. (`docs/DENOMINATOR.md` still quotes 2,674.)

The last 109 had three shapes, each now handled by a rule with a known answer in the self-test:
- **Register copies.** `move s2,s1` (0x0010b8) and `move v1,s2` (0x0d37bc) carry a high half
  into another register; a write used to drop it. `move rd,rs` now gives rd exactly rs's value.
  Known answer: 0x001120 = 0x1b8bfc (the pair at 0x0010f8).
- **Landing pads.** The LO16 sat in exception landing-pad code, which was never analysed. A pad
  is entered only by the unwinder from a call whose return address minus one is in one of its
  LSDA call-site ranges, with the callee-saved registers s0–s8 as they were after that call's
  delay slot. A pad's state is the meet of those, s0–s8 only. Known answer: 0x005e6c =
  0x1dd6b0 (the pair at 0x005dcc).
- **Calls that never return.** A call to `_Unwind_Resume` was treated as falling through into
  the next landing pad, emptying its state (0x075224). By the GCC source, `_Unwind_Resume`
  ends in `abort()` or `__builtin_eh_return` and never returns. `hilo.py` finds it as the one
  retail function equal to the reference copy (0x166df8), without going through libsyms, which
  depends on `hilo.py`. Known answer: 0x0752cc = 0x1a6490 (the pair at 0x075268).

All 2,908 are now recovered. None of the 2,674 or 2,799 recovered before changed, and the
paired check now covers all 13,177 proven LO16s and agrees on each.

## sbs.py: the working diff

Prints the grader's verdict, then the frame size and saved-register set (retail and compiled),
then the earliest differing instruction, then an aligned listing. Default keys are exact after
masking relocated fields. `--blind` also masks the register fields named by each instruction's
operand letters (GPR, FPR, VFPU), so a line that differs only in register choice counts as
equal. The order of work is frame, then structure (`--blind`), then registers. One function
takes 0.15 to 0.7 s cached and about 2.2 s cold for the largest file.

## image.py: the M2 gate

Starts from the retail file, writes each EXACT `@implements` function's compiled bytes at its
address with every relocated field written from its resolved target (segment base subtracted,
as retail's relocations store them), and compares the whole file. Red on any differing byte,
any placed function that is not EXACT or whose size differs from `funcs.csv`, any overlap, or
fewer functions placed than `@implements` tags in real files (or none). `--files` limits it to
some real files (used to show faults against a green baseline); `--replace`, `--plant-drop` and
`--plant-force` exist only to plant faults.

Measured on the whole tree: 6.1 s cold (265 files compiled, 4.3 s of it compiling), 2.5 s
cached (0.6 s compile, 1.8 s grading).

## Hooks

`tools/hooks/install.py` sets `core.hooksPath` in the worktree's own config
(`git config --worktree`), so other worktrees and the main checkout are untouched; it refuses
if `extensions.worktreeConfig` is off, and `--uninstall` restores the previous value. It is
installed in the `claude/grader-c43391` worktree only.

- **pre-commit** grades what is staged, not the working tree: it writes the index's copy of
  `src/`, `include/` and any other staged source under `build/hook/stage/` and grades that.
  It refuses a staged source with an `@implements` that is not EXACT, a tag without WHAT IT
  DOES, a malformed tag, an address tagged twice outside `src/control/`, and AI-attribution
  text in any added line. Without `RRPSP_CC_HOST`/`RRPSP_CC_KEY` it refuses any commit that
  stages a tagged source.
- **commit-msg** refuses attribution trailers and credit lines in the message.

The attribution patterns are in `hookcheck.py`, written in pieces so the file does not match
itself.

## validate.py

Runs, with times: `reference` (six MD5s), `tags`, `attribution` (tracked files and this
branch's commit messages), `libsyms` (`libsyms.csv` is what `libsyms.py` builds now; it went red
once, rightly, when the `hilo.py` fix raised the site counts), `untagged` (`docs/UNTAGGED.md` is
what `tools/untagged.py` writes now), `compiler` (the 60 control functions: size, words and relocation
types equal, which is what pins the compiler; EXACT is printed beside it), `image`, `tiers`,
and `faults`. Red if any gate is red. From a fresh clone after `./setup.sh`: 26 s with no
compile cache, 12 s cached.

## Planted faults

Each fault is planted in a copy under `build/plant/` (or, for the hook, a temporary git index
through `GIT_INDEX_FILE`); `src/`, `config/` and the real index are never changed, and
`validate.py` checks that afterwards. Each is shown against a baseline that is green for the
same scope (the four files below: image GREEN, 23/23 EXACT). `validate.py` repeats all of them
on every run. Recorded from a fresh clone, 2026-11-17:

```
caught 1 global moved by 4 bytes (src/sequence/FadeColourState.c 0x0e9e08)
       score BADREF: word 0 R_MIPS_HI16: compiled D_1d5a80 (name) -> 0x1d5a84, retail -> 0x1d5a80
       | image RED: 7 functions placed, 8 @implements tags in the given files
       | forced into the image: 1 bytes differ from retail; first at file offset 0xe9e90
caught 2 string literal changed by one character (src/sound/RadioCommon.cpp 0x10abd0)
       score BADREF: word 16 R_MIPS_HI16: data object data .rodata+0x34 (.rodata+0x34, 68 bytes,
       retail 0x1b256c): byte +0x1f compiled 3f, retail 21
       | image RED: no function placed; 0 functions placed, 1 @implements tags in the given files
caught 3 float constant changed (src/race/SpeedUnit.c 0x06b714)
       score BADREF: word 5 R_MIPS_HI16: data object data .rodata.cst4+0x0 (.rodata.cst4+0x0,
       4 bytes, retail 0x1a51cc): byte +0x0 compiled 04, retail fc
       | image RED: 3 functions placed, 4 @implements tags in the given files
caught 4 same-shaped callees swapped (src/race/FadeSequence.cpp 0x0ff7f0)
       score BADREF: word 2 R_MIPS_26: compiled f_0e9eb4 (tag) -> 0x0e9eb4, retail -> 0x100bbc
       | image RED: 9 functions placed, 10 @implements tags in the given files
caught 5 stale object left in build/
       (a) good object at the output path: score BADREF, image RED
       (b) compile step leaves it: score MISSING: compile failed: object ... is older than
           this compile (stale)
caught 6 function removed from the placed set (0x0e9e08)
       image RED: 7 functions placed, 8 @implements tags in the given files
caught 7 pre-commit with a non-EXACT @implements staged (src/sequence/FadeColourState.c)
       exit 1: pre-commit: REFUSED
         src/sequence/FadeColourState.c:35: @implements 0x0e9e08 f_0e9e08 is BADREF: word 0
         R_MIPS_HI16: compiled D_1d5a80 (name) -> 0x1d5a84, retail -> 0x1d5a80
caught commit-msg with an attribution trailer: exit 1
(added later)
caught 10 untagged method renamed to the next function (src/sound/SoundPack.cpp 0x114a4c)
       score BADREF: word 4 R_MIPS_26: compiled _ZN9CPackFile8f_115834EPv (method-name)
       -> 0x115834, retail -> 0x115800 | image RED: 9 functions placed, 10 @implements ...
caught 11 one site of an untagged method points elsewhere (src/race/PlayerInputProxy.cpp)
       0x038604 BADREF: ... f_044c3c (method-name) -> 0x044c3c, retail -> 0x044a28
       | 0x037d6c BADREF: method-name rule: another site of _ZN5Codec8f_044c3cEi points at
         0x044a28, not its name address 0x044c3c | 0x0386a8 BADREF: (the same)
caught tags: missing WHAT IT DOES and an address tagged twice
faults GREEN 12.12 s 10/10 caught; src/ and config/ unchanged
```

Added later, with libsyms: fault 8, one call site of `free` pointed at `malloc`, is caught
by `libsyms.py --selftest` (free refused, 1 disagreeing site, no other row changed).

Fault 1 is `D_1d5a80 = 1` written as `(&D_1d5a80)[1] = 1`: the same instructions with the
target 4 bytes on. The forced placement puts the faulty function into the image with its
compiled targets, as a grader that missed the fault would, and shows the byte comparison
catching it on its own (the LO16 field differs). Fault 5 (a) puts the real file's good object
at the planted copy's output path, newer than the source; the gate recompiles and stays red.
(b) makes the compile step return without writing, which leaves that object in place an hour
old; the freshness check (the object must be written by this compile) refuses it.

### A real commit attempt

The same fault staged for a real `git commit` through a temporary index, with the hooks
installed in this worktree. Nothing was committed and HEAD did not move:

```
$ git diff --cached --stat
 src/sequence/FadeColourState.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
$ git commit -m "Move the fade flag store"
pre-commit: REFUSED
  src/sequence/FadeColourState.c:35: @implements 0x0e9e08 f_0e9e08 is BADREF: word 0 R_MIPS_HI16: compiled D_1d5a80 (name) -> 0x1d5a84, retail -> 0x1d5a80
exit 1
$ git commit --allow-empty -m (a message whose third line is a co-author trailer naming an AI tool)
commit-msg: REFUSED: attribution in the commit message
  line 3: co-author trailer naming an AI tool: ...
exit 1
```

With an unchanged function and only a comment added to the staged file, the pre-commit hook
passes in 1.1 s: `1 staged tagged source(s): every @implements EXACT, every tag explained, no
address tagged twice`.

## Not checked

- `.eh_frame` and `.gcc_except_table`: the unwind and exception tables are not compared, so
  wrong cleanup regions, landing pads or LSDA contents in C++ are not caught. This includes
  the open CarMatrix.c question in `docs/COMPILER.md`.
- `.pdr`, `.mdebug`, `.reginfo`, `.comment`, and `.ctors`/`.dtors` entries.
- The contents of data that no function refers to, and data reached only through a name
  (`D_XXXXXX`): its address is checked, not its bytes.
- The bytes of data defined only in a file that is not a real translation unit.
- `.bss` items: only that the target lies in retail `.bss` (they have no contents).
- The PRX's own relocation table and section headers. The image gate writes function bytes
  only, so the file comparison covers code.
- The compile cache in `build/cc-cache/` is trusted. `cc.py` keys it by compiler, flags, source
  and header bytes, but an entry edited by hand would be served. `--no-cache` recompiles
  everything.
- Behaviour (T3). No oracle exists.

## Open questions (not settled by analysis)

- **References that no tool output resolves.** The swapped `__gedf2`/`__ltdf2` calls, C++ methods
  that no tag claims (`docs/UNTAGGED.md`), and LO16s whose high half `hilo.py` still does not
  recover. Each makes its function BADREF, so the image gate is red. `score.py --tree` lists
  them with the first failing reference.
- **What is left after these rules is all source structure** (listed by `image.py --list`):
  the swapped `__gedf2`/`__ltdf2` comparisons; the class hierarchy that RTTI shows (retail
  `Car::CRidgeCar : Car::CCarBufferPSP`, `RRP::CRidgeComcar : Car::CRidgeCar` only,
  `RRP::CRidgeNetcar : RRP::CRidgeComcar`, `RRP::CRidgeMycar : Car::CRidgeCar`); `CCamTV`
  methods that should override `CCamProto`'s slots 6–9; `Select::CBaseMenu`'s base-object
  constructor, which is retail 0x06c540, written in MenuMovie.cpp as `f_06c540`; the
  `Select::CStartMenu::CSub` vtable (retail 0x1a62b0), which no file emits because its key
  function `CSub::s2` has no body; and CarManager.cpp's stand-in base classes `f_0e69a0` and
  `f_0e69c8`, whose constructor and destructor calls retail makes to `CDispName`'s tagged C1
  and D1 (0x0e69a0, 0x0e69c8). Each needs a change under `src/`.
- **The `_ge_df`/`_lt_df` frame.** Why the reference objects have a 112-byte frame where stock
  1.3.1 gives 96 with the makefile flags is not known.
- **Whether rules 4 and 6 (libfuncs.csv symbols, import NIDs) are accepted** as proof of a
  target.
