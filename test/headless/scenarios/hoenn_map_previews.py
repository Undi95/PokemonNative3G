# Aperçus de lieu de RF à Hoenn (v1.1, 2026-11-04, demande user : « l'image qui s'affiche comme à Kanto à l'entrée
# d'une zone ou d'un donjon ») : les entrées MPS_HOENN_* de sMapPreviewScreenData (src/kanto_map_preview_screen.c),
# avec une image de RF qui ne montre pas un lieu unique. Pour chacun, entrée depuis la carte voisine : l'aperçu
# s'affiche avec le nom de Hoenn (table d'Émeraude), 120 images à la première visite (drapeau du lieu posé par le
# script de transition de la carte d'entrée : setworldmapflag ou FLAG_LANDMARK_*), puis, pour une grotte, le panneau
# d'Émeraude ; une forêt n'a pas de panneau, comme dans RF. Captures « LIEU » (aperçu) à revoir.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_map_previews import TASKS, enter, entrance, free, map_infos, previews, running
from kanto_tour import log

# La Grotte Terra n'a pas d'entrée fixe (warp dynamique) : une de ses entrées de la Route 114
TERRA_CAVE = ("TerraCave_Entrance", 8, 18, "Route114", 6, 46)
# Le nom écrit dans l'aperçu (GetMapName d'Émeraude)
NAMES = {"MAPSEC_PETALBURG_WOODS": "BOIS CLEMENTI", "MAPSEC_SAFARI_ZONE": "PARC SAFARI",
         "MAPSEC_RUSTURF_TUNNEL": "TUNNEL MERAZON", "MAPSEC_GRANITE_CAVE": "GROTTE GRANITE",
         "MAPSEC_METEOR_FALLS": "SITE METEORE", "MAPSEC_FIERY_PATH": "CHEMIN ARDENT",
         "MAPSEC_SHOAL_CAVE": "GROTTE TREFONDS", "MAPSEC_CAVE_OF_ORIGIN": "GROTTE ORIGINE",
         "MAPSEC_VICTORY_ROAD": "ROUTE VICTOIRE", "MAPSEC_SCORCHED_SLAB": "GROTTE ZENITH",
         "MAPSEC_ALTERING_CAVE": "GROTTE METAMO", "MAPSEC_ARTISAN_CAVE": "GROTTE ATELIER",
         "MAPSEC_TERRA_CAVE": "GROTTE TERRA"}
POPUP_EM = "Task_MapNamePopUpWindow"   # le panneau d'Émeraude (map_name_popup.c)


def popup_after(game, limit=200):
    """Après l'arrivée : le panneau d'Émeraude vient-il ?"""
    for _ in range(0, limit, 2):
        if running(game, POPUP_EM):
            return True
        game.wait(2)
    return False


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.rencontres", 0)
    infos = map_infos()
    table = previews("hoenn")
    expect(game, len(table) == len(NAMES), f"{len(NAMES)} lieux de Hoenn à aperçu ({len(table)})")

    # Chaque lieu à sa première visite (drapeau remis à zéro) : aperçu de 120 images, le nom de Hoenn
    long_frames = {}
    for mapsec, kind, flag in table:
        place = TERRA_CAVE if mapsec == "MAPSEC_TERRA_CAVE" else entrance(infos, mapsec)
        game.flag(flag, 0)
        frames, written = enter(game, place, TASKS[kind], shot=mapsec[7:].lower())
        popup = popup_after(game)
        game.note(f"APERÇU {mapsec} ({kind[9:].lower()}) : {place[0]} depuis {place[3]}, {frames} images, "
                  f"nom {written}, panneau d'Émeraude {popup}")
        expect(game, any(NAMES[mapsec] in t for t in written), f"{mapsec} : nom {NAMES[mapsec]} ({written})")
        expect(game, game.flag(flag) == 1, f"{mapsec} : lieu visité ({flag})")
        # Grotte : le panneau d'Émeraude après l'aperçu ; forêt : l'aperçu tient lieu de panneau (RF)
        expect(game, popup == (kind == "MPS_TYPE_CAVE"), f"{mapsec} : panneau d'Émeraude {popup}")
        long_frames[mapsec] = frames

    # Deuxième visite : 40 images au lieu de 120, grotte (drapeau) et forêt (sHasVisitedMapBefore)
    for mapsec, kind in (("MAPSEC_GRANITE_CAVE", "MPS_TYPE_CAVE"), ("MAPSEC_PETALBURG_WOODS", "MPS_TYPE_FOREST")):
        frames, _ = enter(game, entrance(infos, mapsec), TASKS[kind])
        game.note(f"2e VISITE {mapsec} : {frames} images (1re : {long_frames[mapsec]})")
        expect(game, 70 <= long_frames[mapsec] - frames <= 90, f"{mapsec} : 80 images de moins à la 2e visite "
               f"({long_frames[mapsec]} → {frames})")

    # À pied, par l'entrée de la Grotte Granite (Route 106) : le vrai chemin du joueur
    free(game)
    enter(game, entrance(infos, "MAPSEC_GRANITE_CAVE"), TASKS["MPS_TYPE_CAVE"], walk=True)
    expect(game, popup_after(game), "Grotte Granite à pied : le panneau d'Émeraude après l'aperçu")
