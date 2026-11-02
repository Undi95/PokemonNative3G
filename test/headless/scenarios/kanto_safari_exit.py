# Sortie du Parc Safari de Kanto : les scripts de Rouge Feu (SafariZone_EventScript_TimesUp, _OutOfBalls,
# _RetirePrompt de RF), qui ramènent à l'entrée de Parmanie et mettent sa scène. Avant : ceux d'Émeraude, qui
# envoyaient à l'entrée du Parc Safari de la Route 121 (Hoenn).
from driver import *

FIXTURE = "kanto"


def enter_safari(game):
    game.warp("FuchsiaCity_SafariZone_Entrance", 4, 4)
    game.press("UP", 16)
    for _ in range(300):
        if game.state.map_name == "KantoSafariZone_Center" and game.state.free:
            break
        game.tap("A", hold=2, gap=20)
    expect(game, game.state.map_name == "KantoSafariZone_Center", "entrée dans le Parc Safari")


def back_at_entrance(game, why):
    for _ in range(200):
        if game.state.map_name == "FuchsiaCity_SafariZone_Entrance" and game.state.free:
            break
        game.tap("A", hold=2, gap=20)
    expect(game, game.state.map_name == "FuchsiaCity_SafariZone_Entrance",
           f"{why} : retour à l'entrée de Parmanie (carte {game.state.map_name})")
    expect(game, "safari 0" in game.dev("jeu.safari"), f"{why} : plus en mode Safari")


def play(game):
    continue_game(game)
    game.money(10000)
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.dev("jeu.rencontres", 0)

    # Le temps : 1 pas restant, un pas
    enter_safari(game)
    game.dev("jeu.safari", 1)
    since, frame = mark(game), game.frames
    game.press("UP", 16)                        # dans le parc (en bas : la porte de sortie)
    wait_text(game, "Ding-dong", since, limit=300)
    expect_sound(game, "SE_DING_DONG", frame)
    back_at_entrance(game, "temps écoulé")
    check_screen(game, "kanto_safari_exit-temps")

    # PARTIR (menu Start), OUI
    enter_safari(game)
    since = mark(game)
    game.tap("START", gap=40)
    retire = next(i for i, (_, name) in enumerate(game.start_menu()[0]) if "PARTIR" in name.upper())
    game.tap("DOWN", times=retire, gap=10)
    game.tap("A", gap=30)
    wait_text(game, "quitter", since, limit=300)
    game.tap("A", gap=30)                       # OUI
    back_at_entrance(game, "retraite")

    # La dernière SAFARI BALL lancée en combat (capturé ou non : _OutOfBalls ou _OutOfBallsMidBattle)
    enter_safari(game)
    game.dev("jeu.safari", 600, 1)
    game.dev("jeu.rencontres", 1)
    grid = live_map(game)
    px, py = game.state.pos
    grass = sorted(((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == "g"),
                   key=lambda t: abs(t[0] - px) + abs(t[1] - py))
    for x, y in grass[:20]:
        if grid.path((px, py), (x, y), set(game.state.objects)) is not None:
            walk_to(game, x, y, live=True, on_battle=lambda g: None)
            break
    for i in range(400):
        if game.state.battle:
            break
        game.press(("LEFT", "RIGHT")[i % 2], 16)
    expect(game, game.state.battle, "rencontre dans l'herbe du Parc Safari")
    since = mark(game)
    for _ in range(100):                        # le menu (« PIERRE »), puis BALL (en haut à gauche)
        if saw_text(game, "PIERRE", since):
            break
        game.tap("A", hold=2, gap=20)
    game.wait(30)
    game.tap("A", gap=20)
    back_at_entrance(game, "plus de SAFARI BALLS")
