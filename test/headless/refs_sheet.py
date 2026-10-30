#!/usr/bin/env python3
"""Puts reference screens on one image, to look at them all at once: the new
ones of the last suite run (from its journals), or the given names.

usage: refs_sheet.py [NAME ...] [--all] [--out FILE]
"""

import argparse
import glob
import os

from PIL import Image, ImageDraw

from headless import BUILD_DIR, REPO_DIR

REFS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "refs")


def new_refs():
    names = []
    for journal in glob.glob(os.path.join(BUILD_DIR, "suite", "*", "journal.txt")):
        with open(journal, encoding="utf-8") as f:
            for line in f:
                if "NOUVELLE RÉFÉRENCE écran " in line:
                    names.append(line.split("écran ", 1)[1].split(" : ")[0])
    return sorted(set(names))


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("names", nargs="*")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--columns", type=int, default=4)
    parser.add_argument("--scale", type=float, default=1.0, help="size of each screen (0.5: half)")
    parser.add_argument("--out", default=os.path.join(BUILD_DIR, "refs_sheet.png"))
    args = parser.parse_args()
    names = args.names or ([os.path.basename(p)[:-4] for p in sorted(glob.glob(os.path.join(REFS, "*.png")))]
                           if args.all else new_refs())
    if not names:
        print("aucune référence")
        return
    w, h = int(240 * args.scale), int(160 * args.scale)
    rows = (len(names) + args.columns - 1) // args.columns
    sheet = Image.new("RGB", (args.columns * (w + 4), rows * (h + 16)), (40, 40, 40))
    draw = ImageDraw.Draw(sheet)
    for i, name in enumerate(names):
        x, y = (i % args.columns) * (w + 4) + 2, (i // args.columns) * (h + 16) + 2
        sheet.paste(Image.open(os.path.join(REFS, name + ".png")).resize((w, h)), (x, y + 12))
        draw.text((x, y), name[:int(38 * args.scale) + 4], fill=(255, 255, 255))
    sheet.save(args.out)
    print(f"{len(names)} écrans : {args.out}")


if __name__ == "__main__":
    main()
