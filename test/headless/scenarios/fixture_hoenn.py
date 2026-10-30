# Sauvegarde de départ « hoenn » (FIXTURE = "hoenn") : nouvelle partie d'Émeraude (--kanto-start 0), camion,
# maman, l'horloge de la chambre réglée : le joueur est libre dans sa chambre (maison de Brendan, 2F).
from driver import *

SUITE = False
KANTO_START = 0


def play(game):
    new_hoenn_game(game)
    leave_map(game, "RIGHT")                        # sortie du camion : maman
    finish_dialog(game)
    expect_map(game, "LittlerootTown_BrendansHouse_1F")
    take_warp(game, "LittlerootTown_BrendansHouse_2F")
    finish_dialog(game)
    talk_to_object(game, 5, 1, finish=False)        # l'horloge murale
    for _ in range(30):                             # « L'horloge est arrêtée… »
        if "WallClock" in game.function(game.state.cb2):
            break
        game.tap("A", gap=20)
    game.wait(60)
    since = mark(game)
    game.tap("A")                                   # l'heure
    wait_text(game, "Est-ce la bonne heure", since)
    game.wait(30)
    game.tap("UP")
    game.tap("A")                                   # OUI
    finish_dialog(game)                             # maman monte
    expect_flag(game, "FLAG_SET_WALL_CLOCK")
    save(game)
