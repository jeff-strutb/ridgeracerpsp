#!/bin/sh
# Extract the retail executables from the user-supplied ISOs in references/ into orig/<region>/ and check MD5s.
set -e
cd "$(dirname "$0")"
x() {  # region iso md5
  mkdir -p "orig/$1"
  bsdtar -xOf "references/$2" PSP_GAME/SYSDIR/BOOT.BIN > "orig/$1/BOOT.BIN"
  bsdtar -xOf "references/$2" PSP_GAME/SYSDIR/EBOOT.BIN > "orig/$1/EBOOT.BIN"
  got=$(md5 -q "orig/$1/BOOT.BIN")
  [ "$got" = "$3" ] || { echo "orig/$1/BOOT.BIN: MD5 $got, expected $3" >&2; exit 1; }
  echo "orig/$1/BOOT.BIN OK"
}
x us "Ridge Racer (USA) (En,Fr,De,Es,It).iso" e87ea7c17004cd13945664152608140c
x eu "Ridge Racer (Europe, Australia) (En,Fr,De,Es,It).iso" 4eaa1ff90e56f5ff1521e4e59597e9f2
x jp "Ridge Racers (Japan).iso" 524c500adbe299a546e03ad40ada5a56

# enforce the filing and provenance rules on every commit
python3 tools/common/install_hooks.py
