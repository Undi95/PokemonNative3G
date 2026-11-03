# Menu DEBUG > Outils > Scripts > Drapeaux et variables (scripts.drapeaux, src/debug_tools.c) : les catégories,
# A ouvre « Hoenn : Badges », A bascule le 1er badge (le drapeau change dans la partie), B revient aux catégories
# avec le curseur dessus ; une variable change avec R. Les noms marchent aussi dans les commandes.
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    expect(game, game.flag("FLAG_BADGE01_GET") == 0, "pas de badge au départ")

    since = mark(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30)          # DEBUG
    game.tap("DOWN", 16, gap=10); game.wait(10); game.tap("A")                # Outils (sondes)
    wait_text(game, "Scripts", since); game.wait(30)
    game.tap("DOWN", 2, gap=16); game.wait(10); game.tap("A")                 # Scripts
    wait_text(game, "Histoires finies", since); game.wait(30)                 # « Drapeaux et variables » : la suivante
    game.tap("DOWN", 6, gap=16); game.wait(10); game.tap("A"); game.wait(60)  # Drapeaux et variables (après Histoires finies)
    check_screen(game, "devtools_flags-categories")
    expect_text(game, "Hoenn : Badges : 8 (0 ON)", since)

    game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(60)          # Hoenn : Badges
    expect_text(game, "BADGE01 GET --", since)      # le jeu n'a pas de « _ » : une espace
    game.tap("A"); game.wait(60)                                           # BADGE01 : ON
    check_screen(game, "devtools_flags-badges")
    expect_text(game, "BADGE01 GET ON", since)
    expect(game, game.flag("FLAG_BADGE01_GET") == 1, "le badge 1 est à ON dans la partie")

    game.tap("B"); game.wait(60)                                           # retour : Badges sous le curseur
    expect_text(game, "Hoenn : Badges : 8 (1 ON)", since)

    # Kanto : Variables, la 1re : R l'augmente de 1
    categories = game.dev("scripts.drapeaux").splitlines()
    index = next(i for i, c in enumerate(categories) if c.startswith("Kanto : Variables"))
    name = game.dev("scripts.drapeaux", index).splitlines()[0].split(" = ")[0]
    before = game.var(f"VAR_KANTO_{name}")
    game.tap("DOWN", index - 1, gap=6); game.wait(10); game.tap("A"); game.wait(60)
    game.tap("R"); game.wait(40)
    check_screen(game, "devtools_flags-variables")
    expect(game, game.var(f"VAR_KANTO_{name}") == before + 1, f"VAR_KANTO_{name} : {before} -> {before + 1}")
    for _ in range(10):         # catégories, outils, catégories d'outils, menu DEBUG, menu Start : B jusqu'à la carte
        if game.state.free:
            break
        game.tap("B", gap=40)
    expect(game, game.state.free, "retour sur la carte avec B")
