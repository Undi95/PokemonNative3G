#!/usr/bin/env python3
"""Objets cachés de Rouge Feu (PokemonNative3G, 2026-10-30) : quantité (jetons cachés du Casino de Céladopole) et
« sous les pieds » (Restes sous Ronflex, Grelot Zen…, trouvés avec le CHERCH'OBJET) étaient retirés à l'import
(tools/kanto/import_kanto.py). Recopie ces deux champs des map.json de RF dans ceux du projet. Relancer ne change rien.
Usage : python tools/kanto_hidden_items.py   (depuis la racine du projet)
"""
import json
import os

FR = '../decomps/pokerougefeu'
n = 0
for name in sorted(os.listdir(f'{FR}/data/maps')):
    src = f'{FR}/data/maps/{name}/map.json'
    if not os.path.exists(src):
        continue
    fr = [b for b in json.load(open(src, encoding='utf-8')).get('bg_events', [])
          if b['type'] == 'hidden_item' and (b.get('quantity', 1) != 1 or b.get('underfoot'))]
    if not fr:
        continue
    dst = f'data/maps/{name}/map.json'
    if not os.path.exists(dst):  # carte gardée d'Émeraude (Rocher Nombril)
        continue
    text = open(dst, encoding='utf-8').read()
    data = json.loads(text)
    for b in fr:
        match = [e for e in data['bg_events'] if e['type'] == 'hidden_item' and (e['x'], e['y']) == (b['x'], b['y'])]
        assert len(match) == 1, (name, b)
        if match[0].get('quantity') != b['quantity'] or match[0].get('underfoot') != b['underfoot']:
            match[0]['quantity'], match[0]['underfoot'] = b['quantity'], b['underfoot']
            n += 1
    with open(dst, 'w', encoding='utf-8', newline='\n') as f:
        f.write(json.dumps(data, indent=2, ensure_ascii=False) + '\n')
print('ok', n, 'objets cachés')
