#!/usr/bin/env python3
"""Relevé du panneau du nom de lieu (v1.1, 2026-11-04) : une carte par section (MAPSEC) des deux régions, téléporté
dessus, on note ce qui s'affiche à l'arrivée et on le capture une fois la boîte descendue :
- « rf »      : le panneau de Rouge Feu (kanto_map_name_popup.c), attendu sur les cartes de Kanto ;
- « em »      : celui d'Émeraude (map_name_popup.c), au cadre de la section (sMapSectionToThemeId), attendu à Hoenn ;
- « apercu »  : l'aperçu d'un lieu (map_preview_screen.c), à la place du panneau, comme RF ;
- « rien »    : aucun des trois (carte sans nom à l'arrivée, show_map_name faux…).
Une carte de Kanto avec le panneau d'Émeraude (ou l'inverse) est une erreur. Le résultat va dans
build/headless/panneaux/panneaux.json, et les planches (le haut de l'écran, par région) dans le même dossier.

usage: panneaux.py BINAIRE [--cartes REGEX] [--toutes] [--out DIR]
  --toutes : toutes les cartes qui montrent leur nom, pas une par section
"""

import argparse
import json
import os
import re
import sys

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import driver  # noqa: E402
from crawl import all_maps, map_info, region, spawn_point  # noqa: E402
from driver import continue_game  # noqa: E402
from headless import BUILD_DIR, fixture  # noqa: E402

TASKS = {"Task_MapNamePopup": "rf", "Task_MapNamePopUpWindow": "em"}
CROP = (0, 0, 176, 36)   # le haut de l'écran : les deux panneaux y tiennent (RF : 23 tiles avec le « TOIT »)


def what_shows(game):
    names = [game.function(t) for t in game.state.tasks]
    for name in names:
        for task, kind in TASKS.items():
            if name.startswith(task):
                return kind
    if any("MapPreview" in n for n in names):
        return "apercu"
    return None


def survey(game, name, shots):
    spawn = spawn_point(name)
    game.wait(2)
    if not game.state.free:
        driver.finish_dialog(game)
    # Une scène d'arrivée coupée par le téléport (Île 4…) laisse le panneau caché
    game.flag("FLAG_HIDE_MAP_NAME_POPUP", 0)
    game.warp(name, *spawn)
    kind, frames = None, 0
    # Le panneau vient à l'arrivée (warp() attend que le joueur puisse bouger : l'aperçu est déjà passé)
    for frames in range(0, 120, 2):
        kind = what_shows(game)
        if kind in ("rf", "em"):
            break
        game.wait(2)
    if kind in ("rf", "em"):
        game.wait(40)   # la boîte a fini de glisser
        game.shot(name)
        shots.append(name)
    return kind or "rien"


def sheet(folder, items, out, zoom=2, cols=4):
    w, h = (CROP[2] - CROP[0]) * zoom, (CROP[3] - CROP[1]) * zoom
    rows = (len(items) + cols - 1) // cols
    image = Image.new("RGB", (cols * (w + 6), max(1, rows) * (h + 14)), (30, 30, 30))
    draw = ImageDraw.Draw(image)
    for k, (name, label) in enumerate(items):
        x, y = (k % cols) * (w + 6), (k // cols) * (h + 14)
        path = os.path.join(folder, name + ".ppm")
        if os.path.exists(path):
            shot = Image.open(path).convert("RGB").crop(CROP).resize((w, h), Image.NEAREST)
            image.paste(shot, (x, y + 12))
        draw.text((x + 2, y), label[:w // 6], fill=(255, 255, 0))
    image.save(out)
    return out


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("binary")
    parser.add_argument("--cartes", default=None)
    parser.add_argument("--toutes", action="store_true")
    parser.add_argument("--out", default=os.path.join(BUILD_DIR, "panneaux"))
    args = parser.parse_args()

    chosen, seen = [], set()
    for name in all_maps():
        if args.cartes and not re.search(args.cartes, name):
            continue
        info = map_info(name)
        if not info.get("show_map_name"):
            continue
        key = (info["region_map_section"], region(name))
        if not args.toutes and key in seen:
            continue
        seen.add(key)
        chosen.append((name, info["region_map_section"], region(name)))
    print(len(chosen), "cartes")

    save = fixture(args.binary, "kanto")
    game = driver.Game(args.binary, os.path.join(args.out, "jeu"), save=save, max_frames=10_000_000)
    continue_game(game)
    game.dev("jeu.rencontres", 0)
    results, shots = [], []
    try:
        for k, (name, mapsec, where) in enumerate(chosen):
            try:
                kind = survey(game, name, shots)
            except driver.GameError as e:
                kind = "erreur : " + str(e)[:200]
            wrong = (where == "kanto" and kind == "em") or (where == "hoenn" and kind == "rf")
            results.append({"carte": name, "section": mapsec, "region": where, "panneau": kind, "faux": wrong})
            print(f"{k + 1:3}/{len(chosen)} {where:5} {kind:7} {'FAUX ' if wrong else ''}{name} ({mapsec})",
                  flush=True)
    finally:
        game.finish()

    with open(os.path.join(args.out, "panneaux.json"), "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=1)
    shots_dir = game.shots_dir
    for where in ("kanto", "hoenn"):
        items = [(r["carte"], f"{r['carte']} {r['section'][7:]}") for r in results
                 if r["region"] == where and r["carte"] in shots]
        for part in range(0, len(items), 48):
            print(sheet(shots_dir, items[part:part + 48],
                        os.path.join(args.out, f"planche_{where}_{part // 48 + 1}.png")))
    wrong = [r for r in results if r["faux"]]
    counts = {}
    for r in results:
        counts[(r["region"], r["panneau"])] = counts.get((r["region"], r["panneau"]), 0) + 1
    print("BILAN", sorted(counts.items()))
    for r in wrong:
        print("FAUX", r)
    sys.exit(1 if wrong else 0)


if __name__ == "__main__":
    main()
