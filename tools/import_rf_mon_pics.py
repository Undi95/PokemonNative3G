#!/usr/bin/env python3
"""Sprites des Pokémon de Rouge Feu (option POKéMON = KANTO).

Copie face / dos / palettes de Rouge Feu dans graphics/kanto/pokemon/ et écrit
src/data/kanto_mon_pics.h (images + tables gKantoMon*, mêmes indices que les tables d'Émeraude).
La face de Rouge Feu n'a qu'une image : elle est doublée (64x128) comme les faces animées
d'Émeraude, pour que le code qui lit la 2e image trouve la même.

Usage (racine du dépôt) : python3 tools/import_rf_mon_pics.py [chemin du décomp de Rouge Feu]
"""
import os
import re
import shutil
import sys
from PIL import Image

RF = sys.argv[1] if len(sys.argv) > 1 else '../decomps/pokerougefeu/'
OUT = 'graphics/kanto/pokemon/'
GFX = re.compile(r'^const u32 gMon(FrontPic|BackPic|Palette|ShinyPalette)_(\w+)\[\] = INCBIN_U32\("graphics/pokemon/([\w/]+)\.(4bpp|gbapal)\.lz"\);')
TABLES = ['front_pic_table', 'back_pic_table', 'palette_table', 'shiny_palette_table',
          'front_pic_coordinates', 'back_pic_coordinates', 'enemy_mon_elevation']


def copy_front(src, dst):
    img = Image.open(src)
    if img.height == 64:
        out = Image.new('P', (64, 128))
        out.putpalette(img.getpalette())
        out.paste(img, (0, 0))
        out.paste(img, (0, 64))
        img = out
    img.save(dst)


def main():
    decls = []
    lines = [l for l in open(RF + 'src/graphics.c', encoding='utf-8') if 'CircledQuestionMark' in l]
    leafgreen = False
    for line in open(RF + 'src/data/graphics/pokemon.h', encoding='utf-8'):
        if line.startswith('#ifdef LEAFGREEN'):
            leafgreen = True  # Deoxys de Vert Feuille : on garde celui de Rouge Feu
        elif line.startswith('#endif'):
            leafgreen = False
        elif not leafgreen:
            lines.append(line)
    for line in lines:
        m = GFX.match(line)
        if not m:
            continue
        kind, name, path, ext = m.groups()
        if name == 'Castform':
            continue  # 4 formes assemblées : on garde celles d'Émeraude (gMon*_Castform)
        src = RF + 'graphics/pokemon/' + path + ('.png' if ext == '4bpp' else '.pal')
        dst_rel = path.replace('front', 'anim_front') if kind == 'FrontPic' else path
        dst = OUT + dst_rel + ('.png' if ext == '4bpp' else '.pal')
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        if kind == 'FrontPic':
            copy_front(src, dst)
        else:
            shutil.copyfile(src, dst)
        fmt = '.4bpp.lz' if ext == '4bpp' else '.gbapal.lz'
        decls.append('static const u32 gKantoMon%s_%s[] = INCGFX_U32("%s", "%s");' % (kind, name, dst, fmt))

    out = ['// Généré par tools/import_rf_mon_pics.py : sprites des Pokémon de Rouge Feu (option POKéMON = KANTO)',
           '// Inclus par src/data.c après les macros SPECIES_SPRITE / SPECIES_PAL.', ''] + decls + ['']
    for t in TABLES:
        body = open(RF + 'src/data/pokemon_graphics/%s.h' % t, encoding='utf-8').read()
        body = re.sub(r'\bgMon(\w+)', r'gKantoMon\1', body)
        body = body.replace('gEnemyMonElevation', 'gKantoEnemyMonElevation')
        body = re.sub(r'gKantoMon(\w+)_Castform\b', r'gMon\1_Castform', body)
        out.append(body.rstrip() + '\n')
    open('src/data/kanto_mon_pics.h', 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
    print(len(decls), 'images/palettes')


if __name__ == '__main__':
    main()
