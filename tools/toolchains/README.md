# Toolchains

Pinned, never installed on the host. Tarballs live in `dist/`, which is gitignored. Run `shasum -a 256 -c SHA256SUMS` from this directory to verify them.

| Tarball | Ident | Source |
|---|---|---|
| psp-gcc-1.3.1 | `3.3.3+allegrex-2.2.1-psp-1.3.1` (cc1, cc1plus, binutils) | github.com/decompme/compilers release `compilers` |
| psp-gcc-1.7.1 | `3.3.3+allegrex-2.2.2-psp-1.7.1` (cc1 and cc1plus only; as/ld are empty stubs) | same |

The retail build used `3.3.3+allegrex-2.2.1-psp-1.5.1`. Both tarballs are i386 Linux ELF binaries that depend only on `libc.so.6`.

## Running them

The binaries run inside a Lima VM (Debian 12 arm64, pinned image, using qemu-user-static for i386 via binfmt). Only the repo is shared with the VM, at the same path as on the host.

```bash
tools/toolchains/lima.sh <cmd...>
```

The first call extracts Lima from `dist/` into `build/toolchains/lima` and creates the VM in `build/lima`. That takes a few minutes. After that, a call takes about 0.3 s per cc1+as round trip.

Unpack the compilers into `build/toolchains/psp-gcc-<ver>/`. Call `cc1`/`cc1plus` and `psp-as` directly rather than through the `psp-gcc` driver.

Lima: `dist/lima-2.2.1-Darwin-arm64.tar.gz`, from github.com/lima-vm/lima releases v2.2.1.

## Ghidra

Ghidra 12.1.3 (Homebrew) is used with **ghidra-allegrex v21.4** (github.com/kotcrab/ghidra-allegrex, asset `ghidra_12.1.3_PUBLIC_20260825_ghidra-allegrex.zip`, sha256 `62e829fa9e6ed6f2bd343763fb339a3f8812b02a4e0ed5a9409b14007b408243`). It is installed into the user Extensions directory.

For headless use, set `JAVA_HOME` to the Homebrew openjdk@21. The retail BOOT.BIN imports as "PSP Executable (ELF)", `Allegrex:LE:32:default`.

## Reconstructed retail compiler: psp-gcc-1.3.1-nocmov

```bash
python3 tools/toolchains/mk_nocmov.py
```

This builds `build/toolchains/psp-gcc-1.3.1-nocmov` from the unpacked 1.3.1. Retail never uses conditional moves, and stock 1.3.1/1.7.1 do. The script patches cc1 and cc1plus so that conditional moves are never generated: 4 optab stores become NOPs, and 13 `recog` returns become -1. It locates each site by disassembly and checks the original bytes before patching.

The script's docstring has the full rationale. `docs/decomp/GCC33-HANDBOOK.md` has the evidence. This is the scorer's default compiler.

## External sources (cloned into build/ext/, not tracked)

| Source | Pin | Used for |
|---|---|---|
| github.com/hrydgard/ppsspp | tag v1.20.4, commit `fa50bb1976065c4f8b1b47af227d367fe9771555` (shallow, with submodules) | Phase 1 behaviour oracle; its HLE NID tables name the imported system calls (`tools/analysis/imports.py`) |
| github.com/John-K/pspdecrypt | commit `c156627db7634d395c380c0a9589130f603307fc` (GPL-3.0), built with `make` against Homebrew OpenSSL | `tools/refcheck.py --eboot`: decrypted EBOOT.BIN == BOOT.BIN for US, EU and JP |

```bash
git clone https://github.com/John-K/pspdecrypt.git build/ext/pspdecrypt && git -C build/ext/pspdecrypt checkout c156627db7634d395c380c0a9589130f603307fc
make -C build/ext/pspdecrypt CFLAGS="-O2 -I/opt/homebrew/opt/openssl@3/include" CXXFLAGS="-O2 -I/opt/homebrew/opt/openssl@3/include -std=c++17" EXTRA_FLAG="-L/opt/homebrew/opt/openssl@3/lib"
git clone --depth 1 --branch v1.20.4 --recurse-submodules --shallow-submodules https://github.com/hrydgard/ppsspp.git build/ext/ppsspp
```
