# PC qui s'allume et s'éteint, vendeurs des Boutiques de Kanto (2026-11-03, docs/A-TESTER.md) :
# - PC du Centre Pokémon de Jadielle (11, 1) et PC de la chambre du joueur à Bourg Palette (1, 1) : la métatuile change
#   à l'allumage (menu ouvert) et revient en l'éteignant ;
# - les 13 Boutiques de Kanto et des Îles Sevii : le vendeur (2, 3), derrière le comptoir, ouvre la boutique (ACHETER).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

MARTS = ("ViridianCity", "PewterCity", "CeruleanCity", "VermilionCity", "LavenderTown", "SaffronCity", "FuchsiaCity",
         "CinnabarIsland", "ThreeIsland", "FourIsland", "SixIsland", "SevenIsland")
# Les autres vendeurs (carte, case du vendeur) : grand magasin de Céladopole, Plateau Indigo, Île 2, Tour des Dresseurs
OTHER_CLERKS = (("CeladonCity_DepartmentStore_2F", (1, 8)), ("CeladonCity_DepartmentStore_2F", (1, 6)),
                ("CeladonCity_DepartmentStore_4F", (3, 13)), ("CeladonCity_DepartmentStore_5F", (1, 7)),
                ("CeladonCity_DepartmentStore_5F", (1, 6)), ("IndigoPlateau_PokemonCenter_1F", (0, 7)),
                ("TwoIsland", (28, 4)), ("TrainerTower_Lobby", (14, 9)))
SIDES = (("LEFT", 1, 0), ("RIGHT", -1, 0), ("UP", 0, 1), ("DOWN", 0, -1))


def other_clerk(game, map_name, pos):
    """Essaie les cases autour du vendeur (à côté, puis de l'autre côté d'un comptoir) jusqu'à ce qu'il parle."""
    for distance in (1, 2):
        for face, dx, dy in SIDES:
            spot = (pos[0] + dx * distance, pos[1] + dy * distance)
            game.warp(map_name, *spot); game.wait(40)
            wait_until(game, lambda s: s.free)
            if game.state.pos != spot:
                continue
            game.press(face, 1); game.wait(20)
            since = mark(game)
            game.tap("A"); game.wait(150)
            shown = " ".join(t for _, t in texts(game, since))
            for _ in range(20):
                if game.state.free:
                    break
                game.tap("B"); game.wait(40)
            if shown:
                return shown
    return ""


def metatile(game, x, y):
    return game.dev("carte.metatuiles", x, y, 1, 1).split("metatuile ")[1].split()[0]


def pc(game, map_name, spot, pc_pos):
    game.warp(map_name, *spot); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 1); game.wait(20)
    off = metatile(game, *pc_pos)
    sounds = len(game.sounds)
    game.tap("A"); game.wait(90)
    on = metatile(game, *pc_pos)
    for _ in range(20):
        if game.state.free:
            break
        game.tap("B"); game.wait(40)
    game.wait(30)
    after = metatile(game, *pc_pos)
    played = [s for _, s in game.sounds[sounds:]]
    game.note(f"PC {map_name} : {off} -> {on} -> {after} {played}")
    return off, on, after, played


def clerk(game, mart):
    game.warp(f"{mart}_Mart", 4, 3); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("LEFT", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(150)
    shown = " ".join(t for _, t in texts(game, since))
    for _ in range(20):
        if game.state.free:
            break
        game.tap("B"); game.wait(40)
    return shown


def play(game):
    continue_game(game)
    for map_name, spot, pc_pos in (("ViridianCity_PokemonCenter_1F", (11, 2), (11, 1)),
                                   ("PalletTown_PlayersHouse_2F", (1, 2), (1, 1))):
        off, on, after, played = pc(game, map_name, spot, pc_pos)
        expect(game, on != off, f"{map_name} : le PC s'allume ({off} -> {on})")
        expect(game, after == off, f"{map_name} : le PC s'éteint ({on} -> {after})")
        expect(game, "SE_PC_ON" in played and "SE_PC_OFF" in played, f"{map_name} : sons du PC ({played})")
    # Jadielle : COLIS de CHEN déjà livré (la scène de la boutique, faite pour un joueur qui entre par la porte, ne
    # se joue pas ; avant la livraison, le vendeur dit de saluer CHEN au lieu de vendre)
    game.var("VAR_KANTO_MAP_SCENE_VIRIDIAN_CITY_MART", 2)
    for mart in MARTS:
        shown = clerk(game, mart)
        expect(game, "ACHETER" in shown, f"{mart} : le vendeur ouvre la boutique ({shown[:90]})")
    game.flag("FLAG_SYS_GAME_CLEAR", 1)                 # Tour des Dresseurs : après la Ligue
    for map_name, pos in OTHER_CLERKS:
        shown = other_clerk(game, map_name, pos)
        game.note(f"{map_name} {pos} : {shown[:120]}")
        expect(game, "ACHETER" in shown or "bienvenue" in shown.lower() or "aider" in shown,
               f"{map_name} {pos} : le vendeur parle ({shown[:90]})")
