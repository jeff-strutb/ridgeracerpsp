#!/bin/sh
# Extract BOOT.BIN and EBOOT.BIN for USA, Europe and Japan into orig/<region>/
# and verify every file against the MD5s recorded in tools/refcheck.py; then
# build build/allegrex_ops.json (the opcode table of the toolchain's own
# psp-objdump) from psp-gcc-1.3.1.tar.gz in the same directory.
#
#   ./setup.sh [ISO_DIR]          ISO_DIR also from $RR_ISO_DIR
#   ./setup.sh --selftest         plant a wrong ISO and prove it is refused
#
# Output goes to $RR_ORIG if set, else <repo>/orig.
set -eu
here=$(cd "$(dirname "$0")" && pwd)
default_iso=/Users/jeffreywilbur/projects/strutb/ridgeracerpsp/references

iso_us='Ridge Racer (USA) (En,Fr,De,Es,It).iso'
iso_eu='Ridge Racer (Europe, Australia) (En,Fr,De,Es,It).iso'
iso_jp='Ridge Racers (Japan).iso'

extract() {   # extract ISO_DIR OUT_DIR
    iso_dir=$1; out=$2
    for region in us eu jp; do
        eval iso=\$iso_$region
        if [ ! -f "$iso_dir/$iso" ]; then
            echo "setup: missing ISO $iso_dir/$iso" >&2; return 1
        fi
        tmp=$(mktemp -d)
        bsdtar -xf "$iso_dir/$iso" -C "$tmp" \
            PSP_GAME/SYSDIR/BOOT.BIN PSP_GAME/SYSDIR/EBOOT.BIN
        mkdir -p "$out/$region"
        mv "$tmp/PSP_GAME/SYSDIR/BOOT.BIN" "$tmp/PSP_GAME/SYSDIR/EBOOT.BIN" \
            "$out/$region/"
        chmod 644 "$out/$region/BOOT.BIN" "$out/$region/EBOOT.BIN"
        rm -rf "$tmp"
    done
    RR_ORIG="$out" python3 "$here/tools/refcheck.py"
}

if [ "${1:-}" = "--selftest" ]; then
    iso_dir=${RR_ISO_DIR:-$default_iso}
    t=$(mktemp -d)
    trap 'rm -rf "$t"' EXIT
    # Planted fault: the USA name points at the Europe ISO.
    mkdir "$t/iso"
    ln -s "$iso_dir/$iso_eu" "$t/iso/$iso_us"
    ln -s "$iso_dir/$iso_eu" "$t/iso/$iso_eu"
    ln -s "$iso_dir/$iso_jp" "$t/iso/$iso_jp"
    if extract "$t/iso" "$t/orig" >"$t/log" 2>&1; then
        cat "$t/log"; echo "setup selftest: FAIL: wrong USA ISO accepted"; exit 1
    fi
    grep FAIL "$t/log"
    echo "setup selftest: wrong USA ISO refused; PASS"
    exit 0
fi

iso_dir=${1:-${RR_ISO_DIR:-$default_iso}}
out=${RR_ORIG:-$here/orig}
extract "$iso_dir" "$out"
echo "setup: reference files verified in $out"
mkdir -p "$here/build"
python3 "$here/tools/analysis/mkopcodes.py" "$iso_dir/psp-gcc-1.3.1.tar.gz" \
    "$here/build/allegrex_ops.json"
