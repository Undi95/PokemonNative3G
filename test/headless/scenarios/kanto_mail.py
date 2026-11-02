# Lecture d'une lettre (ReadMail) : avec Options > MENUS = HOENN, la lettre d'Émeraude ; avec MENUS = KANTO, celle de
# Rouge Feu (kanto_mail.c, 2026-11-02) : mêmes images, mais le message à gauche (police de RF, 5 lignes de 2 mots) et la
# signature dans sa propre fenêtre en bas à droite. Lettres PERLE et REVE : icône du Pokémon.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until
from kanto_tour import log

OPTION_MENU_STYLE = 11   # jeu.options (src/debug_tools.c)


def read_mail(game, item, what):
    reply = game.dev("joueur.lettre", 0, names.number(item), 1)
    expect(game, "lecture ouverte" in reply, f"lettre {item} ouverte ({reply.strip()})")
    game.wait(90); log(game, what)
    game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=600)
    game.wait(30)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.wait(30)
    read_mail(game, "ITEM_ORANGE_MAIL", "orange hoenn")
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    read_mail(game, "ITEM_ORANGE_MAIL", "orange kanto")
    read_mail(game, "ITEM_BEAD_MAIL", "perle kanto")
    read_mail(game, "ITEM_WOOD_MAIL", "bois kanto")
    log(game, "carte")
