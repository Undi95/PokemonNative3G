# Musique des combats contre les légendaires (2026-11-03, docs/A-TESTER.md), comme dans Rouge Feu : MEWTWO = thème de
# MEWTWO, ELECTHOR / SULFURA / ARTIKODIN = thème des légendaires (StartLegendaryBattle de RF), DEOXYS (Île Aurore) =
# thème de DEOXYS, LUGIA / HO-OH (Nombril du Monde) = thème des légendaires de RF (BattleSetup_StartLegendaryBattle
# d'Émeraude). On parle au légendaire depuis la case du dessous (Ho-Oh : sa case de déclenchement ; Deoxys : son script,
# triangle résolu) ; le combat est perdu (1 PV) pour passer au suivant.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)

# (nom, carte, case du joueur, script à lancer ou None pour parler au-dessus, musique)
LEGENDARIES = (
    ("MEWTWO", "CeruleanCave_B1F", (7, 13), None, "MUS_RG_VS_MEWTWO"),
    ("ZAPDOS", "PowerPlant", (5, 12), None, "MUS_RG_VS_LEGEND"),
    ("MOLTRES", "MtEmber_Summit", (9, 7), None, "MUS_RG_VS_LEGEND"),
    ("ARTICUNO", "SeafoamIslands_B4F", (9, 3), None, "MUS_RG_VS_LEGEND"),
    ("DEOXYS", "BirthIsland_Exterior", (15, 13), "BirthIsland_Exterior_EventScript_Deoxys", "MUS_RG_VS_DEOXYS"),
    ("LUGIA", "NavelRock_Bottom", (11, 14), None, "MUS_RG_VS_LEGEND"),
    ("HO_OH", "NavelRock_Top", (12, 11), "NavelRock_Top_EventScript_HoOh", "MUS_RG_VS_LEGEND"),
)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 2)    # la sauvegarde de test arrive à Kanto sans équipe
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for name, map_name, (x, y), script, song in LEGENDARIES:
        game.dev("joueur.pv", 0, 1)          # 1 PV : combat perdu au premier coup
        since = game.frames
        battled = []
        try:
            game.warp(map_name, x, y); game.wait(60)
            finish_dialog(game)
            if script:
                game.script(script)
            else:
                talk_to(game, "UP", finish=False)
            # limite large : le légendaire peut enchaîner des capacités de statut (hasard) avant le coup qui met K.O.
            finish_dialog(game, on_battle=lambda g: (battled.append(True), fight_battle(g, limit=4000)))
        except GameError as error:
            game.note(f"{name} : {error}")
        played = [s for f, s in game.songs if f >= since]
        expect(game, battled and song in played, f"{name} : combat avec {song} (musiques : {played[-5:]})")
