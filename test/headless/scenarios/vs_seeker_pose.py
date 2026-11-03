# Pose du CHERCHE VS (2026-11-03, docs/A-TESTER.md) : avec RED (option PERSO = KANTO), le joueur lève le CHERCHE VS
# (sprite de RF ; le numéro de sprite était tronqué à 8 bits, corrigé) ; avec BRICE, il se tourne vers le bas (Émeraude
# n'a pas de pose). Captures à regarder : 3 images pendant l'utilisation, pour chaque personnage.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from kanto_vs_seeker_rematch import SPOT, route3_trainers, walk_steps

OPTION_PERSO = 6


def play(game):
    continue_game(game)
    game.dev("jeu.rencontres", 0)
    for trainer in route3_trainers():
        game.flag(names.value("KANTO_TRAINER_FLAGS_START") + names.value(trainer) - names.value("KANTO_TRAINERS_START"), 1)
    game.item("ITEM_VS_SEEKER", 1)
    game.flag("FLAG_KANTO_GOT_VS_SEEKER", 1)
    game.dev("joueur.enregistre", names.number("ITEM_VS_SEEKER"))
    for perso, name in ((0, "brice"), (1, "red")):
        game.dev("jeu.options", OPTION_PERSO, perso)
        game.warp(*SPOT); game.wait(30)
        walk_steps(game, 110)                         # la recharge (100 pas)
        game.warp(*SPOT); game.wait(30)
        wait_until(game, lambda s: s.free)
        game.tap("SELECT", hold=4)
        for step in range(3):
            game.wait(20)
            log(game, f"{name} pose {step + 1}")
        game.wait(30)
        log(game, f"{name} bulles")                  # « !! » (revanche) et « X » (refus) au-dessus des dresseurs
        finish_dialog(game, limit=100)
        game.warp("PewterCity", 10, 30); game.wait(30)   # les dresseurs se calment
