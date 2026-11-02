# Option MENUS = KANTO : la fiche de Rouge Feu d'un Pokémon reçu à Hoenn (Bourg-en-Vol) dit où il a été rencontré
# (bug Android du 2026-11-01 : « Rencontré à un échange », RF ne nommait que les lieux de Kanto), et son sprite
# animé d'Émeraude (option POKéMON = HOENN) revient à l'image de repos (détecteur « Pokémon figé »).
from driver import *

FIXTURE = "hoenn"
KANTO_START = 0
OPTION_MENU_STYLE = 11


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_TORCHIC", 5)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    since = mark(game)
    game.tap("START"); game.wait(30)
    game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(240)     # DEBUG, POKéMON
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(300)        # RÉSUMÉ
    game.shot("fiche")
    expect_text(game, "BOURG-EN-VOL", since)
    expect_no_text(game, "échange", since)
    game.wait(200)                                                      # l'animation finie
    game.shot("fiche_apres_animation")
    for _ in range(4):
        game.tap("B"); game.wait(120)
        if game.state.free:
            break
