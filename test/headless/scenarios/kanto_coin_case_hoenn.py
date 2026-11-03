# Casino de Céladopole avec la BOITE JETONS de Hoenn, sans avoir parlé à l'homme du restaurant (docs/A-TESTER.md,
# 2026-11-03 ; les scripts de RF vérifient l'objet, checkitem ITEM_COIN_CASE, la boîte de Hoenn suffit) :
# jetons cachés ramassés, caissière (50 jetons pour 1 000 ¥), machine à sous (l'écran des machines s'ouvre), salle des
# lots (ABRA contre des jetons).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import crawl
from menu_helpers import texts


def coins(game):
    return int(re.search(r"(\d+)", game.dev("joueur.jetons")).group(1))


def talk(game, place, x, y, answers=None):
    """Parle à ce qui est en (x, y) (personnage ou machine), A jusqu'au retour du joueur : les textes."""
    for sx, sy, direction in crawl.spots(place, x, y):
        game.warp(place, sx, sy); game.wait(30)
        since = mark(game)
        talk_to(game, direction, finish=False)
        if not game.state.free:
            finish_dialog(game, limit=300, answers=answers)
            return " ".join(t for _, t in texts(game, since))
    return ""


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_GOT_COIN_CASE", 0)            # l'homme du restaurant pas vu
    game.item("ITEM_COIN_CASE", 1)                      # la BOITE JETONS (celle de Hoenn)
    game.dev("joueur.jetons", 0)

    # Jetons cachés (2, 4)
    said = talk(game, "CeladonCity_GameCorner", 2, 4)
    expect(game, "trouve 10 JETONS" in said and coins(game) == 10, f"jetons cachés ramassés ({coins(game)} ; {said[:80]})")

    # Caissière : 50 jetons (1er choix)
    money = game.money()
    said = talk(game, "CeladonCity_GameCorner", 6, 2)
    game.note(f"CAISSIÈRE : {said}")
    expect(game, coins(game) == 60 and money - game.money() == 1000, f"50 jetons pour 1 000 ¥ ({coins(game)}, {money - game.money()})")

    # Machine à sous (0, 7) : OUI pour jouer, l'écran des machines
    frame = game.frames
    game.warp("CeladonCity_GameCorner", 1, 7); game.wait(30)
    game.press("LEFT", 1); game.wait(20)
    game.tap("A")
    for _ in range(20):
        game.wait(30)
        if any(f >= frame and "Slot" in name for f, name in game.cb2s):
            break
        game.tap("A")
    game.wait(120)
    game.shot("machine")
    screens = [name for f, name in game.cb2s if f >= frame]
    game.note(f"MACHINE : {screens}")
    expect(game, any("Slot" in name for name in screens), f"l'écran des machines à sous s'ouvre ({screens})")
    for i in range(20):                                 # B : « Quitter la partie? », A : OUI
        if game.state.free:
            break
        since = mark(game)
        game.tap("B"); game.wait(60)
        if saw_text(game, "Quitter la partie", since):
            game.tap("A"); game.wait(120)
    wait_until(game, lambda s: s.free, limit=1200)

    # Salle des lots : ABRA (180 jetons)
    game.dev("joueur.jetons", 9999)
    party = len(game.state.party)
    said = talk(game, "CeladonCity_GameCorner_PrizeRoom", 4, 2, answers={"surnom": "B"})
    game.note(f"LOTS : {said}")
    expect(game, len(game.state.party) == party + 1 and coins(game) == 9999 - 180,
           f"ABRA contre 180 jetons ({len(game.state.party)} POKéMON, {coins(game)} jetons)")
