# POKéFLUTE de RF (2026-11-03, docs/A-TESTER.md ; ItemUseOutOfBattle_PokeFlute, BattleScript_UsePokeFlute) :
# - sur le terrain, depuis le sac : les POKéMON endormis de l'équipe se réveillent (fanfare, « La POKéFLUTE a réveillé
#   le POKéMON endormi. »), même avec ANTI-BRUIT (RF réveille toute l'équipe hors combat) ;
# - en combat, depuis les Objets rares : le POKéMON endormi se réveille (« … réveillé »), sauf avec ANTI-BRUIT
#   (M. MIME) : rien, « Super!!! Ça c'est de la musique! ». Avant le 2026-11-03, le combat se bloquait après le réveil
#   (updatestatusicon BS_PLAYER2 : « tous les combattants » dans RF, le 2e du joueur dans Émeraude).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import wild_battle, wait_action_menu, pick, bag, texts
from region_maps import key_item_from_bag

ASLEEP = 7          # STATUS1_SLEEP : 7 tours


def status(game, slot):
    return int(game.dev("joueur.statut", slot).split("statut")[1], 16)


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def flute_in_battle(game):
    """SAC (de RF) > Objets rares > POKéFLUTE > UTILIS. ; les textes jusqu'au menu suivant, puis FUITE."""
    wait_action_menu(game)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    index = next(i for i, n in enumerate(keys) if n.startswith("POKéFLUTE"))
    since = mark(game)
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)
    for _ in range(4):                                  # le sac s'ouvre sur la dernière poche : jusqu'aux Objets rares
        pockets = [t for window, t in texts(game, since) if window == 2]
        if pockets and pockets[-1] == "OBJ. RARES":
            break
        game.tap("LEFT"); game.wait(90)
    game.tap("UP", 12, gap=10); game.wait(20)
    if index:
        game.tap("DOWN", index, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS."); game.wait(120)
    wait_action_menu(game, since)
    text = said(game, since)
    game.tap("DOWN"); game.wait(10); game.tap("RIGHT"); game.wait(10); game.tap("A")       # FUITE
    for _ in range(40):
        if not game.state.battle:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=900)
    return text


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO (objets rares dans la 2e poche)
    game.item("ITEM_POKE_FLUTE", 1)
    game.give_mon("SPECIES_PIKACHU", 30)               # 0
    game.give_mon("SPECIES_MR_MIME", 40)               # 1 : ANTI-BRUIT

    # Sur le terrain : les deux se réveillent
    game.dev("joueur.statut", 0, ASLEEP)
    game.dev("joueur.statut", 1, ASLEEP)
    game.warp("PalletTown", 10, 9); game.wait(30)
    since = mark(game)
    key_item_from_bag(game, "POKéFLUTE")
    wait_text(game, "a réveillé", since, limit=900)
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=900)
    field = said(game, since)
    expect(game, "Vous jouez de la POKéFLUTE" in field and "a réveillé" in field,
           f"terrain : la POKéFLUTE réveille ({field[-90:]})")
    expect(game, status(game, 0) == 0 and status(game, 1) == 0,
           f"terrain : PIKACHU et M. MIME réveillés ({status(game, 0):#x}, {status(game, 1):#x})")

    # En combat : PIKACHU endormi, réveillé
    game.dev("joueur.statut", 0, ASLEEP)
    wild_battle(game)
    text = flute_in_battle(game)
    expect(game, "réveille" in text and "de la musique" not in text, f"combat : PIKACHU se réveille ({text[-100:]})")
    expect(game, status(game, 0) == 0, f"combat : PIKACHU réveillé après le combat ({status(game, 0):#x})")

    # En combat : M. MIME (ANTI-BRUIT) endormi en tête (PIKACHU K.O.), il dort toujours
    game.dev("joueur.pv", 0, 0)
    game.dev("joueur.statut", 1, ASLEEP)
    wild_battle(game)
    text = flute_in_battle(game)
    expect(game, "de la musique" in text and "réveill" not in text,
           f"combat : ANTI-BRUIT, M. MIME n'entend rien ({text[-100:]})")
    expect(game, status(game, 1) != 0, f"combat : M. MIME dort toujours ({status(game, 1):#x})")
