#!/usr/bin/env python3
"""Cartographie Émeraude / Rouge Feu / fusion.

Compare les deux décomps (../decomps/pokeemeraude et ../decomps/pokerougefeu) et ce dépôt (la fusion),
puis écrit docs/carto/*.md. À relancer après chaque import :  python tools/cartographie.py
Repérage par NOM : une fonction de RF portée sous un autre nom n'est pas vue (variantes reconnues :
Kanto<Nom>, Kanto_<Nom>, <Nom>_Kanto ; constantes : PREFIXE_KANTO_..., ..._FRLG).
"""
import os
import re
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
E = os.path.normpath(os.path.join(ROOT, '..', 'decomps', 'pokeemeraude'))
R = os.path.normpath(os.path.join(ROOT, '..', 'decomps', 'pokerougefeu'))
F = ROOT
OUT = os.path.join(ROOT, 'docs', 'carto')

FUNC_RE = re.compile(r'^(?:[A-Za-z_]\w*[ \t*]+)+(\w+)\s*\([^;{}]*?\)\s*\n\{', re.M)
KEYWORDS = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'else'}
summary = []


def rd(p):
    with open(p, encoding='utf-8', errors='replace') as f:
        return f.read().replace('\r\n', '\n')


def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', '', t, flags=re.S)
    return re.sub(r'(?m)//[^\n]*', '', t)


def c_files(base):
    """chemins relatifs à src/ des .c (src/data exclu : ce sont des données incluses)"""
    res = []
    for d, _, fs in os.walk(os.path.join(base, 'src')):
        if os.sep + 'data' in d[len(base):]:
            continue
        res += [os.path.relpath(os.path.join(d, f), os.path.join(base, 'src')).replace('\\', '/') for f in fs if f.endswith('.c')]
    return sorted(res)


def functions(path):
    """{nom: corps normalisé} des fonctions définies dans un .c"""
    t = strip_comments(rd(path))
    res = {}
    for m in FUNC_RE.finditer(t):
        name = m.group(1)
        if name in KEYWORDS:
            continue
        start = m.end() - 1
        end = t.find('\n}', start)
        res[name] = re.sub(r'\s+', '', t[start:end + 2] if end >= 0 else '')
    return res


def all_functions(base):
    """fichier -> {nom: corps} ; nom -> {corps}"""
    per_file, by_name = {}, defaultdict(set)
    for f in c_files(base):
        fn = functions(os.path.join(base, 'src', f))
        per_file[f] = fn
        for n, b in fn.items():
            by_name[n].add(b)
    return per_file, by_name


def variants(n):
    return (n, 'Kanto' + n, 'Kanto_' + n, n + '_Kanto', 'Kanto' + n[:1].upper() + n[1:])


def defines(base, rel, prefix):
    p = os.path.join(base, rel)
    if not os.path.exists(p):
        return []
    seen, res = set(), []
    pat = r'^\s*(?:#define\s+(%s\w+)|(%s\w+)\s*(?:=[^,\n]*)?,)' % (re.escape(prefix), re.escape(prefix))
    for m in re.finditer(pat, strip_comments(rd(p)), re.M):
        n = m.group(1) or m.group(2)
        if n not in seen:
            seen.add(n)
            res.append(n)
    return res


def define_values(base, rel, prefix):
    p = os.path.join(base, rel)
    raw = {m.group(1): m.group(2) for m in re.finditer(
        r'^\s*#define\s+(%s\w+)\s+(0x[0-9A-Fa-f]+|\d+|%s\w+)\b' % (re.escape(prefix), re.escape(prefix)), rd(p), re.M)}
    res = {}
    for n, v in raw.items():
        while v in raw and v != n:  # alias : #define ITEM_TM01_FOCUS_PUNCH ITEM_TM01
            v = raw[v]
        if v[:1].isdigit():
            res[n] = int(v, 0)
    return res


def fusion_defines():
    s = set()
    for d, _, fs in os.walk(os.path.join(F, 'include')):
        for f in fs:
            if f.endswith('.h'):
                t = rd(os.path.join(d, f))
                s.update(re.findall(r'^\s*#define\s+(\w+)', t, re.M))
                s.update(re.findall(r'^\s+([A-Z][A-Z0-9_]+)\s*(?:=[^,\n]*)?,', t, re.M))
    return s


def const_in_fusion(name, prefix, fdefs):
    rest = name[len(prefix):]
    return any(v in fdefs for v in (name, prefix + 'KANTO_' + rest, prefix + 'RG_' + rest, name + '_FRLG', 'KANTO_' + name))


def wrap(names, width=110):
    lines, cur = [], ''
    for n in names:
        if cur and len(cur) + len(n) + 2 > width:
            lines.append(cur + ',')
            cur = n
        else:
            cur = cur + ', ' + n if cur else n
    if cur:
        lines.append(cur)
    return '\n'.join(lines) if lines else '(aucun)'


def write(name, title, body):
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, name), 'w', encoding='utf-8', newline='\n') as f:
        f.write('# %s\n\n> Généré par `tools/cartographie.py` — ne pas éditer à la main.\n\n%s\n' % (title, body.rstrip()))


# ---------------------------------------------------------------- sources C
eF, eN = all_functions(E)
rF, rN = all_functions(R)
fF, fN = all_functions(F)
fusion_names = set(fN)
stub_file = 'kanto_specials_stubs.c'
stubbed = set(re.findall(r'^\w[\w \t*]*?\b(\w+)\([^)]*\)\s*\{', rd(os.path.join(F, 'src', stub_file)), re.M))
fusion_names |= stubbed


def ported(n):
    return any(v in fusion_names for v in variants(n)) and n not in stubbed


def where_in_fusion(names):
    c = Counter()
    for n in names:
        for f, fn in fF.items():
            if any(v in fn for v in variants(n)):
                c[f] += 1
                break
    return ', '.join('%s (%d)' % (f, k) for f, k in c.most_common(3))


e_body = {}
for fn in eF.values():
    for n, b in fn.items():
        if len(b) > 40:
            e_body.setdefault(b, n)
e_files, r_files = set(eF), set(rF)
# copies Kanto d'un fichier RF : src/kanto_<nom>.c (sinon table ci-dessous)
KANTO_SRC = {'kanto_summary_screen.c': 'pokemon_summary_screen.c', 'kanto_specials.c': 'field_specials.c',
             'kanto_list_menu.c': 'field_specials.c', 'kanto_save.c': None}
kanto_copy = defaultdict(list)
for ff in fF:
    if ff.startswith('kanto_'):
        src = KANTO_SRC.get(ff, ff[len('kanto_'):])
        if src in rF:
            kanto_copy[src].append(ff)
rows, missing, diff_rows = [], [], []
tot = Counter()
for f in sorted(r_files):
    fn = rF[f]
    only = [n for n in fn if n not in eN]
    common = [n for n in fn if n in eN]
    same = [n for n in common if fn[n] in eN[n]]
    diff = [n for n in common if fn[n] not in eN[n]]
    only_ok = [n for n in only if ported(n)]
    renamed = [n for n in only if n not in only_ok and fn[n] in e_body]
    diff_ok = [n for n in diff if any(v in fusion_names for v in variants(n)[1:])]
    tot.update(fn=len(fn), only=len(only), only_ok=len(only_ok), renamed=len(renamed), same=len(same), diff=len(diff), diff_ok=len(diff_ok))
    kind = 'RF seul' if f not in e_files else 'commun'
    pct = 100 * (len(only_ok) + len(renamed)) // len(only) if only else 100
    copies = kanto_copy.get(f, [])
    in_copy = [n for n in fn if any(v in fF[c] for c in copies for v in variants(n))]
    where = '; '.join(['copie %s : %d/%d fonctions' % ('+'.join(copies), len(in_copy), len(fn))] if copies else [])
    other = where_in_fusion([n for n in only_ok if n not in in_copy])
    where = '; '.join(x for x in (where, other) if x)
    rows.append((f, kind, len(fn), len(only), len(renamed), len(only_ok), pct, len(same), len(diff), where))
    lost = [n for n in only if n not in only_ok and n not in renamed]
    if lost:
        missing.append('### %s (%s, %d/%d)\n%s\n' % (f, kind, len(lost), len(only), wrap(lost)))
    if diff:
        diff_rows.append('### %s\n%s\n' % (f, wrap(['%s%s' % (n, ' ✓' if n in diff_ok else '') for n in diff])))

hdr = ('| Fichier RF | Où | Fonctions | Propres à RF | dont même code dans Ém. | dont portées | % couvert | Identiques à Ém. | Différentes d\'Ém. | Fichier(s) de la fusion |\n'
       '|---|---|---|---|---|---|---|---|---|---|\n')
only_rf_rows = [r for r in rows if r[1] == 'RF seul']
common_rows = [r for r in rows if r[1] == 'commun']
fmt = lambda r: '| %s | %s | %d | %d | %d | %d | %d | %d | %d | %s |' % r
body = ('Légende : « Propres à RF » = noms de fonctions absents de tout `src/` d\'Émeraude ; « même code dans Ém. » = '
        'corps identique à une fonction d\'Émeraude d\'un autre nom (rien à porter) ; « portées » = définies dans ce dépôt '
        'sous le même nom ou une variante Kanto (stubs compris) ; « Différentes d\'Ém. » = même nom, corps différent '
        '(comportement ou présentation propre à RF, ou simple écart de constantes).\n\n'
        '## Fichiers présents seulement dans Rouge Feu (%d)\n\n' % len(only_rf_rows) + hdr +
        '\n'.join(fmt(r) for r in sorted(only_rf_rows, key=lambda r: (r[6], -r[3]))) +
        '\n\n## Fichiers présents dans les deux jeux (%d)\n\n' % len(common_rows) + hdr +
        '\n'.join(fmt(r) for r in sorted(common_rows, key=lambda r: -(r[3] - r[4] - r[5] + r[8]))) +
        '\n\n## Fichiers présents seulement dans Émeraude (%d)\n\n' % len(e_files - r_files) +
        wrap(['%s (%d)' % (f, len(eF[f])) for f in sorted(e_files - r_files)]) + '\n')
write('sources.md', 'Sources C : Émeraude / Rouge Feu / fusion', body)
write('fonctions-rf-absentes.md', 'Fonctions propres à Rouge Feu absentes de la fusion',
      'Par fichier RF : (nombre absent / nombre propre à RF). Les stubs de `%s` comptent comme absents.\n\n' % stub_file +
      '\n'.join(missing))
write('fonctions-divergentes.md', 'Fonctions de même nom, corps différent (RF vs Émeraude)',
      '« ✓ » = une variante Kanto existe dans la fusion. Sans ✓ : la fusion utilise la version d\'Émeraude partout.\n\n' +
      '\n'.join(diff_rows))
summary.append('SOURCES : %d .c Ém. / %d .c RF / %d .c fusion ; RF seul %d fichiers, commun %d, Ém. seul %d' % (
    len(e_files), len(r_files), len(fF), len(only_rf_rows), len(common_rows), len(e_files - r_files)))
summary.append('FONCTIONS RF : %(fn)d dont propres %(only)d (même code Ém. %(renamed)d, portées %(only_ok)d), mêmes noms identiques %(same)d, divergentes %(diff)d (variante Kanto %(diff_ok)d)' % tot)
summary.append('Fichiers RF seuls par % couvert : ' + ' | '.join('%s %d%%/%d' % (r[0], r[6], r[3]) for r in sorted(only_rf_rows, key=lambda r: r[6]) if r[3]))
summary.append('Copies Kanto : ' + ' | '.join('%s %s' % (r[0], r[9]) for r in rows if r[9].startswith('copie')))
summary.append('Fichiers communs, propres RF non couverts : ' + ' | '.join('%s %d' % (r[0], r[3] - r[4] - r[5]) for r in sorted(common_rows, key=lambda r: -(r[3] - r[4] - r[5]))[:40]))

# ---------------------------------------------------------------- constantes
fdefs = fusion_defines()
CONSTS = [
    ('Objets', 'include/constants/items.h', 'ITEM_'),
    ('Espèces', 'include/constants/species.h', 'SPECIES_'),
    ('Capacités', 'include/constants/moves.h', 'MOVE_'),
    ('Talents', 'include/constants/abilities.h', 'ABILITY_'),
    ('Types de combat', 'include/constants/battle.h', 'BATTLE_TYPE_'),
    ('Effets de terrain', 'include/constants/field_effects.h', 'FLDEFF_'),
    ('Actions de déplacement', 'include/constants/event_object_movement.h', 'MOVEMENT_ACTION_'),
    ('Types de déplacement', 'include/constants/event_object_movement.h', 'MOVEMENT_TYPE_'),
    ('Comportements de métatiles', 'include/constants/metatile_behaviors.h', 'MB_'),
    ('Météo', 'include/constants/weather.h', 'WEATHER_'),
    ('Musiques', 'include/constants/songs.h', 'MUS_'),
    ('Bruitages', 'include/constants/songs.h', 'SE_'),
    ('Classes de dresseurs', 'include/constants/trainers.h', 'TRAINER_CLASS_'),
    ('Portraits de dresseurs', 'include/constants/trainers.h', 'TRAINER_PIC_'),
    ('Sprites de terrain', 'include/constants/event_objects.h', 'OBJ_EVENT_GFX_'),
    ('Statistiques de jeu', 'include/constants/game_stat.h', 'GAME_STAT_'),
    ('Effets d\'objets tenus', 'include/constants/hold_effects.h', 'HOLD_EFFECT_'),
    ('Effets de capacités', 'include/constants/battle_move_effects.h', 'EFFECT_'),
    ('Drapeaux', 'include/constants/flags.h', 'FLAG_'),
    ('Variables', 'include/constants/vars.h', 'VAR_'),
]
parts = ['| Catégorie | Émeraude | Rouge Feu | Communs | RF seul | RF seul présent dans la fusion |\n|---|---|---|---|---|---|']
details = []
for title, rel, pre in CONSTS:
    ce, cr = defines(E, rel, pre), defines(R, rel, pre)
    se, sr = set(ce), set(cr)
    ronly = [n for n in cr if n not in se]
    ok = [n for n in ronly if const_in_fusion(n, pre, fdefs)]
    alias = {}
    if pre == 'ITEM_':  # numéros d'objets communs à la 3G : un nom propre à RF peut être un autre nom d'Émeraude
        ve, vr = define_values(E, rel, pre), define_values(R, rel, pre)
        inv = {v: n for n, v in ve.items()}
        alias = {n: inv[vr[n]] for n in ronly if n in vr and vr[n] in inv}
        ok += [n for n in alias if n not in ok]
    parts.append('| %s (`%s`) | %d | %d | %d | %d | %d |' % (title, pre, len(ce), len(cr), len(se & sr), len(ronly), len(ok)))
    if pre in ('FLAG_', 'VAR_'):
        continue  # trop longs : voir les en-têtes ; ceux de Kanto sont préfixés KANTO_ dans la fusion
    details.append('## %s (`%s`, %s)\n\n**Rouge Feu seulement** (✗ = absent de la fusion) :\n%s\n\n**Émeraude seulement** :\n%s\n' % (
        title, pre, rel, wrap([n + (' = ' + alias[n] if n in alias else '' if n in ok else ' ✗') for n in ronly]),
        wrap([n for n in ce if n not in sr])))
    summary.append('CONST %s : Ém %d / RF %d / RF seul %d (fusion %d)' % (pre, len(ce), len(cr), len(ronly), len(ok)))
write('constantes.md', 'Constantes : Émeraude / Rouge Feu / fusion', '\n'.join(parts) + '\n\n' + '\n'.join(details))


# ---------------------------------------------------------------- scripts : specials, commandes, macros, fichiers
def specials(base):
    return list(dict.fromkeys(re.findall(r'^\s*def_special\s+(\w+)', rd(os.path.join(base, 'data/specials.inc')), re.M)))


def scrcmds(base):
    return re.findall(r'^\s*\.4byte\s+(\w+)', rd(os.path.join(base, 'data/script_cmd_table.inc')), re.M)


def macros(base, rel):
    return re.findall(r'^\s*\.macro\s+(\w+)', rd(os.path.join(base, rel)), re.M)


def listdir(base, rel):
    p = os.path.join(base, rel)
    return sorted(os.listdir(p)) if os.path.isdir(p) else []


out = []
se, sr = specials(E), specials(R)
r_sp = [n for n in sr if n not in set(se)]
st = {'porté': [], 'stub': [], 'absent': []}
for n in r_sp:
    st['stub' if n in stubbed else 'porté' if ported(n) else 'absent'].append(n)
out.append('## Specials (`data/specials.inc`)\n\nÉmeraude %d, Rouge Feu %d, communs %d.\n\n**RF seul — portés (%d)** :\n%s\n\n'
           '**RF seul — stubs (%d)** (`src/%s`) :\n%s\n\n**RF seul — absents (%d)** :\n%s\n\n**Émeraude seul (%d)** :\n%s\n' % (
               len(se), len(sr), len(set(se) & set(sr)), len(st['porté']), wrap(st['porté']), len(st['stub']), stub_file,
               wrap(st['stub']), len(st['absent']), wrap(st['absent']), len(set(se) - set(sr)), wrap([n for n in se if n not in set(sr)])))
summary.append('SPECIALS : Ém %d / RF %d ; RF seul %d = porté %d, stub %d, absent %d' % (
    len(se), len(sr), len(r_sp), len(st['porté']), len(st['stub']), len(st['absent'])))

ce, cr = scrcmds(E), scrcmds(R)
lines = []
for i in range(max(len(ce), len(cr))):
    a = ce[i] if i < len(ce) else '—'
    b = cr[i] if i < len(cr) else '—'
    if a != b:
        lines.append('| 0x%02x | %s | %s |' % (i, a, b))
out.append('## Commandes de script (`data/script_cmd_table.inc`)\n\nÉmeraude %d, Rouge Feu %d. Opcodes qui diffèrent '
           '(la fusion garde ceux d\'Émeraude ; ceux de RF sont dans `src/kanto_scrcmd.c`) :\n\n| Opcode | Émeraude | Rouge Feu |\n|---|---|---|\n%s\n' % (
               len(ce), len(cr), '\n'.join(lines)))

for title, rel in (('Macros de script', 'asm/macros/event.inc'), ('Macros de script de combat', 'asm/macros/battle_script.inc'),
                   ('Macros de mouvement', 'asm/macros/movement.inc')):
    me, mr = macros(E, rel), macros(R, rel)
    fm = set(macros(F, rel))
    for extra in ('asm/macros/kanto_event.inc',):
        if rel.endswith('event.inc') and os.path.exists(os.path.join(F, extra)):
            fm |= set(macros(F, extra))
    ronly = [n for n in mr if n not in set(me)]
    out.append('## %s (`%s`)\n\nÉmeraude %d, Rouge Feu %d.\n\n**RF seul** (✗ = absent de la fusion) :\n%s\n\n**Émeraude seul** :\n%s\n' % (
        title, rel, len(me), len(mr), wrap([n + ('' if n in fm else ' ✗') for n in ronly]), wrap([n for n in me if n not in set(mr)])))

de, dr = listdir(E, 'data/scripts'), listdir(R, 'data/scripts')
out.append('## Scripts communs (`data/scripts/`)\n\n**RF seul** :\n%s\n\n**Émeraude seul** :\n%s\n\n**Communs** :\n%s\n' % (
    wrap([n for n in dr if n not in de]), wrap([n for n in de if n not in dr]), wrap([n for n in dr if n in de])))
write('scripts.md', 'Scripts : specials, commandes, macros', '\n'.join(out))


# ---------------------------------------------------------------- graphismes, sauvegarde, cartes
def gfx_dirs(base):
    res = []
    g = os.path.join(base, 'graphics')
    for d in sorted(os.listdir(g)):
        if os.path.isdir(os.path.join(g, d)):
            res.append(d)
    return res


ge, gr = gfx_dirs(E), gfx_dirs(R)
kg = set(listdir(F, 'graphics/kanto'))
fg = set(gfx_dirs(F))
gfx = ('## Dossiers `graphics/`\n\n**RF seul** (✓ = un dossier du même nom existe dans `graphics/` ou `graphics/kanto/` de la fusion) :\n%s\n\n'
       '**Émeraude seul** :\n%s\n\n**Communs** (contenu souvent différent ; les variantes RF importées sont sous `graphics/kanto/`) :\n%s\n\n'
       '**Dans `graphics/kanto/` de la fusion** :\n%s\n') % (
    wrap([n + (' ✓' if n in kg or n in fg else '') for n in gr if n not in ge]), wrap([n for n in ge if n not in gr]),
    wrap([n + (' (kanto ✓)' if n in kg else '') for n in gr if n in ge]), wrap(sorted(kg)))


def save_fields(base, struct):
    t = strip_comments(rd(os.path.join(base, 'include/global.h')))
    m = re.search(r'^struct %s\n\{(.*?)^\};' % struct, t, re.M | re.S)
    if not m:
        return []
    return [re.sub(r'\[.*', '', x) for x in re.findall(r'(\w+(?:\[[^\]]*\])*)\s*(?::\s*\d+)?\s*;', m.group(1))]


sav = []
for s in ('SaveBlock1', 'SaveBlock2'):
    fe, fr = save_fields(E, s), save_fields(R, s)
    sav.append('### %s\n\n**RF seul** :\n%s\n\n**Émeraude seul** :\n%s\n' % (s, wrap([n for n in fr if n not in fe]), wrap([n for n in fe if n not in fr])))
ks = os.path.join(F, 'include/kanto_save.h')
if os.path.exists(ks):
    m = re.search(r'struct SaveBlockKanto\s*\{(.*?)\};', strip_comments(rd(ks)), re.S)
    if m:
        sav.append('### SaveBlockKanto (fusion, `include/kanto_save.h`)\n\n%s\n' % wrap(
            [re.sub(r'\[.*', '', x) for x in re.findall(r'(\w+(?:\[[^\]]*\])*)\s*(?::\s*\d+)?\s*;', m.group(1))]))


def map_groups(base):
    j = rd(os.path.join(base, 'data/maps/map_groups.json'))
    import json
    d = json.loads(j)
    return {g: d[g] for g in d.get('group_order', [])}


mg_e, mg_r, mg_f = map_groups(E), map_groups(R), map_groups(F)
maps = '## Cartes (`data/maps/map_groups.json`)\n\nÉmeraude : %d groupes, %d cartes. Rouge Feu : %d groupes, %d cartes. Fusion : %d groupes, %d cartes.\n' % (
    len(mg_e), sum(map(len, mg_e.values())), len(mg_r), sum(map(len, mg_r.values())), len(mg_f), sum(map(len, mg_f.values())))
fm = {m for g in mg_f.values() for m in g}
rmiss = [m for g in mg_r.values() for m in g if not any(v in fm for v in (m, 'Kanto' + m, m + '_Frlg'))]
maps += '\nCartes de RF absentes de la fusion (par nom) : %d\n%s\n' % (len(rmiss), wrap(rmiss))
em = {m for g in mg_e.values() for m in g}
same = [m for g in mg_r.values() for m in g if m in em]
maps += ('\nCartes de RF de même nom qu\'une carte d\'Émeraude : %d (→ Kanto<Nom> = importée sous ce nom ; sinon la fusion '
         'n\'a que celle d\'Émeraude)\n%s\n') % (len(same), wrap([m + (' → Kanto' + m if 'Kanto' + m in fm else '') for m in same]))
write('donnees.md', 'Graphismes, sauvegarde, cartes', gfx +'\n## Sauvegarde (`include/global.h`)\n\n' + '\n'.join(sav) + '\n' + maps)
summary.append('CARTES : Ém %d / RF %d / fusion %d' % (sum(map(len, mg_e.values())), sum(map(len, mg_r.values())), sum(map(len, mg_f.values()))))
summary.append('GRAPHICS : RF seul ' + ', '.join(n for n in gr if n not in ge) + ' | Ém seul ' + ', '.join(n for n in ge if n not in gr))
print('\n'.join(summary))
