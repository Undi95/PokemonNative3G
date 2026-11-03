# Piste Cyclable de Kanto (2026-11-03, docs/A-TESTER.md), comme dans Rouge Feu :
# - Route 16 avec la Piste en cours (VAR_KANTO_MAP_SCENE_ROUTE16 = 1, posée par le poste) : le joueur arrive à vélo
#   (ForcePlayerOntoBike), FLAG_KANTO_SYS_ON_CYCLING_ROAD est posé, et SELECT (vélo enregistré) refuse qu'il descende ;
# - après un TÉLÉPORT, puis après un K.O., il n'est plus considéré comme sur la Piste (Overworld_ResetKantoStateAfterWarp,
#   le même que pour le Vol et la Corde Sortie) ;
# - portique nord de la Route 16 : sans vélo, le garde renvoie le joueur ; avec le vélo de Hoenn (FLAG_RECEIVED_BIKE), on passe.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, texts

BIKES = 0x06      # PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE


def avatar(game):
    return int(game.dev("carte.info").splitlines()[2].split("avatar ")[1].split(",")[0], 16)


def on_cycling_road(game, spot=(18, 9)):
    game.var("VAR_KANTO_MAP_SCENE_ROUTE16", 1)
    game.warp("Route16", *spot); game.wait(60)
    wait_until(game, lambda s: s.free)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_ABRA", 20)                       # TÉLÉPORT
    game.item("ITEM_MACH_BIKE", 1)
    game.dev("joueur.enregistre", names.number("ITEM_MACH_BIKE"))
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    talk_to(game, "UP")                                     # dernier Centre : Jadielle

    # Sur la Piste : à vélo d'office, impossible d'en descendre
    on_cycling_road(game)
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 1)
    expect(game, avatar(game) & BIKES, f"arrivée à vélo sur la Piste (avatar {avatar(game):#x})")
    since = mark(game)
    game.tap("SELECT", hold=4); game.wait(60)
    refused = " ".join(t for _, t in texts(game, since))
    finish_dialog(game)
    expect(game, avatar(game) & BIKES, f"SELECT : toujours à vélo ({refused[:80]})")
    expect(game, refused != "", f"SELECT : un message de refus ({refused[:80]})")

    # TÉLÉPORT depuis l'équipe
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "TELEPORT")
    finish_dialog(game)
    wait_until(game, lambda s: s.free, limit=900)
    expect_map(game, "ViridianCity")                       # devant le dernier Centre visité
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 0)
    expect_var(game, "VAR_KANTO_MAP_SCENE_ROUTE16", 0)

    # K.O. sur la Piste : herbe de la Route 16 (33..41, 5..7)
    on_cycling_road(game, (36, 6))
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 1)
    game.give_mon("SPECIES_MAGIKARP", 5)                    # TREMPETTE ; ABRA, lui, fuirait par TÉLÉPORT
    game.dev("joueur.pv", 0, 0)
    game.dev("joueur.pv", 1, 1)
    for i in range(200):
        if game.state.battle:
            break
        game.press("LEFT" if i % 2 == 0 else "RIGHT", 8); game.wait(2)
    finish_dialog(game, on_battle=fight_battle)
    expect(game, game.battles and game.battles[-1]["outcome"] == "LOST", f"K.O. ({game.battles[-1:]})")
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 0)
    expect_var(game, "VAR_KANTO_MAP_SCENE_ROUTE16", 0)

    # Portique de la Route 16 : le garde arrête les piétons sans vélo ; le vélo de Hoenn (FLAG_RECEIVED_BIKE) suffit
    for has_bike in (0, 1):
        game.flag("FLAG_RECEIVED_BIKE", has_bike)
        game.warp("Route16_NorthEntrance_1F", 10, 12); game.wait(40)
        wait_until(game, lambda s: s.free)
        since = mark(game)
        game.press("LEFT", 16 * 6)
        finish_dialog(game)
        wait_until(game, lambda s: s.free)
        said = " ".join(t for _, t in texts(game, since))
        if has_bike:
            expect(game, game.state.pos[0] <= 4 and "piétons" not in said,
                   f"portique avec le vélo de Hoenn : passage libre ({game.state.pos}, {said[:60]})")
        else:
            expect(game, game.state.pos[0] >= 7 and "piétons" in said,
                   f"portique sans vélo : le garde renvoie le joueur ({game.state.pos}, {said[:60]})")
