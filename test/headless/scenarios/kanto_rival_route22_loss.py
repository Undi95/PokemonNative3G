# Perdre contre le rival sur la Route 22 (2026-11-03, docs/A-TESTER.md : avant, le jeu plantait). Comme dans Rouge
# Feu (trainerbattle_earlyrival, drapeaux 0 : pas de soin après) : le rival gagne avec son texte de victoire, puis K.O.
# et reprise devant l'infirmière du dernier Centre (Jadielle). La scène n'est pas finie : le rival attend encore.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 2)    # la sauvegarde de test arrive à Kanto sans équipe
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.money(3000)
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    talk_to(game, "UP")                      # dernier Centre visité : Jadielle
    game.dev("joueur.pv", 0, 1)              # 1 PV : le premier coup met K.O.
    game.var("VAR_KANTO_STARTER_MON", 2)     # CARAPUCE : le rival a BULBIZARRE
    game.var("VAR_KANTO_MAP_SCENE_ROUTE22", 1)

    since = mark(game)
    game.warp("Route22", 32, 5); game.wait(30)
    game.press("RIGHT", 16)                  # case (33, 5) : le rival arrive
    battles = []
    finish_dialog(game, on_battle=lambda g: (battles.append(g.state.battle), fight_battle(g)))
    expect_text(game, "Tu vas à la LIGUE", since)
    expect(game, len(battles) == 1, "un combat contre le rival")
    expect_text(game, "Je suis fort, hein?", since)
    expect_text(game, "se hâte vers un CENTRE", since)
    expect_map(game, "ViridianCity_PokemonCenter_1F", (7, 4))
    expect_var(game, "VAR_KANTO_MAP_SCENE_ROUTE22", 1)   # le rival reviendra
    expect(game, game.state.party[0][2] == game.state.party[0][3], "équipe soignée par l'infirmière")
