# Objets d'intérieur de RF (docs/A-TESTER.md, 2026-11-03 ; GetInteractedMetatileScript de field_control_avatar.c,
# tools/kanto_tile_attributes.py) : pour chaque comportement, une case de Kanto qui l'a, regardée depuis la case du
# dessous (ou d'un côté) avec A : un texte s'affiche (noté au journal pour relecture). Aussi l'eau de la Piste
# Cyclable (SURF proposé) et les traces de pas sur le sable des grottes (MB_SAND_CAVE, captures « sable-N »).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from headless import REPO_DIR
from menu_helpers import texts

BEHAVIORS = ("MB_CABINET", "MB_KITCHEN", "MB_DRESSER", "MB_FOOD", "MB_BLUEPRINTS", "MB_PAINTING",
             "MB_POWER_PLANT_MACHINE", "MB_TELEPHONE", "MB_COMPUTER", "MB_ADVERTISING_POSTER", "MB_FOOD_SMELLS_TASTY",
             "MB_TRASH_BIN", "MB_CUP", "MB_BLINKING_LIGHTS", "MB_NEATLY_LINED_UP_TOOLS", "MB_POKEMART_SHELF",
             "MB_BURGLARY", "MB_TRAINER_TOWER_MONITOR")
SIDES = (((0, 1), "UP"), ((-1, 0), "RIGHT"), ((1, 0), "LEFT"))


def kanto_maps():
    with open(os.path.join(REPO_DIR, "data", "maps", "map_groups.json"), encoding="utf-8") as f:
        groups = json.load(f)
    return [m for g in groups["group_order"] if "Kanto" in g for m in groups[g]]


def events(name):
    with open(os.path.join(REPO_DIR, "data", "maps", name, "map.json"), encoding="utf-8") as f:
        info = json.load(f)
    spots = {(e["x"], e["y"]) for key in ("object_events", "bg_events", "coord_events", "warp_events")
             for e in info.get(key) or []}
    return spots


def candidates(behavior, limit=2):
    """(carte, case d'où regarder, direction) pour un comportement : jusqu'à limit cartes différentes."""
    found = []
    for name in kanto_maps():
        try:
            grid = maps.load(name)
        except (KeyError, FileNotFoundError):
            continue
        busy = events(name)
        spot = next(((x + dx, y + dy, face) for y in range(grid.height) for x in range(grid.width)
                     if grid.behaviors[y][x] == behavior and (x, y) not in busy
                     for (dx, dy), face in SIDES
                     if grid.tile(x + dx, y + dy) == "." and (x + dx, y + dy) not in busy
                     and "WATER" not in grid.behaviors[y + dy][x + dx]), None)
        if spot:
            found.append((name,) + spot)
            if len(found) == limit:
                break
    return found


def examine(game, name, x, y, face):
    game.warp(name, x, y); game.wait(30)
    finish_dialog(game, settle=20)
    if game.state.pos != (x, y):
        return None
    game.press(face, 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    for _ in range(12):
        if game.state.free:
            break
        game.tap("A"); game.wait(30)
    finish_dialog(game, settle=20)
    return " / ".join(t for w, t in texts(game, since) if w == 0)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_LAPRAS", 50)
    game.dev("joueur.capacite", 0, 0, names.value("MOVE_SURF"))
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1)
    missing = []
    for behavior in BEHAVIORS:
        shown = []
        for name, x, y, face in candidates(behavior):
            said = examine(game, name, x, y, face)
            game.note(f"OBJET {behavior} {name} ({x}, {y}) {face} : {said}")
            if said:
                shown.append(said)
        if not shown:
            missing.append(behavior)
    expect(game, not missing, f"un texte pour chaque objet d'intérieur de RF (sans : {missing})")

    # Eau de la Piste Cyclable (Route 17) : comme dans RF, de l'eau de décor (terrain « normal » dans les attributs de
    # RF, pas « eau » : IsPlayerFacingSurfableFishableWater ne propose pas SURF), qui fait un reflet (capture « reflet »)
    water = candidates("MB_CYCLING_ROAD_WATER", 1)
    said = examine(game, *water[0]) if water else None
    name, x, y, face = water[0]
    dx, dy = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}[face]
    tile = game.dev("carte.metatuiles", x + dx, y + dy, 1, 1)
    game.note(f"EAU PISTE CYCLABLE {water} : {said} ; {tile}")
    expect(game, not said and "terrain 0" in tile, f"eau de la Piste Cyclable : pas de SURF, comme RF ({said} ; {tile})")
    grid = maps.load(name)
    above = next(((x2, y2) for y2 in range(grid.height - 1) for x2 in range(grid.width)
                  if grid.behaviors[y2 + 1][x2] == "MB_CYCLING_ROAD_WATER" and grid.tile(x2, y2) == "."
                  and "WATER" not in grid.behaviors[y2][x2]), None)
    if above:
        game.warp(name, *above); game.wait(40)
        game.shot("reflet")

    # Sable des grottes : traces de pas
    sand = next(((n, x, y) for n in kanto_maps() if os.path.isdir(os.path.join(REPO_DIR, "data", "maps", n))
                 for grid, busy in [(maps.load(n), events(n))] for y in range(grid.height) for x in range(grid.width - 3)
                 if all(grid.behaviors[y][x + k] == "MB_SAND_CAVE" and grid.tile(x + k, y) == "."
                        and (x + k, y) not in busy for k in range(4))),
                None)
    game.note(f"SABLE {sand}")
    expect(game, sand is not None, "une rangée de sable de grotte")
    if sand:
        name, x, y = sand
        game.warp(name, x, y); game.wait(30)
        finish_dialog(game, settle=20)
        game.dev("jeu.rencontres", 0)
        game.press("RIGHT", 48)
        for i in range(3):
            game.shot(f"sable-{i}"); game.wait(10)
