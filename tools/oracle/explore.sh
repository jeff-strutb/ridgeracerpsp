#!/bin/sh
# Run retail on a script and save a contact sheet of every Nth frame (for writing scripts).
#   tools/oracle/explore.sh SCRIPT FRAMES EVERY OUTDIR [FIRST]
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
ISO="$ROOT/references/Ridge Racer (USA) (En,Fr,De,Es,It).iso"
mkdir -p "$4" "$ROOT/build/oracle/a7/stage"
rm -f "$4"/frame_*.png
cp "$ROOT/orig/us/BOOT.BIN" "$ROOT/build/oracle/a7/stage/BOOT.elf"
MS="$ROOT/build/oracle/a7/stage/memstick"; rm -rf "$MS"; mkdir -p "$MS"
RRBOX_EPOCH=1104537600 TZ=UTC RRBOX_MEMSTICK="$MS" "$ROOT/build/ext/ppsspp-build/PPSSPPHeadless" "$ROOT/build/oracle/a7/stage/BOOT.elf" \
  -m "$ISO" -i --graphics=software --rr-frames="$2" --rr-script="$1" --rr-shots="$3:$4" >/dev/null 2>&1
if [ -n "$5" ]; then for f in "$4"/frame_*.png; do n=$(basename "$f" .png | sed 's/frame_0*//'); [ "${n:-0}" -lt "$5" ] && rm "$f"; done; fi
python3 "$ROOT/tools/oracle/sheet.py" "$4"
