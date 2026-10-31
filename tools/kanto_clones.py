#!/usr/bin/env python3
"""Objets « clone » de Rouge Feu (PokemonNative3G, 2026-10-31) : sur 9 cartes de Kanto, l'obstacle de la carte voisine
(arbre à Couper en bordure, garde de la Grotte Azurée, deux PNJ) est affiché au bord de la carte, au lieu d'apparaître
seulement quand on la franchit. Le moteur les gère comme RF (LoadObjEventTemplatesFromHeader,
InitObjectEventStateFromTemplate) ; ce script les ajoute à la fin des objets des cartes déjà importées (sans décaler
les numéros des autres). tools/kanto/import_kanto.py les garde aussi à l'import. Relancer ne fait rien de plus.
Usage : python tools/kanto_clones.py   (depuis la racine du projet)
"""
import glob
import json
import os

RF = os.path.join('..', 'decomps', 'pokerougefeu', 'data', 'maps')
# Noms de RF -> noms du port (constants/kanto_event_objects.h, map.json importés)
GFX = {'OBJ_EVENT_GFX_CUT_TREE': 'OBJ_EVENT_GFX_KANTO_CUT_TREE', 'OBJ_EVENT_GFX_FAT_MAN': 'OBJ_EVENT_GFX_KANTO_FAT_MAN',
       'OBJ_EVENT_GFX_COOLTRAINER_M': 'OBJ_EVENT_GFX_KANTO_COOLTRAINER_M'}


def convert(o):
    return {'type': 'clone', 'graphics_id': GFX[o['graphics_id']], 'x': o['x'], 'y': o['y'],
            'target_local_id': o['target_local_id'].replace('LOCALID_', 'LOCALID_KANTO_', 1),
            'target_map': o['target_map']}


added = 0
for rf_path in sorted(glob.glob(os.path.join(RF, '*', 'map.json'))):
    rf = json.load(open(rf_path, encoding='utf-8'))
    clones = [convert(o) for o in rf.get('object_events', []) if o.get('type') == 'clone']
    if not clones:
        continue
    path = os.path.join('data', 'maps', os.path.basename(os.path.dirname(rf_path)), 'map.json')
    text = open(path, encoding='utf-8', newline='').read()
    data = json.loads(text)
    have = [o for o in data['object_events'] if o.get('type') == 'clone']
    for c in clones:
        if c not in have:
            data['object_events'].append(c)
            added += 1
    out = json.dumps(data, indent=2, ensure_ascii=False) + '\n'
    if '\r\n' in text:
        out = out.replace('\n', '\r\n')
    open(path, 'w', encoding='utf-8', newline='').write(out)
print('clones ajoutés :', added)
