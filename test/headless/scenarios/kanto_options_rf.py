# Options > MENUS = KANTO (choix user 2026-11-02) : l'écran Options est celui de Rouge Feu (option_menu.c de RF : titre
# au cadre standard de RF, bandeau « CHOIX / CHANGER / ANNUL. », une valeur par ligne, ◀▶ la change, A ou B ferme) avec
# les deux pages de la fusion (L/R) et le défilement (7 lignes visibles). Les valeurs vont dans gSaveBlock2.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until
from kanto_tour import log
from matrix import MENU_OPTION, open_start_entry
from redleaf_acro import close_menus

OPTION_TEXT_SPEED, OPTION_BATTLE_STYLE, OPTION_MENU_STYLE, OPTION_BAG_STYLE = 0, 3, 11, 13   # jeu.options


def option(game, number):
    line = next(line for line in game.dev("jeu.options").splitlines() if line.startswith(f"{number} "))
    return int(line.rsplit("=", 1)[1])


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    speed = option(game, OPTION_TEXT_SPEED)
    open_start_entry(game, MENU_OPTION)
    game.wait(90); log(game, "page 1")
    game.tap("RIGHT"); game.wait(20); log(game, "vitesse changee")            # VIT. TEXTE : valeur suivante
    game.tap("DOWN", 2, gap=12); game.tap("RIGHT"); game.wait(20)             # STYLE COMBAT : l'autre valeur
    game.tap("DOWN", 5, gap=12); game.wait(20); log(game, "defilement")      # JOUR/NUIT puis RETOUR : la liste défile
    game.tap("R"); game.wait(30); log(game, "page 2")
    game.tap("DOWN", 6, gap=12); game.tap("RIGHT"); game.wait(20); log(game, "page 2 sac")   # SAC : KANTO
    game.tap("DOWN", 3, gap=12); game.wait(20); log(game, "page 2 bas")      # TITRE, INTRO, RETOUR : la liste défile
    game.tap("B"); game.wait(60)
    close_menus(game)
    expect(game, option(game, OPTION_TEXT_SPEED) == (speed + 1) % 3, "VIT. TEXTE changée et gardée")
    expect(game, option(game, OPTION_BATTLE_STYLE) == 1, "STYLE COMBAT : DEFINI")
    expect(game, option(game, OPTION_BAG_STYLE) == 1, "SAC : KANTO")
    expect(game, option(game, OPTION_MENU_STYLE) == 1, "MENUS reste KANTO")
