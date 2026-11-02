# Cycle jour/nuit, la nuit : combat sauvage sur la Route 1. L'animation de transition vers le combat garde la teinte
# de nuit jusqu'au bout (bug Android du 2026-11-01 : le terrain repassait en couleurs de jour pendant l'animation,
# BattleTransition_StartOnField met CB2_OverworldBasic). Le détecteur « teinte jour/nuit coupée » ne doit rien voir.
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    game.command("daynight", 1)
    game.command("clock", 23, 0)
    game.warp("Route1", 12, 9)
    game.wait(70)                                   # la teinte relit l'heure une fois par seconde
    def in_transition():
        return game.state.battle or game.function(game.state.cb2) == "CB2_OverworldBasic"

    for _ in range(80):
        if in_transition():
            break
        game.press("UP" if game.state.pos[1] >= 9 else "DOWN", 16)
        if not in_transition():
            game.wait(8)
    expect(game, in_transition(), "un combat sauvage commence")
    # L'animation de transition, une capture toutes les 6 images
    for i in range(16):
        game.shot(f"transition_{i:02}")
        game.wait(6)
    tint = [text for _, kind, text in game.anomalies if kind == "teinte jour/nuit coupée"]
    expect(game, not tint, "la teinte de nuit reste pendant l'animation de transition")
