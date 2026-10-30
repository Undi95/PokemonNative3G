# Panneaux de Rouge Feu (2026-10-30) : un panneau s'ouvre quand on marche vers lui et se ferme quand on s'éloigne ;
# enseigne du Centre Pokémon de Jadielle (tuile MB_POKEMON_CENTER_SIGN) ; avec Options > DIALOGUE = KANTO, cadre
# « panneau » de RF et texte bleu (homme) / rouge (femme) des PNJ de Kanto.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, talk_to_object, wait_text, wait_until
from kanto_dotted_hole_rf import set_dialog_kanto
from kanto_tour import log


def walk_into(game, direction):
    """Se tourne puis marche vers le panneau (sans A)."""
    game.tap(direction); game.wait(10)
    game.press(direction, 30)


def play(game):
    continue_game(game)

    # Bourg Palette : panneau de la ville (9, 11) en marchant vers lui
    game.warp("PalletTown", 9, 12); game.wait(30)
    since_town = mark(game)
    walk_into(game, "UP")
    wait_text(game, "BOURG PALETTE", since_town)
    game.wait(90)
    expect(game, not game.state.free, "message du panneau ouvert sans A")
    log(game, "panneau")
    game.press("DOWN", 4)   # s'éloigner ferme le message
    wait_until(game, lambda s: s.free, limit=120)
    expect(game, game.state.free, "message fermé en s'éloignant")
    game.wait(30)

    # Jadielle : enseigne du Centre Pokémon (tuiles 24-25, 26), en marchant vers elle puis avec A
    game.warp("ViridianCity", 24, 27); game.wait(30)
    since = mark(game)
    walk_into(game, "UP")
    wait_text(game, "CENTRE POKéMON", since)
    finish_dialog(game)
    since_a = mark(game)
    game.tap("A"); wait_text(game, "CENTRE POKéMON", since_a)   # aussi avec A, face à l'enseigne
    finish_dialog(game)
    game.warp("ViridianCity", 35, 20); game.wait(30)
    since_mart = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "BOUTIQUE POKéMON", since_mart)
    finish_dialog(game)

    # Options > DIALOGUE = KANTO : cadre « panneau » et couleur des PNJ
    set_dialog_kanto(game)
    game.warp("PalletTown", 9, 12); game.wait(30)
    since_rf = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "BOURG PALETTE", since_rf)
    game.wait(120); log(game, "panneau RF")
    finish_dialog(game)
    since_npc = mark(game)
    talk_to_object(game, *game.state.objects[0], finish=False)
    game.wait(120); log(game, "PNJ RF")
    finish_dialog(game)

    # Vérifications
    expect_text(game, "BOURG PALETTE", since_town)
    expect_text(game, "Soignez vos POKéMON", 0)
    expect_text(game, "Faites le plein", since_mart)
    expect(game, any(win == 0 for _, win, _ in game.texts[since_npc:]), "le PNJ a parlé")
