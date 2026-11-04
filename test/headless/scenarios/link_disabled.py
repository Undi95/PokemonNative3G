# Link caché (LINK_ENABLED = FALSE, include/config.h ; décision du 2026-11-02 : codé, inaccessible jusqu'à la phase
# multijoueur). Avec le POKéDEX (le test d'avant, qui donne aussi « en préparation »), chaque entrée du link répond
# qu'elle est en réglage (special Fusion_IsLinkEnabled) : à Hoenn (Centre de Rosyères 2F) et à Kanto (Centre de
# Jadielle 2F), l'hôtesse de l'Union Room et celle du coin direct (échanges, combats, mini-jeux) ; à Hoenn, le
# guichet des concours en link et le Mixeur à plusieurs de Nénucrique, et les combats multi en link de la Tour de Combat.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import crawl
from menu_helpers import texts

# (carte, position du PNJ ou du panneau, ce qu'il doit répondre)
ENTRIES = (("OldaleTown_PokemonCenter_2F", (6, 2), "en préparation"),
           ("OldaleTown_PokemonCenter_2F", (10, 2), "en préparation"),
           ("ViridianCity_PokemonCenter_2F", (6, 2), "en préparation"),
           ("ViridianCity_PokemonCenter_2F", (10, 2), "en préparation"),
           ("LilycoveCity_ContestLobby", (15, 2), "des réglages"),
           ("LilycoveCity_ContestLobby", (23, 5), "des réglages"),
           ("BattleFrontier_BattleTowerLobby", (18, 5), "des réglages"))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for place, spot, expected in ENTRIES:
        said = ""
        for sx, sy, direction in crawl.spots(place, *spot):
            game.warp(place, sx, sy); game.wait(30)
            finish_dialog(game, settle=20)
            since = mark(game)
            talk_to(game, direction, finish=False)
            finish_dialog(game, limit=300)
            said = " ".join(t for _, t in texts(game, since))
            if said:
                break
        game.note(f"{place} {spot} : {said[:160]}")
        expect(game, expected in said and game.state.map_name == place,
               f"{place} {spot} : « {expected} » ({said[:100]})")
