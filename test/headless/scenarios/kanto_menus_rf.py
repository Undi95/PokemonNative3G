# Options > MENUS = KANTO (2026-11-02) : les choix multiples des scripts, leur grille et le OUI / NON sont ceux de
# Rouge Feu (script_menu.c et new_menu_helpers.c de RF) : police de RF, lignes de 14 px (fenêtre de 7 tiles pour
# 4 choix), OUI / NON d'une colonne plus large. Avec MENUS = HOENN, ceux d'Émeraude (kanto_blackboard, kanto_card_stickers).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from kanto_tour import log
from kanto_card_stickers import press_until_text

OPTION_MENU_STYLE = 11   # jeu.options (src/debug_tools.c)


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    game.money(1000)
    game.wait(30)

    # Tableau de l'école de Jadielle : grille de RF (3 colonnes)
    game.warp("ViridianCity_School", 4, 2); game.wait(30)
    since = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "STATUT", since)
    press_until_text(game, "Lire quel sujet", since)
    wait_text(game, "RETOUR", since)
    game.wait(30); log(game, "grille")
    game.tap("RIGHT"); game.wait(10); game.tap("DOWN"); game.wait(10); log(game, "curseur")
    since_read = mark(game)
    game.tap("A")
    wait_text(game, "gelé", since_read)
    press_until_text(game, "Lire quel sujet", since_read)
    wait_text(game, "RETOUR", since_read)   # la grille revient
    game.wait(10); game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=300)

    # Casino de Céladopole : OUI / NON de RF, puis 4 choix de RF (fenêtre de 7 tiles)
    game.warp("CeladonCity_GameCorner", 16, 13); game.wait(30)
    since_photo = mark(game)
    game.tap("RIGHT"); game.wait(10); game.tap("A")
    wait_text(game, "IMPRIMANTE", since_photo)
    press_until_text(game, "OUI", since_photo)
    game.wait(30); log(game, "oui non")
    game.tap("A")
    wait_text(game, "SEPIA", since_photo)
    game.wait(30); log(game, "quatre choix")
    game.tap("DOWN", 3, gap=10); game.wait(10); log(game, "sepia")
    game.tap("A")
    finish_dialog(game)
    expect(game, game.var("VAR_KANTO_TRAINER_CARD_MON_ICON_TINT_IDX") == 3, "photo SEPIA (4e choix)")
