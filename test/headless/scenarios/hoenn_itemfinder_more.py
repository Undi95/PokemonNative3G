# Cherch'Objet de RF à Hoenn (docs/A-TESTER.md, 2026-11-03 ; src/kanto_itemfinder.c) :
# - couleur des flèches : captures « fleches-PERSO-N » avec BRICE et RED (palette du joueur) ;
# - objet caché dans la carte voisine : PÉPITE de Vergazon (2, 15), le joueur sur la Route 114 à 5 cases à gauche,
#   de l'autre côté de la jonction : « L'appareil réagit » ;
# - joueur debout sur un objet caché ordinaire (SUPER POTION de la Route 104 en 7,6) : la réponse la plus forte.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

OPTION_CHARACTER = 6


def use(game, shots=None):
    """SELECT (CHERCH'OBJET enregistré) : les textes, jusqu'au retour du joueur."""
    since = mark(game)
    game.tap("SELECT")
    if shots:
        for i in range(10):
            game.wait(6)
            game.shot(f"{shots}-{i}")
    for _ in range(30):
        game.wait(40)
        if game.state.free:
            break
        game.tap("A")
    finish_dialog(game, settle=20)
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.item("ITEM_ITEMFINDER", 1)
    game.dev("joueur.enregistre", names.value("ITEM_ITEMFINDER"))

    # Les flèches avec BRICE puis RED
    for who, perso in (("brice", 0), ("red", 1)):
        game.dev("jeu.options", OPTION_CHARACTER, perso)
        game.flag("FLAG_HIDDEN_ITEM_ROUTE_104_SUPER_POTION", 0)
        game.warp("Route104", 7, 9); game.wait(30)
        said = use(game, shots=f"fleches-{who}")
        expect(game, "réagit" in said, f"{who} : l'appareil réagit ({said[:80]})")
    game.dev("jeu.options", OPTION_CHARACTER, 0)

    # La carte voisine : la PÉPITE de Vergazon depuis la Route 114
    game.flag("FLAG_HIDDEN_ITEM_FALLARBOR_TOWN_NUGGET", 0)
    grid = maps.load("Route114")
    spot = next((x, 15) for x in range(grid.width - 3, grid.width - 6, -1) if grid.tile(x, 15) == ".")
    game.warp("Route114", *spot); game.wait(30)
    said = use(game)
    game.note(f"VOISINE Route114 {spot} : {said}")
    expect(game, "réagit" in said, f"objet de Vergazon vu depuis la Route 114 ({spot} : {said[:80]})")

    # Debout sur la SUPER POTION de la Route 104 (objet caché ordinaire) : comme RF (SetNormalHiddenItem), la réponse la
    # plus forte (4 bips) ; seuls les objets « sous les pieds » de RF se déterrent (kanto_hidden_items)
    game.flag("FLAG_HIDDEN_ITEM_ROUTE_104_SUPER_POTION", 0)
    potions = game.item("ITEM_SUPER_POTION")
    game.warp("Route104", 7, 6); game.wait(30)
    sounds = len(game.sounds)
    said = use(game)
    dings = sum(s == "SE_ITEMFINDER" for _, s in game.sounds[sounds:])
    game.note(f"DESSUS : {said} ; {dings} bips")
    expect(game, "réagit" in said and dings == 4, f"debout sur l'objet : réponse forte, 4 bips ({dings} ; {said[:80]})")
    expect(game, game.item("ITEM_SUPER_POTION") == potions, "l'objet ordinaire n'est pas déterré (comme RF)")
    expect_flag(game, "FLAG_HIDDEN_ITEM_ROUTE_104_SUPER_POTION", 0)
