# Légendaires de Kanto (docs/A-TESTER.md, 2026-11-03) : l'IA de RF (BattleAI_SetupFlags, BATTLE_TYPE_LEGENDARY_FRLG :
# AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY = 0x7) contre ÉLECTHOR (Centrale),
# SULFURA (Mont Braise), ARTIKODIN (Îles Écume) et MEWTWO (Caverne Azurée) ; un POKéMON sauvage ordinaire n'a pas
# d'IA (0). Le combat lancé, le joueur fuit (impossible : il est perdu) ou le gagne.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import crawl

LEGENDARIES = (("PowerPlant", (5, 11), "FLAG_KANTO_HIDE_ZAPDOS"), ("MtEmber_Summit", (9, 6), "FLAG_KANTO_HIDE_MOLTRES"),
               ("SeafoamIslands_B4F", (9, 2), "FLAG_KANTO_HIDE_ARTICUNO"),
               ("CeruleanCave_B1F", (7, 12), "FLAG_KANTO_HIDE_MEWTWO"))


def ai_flags(game):
    for _ in range(60):
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    game.wait(300)
    found = re.search(r"ia (0x[0-9a-f]+|0)", game.dev("combat.etat"))
    return int(found.group(1), 16) if found else None


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    found = {}
    for place, (x, y), flag in LEGENDARIES:
        game.flag(flag, 0)
        for sx, sy, direction in crawl.spots(place, x, y):
            game.warp(place, sx, sy); game.wait(30)
            finish_dialog(game, settle=20)
            if game.state.pos == (sx, sy):
                break
        talk_to(game, direction, finish=False)
        found[place] = ai_flags(game)
        game.note(f"IA {place} : {found[place]}")
        fight_battle(game, limit=6000)
        finish_dialog(game)
    # Un sauvage ordinaire (Route 1)
    game.warp("Route1", 12, 9); game.wait(30)
    game.dev("jeu.hasard", 4)
    for i in range(80):
        if game.state.battle:
            break
        game.press("UP" if i % 2 else "DOWN", 16)
    wild = ai_flags(game)
    game.note(f"IA sauvage : {wild}")
    fight_battle(game, limit=6000)

    for place, flags in found.items():
        expect(game, flags == 0x7, f"{place} : IA de RF des légendaires 0x7 ({flags})")
    expect(game, wild == 0, f"sauvage ordinaire : pas d'IA ({wild})")
