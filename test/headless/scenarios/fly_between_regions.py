# Vol entre régions (2026-11-03, docs/A-TESTER.md ; kanto_region_map.c, CanFlyBetweenRegions) : après la Ligue de Kanto
# et le Rubis/Saphir rendus à CÉLIO, VOL depuis l'équipe à Bourg Palette, SELECT = carte de vol de Hoenn (curseur sur
# BOURG-EN-VOL), A : on s'envole et on atterrit à Bourg-en-Vol ; puis l'inverse, de Bourg-en-Vol à Bourg Palette.
# Sans ces deux conditions, SELECT ne change pas de carte.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick

FLY_MAPS = {"kanto": "KantoCB2_OpenFlyMap", "hoenn": "CB2_FlyMap"}      # écrans (callback 2) des deux cartes de vol


def fly_select(game, start, fly=True):
    """À start, VOL depuis l'équipe, SELECT (carte de l'autre région), puis A (s'envoler) ou B (renoncer) ; rend les
    écrans traversés."""
    game.warp(*start); game.wait(30)
    first = game.frames
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "VOL"); game.wait(240)
    game.tap("SELECT"); game.wait(180)
    for _ in range(12):
        if game.state.free:
            break
        game.tap("A" if fly else "B"); game.wait(120)
    wait_until(game, lambda s: s.free, limit=1500)
    return [name for frame, name in game.cb2s if frame >= first]


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_DRAGONITE", 60)
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_FLY"))
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1)
        game.flag(f"FLAG_BADGE0{i + 1}_GET", 1)
    game.flag("FLAG_VISITED_LITTLEROOT_TOWN", 1)
    game.flag("FLAG_KANTO_WORLD_MAP_PALLET_TOWN", 1)

    # Sans la Ligue de Kanto : SELECT ne change pas de carte (B pour sortir)
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 0)
    screens = fly_select(game, ("PalletTown", 10, 9), fly=False)
    expect(game, FLY_MAPS["kanto"] in screens and FLY_MAPS["hoenn"] not in screens,
           f"Ligue de Kanto pas finie : SELECT, toujours la carte de Kanto ({' > '.join(screens[:8])})")
    expect_map(game, "PalletTown")

    # Kanto -> Hoenn
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    game.flag("FLAG_KANTO_SYS_CAN_LINK_WITH_RS", 1)
    screens = fly_select(game, ("PalletTown", 10, 9))
    expect(game, FLY_MAPS["kanto"] in screens and FLY_MAPS["hoenn"] in screens,
           f"Bourg Palette : carte de Kanto, SELECT, carte de Hoenn ({' > '.join(screens[:8])})")
    expect_map(game, "LittlerootTown")
    # Hoenn -> Kanto
    screens = fly_select(game, ("LittlerootTown", 10, 10))
    expect(game, screens.index(FLY_MAPS["hoenn"]) < screens.index(FLY_MAPS["kanto"]),
           f"Bourg-en-Vol : carte de Hoenn, SELECT, carte de Kanto ({' > '.join(screens[:8])})")
    expect_map(game, "PalletTown")
