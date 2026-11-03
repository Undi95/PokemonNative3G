# Tour des Dresseurs de l'Île 7 (docs/A-TESTER.md, 2026-11-03) : chaque mode choisi à l'accueil (SOLO, DUO, KO, MIXTE ;
# KANTO_MULTICHOICE_TRAINER_TOWER_MODE), puis le 1er étage : les dresseurs que le code y place (disposition de RF, notée
# au journal, captures « etage-MODE ») ; entre deux modes, reset et CONTINUER (la sauvegarde d'avant le défi).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import challenges
from menu_helpers import texts, menu_block

MODES = ("SOLO", "DUO", "KO", "MIXTE")


def answer(game, since, label):
    """Attend le menu qui contient label (en appuyant sur A dans les messages), puis le choisit. Rend la marque prise
    juste avant le A du choix (le menu suivant s'écrit pendant ce A)."""
    for _ in range(40):
        shown = [t for _, t in texts(game, since)]
        if label in shown:
            break
        game.tap("A"); game.wait(30)
    game.wait(30)
    index, _ = menu_block(game, since, label)
    if index:
        game.tap("DOWN", index, gap=12); game.wait(10)
    after = mark(game)
    game.tap("A"); game.wait(30)
    return after


def floor_objects(game):
    reply = game.dev("carte.objets")
    game.note(f"OBJETS {reply}")
    return [line for line in reply.splitlines() if "objet" in line and " id 255 " not in line]


def nurse(game):
    """L'infirmière du hall (4, 9), derrière son comptoir : elle soigne l'équipe."""
    import crawl
    game.dev("joueur.pv", 0, 1)
    for sx, sy, direction in crawl.spots("TrainerTower_Lobby", 4, 9):
        game.warp("TrainerTower_Lobby", sx, sy); game.wait(30)
        since = mark(game)
        talk_to(game, direction, finish=False)
        finish_dialog(game, limit=300)
        said = " ".join(t for _, t in texts(game, since))
        if said:
            return said
    return ""


def play(game):
    layouts = {}
    continue_game(game)
    challenges.give_team(game, 50, challenges.HILL_TEAM)
    said = nurse(game)
    species, level, hp, max_hp = game.state.party[0][:4]
    game.note(f"INFIRMIÈRE : {said}")
    expect(game, hp == max_hp and "soign" in said, f"l'infirmière du hall soigne ({hp}/{max_hp} ; {said[-80:]})")
    game.press("A+B+START+SELECT", 1); game.wait(400)
    for n, mode in enumerate(MODES):
        if n:
            game.press("A+B+START+SELECT", 1); game.wait(400)
        continue_game(game)                             # (la sauvegarde d'avant le défi)
        challenges.give_team(game, 50, challenges.HILL_TEAM)
        game.warp("TrainerTower_Lobby", 9, 8); game.wait(30)
        since = mark(game)
        game.press("UP", 16); game.wait(30)
        since = answer(game, since, "OUI")
        answer(game, since, mode)
        for _ in range(20):                         # « Partez! », sans reparler à l'hôtesse une fois libre
            game.wait(30)
            if game.state.free:
                break
            game.tap("A")
        walk_to(game, 9, 2)
        game.press("RIGHT", 20)
        wait_until(game, lambda s: s.free and s.map_name == "TrainerTower_1F", limit=600)
        game.wait(60)
        expect_map(game, "TrainerTower_1F")
        # Le couloir du milieu (rangée 13), vers la droite : les dresseurs apparaissent, l'un d'eux repère le joueur
        since = mark(game)
        try:
            walk_to(game, 6, 13, live=True, on_battle=stop)
            for _ in range(6):
                if game.state.battle:
                    break
                game.press("RIGHT", 16); game.wait(10)
            for _ in range(40):
                if game.state.battle:
                    break
                game.tap("A", hold=2, gap=20)
        except Started:
            pass
        game.wait(300)
        layouts[mode] = floor_objects(game)
        battle = game.dev("combat.etat").splitlines()[0]
        intro = " ".join(t for _, t in texts(game, since) if "combat est lancé" in t)
        game.shot(f"etage-{mode.lower()}")
        game.note(f"MODE {mode} : {battle} ; {intro} ; {layouts[mode]}")
        layouts[mode] = (re.search(r"combattants (\d+)", battle).group(1), intro)
    game.note(f"MODES {layouts}")
    expect(game, layouts["SOLO"][0] == "2" and layouts["DUO"][0] == "4",
           f"SOLO : combat simple, DUO : combat double ({layouts})")
    expect(game, all(intro for _, intro in layouts.values()), f"un combat dans chaque mode ({layouts})")


class Started(Exception):
    pass


def stop(game):
    raise Started
