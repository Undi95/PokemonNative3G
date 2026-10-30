# Terrain de Rouge Feu (2026-10-30) : trou des Îles Écume (MB_FALL_WARP), glace fine de la Grotte de Glace (se fissure,
# puis casse et fait tomber), panneaux du Plateau Indigo (enseignes MB_INDIGO_PLATEAU_SIGN_1/2 en marchant vers eux),
# START pendant un panneau (le ferme puis ouvre le menu), objets cachés qui réapparaissent (après 1 500 pas).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, finish_dialog, mark, wait_text, wait_until


def step(game, direction, frames=40):
    """Un pas (se tourner d'abord : un appui court ne fait que tourner)."""
    game.tap(direction, hold=2, gap=10)
    game.press(direction, 16); game.wait(frames)


def warp(game, map_name, x, y):
    game.warp(map_name, x, y); game.wait(30)
    wait_until(game, lambda s: s.free, limit=900); game.wait(30)


def renewable_flags():
    import os, re
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..')
    text = open(os.path.join(root, 'include', 'constants', 'kanto_flags_vars.h'), encoding='utf-8').read()
    return re.findall(r'#define (FLAG_KANTO_HIDDEN_ITEM_\w+)', text)


def play(game):
    continue_game(game)

    # Îles Écume 1F : le trou (21, 8) fait tomber au B1F
    warp(game, "SeafoamIslands_1F", 21, 9)
    step(game, "UP", 120)
    wait_until(game, lambda s: s.free, limit=600)
    expect_map(game, "SeafoamIslands_B1F")

    # Grotte de Glace 1F : glace fine (8, 3) ; 1er passage = fissure, 2e = trou
    warp(game, "FourIsland_IcefallCave_1F", 8, 4)
    step(game, "UP"); step(game, "DOWN")
    expect_map(game, "FourIsland_IcefallCave_1F")
    step(game, "UP", 120)
    wait_until(game, lambda s: s.free, limit=600)
    expect_map(game, "FourIsland_IcefallCave_B1F")
    warp(game, "FourIsland_IcefallCave_1F", 8, 4)   # comme RF (drapeaux temporaires) : glace neuve en revenant
    step(game, "UP", 120)
    expect_map(game, "FourIsland_IcefallCave_1F")

    # Plateau Indigo : enseigne en marchant vers elle, puis START pendant le message
    warp(game, "IndigoPlateau_Exterior", 8, 8)
    since = mark(game)
    game.tap("UP"); game.wait(10); game.press("UP", 30)
    wait_text(game, "PLATEAU INDIGO", since)
    game.wait(60)
    since_menu = mark(game)
    game.tap("START"); game.wait(120)
    expect(game, any("DEBUG" in t for _, _, t in game.texts[since_menu:]), "START pendant le panneau : menu Start ouvert")
    game.tap("B"); wait_until(game, lambda s: s.free, limit=300)
    since2 = mark(game)
    warp(game, "IndigoPlateau_Exterior", 14, 11)
    game.tap("UP"); game.wait(10); game.press("UP", 30)
    wait_text(game, "La plus haute instance", since2)
    finish_dialog(game)
    expect_text(game, "Le rêve de tout DRESSEUR", since)
    expect_text(game, "La plus haute instance", since2)

    # Objets cachés renouvelables : après 1 500 pas, en entrant sur une de leurs cartes (Route 20), un tirage en fait revenir
    flags = renewable_flags()
    hidden = [f for f in flags if game.flag(f) == 1]
    game.var("VAR_KANTO_RENEWABLE_ITEM_STEP_COUNTER", 1500)
    warp(game, "Route20", 60, 8)
    expect_var(game, "VAR_KANTO_RENEWABLE_ITEM_STEP_COUNTER", 0)
    back = [f for f in hidden if game.flag(f) == 0]
    game.note(f"objets cachés revenus : {back}")
    expect(game, len(back) >= 1, "au moins un objet caché revenu")
