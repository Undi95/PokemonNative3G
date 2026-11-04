#!/usr/bin/env python3
"""Puts reference screens on one image, to look at them all at once: the new
ones of the last suite run (from its journals), or the given names.

--changed [REV] instead shows each reference changed since REV (git, default
HEAD) as old | new | difference (changed pixels in red), several sheets of
--per-sheet rows: to review every --update-refs one by one, for instance after
a change that moves the random number generator.

usage: refs_sheet.py [NAME ...] [--all] [--out FILE]
       refs_sheet.py --changed [REV] [--per-sheet N] [--out DIR]
"""

import argparse
import glob
import io
import os
import subprocess

from PIL import Image, ImageChops, ImageDraw

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


def changed_refs(rev):
    """(name, old image or None, new image) for each reference .png changed since rev."""
    paths = subprocess.run(["git", "-C", REPO_DIR, "diff", "--name-only", rev, "--", REFS],
                           capture_output=True, text=True, check=True).stdout.split()
    changed = []
    for path in sorted(p for p in paths if p.endswith(".png")):
        full = os.path.join(REPO_DIR, path)
        if not os.path.exists(full):
            continue                                   # deleted: nothing new to look at
        old = subprocess.run(["git", "-C", REPO_DIR, "show", f"{rev}:{path}"], capture_output=True)
        changed.append((os.path.basename(path)[:-4],
                        Image.open(io.BytesIO(old.stdout)).convert("RGB") if old.returncode == 0 else None,
                        Image.open(full).convert("RGB")))
    return changed


def difference(old, new):
    """new, darkened, with the pixels that differ from old in red (all red if there is no old one)."""
    out = Image.eval(new, lambda c: c // 4)
    if old is None or old.size != new.size:
        return Image.new("RGB", new.size, (255, 0, 0))
    mask = ImageChops.difference(old, new).convert("L").point(lambda v: 255 if v else 0)
    out.paste((255, 0, 0), mask=mask)
    return out


def changed_sheets(rev, per_sheet, out_dir, scale):
    changed = changed_refs(rev)
    if not changed:
        print(f"aucune référence changée depuis {rev}")
        return
    os.makedirs(out_dir, exist_ok=True)
    w, h = int(240 * scale), int(160 * scale)
    for start in range(0, len(changed), per_sheet):
        chunk = changed[start:start + per_sheet]
        sheet = Image.new("RGB", (3 * (w + 8), len(chunk) * (h + 16)), (40, 40, 40))
        draw = ImageDraw.Draw(sheet)
        for i, (name, old, new) in enumerate(chunk):
            y = i * (h + 16)
            pixels = new.width * new.height - ImageChops.difference(old, new).convert("L").histogram()[0] \
                if old is not None and old.size == new.size else new.width * new.height
            draw.text((2, y), f"{name}  ({pixels} px)" + ("  NOUVELLE" if old is None else ""), fill=(255, 255, 0))
            for j, image in enumerate((old, new, difference(old, new))):
                if image is not None:
                    sheet.paste(image.resize((w, h), Image.NEAREST), (j * (w + 8), y + 14))
        sheet.save(os.path.join(out_dir, f"refs_changees_{start // per_sheet + 1:02d}.png"))
    print(f"{len(changed)} références changées depuis {rev} : {(len(changed) + per_sheet - 1) // per_sheet} "
          f"planches (ancien | nouveau | différence) dans {out_dir}")


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("names", nargs="*")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--changed", nargs="?", const="HEAD", metavar="REV",
                        help="old | new | difference of the references changed since REV (default HEAD)")
    parser.add_argument("--per-sheet", type=int, default=4, help="--changed: rows per sheet")
    parser.add_argument("--columns", type=int, default=4)
    parser.add_argument("--scale", type=float, default=None, help="size of each screen (0.5: half)")
    parser.add_argument("--out", default=None, help="sheet file (directory with --changed)")
    args = parser.parse_args()
    if args.changed:
        changed_sheets(args.changed, args.per_sheet, args.out or os.path.join(BUILD_DIR, "refs_changees"),
                       args.scale or 2.0)
        return
    args.scale = args.scale or 1.0
    args.out = args.out or os.path.join(BUILD_DIR, "refs_sheet.png")
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
