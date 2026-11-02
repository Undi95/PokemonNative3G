# Build KANTO_DEBUG=1 : nouvelle partie à Bourg Palette, scène de CHEN, choix de CARAPUCE au labo
# (sans surnom), puis le premier combat contre le rival (TRAINER_BATTLE_EARLY_RIVAL).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import fight_battle, finish_dialog, wait_until, walk_to
from kanto_tour import log

SEED = int(os.environ.get("KANTO_RIVAL_SEED", "4"))   # une graine où CARAPUCE gagne (jeu.hasard ; 3 et 5 perdent)

def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    walk_to(game, 12, 2); game.tap("UP"); game.wait(20); game.tap("UP"); game.wait(60)
    finish_dialog(game); log(game, "labo")
    walk_to(game, 9, 5); game.tap("UP"); game.wait(20)
    # « Tu veux CARAPUCE ? » : OUI ; ensuite B partout (refuse le surnom)
    for _ in range(12):
        game.tap("A"); game.wait(50)
    for _ in range(300):
        if game.state.free:
            break
        game.tap("B"); game.wait(10)
    log(game, "starter choisi")
    # Le combat CARAPUCE / BULBIZARRE niveau 5 dépend du hasard : graine fixée, la suite ne dépend plus du minutage d'avant
    game.dev("jeu.hasard", SEED)
    walk_to(game, 6, 8, on_battle=fight_battle); log(game, "déclencheur")
    finish_dialog(game); log(game, "après le combat")

    # Vérifications
    expect_party(game, "SPECIES_SQUIRTLE", 6)
    expect_battle(game, trainer="TRAINER_KANTO_RIVAL_OAKS_LAB_BULBASAUR", outcome="WON")
    expect_flag(game, "FLAG_KANTO_BEAT_RIVAL_IN_OAKS_LAB")
    expect_text(game, "BLUE obtient BULBIZARRE")
