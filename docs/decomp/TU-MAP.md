# Translation units and the denominator (US BOOT.BIN)

Measured 2026-10-12. To regenerate:

```bash
python3 tools/analysis/funcmap.py && python3 tools/analysis/libid.py && python3 tools/analysis/tumap.py
```

The outputs are `config/us/funcs.csv`, `config/us/libfuncs.csv` and `config/us/tus.csv`. Query them rather than this page.

## Object boundaries

- **`.eh_frame` has one CIE per C++ object compiled with exceptions, and that object's FDEs follow it.**
  - There are 262 CIE groups.
  - Their address spans never overlap and run in strictly increasing order, so each group is one object's `.text`.
  - The linker did not merge CIEs.
  - In 12 groups the FDEs are not in address order. Template and inline (linkonce) functions are emitted after the object's own functions, but they are still placed inside its span.
- **`.comment` has 493 idents, one per linked object, in link order.**
  - 488 are `psp-1.5.1`, and 5 are `psp-1.5.1.internal`.
  - That leaves 493 − 262 = 231 objects without EH tables (C, assembly, C library members). They sit in the 191 gaps between CIE groups, and a gap may hold several of them.
- **Data order cross-check.** An object's exclusively-referenced data mostly follows text order:
  - `.rodata`: 236/266
  - `.data`: 69/81
  - `.bss`: 73/108
  - The exceptions are expected. Some are globals of other objects used by just one object; others come from linker-allocated common `.bss` and merged constants. This is supporting evidence only; the CIE order is the proof.

**Open:** splitting multi-object gaps. This uses each object's `.rodata`/`.data` clusters and string anchors.

## Libraries

`tools/analysis/libid.py` fingerprints every function in the libraries shipped with psp-gcc 1.3.1 and 1.7.1:

- newlib `libc`/`libm`, libstdc++, libsupc++, libgcc, crt0
- 1,870 fingerprints in all, with relocated fields masked

A retail function is identified only when its masked words are identical to a library function's and that fingerprint occurs at exactly one retail address. Generic shapes, such as empty functions and trivial destructors, recur in game code and are never claimed.

This finds 541 functions (148 KB). It under-counts: retail's libraries were built by the 1.5.1 compiler, which has no conditional moves, so many library functions differ slightly from the shipped builds.

The link order, laid out by `tus.csv` `class`:

| Range | Class | What |
|---|---|---|
| 0x000040 to 0x1158d8 | game | game objects, including Namco middleware (nuSound, the ATRAC/SAS players) |
| 0x1158d8 to 0x131018 | lib:newlib | newlib libc + libm (one gap, 416 functions) |
| 0x131018 to 0x15a498 | lib:libstdc++ (with unknown islands) | libstdc++ v3: streams, locale, `basic_string` |
| 0x15a498 to 0x1634c0 | unknown | 13 objects, not yet identified (strings such as `_root`, `_CANTPRESSBUTTON`) |
| 0x1634c0 to 0x168d44 | lib:libgcc (with unknown islands) | 64-bit division (0x163544/0x163a94 are 1.5.1 builds of `__udivdi3`/`__umoddi3`) and the DWARF unwinder |
| 0x168d44 to 0x16e3fc | lib:libc | the time functions and the C library tail |

## Denominator

| Class | Rows | Bytes | Functions |
|---|---:|---:|---:|
| game | 378 | 1,136,792 | 5,466 |
| lib:libstdc++ | 45 | 165,592 | 944 |
| lib:newlib + lib:libc | 2 | 134,648 | 559 |
| lib:libgcc | 5 | 19,884 | 129 |
| unknown | 23 | 43,176 | 342 |

Bytes in this table are **object span** bytes, which include alignment padding between functions. The progress bars count **function** bytes from `funcs.csv`: by that measure the game denominator is 5,466 functions and 1,124,396 B (`tools/progress.py`).

**M1 and M2 are measured against the game row.** Library code is FENCED. It is matched from its own source (newlib, libstdc++ v3 and libgcc from GCC 3.3.3) or reproduced by linking, and it does not count toward progress.

"unknown" stays out of both the numerator and the denominator until it is identified. If it turns out to be game code, the denominator grows.
