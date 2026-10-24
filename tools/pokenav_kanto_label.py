#!/usr/bin/env python3
"""POKéNAV (PokemonNative3G, 2026-10-24) : libellé « CARTE DE KANTO » (graphics/pokenav/options/kanto_map.png), fait à
partir de « CARTE DE HOENN » : lettres A, T, N, O reprises du libellé, K dessiné dans le même style.
Usage : python tools/pokenav_kanto_label.py   (depuis la racine du projet)
"""
from PIL import Image

D = 'graphics/pokenav/options/'
im = Image.open(D + 'hoenn_map.png')
out = im.copy()


def glyph(x0, y0):
    return [[im.getpixel((x0 + x, y0 + y)) for x in range(6)] for y in range(10)]


K = [[int(c) for c in row] for row in (
    "124412", "124122", "121224", "112244", "111244", "122124", "124412", "124412", "124412", "224422")]
A = glyph(22, 4)    # « CAR » (bande 1)
T = glyph(2, 20)    # « TE DE » (bande 2)
O = glyph(6, 36)    # « HOENN » (bande 3)
N = glyph(18, 36)
for i, g in enumerate((K, A, N, T, O)):
    for y in range(10):
        for x in range(6):
            out.putpixel((i * 6 + x, 36 + y), g[y][x])
out.save(D + 'kanto_map.png')
print('ok')
