# Cartes de dresseur des deux régions (2026-11-03, docs/A-TESTER.md « Carte dresseur » ; trainer_card.c d'Émeraude et,
# depuis le 2026-11-04, kanto_trainer_card.c = trainer_card.c de RF pour celle de Kanto) :
# - à Hoenn, la carte d'Émeraude s'ouvre d'abord, avec les badges de Hoenn ; SELECT : la carte de Kanto (RF), badges
#   de Kanto ;
# - à Kanto, la carte de Kanto d'abord ; SELECT : celle de Hoenn ;
# - le verso de chacune (A) ; le portrait suit l'option PERSO (BRICE puis RED) sur les deux cartes.
# Badges différents dans les deux régions (3 à Hoenn, 5 à Kanto) pour les distinguer à l'écran.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
sys.path.insert(0, os.path.dirname(driver.__file__))
from kanto_tour import log
from matrix import MENU_PLAYER, OPTIONS, back_to_free, open_start_entry
from menu_helpers import texts
import names

OPTION_PERSO = dict(OPTIONS)["PERSO"]


def back_text(game, since):
    """Le titre du verso : « CARTE DE DRESSEUR de … » écrit (Émeraude), ou seulement le nom (RF : « DRESSEUR: » est
    dans l'image de la carte)."""
    said = " ".join(text for _, text in texts(game, since))
    return "emeraude" if "CARTE DE DRESSEUR de" in said else "rf" if said and "CARTE" not in said else said[:60]


def both_cards(game, where, first, second):
    open_start_entry(game, MENU_PLAYER)
    game.wait(150); log(game, f"{where} recto")
    since = mark(game)
    game.tap("A"); game.wait(90); log(game, f"{where} verso")
    expect(game, back_text(game, since) == first, f"{where} : la carte {first} d'abord ({back_text(game, since)})")
    game.tap("B"); game.wait(90)                 # au verso, B retourne la carte
    game.tap("SELECT"); game.wait(180); log(game, f"{where} SELECT recto")
    since = mark(game)
    game.tap("A"); game.wait(90); log(game, f"{where} SELECT verso")
    expect(game, back_text(game, since) == second, f"{where} : SELECT, la carte {second} ({back_text(game, since)})")
    back_to_free(game)


def play(game):
    continue_game(game)
    for i in range(8):
        game.flag(names.value("FLAG_BADGE01_GET") + i, int(i < 3))
        game.flag(names.value("FLAG_KANTO_BADGE01_GET") + i, int(i < 5))

    for perso in (0, 1):                          # BRICE, puis RED
        game.dev("jeu.options", OPTION_PERSO, perso)
        name = "brice" if perso == 0 else "red"
        game.warp("LittlerootTown", 10, 10)
        both_cards(game, f"hoenn {name}", "emeraude", "rf")
        game.warp("PalletTown", 10, 8)
        both_cards(game, f"kanto {name}", "rf", "emeraude")
