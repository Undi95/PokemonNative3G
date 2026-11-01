# Options DIALOGUE = KANTO et POLICE = KANTO dans Émeraude, depuis la sauvegarde « hoenn » : début de partie
# (maman, Flora, Route 101, premier combat), puis menu Start, écran de sauvegarde, sac, équipe et résumé.
# Aucune lettre ne doit être coupée par le bord de sa fenêtre : les lignes écrites pour la police d'Émeraude
# et trop larges pour celle de Rouge Feu passent à la ligne suivante (text.c, WrapTextToWindow).
from driver import *

FIXTURE = "hoenn"
KANTO_START = 0


def set_options(game):
    """START > OPTIONS, page 2 : DIALOGUE puis POLICE = KANTO."""
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A")
    game.wait(150)
    game.tap("R"); game.wait(30); game.tap("DOWN", 2, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(20)
    game.tap("DOWN"); game.wait(20); game.tap("RIGHT"); game.wait(60)
    game.shot("options")
    game.tap("B"); game.wait(150)
    game.tap("B")                                   # le menu Start, rouvert au retour
    wait_until(game, lambda s: s.free)


def dialog_shots(game, name, count):
    """Une capture par page du dialogue en cours (le texte fini de s'écrire), puis la suite."""
    for i in range(count):
        game.wait(150)
        game.shot(f"{name}_{i + 1}")
        game.tap("A")
    finish_dialog(game)


def menu_shot(game, name, ups, frames=240):
    """START, ups fois HAUT depuis la dernière entrée choisie, A, puis une capture."""
    game.tap("START"); game.wait(30)
    game.tap("UP", ups, gap=10)
    game.tap("A"); game.wait(frames)
    game.shot(name)


def close_menus(game):
    """B jusqu'à pouvoir bouger (un écran ramène au menu Start, encore ouvert)."""
    for _ in range(6):
        game.tap("B"); game.wait(150)
        if game.state.free:
            return
    raise GameError(f"les menus ne se ferment pas : {game.describe()}")


def play(game):
    continue_game(game)
    set_options(game)
    expect(game, game.command("font") == 1, "option POLICE = KANTO")
    take_warp(game, "LittlerootTown_BrendansHouse_1F")
    dialog_shots(game, "maman", 4)
    take_warp(game, "LittlerootTown")
    finish_dialog(game)
    take_warp(game, "LittlerootTown_MaysHouse_1F")
    dialog_shots(game, "maman_flora", 3)
    take_warp(game, "LittlerootTown_MaysHouse_2F")
    finish_dialog(game)
    talk_to_object(game, 5, 4, finish=False)        # la POKé BALL de Flora : Flora arrive
    dialog_shots(game, "flora", 4)
    take_warp(game, "LittlerootTown_MaysHouse_1F")
    finish_dialog(game)
    take_warp(game, "LittlerootTown")
    finish_dialog(game)

    walk_to(game, 11, 2)                            # sortie nord : le PROF. SEKO poursuivi
    leave_map(game, "UP")
    finish_dialog(game)
    expect_map(game, "Route101")
    talk_to_object(game, 7, 14, finish=False)       # le sac du PROF. SEKO
    for _ in range(60):                             # écran du choix, puis « Tu choisis ce POKéMON ? » OUI
        if game.state.battle:
            break
        game.tap("A", hold=4, gap=26)
    expect(game, game.state.battle, "le premier combat commence")
    game.wait(400)
    game.shot("combat")
    fight_battle(game)
    finish_dialog(game, answers={"surnom": "B"})
    expect_map(game, "LittlerootTown_ProfessorBirchsLab")

    menu_shot(game, "sauvegarde", 0, 120)          # le menu reprend la place de la dernière entrée : SAUVER
    close_menus(game)
    menu_shot(game, "sac", 2)                       # SAUVER -> (carte) -> SAC
    close_menus(game)
    menu_shot(game, "equipe", 1)                    # SAC -> POKéMON
    game.tap("A"); game.wait(60); game.shot("equipe_menu")
    game.tap("A"); game.wait(240); game.shot("resume")
    close_menus(game)

    for frame, win, text in game.clipped:
        game.note(f"COUPÉ fenêtre {win} : {text}")
    expect(game, not game.clipped, f"{len(game.clipped)} texte(s) coupé(s) par le bord de leur fenêtre")
