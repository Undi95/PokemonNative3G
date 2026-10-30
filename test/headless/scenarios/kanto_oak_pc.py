# Build KANTO_DEBUG=1 : DEBUG > Débloquer les 2 POKéDEX (151 vus, 76 attrapés), téléport JADIELLE, Centre Pokémon,
# PC : « PC du PROF. CHEN » entre le PC du joueur et DECONNEXION, note du Pokédex de Kanto par Chen.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 6, gap=10); game.tap("A"); game.wait(60)
    game.tap("B"); game.wait(30); game.tap("B"); wait_until(game, lambda s: s.free)
    debug_warp(game, 1); log(game, "Jadielle")
    game.tap("UP", hold=16); game.wait(200); wait_until(game, lambda s: s.free); log(game, "Centre")
    game.tap("UP", 4, hold=16, gap=4); game.tap("RIGHT", 4, hold=16, gap=4); game.tap("UP", 2, hold=16, gap=4)
    game.wait(30); game.tap("UP"); game.wait(30); log(game, "devant le PC")
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(120); log(game, "menu PC")
    game.tap("DOWN", 2, gap=20); game.wait(30); game.tap("A"); game.wait(120); log(game, "PC de Chen")
    for _ in range(12):
        game.tap("A"); game.wait(90)
    log(game, "note")
    for _ in range(20):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    log(game, "fini")

    # Vérifications
    expect_text(game, "Connexion au PC du PROF. CHEN")
    expect_text(game, "151 POKéMON vus et 76 POKéMON pris")
    expect_text(game, "tu devrais aller pêcher plus")
