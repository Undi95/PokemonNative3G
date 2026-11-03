# Celebi et Jirachi de la fusion, cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », MEWTWO N.100 :
# - Celebi (autel de la Forêt Baies) : avant la Ligue de Kanto, l'autel seul ; ensuite CELEBI apparaît, fuite
#   (il revient à la visite suivante), capture à la MASTER BALL, puis l'autel est silencieux ; l'autel avec Red ;
# - Jirachi (Chutes Météore) : météorite absente avant les Ligues ; flash spécial à la TV de Hoenn une seule fois ;
#   sans POKé FLÛTE, le texte d'explication ; avec, combat, fuite (il se rendort), capture.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from kanto_tour import log
from menu_helpers import wait_action_menu, texts


def talk_up(game):
    wait_until(game, lambda s: s.free)
    since = mark(game)
    game.tap("A"); game.wait(40)
    return since


def until_free_or_battle(game, yes=True, limit=40):
    for _ in range(limit):
        if game.state.battle or game.state.free:
            break
        game.tap("A"); game.wait(50)


def battle(game, action):
    """Le combat légendaire : FUITE, ou MASTER BALL (sac de RF : POKé BALLS = 3e poche)."""
    wait_until(game, lambda s: s.battle, limit=900)
    wait_action_menu(game)
    if action == "fuite":
        game.tap("DOWN"); game.wait(10); game.tap("RIGHT"); game.wait(10); game.tap("A")
    else:
        game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)
        game.tap("RIGHT", 2, gap=90); game.wait(60)
        game.tap("A"); game.wait(60); game.tap("A"); game.wait(400)
    for _ in range(60):
        if not game.state.battle:
            break
        game.tap("B"); game.wait(40)
    finish_dialog(game, answers={"surnom": "B"})


def party_species(game):
    return [int(s) for s in re.findall(r"espece (\d+)", game.dev("joueur.equipe"))]


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.give_mon("SPECIES_MEWTWO", 100)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.item("ITEM_MASTER_BALL", 2)

    # --- Celebi ---
    game.flag("FLAG_SYS_GAME_CLEAR", 1)
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 0)
    game.warp("ThreeIsland_BerryForest", 45, 6); game.wait(60)
    game.press("UP", 2); game.wait(20)
    since = talk_up(game); finish_dialog(game)
    shrine_before = texts(game, since)
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    since = talk_up(game); until_free_or_battle(game)
    battle(game, "fuite")
    ran = (texts(game, since), game.flag("FLAG_CAUGHT_CELEBI"), game.flag("FLAG_DEFEATED_CELEBI"))
    since = talk_up(game); until_free_or_battle(game)
    came_back = game.state.battle
    battle(game, "balle")
    caught_celebi = game.flag("FLAG_CAUGHT_CELEBI")
    since = talk_up(game); finish_dialog(game)
    shrine_after = texts(game, since)
    game.dev("jeu.options", 6, 1)                      # PERSO = RED/LEAF : l'autel (dessin maison) avec Red
    game.warp("ThreeIsland_BerryForest", 45, 6); game.wait(90)
    log(game, "autel avec Red")
    game.dev("jeu.options", 6, 0)

    # --- Jirachi ---
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 0)
    game.warp("MeteorFalls_B1F_2R", 7, 4); game.wait(60)
    meteorite_before = "7,3" in game.dev("carte.objets")
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    since = mark(game)
    game.script("EventScript_TV"); finish_dialog(game)
    tv_first = texts(game, since)
    since = mark(game)
    game.script("EventScript_TV"); finish_dialog(game)
    tv_second = texts(game, since)
    game.warp("MeteorFalls_B1F_2R", 7, 4); game.wait(60)
    meteorite_after = "en 7,3" in game.dev("carte.objets")
    game.press("UP", 2); game.wait(20)
    since = talk_up(game); finish_dialog(game)
    no_flute = texts(game, since)
    log(game, "meteorite")
    game.item("ITEM_POKE_FLUTE", 1)
    since = talk_up(game); until_free_or_battle(game)
    battle(game, "fuite")
    asleep = texts(game, since)
    since = talk_up(game); until_free_or_battle(game)
    battle(game, "balle")
    caught_jirachi = game.flag("FLAG_CAUGHT_JIRACHI")
    since = talk_up(game); finish_dialog(game)
    dull = texts(game, since)
    species = party_species(game)

    # Vérifications
    joined = lambda shown: " ".join(t for _, t in shown)
    expect(game, "autel en bois" in joined(shrine_before), f"Celebi : autel seul avant la Ligue de Kanto ({joined(shrine_before)[-60:]})")
    expect(game, "CELEBI" in joined(ran[0]) and not ran[1] and not ran[2] and came_back,
           f"Celebi : fuite, il revient ({joined(ran[0])[-60:]})")
    expect(game, caught_celebi and names.number("SPECIES_CELEBI") in species, "Celebi capturé")
    expect(game, "autel en bois" in joined(shrine_after), "Celebi : autel silencieux après la capture")
    expect(game, not meteorite_before and meteorite_after, f"météorite absente avant les Ligues ({meteorite_before}, {meteorite_after})")
    expect(game, "FLASH SPÉCIAL" in joined(tv_first) and "FLASH SPÉCIAL" not in joined(tv_second),
           f"TV : flash spécial une seule fois ({joined(tv_second)[:60]})")
    expect(game, "POKé FLÛTE" in joined(no_flute) or "mélodie" in joined(no_flute),
           f"sans POKé FLÛTE : explication ({joined(no_flute)[-80:]})")
    expect(game, caught_jirachi and names.number("SPECIES_JIRACHI") in species, f"Jirachi : fuite ({joined(asleep)[-50:]}) puis capture")
    expect(game, "ne brille plus" in joined(dull), "météorite éteinte après la capture")
