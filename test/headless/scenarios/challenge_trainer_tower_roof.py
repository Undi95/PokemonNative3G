# Défi complet de la Tour des Dresseurs de l'Île 7 (RF ; docs/A-TESTER.md, 2026-11-03) : SOLO, à chaque étage le
# couloir du milieu jusqu'au dresseur (combat gagné), puis l'escalier (15, 6) ; sur le toit, le propriétaire : prix et
# temps final (captures « toit-N »). Raccourci de test : l'équipe est soignée à chaque étage (sinon la même équipe au
# niveau 70 perd vers le 5e étage).
from driver import *
import os, sys
import driver
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import challenges
from menu_helpers import texts
from kanto_trainer_tower_modes import answer

FIXTURE = "kanto"


def floor(game, n):
    """Un étage : le dresseur du couloir (13), puis l'escalier."""
    game.wait(60)
    walk_to(game, 6, 13, live=True, on_battle=lambda g: None)
    for _ in range(8):
        if game.state.battle:
            break
        game.press("RIGHT", 16); game.wait(10)
    for _ in range(40):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=20)
    won = False
    if game.state.battle:
        fight_battle(game, limit=6000)
        won = game.battles[-1]["outcome"] == "WON"
    finish_dialog(game, limit=300)
    walk_to(game, 16, 6, live=True, on_battle=lambda g: fight_battle(g, limit=6000))
    here = game.state.map_name
    for _ in range(3):                                  # MB_UP_LEFT_STAIR_WARP : sur l'escalier (15, 6), encore GAUCHE
        if game.state.map_name != here:
            break
        game.press("LEFT", 20); game.wait(30)
    wait_until(game, lambda s: s.free and s.map_name != here, limit=900)
    return won


def play(game):
    continue_game(game)
    challenges.give_team(game, 70, challenges.HILL_TEAM)
    game.dev("jeu.options", 3, 1)                       # style DEFINI
    game.max_frames = game.frames + 250000
    game.warp("TrainerTower_Lobby", 9, 8); game.wait(30)
    since = mark(game)
    game.press("UP", 16); game.wait(30)
    since = answer(game, since, "OUI")
    answer(game, since, "SOLO")
    for _ in range(20):
        game.wait(30)
        if game.state.free:
            break
        game.tap("A")
    walk_to(game, 9, 2)
    game.press("RIGHT", 20)
    wait_until(game, lambda s: s.free and s.map_name == "TrainerTower_1F", limit=600)
    results = []
    sounds = len(game.sounds)
    for n in range(1, 9):
        game.heal()                                     # raccourci de test : l'équipe soignée à chaque étage
        results.append(floor(game, n))
        game.note(f"ÉTAGE {n} : {'gagné' if results[-1] else 'sans combat gagné'} ; maintenant {game.state.map_name}")
    expect_map(game, "TrainerTower_Roof")
    expect(game, all(results), f"8 étages gagnés ({results})")
    # Musique de victoire de RF (MUS_VICTORY_TRAINER de RF = MUS_RG_VICTORY_TRAINER, 2026-11-04), pas celle d'Émeraude
    played = [s for _, s in game.sounds[sounds:]]
    expect(game, "MUS_RG_VICTORY_TRAINER" in played and "MUS_VICTORY_TRAINER" not in played,
           f"musique de victoire de RF ({sorted(set(s for s in played if 'VICTORY' in s))})")

    # Le toit : le propriétaire (9, 7), parlé depuis le dessous
    since = mark(game)
    walk_to(game, 9, 8, live=True)
    talk_to(game, "UP", finish=False)
    for i in range(30):
        if game.state.free:
            break
        if i % 3 == 0:
            game.shot(f"toit-{i // 3}")
        game.tap("A"); game.wait(40)
    finish_dialog(game, limit=300)
    roof = " ".join(t for w, t in texts(game, since) if w == 0)
    game.note(f"TOIT : {roof}")
    expect(game, roof != "", f"le propriétaire parle sur le toit ({roof[:100]})")
