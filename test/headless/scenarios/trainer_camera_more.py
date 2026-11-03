# Caméra des dresseurs de RF (docs/A-TESTER.md, 2026-11-03), les cas de trainer_camera en plus :
# - deux dresseurs qui repèrent le joueur en même temps, chacun à 2 cases (Route 120, Leonel et Angelica) : combat à
#   deux contre un (combat double), captures « deux-N » ;
# - dresseur déguisé en arbre qui repère de loin (Route 120, Riley) : il se révèle et vient, captures « deguise-N ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))


def spotted(game, map_name, start, step, shots):
    """Le joueur entre dans le champ : captures toutes les 10 images jusqu'au combat, puis l'état du combat."""
    game.warp(map_name, *start); game.wait(30)
    finish_dialog(game, settle=20)
    game.press(step, 16)
    for i in range(40):
        game.shot(f"{shots}-{i}")
        if game.state.battle:
            break
        game.wait(10)
        if not game.state.battle and not game.state.free and i % 4 == 3:
            game.tap("A")
    for _ in range(60):
        if game.state.battle:
            break
        game.tap("A"); game.wait(20)
    game.wait(200)
    battle = game.dev("combat.etat").splitlines()[0]
    fight_battle(game, limit=6000)
    finish_dialog(game)
    return battle


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.give_mon("SPECIES_LUGIA", 100)
    for slot in range(2):
        game.dev("joueur.capacite", slot, 0, names.value("MOVE_PSYCHIC"))
    game.dev("jeu.options", 0, 2)                       # texte rapide

    # Deux dresseurs à 2 cases, de chaque côté (Route 120, Leonel et Angelica)
    battle = spotted(game, "Route120", (16, 35), "UP", "deux")
    game.note(f"DEUX DRESSEURS : {battle} ; {game.battles[-1] if game.battles else None}")
    expect(game, "combattants 4" in battle, f"combat à deux contre un ({battle})")

    # Dresseur déguisé en arbre, à 3 cases (Callie, qui regarde la même colonne, déjà battue)
    game.flag(names.value("TRAINER_FLAGS_START") + names.value("TRAINER_CALLIE"), 1)
    battle = spotted(game, "Route120", (18, 31), "RIGHT", "deguise")
    game.note(f"DÉGUISÉ : {battle} ; {game.battles[-1] if game.battles else None}")
    expect(game, "en combat 1" in battle, f"le dresseur déguisé repère le joueur de loin ({battle})")
