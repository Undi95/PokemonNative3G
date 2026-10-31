# Approche des dresseurs, la même dans tout le jeu (2026-10-31) : un dresseur tourné vers le bas qui repère le joueur
# de loin (approche de plus de 2 pas) est montré par la caméra de Rouge Feu, qui monte jusqu'à lui puis redescend ;
# comme dans Émeraude, le joueur se tourne vers lui avant le combat. Deandre (Route 118, Hoenn) et Kent (Mt. Moon,
# Kanto), portée 4.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import FACING, continue_game, fight_battle, finish_dialog, wait_until
import names
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

# (carte, case du dresseur, case de départ, pas qui entre dans son champ à 4 cases, dresseurs déjà battus, nom)
TRAINERS = (("Route118", (7, 7), (6, 11), "RIGHT", ("TRAINER_ROSE_1",), "Route 118"),  # Rose (7, 12) regarde en haut
            ("MtMoon_1F", (7, 26), (7, 31), "UP", (), "Mt Moon"))


def spotted_from_afar(game, map_name, trainer, start, step, beaten, name):
    """Le joueur entre dans le champ du dresseur à 4 cases. Rend : départ, caméra vue (un objet invisible monte entre
    le joueur et le dresseur), direction du joueur au début du combat."""
    x, y = trainer
    for other in beaten:
        game.flag(names.value("TRAINER_FLAGS_START") + names.value(other), 1)
    game.warp(map_name, *start); game.wait(30)
    start_pos = game.state.pos
    others = set(game.state.objects)
    game.press(step, 16)
    camera = False
    facing = None
    for _ in range(300):
        game.wait(2)
        above = [o for o in game.state.objects if o not in others and o[0] == x and y < o[1] < y + 4]
        if above and not camera:
            camera = True
            game.wait(20)
            log(game, "caméra " + name)
        if game.state.battle:
            break
        facing = game.state.facing
    fight_battle(game)
    finish_dialog(game)
    return start_pos, camera, facing


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)   # la sauvegarde de test arrive à Kanto sans équipe
    seen = {}
    for map_name, trainer, start, step, beaten, name in TRAINERS:
        seen[name] = spotted_from_afar(game, map_name, trainer, start, step, beaten, name)

    # Vérifications
    for map_name, trainer, start, step, beaten, name in TRAINERS:
        start_pos, camera, facing = seen[name]
        expect(game, start_pos == start, f"{name} : départ en {start} ({start_pos})")
        expect(game, camera, f"{name} : la caméra monte jusqu'au dresseur")
        expect(game, facing == FACING["UP"], f"{name} : le joueur se tourne vers le dresseur ({facing})")
