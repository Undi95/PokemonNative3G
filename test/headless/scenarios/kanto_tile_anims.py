# Animations des tuiles de Kanto (docs/A-TESTER.md, 2026-11-03 ; tileset_anims.c, InitTilesetAnim_Kanto*) : dans une
# carte de chaque tileset animé, les tiles que l'animation recopie (BG_VRAM + TILE_OFFSET_4BPP(n), lus avec gfx.tile)
# changent au fil des images : fleurs, eau et sable des rivages (tileset général), fontaines de Céladopole et de
# Sylphe SARL, vapeur du Mont Braise, porte motorisée de l'arène de Carmin, fleurs de l'arène de Céladopole.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os
from headless import REPO_DIR

# (animation, carte, tile de destination, période de l'animation en images)
ANIMS = (("fleurs", "PalletTown", 508, 64), ("eau des rivages", "PalletTown", 416, 64),
         ("sable des rivages", "PalletTown", 464, 64), ("fontaine de Céladopole", "CeladonCity", 744, 120),
         ("fontaine de Sylphe SARL", "SilphCo_1F", 976, 160), ("vapeur du Mont Braise", "MtEmber_SummitPath_1F", 896, 256),
         ("porte motorisée de Carmin", "VermilionCity_Gym", 880, 15),   # 2 images, une toutes les 2 images
         ("fleurs de l'arène de Céladopole",
                                                                       "CeladonCity_Gym", 739, 256))


def arrival(name):
    """Une case où arriver : la première entrée de la carte."""
    with open(os.path.join(REPO_DIR, "data", "maps", name, "map.json"), encoding="utf-8") as f:
        warp = json.load(f)["warp_events"][0]
    return warp["x"], warp["y"]


def play(game):
    continue_game(game)
    for what, place, tile, period in ANIMS:
        if game.state.map != place:
            game.warp(place, *arrival(place)); game.wait(60)
            finish_dialog(game, settle=40)
        frames = set()
        for _ in range(16):                 # les 4 premiers tiles recopiés (un seul peut ne pas changer)
            frames.add(tuple(game.dev("gfx.tile", 0, tile + k) for k in range(4)))
            game.wait(period // 16 + 1)
        game.note(f"ANIMATION {what} ({place}, tile {tile}) : {len(frames)} images différentes")
        expect(game, len(frames) >= 2, f"{what} : le tile {tile} change ({len(frames)})")
        game.shot(f"{place}-{tile}")
