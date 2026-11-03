# L'arrosoir avec RED, LEAF et BRICE (docs/A-TESTER.md, 2026-11-03 ; sprites de Red/Leaf faits d'après Brendan/May) :
# un plant de baie (outil carte.baie : ROUTE 104, 2e terreau, CERIZ en pousse), l'ARROSOIR depuis le dessous :
# « arroser? » OUI, l'animation d'arrosage filmée (captures « PERSO-arrosoir-N »), le plant compte un arrosage.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re
import names

OPTION_CHARACTER = 6
PERSOS = (("red", 1, 0), ("leaf", 1, 1), ("brice", 0, 0))
TREE = "BERRY_TREE_ROUTE_104_SOIL_2"       # en (35, 6)


def play(game):
    continue_game(game)
    game.item("ITEM_WAILMER_PAIL", 1)
    tree = names.value(TREE)
    for who, perso, gender in PERSOS:
        game.dev("jeu.options", OPTION_CHARACTER, perso)
        game.dev("joueur.genre", gender)
        game.dev("carte.baie", tree, 1, 2)              # CERIZ, en pousse, pas encore arrosée
        game.warp("Route104", 35, 7); game.wait(30)
        finish_dialog(game, settle=20)
        game.press("UP", 1); game.wait(20)
        since = mark(game)
        game.tap("A")
        for _ in range(30):                             # « … a bourgeonné. », puis la question et OUI/NON
            game.wait(20)
            if saw_text(game, "OUI", since):
                break
            if not saw_text(game, "arroser", since):
                game.tap("A")
        game.wait(30); game.tap("A")                    # OUI
        wait_text(game, "arrose la", since=since, limit=300)
        for i in range(32):                             # le message « … arrose la CERIZ. », puis l'animation
            game.wait(8)
            game.shot(f"{who}-arrosoir-{i}")
        finish_dialog(game, limit=200)
        state = game.dev("carte.baie", tree)
        game.note(f"ARROSOIR {who} : {state.strip()}")
        expect(game, "arrosages 1" in state, f"{who} : le plant est arrosé ({state.strip()})")
