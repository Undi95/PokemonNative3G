#!/usr/bin/env python3
"""Importe les rencontres sauvages de Rouge Feu.

Usage : gen_wild.py FR_DIR EM_DIR

Ajoute à la fin de gWildMonHeaders (src/data/wild_encounters.json d'Émeraude) les rencontres
FireRed de RF (les LeafGreen sont ignorées). Les cartes RF renommées à l'import (MAP_KANTO_X)
suivent leur nouveau nom ; les labels deviennent gKantoX. Relancer remplace les entrées Kanto
sans toucher au reste du fichier.
"""
import glob, json, re, sys

fr, em = sys.argv[1], sys.argv[2]
EM_JSON = f'{em}/src/data/wild_encounters.json'

ids = {json.load(open(p, encoding='utf-8'))['id'] for p in glob.glob(f'{em}/data/maps/*/map.json')}
fr_group = json.load(open(f'{fr}/src/data/wild_encounters.json', encoding='utf-8'))['wild_encounter_groups'][0]

entries = []
for e in fr_group['encounters']:
    if 'LeafGreen' in e['base_label']:
        continue
    e = dict(e)
    renamed = 'MAP_KANTO_' + e['map'][len('MAP_'):]
    e['map'] = renamed if renamed in ids else e['map']
    if e['map'] not in ids:
        sys.exit(f'carte inconnue : {e["map"]}')
    e['base_label'] = 'gKanto' + e['base_label'][1:].replace('_FireRed', '')
    entries.append(e)

text = open(EM_JSON, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in text else '\n'


def matching(s, i):
    """Indice juste après le crochet/l'accolade fermant celui en s[i]."""
    depth = 0
    for j in range(i, len(s)):
        if s[j] in '[{':
            depth += 1
        elif s[j] in ']}':
            depth -= 1
            if depth == 0:
                return j + 1
    raise ValueError


start = text.index('[', text.index('"encounters"', text.index('"gWildMonHeaders"')))
end = matching(text, start)
# éléments existants, sans les entrées Kanto d'un import précédent
items, i = [], start + 1
while True:
    i = text.find('{', i, end)
    if i < 0:
        break
    j = matching(text, i)
    if '"gKanto' not in text[i:j]:
        items.append(text[i:j])
    i = j
indent = ' ' * 8
for e in entries:
    items.append(json.dumps(e, indent=2, ensure_ascii=False).replace('\n', nl + indent))
body = '[' + nl + indent + (',' + nl + indent).join(items) + nl + '      ]'
open(EM_JSON, 'w', encoding='utf-8', newline='').write(text[:start] + body + text[end:])
print(f'{len(entries)} rencontres RF ajoutées')
