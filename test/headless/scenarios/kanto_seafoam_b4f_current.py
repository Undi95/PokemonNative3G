# Îles Écume B4F (2026-11-03, docs/A-TESTER.md) : tomber par un trou du B3F tant que les deux rochers n'arrêtent pas le
# courant du B4F. Comme dans Rouge Feu (SeafoamIslands_B4F_EventScript_EnterByFalling) : le courant emporte le joueur
# (RideCurrentFar / Close selon la colonne) et le dépose sur la terre, à pied (SeafoamIslandsB4F_CurrentDumpsPlayerOnLand).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)

SURFING = 0x08    # PLAYER_AVATAR_FLAG_SURFING


def fall(game, hole):
    """Depuis la case à gauche du trou du B3F, un pas dedans ; rend (carte, case, avatar, comportement de la case)."""
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B4F_BOULDER_1", 1)    # rochers pas encore poussés : le courant passe
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B4F_BOULDER_2", 1)
    game.flag("FLAG_KANTO_STOPPED_SEAFOAM_B4F_CURRENT", 0)
    game.warp("SeafoamIslands_B3F", hole[0] - 1, hole[1]); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("RIGHT", 16)
    for _ in range(60):
        game.wait(20)
        if game.state.map_name == "SeafoamIslands_B4F" and game.state.free:
            break
    game.wait(30)
    info = game.dev("carte.info").splitlines()[2]
    avatar = int(info.split("avatar ")[1].split(",")[0], 16)
    x, y = game.state.pos
    tile = game.dev("carte.metatuiles", x, y, 1, 1)
    return game.state.map_name, (x, y), avatar, tile


def play(game):
    continue_game(game)
    for hole in ((6, 18), (9, 18)):
        map_name, pos, avatar, tile = fall(game, hole)
        game.note(f"trou {hole} : {map_name} {pos} avatar {avatar:#x} {tile}")
        expect(game, map_name == "SeafoamIslands_B4F", f"trou {hole} : tombé au B4F ({map_name})")
        expect(game, not avatar & SURFING, f"trou {hole} : déposé à pied ({pos}, avatar {avatar:#x})")
        # Le courant mène en (12, 13), dans l'eau au bord ; le débarquement (saut vers le nord) pose sur (12, 12),
        # la terre (escalier de roche)
        expect(game, pos == (12, 12), f"trou {hole} : sur le rivage en (12, 12) ({pos} ; {tile.strip()[:60]})")
