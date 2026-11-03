# Course (B) dans les intérieurs (2026-11-03, docs/A-TESTER.md ; bike.c, IsRunningDisallowed : gMapHeader.allowRunning
# ignoré, seules les tuiles qui l'interdisent bloquent) : maison, Centre POKéMON et grotte, à Hoenn et à Kanto. Avec B,
# 32 images de DROITE font 4 cases (course, 8 images par case) ; sans B, 2 cases (marche).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os
import driver
import maps

PLACES = ("LittlerootTown_BrendansHouse_1F", "OldaleTown_PokemonCenter_1F", "GraniteCave_1F",
          "PalletTown_PlayersHouse_1F", "ViridianCity_PokemonCenter_1F", "MtMoon_1F")


def free_row(name, length=5):
    """Le début d'une rangée de length cases libres (« . ») sans objet, warp ni événement de case, pour courir vers
    la droite (4 cases)."""
    grid = maps.load(name)
    info = json.load(open(os.path.join(maps.REPO_DIR, "data", "maps", name, "map.json"), encoding="utf-8"))
    taken = {(o["x"], o["y"]) for o in info.get("object_events", [])} | set(grid.warps)
    taken |= {(c["x"], c["y"]) for c in info.get("coord_events", [])}
    for y in range(1, grid.height - 1):
        row = grid.tiles[y]
        for x in range(0, grid.width - length + 1):
            cells = [(x + i, y) for i in range(length)]
            if all(row[cx] == "." and (cx, cy) not in taken for cx, cy in cells):
                return x, y
    raise GameError(f"pas de rangée libre dans {name}")


def moved(game, name, spot, buttons):
    game.warp(name, *spot); game.wait(30)
    game.press("RIGHT", 1); game.wait(12)          # se tourner vers la droite (un appui court ne fait pas de pas)
    start = game.state.pos[0]
    game.press(buttons, 32)
    game.wait(20)
    return game.state.pos[0] - start


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_B_DASH", 1)
    game.dev("jeu.rencontres", 0)
    for name in PLACES:
        spot = free_row(name)
        run = moved(game, name, spot, "RIGHT+B")
        walk = moved(game, name, spot, "RIGHT")
        game.note(f"{name} {spot} : course {run}, marche {walk}")
        expect(game, run >= 4 and walk <= 3, f"{name} : B fait courir ({run} cases contre {walk} en 32 images)")
