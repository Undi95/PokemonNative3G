# Capture avec l'équipe pleine (docs/A-TESTER.md, 2026-11-03) : le message de transfert nomme le PC de la région
# (Fusion_GetPCOwner, B_PC_CREATOR_NAME) : à Kanto celui de LÉO (FLAG_KANTO_SYS_NOT_SOMEONES_PC), à Hoenn celui
# d'ANNETTE (FLAG_SYS_PC_LANETTE). MASTER BALL sur le 1er POKéMON sauvage, surnom refusé.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

OPTION_BAG = 13
PLACES = (("Route1", 12, 9, "LEO"), ("Route101", 13, 2, "ANNETTE"))     # (des herbes hautes, deux cases de haut)


def catch(game, place, x, y):
    game.warp(place, x, y); game.wait(30)
    game.dev("jeu.hasard", 4)
    since = mark(game)
    for i in range(120):
        if game.state.battle:
            break
        game.press("UP" if i % 2 else "DOWN", 16)
    wait_text(game, "sauvage", since=since, limit=900)
    for _ in range(20):
        if saw_text(game, "Que doit faire", since):
            break
        game.tap("A"); game.wait(40)
    game.wait(30)
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)      # SAC
    game.tap("RIGHT", 2, gap=90); game.wait(60)                          # Balls : MASTER BALL
    game.tap("A"); game.wait(60); game.tap("A")
    for _ in range(60):
        if game.state.free:
            break
        dialogue = [t for w, t in texts(game, since) if w == 0]
        game.tap("B" if dialogue and "surnom" in dialogue[-1] else "A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=1200)
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 70)
    for _ in range(5):
        game.give_mon("SPECIES_RATTATA", 5)
    game.item("ITEM_MASTER_BALL", 5)
    game.dev("jeu.options", OPTION_BAG, 1)
    game.flag("FLAG_KANTO_SYS_NOT_SOMEONES_PC", 1)
    game.flag("FLAG_SYS_PC_LANETTE", 1)
    for place, x, y, owner in PLACES:
        said = catch(game, place, x, y)
        game.note(f"CAPTURE {place} : {said[-220:]}")
        expect(game, "transféré" in said and owner in said.upper().replace("É", "E"),
               f"{place} : transfert sur le PC de {owner} ({said[-150:]})")
