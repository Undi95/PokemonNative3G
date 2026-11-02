# Build KANTO_DEBUG=1 : DEBUG « MEWTWO + KADABRA » (aucune CS) et « POKé MONTURE + badges », téléport JADIELLE :
# COUPE sur l'arbre (INSECATEUR appelé), SURF sur l'étang (LOKHLASS appelé), puis VOL depuis le sac (carte de vol,
# annulée : retour au terrain).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to, finish_dialog


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 14, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 1)
    walk_to(game, 11, 23)
    game.press("DOWN", 1); game.wait(20); game.tap("A"); game.wait(60); log(game, "arbre")
    game.tap("A"); game.wait(40); log(game, "oui")
    for k in range(4):
        game.wait(30); log(game, "coupe %d" % k)
    finish_dialog(game); game.wait(60); log(game, "arbre coupé")
    walk_to(game, 11, 25)
    game.press("DOWN", 1); game.wait(20); game.tap("A"); game.wait(60); log(game, "eau")
    game.tap("A"); game.wait(40)
    for k in range(4):
        game.wait(30); log(game, "surf %d" % k)
    finish_dialog(game); game.wait(60); log(game, "sur l'eau")
    game.press("UP", 1); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("DOWN", 2, gap=10); game.tap("A"); game.wait(200); log(game, "sac")
    game.tap("RIGHT", 4, gap=30); game.wait(30); log(game, "objets rares")
    game.tap("A"); game.wait(40); game.tap("A"); game.wait(240); log(game, "carte de vol")
    game.tap("B"); game.wait(240); log(game, "annulé")

    # Vérifications
    expect_text(game, "KADABRA utilise COUPE")
    expect_text(game, "Voulez-vous utiliser SURF")
    expect_text(game, "POKé MONTURE")
    # Le Surf à Kanto : la musique de RF (MUS_SURF de RF = MUS_RG_SURF), pas celle de Hoenn de même nom d'origine
    expect_song(game, "MUS_RG_SURF")
    expect(game, "MUS_SURF" not in [name for f, name in game.songs], "pas la musique du Surf de Hoenn à Kanto")
