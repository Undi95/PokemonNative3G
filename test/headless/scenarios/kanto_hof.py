# Build KANTO_DEBUG=1 : téléport DEBUG au Panthéon de Kanto, enregistrement (moniteur RF),
# Panthéon puis crédits de Kanto (musique continue : --audio).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    game.wait(30); game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 24); game.tap("A"); game.wait(200); log(game, "Panthéon")
    for _ in range(300):
        game.tap("A", gap=60)
    log(game, "fin")

    # Vérifications
    expect_text(game, "Bienvenue au PANTHEON")
    expect_flag(game, "FLAG_KANTO_SYS_GAME_CLEAR")
    expect_song(game, "MUS_RG_HALL_OF_FAME")    # MUS_HALL_OF_FAME de RF (celui d'Émeraude : le Panthéon de Hoenn)
    expect_song(game, "MUS_RG_CREDITS")
    expect_map(game, "PalletTown")
