# Les sons de Kanto sont ceux de Rouge Feu, pas un son d'Émeraude de même nom (docs/CONNAISSANCE-JEU.md, « Sons ») :
# - porte : SE_DOOR de RF = SE_RG_DOOR (SE_DOOR d'Émeraude = SE_RS_DOOR de RF) ;
# - soins hors Centre (EventScript_OutOfCenterPartyHeal) : MUS_HEAL de RF = MUS_HEAL d'Émeraude, pas MUS_RG_HEAL
#   (MUS_HEAL_UNUSED de RF, jamais joué dans RF) ;
# - caisse (achat en boutique de RF) : SE_SHOP de RF = SE_RG_SHOP (SE_SHOP d'Émeraude = SE_RS_SHOP de RF).
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.dev("jeu.rencontres", 0)

    # La porte de la maison du joueur (Bourg Palette, 6,7) : on y entre par le bas
    game.warp("PalletTown", 6, 8)
    frame = game.frames
    game.press("UP", 16)
    wait_until(game, lambda s: s.map_name == "PalletTown_PlayersHouse_1F" and s.free, limit=600)
    expect_sound(game, "SE_RG_DOOR", frame)
    expect(game, not any(name == "SE_DOOR" for f, name in game.sounds if f >= frame), "pas la porte d'Émeraude")

    # Les soins hors Centre
    frame = game.frames
    game.script("EventScript_OutOfCenterPartyHeal")
    wait_until(game, lambda s: s.free, limit=900)
    expect_sound(game, "MUS_HEAL", frame)       # une fanfare : un autre lecteur que la musique de la carte
    expect(game, not any(name == "MUS_RG_HEAL" for f, name in game.sounds if f >= frame), "pas MUS_RG_HEAL")

    # La caisse : un achat à la boutique d'Argenta (écran de RF, MENUS = KANTO), vendeur en (2, 3)
    game.dev("jeu.options", 11, 1)
    game.money(10000)
    game.warp("PewterCity_Mart", 3, 3)
    since, frame = mark(game), game.frames
    game.tap("LEFT", gap=20)                    # face au vendeur
    game.tap("A", gap=30)
    for _ in range(40):                         # « Bonjour! », ACHETER, le 1er objet, quantité 1, OUI
        if any(name == "SE_RG_SHOP" for f, name in game.sounds if f >= frame):
            break
        game.tap("A", gap=30)
    expect_sound(game, "SE_RG_SHOP", frame)
    expect(game, not any(name == "SE_SHOP" for f, name in game.sounds if f >= frame), "pas la caisse d'Émeraude")
