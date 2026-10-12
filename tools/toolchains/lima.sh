#!/bin/sh
# Run a command inside the rrpsp toolchain VM, in the current directory.
# Usage: tools/toolchains/lima.sh <cmd...>     (starts the VM on first use)
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
export LIMA_HOME="$ROOT/build/lima"
LIMACTL="$ROOT/build/toolchains/lima/bin/limactl"
if [ ! -x "$LIMACTL" ]; then
  mkdir -p "$ROOT/build/toolchains/lima"
  tar -xzf "$ROOT/tools/toolchains/dist/lima-2.2.1-Darwin-arm64.tar.gz" -C "$ROOT/build/toolchains/lima"
fi
status="$("$LIMACTL" list --format '{{.Status}}' rrpsp 2>/dev/null || true)"
if [ -z "$status" ]; then
  "$LIMACTL" start --tty=false --name=rrpsp "$ROOT/tools/toolchains/lima/rrpsp.yaml" >&2
elif [ "$status" != "Running" ]; then
  "$LIMACTL" start --tty=false rrpsp >&2
fi
exec "$LIMACTL" shell --workdir "$(pwd)" rrpsp "$@"
