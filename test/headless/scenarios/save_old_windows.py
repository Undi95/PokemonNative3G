# Sauvegarde Windows de la version 1.1 (saves/windows-1.1-hoenn.sav : fixture « hoenn » faite par l'exe de la 1.1,
# MinGW et ses champs de bits à la Microsoft, struct ObjectEvent de 40 octets au lieu de 36). Elle doit se continuer
# telle quelle sur toutes les plateformes (conversion au chargement, src/save.c SaveBlock1FromOldWindows) : joueur dans
# sa chambre, et une fois resauvegardée, le fichier est au format GBA (le même que Linux et Android).
from driver import *

SAVE = "windows-1.1-hoenn.sav"


def play(game):
    since = mark(game)
    continue_game(game)
    expect_map(game, "LittlerootTown_BrendansHouse_2F", (5, 2))
    info = game.dev("sys.sauvegarde")
    expect(game, "ancien format Windows" in info, "dernier secteur de SaveBlock1 reconnu : ancien format Windows")
    expect(game, "FAUX" not in info, "aucun secteur rejeté")
    # Le joueur bouge (les objets de la carte viennent de la sauvegarde convertie)
    walk_to(game, 5, 4)
    expect_map(game, "LittlerootTown_BrendansHouse_2F", (5, 4))
    save(game)
    info = game.dev("sys.sauvegarde")
    expect(game, "compteur 2," in info and "ancien format" in info, "nouvelle sauvegarde dans l'autre emplacement")
    # Après un reset, la nouvelle sauvegarde (format GBA cette fois) remet le joueur où il l'a faite
    game.press("A+B+START+SELECT", 2)
    continue_game(game)
    expect_map(game, "LittlerootTown_BrendansHouse_2F", (5, 4))
