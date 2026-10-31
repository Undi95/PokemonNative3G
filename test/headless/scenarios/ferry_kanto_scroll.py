# Build KANTO_DEBUG=1 : port de Nénucrique avec toutes les destinations (ZONE DE COMBAT, KANTO et les quatre billets
# d'événement) : plus de 6 choix, menu défilant (2026-10-31, textes selon les destinations ouvertes). On descend jusqu'à
# KANTO (3e ligne), texte du marin, puis NON : retour au menu, et on annule.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, talk_to, mark, finish_dialog, saw_text

FLAGS = ["FLAG_MET_SCOTT_ON_SS_TIDAL",
         "FLAG_ENABLE_SHIP_SOUTHERN_ISLAND", "FLAG_SHOWN_EON_TICKET",
         "FLAG_ENABLE_SHIP_NAVEL_ROCK", "FLAG_SHOWN_MYSTIC_TICKET",
         "FLAG_ENABLE_SHIP_BIRTH_ISLAND", "FLAG_SHOWN_AURORA_TICKET",
         "FLAG_ENABLE_SHIP_FARAWAY_ISLAND", "FLAG_SHOWN_OLD_SEA_MAP"]
ITEMS = ["ITEM_EON_TICKET", "ITEM_MYSTIC_TICKET", "ITEM_AURORA_TICKET", "ITEM_OLD_SEA_MAP"]


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    for flag in FLAGS:
        game.flag(flag, 1)
    for item in ITEMS:
        game.item(item, 1)
    debug_warp(game, 36)

    since = mark(game)
    talk_to(game, "UP", finish=False)
    for _ in range(40):
        if any(t.strip() == "KANTO" for _, w, t in game.texts[since:] if w != 0):
            break
        game.tap("A", hold=2, gap=10)
    game.wait(40); log(game, "menu défilant")
    game.tap("DOWN", 2, gap=12); game.wait(20); log(game, "sur KANTO")
    game.tap("A"); game.wait(30)
    finish_dialog(game, answers={"le voyage d": "B", "souhaiteriez-vous aller": "B"})
    log(game, "annulé")

    # Vérifications
    expect(game, saw_text(game, "personne ne connaît", since=since), "texte du marin pour KANTO")
    expect(game, saw_text(game, "souhaiteriez-vous aller", since=since), "retour au menu")
    expect(game, saw_text(game, "Revenez une autre fois", since=since), "annulation")
    expect_flag(game, "FLAG_FUSION_KANTO_VISITED", 0)
    expect_map(game, "LilycoveCity_Harbor")
