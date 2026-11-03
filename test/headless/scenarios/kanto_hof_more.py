# Panthéon et crédits de Kanto (docs/A-TESTER.md, 2026-11-03) : à l'enregistrement, le moniteur de RF (16x16, 4
# images, field_effect.c, Fusion_IsInKanto) et pas les écrans d'Émeraude (captures « enregistrement-N ») ; pendant le
# défilé des crédits, MUS_RG_CREDITS jouée une seule fois, sans autre musique ni arrêt jusqu'au retour à Bourg Palette.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import give_mewtwo
from menu_helpers import texts, open_start_entry
from pc_menu_regions import pc_menu


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    hoenn_before = game.dev("jeu.stat", names.number("GAME_STAT_ENTERED_HOF")).strip()
    game.wait(30); game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 24); game.tap("A"); game.wait(200)

    # L'enregistrement (FLDEFF_HALL_OF_FAME_RECORD) : le moniteur de la salle
    shots = 0
    for _ in range(80):
        if any("HallOfFameRecord" in game.function(t) for t in game.state.tasks):
            for i in range(8):
                game.shot(f"enregistrement-{i}"); game.wait(12)
            shots = 8
            break
        game.tap("A"); game.wait(30)
    expect(game, shots == 8, "enregistrement du Panthéon filmé")

    playing = []                                             # (image, musique en cours) toutes les 60 images
    for _ in range(400):
        if game.state.free and game.state.map == "PalletTown":
            break
        playing.append((game.frames, game.state.bgm))
        game.tap("A", gap=60)
    credits = [(f, s) for f, s in game.songs if s == "MUS_RG_CREDITS"]
    start = credits[0][0] if credits else None
    # Après le défilé, le jeu repart sur l'intro (comme RF) : la fin des crédits = la musique suivante
    end = next((f for f, s in game.songs if start is not None and f > start), game.frames)
    song = names.value("MUS_RG_CREDITS")
    # (RF baisse la musique à la toute fin : FadeOutMapMusic(16) de credits.c, les 400 dernières images ne comptent pas)
    gaps = [f for f, bgm in playing if start is not None and start + 60 < f < end - 400 and bgm != song]
    game.note(f"CRÉDITS de {start} à {end} ; musique différente aux images {gaps[:10]}")
    expect(game, len(credits) == 1, f"MUS_RG_CREDITS une seule fois ({credits})")
    expect(game, start is not None and end - start > 10000 and not gaps,
           f"MUS_RG_CREDITS sans arrêt sur tout le défilé ({start} à {end}, ailleurs {gaps[:10]})")
    expect_map(game, "PalletTown")

    # Le PC d'un Centre de Kanto > PANTHEON : l'équipe enregistrée (Panthéon de RF, capture « pc-pantheon »)
    entries, _ = pc_menu(game, "kanto")
    game.tap("DOWN", entries.index("PANTHEON"), gap=12); game.wait(10)
    since = mark(game)
    game.tap("A"); game.wait(300)
    game.shot("pc-pantheon")
    shown = " ".join(t for _, t in texts(game, since))
    game.note(f"PC PANTHEON : {shown}")
    expect(game, "MEWTWO" in shown, f"le Panthéon du PC montre l'équipe enregistrée ({shown[:120]})")
    # L'entrée est comptée, comme la sauvegarde du Panthéon de RF : « PANTHEON Nº 1 » ; dans le compteur de Kanto,
    # celui de Hoenn ne bouge pas (compteurs séparés, décision du 2026-11-03)
    expect(game, "PANTHEON Nº 1" in shown, f"Panthéon n° 1 ({shown[:60]})")
    kanto = game.dev("jeu.stat", names.number("GAME_STAT_KANTO_ENTERED_HOF")).strip()
    hoenn = game.dev("jeu.stat", names.number("GAME_STAT_ENTERED_HOF")).strip()
    game.note(f"COMPTEURS : Kanto « {kanto} », Hoenn « {hoenn_before} » puis « {hoenn} »")
    expect(game, kanto.endswith("= 1") and hoenn == hoenn_before, f"compteurs séparés ({kanto} ; {hoenn_before} → {hoenn})")
    for i in range(20):
        if game.state.free:
            break
        game.tap("AB"[i % 2]); game.wait(60)

    # La carte de dresseur de Kanto : une étoile (couleur) et la date du premier Panthéon au verso (captures « carte »)
    game.tap("START"); game.wait(40)
    entries, _ = game.start_menu()
    game.tap("B"); game.wait(30)
    standard = ("POKéDEX", "POKéMON", "SAC", "POKéNAV", "SAUVER", "OPTIONS", "RETOUR", "DEBUG")
    name = next(n for _, n in entries if n not in standard)        # l'entrée du nom du joueur
    open_start_entry(game, name); game.wait(240)
    since = mark(game)
    game.shot("carte-recto")
    game.tap("A"); game.wait(120)
    game.shot("carte-verso")
    back = " ".join(t for _, t in texts(game, since))
    game.note(f"CARTE verso : {back}")
    expect(game, "PANTHEON" in back.upper(), f"verso de la carte : le premier Panthéon ({back[:120]})")
