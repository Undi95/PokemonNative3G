# Boîtes d'argent et de jetons des scripts (2026-11-02), au guichet des jetons du Casino de Céladopole (showmoneybox
# 0, 0 et showcoinsbox 0, 5, puis achat de 50 jetons) :
# - Options > MENUS = KANTO : celles de Rouge Feu (money.c, coins.c : « ARGENT » / « JETONS » écrits dans la fenêtre,
#   le montant dessous en petite police, 8 × 3, cadre standard de RF), comme ses choix multiples et son OUI/NON ;
# - MENUS = HOENN : celles d'Émeraude (10 × 2 avec l'étiquette ARGENT en sprite, 7 × 2). Les scripts de RF placent la
#   boîte des jetons par son cadre : sa fenêtre est en 1, 6 (avant : en 0, 5, le cadre à moitié hors de l'écran).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until
from kanto_tour import log

OPTION_MENU_STYLE = 11   # jeu.options (src/debug_tools.c)


def windows(game):
    """Les fenêtres ouvertes : {(x, y): (largeur, hauteur)}."""
    return {(int(m.group(1)), int(m.group(2))): (int(m.group(3)), int(m.group(4)))
            for m in re.finditer(r"en (-?\d+),(-?\d+) taille (\d+)x(\d+)", game.dev("gfx.fenetres"))}


def buy_coins(game, what):
    game.warp("CeladonCity_GameCorner", 6, 3); game.wait(30)
    game.press("UP", 2); game.wait(20)
    game.tap("A"); game.wait(150)
    log(game, f"{what} boites")
    shown = windows(game)
    game.tap("A"); game.wait(150)
    log(game, f"{what} choix")
    for _ in range(20):                               # 50 JETONS, puis les messages

        if game.state.free:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=600)
    return shown, windows(game)


def play(game):
    continue_game(game)
    game.item("ITEM_COIN_CASE", 1)
    game.money(5000)
    game.dev("joueur.jetons", 0)
    game.dev("jeu.options", OPTION_MENU_STYLE, 0)
    hoenn, hoenn_after = buy_coins(game, "hoenn")
    coins_hoenn = game.dev("joueur.jetons")
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    kanto, kanto_after = buy_coins(game, "kanto")
    coins_kanto = game.dev("joueur.jetons")

    # Vérifications
    expect(game, hoenn.get((1, 1)) == (10, 2) and hoenn.get((1, 6)) == (7, 2),
           f"MENUS = HOENN : argent 10 × 2 en 1, 1 et jetons 7 × 2 en 1, 6 ({hoenn})")
    expect(game, kanto.get((1, 1)) == (8, 3) and kanto.get((1, 6)) == (8, 3),
           f"MENUS = KANTO : argent et jetons de RF, 8 × 3 en 1, 1 et 1, 6 ({kanto})")
    expect(game, "jetons 50" in coins_hoenn and "jetons 100" in coins_kanto,
           f"50 jetons achetés à chaque fois ({coins_hoenn.strip()}, {coins_kanto.strip()})")
    expect(game, game.money() == 3000, f"2 × 1 000 ¥ payés ({game.money()})")
    expect(game, (1, 1) not in hoenn_after and (1, 6) not in hoenn_after and (1, 1) not in kanto_after
           and (1, 6) not in kanto_after, "boîtes fermées à la fin")
