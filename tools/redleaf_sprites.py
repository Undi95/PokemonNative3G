#!/usr/bin/env python3
"""Sprites de Red/Leaf (option PERSO) qui n'existent pas dans Rouge Feu : Vélo Cross, arrosoir, plongée.

Chaque image part de celle de Brendan/May : le corps et le vélo passent dans la palette de Red/Leaf
(table de couleurs ci-dessous), et la tête est remplacée par celle de Red/Leaf, prise dans leurs
sprites de Rouge Feu dans la même direction (détectée en comparant avec les têtes de Brendan/May).

Usage (racine du dépôt) : python3 tools/redleaf_sprites.py [--preview DOSSIER]
Écrit graphics/kanto/object_events/pics/people/{red,green}_{acro_bike,watering,underwater}.png
"""
import os
import sys
from PIL import Image

EM = 'graphics/object_events/pics/people/'
RF = 'graphics/kanto/object_events/pics/people/'

# Indices de la palette de Brendan/May -> indices de la palette du joueur de Rouge Feu
BRENDAN_TO_RED = {0: 0, 1: 2, 2: 2, 3: 3, 4: 4, 5: 5, 6: 6, 7: 6, 8: 6, 9: 9, 10: 13, 11: 14, 12: 11, 13: 12, 14: 9, 15: 15}
MAY_TO_LEAF = {0: 0, 1: 2, 2: 2, 3: 3, 4: 4, 5: 6, 6: 6, 7: 1, 8: 8, 9: 10, 10: 7, 11: 6, 12: 7, 13: 6, 14: 9, 15: 15}
# Sous l'eau : palette propre à la plongée, gardée telle quelle (seule la tête change de forme)
HEAD_ROWS = 14
# Vélo Cross : direction de chaque image (sAnimTable_AcroBike) ; 0-8 = vélo ordinaire
ACRO_DIRS = 'SNWSSNNWW' + 'SSSSNNNNWWWWSSNNWW'


def frames(img, w=32, h=32):
    return [img.crop((i * w, 0, (i + 1) * w, h)) for i in range(img.width // w)]


def pixels(im):
    return [[im.getpixel((x, y)) for x in range(im.width)] for y in range(im.height)]


def top_row(px):
    for y, row in enumerate(px):
        if any(row):
            return y
    return None


def head(px, rows=HEAD_ROWS):
    """(ligne du haut, centre x, pixels de la tête) ; la tête = les `rows` premières lignes non vides"""
    t = top_row(px)
    xs = [x for y in range(t, min(t + rows, len(px))) for x in range(len(px[0])) if px[y][x]]
    cx = (min(xs) + max(xs)) / 2
    return t, cx, [px[y][:] for y in range(t, min(t + rows, len(px)))]


def mirror(px):
    return [row[::-1] for row in px]


def head_distance(a, b):
    """différence entre deux têtes (pixels opaques non communs), centrées"""
    (_, ca, ha), (_, cb, hb) = a, b
    d = 0
    off = round(cb - ca)
    for y in range(min(len(ha), len(hb))):
        for x in range(len(ha[0])):
            xb = x + off
            pa = ha[y][x]
            pb = hb[y][xb] if 0 <= xb < len(hb[0]) else 0
            d += (pa != pb)
    return d


def build(src_path, ref_path, ref_dirs, red_head_path, red_dirs, colors, size=(32, 32), keep_palette=False, dirs=None, copy=0):
    src = Image.open(src_path)
    ref = Image.open(ref_path)
    red = Image.open(red_head_path)
    rw = red.width // len(red_dirs) if False else size[0]
    ref_heads = {}
    for d, i in ref_dirs.items():
        px = pixels(frames(ref, *size)[i])
        ref_heads[d] = head(px)
        if d == 'W':
            ref_heads['E'] = head(mirror(px))
    red_frames = frames(red, red.width // red_count(red, red_dirs), red.height)
    red_heads = {}
    for d, i in red_dirs.items():
        px = pixels(red_frames[i])
        red_heads[d] = head(px)
        if d == 'W':
            red_heads['E'] = head(mirror(px))

    out = Image.new('P', src.size, 0)
    out.putpalette((red if not keep_palette else src).getpalette())
    for n, fr in enumerate(frames(src, *size)):
        if n < copy:
            # images de vélo ordinaires : celles de Rouge Feu telles quelles
            out.paste(red_frames[n], (n * size[0], 0))
            continue
        px = pixels(fr)
        if top_row(px) is None:
            continue
        h = head(px)
        d = dirs[n] if dirs else min(ref_heads, key=lambda k: head_distance(h, ref_heads[k]))
        t, cx, hp = h
        # corps : couleurs de Red/Leaf, tête de Brendan/May effacée
        body = [[colors.get(v, v) if not keep_palette else v for v in row] for row in px]
        for y in range(t, min(t + HEAD_ROWS, size[1])):
            body[y] = [0] * size[0]
        # tête de Red/Leaf, alignée en haut et au centre
        rt, rcx, rh = red_heads[d]
        off = round(cx - rcx)
        for y, row in enumerate(rh):
            for x, v in enumerate(row):
                if v and 0 <= x + off < size[0] and t + y < size[1]:
                    body[t + y][x + off] = v if not keep_palette else colors.get(v, v)
        for y in range(size[1]):
            for x in range(size[0]):
                out.putpixel((n * size[0] + x, y), body[y][x])
    return out


def red_count(img, dirs):
    # Les planches de Rouge Feu ont des images de 16 ou 32 de large : on prend la hauteur comme repère
    return img.width // (16 if img.height == 32 and img.width % 32 and img.width % 16 == 0 else 32)


def build_underwater(src_path, head_path):
    """Plongée : silhouette de Brendan/May dans sa palette bleu-gris, tête de Red/Leaf (sprite de surf)
    (sprite de marche) passée dans ces tons selon sa luminosité. Images : 0 = sud, 1 = nord, 2 et 3 = ouest."""
    src = Image.open(src_path)
    hd = Image.open(head_path)
    hpal = hd.getpalette()
    shades = [9, 5, 6, 7, 8]  # du plus clair au plus foncé dans la palette de plongée

    def to_water(v):
        if v in (0, 15):
            return v
        r, g, b = hpal[v * 3:v * 3 + 3]
        lum = (r * 299 + g * 587 + b * 114) / 1000
        return shades[min(4, int((255 - lum) / 52))]

    hfr = frames(hd, 16, 32)
    heads = {'S': head(pixels(hfr[0])), 'N': head(pixels(hfr[1])), 'W': head(pixels(hfr[2]))}
    out = Image.new('P', src.size, 0)
    out.putpalette(src.getpalette())
    for n, fr in enumerate(frames(src)):
        px = pixels(fr)
        t, cx, _ = head(px)
        rt, rcx, rh = heads['SNWW'[n]]
        for y in range(t, min(t + HEAD_ROWS, 32)):
            px[y] = [0] * 32
        off = round(cx - rcx)
        for y, row in enumerate(rh):
            for x, v in enumerate(row):
                if v and 0 <= x + off < 32 and t + y < 32:
                    px[t + y][x + off] = to_water(v)
        for y in range(32):
            for x in range(32):
                out.putpixel((n * 32 + x, y), px[y][x])
    return out


def main():
    preview = sys.argv[2] if len(sys.argv) > 2 and sys.argv[1] == '--preview' else None
    jobs = []
    for who, em, rf, colors in (('red', 'brendan', 'red', BRENDAN_TO_RED), ('green', 'may', 'green', MAY_TO_LEAF)):
        bike_dirs = {'S': 0, 'N': 1, 'W': 2}
        jobs.append((f'{who}_acro_bike', build(EM + f'{em}/acro_bike.png', EM + f'{em}/mach_bike.png', bike_dirs,
                                               RF + f'{rf}_bike.png', bike_dirs, colors, dirs=ACRO_DIRS, copy=9)))
        jobs.append((f'{who}_watering', build(EM + f'{em}/watering.png', EM + f'{em}/watering.png', {'S': 0, 'N': 2, 'W': 4},
                                              RF + f'{rf}_bike.png', bike_dirs, colors)))
        jobs.append((f'{who}_underwater', build_underwater(EM + f'{em}/underwater.png', RF + f'{rf}_normal.png')))
    for name, img in jobs:
        img.save(RF + name + '.png')
        if preview:
            big = img.convert('RGBA').resize((img.width * 3, img.height * 3), Image.NEAREST)
            big.save(os.path.join(preview, name + '.png'))
        print(RF + name + '.png')


if __name__ == '__main__':
    main()
