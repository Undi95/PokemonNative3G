# ZARBI des Ruines de Tanoby (2026-10-30, wild_encounter.c de RF) : aucune rencontre avant l'ouverture des ruines ;
# ensuite, la lettre dépend de la chambre et de la case (MONEAN : A ou ?, VIAPOIS : Z ou !).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, finish_dialog, wait_until, walk_to


class Battle(Exception):
    pass


def stop_at_battle(game):
    raise Battle


def unown_letter(personality):
    """GET_UNOWN_LETTER (include/pokemon.h) : 0 = A … 25 = Z, 26 = !, 27 = ?"""
    p = personality
    return ((((p >> 24) & 3) << 6) | (((p >> 16) & 3) << 4) | (((p >> 8) & 3) << 2) | (p & 3)) % 28


def pace(game, steps):
    """Allers-retours sur la rangée du bas ; True si un combat commence."""
    try:
        for i in range(steps):
            walk_to(game, 2 if i % 2 == 0 else 20, 14, on_battle=stop_at_battle)
    except Battle:
        return True
    return False


def run_away(game):
    wait_until(game, lambda s: s.battle and not s.script, limit=1200)
    for _ in range(10):
        game.wait(120)
        if not game.state.battle:
            break
        game.tap("DOWN"); game.tap("RIGHT"); game.tap("A"); game.wait(200)
        game.tap("A", 3, gap=40)
    wait_until(game, lambda s: s.free, limit=1500)


def letters_in(game, chamber, allowed, count):
    game.warp(chamber, 11, 14); game.wait(30)
    seen = []
    for _ in range(count):
        if not pace(game, 40):
            break
        wait_until(game, lambda s: s.foe, limit=600)
        foe = game.state.foe[0]
        if foe[0] == names_species("SPECIES_UNOWN"):
            seen.append(unown_letter(foe[6]))
        run_away(game)
    game.note(f"lettres vues à {chamber} : {seen}")
    expect(game, len(seen) >= 1, f"ZARBI rencontrés à {chamber}")
    expect(game, all(l in allowed for l in seen), f"lettres de {chamber} dans {sorted(allowed)}")


def names_species(name):
    import names
    return names.value(name)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.flag("FLAG_KANTO_SYS_UNLOCKED_TANOBY_RUINS", 0)
    game.warp("SevenIsland_TanobyRuins_MoneanChamber", 11, 14); game.wait(30)
    expect(game, not pace(game, 12), "pas de ZARBI avant l'ouverture des ruines")

    game.flag("FLAG_KANTO_SYS_UNLOCKED_TANOBY_RUINS", 1)
    letters_in(game, "SevenIsland_TanobyRuins_MoneanChamber", {0, 27}, 3)
    letters_in(game, "SevenIsland_TanobyRuins_ViapoisChamber", {25, 26}, 3)
