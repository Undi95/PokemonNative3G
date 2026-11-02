# NOUVELLE PARTIE par-dessus une sauvegarde aux options KANTO (bug Android du 2026-11-01 : boîte cassée et texte bleu
# dans l'intro, Red joué à Hoenn). Décision : les options d'affichage restent d'une partie à l'autre, PERSO est remis
# (l'intro choisit le personnage). L'intro du Prof. Seko doit dessiner la boîte de RF (aucune anomalie « cadre de
# boîte »), en gris, et la partie commence avec Brice ou Flora.
from driver import *

FIXTURE = "kanto"
KANTO_START = 0

# Options des outils de debug (jeu.options N V)
OPTION_PLAYER_CHARACTER, OPTION_DIALOG_STYLE, OPTION_FONT, OPTION_MENU_STYLE = 6, 8, 9, 11
TEXT_COLOR_DARK_GRAY = 2


def option(game, number):
    line = next(line for line in game.dev("jeu.options").splitlines() if line.startswith(f"{number} "))
    return int(line.rsplit("=", 1)[1])


def play(game):
    continue_game(game)
    for number in (OPTION_PLAYER_CHARACTER, OPTION_DIALOG_STYLE, OPTION_FONT, OPTION_MENU_STYLE):
        game.dev("jeu.options", number, 1)
    save(game)

    # Reset, puis NOUVELLE PARTIE (2e entrée du menu principal)
    since = mark(game)
    game.press("A+B+START+SELECT", 2)
    for _ in range(40):                             # intro, écran titre, jusqu'au menu principal
        if saw_text(game, "NOUVELLE PARTIE", since):
            break
        game.tap("START"); game.wait(60)
    else:
        raise GameError(f"pas de menu principal après le reset : {game.describe()}")
    game.wait(30); game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(120)
    shots = 0
    for i in range(400):
        if game.state.overworld and game.state.map_name == "InsideOfTruck":
            break
        if i in (12, 20, 40, 60):
            game.shot(f"intro_{shots}"); shots += 1
        game.tap("A", hold=4, gap=26)
    else:
        raise GameError(f"le camion n'est pas venu : {game.describe()}")
    wait_until(game, lambda s: s.free, limit=6000)

    # Le texte du professeur est gris (pas la couleur des PNJ de Kanto), dans la boîte de RF
    first = next(i for i, (frame, win, text) in enumerate(game.texts) if frame >= since and "Bonjour" in text)
    expect(game, game.text_colors[first] == TEXT_COLOR_DARK_GRAY,
           f"texte du Prof. Seko en gris (couleur {game.text_colors[first]})")
    expect(game, option(game, OPTION_PLAYER_CHARACTER) == 0, "PERSO remis à BRICE/FLORA")
    for number, name in ((OPTION_DIALOG_STYLE, "DIALOGUE"), (OPTION_FONT, "POLICE"), (OPTION_MENU_STYLE, "MENUS")):
        expect(game, option(game, number) == 1, f"{name} gardé à KANTO")
