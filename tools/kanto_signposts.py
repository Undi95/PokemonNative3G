#!/usr/bin/env python3
"""Panneaux de Rouge Feu (PokemonNative3G, 2026-10-30) : les tuiles MB_SIGNPOST, MB_POKEMART_SIGN, MB_POKEMON_CENTER_SIGN
et MB_INDIGO_PLATEAU_SIGN_1/2 de RF étaient devenues MB_NORMAL à l'import (tools/kanto/import_kanto.py). Elles reprennent
leur comportement (places 0xC8-0xCC d'Émeraude, inutilisées) : enseignes Centre / Boutique / Plateau Indigo, panneaux
qui s'ouvrent quand on marche vers eux (field_control_avatar.c). Relancer ne change rien de plus.
Usage : python tools/kanto_signposts.py   (depuis la racine du projet)
"""
import os
import struct

FR = '../decomps/pokerougefeu'
EM_MT_PRI = 512
SIGNS = ('MB_SIGNPOST', 'MB_POKEMART_SIGN', 'MB_POKEMON_CENTER_SIGN', 'MB_INDIGO_PLATEAU_SIGN_1', 'MB_INDIGO_PLATEAU_SIGN_2')


def rd(p):
    return open(p, encoding='utf-8').read()


names = [l.split(',')[0].strip() for l in rd('include/constants/metatile_behaviors.h').split('enum')[1].split('\n')
         if l.strip().startswith('MB_')]
em = {n: i for i, n in enumerate(names)}
fr = {}
for line in rd(f'{FR}/include/constants/metatile_behaviors.h').splitlines():
    p = line.split()
    if len(p) >= 3 and p[0] == '#define' and p[1] in SIGNS:
        fr[int(p[2], 0)] = em[p[1]]
assert len(fr) == len(SIGNS), fr


def fr_attrs(path):
    return [a & 0x1FF for (a,) in struct.iter_unpack('<I', open(path, 'rb').read())]


def patch(path, behaviors):
    """behaviors[i] = comportement RF de la métatuile i du fichier Émeraude (None = pas de source)."""
    out = bytearray(open(path, 'rb').read())
    n = 0
    for i, b in enumerate(behaviors):
        if b in fr and i * 2 < len(out):
            old = struct.unpack_from('<H', out, i * 2)[0]
            new = (old & ~0xFF) | fr[b]
            if new != old:
                struct.pack_into('<H', out, i * 2, new)
                n += 1
    open(path, 'wb').write(out)
    return n


total = 0
pri = {}
for name in ('general', 'building'):
    attrs = fr_attrs(f'{FR}/data/tilesets/primary/{name}/metatile_attributes.bin')
    mts = open(f'{FR}/data/tilesets/primary/{name}/metatiles.bin', 'rb').read()
    pri[name] = (attrs, mts)
    total += patch(f'data/tilesets/primary/kanto_{name}/metatile_attributes.bin', attrs[:EM_MT_PRI])

# Secondaires : 128 métatuiles de la fin du primaire RF recopiées en tête (cf. import_kanto.py), puis le secondaire RF.
for d in sorted(os.listdir('data/tilesets/secondary')):
    if not d.startswith('kanto_'):
        continue
    src = f'{FR}/data/tilesets/secondary/{d[len("kanto_"):]}'
    for suffix in ('_building', '_general'):  # variante : même secondaire RF avec l'autre primaire (import_kanto.py)
        if not os.path.isdir(src) and src.endswith(suffix):
            src = src[:-len(suffix)]
    assert os.path.isdir(src), src
    mts = open(f'data/tilesets/secondary/{d}/metatiles.bin', 'rb').read()
    head = [p for p, (a, m) in pri.items() if m[EM_MT_PRI * 16:] == mts[:len(m) - EM_MT_PRI * 16]]
    assert len(head) == 1, (d, head)
    behaviors = pri[head[0]][0][EM_MT_PRI:] + fr_attrs(f'{src}/metatile_attributes.bin')
    n = patch(f'data/tilesets/secondary/{d}/metatile_attributes.bin', behaviors)
    if n:
        print(d, n)
    total += n
print('ok', total, 'tuiles')
