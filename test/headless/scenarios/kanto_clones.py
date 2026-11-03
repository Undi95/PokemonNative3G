# Objets « clone » de RF (docs/A-TESTER.md, 2026-11-03 ; les 9 de Kanto, type « clone » des map.json) : pour chacun, le
# joueur part de sa carte, aligné sur le clone, assez loin pour que RF le crée, et marche tout droit vers la carte
# voisine : l'obstacle est là avant la jonction (objet à la place du clone), puis pas de doublon après ; captures
# « CARTE-N » à chaque pas. Route 21 : en surfant (le gros homme de Bourg Palette).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, sys
import driver
import maps
from headless import REPO_DIR

STEPS = {"LEFT": (-1, 0), "RIGHT": (1, 0), "UP": (0, -1), "DOWN": (0, 1)}


def clones():
    found = []
    for name in sorted(os.listdir(os.path.join(REPO_DIR, "data", "maps"))):
        path = os.path.join(REPO_DIR, "data", "maps", name, "map.json")
        if os.path.exists(path):
            with open(path, encoding="utf-8") as f:
                for o in json.load(f).get("object_events") or []:
                    if o.get("type") == "clone":
                        found.append((name, o["x"], o["y"], o["target_map"]))
    return found


def start(grid, x, y, water):
    """La case de départ, alignée sur le clone, assez loin pour qu'il soit créé (RF : pas de clone à moins de 8 cases
    en largeur, 6 en hauteur, à l'arrivée ; TemplateIsObstacleAndWithinView), d'où l'on marche tout droit jusqu'à la
    jonction ; la direction et le nombre de pas pour la passer de 2 cases."""
    wanted = "~" if water else ".g"
    if x < 0 or x >= grid.width:
        direction = "LEFT" if x < 0 else "RIGHT"
        sx = x + 10 if x < 0 else x - 10
        border = 0 if x < 0 else grid.width - 1
        for d in sorted(range(-8, 9), key=abs):
            path = range(min(sx, border), max(sx, border) + 1)
            if all(grid.tile(px, y + d) in wanted for px in path):
                return (sx, y + d), direction, abs(sx - border) + 3
    else:
        direction = "UP" if y < 0 else "DOWN"
        sy = y + 8 if y < 0 else y - 8
        border = 0 if y < 0 else grid.height - 1
        for d in sorted(range(-8, 9), key=abs):
            path = range(min(sy, border), max(sy, border) + 1)
            if all(grid.tile(x + d, py) in wanted for py in path):
                return (x + d, sy), direction, abs(sy - border) + 3
    raise GameError(f"pas de chemin droit vers le clone ({x}, {y})")


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_LAPRAS", 50)
    game.dev("jeu.rencontres", 0)                       # pas de combat sauvage dans les herbes du chemin
    only = os.environ.get("KANTO_CLONES")                # (pour en regarder un seul : KANTO_CLONES=CeruleanCity)
    for name, cx, cy, target in clones():
        if only and name not in only.split(","):
            continue
        grid = maps.load(name)
        water = name.startswith("Route21")
        (sx, sy), direction, steps = start(grid, cx, cy, water)
        game.warp(name, sx, sy); game.wait(30)
        finish_dialog(game, settle=20)
        if water:
            game.dev("joueur.avatar", 3); game.wait(40)
        game.wait(30)
        game.note(f"OBJETS {game.dev('carte.objets')}")
        before = [o[:2] for o in game.state.objects]
        seen = False                                    # le clone, créé quand il entre dans la fenêtre des objets
        game.shot(f"{name}-0")
        for n in range(1, steps + 1):
            game.press(direction, 16); game.wait(8)
            finish_dialog(game, settle=10)
            game.shot(f"{name}-{n}")
            if game.state.map_name == name:
                before = [o[:2] for o in game.state.objects]
                seen |= (cx, cy) in before
        after = [o[:2] for o in game.state.objects]
        game.note(f"CLONE {name} ({cx}, {cy}) -> {target} : départ {sx},{sy} {direction}, avant {before}, après "
                  f"{game.state.map_name} {after}")
        expect(game, seen, f"{name} : l'objet de {target} est là avant la jonction ({cx}, {cy} dans {before})")
        expect(game, len(after) == len(set(after)), f"{name} : pas de doublon après la jonction ({after})")
