# Pente de la Piste Cyclable (Route 17, MB_CYCLING_ROAD_PULL_DOWN de RF ; 2026-11-03, docs/A-TESTER.md ;
# MovePlayerOnCyclingRoadSlope) : à vélo, sans rien toucher on descend tout seul (vite), B retenu freine (on reste sur
# place), une direction fait avancer normalement ; VELO COURSE et VELO CROSS. Les herbes de la pente
# (MB_CYCLING_ROAD_PULL_DOWN_GRASS) ont des rencontres.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re
import driver
import names


def route17_trainers_beaten(game):
    """Les motards de la Route 17 déjà battus : sinon l'un repère le joueur pendant la glissade (commandes bloquées)."""
    path = os.path.join(os.path.dirname(driver.__file__), "..", "..", "data", "kanto", "data", "scripts", "trainers.inc")
    trainers = re.findall(r"Route17_EventScript_\w+::\n\ttrainerbattle\w* (TRAINER_\w+)", open(path, encoding="utf-8").read())
    for trainer in trainers:
        # Dresseurs de Kanto : leurs drapeaux sont dans le bloc Kanto (TrainerFlag, battle_setup.c)
        game.flag(names.value("KANTO_TRAINER_FLAGS_START") + names.value(trainer) - names.value("KANTO_TRAINERS_START"), 1)
    return trainers

START = (3, 40)      # colonne de pente continue (en x = 8, un obstacle arrête la descente à la rangée 43)


def ride(game, bike, spot=START):
    """Monte à vélo sur la pente en retenant B (sinon on glisse aussitôt : le joueur n'est jamais « libre »)."""
    game.warp("Route17", *spot); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.dev("joueur.enregistre", names.number(bike))
    game.tap("SELECT", hold=4)
    game.press("B", 40)


def moved(game, buttons, frames):
    before = game.state.pos
    game.press(buttons, frames)
    return game.state.pos[1] - before[1]


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.item("ITEM_MACH_BIKE", 1)
    game.item("ITEM_ACRO_BIKE", 1)
    game.dev("jeu.rencontres", 0)                       # pas de combat pendant les mesures
    expect(game, len(route17_trainers_beaten(game)) >= 10, "les 10 dresseurs de la Route 17 marqués battus")

    for bike in ("ITEM_MACH_BIKE", "ITEM_ACRO_BIKE"):
        ride(game, bike)
        braked = moved(game, "B", 60)
        alone = moved(game, "-", 60)
        game.press("B", 16)                              # finir le pas en cours, arrêté
        up_braked = moved(game, "UP+B", 64)
        up = moved(game, "UP", 64)
        game.note(f"{bike} : seul {alone:+d}, B {braked:+d}, HAUT+B {up_braked:+d}, HAUT {up:+d}")
        expect(game, alone >= 8, f"{bike} : sans rien toucher, on descend vite ({alone:+d} cases en 60 images)")
        expect(game, braked == 0, f"{bike} : B retenu freine ({braked:+d})")
        expect(game, up_braked <= -3 and up <= -3,
               f"{bike} : HAUT fait monter, avec ou sans B ({up_braked:+d}, {up:+d} cases en 64 images)")

    # Les herbes de la pente : des rencontres
    game.dev("jeu.rencontres", 1)
    ride(game, "ITEM_MACH_BIKE", (17, 10))
    for i in range(40):
        if game.state.battle:
            break
        game.warp("Route17", 17 + i % 3, 10); game.wait(10)
        game.dev("joueur.enregistre", names.number("ITEM_MACH_BIKE"))
        if not game.state.battle:
            game.tap("SELECT", hold=4); game.wait(20)
        game.press("-", 40)
        game.wait(100)                                   # une rencontre met ~90 images à passer en combat
    expect(game, game.state.battle or bool(game.battles), f"herbe de la pente : une rencontre ({game.battles[-1:]})")
