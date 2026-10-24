#!/usr/bin/env python3
"""Icônes dessinées pour la fusion (PokemonNative3G, 2026-10-24) : AUTO-REPOUSSE, OVO-CHRONO, CHARME CHROMA,
CHARME OVALE. 24x24, 16 couleurs, couleur 0 = transparente (graphics/items/icons + icon_palettes).
Relancer redessine les mêmes fichiers.
Usage : python tools/fusion_icons.py [aperçu.png]   (depuis la racine du projet)
"""
import math
import sys
from PIL import Image, ImageDraw

D = 'graphics/items/'
BG, OUT = (180, 180, 180), (49, 49, 49)


def load(name):
    im = Image.open(f'{D}icons/{name}.png')
    pal = [tuple(map(int, l.split())) for l in open(f'{D}icon_palettes/{name}.pal').read().split('\n')[3:19]]
    return [[im.getpixel((x, y)) for x in range(24)] for y in range(24)], pal


def save(name, px, pal):
    pal = (pal + [(0, 0, 0)] * 16)[:16]
    im = Image.new('P', (24, 24))
    im.putpalette([c for rgb in pal for c in rgb] + [0] * (768 - 48))
    for y in range(24):
        for x in range(24):
            im.putpixel((x, y), px[y][x])
    im.save(f'{D}icons/{name}.png')
    with open(f'{D}icon_palettes/{name}.pal', 'w', newline='\r\n') as f:
        f.write('JASC-PAL\n0100\n16\n' + ''.join(f'{r} {g} {b}\n' for r, g, b in pal))


def blank():
    return [[0] * 24 for _ in range(24)]


def from_image(im):
    return [[im.getpixel((x, y)) for x in range(24)] for y in range(24)]


def ring(px, cx, cy, r0, r1, col, skip=lambda a: False):
    for y in range(24):
        for x in range(24):
            d = math.hypot(x + 0.5 - cx, y + 0.5 - cy)
            a = math.degrees(math.atan2(y + 0.5 - cy, x + 0.5 - cx)) % 360
            if r0 <= d <= r1 and not skip(a):
                px[y][x] = col


def outline(px, inside, col=1):
    """contour (couleur col) autour des pixels pour lesquels inside(x, y)."""
    add = []
    for y in range(24):
        for x in range(24):
            if px[y][x] == 0 and any(0 <= x + dx < 24 and 0 <= y + dy < 24 and inside(x + dx, y + dy)
                                     for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                add.append((x, y))
    for x, y in add:
        px[y][x] = col


# --- AUTO-REPOUSSE : la bombe du REPOUSSE, teinte turquoise, une flèche circulaire à la place de la POKé BALL
px, _ = load('repel')
_, pal = load('auto_repel')
for y in range(12, 21):
    for x in range(7, 17):
        if px[y][x] != 1 or 7 < x < 16:
            px[y][x] = px[10][x]
pal[2] = (255, 255, 255)
pal[10] = (32, 98, 90)
cx, cy = 12.0, 16.5
ring(px, cx, cy, 2.0, 3.6, 2, skip=lambda a: 300 <= a or a <= 10)
for x, y in ((14, 12), (15, 12), (16, 12), (15, 13), (16, 13), (16, 14), (16, 11)):
    px[y][x] = 2
for y in range(24):
    for x in range(24):
        if px[y][x] == 2 and 11 <= y <= 21 and 7 <= x <= 17:
            for dx, dy in ((1, 1), (0, 1), (1, 0)):
                if px[y + dy][x + dx] not in (2, 1):
                    px[y + dy][x + dx] = 10
save('auto_repel', px, pal)

# --- OVO-CHRONO : un OEUF crème avec une petite horloge dorée
px, pal = load('lucky_egg')
pal[2], pal[3], pal[4], pal[5] = (255, 246, 213), (238, 222, 172), (205, 180, 123), (255, 255, 255)
pal[6], pal[7], pal[8], pal[9] = (255, 213, 65), (205, 148, 16), (123, 82, 8), (98, 172, 74)
for x, y in ((8, 8), (9, 8), (8, 9), (12, 6), (13, 6), (13, 12), (14, 12), (10, 14)):  # taches vertes
    if px[y][x] in (2, 3, 4):
        px[y][x] = 9
cx, cy = 17.0, 17.0
for y in range(24):
    for x in range(24):
        d = math.hypot(x + 0.5 - cx, y + 0.5 - cy)
        if d <= 5.6:
            px[y][x] = 1 if d > 4.7 else 8 if d > 3.9 else 6 if d > 3.1 else 5
for x, y in ((16, 14), (16, 15), (16, 16), (17, 16), (18, 16)):  # aiguilles
    px[y][x] = 1
px[13][16], px[16][19] = 7, 7
px[13][14] = 6
save('ovo_chrono', px, pal)

# --- CHARME CHROMA : étoile dorée sur une attache
pal = [BG, OUT, (255, 255, 255), (255, 246, 164), (255, 222, 65), (230, 172, 16), (172, 115, 8),
       (213, 213, 222), (139, 139, 156), (255, 156, 205)]
im = Image.new('P', (24, 24), 0)
dr = ImageDraw.Draw(im)
pts = []
for k in range(10):
    r = 9.2 if k % 2 == 0 else 4.0
    a = math.radians(-90 + k * 36)
    pts.append((11.5 + r * math.cos(a), 14.0 + r * math.sin(a)))
dr.polygon(pts, fill=5, outline=1)
px = from_image(im)
for y in range(24):
    for x in range(24):
        if px[y][x] == 5:
            if x + y < 22:
                px[y][x] = 4
            if x + y < 18:
                px[y][x] = 3
            if x - y > 3 or y > 17 and x > 12:
                px[y][x] = 6
px[11][9], px[12][9], px[11][10] = 2, 2, 2
ring(px, 11.5, 3.0, 1.0, 2.2, 7)
px[2][11], px[2][12] = 8, 8
for x, y in ((19, 5), (20, 4), (21, 5), (20, 6), (3, 20), (4, 19), (5, 20), (4, 21)):  # éclats
    if px[y][x] == 0:
        px[y][x] = 9 if x > 10 else 3
outline(px, lambda x, y: px[y][x] in (7, 8))
save('shiny_charm', px, pal)

# --- CHARME OVALE : ovale bleu sur une attache
pal = [BG, OUT, (255, 255, 255), (189, 230, 255), (106, 189, 246), (49, 131, 213), (24, 74, 156),
       (213, 213, 222), (139, 139, 156)]
im = Image.new('P', (24, 24), 0)
dr = ImageDraw.Draw(im)
dr.ellipse((5, 6, 18, 22), fill=5, outline=1)
px = from_image(im)
for y in range(24):
    for x in range(24):
        if px[y][x] == 5:
            d = math.hypot((x - 9.5) / 5.0, (y - 11.0) / 6.0)
            px[y][x] = 3 if d < 0.45 else 4 if d < 0.95 else 5
            if math.hypot((x - 11.5) / 6.5, (y - 14.0) / 8.0) > 0.78 and (x > 12 or y > 16):
                px[y][x] = 6
px[9][8], px[9][9], px[10][8] = 2, 2, 2
ring(px, 11.5, 3.5, 1.0, 2.2, 7)
px[2][11], px[2][12] = 8, 8
outline(px, lambda x, y: px[y][x] in (7, 8))
save('oval_charm', px, pal)

if len(sys.argv) > 1:  # aperçu agrandi des 4 icônes
    out = Image.new('RGB', (4 * 192, 192))
    for k, n in enumerate(('auto_repel', 'ovo_chrono', 'shiny_charm', 'oval_charm')):
        p, pl = load(n)
        im = Image.new('RGB', (24, 24))
        for y in range(24):
            for x in range(24):
                im.putpixel((x, y), pl[p[y][x]])
        out.paste(im.resize((192, 192), Image.NEAREST), (k * 192, 0))
    out.save(sys.argv[1])
print('ok')
