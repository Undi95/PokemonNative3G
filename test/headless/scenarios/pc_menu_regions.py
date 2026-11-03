# Menu du PC des Centres Pokémon dans les deux régions (docs/A-TESTER.md, 2026-11-03 ; CreatePCMultichoice de
# script_menu.c, data/scripts/pc.inc) : à Kanto, PC de LÉO, PC du joueur, PC du PROF. CHEN (Pokédex reçu), PANTHEON
# (Ligue de Kanto finie), DECONNEXION ; à Hoenn, PC de ANNETTE ou de ???, PC du joueur, PANTHEON (Ligue de Hoenn finie),
# DECONNEXION. PANTHEON ouvre le Panthéon de la région (RF : KantoCB2_InitHofPC, Émeraude : CB2_DoHallOfFamePC),
# captures « pantheon-REGION ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts, menu_block, press_until_free

PCS = {"kanto": ("ViridianCity_PokemonCenter_1F", (11, 2)), "hoenn": ("OldaleTown_PokemonCenter_1F", (10, 2))}
HOF_SCREENS = {"kanto": "KantoCB2_InitHofPC", "hoenn": "CB2_DoHallOfFamePC"}


def pc_menu(game, region):
    """Allume le PC : les entrées du menu (textes de sa fenêtre)."""
    place, spot = PCS[region]
    game.warp(place, *spot); game.wait(30)
    finish_dialog(game, settle=20)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A")
    for _ in range(10):
        game.wait(40)
        if any(t == "DECONNEXION" for _, t in texts(game, since)):
            break
        game.tap("A")
    game.wait(30)
    # CreatePCMultichoice écrit d'abord les entrées 3 et suivantes, puis les deux PC du haut
    index, count = menu_block(game, since, "DECONNEXION")
    shown = [t for _, t in texts(game, since)]
    end = shown.index("DECONNEXION")
    return shown[end + 1:end + 3] + shown[end - index:end + 1], since


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    game.flag("FLAG_SYS_GAME_CLEAR", 1)
    for region in ("kanto", "hoenn"):
        entries, since = pc_menu(game, region)
        game.note(f"PC {region} : {entries}")
        expect(game, "PANTHEON" in entries and entries[-1] == "DECONNEXION", f"PC de {region} : {entries}")
        expect(game, ("PC du PROF. CHEN" in entries) == (region == "kanto"), f"PC du PROF. CHEN à Kanto seulement")
        frame = game.frames
        game.tap("DOWN", entries.index("PANTHEON"), gap=12); game.wait(10)
        game.tap("A")
        for _ in range(30):
            game.wait(20)
            if any(f >= frame and name == HOF_SCREENS[region] for f, name in game.cb2s):
                break
        game.wait(200)
        game.shot(f"pantheon-{region}")
        opened = [name for f, name in game.cb2s if f >= frame]
        game.note(f"PANTHEON {region} : {opened}")
        expect(game, HOF_SCREENS[region] in opened, f"PANTHEON de {region} : {HOF_SCREENS[region]} ({opened})")
        for i in range(20):                     # (le Panthéon d'Émeraude ne se ferme qu'avec A)
            if game.state.free:
                break
            game.tap("AB"[i % 2]); game.wait(60)
        press_until_free(game)
