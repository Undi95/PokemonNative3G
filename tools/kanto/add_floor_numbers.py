"""Ajoute aux cartes de Kanto déjà importées le « floor_number » de RF (étage du panneau du nom de lieu de RF), que
import_kanto.py ne gardait pas avant le 2026-11-02. Même format que import_kanto.write_json ; seules les cartes à étage
(floor_number non nul) changent. Usage : python tools/kanto/add_floor_numbers.py"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FR = os.path.join(os.path.dirname(ROOT), 'decomps', 'pokerougefeu')


def write_json(path, data):
    with open(path, 'w', encoding='utf-8', newline='\n') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write('\n')


def main():
    changed, missing = 0, []
    for m in sorted(os.listdir(os.path.join(FR, 'data', 'maps'))):
        path = os.path.join(FR, 'data', 'maps', m, 'map.json')
        if not os.path.exists(path):
            continue
        with open(path, encoding='utf-8') as f:
            fr = json.load(f)
        floor = fr.get('floor_number', 0)
        if not floor:
            continue
        # Nom dans la fusion : celui de RF, ou « Kanto » + nom quand il existait déjà dans Émeraude (import_kanto.py)
        target = None
        for name, map_id in ((m, fr['id']), ('Kanto' + m, 'MAP_KANTO_' + fr['id'][len('MAP_'):])):
            p = os.path.join(ROOT, 'data', 'maps', name, 'map.json')
            if os.path.exists(p):
                with open(p, encoding='utf-8') as f:
                    em = json.load(f)
                if em['id'] == map_id:
                    target = (p, em)
                    break
        if target is None:
            missing.append(m)
            continue
        p, em = target
        if em.get('floor_number') == floor:
            continue
        out = {}
        for k, v in em.items():
            if k == 'floor_number':
                continue
            out[k] = v
            if k == 'battle_scene':
                out['floor_number'] = floor
        write_json(p, out)
        changed += 1
    print(f'{changed} carte(s) avec étage ; absentes de la fusion : {missing}')


if __name__ == '__main__':
    sys.exit(main())
