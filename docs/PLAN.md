# Ridge Racer (PSP): matching decompilation plan

Target: **M1** (every game function is T3 or T4) and then **M2** (every game
function is T4, and the rebuilt `BOOT.BIN` is byte-identical to retail).

The tiers are the same as in Boss Rally / Top Gear Rally:

| Tier | Meaning |
|---|---|
| T1 | Draft only. |
| T2 | In the tree, not done. |
| T3 | Certified complete and functionally exact: the same inputs produce the same outputs, proven by the oracle. Not byte-exact. |
| T4 | Bytes diff clean, and every relocation resolves to the same target. |

There is nothing between T3 and T4. EXCLUDED means game code that provably
never runs, with the proof in the file. FENCED means SDK or library code, which
is removed from the denominator only once it has been identified.

---

## 1. What the binary gives us (measured 2026-10-12)

### Reference executable

Every region ships an **unencrypted `PSP_GAME/SYSDIR/BOOT.BIN`**, which is a
plain ELF. No key work is needed to start.

| Region | Disc ID | BOOT.BIN MD5 | .text size |
|---|---|---|---|
| USA | ULUS-10001 | `e87ea7c17004cd13945664152608140c` | 0x16e3bc |
| EUR | UCES-00002 | `4eaa1ff90e56f5ff1521e4e59597e9f2` | 0x16e3bc |
| JPN | ULJS-00001 (*Ridge Racers*) | `524c500adbe299a546e03ad40ada5a56` | 0x16d810 |

- **EUR differs from USA by 5 bytes.** One is in `.text` at +0x10bd68 and four are in `.data` at +0x1ecd9, near the `ULUS10001` product string.
- **JPN is a separate, earlier build.** Its sizes differ, and it has eight objects from the SDK 1.4.0 toolchain.
- **Reference: USA `BOOT.BIN`** (confirmed by Jeff 2026-10-12).
  - EUR becomes a build variant at almost no cost.
  - JPN plays the role the N64 build played for Boss Rally: useful, never authoritative.

### Toolchain

The toolchain is named in `.comment`. There are 493 ident strings, one per
linked object, in link order:

- 488 × `GCC: (GNU) 3.3.3+allegrex-2.2.1-psp-1.5.1`
- 5 × `GCC: (GNU) 3.3.3+allegrex-2.2.1-psp-1.5.1.internal`, most likely SDK or CRT objects.

This is SCE's own GCC, which matters for two reasons:

- GCC is deterministic, and it can dump every pass (`-da`). That is the diagnostic Boss Rally had to build `c2read` and an instrumented uopt to get.
- `.sbss` is empty, which points to `-G0`. That still has to be confirmed by the control set.

### Module format

The module is a relocatable PRX (`e_type` 0xFFA0) that **keeps its full
relocation tables**:

- `.rel.text`: 61,577 entries.
- `.rel.rodata`, `.rel.data`, `.rel.eh_frame`, `.rel.ctors` and others.

**Every code and data reference in the binary is known exactly.** That removes
whole bug classes Boss Rally fought: guessed %hi/%lo pairs, reference-filled
slots hiding wrong targets, jump tables mistaken for code, and `DAT_` symbols
that were really literals.

### Structure

- **C++ with RTTI and exceptions.** `.eh_frame` (150 KB) holds 262 CIEs and 3,977 FDEs. `.gcc_except_table` is 25 KB.
- FDEs give exact extents for every function that has unwind info.
- CIEs probably mark object-file boundaries. That has to be verified before anything depends on it.
- 154 mangled typeinfo names give the namespace and class skeleton for free, for example:
  - `Fj::C2DAnalogMeter` and about 30 other HUD classes
  - `An::CSwgRenderer`
  - `Car::CCarBufferPSP`
  - `Controller::CCustomController`
  - `DB::CDataBase`
  - `Is::CHuffman`
  - `Ng::CJob`
  - `RRBios::TextureManager`
- Vtables in `.data`, combined with their relocations, map methods to classes.
- `.ctors` has 74 entries and `.dtors` has 48, which identify the TUs that have static initializers.

### Size

| Section | Size |
|---|---|
| `.text` | 1.50 MB |
| `.rodata` | 121 KB |
| `.data` | 131 KB |
| `.bss` | 760 KB |

There are about 7,800 `jr ra` instructions, so roughly 7 to 8k functions. That is
far larger than Top Gear Rally's 572. The denominator will be fixed in Phase 0
and quoted with every percentage.

### Statically linked SCE libraries

The FENCED lane covers the statically linked SCE libraries: libc, libm, libgu
and libgum, sas, the module stubs (`.sceStub.text`) and the CRT. Its first job
is to identify them.

---

## 2. Lessons carried over from Boss Rally and Top Gear Rally

Each lesson is listed with the rule it becomes here. These go into `docs/RULES.md`
on day one, and wherever possible they are **enforced by a hook or a gate, not
by prose**, because "a rule nothing checks is a preference."

### Reference and toolchain

1. **Rule 0: the reference is checked, not remembered.** Boss Rally used the wrong binary twice. `tools/refcheck.py` runs at the start of every session and refuses to run on the wrong MD5. `setup.sh` extracts the binary from Jeff's ISOs, and nothing from retail is tracked.
2. **Prove that `BOOT.BIN` is what actually runs.** The `EBOOT.BIN` is the signed `~PSP` container. Decrypt it once with an open-source PRX decrypter and confirm its payload equals `BOOT.BIN` before `BOOT.BIN` becomes the reference. If they differ, `EBOOT` is the reference.
3. **Identify the compiler on a control set, never on a hard function.**
   - decomp.me's `decompme/compilers` release has `psp-gcc` **1.3.1** (allegrex-2.2.1) and **1.7.1** (allegrex-2.2.2), which bracket the build's 1.5.1. Neither is the exact version.
   - Score about 60 mixed functions under both, including SDK library functions whose behaviour is known. If 1.3.1 matches the whole control set, the allegrex-2.2.1 code generator is the same one, and the `.comment` ident is supplied via `.ident`/`-fno-ident`.
   - Recall that "a WRONG compiler gives the prettiest region count."
4. **The toolchain is self-contained.** It is staged in-repo under `tools/toolchains/`, pinned by sha256, and never installed on the host. It must run on Apple Silicon. If only Linux or Windows binaries exist, use pinned Wine or a pinned container for those binaries only.
5. **The gate builds what it grades.** Delete the `.o` before every compile, never grade stale objects, and measure nothing while a sweep or refile is running.

### Build and gates

6. **Day-one round trip.** Before any C exists, the all-assembly build must reproduce `BOOT.BIN` byte-for-byte. That covers every section, the relocation tables, `.eh_frame` and `.comment`. Every later match is then incremental against a green image.
7. **Image gate (M2).** `tools/image_build.py` compares the rebuilt `BOOT.BIN` to the reference and must show 0 differing bytes. Here the relocation tables are part of the file, so "relocations resolve the same" is checked by the same diff. It has three exits:
   - 0: OK.
   - 1: FAILED or INCONCLUSIVE.
   - 2: sources changed during the run.
8. **Shiftable build (M1).** Because every reference is relocated, a non-matching build can be **relinked** with functions at different sizes. No annex or jump-thunk scheme is needed. Prove shiftability early:
   - Insert padding between every TU.
   - Run the oracle, and require the run to be identical.
   - Any failure means a reference the tables do not cover, and it is found now rather than at M1.
9. **Explicit manifest, no inference.** Each function carries `/* @implements 0xADDR us Name */`, and `tools/manifest.py` is the only answer to "is this ported?" `isported.py` was wrong seven different ways.
   - One address with two tags is a duplicate.
   - Untagged ports are a defect; Boss Rally had about 259 of them, and they were free matches.
10. **Validate a detector before acting on it.** "A detector you have not validated is not evidence, and it fails toward 'missing'." Every audit tool is checked against a known answer before any worker is dispatched on its output. Audits are twin-aware: always search both the US and JP addresses.

### Correctness and evidence

11. **T3 is proven by a differential oracle, never by reading.** This is the largest PSP-specific piece of work; see Phase 1.
    - Boss Rally's synthetic-seed oracle certified a function that swapped its arguments, so every T3 had to be reset.
    - Whole-image A7 found about 25 real bugs that per-function A5 had certified. "A7 is never superseded."
12. **Measure coverage per instruction.**
    - An unreached function is UNCOVERED, not passed.
    - Force unexecuted branches from real state.
    - Use asymmetric data, because equal x/y/z values hide component swaps.
    - Every oracle run has a negative control with a planted bug.
13. **A test that cannot fail is worse than no test.** Mutation-test every assertion: reinstate the bug, confirm the test fails, restore, and report the result.
14. **Golden values come from an independent source.** That means the emulator running retail, never values read off the same disassembly that produced the C.
15. **A frontier is not a placeholder.** Unported callees are counted, do-nothing frontiers. A stand-in that returns a plausible value "is a lie with a counter on it." Accuracy comes first, and playability is a consequence, never the target.
16. **State the denominator before any percentage.** "Ported" is a ceiling on code transcribed, never a floor on code correct. The README never carries hand-typed numbers; it says to query the tree.
17. **A deviation's stated reason is itself a claim.**
    - No file-wide waivers. This matters for VFPU and FPU rounding: Boss Rally's "unavoidable x87" waiver hid 24 wrong comparisons.
    - A claim that the original is wrong needs the instruction addresses that prove it.
18. **Float literals are read from the binary**, using `litcheck.py`. Spellings that differ by one or two ulp are invisible to a relocation-blind grader.
19. **Return types are behaviour.** A `void` that drops a `$v0` the caller tests is a bug, even when the bytes nearly match.
20. **Never lower a gate to hit a number.** Walls are dated verdicts: re-triage parked functions whenever a new lever class is found.

### Matching method

21. **Hand transcription only.** The hard rule from 2026-10-05 carries over unchanged: no permuter, no flag sweeps and no variant batches. Boss Rally's record was permuter 0/95, refine 0/258 and crank 4/536, while a single stack-slot census broke a 12-session wall.
    - The flags are identified once, on the control set.
    - Per-file overrides are allowed only with evidence.
22. **Diagnose, don't hypothesize.** For GCC, the diagnostic is free:
    - `-da` RTL dumps show which pass made the divergent choice, such as combine, sched, local-alloc or global-alloc, and reload.
    - Build a GCC version of the IDO-HANDBOOK symptom table (`docs/decomp/GCC33-HANDBOOK.md`) as the project goes.
23. **Infer the source from the bytes; never permute spellings.**
24. **Order of work is frame, then structure (register-blind), then allocation.** For residue, name the compiler pass responsible before touching the code.
25. **TU fidelity from day one.**
    - Every match is filed into its real translation unit, using TU boundaries recovered from the CIEs, the `.comment` order, `.ctors` and data and literal placement.
    - There are no address-slice files; that rule is enforced by a pre-commit hook. Boss Rally stranded 570 functions in slices.
    - Refiles are byte-identity-checked, because neighbours change code generation.
26. **Library code is matched from its own source** when the source exists (as zlib 1.0.4 was for Top Gear Rally). Check for zlib, the Mersenne Twister and Huffman code. Otherwise it is FENCED.
27. **Naming.**
    - Grep the address before naming anything.
    - Use `g_<hex>` until a role is proven.
    - Every function gets a plain-English `WHAT IT DOES:` paragraph, enforced by a hook.
    - The RTTI and vtable skeleton seeds class and method names.

### Process and parallel sessions

28. **Lock before you target.** `tools/claim.py` takes fcntl-locked claims that go stale after 90 minutes. Parallel work splits by `.c` file only, and header edits are serialized.
29. **Commit after every edit that survives a compile.**
    - Partial-stage with `git apply --cached`, because `git commit -- path` takes other sessions' hunks.
    - Grep for your own text after committing.
    - Never rewrite shared CSVs wholesale.
    - Workers killed by usage limits lost everything they had not committed.
30. **Only one A7 run at a time.** Fan-out is good for running a diagnostic across many sites and bad at inventing levers.
31. **No attribution, ever.** A `provcheck` pre-commit hook enforces it, alongside `WHAT IT DOES`, the slice ban and the manifest ratchet.

---

## 3. Phases

### Phase 0: foundation

The exit criterion is a green round-trip image with a fixed denominator.

1. **Repo skeleton.**
   - `setup.sh`, which extracts each region from the user-supplied ISO and checks its MD5.
   - `refcheck.py` and the RULES hub.
   - Hooks: provcheck, WHAT-IT-DOES, slice ban, and manifest ratchet.
   - Port the shared tooling from brally `tools/common/` rather than rewriting it.
2. **EBOOT equals BOOT check** (lesson 2).
3. **ELF and PRX tooling.**
   - Parse sections, `.rel.*` (including the SCE relocation types), `.eh_frame` and `.gcc_except_table`, `sceModuleInfo`, and the stub and NID tables.
   - Disassemble with an Allegrex-aware disassembler that covers VFPU, `ext`/`ins`, `min`/`max`, `clz`, `seb`/`seh` and `wsbh`. Use rabbitizer, whose Allegrex support must be verified on known VFPU sequences first.
4. **Function map.**
   - Use the union of FDE extents, relocation targets of `R_MIPS_26` and `HI16`/`LO16` pairs into `.text`, and recursive descent.
   - Relocated `.rodata` words pointing into `.text` are jump tables, never entries.
   - Reconcile against the `jr ra` census.
   - Fix the denominator, and split it into game, FENCED and unknown.
5. **TU map.**
   - Test the hypothesis that each CIE marks one object, and cross-check it against `.comment` (493 idents) and `.ctors`.
   - Record `config/tu_map.csv` with its evidence column.
6. **Toolchain (lesson 3).** This needs Jeff's approval to download.
   - Stage `psp-gcc` 1.3.1 and 1.7.1, and the binutils that ship with them.
   - Run the control set, and fix the flags (`-O?`, `-G0`, `-fexceptions`, `-mno-explicit-relocs`?).
   - Write the result up in `docs/decomp/toolchain/compiler-id.md`.
7. **Round-trip build.** Build asm per TU, link with a linker script that reproduces the section layout, and run an SCE-format relocation emitter. The result must be byte-identical `BOOT.BIN`.
8. **Symbol seed.**
   - RTTI, typeinfo and vtables give classes and methods.
   - Strings give functions such as `GhostLoad`, `ReplayLoad` and `PSPInit`.
   - The stub NIDs give SDK imports, using the public NID databases.
   - Library signatures identify the FENCED code.

### Phase 1: the T3 oracle ("rrbox")

The exit criterion is that the oracle catches every planted bug in a
negative-control suite.

Unicorn has no Allegrex or VFPU support, so the box is **PPSSPP headless built
in-repo**, pinned, with a deterministic virtual clock. It needs:

- HLE syscalls recorded and replayed. This is the counterpart of Boss Rally's import and OS replay.
- Any unmodelled hardware access stops the run, by name.
- **A5**: snapshot at real call sites, run retail, restore, run the candidate, and compare RAM, `$sp`, callee-saved registers, FPU and VFPU state, and return registers.
- **A7**: the shiftable image runs every input script frame by frame against retail, comparing GE display lists, audio buffers and all of RAM.
- Input scripts are goal-driven: menus, every course and mode, replays, ghost save and load, and ad-hoc multiplayer as far as the box can model it.
- Per-instruction coverage is reported.
- Stale-stack detection by register perturbation.

The emulator's accuracy matters less than its determinism, because retail and
candidate run on the same box. Divergences in VFPU rounding are still checked
against known hardware results before any T3 depends on them.

### Phase 2: matching (T2 to T4)

- There are two lanes: C++ game code, and C or library code. A FENCED lane identifies the SDK libraries.
- Start with leaf functions and the hand-picked control set to build the GCC 3.3 handbook. Then work TU by TU in link order, so files fill up whole.
- Per-function grader: compile, extract the function by symbol, and compare bytes plus the relocation rows (type, offset and target symbol), masking nothing.
- Tooling is `fn.py` (cycle under 2 s), `firstdiff`, register-blind `msetdiff` and `sbs`.

### Phase 3: M1

- Every game function is T3 or T4 in the shiftable image.
- A7 is green on the full script set, and per-instruction coverage is reported with its gaps.

### Phase 4: M2

- Every game function is T4, the FENCED code is resolved, and the whole `BOOT.BIN` is byte-identical.
- EUR is then built as a variant; its 5-byte delta comes from a define.
- JPN follows as a second build if wanted.

---

## 4. Risks and open decisions

| Risk or decision | Plan |
|---|---|
| The exact `psp-1.5.1` compiler is not public. pspdev's homebrew toolchain is not a candidate: its GitHub history runs from GCC 4.3.2 (2010) to 15.2.0, with a different Allegrex port and code generator (checked 2026-10-12). | Bracket it with 1.3.1 and 1.7.1 on the control set. If neither matches 100%, that is the first blocker to raise. |
| CIE-per-TU is a hypothesis. | Verify it against `.comment`, `.ctors` and literal placement before relying on it. |
| PPSSPP HLE fidelity for A7. | Determinism is what matters, and retail and candidate share the box. Unmodelled behaviour stops the run, never passes it. |
| GCC 3.3 C++ (EH tables, vtable and thunk emission, template instantiation order) must also match byte-for-byte. | `.eh_frame` and `.gcc_except_table` are in the image gate from day one. |
| Scale: about 13× Top Gear Rally. | Multi-session lanes from Phase 2, with locks, per-file splits and commit-per-compile. |

**Status 2026-10-12 (end of day):**

Compiler:
- **Control set: 47 of 61 hand-transcribed retail functions are byte-exact** with `psp-gcc-1.3.1-nocmov` at `-O2 -G0`. Batch 5 was still being worked when this was counted.
- psp-gcc 1.3.1 and 1.7.1 are indistinguishable on the control set and on a 120-file corpus.
- Retail differs from both in one proven way: it has no conditional moves at all. `tools/toolchains/mk_nocmov.py` reproduces that by patching 1.3.1. The f_0877a8 select matches only under the variant, and nothing regressed.
- Per-TU flags differ. Two functions need `-fno-schedule-insns2` and `-frename-registers` respectively.
- C++ TUs need `cc1plus -fexceptions`.
- Newlib is statically linked.
- All findings are in `docs/decomp/GCC33-HANDBOOK.md`.

Tooling:
- `setup.sh` extracts the executables.
- `tools/analysis/prx.py` decodes SCE relocations.
- `tools/analysis/funcmap.py` builds the function map: 7,237 functions, 98.5% of `.text`. It needs a prologue split (2 merged pairs found).
- `tools/rrdis.py` gives annotated listings, and `tools/score.py` is the per-function grader.
- The psp-gcc tarballs run in a Lima VM.
- ghidra-allegrex is installed.

**Needs Jeff:**

1. Later approvals will cover PPSSPP source, rabbitizer and an open-source PRX decrypter.
2. Whether you already hold the exact `3.3.3+allegrex-2.2.1-psp-1.5.1` toolchain. If so, it replaces the bracket test.
