# Build KANTO_DEBUG=1 : MEWTWO, Repaire Rocket B1F : le sbire (24, 12) repère le joueur. Comme dans Rouge Feu français
# (pokemon.c, Localize_BattleStrings ; 2026-11-02), nom et classe sont échangés dans les messages du combat :
# « SBIRE TEAM ROCKET » (avant : « TEAM ROCKET SBIRE »), comme Émeraude pour les TEAM MAGMA et AQUA.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import saw_text, wait_text, wait_until
from kanto_tour import give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    game.warp("RocketHideout_B1F", 22, 13); game.wait(30)
    game.tap("UP", hold=2, gap=10); game.press("UP", 16)      # dans le champ du sbire (portée 2, tourné à gauche)
    for _ in range(60):                                       # « T'es qui ? … »
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    wait_text(game, "Un combat est lancé", since=0, limit=900)
    game.wait(240); log(game, "annonce")
    for _ in range(30):
        if saw_text(game, "est envoyé par"):
            break
        game.tap("A"); game.wait(30)
    game.wait(160); log(game, "envoi")
    for _ in range(200):
        if game.state.free:
            break
        game.tap("A"); game.wait(30)
    wait_until(game, lambda s: s.free)

    # Vérifications
    expect_battle(game, trainer="TRAINER_KANTO_TEAM_ROCKET_GRUNT_8", outcome="WON")
    expect_text(game, "par SBIRE TEAM ROCKET")
    expect_text(game, "envoyé par SBIRE TEAM ROCKET")
    expect_no_text(game, "TEAM ROCKET SBIRE")
