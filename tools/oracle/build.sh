#!/bin/sh
# Build rrbox: PPSSPP v1.20.4 (pinned) headless with tools/oracle/ppsspp-rrbox.patch applied.
# Everything lives in build/ext/ (not tracked). Safe to re-run.
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
SRC="$ROOT/build/ext/ppsspp"
PIN=fa50bb1976065c4f8b1b47af227d367fe9771555
if [ ! -d "$SRC" ]; then
  git clone --depth 1 --branch v1.20.4 --recurse-submodules --shallow-submodules https://github.com/hrydgard/ppsspp.git "$SRC"
fi
[ "$(git -C "$SRC" rev-parse HEAD)" = "$PIN" ] || { echo "build/ext/ppsspp is not at $PIN" >&2; exit 1; }
if git -C "$SRC" apply --check "$ROOT/tools/oracle/ppsspp-rrbox.patch" 2>/dev/null; then
  git -C "$SRC" apply "$ROOT/tools/oracle/ppsspp-rrbox.patch"
elif ! git -C "$SRC" apply --reverse --check "$ROOT/tools/oracle/ppsspp-rrbox.patch" 2>/dev/null; then
  echo "rrbox patch neither applies nor is already applied; inspect build/ext/ppsspp" >&2; exit 1
fi
cmake -S "$SRC" -B "$ROOT/build/ext/ppsspp-build" -DHEADLESS=ON -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build "$ROOT/build/ext/ppsspp-build" --target PPSSPPHeadless -j 10
echo "rrbox: $ROOT/build/ext/ppsspp-build/PPSSPPHeadless"
