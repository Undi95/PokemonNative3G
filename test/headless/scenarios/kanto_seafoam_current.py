# Îles Écume : tomber par un trou de B2F dans l'eau de B3F, quand les rochers n'y sont pas encore (courant actif).
# Comme dans Rouge Feu (2026-11-02) : le joueur arrive à pied (MetatileBehavior_IsSurfableInSeafoamIslands), la fin de
# la chute le met en Surf avec VAR_TEMP_1 = 1, et le script EnterByFalling de B3F le fait suivre le courant jusqu'à
# B4F. Avant, la fusion le mettait en Surf sans courant : l'énigme des rochers était sautée.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B3F_BOULDER_1", 1)   # rochers encore à B2F : le courant de B3F coule
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B3F_BOULDER_2", 1)
    game.flag("FLAG_KANTO_STOPPED_SEAFOAM_B3F_CURRENT", 0)
    game.warp("SeafoamIslands_B2F", 24, 9); game.wait(30)
    game.press("UP", 16)                                      # dans le trou (24, 8)
    for _ in range(600):
        if game.state.map_name == "SeafoamIslands_B4F" and game.state.free:
            break
        game.wait(2)
    expect(game, game.state.map_name == "SeafoamIslands_B4F", f"le courant mène à B4F ({game.state.map_name})")
    expect_song(game, "MUS_RG_SURF")   # le courant l'a emporté en Surf (B3F : VAR_TEMP_1 = 1, puis B4F)
