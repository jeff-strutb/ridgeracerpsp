# rrbox: the behaviour oracle

`rrbox` is PPSSPP v1.20.4's headless runner with `ppsspp-rrbox.patch` applied. `build.sh` clones the pinned source into `build/ext/`, applies the patch and builds it.

The oracle runs the original game, or a candidate built from this tree, and records what it does every frame.

## Determinism

Two runs of the same executable and script must be identical. Measured 2026-10-12: ten one-minute runs of retail had identical traces, and all 3,600 frame hashes were distinct, so the game state really changes.

What it takes:

| Setting | Why |
|---|---|
| `-i`, the pure interpreter | The JIT patches its own block markers (opcode `0x68…`) into emulated RAM, and their numbering differs between runs. |
| `RRBOX_EPOCH` and `TZ=UTC` | They fix both wall-clock sources: the kernel start time and the RTC base. |
| 32 MB launch hardware | The headless default is a Slim with 64 MB, and the memory size changes the game's heap. |
| Wi-Fi off | Removes network-dependent behaviour. |
| SAS mixing on the emulation thread; `IOTIMING_FAST` | Nothing waits on host thread timing. |
| An empty memory stick inside the repo for every run (`RRBOX_MEMSTICK`) | PPSSPP's default memory stick is the host's `~/.ppsspp`, which the oracle must never touch, and a save left over from an earlier run would change the game's path. |

## Booting a candidate

The executable boots from a host file with the retail disc mounted (`-m`). Two traps:

- **The extension.** PPSSPP treats a `.BIN` as a raw disc image and then boots nothing, so executables are staged as `.elf`.
- **The path.** The launch path is written into emulated RAM, so retail and candidate are staged at the same path, one run after the other.

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
| `race_seaside_start` | 7,800 | The new-game path to a race: Rally-X; the intro; the title; creating a driver profile (the system keyboard, where START accepts the default name); saving (system dialogs confirm with CIRCLE); World Tours, Basic Tour, Class 1, Seaside Route 765; car and transmission select; loading; the fly-by; the countdown; about 50 s of racing holding accelerate, with no steering. |

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
- the count and hash of every memory write the call made outside its own stack frame (callees included, on its own thread only);
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

**Teeth.** Two bugs were planted in the module loader's draft, and both were caught at its first call, by A5 and by A7:

- returning the module id + 1;
- swapping the `sprintf` arguments.

## Fault injection

A script line `force NAME N VALUE` makes the Nth call (0-based) of system function NAME return VALUE (hex) instead of its real result. The function still runs and has its side effects, just as a real failure would. Both retail and the candidate get the same forcing, so error paths that normal play never takes run and are compared.

The `fault_loader_*` scripts drive every path of the module loader: failed open, failed load, failed start, a module id of 0, and a file handle of 0. That took it from 56/72 to 72/72 instructions covered.

## Tiers from the ledger

A `@draft` is **T3** when its `config/us/t3_live.csv` row says PASS with full coverage and the source hash still matches (`tools/progress.py`). The module loader (0x0004a4) is the first: 91 calls over seven scripts, all 72 instructions executed, and A7 identical on every script.

## Not built yet

- Driving the power-resume and shutdown paths, which still show as uncovered.
- Display-list and audio comparison.
- Scripts that steer, finish laps, and reach the other modes.
- Per-instruction coverage.
