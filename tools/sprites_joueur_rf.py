#!/usr/bin/env python3
"""Sprites du joueur en style Rouge Feu (à Kanto), depuis le pack de Poffin_Case (« FRHoenn », PokéCommunity).

Le pack donne Brice et Flora dans leur tenue d'Émeraude, dessinés en style Rouge Feu, avec toutes les poses
d'Émeraude et celles de Rouge Feu (surf, objet / Cherche VS, Cherche VS à vélo), et pour Red et Leaf les poses
qu'Émeraude a en plus de Rouge Feu (figures du Vélo Cross, plongée, arrosoir, décoration). Ses PNG sont en couleurs
directes, avec des couleurs qui ne tombent pas pile sur celles de la GBA et quelques pixels parasites : chaque pixel
est ramené à la couleur de la palette du personnage (la même valeur GBA, sinon la plus proche ; le nombre de pixels
corrigés est affiché). Les feuilles « objet » de Rouge Feu du pack sont posées sur une grille irrégulière : chaque
pose est recalée sur la même pose de Red/Leaf (le plus de pixels en commun).

Usage (racine du dépôt) : python3 tools/sprites_joueur_rf.py DOSSIER_DU_PACK
Écrit graphics/kanto/object_events/pics/people/{brendan,may}_*.png, {red,green}_{acro_bike,underwater,watering,
decorating}.png et les palettes graphics/kanto/object_events/palettes/{brendan,may}[_reflection].pal.
"""
import os
import sys

from PIL import Image

PEOPLE = "graphics/kanto/object_events/pics/people/"
PALETTES = "graphics/kanto/object_events/palettes/"
UNDERWATER_PAL = "graphics/object_events/palettes/player_underwater.pal"
TRANSPARENT = (115, 197, 164)

# Palettes de Brice et Flora en style RF : l'ordre de la palette de PNJ « blanche » de Rouge Feu (npc_white.pal, celle
# de leurs sprites de l'Union Room), le jaune de la tenue de Rubis/Saphir devenu le vert d'Émeraude (5-6). Brice a le
# gris moyen du chapeau, Flora l'olive des cheveux (12) : le pack les partage, 17 couleurs en tout.
BRENDAN_PAL = [TRANSPARENT, (248, 216, 184), (240, 192, 152), (216, 152, 112), (120, 64, 64), (103, 203, 124),
               (78, 157, 95), (56, 56, 24), (224, 112, 80), (144, 64, 40), (80, 16, 0), (192, 200, 216),
               (136, 144, 144), (72, 72, 88), (255, 255, 255), (0, 0, 0)]
MAY_PAL = BRENDAN_PAL[:12] + [(120, 112, 64)] + BRENDAN_PAL[13:]

ITEM = "objet"  # feuille « objet » de RF du pack (grille irrégulière)

# (fichier du pack, largeur des images, nombre d'images, fichier écrit, palette)
SHEETS = [
    ("PLAYER/E/100.png", 16, 18, "brendan_normal.png", "brendan"),        # marche + course
    ("PLAYER/E/101.png", 32, 9, "brendan_bike.png", "brendan"),
    ("PLAYER/E/102.png", 32, 27, "brendan_acro_bike.png", "brendan"),
    ("PLAYER/E/2(FR).png", 16, 12, "brendan_surf.png", "brendan"),       # surf de RF (assis, 16x32)
    ("PLAYER/E/3(FR).png", ITEM, 9, "brendan_item.png", "brendan"),      # capacité de terrain et Cherche VS de RF
    ("PLAYER/E/6(FR).png", 32, 6, "brendan_vs_seeker_bike.png", "brendan"),
    ("PLAYER/E/137.png", 32, 12, "brendan_fish.png", "brendan"),
    ("PLAYER/E/111.png", 32, 9, "brendan_underwater.png", "underwater"),
    ("PLAYER/E/191.png", 32, 9, "brendan_watering.png", "brendan"),
    ("PLAYER/E/193.png", 16, 1, "brendan_decorating.png", "brendan"),
    ("PLAYER/E/105.png", 32, 18, "may_normal.png", "may"),               # son chignon dépasse 16 pixels
    ("PLAYER/E/106.png", 32, 9, "may_bike.png", "may"),
    ("PLAYER/E/107.png", 32, 27, "may_acro_bike.png", "may"),
    ("PLAYER/E/9(FR).png", 16, 12, "may_surf.png", "may"),
    ("PLAYER/E/12(FR).png", ITEM, 9, "may_item.png", "may"),
    ("PLAYER/E/13(FR).png", 32, 6, "may_vs_seeker_bike.png", "may"),
    ("PLAYER/E/138.png", 32, 12, "may_fish.png", "may"),
    ("PLAYER/E/112.png", 32, 9, "may_underwater.png", "underwater"),
    ("PLAYER/E/192.png", 32, 9, "may_watering.png", "may"),
    ("PLAYER/E/194.png", 16, 1, "may_decorating.png", "may"),
    # Red et Leaf : les 9 premières images du Vélo Cross (vélo ordinaire) sont celles de Rouge Feu, le pack n'a que
    # les figures (9-26)
    ("EXTRA/102(Red).png", 32, 27, "red_acro_bike.png", "red"),
    ("EXTRA/111(Red).png", 32, 9, "red_underwater.png", "underwater"),
    ("EXTRA/191(Red).png", 32, 9, "red_watering.png", "red"),
    ("EXTRA/193(Red).png", 16, 1, "red_decorating.png", "red"),
    ("EXTRA/107(Leaf).png", 32, 27, "green_acro_bike.png", "green"),
    ("EXTRA/112(Leaf).png", 32, 9, "green_underwater.png", "underwater"),
    ("EXTRA/192(Leaf).png", 32, 9, "green_watering.png", "green"),
    ("EXTRA/194(Leaf).png", 16, 1, "green_decorating.png", "green"),
]
BIKE_FROM_RF = {"red_acro_bike.png": "red_bike.png", "green_acro_bike.png": "green_bike.png"}
ITEM_REFERENCE = {"brendan": "red_item.png", "may": "green_item.png"}

# Palettes de Rouge Feu et leurs reflets (sur l'eau) : le reflet d'une nouvelle couleur part du reflet de la couleur
# officielle la plus proche
RF_REFLECTIONS = [("player", "player_reflection"), ("npc_white", "npc_white_reflection"),
                  ("npc_blue", "npc_blue_reflection"), ("npc_pink", "npc_pink_reflection"),
                  ("npc_green", "npc_green_reflection"), ("rs_quinty_plump", "rs_quinty_plump_reflection")]


def gba(c):
    return tuple(v >> 3 for v in c)


def pal_value(c):
    """valeur 8 bits d'une couleur, comme les .pal du décomp (5 bits × 255 / 31)"""
    return tuple(round((v >> 3) * 255 / 31) for v in c)


def read_pal(path):
    words = open(path).read().split()
    return [tuple(int(v) for v in words[3 + 3 * i:6 + 3 * i]) for i in range(16)]


def write_pal(path, colors):
    with open(path, "w", newline="\r\n") as f:
        f.write("JASC-PAL\n0100\n16\n")
        for c in colors:
            f.write("%d %d %d\n" % pal_value(c))


def reflection(colors):
    pairs = []
    for base, refl in RF_REFLECTIONS:
        pairs += zip(read_pal(PALETTES + base + ".pal")[1:], read_pal(PALETTES + refl + ".pal")[1:])
    out = [read_pal(PALETTES + "player_reflection.pal")[0]]
    for c in colors[1:]:
        b, r = min(pairs, key=lambda p: sum((x - y) ** 2 for x, y in zip(gba(c), gba(p[0]))))
        out.append(tuple(max(0, min(255, rv + cv - bv)) for rv, cv, bv in zip(r, c, b)))
    return out


def to_indexed(frame, palette, bg):
    """image indexée dans `palette` (0 = transparent) et le nombre de pixels ramenés à la couleur la plus proche"""
    out = Image.new("P", frame.size)
    out.putpalette([v for c in palette for v in pal_value(c)] + [0] * (768 - 48))
    exact = {gba(c): i for i, c in enumerate(palette) if i}
    fixed = 0
    for y in range(frame.height):
        for x in range(frame.width):
            c = frame.getpixel((x, y))
            if c == bg:
                continue
            i = exact.get(gba(c))
            if i is None:
                i = min(range(1, 16), key=lambda k: sum((a - b) ** 2 for a, b in zip(c, palette[k])))
                fixed += 1
            out.putpixel((x, y), i)
    return out, fixed


def item_frames(sheet, bg, reference, width):
    """les 9 poses d'une feuille « objet » du pack, chacune recalée sur la même pose de `reference` (16x32)"""
    columns = [x for x in range(sheet.width) if any(sheet.getpixel((x, y)) != bg for y in range(32))]
    groups = []
    for x in columns:
        if groups and x == groups[-1][1] + 1:
            groups[-1][1] = x
        else:
            groups.append([x, x])
    if len(groups) != 9:
        sys.exit(f"feuille objet : {len(groups)} poses au lieu de 9")
    frames = []
    for k, (a, b) in enumerate(groups):
        ref = {(x, y) for x in range(16) for y in range(32) if reference.getpixel((k * 16 + x, y))}
        best = None
        for x0 in range(a - 16, b + 1):          # la pose de référence couvre x0..x0+15 dans la feuille
            fig = {(x - x0, y) for x in range(a, b + 1) for y in range(32) if sheet.getpixel((x, y)) != bg}
            score = len(fig & ref) - len(fig ^ ref)
            if best is None or score > best[0]:
                best = (score, x0)
        x0 = best[1] - (width - 16) // 2
        frame = Image.new("RGB", (width, 32), bg)
        for x in range(width):
            if 0 <= x0 + x < sheet.width:
                for y in range(32):
                    frame.putpixel((x, y), sheet.getpixel((x0 + x, y)))
        if any(not (x0 <= x < x0 + width) for x in range(a, b + 1)):
            sys.exit(f"feuille objet, pose {k} : plus large que {width} pixels")
        frames.append(frame)
    return frames


def main():
    pack = sys.argv[1]
    palettes = {"brendan": BRENDAN_PAL, "may": MAY_PAL, "underwater": read_pal(UNDERWATER_PAL),
                "red": read_pal(PALETTES + "player.pal"), "green": read_pal(PALETTES + "player.pal")}
    for name, colors in (("brendan", BRENDAN_PAL), ("may", MAY_PAL)):
        write_pal(PALETTES + name + ".pal", colors)
        write_pal(PALETTES + name + "_reflection.pal", reflection(colors))
    for source, width, count, target, pal in SHEETS:
        sheet = Image.open(os.path.join(pack, source)).convert("RGB")
        bg = sheet.getpixel((0, 0))
        if width == ITEM:
            # Flora a des poses de 18 pixels de large : images de 32
            frame_width = 32 if pal == "may" else 16
            frames = item_frames(sheet, bg, Image.open(PEOPLE + ITEM_REFERENCE[pal]), frame_width)
        else:
            frame_width = width
            if sheet.width < width * count:
                sys.exit(f"{source} : {sheet.width} pixels de large pour {count} images de {width}")
            frames = [sheet.crop((k * width, 0, (k + 1) * width, 32)) for k in range(count)]
        out = Image.new("P", (frame_width * count, 32))
        out.putpalette([v for c in palettes[pal] for v in pal_value(c)] + [0] * (768 - 48))
        total = 0
        for k, frame in enumerate(frames):
            indexed, fixed = to_indexed(frame, palettes[pal], bg)
            total += fixed
            out.paste(indexed, (k * frame_width, 0))
        if target in BIKE_FROM_RF:
            bike = Image.open(PEOPLE + BIKE_FROM_RF[target])
            out.paste(bike.crop((0, 0, 32 * 9, 32)), (0, 0))
        out.save(PEOPLE + target)
        print(f"{target:28} {count:2} images {frame_width}x32  ({total} pixels ramenés à la couleur la plus proche)")


if __name__ == "__main__":
    main()
