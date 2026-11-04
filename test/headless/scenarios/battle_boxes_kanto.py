# BOITES COMBAT = KANTO en combat double et au Parc Safari (2026-11-03, docs/A-TESTER.md) : boîtes de PV et boîte de
# texte de Rouge Feu ; le combat simple est vu dans la grille (matrix.py). Écrans à regarder : le menu d'action d'un
# combat double (les jumelles de la Route 8, deux boîtes de chaque côté) et celui du Safari (BALL, APPAT, PIERRE, FUITE).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import crawl
from kanto_safari import wait_menu
from kanto_tour import log
from matrix import talk_at
from menu_helpers import wait_action_menu

OPTION_BATTLE_BOXES = 12


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.money(10000)
    game.dev("jeu.options", 0, 2)                      # texte rapide
    game.dev("jeu.options", OPTION_BATTLE_BOXES, 1)
    crawl.give_mewtwo(game)
    game.give_mon("SPECIES_PIKACHU", 30)
    game.dev("jeu.rencontres", 0)

    # Combat double : ELI et ANNE (Route 8)
    talk_at(game, "Route8", 40, 3)
    for _ in range(80):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=4)
    wait_action_menu(game)
    log(game, "double")
    expect(game, game.state.battle, "combat double contre ELI et ANNE")
    fight_battle(game, limit=4000)                      # combat double : sa durée dépend du hasard
    finish_dialog(game, limit=200)

    # Parc Safari : le guichet (OUI à tout), puis l'herbe
    game.dev("jeu.rencontres", 1)
    game.warp("FuchsiaCity_SafariZone_Entrance", 4, 4)
    game.press("UP", 16)
    for _ in range(300):
        if game.state.map_name == "KantoSafariZone_Center" and game.state.free:
            break
        game.tap("A", hold=2, gap=20)
    grid = live_map(game)
    px, py = game.state.pos
    grass = sorted(((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == "g"),
                   key=lambda t: abs(t[0] - px) + abs(t[1] - py))
    for x, y in grass[:20]:
        if grid.path((px, py), (x, y), set(game.state.objects)) is not None:
            walk_to(game, x, y, live=True, on_battle=lambda g: None)
            break
    for i in range(400):
        if game.state.battle:
            break
        game.press(("LEFT", "RIGHT")[i % 2], 16)
    since = mark(game)
    wait_menu(game, since)
    log(game, "safari")
    expect_text(game, "PIERRE", since)
