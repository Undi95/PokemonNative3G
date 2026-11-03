# Jetons cachés du Casino de Céladopole (docs/A-TESTER.md, 2026-11-03 ; EventScript_TryPickUpHiddenCoins de RF) : les
# 10 jetons cachés en (2, 4), sans BOITE JETONS (« rien pour les ranger », rien n'est pris), avec une BOITE JETONS qui
# ne peut pas les contenir (9 995 jetons : « pleine », rien n'est pris), puis juste assez de place (9 989 : 9 999).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re

FLAG = "FLAG_KANTO_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS"


def coins(game):
    return int(re.search(r"(\d+)", game.dev("joueur.jetons")).group(1))


def search(game):
    """Face aux jetons cachés, A : les textes jusqu'au retour du joueur."""
    game.warp("CeladonCity_GameCorner", 2, 5); game.wait(30)
    since = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "JETONS", since)
    finish_dialog(game)
    return " ".join(" ".join(t.split()) for _, _, t in game.texts[since:])


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_GOT_COIN_CASE", 1)

    # Sans BOITE JETONS
    game.item("ITEM_COIN_CASE", 0)
    game.dev("joueur.jetons", 0)
    text = search(game)
    expect(game, "trouve 10 JETONS" in text and "rien pour les ranger" in text, f"sans BOITE JETONS ({text})")
    expect(game, coins(game) == 0, f"aucun jeton pris ({coins(game)})")
    expect_flag(game, FLAG, 0)

    # BOITE JETONS sans la place
    game.item("ITEM_COIN_CASE", 1)
    game.dev("joueur.jetons", 9995)
    text = search(game)
    expect(game, "trouve 10 JETONS" in text and "est pleine" in text, f"BOITE JETONS pleine ({text})")
    expect(game, coins(game) == 9995, f"aucun jeton pris ({coins(game)})")
    expect_flag(game, FLAG, 0)

    # Juste la place : 9 989 + 10 = 9 999
    game.dev("joueur.jetons", 9989)
    text = search(game)
    expect(game, "trouve 10 JETONS" in text and "pleine" not in text, f"10 jetons rangés ({text})")
    expect(game, coins(game) == 9999, f"9 999 jetons ({coins(game)})")
    expect_flag(game, FLAG, 1)
