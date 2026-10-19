# Build KANTO_DEBUG=1 : nouvelle partie à Bourg Palette, entre dans les maisons, le labo,
# parle aux PNJ, puis téléport à Jadielle et soin au Centre Pokémon.
from driver import finish_dialog, leave_map, talk_to, walk_to, wait_until


def log(game, what):
    print(f"{what}: {game.state}", flush=True)


def debug_warp(game, index):
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", index); game.tap("A")
    wait_until(game, lambda s: s.free)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    log(game, "arrivée")
    walk_to(game, 3, 11); talk_to(game, "UP"); log(game, "dame du panneau")
    walk_to(game, 6, 8); leave_map(game, "UP"); log(game, "maison 1F")
    walk_to(game, 8, 5); talk_to(game, "UP"); log(game, "maman")
    walk_to(game, 10, 3); leave_map(game, "UP"); log(game, "maison 2F")
    walk_to(game, 10, 2); wait_until(game, lambda s: s.free); log(game, "retour 1F")
    walk_to(game, 4, 7); leave_map(game, "DOWN"); log(game, "dehors")
    walk_to(game, 16, 14); leave_map(game, "UP"); log(game, "labo")
    walk_to(game, 3, 12); talk_to(game, "UP"); log(game, "assistant")
    walk_to(game, 6, 11); leave_map(game, "DOWN"); log(game, "dehors")
    debug_warp(game, 1); log(game, "Jadielle")
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre Pokémon")
    walk_to(game, 7, 4); talk_to(game, "UP"); log(game, "infirmière")
    walk_to(game, 7, 7); leave_map(game, "DOWN"); log(game, "dehors")
