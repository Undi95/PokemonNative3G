# Vérifie le banc de test lui-même : reprise de la sauvegarde de départ, commandes de test (flags,
# variables, objets, Pokémon, téléport, sauvegarde), texte lu par le journal, écran de référence.
from driver import (continue_game, expect, expect_flag, expect_item, expect_map, expect_party, expect_text,
                    expect_var, mark, talk_to_object)

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    expect_map(game, "PalletTown")

    game.flag("FLAG_BADGE01_GET", 1)
    expect_flag(game, "FLAG_BADGE01_GET", 1)
    game.flag("FLAG_BADGE01_GET", 0)
    expect_flag(game, "FLAG_BADGE01_GET", 0)
    game.var("VAR_TEMP_1", 7)
    expect_var(game, "VAR_TEMP_1", 7)

    before = game.item("ITEM_POTION")
    game.item("ITEM_POTION", 3)
    expect_item(game, "ITEM_POTION", before + 3)

    game.give_mon("SPECIES_PIKACHU", 12)
    game.wait(2)
    expect_party(game, "SPECIES_PIKACHU", 12)
    game.heal()

    game.money(1234)
    expect(game, game.money() == 1234, "argent 1234")

    # Le premier PNJ de Bourg Palette
    since = mark(game)
    talk_to_object(game, *game.state.objects[0])
    expect(game, any(win == 0 for _, win, _ in game.texts[since:]), "le PNJ a parlé (boîte de dialogue)")

    since = mark(game)
    game.warp("ViridianCity", 26, 28)
    expect_map(game, "ViridianCity", (26, 28))
    game.wait(60)
    expect_text(game, "JADIELLE", since)    # le nom de la carte s'affiche
