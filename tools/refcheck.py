#!/usr/bin/env python3
"""Reference-binary gate.  Every tool reads retail bytes through this module.

The reference for the decompilation is the USA BOOT.BIN.  The other five
files are recorded so that setup.sh can prove what it extracted.

    import refcheck
    data = refcheck.require()                 # USA BOOT.BIN bytes, or exit 2
    data = refcheck.require('eu', 'BOOT.BIN')

CLI:
    tools/refcheck.py             check all six files under orig/
    tools/refcheck.py --selftest  prove the check refuses a corrupted file

The orig/ directory is <repo>/orig unless RR_ORIG is set.
"""
import hashlib
import os
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

REFS = {
    ('us', 'BOOT.BIN'):  'e87ea7c17004cd13945664152608140c',
    ('us', 'EBOOT.BIN'): 'aad6a9e6a2302a01a7d976ff9061b124',
    ('eu', 'BOOT.BIN'):  '4eaa1ff90e56f5ff1521e4e59597e9f2',
    ('eu', 'EBOOT.BIN'): 'a90810670d287815354ffd5d6110cb59',
    ('jp', 'BOOT.BIN'):  '524c500adbe299a546e03ad40ada5a56',
    ('jp', 'EBOOT.BIN'): '95ffb39cf488ee7782bfc2632d1a6e8a',
}


class RefError(Exception):
    pass


def orig_dir():
    return Path(os.environ.get('RR_ORIG', ROOT / 'orig'))


def path(region='us', name='BOOT.BIN'):
    return orig_dir() / region / name


def check_file(p, region, name):
    """Return the bytes of p if its MD5 is the recorded one, else raise."""
    want = REFS[(region, name)]
    p = Path(p)
    if not p.is_file():
        raise RefError(f'{p}: missing (run ./setup.sh)')
    data = p.read_bytes()
    got = hashlib.md5(data).hexdigest()
    if got != want:
        raise RefError(f'{p}: MD5 {got}, expected {want} for {region} {name}')
    return data


def require(region='us', name='BOOT.BIN'):
    """Bytes of a verified reference file.  Exits with status 2 otherwise."""
    try:
        return check_file(path(region, name), region, name)
    except RefError as e:
        sys.stderr.write(f'refcheck: REFUSED: {e}\n')
        raise SystemExit(2)


def selftest():
    good = path('us', 'BOOT.BIN')
    data = check_file(good, 'us', 'BOOT.BIN')
    with tempfile.TemporaryDirectory() as td:
        bad = Path(td) / 'BOOT.BIN'
        planted = bytearray(data)
        planted[0x1000] ^= 0x01            # one bit in .text
        bad.write_bytes(planted)
        try:
            check_file(bad, 'us', 'BOOT.BIN')
        except RefError as e:
            print(f'selftest: planted fault refused: {e}')
        else:
            print('selftest: FAIL: corrupted BOOT.BIN was accepted')
            return 1
        bad.unlink()
        try:
            check_file(bad, 'us', 'BOOT.BIN')
        except RefError as e:
            print(f'selftest: missing file refused: {e}')
        else:
            print('selftest: FAIL: missing file was accepted')
            return 1
    print('selftest: genuine file accepted; PASS')
    return 0


def main(argv):
    if argv[1:] == ['--selftest']:
        return selftest()
    bad = 0
    for (region, name), want in REFS.items():
        try:
            check_file(path(region, name), region, name)
            print(f'ok   {region} {name} {want}')
        except RefError as e:
            print(f'FAIL {e}')
            bad += 1
    return 2 if bad else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
