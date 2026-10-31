#!/usr/bin/env python3
"""Largeur du retour des specials lus par specialvar (PokemonNative3G, 2026-10-31).

Le port appelle les specials par un pointeur u16 (*)(void) (src/scrcmd.c). Sur PC, une fonction qui rend un u8, un
bool8 ou un s8 ne remplit que l'octet bas du registre : le reste peut valoir n'importe quoi (sur GBA, la fonction
étendait elle-même la valeur). Ces specials sont marqués dans data/specials.inc et data/kanto/kanto_specials.inc
(`def_special Nom, ret=SPECIAL_RET_U8` ou `SPECIAL_RET_S8`), et ScrCmd_specialvar ramène la valeur à cette largeur.

Usage (depuis la racine du projet) :
  python tools/special_returns.py           marque les specials qui ne le sont pas
  python tools/special_returns.py --check   vérifie seulement (code 1 s'il en manque ou si une marque est fausse)
"""
import glob
import re
import sys

SPECIAL_FILES = ('data/specials.inc', 'data/kanto/kanto_specials.inc')
RET_OF_TYPE = {'u8': 'SPECIAL_RET_U8', 'bool8': 'SPECIAL_RET_U8', 's8': 'SPECIAL_RET_S8'}


def rd(path):
    return open(path, encoding='utf-8', errors='ignore', newline='').read()


def read_by_specialvar():
    names = set()
    for path in glob.glob('data/**/*.inc', recursive=True) + glob.glob('data/**/*.s', recursive=True):
        names.update(re.findall(r'\bspecialvar\s+\w+\s*,\s*(\w+)', rd(path)))
    return names


def return_types(names):
    src = ''.join(rd(path) for path in glob.glob('src/*.c'))
    types = {}
    for name in names:
        m = re.search(r'^(?:static\s+)?(\w+)\s+' + name + r'\s*\(\s*void\s*\)', src, re.M)
        types[name] = m.group(1) if m else None
    return types


def main():
    check = '--check' in sys.argv
    types = return_types(read_by_specialvar())
    wanted = {name: RET_OF_TYPE[t] for name, t in types.items() if t in RET_OF_TYPE}
    problems = []
    for path in SPECIAL_FILES:
        text = rd(path)
        out = []
        for line in text.splitlines(keepends=True):
            m = re.match(r'(\s*def_special\s+)(\w+)(.*?)(\r?\n?)$', line)
            if not m or m.group(2) == 'ptr:req,':
                out.append(line)
                continue
            name, rest = m.group(2), m.group(3)
            have = re.search(r'ret=(\w+)', rest)
            want = wanted.get(name)
            if (have.group(1) if have else None) != want:
                problems.append(f'{path}: {name} ({types.get(name)}) : {have.group(1) if have else "sans marque"} -> {want}')
                if not check:
                    rest = re.sub(r',\s*ret=\w+', '', rest)
                    comment = ''
                    cm = re.search(r'\s*(@.*)$', rest)
                    if cm:
                        comment, rest = ' ' + cm.group(1).strip(), rest[:cm.start()]
                    if want:
                        rest += f', ret={want}'
                    line = m.group(1) + name + rest + comment + m.group(4)
            out.append(line)
        if not check:
            open(path, 'w', encoding='utf-8', newline='').write(''.join(out))
    for p in problems:
        print(p)
    print(f'{len(wanted)} specials à retour étroit lus par specialvar ; {len(problems)} marque(s) '
          + ('à corriger' if check else 'corrigée(s)'))
    return 1 if check and problems else 0


if __name__ == '__main__':
    sys.exit(main())
