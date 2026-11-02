# Le RAMOLOSS de Parmanie (36, 15) erre en marchant lentement : MOVEMENT_TYPE_WANDER_AROUND_SLOWER de Rouge Feu
# (MovementType_WanderAround_Step5Slower : marche lente, 1 pixel toutes les 2 images = 32 images par case). Avant :
# MOVEMENT_TYPE_WANDER_AROUND (16 images par case).
import re

from driver import *

FIXTURE = "kanto"
SLOWER = 0x54   # MOVEMENT_TYPE_WANDER_AROUND_SLOWER


def slowpoke(game):
    """(x, y, type de mouvement) du RAMOLOSS, d'après carte.objets."""
    for line in game.dev("carte.objets").splitlines():
        m = re.search(r"en (-?\d+),(-?\d+) mouvement (\d+)", line)
        if m and int(m.group(3)) == SLOWER:
            return int(m.group(1)), int(m.group(2)), int(m.group(3))
    return None


def play(game):
    continue_game(game)
    game.dev("jeu.rencontres", 0)
    game.warp("FuchsiaCity", 34, 18)
    found = slowpoke(game)
    expect(game, found is not None, "un objet de Parmanie a le mouvement WANDER_AROUND_SLOWER (le RAMOLOSS)")
    if not found:
        return
    # Ses pas : l'image où sa case change ; une marche lente met 32 images, une marche normale 16
    changes, last = [], found[:2]
    for _ in range(1500):
        game.wait(2)
        pos = slowpoke(game)[:2]
        if pos != last:
            changes.append(game.frames)
            last = pos
        if len(changes) >= 3:
            break
    expect(game, len(changes) >= 2, f"le RAMOLOSS se déplace ({len(changes)} pas vus)")
