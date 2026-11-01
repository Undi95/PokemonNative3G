# Build KANTO_DEBUG=1 : animation des portes la nuit (cycle jour/nuit, day_night.c / field_door.c). On entre à 23 h
# par une porte de chaque animation (Hoenn et Kanto), puis on ressort : une capture toutes les 3 images pendant
# l'ouverture et la fermeture, dans shots/ (la vitre de la porte reste allumée, l'ouverture et le sol non).
from driver import *  # les vérifications (expect...)
from driver import wait_until

DOORS = (   # carte, porte (x, y) : une porte de chaque animation des villes et routes
    ("BattleFrontier_OutsideEast", 16, 14),
    ("BattleFrontier_OutsideEast", 39, 29),
    ("BattleFrontier_OutsideEast", 4, 44),
    ("BattleFrontier_OutsideEast", 10, 28),
    ("BattleFrontier_OutsideEast", 3, 51),
    ("BattleFrontier_OutsideWest", 19, 17),
    ("BattleFrontier_OutsideWest", 11, 38),
    ("BattleFrontier_OutsideWest", 51, 51),
    ("CeladonCity", 34, 21),
    ("CeladonCity", 11, 14),
    ("CeladonCity", 30, 11),
    ("CeladonCity", 48, 11),
    ("CeruleanCity", 10, 11),
    ("CinnabarIsland", 8, 9),
    ("DewfordTown", 3, 3),
    ("DewfordTown", 8, 17),
    ("EverGrandeCity", 18, 5),
    ("FallarborTown", 8, 7),
    ("FallarborTown", 6, 17),
    ("FiveIsland", 12, 6),
    ("FourIsland", 12, 13),
    ("FuchsiaCity", 24, 5),
    ("FuchsiaCity", 28, 16),
    ("LavaridgeTown", 12, 15),
    ("LavenderTown", 10, 11),
    ("LilycoveCity", 27, 6),
    ("LilycoveCity", 37, 24),
    ("LilycoveCity", 23, 24),
    ("LilycoveCity", 39, 14),
    ("LittlerootTown", 14, 8),
    ("LittlerootTown", 7, 16),
    ("MauvilleCity", 35, 5),
    ("MossdeepCity", 28, 9),
    ("MossdeepCity", 64, 15),
    ("OldaleTown", 5, 7),
    ("OldaleTown", 6, 16),
    ("OneIsland", 19, 9),
    ("PacifidlogTown", 16, 13),
    ("PalletTown", 6, 7),
    ("PalletTown", 16, 13),
    ("PewterCity", 25, 4),
    ("Route110", 15, 16),
    ("Route113", 33, 5),
    ("Route121", 37, 5),
    ("RustboroCity", 13, 30),
    ("RustboroCity", 33, 19),
    ("SaffronCity", 33, 30),
    ("SaffronCity", 22, 14),
    ("SevenIsland", 11, 9),
    ("SlateportCity", 5, 19),
    ("SootopolisCity", 9, 6),
    ("SootopolisCity", 45, 6),
    ("VerdanturfTown", 10, 14),
    ("VermilionCity", 9, 6),
    ("ViridianCity", 25, 11),
    ("ViridianCity", 26, 26),
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
    game.var("VAR_KANTO_MAP_SCENE_FOUR_ISLAND", 1)   # pas de rival à l'arrivée
    for name, x, y in DOORS:
        game.warp(name, x, y + 1); game.wait(70)
        name = f"{name}_{x}_{y}"
        film(game, f"{name}_entree", "UP")
        wait_until(game, lambda s: s.free, limit=600); game.wait(30)
        film(game, f"{name}_sortie", "DOWN", frames=90, skip=40)
        wait_until(game, lambda s: s.free, limit=600)
    game.command("daynight", 0)
