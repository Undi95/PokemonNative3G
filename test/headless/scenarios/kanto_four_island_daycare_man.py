# Île 4 (2026-11-03, docs/A-TESTER.md) : le vieil homme de la pension se déplace quand un œuf attend
# (FourIsland_EventScript_TrySetDayCareManPos de RF, sur FLAG_PENDING_DAYCARE_EGG, le drapeau de la pension
# d'Émeraude ; avant, le script lisait un drapeau de Kanto jamais posé) : (16, 13) sans œuf, (16, 14) avec.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)


def man_position(game):
    """Arrive sur l'Île 4 et rend la case du vieil homme (objet chargé près du joueur)."""
    game.warp("FourIsland", 16, 17); game.wait(60)
    wait_until(game, lambda s: s.free)
    for line in game.dev("carte.objets").splitlines():
        if "gfx 0x" in line and " en 16," in line:
            return tuple(int(v) for v in line.split(" en ")[1].split()[0].split(","))
    return None


def play(game):
    continue_game(game)
    game.var("VAR_KANTO_MAP_SCENE_FOUR_ISLAND", 1)      # scène du rival déjà vue
    game.flag("FLAG_PENDING_DAYCARE_EGG", 0)
    without = man_position(game)
    game.flag("FLAG_PENDING_DAYCARE_EGG", 1)
    game.warp("FourIsland_PokemonDayCare", 4, 7); game.wait(40)   # le placement se fait en arrivant sur l'île
    with_egg = man_position(game)
    game.note(f"vieil homme : sans œuf {without}, avec œuf {with_egg}")
    expect(game, without == (16, 13), f"sans œuf : devant la pension en (16, 13) ({without})")
    expect(game, with_egg == (16, 14), f"œuf qui attend : il s'avance en (16, 14) ({with_egg})")
