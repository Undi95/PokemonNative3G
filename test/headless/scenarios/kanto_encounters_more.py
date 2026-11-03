# Rencontres de Kanto selon le type de rencontre de RF (docs/A-TESTER.md, 2026-11-03 ; IsLandWildEncounterAt et
# IsWaterWildEncounterAt de wild_encounter.c) : dans chaque lieu, deux cases voisines du type « terre » (1) ou « eau »
# (2) d'après carte.metatuiles, des allers-retours jusqu'à un combat sauvage, dont l'espèce est dans la table du lieu.
# Mt. Ember (extérieur et chemin Rubis), Route Victoire, Îles Écume, surf sur l'eau de la Route 21, et DOUX PARFUM dans
# la Forêt de Jade.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, re, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from headless import REPO_DIR
from menu_helpers import open_start_entry, pick

LAND, WATER = 1, 2
PLACES = (("MtEmber_Exterior", LAND), ("MtEmber_RubyPath_B2F", LAND), ("KantoVictoryRoad_2F", LAND),
          ("SeafoamIslands_B1F", LAND), ("Route21_North", WATER))


def table(map_name, area):
    with open(os.path.join(REPO_DIR, "src", "data", "wild_encounters.json"), encoding="utf-8") as f:
        data = json.load(f)
    map_id = maps_info(map_name)["id"]
    return {names.value(m["species"]) for g in data["wild_encounter_groups"] for e in g["encounters"]
            if e.get("map") == map_id for m in e.get(area, {}).get("mons", [])}


def maps_info(map_name):
    with open(os.path.join(REPO_DIR, "data", "maps", map_name, "map.json"), encoding="utf-8") as f:
        return json.load(f)


def arrive(game, place, grid):
    """Arrivée dans la carte (pour lire ses métatuiles) : sa première entrée, sinon sa première case libre."""
    warps = maps_info(place)["warp_events"]
    spot = (warps[0]["x"], warps[0]["y"]) if warps else \
        next((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == ".")
    game.warp(place, *spot); game.wait(30)
    finish_dialog(game, settle=20)


def encounter_tiles(game, grid, kind):
    """Deux cases voisines (gauche, droite) du type de rencontre kind, sans collision."""
    tiles = {}
    for top in range(0, grid.height, 16):
        for left in range(0, grid.width, 16):
            reply = game.dev("carte.metatuiles", left, top, min(16, grid.width - left), min(16, grid.height - top))
            for m in re.finditer(r"(\d+),(\d+) : .*? rencontre (\d+) elevation \d+ collision (\d+)", reply):
                if int(m.group(3)) == kind and m.group(4) == "0":
                    tiles[(int(m.group(1)), int(m.group(2)))] = True
    return next(((x, y), (x + 1, y)) for (x, y) in sorted(tiles) if (x + 1, y) in tiles and (x + 2, y) in tiles)


def pace(game, a, b, limit=120):
    for _ in range(limit):
        game.press("RIGHT", 16); game.wait(4)
        if game.state.battle:
            return True
        game.press("LEFT", 16); game.wait(4)
        if game.state.battle:
            return True
    return False


def foe_and_flee(game):
    wait_until(game, lambda s: s.foe, limit=600)
    species = game.state.foe[0][0]
    fight_battle(game)
    finish_dialog(game)
    return species


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.dev("joueur.capacite", 0, 0, names.value("MOVE_PSYCHIC"))
    game.dev("joueur.capacite", 0, 1, names.value("MOVE_SWEET_SCENT"))
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for place, kind in PLACES:
        grid = maps.load(place)
        arrive(game, place, grid)
        a, b = encounter_tiles(game, grid, kind)
        game.warp(place, *a); game.wait(30)
        finish_dialog(game, settle=20)
        if kind == WATER:
            game.dev("joueur.avatar", 3); game.wait(40)
        met = pace(game, a, b)
        species = foe_and_flee(game) if met else None
        allowed = table(place, "land_mons" if kind == LAND else "water_mons")
        game.note(f"RENCONTRE {place} ({a}, {'terre' if kind == LAND else 'eau'}) : {species}")
        expect(game, met and species in allowed, f"{place} : rencontre sur {a} ({species})")

    # DOUX PARFUM dans la Forêt de Jade, sur une case « terre »
    grid = maps.load("ViridianForest")
    arrive(game, "ViridianForest", grid)
    a, _ = encounter_tiles(game, grid, LAND)
    game.warp("ViridianForest", *a); game.wait(30)
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "DOUX PARFUM")
    for _ in range(40):
        if game.state.battle:
            break
        game.wait(30)
    met = game.state.battle
    species = foe_and_flee(game) if met else None
    game.note(f"DOUX PARFUM ViridianForest {a} : {species}")
    expect(game, met and species in table("ViridianForest", "land_mons"), f"DOUX PARFUM : un combat ({species})")
