#!/usr/bin/env python3
"""Rejoue un rapport de bug (menu DEBUG > Rapport de bug, src/platform/devtools.c) dans le banc headless : la
sauvegarde du lancement, l'heure du lancement et les touches de chaque image, jusqu'au moment du rapport. Écrit
journal.txt (ce que le jeu a fait), la dernière image (shots/fin.ppm, comparée à la capture du rapport) et l'état des
outils de debug à la fin (etat.txt), dans build/headless/replay/NOM/.

usage: replay.py BINAIRE RAPPORT [--images N]     RAPPORT : le .tar du rapport, ou son dossier déjà extrait
       --images N : s'arrêter N images avant la fin (regarder juste avant le bug)
"""

import argparse
import calendar
import os
import re
import sys
import tarfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import driver  # noqa: E402
from headless import BUILD_DIR  # noqa: E402

# L'état des outils de debug repris à la fin, comme dans rapport.txt
COMMANDS = ["sys.anomalies", "jeu.etat", "jeu.options", "carte.info", "carte.objets", "scripts.contexte",
            "joueur.equipe", "combat.etat", "texte.imprimantes", "gfx.fenetres", "gfx.sprites", "sys.etat"]


def extract(report, out_dir):
    """Le dossier du rapport (extrait d'un .tar si besoin)."""
    if os.path.isdir(report):
        return report
    folder = os.path.join(out_dir, "rapport")
    os.makedirs(folder, exist_ok=True)
    with tarfile.open(report) as tar:
        for member in tar.getmembers():
            if member.isfile() and "/" not in member.name and ".." not in member.name:
                with open(os.path.join(folder, member.name), "wb") as f:
                    f.write(tar.extractfile(member).read())
    return folder


def read_keys(path):
    """(début du jeu en secondes, [(images, boutons)]) de touches.txt."""
    start, runs = None, []
    with open(path, encoding="utf-8") as f:
        for line in f:
            match = re.match(r"# lancement (\d+)-(\d+)-(\d+) (\d+):(\d+):(\d+)", line)
            if match:
                # L'horloge du banc est en UTC (gmtime) : l'heure locale du téléphone écrite comme UTC
                start = calendar.timegm(tuple(int(x) for x in match.groups()) + (0, 0, 0))
            elif line.strip() and not line.startswith("#"):
                frames, buttons = line.split()
                runs.append((int(frames), buttons))
    return start, runs


def compare(a, b):
    """Nombre de pixels différents entre deux PPM (None si une image manque)."""
    try:
        from PIL import Image, ImageChops
    except ImportError:
        return None
    if not (os.path.exists(a) and os.path.exists(b)):
        return None
    diff = ImageChops.difference(Image.open(a).convert("RGB"), Image.open(b).convert("RGB")).convert("L")
    return diff.point(lambda value: 255 if value else 0).histogram()[255]


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("binary")
    parser.add_argument("report")
    parser.add_argument("--images", type=int, default=0, help="s'arrêter tant d'images avant la fin")
    args = parser.parse_args()

    name = os.path.splitext(os.path.basename(os.path.normpath(args.report)))[0]
    out_dir = os.path.join(BUILD_DIR, "replay", name)
    os.makedirs(out_dir, exist_ok=True)
    folder = extract(args.report, out_dir)
    start, runs = read_keys(os.path.join(folder, "touches.txt"))
    total = sum(frames for frames, _ in runs)
    stop = total - args.images

    begin = time.time()
    game = driver.Game(args.binary, out_dir, save=os.path.join(folder, "lancement.sav"), kanto_start=0,
                       test_time=start, max_frames=total + 10)
    played = 0
    for frames, buttons in runs:
        frames = min(frames, stop - played)
        if frames <= 0:
            break
        game.press(buttons, frames)
        played += frames
    game.shot("fin")
    with open(os.path.join(out_dir, "etat.txt"), "w", encoding="utf-8") as f:
        for command in COMMANDS:
            try:
                f.write(f"=== {command}\n{game.dev(command)}\n")
            except driver.GameError as e:
                f.write(f"=== {command}\nERREUR {e}\n")
    game.finish()

    capture = os.path.join(folder, "capture.ppm")
    different = compare(os.path.join(out_dir, "shots", "fin.ppm"), capture) if args.images == 0 else None
    print(f"{played} images rejouées en {time.time() - begin:.0f} s ; journal : {os.path.join(out_dir, 'journal.txt')}")
    print(f"état à la fin : {os.path.join(out_dir, 'etat.txt')} ; dernière image : {os.path.join(out_dir, 'shots', 'fin.ppm')}")
    if different is not None:
        print("même image que la capture du rapport" if different == 0
              else f"{different} pixels différents de la capture du rapport (le rejeu a divergé ?)")
    sys.exit(0 if different in (None, 0) else 1)


if __name__ == "__main__":
    main()
