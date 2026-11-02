# Outils de debug (src/debug_tools.c, docs/DEVTOOLS.md) : chaque commande répond dans le banc (« !dev »), puis
# l'écran des outils du menu DEBUG (src/debug_tools_menu.c) : catégorie Jeu > État du moteur (résultat qui défile),
# Graphismes > Palette (saisie des nombres), retour au menu DEBUG.
from driver import *

FIXTURE = "kanto"

# Ce que chaque commande doit dire de la partie de départ (Bourg Palette, équipe vide)
EXPECTED = {
    "jeu.etat": "cb2 CB2_Overworld",
    "jeu.options": "POLICE (1 = Kanto) = 0",
    "carte.info": "BOURG PALETTE",
    "carte.objets": "joueur",
    "scripts.contexte": "contexte global",
    "scripts.flag 2165": "flag 2165 = 0",
    "scripts.var 16384": "var 0x4000",
    "joueur.equipe": "",
    "joueur.sac": "argent 3000",
    "combat.etat": "en combat 0",
    "gfx.sprites": "MovementType_Player",
    "gfx.palette 1 0": "palette OBJ 0",
    "gfx.bg": "DISPCNT",
    "gfx.bgligne 0 0": ":",
    "gfx.tile 0 0": "00000000",
    "gfx.fenetres": "fenetre 0",
    "texte.imprimantes": "",
    "son.etat": "musique",
    "sys.etat": "jour/nuit",
}


def play(game):
    continue_game(game)

    # Le registre : chaque commande, et la liste (aide) les donne toutes
    listing = game.dev("aide")
    for line, words in EXPECTED.items():
        expect(game, line.split()[0] in listing, f"{line.split()[0]} dans la liste")
        text = game.dev(*line.split())
        expect(game, words in text, f"{line} : « {words} »")
    try:
        game.dev("inexistante")
        expect(game, False, "une commande inconnue est refusée")
    except GameError:
        expect(game, True, "une commande inconnue est refusée")

    # L'écran du menu DEBUG : DEBUG (1re entrée du menu Start) > Outils (sondes), avant-dernière entrée
    since = mark(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 16, gap=10); game.wait(10); game.tap("A"); game.wait(30)
    game.shot("categories")
    game.tap("A"); game.wait(30)                    # Jeu
    game.tap("A"); game.wait(60)                    # État du moteur
    game.shot("etat")
    expect_text(game, "jeu.etat", since)
    expect_text(game, "cb2", since)
    game.tap("DOWN", 3, gap=10); game.wait(20)
    game.shot("etat_defile")
    game.tap("B"); game.wait(20); game.tap("B"); game.wait(20)   # retour aux catégories
    game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(30)  # Graphismes
    game.tap("DOWN"); game.tap("A"); game.wait(30)  # Palette : 2 nombres
    game.tap("UP"); game.wait(10)                   # 1er nombre = 1 (OBJ)
    game.shot("saisie")
    game.tap("A"); game.wait(10); game.tap("A"); game.wait(60)
    game.shot("palette")
    expect_text(game, "palette OBJ 0", since)
    for _ in range(4):                              # résultat, commandes, catégories, puis le menu DEBUG
        game.tap("B"); game.wait(30)
    expect_text(game, "Outils (sondes)", since)
    game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free)
