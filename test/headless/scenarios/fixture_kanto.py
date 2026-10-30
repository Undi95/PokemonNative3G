# Sauvegarde de départ « kanto » (FIXTURE = "kanto") : nouvelle partie avec --kanto-start 1, le joueur
# est libre à Bourg Palette, équipe vide, menu DEBUG disponible (build KANTO_DEBUG=1).
from driver import expect_map, new_kanto_game, save

SUITE = False


def play(game):
    new_kanto_game(game)
    expect_map(game, "PalletTown")
    save(game)
