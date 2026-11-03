# POKé MONTURE (fusion : à la place des CS de Kanto, data/scripts/fusion_poke_monture.inc), les 7 dons
# (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto » : là où RF donnait une CS, le 1er don donne la POKé MONTURE,
# les suivants lui ajoutent une capacité ; chaque fois le flag de RF (FLAG_KANTO_GOT_HM0x) est posé.
# Capitaine du S.S. Anne (COUPE), Route 16 (VOL), Parc Safari (SURF), gardien de Parmanie avec la DENT D'OR (FORCE),
# assistant de la Route 2 avec assez de Pokémon (FLASH), Source Braise (ÉCLATE-ROC), puce de la Grotte de Glace
# (CASCADE).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_until
from kanto_tour import log
from menu_helpers import texts

GIFTS = [   # carte, PNJ, flag posé, capacité
    ("SSAnne_CaptainsOffice", (5, 4), "FLAG_KANTO_GOT_HM01", "COUPE"),
    ("Route16_House", (4, 2), "FLAG_KANTO_GOT_HM02", "VOL"),
    ("KantoSafariZone_SecretHouse", (6, 5), "FLAG_KANTO_GOT_HM03", "SURF"),
    ("FuchsiaCity_WardensHouse", (3, 5), "FLAG_KANTO_GOT_HM04", "FORCE"),
    ("Route2_EastBuilding", (4, 6), "FLAG_KANTO_GOT_HM05", "FLASH"),
    ("OneIsland_KindleRoad_EmberSpa", (10, 5), "FLAG_KANTO_GOT_HM06", "ECLATE-ROC"),
    ("FourIsland_IcefallCave_1F", (12, 16), "FLAG_KANTO_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_HM07", "CASCADE"),
]
SIDES = (("UP", 0, 1), ("RIGHT", -1, 0), ("LEFT", 1, 0), ("DOWN", 0, -1))


def talk_to_npc(game, place, npc):
    """Se place à côté du PNJ (d'abord en dessous), lui parle, A partout (OUI aux questions)."""
    for direction, dx, dy in SIDES:
        spot = (npc[0] + dx, npc[1] + dy)
        game.warp(place, *spot); game.wait(40)
        if game.state.pos == spot:
            break
    wait_until(game, lambda s: s.free)
    game.press(direction, 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    finish_dialog(game)
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 30)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_KANTO_HIDE_SAFARI_ZONE_WEST_GOLD_TEETH", 1)   # DENT D'OR ramassée
    game.dev("jeu.debug", 11)                                      # POKéDEX de Kanto complet (assistant de la Route 2)
    results = []
    for place, npc, flag, move in GIFTS:
        said = talk_to_npc(game, place, npc)
        log(game, move)
        results.append((place, move, str(game.flag(flag)).strip() in ("1", "True"), said))
    game.note("dons : " + " ; ".join(f"{p} {m} {f}" for p, m, f, _ in results))

    # Vérifications
    first = results[0][3]
    expect(game, "reçoit" in first and "POKé MONTURE" in first, f"1er don : la POKé MONTURE ({first[-120:]})")
    for place, move, flagged, said in results:
        expect(game, flagged and move in said.replace("ÉCLATE", "ECLATE"),
               f"{place} : {move} ajoutée à la POKé MONTURE ({said[-90:]})")
    expect_item(game, "ITEM_POKE_MONTURE", 1)
