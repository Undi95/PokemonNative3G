# Éclosion d'un œuf (egg_hatch.c d'Émeraude) avec les deux options POKéMON : sprites d'Émeraude (animation du
# Pokémon, en y 75) ; sprites de Rouge Feu (2026-11-02 : comme CB2_EggHatch_1 de RF, le cri seul et son attente,
# Pokémon en y 70 + son y_offset). Œuf préparé par l'outil joueur.oeuf, éclosion par le script EventScript_EggHatch.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, wait_text, wait_until
from kanto_tour import log
from kanto_card_stickers import press_until_text

OPTION_MON_SPRITES = 14   # jeu.options (src/debug_tools.c)


def hatch(game, what):
    reply = game.dev("joueur.oeuf", 0)
    expect(game, "pret a eclore" in reply, f"œuf prêt ({reply.strip()})")
    game.var("VAR_0x8004", 0)
    since = mark(game)
    game.script("EventScript_EggHatch")
    wait_text(game, "Hein", since, limit=600)
    press_until_text(game, "vient de sortir", since)   # A ferme « Hein? », l'éclosion ignore les suivants
    game.wait(20); log(game, what)
    finish_dialog(game, answers={"surnom": "B"})


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 5)
    game.wait(30)
    hatch(game, "pikachu hoenn")
    game.dev("jeu.options", OPTION_MON_SPRITES, 1)
    hatch(game, "pikachu kanto")
    expect_sound(game, "MUS_EVOLVED")
