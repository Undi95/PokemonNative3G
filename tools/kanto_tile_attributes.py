#!/usr/bin/env python3
"""Attributs des métatuiles de Kanto perdus à l'import (tools/kanto/import_kanto.py), rétablis depuis Rouge Feu
(PokemonNative3G). Relancer ne change rien de plus.

1. Comportements de RF absents d'Émeraude, devenus MB_NORMAL : ils reprennent des places inutilisées d'Émeraude
   (include/constants/metatile_behaviors.h, même nom que dans RF) :
   - panneaux (2026-10-30) : MB_SIGNPOST, enseignes Centre / Boutique / Plateau Indigo (field_control_avatar.c) ;
   - (2026-10-31) dalles tournantes de l'Arène de Jadielle et du Repaire Rocket (field_player_avatar.c), objets
     d'intérieur à examiner (armoire, cuisine, ordinateur…), eau de la Piste Cyclable (surfable), sable des grottes
     (traces de pas), moniteur de la Tour des Dresseurs.
   (2026-11-04) moniteur sans fil et écran des records du hall du 2ᵉ étage des Centres (accessibles en solo dans RF,
   comme leurs équivalents d'Émeraude). La porte de l'Union Room de RF et les tuiles sans effet dans RF (MB_WINDOW,
   MB_PORTHOLE) restent MB_NORMAL.
   (2026-11-04) MB_FAST_WATER, le courant des Îles Écume, importé en MB_OCEAN_WATER : on pouvait y surfer sans arrêter
   le courant avec les rochers (party_menu.c, field_control_avatar.c).
2. Type de rencontre de RF (bits 24-26 de ses attributs : aucune, sol, eau) : RF décide avec lui des rencontres
   sauvages de chaque case, Émeraude avec le comportement. Il est rangé dans les bits 8-9 de l'attribut d'Émeraude
   (inutilisés) et lu à Kanto par wild_encounter.c (MapGridGetMetatileEncounterTypeAt).
3. Terrain de RF (bits 9-13 : normal, herbe, eau, cascade ; 2026-11-02) : RF décide avec lui de l'eau en face du
   joueur (Surf, cannes : MetatileAtCoordsIsWaterTile) et de l'herbe que Coupe tond (MetatileAtCoordsIsGrassTile),
   Émeraude avec le comportement. Il est rangé dans les bits 10-11 (MapGridGetMetatileTerrainAt).
Usage : python tools/kanto_tile_attributes.py   (depuis la racine du projet)
"""
import os
import struct

FR = '../decomps/pokerougefeu'
EM_MT_PRI = 512
RESTORED = (
    'MB_SIGNPOST', 'MB_POKEMART_SIGN', 'MB_POKEMON_CENTER_SIGN', 'MB_INDIGO_PLATEAU_SIGN_1', 'MB_INDIGO_PLATEAU_SIGN_2',
    'MB_SPIN_RIGHT', 'MB_SPIN_LEFT', 'MB_SPIN_UP', 'MB_SPIN_DOWN', 'MB_STOP_SPINNING',
    'MB_CABINET', 'MB_KITCHEN', 'MB_DRESSER', 'MB_FOOD', 'MB_BLUEPRINTS', 'MB_PAINTING', 'MB_POWER_PLANT_MACHINE',
    'MB_TELEPHONE', 'MB_COMPUTER', 'MB_ADVERTISING_POSTER', 'MB_FOOD_SMELLS_TASTY', 'MB_TRASH_BIN', 'MB_CUP',
    'MB_BLINKING_LIGHTS', 'MB_NEATLY_LINED_UP_TOOLS', 'MB_BURGLARY', 'MB_POKEMART_SHELF', 'MB_TRAINER_TOWER_MONITOR',
    'MB_CYCLING_ROAD_WATER', 'MB_SAND_CAVE',
    # (2026-11-04) le hall du 2ᵉ étage des Centres : moniteur sans fil et écran des records, accessibles en solo dans RF
    'MB_CABLE_CLUB_WIRELESS_MONITOR', 'MB_BATTLE_RECORDS',
    # (2026-11-04) le courant des Îles Écume (B3F, B4F), qui refuse SURF
    'MB_FAST_WATER',
)
ENCOUNTER_SHIFT = 8      # METATILE_ATTR_ENCOUNTER_SHIFT (include/global.fieldmap.h)
ENCOUNTER_MASK = 0x0300  # METATILE_ATTR_ENCOUNTER_MASK
TERRAIN_SHIFT = 10       # METATILE_ATTR_TERRAIN_SHIFT
TERRAIN_MASK = 0x0C00    # METATILE_ATTR_TERRAIN_MASK


def rd(p):
    return open(p, encoding='utf-8').read()


names = [l.split(',')[0].strip() for l in rd('include/constants/metatile_behaviors.h').split('enum')[1].split('\n')
         if l.strip().startswith('MB_')]
em = {n: i for i, n in enumerate(names)}
fr = {}
for line in rd(f'{FR}/include/constants/metatile_behaviors.h').splitlines():
    p = line.split()
    if len(p) >= 3 and p[0] == '#define' and p[1] in RESTORED:
        fr[int(p[2], 0)] = em[p[1]]
assert len(fr) == len(RESTORED), sorted(set(RESTORED) - {n for n in names if em[n] in fr.values()})


def fr_attrs(path):
    return [a for (a,) in struct.iter_unpack('<I', open(path, 'rb').read())]


def patch(path, attrs):
    """attrs[i] = attributs RF (32 bits) de la métatuile i du fichier Émeraude."""
    out = bytearray(open(path, 'rb').read())
    n = 0
    for i, a in enumerate(attrs):
        if i * 2 >= len(out):
            break
        old = struct.unpack_from('<H', out, i * 2)[0]
        encounter, terrain = (a >> 24) & 0x7, (a >> 9) & 0x1F
        assert encounter <= ENCOUNTER_MASK >> ENCOUNTER_SHIFT and terrain <= TERRAIN_MASK >> TERRAIN_SHIFT, (path, i, a)
        new = (old & ~(ENCOUNTER_MASK | TERRAIN_MASK)) | (encounter << ENCOUNTER_SHIFT) | (terrain << TERRAIN_SHIFT)
        if (a & 0x1FF) in fr:
            new = (new & ~0xFF) | fr[a & 0x1FF]
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
    attrs = pri[head[0]][0][EM_MT_PRI:] + fr_attrs(f'{src}/metatile_attributes.bin')
    n = patch(f'data/tilesets/secondary/{d}/metatile_attributes.bin', attrs)
    if n:
        print(d, n)
    total += n
print('ok', total, 'métatuiles')
