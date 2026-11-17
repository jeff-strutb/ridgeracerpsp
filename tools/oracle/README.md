# rrbox: the behaviour oracle

`rrbox` is PPSSPP v1.20.4's headless runner with `ppsspp-rrbox.patch` applied. `build.sh` clones the pinned source into `build/ext/`, applies the patch and builds it.

The oracle runs the original game, or a candidate built from this tree, and records what it does every frame.

## Determinism

Two runs of the same executable and script must be identical. Measured 2026-10-12: ten one-minute runs of retail had identical traces, and all 3,600 frame hashes were distinct, so the game state really changes. Measured again 2026-10-13 after the I/O drain: 16 runs started together on a fully loaded host had identical traces.

What it takes:

| Setting | Why |
|---|---|
| `-i`, the pure interpreter | The JIT patches its own block markers (opcode `0x68…`) into emulated RAM, and their numbering differs between runs. |
| `RRBOX_EPOCH` and `TZ=UTC` | They fix both wall-clock sources: the kernel start time and the RTC base. |
| 32 MB launch hardware | The headless default is a Slim with 64 MB, and the memory size changes the game's heap. |
| Wi-Fi off | Removes network-dependent behaviour. |
| SAS mixing on the emulation thread; `IOTIMING_FAST` | Emulated time, not host time, decides when sound is mixed and when I/O completes. |
| The host I/O thread is drained at every frame end | Every file read by a PSP thread is copied into emulated RAM on PPSSPP's I/O thread, while the reading PSP thread waits `size/100` µs of emulated time and other threads, and frames, run on. Ridge Racer's 311 KB read of `RRP.DAT` at tick 25,693,114 spans the frame 6 boundary. On an idle host the copy finished before the frame's RAM hash; on a loaded or cold host it did not, and frames 6, 41, 47 and 4,782 to 4,808 hashed differently (6 of 16 runs under load). rrbox now waits for the I/O thread before hashing, shooting, dumping or snapshotting a frame. Emulated state is untouched: with a 40 ms delay forced on every host read, traces match a normal run on every frame, and 16 runs under load all agree. |
| An empty memory stick inside the repo for every run (`RRBOX_MEMSTICK`) | PPSSPP's default memory stick is the host's `~/.ppsspp`, which the oracle must never touch, and a save left over from an earlier run would change the game's path. |

## Booting a candidate

The executable boots from a host file with the retail disc mounted (`-m`). Three traps:

- **The extension.** PPSSPP treats a `.BIN` as a raw disc image and then boots nothing, so executables are staged as `.elf`.
- **The path.** The launch path is written into emulated RAM, so retail and candidate are staged at the same path, one run after the other.
- **Parallel runs.** Runs in parallel need separate memory sticks. Each run clears its own at start, so a shared one corrupts the others.

The module loads at `0x08804000`; `.text` occupies RAM `0x08804040` to `0x089723fc`.

## A7: whole image (`tools/oracle/a7.py`)

For each script in `scripts/`, retail and the candidate each record per frame the emulated cycle count and an XXH3 hash of all 24 MB of user RAM. Every frame must agree.

- `--m1` leaves `.text` out of the hash, for images whose T3 bodies differ in bytes. All data must still match.
- **Teeth:**
  - Retail's power-callback id stored 4 bytes off is caught at frame 0.
  - Retail's main-thread priority changed from 111 to 110 is NOT caught in 30 s of attract mode. A7 sees only behaviour the scripts exercise, so coverage is the limit.

## Scripts

| Script | Frames | What it covers |
|---|---|---|
| `boot_attract` | 1,800 | Boot, the Namco logo, the Rally-X loading game's attract mode. |
| `fault_loader_*` | 300 each | Forced failures of `sceIoOpen`, `sceKernelLoadModuleByID` and `sceKernelStartModule`, which cover every path of the module loader. |
| `race_seaside_start` | 9,000 | The new-game path from an empty memory stick to a race: Rally-X; the intro; the title; creating a driver profile (the system keyboard, where START accepts the default name); saving (system dialogs confirm with CIRCLE); the World Tours intro; World Tours, Basic Tour, Class 1, Seaside Route 765; car and transmission select; loading; the fly-by. GO comes at frame 5,880, followed by about 50 s holding accelerate with no steering. The first version was derived while a save sat in `~/.ppsspp`, and with an empty memory stick it stalled at a menu. It was re-derived. |

`--rr-peek=FILE` appends the listed memory words to every trace line, for studying game state.

`--rr-drive=START:OUT` (with `--rr-drive-params=STEP:HORIZON`, default 20:80) drives the race by search from frame START. Every STEP frames rrbox snapshots the machine in memory, plays each of five options out to HORIZON frames (accelerate straight, or steer left or right for STEP frames and then straight or keep steering), and keeps the one whose car (0x08a4d3b0, x y z) gets furthest along its direction of travel over the last six decisions (about two seconds). Wall hits and spins cost distance, and turning round scores negative: with plain straight-line distance a spun car drove the course backwards. The chosen inputs are appended to OUT as ordinary script lines, so a race driven once becomes a plain script that every later run replays without search. With `--rr-drive-path=FILE` (lines of `x z`, a closed loop such as an earlier lap of the same car taken from a trace), progress is instead arc length along that path: the car's place on it is the nearest point of a segment from 60 units behind to 150 ahead of its place at the last decision. Measuring along the car's own recent direction fails after a spin: on lap 3 of Seaside the car stalled on a wall, turned round, and the driver then rewarded driving the course backwards. Two details matter for the replay to match: the live button state is not part of a savestate, so it is put back by hand after every restore; and the trace, frame dumps and the stop frame ignore the rollouts. A restore leaves one sound buffer (0x08d5bd80 to 0x08d5d5b8) different from a straight run, which never reaches game state; the replayed script, not the search run, is the reference.

`tools/oracle/explore.sh SCRIPT FRAMES EVERY OUTDIR [FIRST]` saves the emulated PSP's displayed frame every N frames and tiles them into a sheet (`sheet.py`). This is how scripts are written. These are the emulator's own output frames, never a capture of the host's screen.

A script file holds one entry per line:

```
FRAME BUTTONS
```

- The buttons are held from that frame on.
- `BUTTONS` is `NONE`, or names joined by `+` (`CROSS`, `CIRCLE`, `SQUARE`, `TRIANGLE`, `START`, `SELECT`, `UP`, `DOWN`, `LEFT`, `RIGHT`, `L`, `R`), or a hex mask.
- A `# frames N` line sets the run length.

## A5: per function (`tools/oracle/a5.py`)

Run `tools/oracle/m1image.py` first. It builds `build/image/BOOT.M1.BIN`: the M2 image with every `@draft` body that fits written into its own slot. Its addresses are pre-resolved for the oracle's fixed load base, and retail's relocation entries in that range are set to `R_MIPS_NONE`, so nothing else moves.

A5 then runs retail and the M1 image on every script, watching every tagged function (`Core/RRBox.cpp` in the patch).

**At entry,** it logs:

- the call number and thread;
- `a0` to `a3`, `t0` and `t1`;
- `f12` to `f15`.

**At return,** it logs:

- `v0`, `v1` and `f0`;
- the count of memory writes the call made outside its own stack frames (callees included, on its own thread only), and a hash of their net effect: each written byte adds H(addr, new) − H(addr, old), so the sum is over the bytes the call changed and does not depend on store order. The count is logged but not compared;
- which of `s0` to `s8` came back changed;
- the cycles the call took.

**Verdicts.** For each function, every call must agree with retail on:

- the entry record;
- the return registers its declared type uses;
- the writes;
- clobbering no callee-saved register.

Otherwise the function DIFFERS. A function no script reaches is UNCOVERED.

**Coverage.** Instruction coverage is measured on the candidate body, as the union over scripts.

**The ledger.** Verdicts go to `config/us/t3_live.csv` with each source file's hash.

**Time-equalised lockstep.** A T3 body takes a different number of cycles, and game code that reads the clock then stores different values (A7 drifted from frame 6 without this). So the candidate run reads retail's call log, and rrbox sets emulated time to retail's at every watched return. An interrupt that lands inside a T3 body at a different point still shows up as a difference.

**What counts as behaviour** (2026-11-02; each rule removed a false difference that stopped isolation):

- Writes are hashed by their net effect (H(addr, new) − H(addr, old) per byte), so store order and repeated stores do not count; the write count is logged, not compared.
- Writes into the running thread's stack below a call's entry sp (its own frames) are left out; writes above it (a caller's locals reached through a pointer) count by the value written and its position in the word, not by address or old contents, since frame layouts differ.
- Arguments that point into the running thread's stack are logged as `stk`; only the registers a function's declared parameters occupy are compared (`a5.arg_keys`; every field when the signature cannot be read).
- Emulated time is set to retail's at every watched entry as well as every return (`tk=` in entry records, never compared).
- `isolate.py` compares the logs thread by thread and ignores call numbers, so a moved thread switch is not a difference. When retail code (exact, or a draft left out) differs on equal arguments, it blames the innermost placed draft still open around it.
- A7 on an M1 image leaves out every thread's stack as well as `.text`.
- Every tag is watched (`a5.watched`): a regex that paired tags with definitions had let 1,826 of 5,419 tags, 158 of them placed drafts, run unwatched.

`tools/oracle/statediff.py SCRIPT FUNC CALL` dumps RAM at a call's entry in both runs (`RRBOX_DUMPAT`), diffs it outside code and stacks, and logs every write to the first differing byte (`RRBOX_WADDR`).

**State, 2026-11-02:** with 11 drafts excluded (`build/oracle/m1_exclude.txt`), A7 is identical on six of seven scripts and `fault_loader_open`'s call logs agree to the end. `race_seaside_start` diverges at frame 407: f_017e40 (a draft not placed) copies a `ResultMenuData` whose source holds different code and heap addresses, not yet traced.

**Stopped at divergence (2026-11-02).** A5 stops the candidate at the first frame whose RAM hash differs from retail's; every call after it runs on different state. The diverging race script had been logging to its 21 GB cap and took most of the gate's time (gate 689 s, now 248 s). The race divergence comes from f_007d80 (exact) handing partly filled stack locals to the screen manager, which copies them into the menu data that retail code reads back: any placed draft that changes stack contents beneath it diverges the run. f_064f10 and f_04ed28 are excluded for that; the Options copy (f_01808c) still differs.

**Teeth.** Two bugs were planted in the module loader's draft, and both were caught at its first call, by A5 and by A7:

- returning the module id + 1;
- swapping the `sprintf` arguments.

## Snapshot start (`tools/oracle/snap.py`)

A function is tested from a saved point just before it first runs, not by replaying from power-on. Replaying means every draft on the way (intro, menus, profile) must already behave exactly as retail does; the race run first called the course loader at frame 4,825 and the track geometry at 5,369, and through 2026-11-17 it still diverged at frame 2,137 for unrelated drafts.

- `snap.py make SCRIPT` plays retail once with `--rr-save-at`: every 250 frames rrbox writes the whole machine (`frame_N.state`, 40 MB), the held buttons (`.meta`) and the memory stick folder (`.memstick/`, a host folder outside the savestate). The same run indexes the frame each watched function is first entered in (`index.json`). Race: 35 snapshots, 2,458 functions, 2 min 16 s, 1.4 GB.
- `snap.py test ADDR...` picks the last snapshot before ADDR's first call and runs retail and the candidate from it (`--rr-start`: loaded at the end of the first frame, frame counter and buttons restored). The candidate is retail with **only ADDR's code replaced** (`--rr-patch`), so a difference is that function's; `--whole` patches every placed draft, as the M1 image does. The patch is every `.text` word where the loaded M1 image differs from loaded retail (a one-frame RAM dump of each; outside `.text` they must agree). Default window: 120 frames past the first call. Comparison is A5's (calls, writes, returns, clobbers) and A7's (RAM per frame, code and stacks left out), with time held equal at every watched boundary. About 15 to 30 s per function.
- `snap.py check SCRIPT FRAME`: retail from the snapshot twice, and the candidate with an empty patch, must agree on every frame and call. 2026-11-17 at frame 4750: both identical over 120 frames, 1,235 functions called.

Both sides start from one machine state, so the result does not depend on how faithfully a loaded snapshot reproduces a straight run, only on determinism. Two details matter:

- The cycle reference (`--rr-cycles-ref`) is loaded after the snapshot. Loaded at startup, retail's per-call timings (numbered from the snapshot) were applied to the boot's own calls, moved the CPU clock before the load, and the empty-patch run diverged at once.
- Call numbers, open calls, coverage and the call log restart at the load (`RRBox::Reset`).

**Teeth:** one planted instruction (f_093bc8 passing 0 instead of its second argument to f_093e64) was caught: f_093e64's entries and f_093bc8's return differ, RAM from frame 4828.

**First results (2026-11-17):** f_0b2f18 (track geometry, 14,288 B) PASS, 9,313 calls from frame 5,250 to the script's end, RAM identical, 1,797/3,572 instructions covered. CMapEnv::Load (0x0d8270) differed: its light keys read row 0 for every key (the `RDX` row argument where `RDX2` passes `i`); fixed, now PASS (1 call, 1,700/1,859 covered). Printf (0x00d354) is reported beside it only because its tag has no definition, so its never-set v0/v1 are compared.

## Fault injection

A script line `force NAME N VALUE` makes the Nth call (0-based) of system function NAME return VALUE (hex) instead of its real result. The function still runs and has its side effects, just as a real failure would. Both retail and the candidate get the same forcing, so error paths that normal play never takes run and are compared.

The `fault_loader_*` scripts drive every path of the module loader: failed open, failed load, failed start, a module id of 0, and a file handle of 0. That took it from 56/72 to 72/72 instructions covered.

## Tiers from the ledger

A `@draft` is **T3** when its `config/us/t3_live.csv` row says PASS with full coverage and the source hash still matches (`tools/progress.py`). The module loader (0x0004a4) is the first: 91 calls over seven scripts, all 72 instructions executed, and A7 identical on every script.

## Not built yet

- Snapshot verdicts in the ledger: `snap.py test` prints them; `config/us/t3_live.csv` is still written only by A5.
- Snapshots for the other scripts, and scripts that reach the rest of the track geometry's paths.

- Driving the power-resume and shutdown paths, which still show as uncovered.
- Display-list and audio comparison.
- Scripts that finish laps and reach the other modes.
- Per-instruction coverage.
