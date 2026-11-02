# Parc Safari de Kanto (Parmanie) : le menu de combat est celui de Rouge Feu (BALL, APPAT, PIERRE, FUITE) et pas celui
# d'Émeraude (POKéBLOC, SE RAP.). APPAT : « lance un APPAT », le Pokémon mange ; PIERRE : « lance une PIERRE », il se
# fâche (HandleAction_ThrowBait / ThrowRock, compteurs et facteurs de RF, animations General_BaitThrow,
# General_SafariRockThrow, General_SafariReaction).
from driver import *
import maps

FIXTURE = "kanto"


def wait_menu(game, since):
    """Le menu d'action du Safari (son texte « PIERRE »), le joueur peut choisir : A sur les messages d'avant."""
    for _ in range(100):
        if saw_text(game, "PIERRE", since):
            break
        game.tap("A", hold=2, gap=20)
    game.wait(30)


def play(game):
    continue_game(game)
    game.money(10000)
    game.dev("jeu.options", 0, 2)               # texte rapide : les captures tombent sur les animations
    # Le guichet : la case (4, 3) devant le comptoir, on y monte par le bas ; OUI (A) à tout
    game.warp("FuchsiaCity_SafariZone_Entrance", 4, 4)
    game.press("UP", 16)
    for _ in range(300):
        if game.state.map_name == "KantoSafariZone_Center" and game.state.free:
            break
        game.tap("A", hold=2, gap=20)
    expect(game, game.state.map_name == "KantoSafariZone_Center", "entrée dans le Parc Safari")

    # Le menu Start : les pas restants sur 600 (RF ; 500 à Hoenn) et les SAFARI BALLS
    since = mark(game)
    game.tap("START", gap=40)
    expect_text(game, "/600", since)
    expect_text(game, "BALLS  30", since)
    check_screen(game, "kanto_safari-menu_start")
    game.tap("B", gap=40)

    # De l'herbe : la plus proche, puis des allers-retours jusqu'à une rencontre
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
    wait_menu(game, since)
    expect_text(game, "APPAT", since)
    expect_no_text(game, "SE RAP", since)
    check_screen(game, "kanto_safari-menu")

    since = mark(game)
    game.tap("RIGHT", gap=20)                   # APPAT (en haut à droite)
    game.tap("A", gap=20)
    wait_text(game, "lance", since, limit=600)
    expect_text(game, "un APPAT", since)
    game.wait(130)                              # le texte, son attente, puis l'APPAT en vol (General_BaitThrow)
    check_screen(game, "kanto_safari-appat")

    since = mark(game)
    for _ in range(200):                        # la réaction (« mange! ») ou la fuite
        if saw_text(game, "PIERRE", since) or not game.state.battle:
            break
        game.tap("A", hold=2, gap=20)
    if game.state.battle:
        expect_text(game, "mange", since)
        since = mark(game)
        game.wait(30)
        game.tap("LEFT", gap=20)                # PIERRE (en bas à gauche)
        game.tap("DOWN", gap=20)
        game.tap("A", gap=20)
        wait_text(game, "lance", since, limit=600)
        expect_text(game, "une PIERRE", since)
        for _ in range(200):
            if saw_text(game, "fâche", since) or not game.state.battle:
                break
            game.tap("A", hold=2, gap=20)
        expect(game, saw_text(game, "fâche", since) or not game.state.battle, "le Pokémon se fâche (ou s'enfuit)")
