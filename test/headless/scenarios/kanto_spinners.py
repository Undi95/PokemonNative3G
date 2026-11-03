# Dalles tournantes de RF (docs/A-TESTER.md, 2026-11-03 ; TryUpdatePlayerSpinDirection de field_player_avatar.c) :
# dans l'Arène de Jadielle et les labyrinthes du Repaire Rocket, le joueur entre sur une dalle depuis une case voisine ;
# il glisse de dalle en dalle (la dernière décide de la direction) jusqu'à une dalle d'arrêt ou un obstacle (mur,
# personnage). La case d'arrivée est comparée à celle que donnent les comportements des tuiles (maps.py). Avec BRICE,
# puis RED et LEAF (Options > PERSO ; captures « glissade-PERSO-N » à revoir).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import maps

OPTION_CHARACTER = 6
SPIN = {"MB_SPIN_RIGHT": (1, 0), "MB_SPIN_LEFT": (-1, 0), "MB_SPIN_UP": (0, -1), "MB_SPIN_DOWN": (0, 1)}
STEPS = {(1, 0): "RIGHT", (-1, 0): "LEFT", (0, -1): "UP", (0, 1): "DOWN"}
PLACES = ("ViridianCity_Gym", "RocketHideout_B2F", "RocketHideout_B3F")


def slide(grid, start, blocked):
    """La case où s'arrête le joueur entré sur la dalle start."""
    pos, direction = start, None
    for _ in range(400):
        behavior = grid.behaviors[pos[1]][pos[0]]
        if behavior == "MB_STOP_SPINNING":
            return pos
        direction = SPIN.get(behavior, direction)
        nxt = (pos[0] + direction[0], pos[1] + direction[1])
        if grid.tile(*nxt) == "#" or nxt in blocked:
            return pos
        pos = nxt
    return None


def entries(grid):
    """Les entrées sur une dalle : (case voisine libre, direction, dalle)."""
    found = []
    for y in range(grid.height):
        for x in range(grid.width):
            if grid.behaviors[y][x] not in SPIN:
                continue
            for (dx, dy), step in STEPS.items():
                fx, fy = x - dx, y - dy
                if grid.tile(fx, fy) == "." and grid.behaviors[fy][fx] not in SPIN \
                        and grid.behaviors[fy][fx] != "MB_STOP_SPINNING" and (fx, fy) not in grid.warps:
                    found.append(((fx, fy), step, (x, y)))
    return found


def try_entry(game, place, grid, entry, shot=None):
    (fx, fy), step, tile = entry
    game.warp(place, fx, fy); game.wait(20)
    finish_dialog(game, settle=20)
    if game.state.pos != (fx, fy):
        return None
    expected = slide(grid, tile, set(game.state.objects))
    game.press(step, 16)                    # (un appui court ne fait que tourner le joueur)
    for i in range(60):
        game.wait(10)
        if shot and i in (1, 3, 5):
            game.shot(f"{shot}-{i}")
        if game.state.battle:
            fight_battle(game); finish_dialog(game)
            return None
        if game.state.free:
            game.wait(20)
            if game.state.free:
                break
    return expected, game.state.pos


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    checked = 0
    for who, perso, gender in (("brice", 0, 0), ("red", 1, 0), ("leaf", 1, 1)):
        game.dev("jeu.options", OPTION_CHARACTER, perso)
        game.dev("joueur.genre", gender)
        for place in PLACES if who == "brice" else PLACES[1:2]:
            grid = maps.load(place)
            found = entries(grid)
            if who == "brice":
                chosen = found[::max(1, len(found) // 8)][:8]
            else:                                   # RED et LEAF : les deux plus longues glissades (le sprite qui tourne)
                far = lambda e: sum(abs(a - b) for a, b in zip(e[2], slide(grid, e[2], set()) or e[2]))
                chosen = sorted(found, key=far, reverse=True)[:2]
            for n, entry in enumerate(chosen):
                result = try_entry(game, place, grid, entry, shot=f"glissade-{who}-{n}" if who != "brice" or n < 2
                                   else None)
                if result is None:
                    game.note(f"DALLE {place} {entry} : interrompue (combat ou scène)")
                    continue
                expected, got = result
                game.note(f"DALLE {place} {entry} : attendu {expected}, arrivé {got}")
                expect(game, got == expected, f"{place}, entrée {entry} : arrêt en {expected} ({got})")
                checked += 1
    expect(game, checked >= 12, f"glissades comparées ({checked})")
