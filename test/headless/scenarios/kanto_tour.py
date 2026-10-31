# Build KANTO_DEBUG=1 : nouvelle partie à Bourg Palette, porte de la maison (fermée, à vendre), le labo,
# parle aux PNJ, puis téléport à Jadielle et soin au Centre Pokémon.
from driver import *  # les vérifications (expect...)
from driver import check_screen, finish_dialog, leave_map, mark, talk_to, walk_to, wait_until


def log(game, what):
    """Une étape du scénario, dans le journal. Dans un scénario qui met SCREENS = True,
    l'écran doit aussi être celui de la référence refs/SCÉNARIO-ÉTAPE.png."""
    game.note(f"ÉTAPE {what}")
    if game.screens:
        check_screen(game, f"{game.name}-{what}")


def debug_warp(game, index):
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", index); game.tap("A")
    wait_until(game, lambda s: s.free)


def ferry_to_kanto(game):
    """Port de Poivressel / Nénucrique, face à l'employé : choisit KANTO dans le menu du ferry, puis OUI."""
    since = mark(game)
    talk_to(game, "UP", finish=False)
    for _ in range(40):
        printed = [(w, t.strip()) for _, w, t in game.texts[since:] if w != 0]
        if any(t == "KANTO" for _, t in printed):
            break
        game.tap("A", hold=2, gap=10)
    game.wait(20)
    printed = [(w, t.strip()) for _, w, t in game.texts[since:] if w != 0 and t.strip() != "▶"]   # sans le curseur
    # les choix du menu : les textes de la fenêtre de KANTO, imprimés à la suite ; le curseur part du dernier
    # (ANNULER / QUITTER), comme dans Émeraude
    k = max(i for i, (_, t) in enumerate(printed) if t == "KANTO")
    window, last = printed[k][0], k
    while last + 1 < len(printed) and printed[last + 1][0] == window:
        last += 1
    game.tap("UP", last - k, gap=10); game.wait(10); game.tap("A"); game.wait(30)
    finish_dialog(game)


def give_mewtwo(game):
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 4); game.tap("A"); game.wait(30); game.tap("B"); game.wait(30)
    wait_until(game, lambda s: s.free)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    log(game, "arrivée")
    walk_to(game, 3, 11); talk_to(game, "UP"); log(game, "dame du panneau")
    walk_to(game, 6, 8); talk_to(game, "UP"); log(game, "maison à vendre : fermée")   # porte fermée tant qu'elle n'est pas achetée
    walk_to(game, 16, 14); leave_map(game, "UP"); log(game, "labo")
    walk_to(game, 3, 12); talk_to(game, "UP"); log(game, "assistant")
    walk_to(game, 6, 11); leave_map(game, "DOWN"); log(game, "dehors")
    give_mewtwo(game)
    debug_warp(game, 1); log(game, "Jadielle")
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre Pokémon")
    walk_to(game, 7, 4); talk_to(game, "UP"); log(game, "infirmière")
    walk_to(game, 7, 7); leave_map(game, "DOWN"); log(game, "dehors")

    # Vérifications
    expect_flag(game, "FLAG_KANTO_VISITED_OAKS_LAB")
    expect_text(game, "Je suis donc son… ASSISTANT")
    expect_map(game, "ViridianCity")
