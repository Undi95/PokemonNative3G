# Écran titre laissé sans toucher : à la fin de sa musique, retour au copyright puis à l'intro, puis à l'écran titre.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120)   # passe l'intro -> écran titre
    for i in range(16):
        game.wait(600); log(game, "t%d" % i)

    # Vérifications
    expect_song(game, "MUS_TITLE")
    expect(game, any("AfterTitleScreen" in line for line in open(game.journal.name, encoding="utf-8")), "retour au copyright après l'écran titre")
    expect_song(game, "MUS_RG_INTRO_FIGHT", 6000)
