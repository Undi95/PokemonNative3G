# Présentation des combats de Rouge Feu, dans tous les combats (décision du 2026-11-02) : un Pokémon qui monte de
# niveau a les bandes verticales de RF (Task_CreateLevelUpVerticalStripes, après l'animation de la boîte de PV).
# MEWTWO N.2 en tête, combats sauvages sur la Route 101 (Hoenn) jusqu'à la montée de niveau.
from driver import *
import maps
import names

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.dev("jeu.options", 4, 1)               # sans animations de combat : seule la montée de niveau s'anime
    game.give_mon("SPECIES_MEWTWO", 2)           # N.3 après un combat (courbe lente : 10 → 33 points)
    game.wait(1)
    slot = len(game.state.party) - 1
    for place in (0, 1):                        # PLAQUAGE : CHOC MENTAL n'atteint pas MEDHYENA (Ténèbres)
        game.dev("joueur.capacite", slot, place, names.number("MOVE_BODY_SLAM"))
    route = maps.load("Route101")
    grass = [(x, y) for y, row in enumerate(route.tiles) for x, c in enumerate(row) if c == "g"]
    x, y = grass[len(grass) // 2]
    game.warp("Route101", x, y)
    game.wait(30)

    state = {}

    def watch(g):
        if "shot" not in state and "Task_CreateLevelUpVerticalStripes" in [g.function(t) for t in g.state.tasks]:
            frame = g.frames
            g.wait(28)                          # les bandes montent sur le Pokémon (film : de +16 à +52 images)
            check_screen(g, "battle_levelup_stripes-bandes")
            expect_sound(g, "SE_SHOP", frame)   # SE_RS_SHOP de RF (même MIDI que SE_SHOP d'Émeraude)
            state["shot"] = True

    for _ in range(4):
        for i in range(300):
            if game.state.battle:
                break
            game.press(("LEFT", "RIGHT")[i % 2], 16)
        if not game.state.battle:
            break
        fight_battle(game, limit=3000, watch=watch)
        game.heal()
        if "shot" in state:
            break
    expect(game, "shot" in state, "bandes verticales de montée de niveau (Task_CreateLevelUpVerticalStripes)")
