#!/usr/bin/env python3
"""
Les fonctions « à vérifier » de docs/carto/inventaire.md (une fonction de RF absente de la fusion par son nom, qui
ressemble à une fonction de la fusion) : ce qui diffère entre les deux corps, jeton par jeton, une fois enlevés les
commentaires, dépliées les macros sans paramètre de chaque fichier (#define tState data[0]) et remplacés les noms
que l'inventaire apparie (RF UseSurfEffect_3 = fusion SurfFieldEffect_ShowMon). « même code » : rien d'autre ne
diffère, la fonction peut aller dans tools/carto_classement.txt comme équivalente.

Usage : python tools/carto_diff.py FICHIER.c [NOM_RF ...] [--court]
        (FICHIER.c : le fichier de RF, comme dans l'inventaire ; --court : une ligne par fonction)
"""
import difflib
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RF = os.path.normpath(os.path.join(ROOT, '..', 'decomps', 'pokerougefeu'))
INV = os.path.join(ROOT, 'docs', 'carto', 'inventaire.md')
TOKEN = re.compile(r'0x[0-9A-Fa-f]+|\d+|[A-Za-z_]\w*|->|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||\+\+|--|[-+*/%&|^]=|\S')


def read(path):
    return open(path, encoding='utf-8', errors='replace').read()


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    return re.sub(r'//[^\n]*', ' ', text)


def pairs():
    """RF -> fusion : tous les couples de l'inventaire (à vérifier, équivalente)."""
    out = {}
    for line in read(INV).splitlines():
        m = re.match(r'(\w+) ~ (\w+) \(', line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def section(rf_file):
    """Les couples « à vérifier » d'un fichier de RF : [(nom RF, nom fusion, fichier fusion)]."""
    out, in_check, in_file = [], False, False
    for line in read(INV).splitlines():
        if line.startswith('## '):
            in_check = line.startswith('## À vérifier')
        elif line.startswith('### '):
            in_file = in_check and line.split()[1] == rf_file
        elif in_file:
            m = re.match(r'(\w+) ~ (\w+) \(([\w.]+)', line)
            if m:
                out.append(m.groups())
    return out


def body(text, name):
    """Le corps d'une fonction (de son nom à l'accolade fermante), ou None."""
    m = re.search(r'^[\w \t\*]*\b' + re.escape(name) + r'\s*\([^;{]*\)\s*\{', text, re.M)
    if not m:
        return None
    i, depth = m.end() - 1, 0
    while i < len(text):
        if text[i] == '{':
            depth += 1
        elif text[i] == '}':
            depth -= 1
            if depth == 0:
                return text[m.end():i]
        i += 1
    return None


def macros(text):
    out = {}
    for m in re.finditer(r'^\s*#define\s+(\w+)(?!\()\s+(.+?)\s*$', text, re.M):
        out[m.group(1)] = TOKEN.findall(m.group(2))
    return out


TYPES = {'u8', 'u16', 'u32', 's8', 's16', 's32', 'int', 'bool8', 'bool16', 'bool32', 'u64', 's64', 'char',
         'vu8', 'vu16', 'vu32', 'uintptr_t', 'size_t', 'struct', 'const'}
SAME = {'TRUE': '1', 'FALSE': '0', 'NULL': '0'}


def number(t):
    try:
        return str(int(t, 0))
    except ValueError:
        return t


def tokens(text, defs, rename):
    """Les jetons d'un corps, sans ce qui n'est qu'une façon d'écrire : accolades, TRUE/1, hexadécimal/décimal,
    GetGpuReg(REG_OFFSET_X) = REG_X, appels au journal de RF (écarté), variables locales (L1, L2… dans l'ordre)."""
    text = re.sub(r'\bQuestLog_\w+\s*\([^;]*\)\s*;', ' ', text)
    text = re.sub(r'\bGetGpuReg\s*\(\s*REG_OFFSET_(\w+)\s*\)', r'REG_\1', text)
    out, todo, depth = [], TOKEN.findall(text), 0
    while todo:
        t = todo.pop(0)
        if t in defs and depth < 200:
            todo = defs[t] + todo
            depth += 1
            continue
        if t in '{}':
            continue
        out.append(number(SAME.get(rename.get(t, t), rename.get(t, t))))
    # variables locales : déclarées par un type (« u16 offset ; », « s16 x = »)
    local = {}
    for i in range(1, len(out)):
        if out[i - 1] in TYPES or (out[i - 1] == '*' and i > 1 and out[i - 2] in TYPES):
            if re.fullmatch(r'[A-Za-z_]\w*', out[i]) and i + 1 < len(out) and out[i + 1] in (';', '=', ',', '['):
                local.setdefault(out[i], f'L{len(local) + 1}')
    return [local.get(t, t) for t in out]


def source(path_or_name, base):
    if os.path.exists(os.path.join(base, 'src', path_or_name)):
        return read(os.path.join(base, 'src', path_or_name))
    return ''


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    short = '--court' in sys.argv
    shown = None if '--tout' in sys.argv else 12   # --tout : toutes les différences
    rf_file = args[0]
    # NOM_RF=NOM_FUSION[@fichier.c] : comparer à une autre fonction que celle que l'inventaire a devinée
    forced = {}
    for a in args[1:]:
        if '=' in a:
            rf_name, target = a.split('=', 1)
            fu_name, _, fu_file = target.partition('@')
            forced[rf_name] = (fu_name, fu_file or rf_file)
    names = {a.split('=')[0] for a in args[1:]}
    rename = pairs()
    rename.update({k: v[0] for k, v in forced.items()})
    rf_text = strip_comments(source(rf_file, RF))
    rf_defs = macros(rf_text)
    same = 0
    todo = section(rf_file)
    todo += [(k, v[0], v[1]) for k, v in forced.items() if k not in {t[0] for t in todo}]
    for rf_name, fu_name, fu_file in todo:
        if names and rf_name not in names:
            continue
        fu_name, fu_file = forced.get(rf_name, (fu_name, fu_file))
        fu_text = strip_comments(source(fu_file, ROOT))
        a, b = body(rf_text, rf_name), body(fu_text, fu_name)
        if a is None or b is None:
            print(f'{rf_name} : corps introuvable ({"RF" if a is None else fu_file})')
            continue
        ta = tokens(a, rf_defs, rename)
        tb = tokens(b, macros(fu_text), {})
        ops = [op for op in difflib.SequenceMatcher(None, ta, tb, autojunk=False).get_opcodes() if op[0] != 'equal']
        if not ops:
            same += 1
            print(f'{rf_name} = {fu_name} ({fu_file}) : même code')
            continue
        print(f'{rf_name} ~ {fu_name} ({fu_file}) : {len(ops)} différence(s)')
        if short:
            continue
        for tag, i1, i2, j1, j2 in ops[:shown]:
            ctx = ' '.join(ta[max(0, i1 - 4):i1])
            print(f'    … {ctx} | RF « {" ".join(ta[i1:i2])} » / fusion « {" ".join(tb[j1:j2])} »')
        if shown and len(ops) > shown:
            print(f'    … et {len(ops) - shown} autres (--tout pour les voir)')
    print(f'\n{same} fonction(s) au même code')


if __name__ == '__main__':
    main()
