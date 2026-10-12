#!/usr/bin/env python3
"""Tile the oracle's saved frames (frame_NNNNN.png) into one labelled contact sheet.

    python3 tools/oracle/sheet.py DIR [OUT.png] [--cols 6] [--scale 0.5]
"""
import argparse
import glob
import os

from PIL import Image, ImageDraw


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dir')
    ap.add_argument('out', nargs='?')
    ap.add_argument('--cols', type=int, default=6)
    ap.add_argument('--scale', type=float, default=0.5)
    a = ap.parse_args()
    files = sorted(glob.glob(os.path.join(a.dir, 'frame_*.png')))
    w, h = int(480 * a.scale), int(272 * a.scale)
    rows = (len(files) + a.cols - 1) // a.cols
    sheet = Image.new('RGB', (a.cols * w, rows * (h + 14)), 'white')
    d = ImageDraw.Draw(sheet)
    for k, f in enumerate(files):
        x, y = (k % a.cols) * w, (k // a.cols) * (h + 14)
        sheet.paste(Image.open(f).convert('RGB').resize((w, h)), (x, y + 14))
        d.text((x + 2, y + 1), os.path.basename(f)[6:11].lstrip('0') or '0', fill='black')
    out = a.out or os.path.join(a.dir, 'sheet.png')
    sheet.save(out)
    print(out)


if __name__ == '__main__':
    main()
