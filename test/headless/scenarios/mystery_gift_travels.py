# Traversées des CARTES MYSTÈRE (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », Ligue de Hoenn finie :
# - Carmin sur Mer, ferry Seagallop (menu de RF, TICKET MYSTIK et TICKET AURORA) : ROC NOMBRI, puis retour à Carmin
#   par le marin de l'île (choix de RF) ; ILE AURORE, retour à Carmin ;
# - Nénucrique, S.S. TIDAL (TICKET AURORA, TICKET MYSTIK, VIEILLE CARTE) : ILE LOINTAINE (scène de M. MARCO la
#   1re fois), ILE AURORE, ROC NOMBRI, chaque fois retour à Nénucrique par le marin d'Émeraude.
# Les deux ports mènent aux mêmes cartes d'Émeraude (kanto_seagallop.c) : les légendaires des îles (drapeaux
# partagés) n'apparaissent qu'une fois, quel que soit le port de départ.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import pick, script_waits_button, texts


def sail(game, face, label, limit=60, cursor=0):
    """Parle au marin (face : direction), A jusqu'au menu qui propose label, le choisit ; puis A jusqu'à l'arrivée
    sur une autre carte. Rend la carte d'arrivée et les textes."""
    wait_until(game, lambda s: s.free)
    start = game.state.map_name
    game.press(face, 2); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    chosen = False
    answered = None
    for _ in range(limit * 5):
        if game.state.map_name != start:
            break
        shown = [t for _, t in texts(game, since)]     # une entrée de menu : le libellé seul
        if not chosen and label in shown:
            game.wait(30)
            pick(game, since, label, cursor=cursor)
            chosen = True
            game.wait(60)
            continue
        # A seulement sur un message qui attend (▼, ou waitbuttonpress d'un msgbox) ou un OUI / NON, une fois
        # chacun : un A de trop validerait un menu
        waiting = shown and (shown[-1].endswith("▼") or shown[-1] == "OUI NON")
        if (waiting and answered != len(game.texts)) or script_waits_button(game):
            answered = len(game.texts)
            game.wait(20)
            game.tap("A")
        game.wait(10)
    wait_until(game, lambda s: s.free and s.map_name != start, limit=3000)
    game.wait(30)
    return game.state.map_name, " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_GAME_CLEAR", 1)
    for item in ("ITEM_MYSTIC_TICKET", "ITEM_AURORA_TICKET", "ITEM_OLD_SEA_MAP"):
        game.item(item, 1)
    for flag in ("FLAG_KANTO_ENABLE_SHIP_NAVEL_ROCK", "FLAG_KANTO_ENABLE_SHIP_BIRTH_ISLAND",
                 "FLAG_ENABLE_SHIP_NAVEL_ROCK", "FLAG_ENABLE_SHIP_BIRTH_ISLAND", "FLAG_ENABLE_SHIP_FARAWAY_ISLAND"):
        game.flag(flag, 1)
    game.var("VAR_KANTO_MAP_SCENE_VERMILION_CITY", 3)
    game.var("VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F", 5)   # RAINBOW PASS

    trips = []
    # Carmin sur Mer
    for label in ("ROC NOMBRI", "ILE AURORE"):
        game.warp("VermilionCity", 24, 32); game.wait(60)
        there, said = sail(game, "DOWN", label)
        log(game, f"carmin {label}")
        back, said_back = sail(game, "DOWN", "CARMIN SUR MER")
        trips.append(("Carmin", label, there, back, game.flag("FLAG_ISLAND_TRIP_FROM_KANTO")))
    # Nénucrique (la 1re fois, la VIEILLE CARTE lance la scène de M. MARCO : départ direct pour l'ILE LOINTAINE)
    for label in ("ILE LOINTAINE", "ILE AURORE", "ROC NOMBRI"):
        game.warp("LilycoveCity_Harbor", 8, 11); game.wait(60)
        there, said = sail(game, "UP", label, cursor="last")   # S.S. TIDAL : curseur sur la dernière ligne
        log(game, f"nenucrique {label}")
        back, said_back = sail(game, "DOWN", "OUI")
        trips.append(("Nénucrique", label, there, back, game.flag("FLAG_ISLAND_TRIP_FROM_KANTO")))
    game.note("traversées : " + " ; ".join(str(t) for t in trips))

    # Vérifications
    arrivals = {"ROC NOMBRI": "NavelRock_Harbor", "ILE AURORE": "BirthIsland_Harbor", "ILE LOINTAINE": "FarawayIsland_Entrance"}
    homes = {"Carmin": "VermilionCity", "Nénucrique": "LilycoveCity_Harbor"}
    for port, label, there, back, trip_flag in trips:
        expect(game, there == arrivals[label] and back == homes[port] and str(trip_flag).strip() in ("0", "False"),
               f"{port} -> {label} : {there}, retour : {back}")
