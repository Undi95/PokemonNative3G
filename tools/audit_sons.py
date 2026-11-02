#!/usr/bin/env python3
"""
Les sons de Kanto sont-ils ceux de Rouge Feu ? Trois vérifications, par le nom d'origine de chaque son (commentaire
de include/constants/songs.h : « #define MUS_HEAL 368 // MUS_ME_ASA », sans le RG_ des copies de RF dans Émeraude) :

  pieges     les constantes de même nom dans les deux jeux mais pas le même son (SE_SHOP de RF = SE_RG_SHOP de la
             fusion), et leurs usages dans le code venu de RF (data/kanto, src/kanto_*.c, cartes de Kanto) ;
  fichiers   chaque fichier de RF et son équivalent dans la fusion : la même suite de sons ;
  chansons   chaque chanson de RF et celle de la fusion de même nom d'origine, compilées (tools/audit_sons.sh) : les
             octets joués, attentes additionnées (deux découpages d'une même attente sont égaux), en-tête, lecteur ;
             puis les samples convertis (même instrument, résolution différente : RF a ses samples à 13 379 Hz).

Usage : python tools/audit_sons.py [pieges|fichiers|chansons]  (tout par défaut)
"""
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RF = os.path.normpath(os.path.join(ROOT, '..', 'decomps', 'pokerougefeu'))
AUDIT = os.path.join(ROOT, 'out', 'audit-sons')
NOTES = ['Cn', 'Cs', 'Dn', 'Ds', 'En', 'Fn', 'Fs', 'Gn', 'Gs', 'An', 'As', 'Bn']
PLAYERS = {'MUSIC_PLAYER_BGM': '0', 'MUSIC_PLAYER_SE1': '1', 'MUSIC_PLAYER_SE2': '2', 'MUSIC_PLAYER_SE3': '3'}
SOUND = re.compile(r'\b((?:MUS|SE|PH)_\w+)\b')


def songs_h(root):
    """Constante -> (numéro, nom d'origine)."""
    consts = {}
    for line in open(os.path.join(root, 'include', 'constants', 'songs.h'), encoding='utf-8'):
        m = re.match(r'#define\s+((?:MUS|SE|PH)_\w+)\s+(\d+)\s*//\s*(\w+)', line)
        if m:
            consts[m.group(1)] = (int(m.group(2)), m.group(3).replace('_RG_', '_', 1))
    return consts


def aliases(root):
    """Les alias de sons des en-têtes (scripts de Kanto : SE_RS_DOOR -> SE_DOOR ; sac de RF : SE_BAG_CURSOR ->
    SE_RG_BAG_CURSOR, include/kanto_bag_compat.h)."""
    out = {}
    for dirpath, _, names in os.walk(os.path.join(root, 'include')):
        for n in names:
            if n.endswith('.h') and n != 'songs.h':
                text = open(os.path.join(dirpath, n), encoding='utf-8', errors='replace').read()
                out.update(re.findall(r'#define\s+((?:MUS|SE)_\w+)\s+((?:MUS|SE)_\w+)', text))
    return out


def song_table(root):
    table = []
    for line in open(os.path.join(root, 'sound', 'song_table.inc'), encoding='utf-8'):
        m = re.match(r'\s*song\s+(\w+),\s*(\w+),\s*(\w+)', line)
        if m:
            table.append((m.group(1), PLAYERS.get(m.group(2), m.group(2)), m.group(3)))
    return table


def by_origin(consts):
    out = {}
    for const, (_, jp) in consts.items():
        out.setdefault(jp, []).append(const)
    return out


def same_song(jp, fusion_by_jp):
    """La constante de la fusion pour un son de RF : la copie de RF (RG_) d'abord, car Émeraude réutilise des noms
    d'origine pour ses propres morceaux (MUS_AJITO : repaire Aqua/Magma ; MUS_RG_AJITO : repaire Rocket)."""
    cands = fusion_by_jp.get(jp, [])
    rg = [c for c in cands if '_RG_' in c]
    return (rg or cands or [None])[0]


# --- pieges --------------------------------------------------------------------------------------------------------
def kanto_files():
    files = []
    for base in ('data/kanto', 'src/data/kanto'):
        for dirpath, _, names in os.walk(os.path.join(ROOT, base)):
            files += [os.path.join(dirpath, n) for n in names if n.endswith(('.inc', '.s', '.h', '.c', '.json'))]
    files += [os.path.join(ROOT, 'src', n) for n in os.listdir(os.path.join(ROOT, 'src')) if n.startswith('kanto_')]
    for m in os.listdir(os.path.join(ROOT, 'data', 'kanto', 'data', 'maps')):
        p = os.path.join(ROOT, 'data', 'maps', m, 'map.json')
        if os.path.exists(p):
            files.append(p)
    for m in os.listdir(os.path.join(ROOT, 'data', 'maps')):
        if m.startswith('Kanto'):
            files.append(os.path.join(ROOT, 'data', 'maps', m, 'map.json'))
    return sorted(files)


def pieges():
    fc, rc = songs_h(ROOT), songs_h(RF)
    fjp = by_origin(fc)
    traps = sorted(c for c in set(fc) & set(rc) if fc[c][1] != rc[c][1])
    print('== Constantes de même nom, son différent ==')
    for c in traps:
        print(f'{c:28} RF = {rc[c][1]:16} fusion = {fc[c][1]:16} -> pour le son de RF : {same_song(rc[c][1], fjp)}')
    # Même nom d'origine porté par un morceau d'Émeraude et par la copie de RF (MUS_NAMINORI : MUS_SURF de Hoenn et
    # MUS_RG_SURF) : la constante de RF de ce nom (MUS_SURF) désigne la copie, celle de la fusion le morceau de Hoenn
    same_name = sorted(c for jp, consts in fjp.items() if any('_RG_' in x for x in consts)
                       for c in consts if '_RG_' not in c and c in rc and rc[c][1] == jp)
    print('\n== Même nom d\'origine, morceaux différents (Émeraude / copie de RF) ==')
    for c in same_name:
        print(f'{c:28} RF = {same_song(rc[c][1], fjp)} ; {c} de la fusion = le morceau d\'Émeraude')
    traps += same_name
    pattern = re.compile(r'\b(' + '|'.join(traps) + r')\b')
    print('\n== Leurs usages dans le code venu de RF (à vérifier un par un : un commentaire peut le justifier) ==')
    count = 0
    for path in kanto_files():
        for n, line in enumerate(open(path, encoding='utf-8', errors='replace'), 1):
            code = line.split('//')[0].split('@')[0]
            for c in pattern.findall(code):
                count += 1
                print(f'{os.path.relpath(path, ROOT)}:{n}: {c} : {line.strip()[:100]}')
    print(f'\n{len(traps)} constantes piège, {count} usages')


# --- fichiers ------------------------------------------------------------------------------------------------------
def counterparts(rel):
    parts = rel.split('/')
    if parts[:2] == ['data', 'maps']:
        return [rel] if parts[-1] == 'map.json' else ['data/kanto/' + rel]
    if parts[:2] == ['data', 'scripts']:
        return ['data/kanto/' + rel]
    if parts[0] == 'src' and len(parts) == 2:
        return ['src/kanto_' + parts[1]]
    if parts[:2] == ['src', 'data']:
        return ['src/data/kanto/' + '/'.join(parts[2:])]
    return []


def fichiers():
    fc, rc = songs_h(ROOT), songs_h(RF)
    fal = aliases(ROOT)
    fnames = {c: jp for c, (_, jp) in fc.items()}
    # MUS_SURF de la fusion n'est pas MUS_SURF de RF (MUS_RG_SURF) : même nom d'origine, morceau d'Émeraude
    fjp = by_origin(fc)
    for jp, consts in fjp.items():
        if any('_RG_' in c for c in consts):
            for c in consts:
                if '_RG_' not in c:
                    fnames[c] = jp + "(Émeraude)"
    fnames.update({a: fnames[t] for a, t in fal.items() if t in fnames})
    rnames = {c: jp for c, (_, jp) in rc.items()}

    def sounds(path, names):
        text = open(path, encoding='utf-8', errors='replace').read()
        text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
        text = re.sub(r'(//|@).*', '', text)    # commentaires (C, assembleur)
        return [names[c] for c in SOUND.findall(text) if c in names]

    same = differ = 0
    for base in ('data/maps', 'data/scripts', 'src'):
        for dirpath, _, files in os.walk(os.path.join(RF, base)):
            for f in files:
                if not f.endswith(('.c', '.inc', '.json', '.h')) or re.search(r'text(_de|_es|_it)?\.inc$', f):
                    continue                    # seul le français est dans la fusion
                rel = os.path.relpath(os.path.join(dirpath, f), RF).replace('\\', '/')
                rs = sounds(os.path.join(dirpath, f), rnames)
                cands = [c for c in counterparts(rel) if os.path.exists(os.path.join(ROOT, c))]
                if not rs or not cands:
                    continue
                fs = sounds(os.path.join(ROOT, cands[0]), fnames)
                if rs == fs:
                    same += 1
                    continue
                differ += 1
                only_rf = [x for x in dict.fromkeys(rs) if rs.count(x) > fs.count(x)]
                only_fu = [x for x in dict.fromkeys(fs) if fs.count(x) > rs.count(x)]
                detail = f'RF seul {only_rf} / fusion seule {only_fu}' if only_rf or only_fu else 'ordre différent'
                print(f'{rel} -> {cands[0]} : {detail}')
    print(f'\n{same} fichiers avec les mêmes sons, {differ} différents (cartes communes, code déplacé, choix de la fusion : '
          'voir docs/CONNAISSANCE-JEU.md, « Sons de Kanto »)')


# --- chansons ------------------------------------------------------------------------------------------------------
def note_value(tok):
    m = re.fullmatch(r'([A-G][ns])(M?)(\d)', tok)
    if not m:
        return None
    return NOTES.index(m.group(1)) + 12 * (int(m.group(3)) * (-1 if m.group(2) else 1) + 2)


def compiled(path):
    """(groupe de voix, en-tête, [(temps, commande)]) d'une chanson compilée par mid2agb."""
    text = open(path).read()
    label = re.search(r'\.global\s+(\w+)', text).group(1)
    consts = dict(re.findall(r'\.equ\s+' + label + r'_(\w+),\s*(.+)', text))
    env = {'mxv': 127, 'c_v': 64}
    for k in ('mvl', 'key', 'tbs', 'pri', 'exg', 'cmp'):
        if k in consts:
            env[f'{label}_{k}'] = int(consts[k])

    def value(expr):
        expr = expr.strip()
        if re.fullmatch(r'v\d+', expr):
            return ('v', int(expr[1:]))
        n = note_value(expr)
        if n is not None:
            return ('note', n)
        if re.fullmatch(r'[A-Z][A-Z0-9_]*', expr) and expr not in env:
            return expr
        e = re.sub(r'(\w+)', lambda m: str(env[m.group(1)]) if m.group(1) in env else m.group(1), expr)
        try:
            return eval(e.replace('/', '//'), {})
        except Exception:
            return expr.replace(label, 'SONG')

    out, t = [], 0
    for line in text.splitlines():
        s = line.strip()
        if s.startswith('.byte'):
            item = tuple(value(x) for x in s[5:].split(','))
            m = re.fullmatch(r'W(\d+)', item[0]) if len(item) == 1 and isinstance(item[0], str) else None
            if m:
                t += int(m.group(1))
            else:
                out.append((t, item))
        elif s.startswith(('.word', 'ptrvalue', '.int')):
            out.append((t, ('ptr', s.split(None, 1)[1].replace(label, 'SONG'))))
        elif re.fullmatch(r'\w+:', s):
            if not re.search(r'_L\d+:$', s):
                t = 0
            out.append((t, ('label', s[:-1].replace(label, 'SONG'))))
    return consts.get('grp'), (consts.get('pri'), consts.get('rev', '').replace(label, 'SONG')), out


def sample_kind(a, b):
    if a == b:
        return 'identique'
    ha, hb = struct.unpack('<4I', a[:16]), struct.unpack('<4I', b[:16])
    if a[16:] == b[16:]:
        return 'en-tête seul (' + ', '.join(f'{n} {x}/{y}' for n, x, y in
                                            zip(('type', 'fréquence', 'boucle', 'taille'), ha, hb) if x != y) + ')'
    return f'données (fréquence {ha[1] // 1024} / RF {hb[1] // 1024} Hz, {len(a) - 16} / RF {len(b) - 16} octets)'


def chansons():
    if not os.path.isdir(AUDIT):
        sys.exit(f'{AUDIT} manque : lancer d\'abord tools/audit_sons.sh (voir son en-tête)')
    fc, rc = songs_h(ROOT), songs_h(RF)
    ft, rt = song_table(ROOT), song_table(RF)
    fjp = by_origin(fc)
    same = differ = 0
    for rconst, (rnum, jp) in sorted(rc.items(), key=lambda x: x[1][0]):
        if rconst.startswith('PH_') or rnum >= len(rt) or rt[rnum][0] == 'mus_dummy':
            continue
        fconst = same_song(jp, fjp)
        if fconst is None:
            print(f'SANS ÉQUIVALENT {rconst} ({jp})')
            continue
        rfile, rplayer, rprio = rt[rnum]
        ffile, fplayer, fprio = ft[fc[fconst][0]]
        notes = []
        if (rplayer, rprio) != (fplayer, fprio):
            notes.append(f'table : lecteur {fplayer} prio {fprio} / RF {rplayer} {rprio}')
        rpath, fpath = os.path.join(AUDIT, 'rf', rfile + '.s'), os.path.join(AUDIT, 'fusion', ffile + '.s')
        if not (os.path.exists(rpath) and os.path.exists(fpath)):
            notes.append('non compilée')
        else:
            _, fhead, fbody = compiled(fpath)
            _, rhead, rbody = compiled(rpath)
            if fhead != rhead:
                notes.append(f'en-tête (priorité, réverbération) {fhead} / RF {rhead}')
            if fbody != rbody:
                diffs = [i for i, (a, b) in enumerate(zip(fbody, rbody)) if a != b]
                kinds = {'fin de piste' if fbody[i][1] == ('FINE',) else 'notes/volume' for i in diffs}
                notes.append(f'{len(diffs)} commandes différentes ({", ".join(sorted(kinds))}), ex. '
                             f'{fbody[diffs[0]] if diffs else "-"} / RF {rbody[diffs[0]] if diffs else "-"}')
        if notes:
            differ += 1
            print(f'DIFFÉRENTE {rconst} ({jp}) : RF {rfile} / fusion {fconst} {ffile}')
            for n in notes:
                print('    ' + n)
        else:
            same += 1
    print(f'\n{same} chansons identiques, {differ} différentes')

    counts = {}
    for name in sorted(os.listdir(os.path.join(AUDIT, 'samples', 'rf'))):
        f = os.path.join(AUDIT, 'samples', 'fusion', name)
        kind = 'absent de la fusion' if not os.path.exists(f) else \
            sample_kind(open(f, 'rb').read(), open(os.path.join(AUDIT, 'samples', 'rf', name), 'rb').read())
        counts[kind.split(' (')[0]] = counts.get(kind.split(' (')[0], 0) + 1
    print(f'samples de RF : {counts}')


if __name__ == '__main__':
    what = sys.argv[1:] or ['pieges', 'fichiers', 'chansons']
    for w in what:
        print(f'\n######## {w} ########')
        {'pieges': pieges, 'fichiers': fichiers, 'chansons': chansons}[w]()
