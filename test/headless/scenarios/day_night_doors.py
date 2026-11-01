# Build KANTO_DEBUG=1 : animation des portes la nuit (cycle jour/nuit, day_night.c / field_door.c). On entre dans
# un Centre Pokémon de Hoenn et de Kanto, au Parc Safari et au Centre Spatial à 23 h, puis on ressort : une capture
# toutes les 3 images pendant l'ouverture et la fermeture, dans shots/ (la vitre de la porte doit rester allumée).
from driver import *  # les vérifications (expect...)
from driver import wait_until

DOORS = (   # carte, porte (x, y)
    ("OldaleTown", 6, 16),
    ("ViridianCity", 26, 26),
    ("FuchsiaCity", 28, 16),
    ("MossdeepCity", 64, 15),
)


def film(game, name, button, frames=60, skip=0):
    game.press(button, 3)
    game.wait(skip)   # sortie : le fondu de l'intérieur, puis l'arrivée dehors
    for i in range(frames // 3):
        game.shot(f"{name}_{i:02d}")
        game.press(button if i < 4 and not skip else "-", 3)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.command("clock", 23, 0)
    game.command("daynight", 1)
    for name, x, y in DOORS:
        game.warp(name, x, y + 1); game.wait(70)
        film(game, f"{name}_entree", "UP")
        wait_until(game, lambda s: s.free, limit=600); game.wait(30)
        film(game, f"{name}_sortie", "DOWN", skip=40)
        wait_until(game, lambda s: s.free, limit=600)
    game.command("daynight", 0)
