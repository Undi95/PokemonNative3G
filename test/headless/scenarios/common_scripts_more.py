# Scripts communs aux deux régions, à Kanto (docs/A-TESTER.md, 2026-11-03) :
# - rochers des Îles Écume : FORCE, le rocher (32, 9) du 1er étage poussé deux fois à gauche puis vers le haut tombe
#   dans le trou (30, 8) (HandleBoulderFallThroughHole de RF : SE_FALL, il disparaît) ;
# - PC coupé à la première arrivée sur l'ÎLE 1 (FLAG_KANTO_SYS_PC_STORAGE_DISABLED), puis rétabli ;
# - infirmière de Kanto (Jadielle) : Pokérus annoncé, Carte Or (4 étoiles de la carte de Hoenn : Panthéon, Pokédex,
#   tableaux du musée, symboles de la Zone de Combat).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def nurse(game):
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    finish_dialog(game, limit=300)
    return said(game, since)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.dev("joueur.capacite", 0, 0, names.value("MOVE_STRENGTH"))
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1)
    game.dev("jeu.rencontres", 0)                       # pas de combat sauvage pendant les poussées

    # Îles Écume : le rocher 2 dans le trou
    game.warp("SeafoamIslands_1F", 33, 9); game.wait(30)
    finish_dialog(game, settle=20)
    game.press("LEFT", 1); game.wait(20)
    game.tap("A"); game.wait(60)
    finish_dialog(game); game.wait(30)                  # « FORCE? » OUI
    for target in ((31, 9), (30, 9)):                   # deux poussées à gauche (chacune attend la fin de la 1re)
        for _ in range(4):
            if target in [o[:2] for o in game.state.objects]:
                break
            game.press("LEFT", 16); game.wait(40)
    walk_to(game, 30, 10, live=True)                    # sous le rocher
    sounds = len(game.sounds)
    game.press("UP", 16); game.wait(90)
    played = [s for _, s in game.sounds[sounds:]]
    objects = [o[:2] for o in game.state.objects]
    game.note(f"ÉCUME : joueur {game.state.pos}, sons {played}, objets {objects}")
    expect(game, "SE_FALL" in played and (30, 8) not in objects and (30, 9) not in objects,
           f"le rocher tombe dans le trou ({played}, {objects})")

    # Île 1 : PC coupé, puis rétabli
    game.flag("FLAG_KANTO_SYS_PC_STORAGE_DISABLED", 1)
    game.var("VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F", 5)     # (la scène de CILEO déjà vue)
    game.warp("OneIsland_PokemonCenter_1F", 9, 2); game.wait(30)
    finish_dialog(game, settle=20)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    finish_dialog(game)
    off = said(game, since)
    game.flag("FLAG_KANTO_SYS_PC_STORAGE_DISABLED", 0)
    since = mark(game)
    game.tap("A"); game.wait(120)
    on = said(game, since)
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(40)
    game.note(f"PC ÎLE 1 : coupé « {off} » ; rétabli « {on[:80]} »")
    expect(game, "inaccessibles" in off and "inaccessibles" not in on and "PC" in on,
           f"PC coupé puis rétabli ({off} / {on[:60]})")

    # Infirmière de Kanto : Pokérus
    game.flag("FLAG_POKERUS_EXPLAINED", 0)
    game.dev("joueur.pokerus", 0, 0x01)
    text = nurse(game)
    game.note(f"POKéRUS : {text[-200:]}")
    expect(game, "POKéRUS" in text, f"l'infirmière parle du Pokérus ({text[-120:]})")

    # Carte Or : les 4 étoiles de la carte de Hoenn
    game.dev("jeu.stat", names.value("GAME_STAT_ENTERED_HOF"), 1)
    game.dev("jeu.pokedex", 386, 1)
    stars = game.dev("joueur.tableaux", 5)
    for i in range(7):
        game.flag(names.value("FLAG_SYS_TOWER_SILVER") + 2 * i, 1)
        game.flag(names.value("FLAG_SYS_TOWER_GOLD") + 2 * i, 1)
    game.flag("FLAG_NURSE_MENTIONS_GOLD_CARD", 0)
    stars = game.dev("joueur.tableaux")
    text = nurse(game)
    game.note(f"CARTE OR ({stars.strip()}) : {text[:200]}")
    expect(game, "etoiles de la carte de Hoenn 4" in stars, f"4 étoiles ({stars})")
    # gText_WelcomeCutShort : l'infirmière s'interrompt (« Voulez-vous les… »), voit la Carte Or (« ! »)
    expect(game, "Voulez-vous les…" in text, f"Carte Or : l'accueil coupé de l'infirmière ({text[:120]})")
