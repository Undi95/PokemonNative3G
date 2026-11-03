# Option SAC (2026-11-03, docs/A-TESTER.md), sauvegarde « hoenn » :
# - SAC = KANTO : planter une baie dans la terre meuble de la Route 104 ouvre le sac d'Émeraude (comme le mixeur,
#   l'apprenti et le bureau de Timmy : leurs poches n'existent pas dans le sac de RF), et la BAIE ORAN est plantée ;
# - SAC = HOENN : le menu Start ouvre le sac d'Émeraude ; SAC = KANTO : celui de Rouge Feu.
# Le sac d'Émeraude s'ouvre par CB2_Bag, celui de RF par CB2_OpenBagMenu (les deux tournent ensuite dans un
# CB2_BagMenuRun).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "hoenn"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import open_start_entry, press_until_free, texts

OPTION_BAG_STYLE = 13


def opened(game, since):
    names = [name for _, name in game.cb2s[since:]]
    return "hoenn" if "CB2_Bag" in names else "kanto" if "CB2_OpenBagMenu" in names else f"? {names}"


def start_menu_bag(game, style, what):
    game.dev("jeu.options", OPTION_BAG_STYLE, style)
    since = len(game.cb2s)
    open_start_entry(game, "SAC"); game.wait(240)
    log(game, what)
    result = opened(game, since)
    press_until_free(game)
    return result


def play(game):
    continue_game(game)
    game.item("ITEM_ORAN_BERRY", 3)
    game.dev("jeu.options", OPTION_BAG_STYLE, 1)
    game.warp("Route104", 35, 7); game.wait(60)
    game.press("UP", 2); game.wait(20)                 # face à la terre meuble (35,6)
    since = mark(game)
    screens = len(game.cb2s)
    game.tap("A")
    wait_text(game, "NON", since=since)
    game.wait(30)
    game.tap("A"); game.wait(300)                      # OUI : planter
    log(game, "planter sac")
    tree_bag = opened(game, screens)
    game.tap("A"); game.wait(60)                       # BAIE ORAN
    for _ in range(12):
        if saw_text(game, "planté", since):
            break
        game.tap("A"); game.wait(60)
    planted = texts(game, since)
    press_until_free(game, "A")

    hoenn = start_menu_bag(game, 0, "menu start hoenn")
    kanto = start_menu_bag(game, 1, "menu start kanto")

    # Vérifications
    expect(game, tree_bag == "hoenn", f"terre meuble : sac d'Émeraude avec SAC = KANTO ({tree_bag})")
    expect(game, any("planté" in t for _, t in planted), f"BAIE ORAN plantée ({planted[-3:]})")
    expect_item(game, "ITEM_ORAN_BERRY", 2)
    expect(game, hoenn == "hoenn" and kanto == "kanto", f"menu Start : sac d'Émeraude puis de RF ({hoenn}, {kanto})")
