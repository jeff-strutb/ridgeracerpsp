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
once, rightly, when the `hilo.py` fix raised the site counts), `compiler` (the 60 control functions: size, words and relocation
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

- **References that no tool output resolves.** Library symbols that `libsyms.py` refuses (the
  typeinfo vtables, `__truncdfsf2`, the swapped `__gedf2`/`__ltdf2`), C++ methods that no tag
  claims, and LO16s whose high half `hilo.py` still does not recover. Each makes its function
  BADREF, so the image gate is red. `score.py --tree` lists them with the first failing
  reference.
- **Whether the store-flag substitutes for a conditional move are accepted** as "closely
  matches" (they decide `__truncdfsf2` and both typeinfo vtables).
- **Whether rules 4 and 6 (libfuncs.csv symbols, import NIDs) are accepted** as proof of a
  target.
