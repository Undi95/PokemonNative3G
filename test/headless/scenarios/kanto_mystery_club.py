# Club Événement Mystère de Kanto (2026-11-03, docs/A-TESTER.md ; data/kanto/data/scripts/mystery_event_club.inc) :
# la dame du Centre d'Argenta demande le profil (OUI), l'écran Easy Chat s'ouvre ; une fois le profil écrit, elle le
# répète (special ShowEasyChatMessage de RF = ShowEasyChatProfile d'Émeraude) puis « Ton profil en dit vraiment long » ;
# une 2e fois, « J'espère en apprendre plus » ; en revenant (le profil enregistré), « On se retrouve encore! ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

LADY = ("PewterCity_PokemonCenter_1F", 13, 3)     # la dame est en (13, 2)


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)                      # texte rapide
    game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE", 0)
    game.warp(*LADY); game.wait(30)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    for _ in range(30):                               # ses pages, OUI, jusqu'à « Quel est ton profil? »
        if saw_text(game, "Quel est ton profil", since):
            break
        game.tap("A", gap=40)
    game.wait(40)
    game.tap("A", gap=20)                             # fermer le message : l'écran du profil s'ouvre (sans autre A)
    wait_text(game, "PROFIL", since, limit=600)
    game.wait(60)
    for _ in range(3):                                # le 1er mot du 1er groupe
        game.tap("A", gap=40)
        game.wait(20)
    ok = mark(game)
    game.tap("START", gap=30)
    for _ in range(4):
        if saw_text(game, "OK?", ok):
            break
        game.tap("A", gap=30)
    wait_text(game, "OK?", ok, limit=300)
    game.wait(30)
    after = mark(game)
    game.tap("A", gap=20)                             # OUI
    finish_dialog(game, limit=200)
    repeated = said(game, after)
    game.note(f"après le profil : {repeated}")
    expect_flag(game, "FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE", 1)
    expect(game, "en dit vraiment long" in repeated, f"elle répète le profil, puis son avis ({repeated[-100:]})")
    words = repeated.split("Mmmh")[0].strip()
    expect(game, len(words) >= 3, f"le profil répété avant son avis ({words})")

    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "en apprendre plus", since), f"une 2e fois : « J'espère en apprendre plus » ({said(game, since)})")
    game.warp(*LADY); game.wait(30)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    wait_text(game, "On se retrouve encore", since)
    finish_dialog(game, answers={"changer ton profil": "B"})
