# Le hall du 2ᵉ étage des Centres de Kanto (RF, rétabli le 2026-11-04 : MB_CABLE_CLUB_WIRELESS_MONITOR et
# MB_BATTLE_RECORDS, tools/kanto_tile_attributes.py, field_control_avatar.c) : le moniteur sans fil (8, 3) dit que
# l'adaptateur sans fil n'est pas branché (pas d'adaptateur sur PC), l'écran des records (12, 3) montre les records
# des combats link (ShowBattleRecords de RF) et se referme avec B. Avant, les deux cases étaient muettes.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts


def face(game, x):
    game.warp("ViridianCity_PokemonCenter_2F", x, 4); game.wait(30)
    finish_dialog(game, settle=20)
    game.press("UP", 1); game.wait(10)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.var("VAR_KANTO_MAP_SCENE_POKEMON_CENTER_TEALA", 2)     # (l'accueil de la 1re visite, déjà vu)

    face(game, 8)
    since = mark(game)
    game.tap("A"); game.wait(60)
    finish_dialog(game)
    said = " ".join(t for _, t in texts(game, since))
    game.note(f"MONITEUR : {said}")
    expect(game, "adaptateur sans fil" in said, f"moniteur sans fil ({said})")

    face(game, 12)
    game.tap("A")
    shown = wait_until(game, lambda s: game.function(s.cb2) not in ("CB2_Overworld", "CB2_OverworldBasic"),
                       step=10, limit=300)
    game.wait(90)
    game.shot("records")
    screen = game.function(game.state.cb2)
    game.note(f"RECORDS : {screen}")
    game.tap("B"); game.wait(120)
    wait_until(game, lambda s: s.free, limit=600)
    expect(game, shown and game.state.map_name == "ViridianCity_PokemonCenter_2F",
           f"écran des records ouvert ({screen}) puis refermé ({game.state.map_name})")
