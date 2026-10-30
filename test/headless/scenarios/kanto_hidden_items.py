# Objets cachés de Rouge Feu (2026-10-30) : jetons cachés du Casino de Céladopole (quantité), Restes « sous les pieds »
# du Cap Falaise (PP MAX : rien avec A, trouvés avec le CHERCH'OBJET quand on est dessus).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until


def use_itemfinder(game):
    """Sac > OBJ. RARES > CHERCH'OBJET > UTILIS."""
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    game.tap("RIGHT", 4, gap=40); game.wait(60)
    game.tap("UP", 40, gap=4); game.wait(30)
    for _ in range(30):
        last = [t for _, w, t in game.texts if w == 1][-1]
        if "objets in" in last:
            break
        game.tap("DOWN", gap=10)
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(150)


def play(game):
    continue_game(game)

    # Casino : 10 jetons cachés en (2, 4), avec la BOITE JETONS
    game.flag("FLAG_KANTO_GOT_COIN_CASE", 1)
    game.item("ITEM_COIN_CASE", 1)
    game.warp("CeladonCity_GameCorner", 2, 5); game.wait(30)
    since_coins = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "JETONS", since_coins)
    finish_dialog(game)
    expect_flag(game, "FLAG_KANTO_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS", 1)

    # Cap Falaise : PP MAX sous les pieds en (16, 28) : rien avec A face à la case
    game.item("ITEM_ITEMFINDER", 1)
    leftovers = game.item("ITEM_PP_MAX")
    game.warp("TwoIsland_CapeBrink", 16, 29); game.wait(30)
    since_a = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    expect(game, not saw_text(game, "PP MAX", since_a), "rien avec A (objet sous les pieds)")
    game.warp("TwoIsland_CapeBrink", 16, 28); game.wait(30)
    since_finder = mark(game)
    use_itemfinder(game)
    for _ in range(20):
        if game.state.free and saw_text(game, "PP MAX", since_finder):
            break
        game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free)

    # Vérifications
    expect_text(game, "trouve 10 JETONS", since_coins)
    expect_text(game, "PP MAX", since_finder)
    expect_item(game, "ITEM_PP_MAX", leftovers + 1)
    expect_flag(game, "FLAG_KANTO_HIDDEN_ITEM_TWO_ISLAND_CAPE_BRINK_PP_MAX", 1)
