# Panneau du nom de lieu (choix user 2026-11-02) : à Kanto, celui de Rouge Feu (kanto_map_name_popup.c : boîte au cadre
# standard qui glisse en haut à gauche, étage des cartes : floor_number réimporté) ; à Hoenn, celui d'Émeraude (bois).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until
from kanto_tour import log


def arrive(game, map_name, x, y, words, what):
    since = mark(game)
    game.warp(map_name, x, y)
    game.note("CARTE " + game.dev("carte.info").splitlines()[1])
    wait_until(game, lambda s: saw_text(game, words, since), limit=300)
    game.wait(40); log(game, what)   # la boîte a fini de glisser (2 px par image)
    game.wait(200)                   # elle repart


def play(game):
    continue_game(game)
    game.wait(240)
    arrive(game, "ViridianCity", 24, 27, "JADIELLE", "ville kanto")
    arrive(game, "SilphCo_5F", 20, 3, "SYLPHE SARL 4", "sylphe 5")   # RF en français : RC, 1ᵉʳ, 2ᵉ… (5F = 4ᵉ)
    arrive(game, "CeladonCity_DepartmentStore_Roof", 10, 6, "TOIT", "toit")
    # D'une autre section, le Repaire Rocket ouvre son aperçu (titre), sans panneau, comme RF ; puis, de B1F à B2F
    # (même section), le panneau avec l'étage
    arrive(game, "RocketHideout_B1F", 20, 10, "REPAIRE ROCKET", "apercu repaire")
    arrive(game, "RocketHideout_B2F", 20, 10, "2 SS", "repaire 2 sous-sol")
    # Chambre de Tanoby encore fermée : la carte est assombrie (WEATHER_SHADE), le panneau reste blanc comme dans RF
    # (la palette BG 13 échappe à la météo à Kanto, field_weather.c)
    game.flag("FLAG_KANTO_SYS_UNLOCKED_TANOBY_RUINS", 0)
    arrive(game, "SevenIsland_TanobyRuins_MoneanChamber", 11, 14, "CHAMBRE", "chambre tanoby fermee")
    arrive(game, "OldaleTown", 5, 10, "ROSYERES", "ville hoenn")
