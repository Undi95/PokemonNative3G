# Vitesse sur les escaliers de roche du Plateau Indigo (MB_ROCK_STAIRS, rangées 14, 16 et 18 ; 2026-11-03,
# docs/A-TESTER.md), mesurée pas à pas en descendant la colonne x = 11. Comme dans Rouge Feu
# (PlayerIsMovingOnRockStairs : vers le bas, la case d'arrivée ; vers le haut, celle de départ) :
# marche 16 images par case, 23 sur l'escalier (PlayerWalkSlow, UpdateWalkSlowAnim : 2 pixels toutes les 3 images, le
# 16e pixel à la 23e image) ; course 8, 11 sur l'escalier (PlayerRunSlow : 1 puis 2 pixels). Vélo de RF sur l'escalier :
# PlayerWalkFast (8) ; dans la fusion, le Vélo Course y est bridé à la 2e vitesse (8, au lieu de 4 lancé) et le Vélo
# Cross roule comme ailleurs (6 : PlayerRideWaterCurrent, sa vitesse d'Émeraude).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import names

STAIRS = (14, 16, 18)


def descend(game, buttons, bike=None):
    """Descend de (11, 7) à (11, 19), à vélo si bike (enregistré sur SELECT après le téléport, qui remet à pied) :
    {rangée d'arrivée : images du pas qui y mène}."""
    game.warp("IndigoPlateau_Exterior", 11, 7); game.wait(30)
    wait_until(game, lambda s: s.free)
    if bike:
        game.dev("joueur.enregistre", names.number(bike))
        game.tap("SELECT", hold=4); game.wait(30)
        wait_until(game, lambda s: s.free)
    changes = []
    last = game.state.pos
    for _ in range(600):
        game.press(buttons, 1)
        pos = game.state.pos
        if pos != last:
            changes.append((game.frames, pos))
            last = pos
        if pos[1] >= 19 or game.state.map_name != "IndigoPlateau_Exterior":
            break
    steps = {p0[1]: f1 - f0 for (f0, p0), (f1, _p1) in zip(changes, changes[1:])}
    game.note(f"{buttons} : {steps}")
    return steps


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_B_DASH", 1)                  # chaussures de course
    game.item("ITEM_MACH_BIKE", 1)
    game.item("ITEM_ACRO_BIKE", 1)

    walk = descend(game, "DOWN")
    run = descend(game, "DOWN+B")
    mach = descend(game, "DOWN", "ITEM_MACH_BIKE")
    acro = descend(game, "DOWN", "ITEM_ACRO_BIKE")

    for name, steps, normal, stairs in (("marche", walk, 16, 23), ("course", run, 8, 11)):
        expect(game, all(steps.get(y) == stairs for y in STAIRS),
               f"{name} : {stairs} images par case sur l'escalier ({[steps.get(y) for y in STAIRS]})")
        expect(game, all(steps.get(y) == normal for y in (15, 17)),
               f"{name} : {normal} entre les marches ({[steps.get(y) for y in (15, 17)]})")
    expect(game, steps_before(mach) == 4, f"Vélo Course lancé : 4 images par case avant l'escalier ({steps_before(mach)})")
    expect(game, all(mach.get(y) == 8 for y in STAIRS),
           f"Vélo Course : 2e vitesse (8) sur l'escalier ({[mach.get(y) for y in STAIRS]})")
    expect(game, all(acro.get(y) == 6 for y in (12, 13) + STAIRS + (15, 17)),
           f"Vélo Cross : 6 partout, escalier compris ({[acro.get(y) for y in (12, 13) + STAIRS + (15, 17)]})")


def steps_before(steps):
    return steps.get(13)
