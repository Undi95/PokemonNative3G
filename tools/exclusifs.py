#!/usr/bin/env python3
"""Exclusivités de version ajoutées aux tables sauvages (PokemonNative3G, décision du 2026-10-24 : ajout permanent).

Kanto / Sevii : les espèces de Vert Feuille absentes du jeu (Chétiflor…, Ramoloss, Flagadoss (2026-10-31), Magmar, Farfuret, Feuforêve, Démanta) sont
prises dans les tables Vert Feuille du décomp de RF. Hoenn : celles de Rubis/Saphir absentes d'Émeraude (Arakdo,
Rosélia, Mangriff, Séléroc, Méditikka, Charmina), aux créneaux de Rubis/Saphir (pret/pokeruby).
Règle : sur les créneaux où les deux versions diffèrent, on alterne nouvelle espèce / espèce d'origine, pour que
les deux restent obtenables. À relancer après tools/kanto/gen_wild.py (qui ne reprend que Rouge Feu).
Usage : python tools/exclusifs.py
"""
import json, sys

RF = '../decomps/pokerougefeu/'
EM_JSON = 'src/data/wild_encounters.json'
KINDS = ('land_mons', 'water_mons', 'rock_smash_mons', 'fishing_mons')
LG_NEW = {'SPECIES_BELLSPROUT', 'SPECIES_WEEPINBELL', 'SPECIES_VICTREEBEL', 'SPECIES_SLOWPOKE', 'SPECIES_SLOWBRO',
          'SPECIES_MAGMAR', 'SPECIES_SNEASEL',
          'SPECIES_MISDREAVUS', 'SPECIES_MANTINE'}

# Hoenn : (carte, table, créneaux de Rubis/Saphir dans l'ordre, espèce) ; niveaux d'Émeraude conservés
HOENN = [
    ('MAP_ROUTE102', 'land_mons', [11], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE117', 'land_mons', [11], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE102', 'water_mons', [4], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE111', 'water_mons', [4], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE114', 'water_mons', [4], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE117', 'water_mons', [4], 'SPECIES_SURSKIT'),
    ('MAP_ROUTE117', 'land_mons', [1, 3], 'SPECIES_ROSELIA'),
    ('MAP_ROUTE114', 'land_mons', [8, 9, 10], 'SPECIES_ZANGOOSE'),
    ('MAP_METEOR_FALLS_1F_1R', 'land_mons', [5, 6, 7], 'SPECIES_LUNATONE'),
    ('MAP_METEOR_FALLS_1F_1R', 'water_mons', [2, 3, 4], 'SPECIES_LUNATONE'),
    ('MAP_METEOR_FALLS_1F_2R', 'land_mons', [3, 4, 5, 7], 'SPECIES_LUNATONE'),
    ('MAP_METEOR_FALLS_B1F_1R', 'land_mons', [3, 4, 5, 7], 'SPECIES_LUNATONE'),
    ('MAP_METEOR_FALLS_B1F_2R', 'land_mons', [3, 5, 7], 'SPECIES_LUNATONE'),
    ('MAP_MT_PYRE_EXTERIOR', 'land_mons', [1, 3], 'SPECIES_MEDITITE'),
    ('MAP_VICTORY_ROAD_B1F', 'land_mons', [3], 'SPECIES_MEDICHAM'),
    ('MAP_VICTORY_ROAD_B2F', 'land_mons', [3, 9, 11], 'SPECIES_MEDICHAM'),
]


def alternate(mons, slots, new_species, log):
    """slots : créneaux qui diffèrent ; un sur deux reçoit la nouvelle espèce (en commençant par elle),
    sauf un créneau unique, qui la reçoit."""
    for k, i in enumerate(slots):
        if k % 2 == 0 and mons[i]['species'] != new_species:
            log.append('%s %d : %s -> %s' % (new_species[8:], i, mons[i]['species'][8:], new_species[8:]))
            mons[i]['species'] = new_species


def present(enc):
    return {m['species'] for e in enc for k in KINDS for m in e.get(k, {}).get('mons', [])}


text = open(EM_JSON, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in text else '\n'
data = json.loads(text)
enc = data['wild_encounter_groups'][0]['encounters']
before_all = present(enc)
log = []

# Kanto : Vert Feuille
lg = {}
for e in json.load(open(RF + 'src/data/wild_encounters.json', encoding='utf-8'))['wild_encounter_groups'][0]['encounters']:
    if 'LeafGreen' in e['base_label']:
        lg['gKanto' + e['base_label'][1:].replace('_LeafGreen', '')] = e
# (Rouge Feu n'a aucune de ces espèces : un créneau qui l'a déjà vient de ce script, d'où l'idempotence)
singles = {}  # espèce -> [(carte, table, créneau)] : un seul créneau sur la carte, on alterne entre cartes
for e in enc:
    other = lg.get(e['base_label'])
    if not other:
        continue
    for kind in KINDS:
        if kind not in e or kind not in other:
            continue
        mine, theirs = e[kind]['mons'], other[kind]['mons']
        by_species = {}
        for i, b in enumerate(theirs):
            if b['species'] in LG_NEW:
                by_species.setdefault(b['species'], []).append(i)
        for sp, slots in by_species.items():
            if len(slots) == 1:
                singles.setdefault(sp, []).append((e, kind, slots[0]))
                continue
            before = len(log)
            alternate(mine, slots, sp, log)
            for line in log[before:]:
                log[log.index(line)] = '%s %s %s' % (e['base_label'], kind, line)
for sp, places in singles.items():
    for k, (e, kind, i) in enumerate(places):
        mons = e[kind]['mons']
        if k % 2 == 0 and mons[i]['species'] != sp:
            log.append('%s %s %s %d : %s -> %s' % (e['base_label'], kind, sp[8:], i, mons[i]['species'][8:], sp[8:]))
            mons[i]['species'] = sp

# Hoenn : Rubis/Saphir
for m, kind, slots, sp in HOENN:
    e = [x for x in enc if x.get('map') == m and not x['base_label'].startswith('gKanto')]
    assert len(e) == 1, m
    before = len(log)
    alternate(e[0][kind]['mons'], slots, sp, log)
    for line in log[before:]:
        log[log.index(line)] = '%s %s %s' % (m, kind, line)

lost = before_all - present(enc)
assert not lost, 'espèces disparues des tables : %s' % sorted(lost)

out = json.dumps(data, indent=2, ensure_ascii=False).replace('\n', nl) + nl
open(EM_JSON, 'w', encoding='utf-8', newline='').write(out)
print('\n'.join(log) if log else 'rien à changer (déjà appliqué)')
