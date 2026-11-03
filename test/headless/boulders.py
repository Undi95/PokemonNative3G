"""Pousser un rocher de FORCE jusqu'à une case : recherche des poussées (un rocher à la fois, les autres rochers et les
murs de la grille en jeu comme obstacles), puis le jeu au banc (walk_to jusqu'à la case derrière le rocher, une
poussée = la direction tenue un pas). Pour les énigmes de FORCE (Îles Écume, Route Victoire).

    plan = boulder_plan(grid, boulder=(7, 18), goal=(20, 16), others=[(4, 12)])
    push_boulder(game, plan)
"""
from collections import deque

from driver import GameError, wait_until, walk_to

DIRECTIONS = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}


def grid_lines(game):
    """La carte en jeu (outil carte.grille) : liste de rangées, '#' bloqué."""
    return game.dev("carte.grille").splitlines()[1:]


def free(lines, x, y, blocked=()):
    return 0 <= y < len(lines) and 0 <= x < len(lines[y]) and lines[y][x] not in "#~" and (x, y) not in blocked


def reachable(lines, start, goal, blocked):
    if start == goal:
        return True
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        for dx, dy in DIRECTIONS.values():
            n = (x + dx, y + dy)
            if n == goal:
                return True
            if n not in seen and free(lines, *n, blocked):
                seen.add(n)
                todo.append(n)
    return False


def boulder_plan(lines, boulder, goal, player, others=(), hole_ok=False):
    """Les poussées qui mènent boulder sur goal : [(case du joueur, direction), ...], ou None. hole_ok : goal est un
    trou ('o'), où le rocher tombe."""
    start = (boulder, player)
    seen = {start}
    todo = deque([(start, [])])
    while todo:
        (b, p), plan = todo.popleft()
        for name, (dx, dy) in DIRECTIONS.items():
            behind = (b[0] - dx, b[1] - dy)
            ahead = (b[0] + dx, b[1] + dy)
            if not free(lines, *behind, set(others) | {b}):
                continue
            if ahead != goal and (not free(lines, *ahead, set(others)) or lines[ahead[1]][ahead[0]] == "o"):
                continue
            if not reachable(lines, p, behind, set(others) | {b}):
                continue
            step = plan + [(behind, name)]
            if ahead == goal:
                return step
            state = (ahead, b)
            if state not in seen and len(step) < 40:
                seen.add(state)
                todo.append((state, step))
    return None


def push_boulder(game, plan):
    """Joue les poussées : walk_to jusqu'à la case derrière le rocher, se tourner vers lui (un appui d'une image),
    puis un appui d'une image le pousse d'une case (le joueur reste où il est) ; on attend la fin de la poussée."""
    for (x, y), direction in plan:
        if game.state.pos != (x, y):
            walk_to(game, x, y)
        if game.state.pos != (x, y):
            raise GameError(f"pas pu se placer en {(x, y)} pour pousser vers {direction}")
        game.press(direction, 1); game.wait(8)
        game.press(direction, 1); game.wait(30)
        wait_until(game, lambda s: s.free, limit=600)
        game.wait(10)
