#!/usr/bin/env python3
"""Espèces obtenables dans la fusion (solo, sans échange) et celles qui manquent.

Sources : rencontres sauvages (src/data/wild_encounters.json), dons et combats fixes des scripts
(givemon / giveegg / setwildbattle / ...), échanges en jeu (trade.h, kanto_ingame_trades_entries.h),
puis fermeture par évolutions (src/data/pokemon/evolution.h) et œufs (pré-évolutions de base).
Option --trade : compte les évolutions par échange (objet « câble link »).

Usage : python tools/obtenables.py [--trade]   (depuis la racine du projet)
"""
import glob, json, re, sys

TRADE_OK = '--trade' in sys.argv
species = []
for m in re.finditer(r'#define (SPECIES_\w+)\s+(\d+)', open('include/constants/species.h', encoding='utf-8').read()):
    n = m.group(1)
    if n in ('SPECIES_NONE', 'SPECIES_EGG') or n.startswith(('SPECIES_OLD_UNOWN', 'SPECIES_UNOWN_')) or int(m.group(2)) > 411:
        continue
    species.append(n)

have = {}  # espèce -> origine


def add(sp, why):
    if sp in species and sp not in have:
        have[sp] = why


# sauvages
w = json.load(open('src/data/wild_encounters.json', encoding='utf-8'))
for g in w['wild_encounter_groups']:
    for e in g['encounters']:
        region = 'Kanto' if e['base_label'].startswith('gKanto') else 'Hoenn'
        for kind in ('land_mons', 'water_mons', 'rock_smash_mons', 'fishing_mons'):
            for mon in e.get(kind, {}).get('mons', []):
                add(mon['species'], 'sauvage %s (%s)' % (region, e.get('map', e['base_label'])))

# scripts
scr = ''
for p in glob.glob('data/**/*.inc', recursive=True) + glob.glob('data/**/*.s', recursive=True):
    scr += open(p, encoding='utf-8', errors='ignore').read()
for m in re.finditer(r'\b(givemon|giveegg|setwildbattle|givecustommon|seteventmon)\s+(SPECIES_\w+)', scr):
    add(m.group(2), 'script (%s)' % m.group(1).split()[0])
# Dons et choix passés par une variable (Dojo de Safrania, lots du Casino, starters de RF) : setvar VAR_TEMP_1/2
for m in re.finditer(r'\bsetvar\s+VAR_TEMP_[12],\s*(SPECIES_\w+)', scr):
    add(m.group(1), 'script (don par variable)')
# Ce que les scripts ne disent pas : chiens errants de Kanto (roamer.c, les trois), starters de Hoenn (Birch,
# starter_choose.c) et leurs œufs (assistant des pensions, fusion_events.c)
for sp in ('SPECIES_RAIKOU', 'SPECIES_ENTEI', 'SPECIES_SUICUNE'):
    add(sp, 'errant à Kanto')
for sp in ('SPECIES_TREECKO', 'SPECIES_TORCHIC', 'SPECIES_MUDKIP'):
    add(sp, 'starter de Hoenn / œuf des pensions')

# échanges en jeu (le Pokémon reçu)
for p in ('src/data/trade.h', 'src/data/kanto_ingame_trades_entries.h'):
    for m in re.finditer(r'\.species\s*=\s*(SPECIES_\w+)', open(p, encoding='utf-8').read()):
        add(m.group(1), 'échange en jeu')

# évolutions
evo = open('src/data/pokemon/evolution.h', encoding='utf-8').read()
evos = []
parts = re.split(r'\[(SPECIES_\w+)\]\s*=', evo)
for a, body in zip(parts[1::2], parts[2::2]):
    for e in re.finditer(r'\{\s*(EVO_\w+)\s*,\s*([^,]+?)\s*,\s*(SPECIES_\w+)\s*\}', body):
        evos.append((a, e.group(1), e.group(3)))
changed = True
while changed:
    changed = False
    for a, method, b in evos:
        if method.startswith('EVO_TRADE') and not TRADE_OK:
            continue
        if a in have and b not in have:
            add(b, 'évolution de %s (%s)' % (a, method)); changed = True
        # œufs : un parent obtenable donne la forme de base
        if b in have and a not in have and not method.startswith('EVO_TRADE'):
            add(a, 'œuf (%s)' % b); changed = True
    # bébés obtenus par œuf mais qui évoluent par échange
    for a, method, b in evos:
        if method.startswith('EVO_TRADE') and b in have and a not in have:
            add(a, 'œuf (%s)' % b); changed = True

missing = [s for s in species if s not in have]
print('%d espèces, %d obtenables, %d manquantes%s' % (len(species), len(have), len(missing), ' (avec évolutions par échange)' if TRADE_OK else ''))
for s in missing:
    print('  ', s)
