# Build KANTO_DEBUG=1 : objets du debug, Route 104 (Hoenn), CHERCH'OBJET depuis le sac : celui de Rouge Feu dans tout
# le jeu (2026-10-31 ; flèches vers l'objet caché, Super Potion en 7,6).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from redleaf_acro import close_menus
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    game.warp("Route104", 7, 9); game.wait(30); log(game, "Route 104")
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    game.tap("RIGHT", 4, gap=40); game.wait(60)
    game.tap("UP", 60, gap=4); game.tap("DOWN", 2, gap=8); game.wait(30); log(game, "curseur")
    game.tap("A"); game.wait(60); game.tap("A")
    rf_arrows = False   # tâche des flèches du Cherch'Objet de RF (celui d'Émeraude fait tourner le joueur)
    for _ in range(75):
        game.wait(2)
        rf_arrows |= any("ItemfinderResponseSoundsAndAnims" in game.function(t) for t in game.state.tasks)
    log(game, "utilisé")
    game.wait(150)
    for _ in range(12):
        if game.state.free:
            break
        game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free); log(game, "fini")

    # Vérifications
    expect_map(game, "Route104")
    expect_text(game, "CHERCH’OBJET est sélectionné")
    expect_text(game, "L’appareil réagit")
    expect(game, rf_arrows, "flèches du Cherch'Objet de RF")
