# Démonstration du vieil homme de Jadielle avec SAC = KANTO : le sac de démonstration de Rouge Feu (InitOldManBag,
# Task_Bag_OldManTutorial) : une POTION et une POKé BALL, deux changements de poche (SE_RG_BAG_POCKET), la POKé BALL
# choisie (SE_SELECT), puis la capture de l'ASPICOT ; le sac du joueur est rendu. Avant : le sac de Wally d'Émeraude.
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.dev("jeu.options", 13, 1)              # SAC = KANTO
    game.dev("jeu.rencontres", 0)
    game.flag("FLAG_KANTO_BADGE01_GET", 0)
    game.var("VAR_KANTO_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN", 1)    # colis remis : il attend à côté de la route (21, 8)
    game.give_mon("SPECIES_BULBASAUR", 5)       # la sauvegarde de test n'a pas d'équipe ; à ce moment du jeu, si
    balls = game.item("ITEM_POKE_BALL")
    game.warp("ViridianCity", 21, 10)
    game.press("UP", 16)                        # (21, 9), face à lui
    game.tap("A", gap=30)

    frame, bag_shot = game.frames, False
    for _ in range(3000):
        s = game.state
        if s.free and game.frames - frame > 120:
            break
        screen = game.function(s.cb2)
        if not bag_shot and "Bag" in screen:
            game.wait(330)                      # les deux poches (102, 204), puis le menu de la POKé BALL (306)
            check_screen(game, "kanto_old_man_bag-sac")
            bag_shot = True
        elif s.battle or "Bag" in screen:
            game.wait(10)                       # combat simulé : on regarde
        else:
            game.tap("A", gap=20)
    expect(game, bag_shot, "le sac de démonstration s'ouvre")
    expect_sound(game, "SE_RG_BAG_POCKET", frame)
    expect_battle(game, foe="SPECIES_WEEDLE", outcome="CAUGHT")
    expect(game, game.item("ITEM_POKE_BALL") == balls, "le sac du joueur est rendu (ses POKé BALLS)")
