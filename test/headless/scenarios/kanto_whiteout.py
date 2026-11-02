# K.O. comme dans Rouge Feu, à Hoenn comme à Kanto (2026-10-31) : perte d'argent selon les badges de la région annoncée
# en combat (« panique et perd X¥ ») et égale à celle retirée, reprise devant l'infirmière du dernier Centre visité
# (message sur fond noir, puis soins), Ligue de Kanto et Piste Cyclable remises à zéro. Cases de reprise particulières
# (Ligue de Hoenn, Plateau Indigo) : on y parle bien à l'infirmière. Celle de l'Île 1 (5, 4) vient de RF ; un warp dans
# ce Centre lance la scène de CILEO.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, fight_battle, finish_dialog, mark, talk_to, wait_until
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

SCURRIED = "se hâte vers un CENTRE"
# (carte, case de reprise de heal_locations.json) : l'infirmière est juste au-dessus, derrière le comptoir
SPECIAL_RESPAWNS = (("EverGrandeCity_PokemonLeague_1F", 3, 4),
                    ("IndigoPlateau_PokemonCenter_1F", 13, 12))


def lose_wild_battle(game, map_name, x, y):
    """Va et vient sur (x, y) - (x + 1, y) jusqu'à une rencontre, perdue avec Magicarpe (Trempette)."""
    game.warp(map_name, x, y); game.wait(30)
    game.dev("joueur.pv", 0, 1)   # 1 PV : le premier coup met K.O. (le combat ne dépend plus des tirages)
    for _ in range(150):
        game.press("RIGHT", 16); game.wait(4)
        game.press("LEFT", 16); game.wait(4)
        if game.state.battle:
            break
    since = mark(game)
    money = game.money()
    fight_battle(game)
    return since, money


def lost_money(game, since):
    found = [re.search(r"perd (\d+)¥", t) for _, _w, t in game.texts[since:]]
    found = [int(m.group(1)) for m in found if m]
    return found[0] if found else None


def white_out(game, map_name, x, y, shot=None):
    """K.O. sur (x, y), puis reprise : ce que les vérifications regardent."""
    since, money = lose_wild_battle(game, map_name, x, y)
    seen = {"lost": lost_money(game, since), "money": money, "after": game.money(),
            "respawn": (game.state.map_name, game.state.pos)}
    wait_text(game, SCURRIED, since)
    if shot:
        game.wait(180)   # fin de l'affichage
        log(game, shot)
    finish_dialog(game)   # A : le message se termine sur une attente de touche
    seen["nurse"] = saw_text(game, "Avant toute chose", since) and saw_text(game, "ont été soignés", since)
    seen["facing"] = game.state.facing   # RF : tourné vers l'infirmière (SetInitialPlayerAvatarStateWithDirection)
    return seen


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 2)   # la sauvegarde de test arrive à Kanto sans équipe
    game.money(10000)

    # 1. Hoenn : dernier soin à Clémenti-Ville (celui de la sauvegarde de test), K.O. sur la Route 102
    hoenn = white_out(game, "Route102", 8, 2)

    # 2. Kanto : soins à Jadielle, puis K.O. au Mt. Moon avec la Ligue et la Piste Cyclable en cours
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    talk_to(game, "UP")
    game.flag("FLAG_KANTO_DEFEATED_LORELEI", 1)
    game.flag("FLAG_KANTO_SYS_ON_CYCLING_ROAD", 1)
    kanto = white_out(game, "MtMoon_1F", 21, 2, shot="message de reprise")

    # 3. Cases de reprise particulières
    nurses = {}
    for map_name, x, y in SPECIAL_RESPAWNS:
        game.warp(map_name, x, y); game.wait(30)
        since = mark(game)
        talk_to(game, "UP")
        nurses[map_name] = saw_text(game, "Bienvenue", since)

    # Vérifications
    for region, seen, respawn in (("Hoenn", hoenn, ("PetalburgCity_PokemonCenter_1F", (7, 4))),
                                  ("Kanto", kanto, ("ViridianCity_PokemonCenter_1F", (7, 4)))):
        expect(game, seen["lost"] is not None and seen["lost"] > 0, f"{region} : perte annoncée en combat ({seen['lost']})")
        expect(game, seen["lost"] == seen["money"] - seen["after"],
               f"{region} : perte annoncée = perte réelle ({seen['lost']} / {seen['money']} -> {seen['after']})")
        expect(game, seen["respawn"] == respawn, f"{region} : reprise devant l'infirmière ({seen['respawn']})")
        expect(game, seen["nurse"], f"{region} : message sur fond noir, puis l'infirmière soigne l'équipe")
        expect(game, seen["facing"] == driver.FACING["UP"], f"{region} : tourné vers l'infirmière ({seen['facing']})")
    expect_flag(game, "FLAG_KANTO_DEFEATED_LORELEI", 0)
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 0)
    for map_name, _x, _y in SPECIAL_RESPAWNS:
        expect(game, nurses[map_name], f"case de reprise face à l'infirmière : {map_name}")
