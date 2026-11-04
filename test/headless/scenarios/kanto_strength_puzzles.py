# Énigmes de FORCE de Rouge Feu (2026-11-03, docs/A-TESTER.md), poussées trouvées par test/headless/boulders.py sur la
# grille en jeu :
# - Îles Écume 1F : un rocher poussé dans un trou disparaît (FLAG_KANTO_HIDE_SEAFOAM_1F_BOULDER_x) et réapparaît sous
#   le trou au B1F (FLAG_KANTO_HIDE_SEAFOAM_B1F_BOULDER_x remis à 0, rocher sur la carte) ;
# - Route Victoire 1F : un rocher sur l'interrupteur (20, 16, MB_STRENGTH_BUTTON) ouvre la barrière de roche (12, 14)
#   (HandleBoulderActivateVictoryRoadSwitch de RF, VAR_KANTO_MAP_SCENE_VICTORY_ROAD_1F = 100).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from boulders import boulder_plan, grid_lines, push_boulder


def solve(game, map_name, boulders, goal, start):
    """Le premier rocher de boulders qui peut aller sur goal : (rocher, plan), en partant de start."""
    game.warp(map_name, *start); game.wait(40)
    game.flag("FLAG_SYS_USE_STRENGTH", 1)            # FORCE déjà utilisée (proposée : kanto_strength) ; un
                                                     # changement de carte l'oublie, comme dans le jeu
    lines = grid_lines(game)
    for boulder in boulders:
        plan = boulder_plan(lines, boulder, goal, start, [b for b in boulders if b != boulder])
        game.note(f"{map_name} : rocher {boulder} -> {goal} : {plan}")
        if plan:
            return boulder, plan
    return None, None


def play(game):
    continue_game(game)
    game.dev("jeu.rencontres", 0)                       # pas de POKéMON sauvage pendant les poussées (Route Victoire)

    # Îles Écume 1F : le rocher de droite dans le trou (30, 8)
    boulder, plan = solve(game, "SeafoamIslands_1F", [(32, 9), (22, 12)], (30, 8), (33, 10))
    expect(game, plan is not None, "Îles Écume : poussées trouvées")
    if plan:
        push_boulder(game, plan)
        game.wait(60)
        index = 2 if boulder == (32, 9) else 1
        expect_flag(game, f"FLAG_KANTO_HIDE_SEAFOAM_1F_BOULDER_{index}", 1)
        expect_flag(game, f"FLAG_KANTO_HIDE_SEAFOAM_B1F_BOULDER_{index}", 0)
        game.warp("SeafoamIslands_B1F", 30, 10); game.wait(40)
        objects = game.dev("carte.objets")
        expect(game, "en 30,8 " in objects, f"B1F : le rocher est sous le trou ({objects.splitlines()[1:4]})")

    # Route Victoire 1F : un rocher sur l'interrupteur (les dresseurs qui repèrent le joueur en chemin sont battus)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.var("VAR_KANTO_MAP_SCENE_VICTORY_ROAD_1F", 0)
    boulder, plan = solve(game, "KantoVictoryRoad_1F", [(7, 18), (4, 12), (16, 3)], (20, 16), (20, 14))
    expect(game, plan is not None, "Route Victoire : poussées trouvées")
    before = game.dev("carte.metatuiles", 12, 14, 1, 2)
    if plan:
        push_boulder(game, plan)
        game.wait(60)
        expect_var(game, "VAR_KANTO_MAP_SCENE_VICTORY_ROAD_1F", 100)
        after = game.dev("carte.metatuiles", 12, 14, 1, 2)
        expect(game, after != before, f"barrière de roche ouverte ({before.split()[:6]} -> {after.split()[:6]})")
