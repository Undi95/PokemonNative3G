# Présentation des combats de Rouge Feu, dans tous les combats (décision du 2026-11-02) : en combat double, la
# capacité sous le curseur blanchit les Pokémon qu'elle touchera (PreviewDeterminativeMoveTargets). Mont Combat,
# combat double contre deux dresseurs : KYOGRE en tête, SURF (les deux adversaires) en première capacité.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    state = {}

    def watch(g):
        if "shot" in state:
            return
        if "since" not in state:
            state["since"] = mark(g)
        if saw_text(g, "SURF", state["since"]):   # la liste des capacités de KYOGRE, SURF sous le curseur
            g.wait(4)
            check_screen(g, "battle_double_targets-surf")
            state["shot"] = True

    challenges.run(game, "TrainerHill_Entrance", party=3, battles=1, level=50, trigger=(9, 6),
                   flags=["FLAG_SYS_GAME_CLEAR"], walking=True, team=challenges.HILL_TEAM, watch=watch)
    expect(game, "shot" in state, "menu des capacités d'un combat double")
