#!/usr/bin/env python3
"""
Les fonctions de même nom dans Rouge Feu et dans la fusion, au corps différent (docs/carto/fonctions-divergentes.md) :
ce qui diffère vraiment entre le corps de RF et celui de la fusion (ce que le jeu exécute), une fois enlevé ce qui
n'est qu'une façon d'écrire (tools/carto_diff.py : commentaires, macros sans paramètre, TRUE/1, hexadécimal,
variables locales, journal de RF) et remplacés les noms déjà appariés (équivalences de l'inventaire, préfixes des
constantes de Kanto : FLAG_X de RF = FLAG_KANTO_X de la fusion).

Le classement à la main va dans tools/carto_divergentes.txt (« NOM catégorie preuve », comme carto_classement.txt) ;
une fonction classée n'est plus listée « à lire ».

Usage : python tools/carto_divergentes.py [FICHIER.c ...] [--tout] [--resume]
        (sans fichier : tous ; --resume : une ligne par fichier ; --tout : toutes les différences de chaque fonction)
Sortie : docs/carto/divergentes-tri.md (le tableau par fichier et la liste à lire), et le détail à l'écran.
"""
import difflib
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from carto_diff import RF, ROOT, body, macros, read, strip_comments, tokens  # noqa: E402

DIVERGENT = os.path.join(ROOT, 'docs', 'carto', 'fonctions-divergentes.md')
INV = os.path.join(ROOT, 'docs', 'carto', 'inventaire.md')
CLASSES = os.path.join(ROOT, 'tools', 'carto_divergentes.txt')
OUT = os.path.join(ROOT, 'docs', 'carto', 'divergentes-tri.md')
# Constantes de Kanto : même nom que dans RF, avec KANTO_ après le préfixe (tools/kanto/import_kanto.py)
KANTO_PREFIXES = ('FLAG_', 'VAR_', 'TRAINER_', 'LOCALID_', 'OBJ_EVENT_GFX_', 'MAPSEC_')
# Familles classées par une règle (décisions du user), sauf si une fonction cite un marqueur propre à Kanto (plus bas)
FAMILY_RULES = (
    (r'^(link|link_rfu|librfu|AgbRfu|union_room|cable_club|trade|berry_crush|dodrio_berry_picking|pokemon_jump|'
     r'mystery_|record_mixing|wireless_communication|battle_controller_link_|berry_fix)',
     'écartée', "link d'Émeraude dans les deux régions (règle des variantes 2026-11-02 ; caché : LINK_ENABLED)"),
    (r'^battle_anim', 'écartée', "animations de combat d'Émeraude dans les deux régions (règle des variantes, "
                                 "docs/VARIANTES-RF.md)"),
    (r'^(battle_script_commands|battle_util|battle_main|battle_controller_(player|opponent|player_partner|safari|'
     r'wally)|battle_ai_|battle_interface|battle_gfx_sfx_util|battle_message|battle_bg|battle_setup|'
     r'battle_transition|battle_tv|reshow_battle_screen|battle_records|battle_dome|battle_tower|pokeball|'
     r'battle_intro|recorded_battle)',
     'écartée', "moteur de combat d'Émeraude dans les deux régions (règle des variantes) ; sans marqueur des "
                "combats propres à Kanto (vieil homme, Pokédude, fantôme, Safari, Tour des Dresseurs, légendaires)"),
    (r'^(bg|sprite|text|palette|menu|list_menu|string_util|menu_indicators|new_menu_helpers|main|gpu_regs|malloc|'
     r'decompress|window|blit|dma3_manager|task|scanline_effect|random|util|text_printer|text_window|'
     r'text_window_graphics|window_8bpp|tilemap_util|blend_palette|librfu|m4a|sound|save|load_save|agb_flash|'
     r'siirtc|rtc|play_time|multiboot|isagbprn|trig|math_util)\.c$',
     'écartée', "moteur commun d'Émeraude (graphismes, texte, menus, sauvegarde, son) dans les deux régions (règle "
                "des variantes) ; les écrans de RF qui en ont besoin ont leur copie kanto_*.c"),
    (r'^pokemon_storage_system', 'écartée', "écran du PC d'Émeraude dans les deux régions (fonds de RF ajoutés ; "
                                            "règle des variantes)"),
)
# Marqueurs de RF propres à Kanto : une fonction qui en cite un (absent du corps de la fusion) se lit à la main
KANTO_MARKERS = re.compile(r'^(BATTLE_TYPE_(POKEDUDE|OLD_MAN_TUTORIAL|GHOST|SAFARI|TRAINER_TOWER|FIRST_BATTLE|'
                           r'LEGENDARY|ROAMER)|FIRERED|LEAFGREEN|TRAINER_CLASS_|MAP_|FLAG_|VAR_|SPECIES_|ITEM_|'
                           r'MUS_|SE_)')


def divergent():
    """[(fichier RF, nom, variante Kanto ✓)] dans l'ordre de fonctions-divergentes.md."""
    out, current = [], None
    for line in read(DIVERGENT).splitlines():
        if line.startswith('### '):
            current = line[4:].strip()
        elif current and line.strip() and not line.startswith(('#', '>', '«')):
            for item in line.split(','):
                item = item.strip()
                if item:
                    out.append((current, item.replace('✓', '').strip(), '✓' in item))
    return out


def equivalences():
    """RF -> fusion : les équivalences prouvées de l'inventaire (« NomRF (NomFusion (fichier… »)."""
    out = {}
    section = False
    for line in read(INV).splitlines():
        if line.startswith('## '):
            section = line.startswith('## Équivalente')
        elif section:
            m = re.match(r'(\w+) \((\w+) \(', line)
            if m:
                out[m.group(1)] = m.group(2)
    return out


def classes():
    out = {}
    if os.path.exists(CLASSES):
        for line in read(CLASSES).splitlines():
            if line.strip() and not line.lstrip().startswith('#'):
                parts = line.split(None, 2)
                if len(parts) >= 2:
                    out[parts[0]] = (parts[1], parts[2] if len(parts) > 2 else '')
    return out


def kanto_names(fu_tokens):
    """FLAG_KANTO_X de la fusion -> FLAG_X (le nom de RF), pour comparer les jetons."""
    out = []
    for t in fu_tokens:
        for p in KANTO_PREFIXES:
            if t.startswith(p + 'KANTO_'):
                t = p + t[len(p) + 6:]
                break
        out.append(t)
    return out


# Normalisation de plus que carto_diff.py, pour ne garder que les différences de sens : préfixes g/s des globales
# (gMovementDelaysMedium = sMovementDelaysMedium), NELEMS = ARRAY_COUNT, constantes remplacées par leur valeur (chaque
# jeu par ses en-têtes et son .c), variables locales et paramètres anonymes. Les noms de drapeaux, variables, cartes,
# dresseurs, espèces, objets, attaques et sons gardent leur nom : leurs valeurs diffèrent entre les deux jeux.
KEEP_NAMES = re.compile(r'^(FLAG_|VAR_|TRAINER_|MAP_(?!OFFSET)|OBJ_EVENT_GFX_|LOCALID_|SPECIES_|ITEM_|'
                        r'MOVE_(?!SPEED)|MUS_|SE_|BATTLE_TYPE_|MAPSEC_|LAYOUT_|HEAL_LOCATION_|SPECIAL_VAR_)')
NUM = re.compile(r'^\d+$')


def fold(toks):
    """Les petites expressions constantes : ( 16 ) = 16, 1 << 4 = 16, 5 + 1 = 6 (si rien de plus prioritaire autour)."""
    changed = True
    while changed:
        changed = False
        out, i = [], 0
        while i < len(toks):
            t = toks[i]
            if t == '(' and i + 2 < len(toks) and NUM.match(toks[i + 1]) and toks[i + 2] == ')' \
                    and not (out and re.match(r'[A-Za-z_]\w*$', out[-1])):     # pas un appel f(16)
                out.append(toks[i + 1]); i += 3; changed = True
                continue
            if NUM.match(t) and i + 2 < len(toks) and toks[i + 1] in ('<<', '+') and NUM.match(toks[i + 2]) \
                    and not (out and out[-1] in ('*', '/', '%', '<<', '>>', '-')) \
                    and not (i + 3 < len(toks) and toks[i + 3] in ('*', '/', '%')):
                a, b = int(t), int(toks[i + 2])
                out.append(str(a << b if toks[i + 1] == '<<' else a + b)); i += 3; changed = True
                continue
            # ( 3 - 1 ) = 2 : seulement entre parenthèses (la priorité est sûre)
            if t == '(' and i + 4 < len(toks) and NUM.match(toks[i + 1]) and toks[i + 2] == '-' \
                    and NUM.match(toks[i + 3]) and toks[i + 4] == ')' and int(toks[i + 1]) >= int(toks[i + 3]):
                out.append(str(int(toks[i + 1]) - int(toks[i + 3]))); i += 5; changed = True
                continue
            out.append(t); i += 1
        toks = out
    return toks
_CONSTANTS = {}


def parse_constants(t, vals, known=None):
    """Les #define et enum à valeur entière du texte t (comme tools/cartographie.py)."""
    known = known or {}
    get = lambda n: vals.get(n, known.get(n))
    for name, v in re.findall(r'^\s*#define\s+(\w+)\s+\(?(0x[0-9A-Fa-f]+|\d+)\)?\s*$', t, re.M):
        vals.setdefault(name, int(v, 0))
    for block in re.findall(r'\benum\s*\w*\s*\{(.*?)\}', t, re.S):
        cur = -1
        for item in block.split(','):
            m = re.match(r'\s*(\w+)\s*(?:=\s*(.+?))?\s*$', item, re.S)
            if not m:
                continue
            expr = m.group(2)
            if expr is None:
                cur += 1
            elif re.match(r'^(0x[0-9A-Fa-f]+|\d+)$', expr):
                cur = int(expr, 0)
            elif get(expr) is not None:
                cur = get(expr)
            else:
                mm = re.match(r'^(\w+)\s*\+\s*(\d+)$', expr)
                if mm and get(mm.group(1)) is not None:
                    cur = get(mm.group(1)) + int(mm.group(2))
                else:
                    break
            vals.setdefault(m.group(1), cur)
    return vals


def constants(base):
    if base not in _CONSTANTS:
        vals = {}
        for d, _, fs in os.walk(os.path.join(base, 'include')):
            for f in fs:
                if f.endswith('.h'):
                    parse_constants(strip_comments(read(os.path.join(d, f))), vals)
        _CONSTANTS[base] = vals
    return _CONSTANTS[base]


def params(text, name):
    """Les noms des paramètres de la fonction name."""
    m = re.search(r'^[\w \t\*]*\b' + re.escape(name) + r'\s*\(([^;{]*)\)\s*\{', text, re.M)
    if not m:
        return set()
    out = set()
    for p in m.group(1).split(','):
        ids = re.findall(r'[A-Za-z_]\w*', p.split('[')[0])
        if ids and ids[-1] != 'void':
            out.add(ids[-1])
    return out


def normalize(toks, vals, args):
    out = []
    for t in toks:
        if t == 'NELEMS':
            t = 'ARRAY_COUNT'
        if re.fullmatch(r'L\d+', t) or t in args:
            t = 'L'
        elif re.fullmatch(r'[A-Za-z_]\w*', t) and not KEEP_NAMES.match(t):
            if t in vals:
                t = str(vals[t])
            elif re.match(r'^[gs][A-Z]', t):
                t = t[1:]
        out.append(t)
    return fold(out)


_IDENTS = {}
LEARNED = {}    # renommages appris (learned_renames), appliqués aux jetons de RF


def identifiers(base):
    """Tous les identifiants des sources (src, include) d'un jeu."""
    if base not in _IDENTS:
        found = set()
        for top in ('src', 'include'):
            for d, _, fs in os.walk(os.path.join(base, top)):
                for f in fs:
                    if f.endswith(('.c', '.h')):
                        found.update(re.findall(r'[A-Za-z_]\w*', read(os.path.join(d, f))))
        _IDENTS[base] = found
    return _IDENTS[base]


def learned_renames(items, rename, cache):
    """Les renommages entre les deux décomps, appris sur les différences : un nom qui n'existe que dans RF, remplacé au
    même endroit par un nom qui n'existe que dans la fusion (InitWalkSlower = InitWalkSlow). Le plus fréquent gagne."""
    rf_ids, fu_ids = identifiers(RF), identifiers(ROOT)
    seen = {}
    for rf_file, name, _ in items:
        result = compare(rf_file, name, rename, cache)
        if result is None:
            continue
        ops, ta, tb = result
        for tag, i1, i2, j1, j2 in ops:
            if tag == 'replace' and i2 - i1 == j2 - j1:
                for x, y in zip(ta[i1:i2], tb[j1:j2]):
                    if re.match(r'[A-Za-z_]\w*$', x) and re.match(r'[A-Za-z_]\w*$', y) \
                            and x not in fu_ids and y not in rf_ids and 'g' + x not in fu_ids and 's' + x not in fu_ids:
                        seen.setdefault(x, {}).setdefault(y, 0)
                        seen[x][y] += 1
    return {x: max(ys, key=ys.get) for x, ys in seen.items()}


_FUSION_INDEX = {}


def fusion_files_of(name):
    """Les fichiers de la fusion qui définissent name (la fusion a déplacé ou copié des fonctions)."""
    if not _FUSION_INDEX:
        src = os.path.join(ROOT, 'src')
        for f in sorted(os.listdir(src)):
            if f.endswith('.c'):
                text = read(os.path.join(src, f))
                # (les paramètres peuvent contenir des parenthèses : void (*callback)(struct Sprite *) ; la fin de
                # la signature est cherchée sans être consommée, pour ne pas avaler la définition suivante)
                for m in re.finditer(r'^[\w \t\*]*?\b(\w+)\s*\((?=[^;{]*\)\s*\{)', text, re.M):
                    _FUSION_INDEX.setdefault(m.group(1), []).append(f)
    return _FUSION_INDEX.get(name, [])


def fusion_candidates(rf_file, name):
    """Les (nom, fichier) de la fusion à essayer, dans l'ordre : une variante Kanto (Kanto_X, KantoX, X_Kanto ; comme
    tools/cartographie.py), une copie de même nom dans un kanto_*.c, celle du fichier de même nom, puis les autres
    (la première dont le corps se lit gagne)."""
    out = []
    for variant in ('Kanto_' + name, 'Kanto' + name, name + '_Kanto', 'Kanto' + name[:1].upper() + name[1:]):
        out += [(variant, f) for f in fusion_files_of(variant)]
    files = fusion_files_of(name)
    out += [(name, f) for f in files if f.startswith('kanto_')]
    out += [(name, f) for f in files if f == rf_file]
    out += [(name, f) for f in files if not f.startswith('kanto_') and f != rf_file]
    return out


def compare(rf_file, name, rename, cache):
    """None si un corps manque, sinon la liste des différences (opcodes) et les deux suites de jetons."""
    if rf_file not in cache:
        rf_text = strip_comments(read(os.path.join(RF, 'src', rf_file)))
        cache[rf_file] = (rf_text, macros(rf_text), parse_constants(rf_text, {}, constants(RF)))
    rf_text, rf_defs, rf_local = cache[rf_file]
    a, b = body(rf_text, name), None
    for fu_name, fu_file in fusion_candidates(rf_file, name):
        key = ('fusion', fu_file)
        if key not in cache:
            text = strip_comments(read(os.path.join(ROOT, 'src', fu_file)))
            cache[key] = (text, macros(text), parse_constants(text, {}, constants(ROOT)))
        fu_text, fu_defs, fu_local = cache[key]
        b = body(fu_text, fu_name)
        if b is not None:
            break
    if a is None or b is None:
        return None
    ta = normalize(tokens(a, rf_defs, rename), {**constants(RF), **rf_local}, params(rf_text, name))
    ta = [LEARNED.get(t, t) for t in ta]
    tb = normalize(kanto_names(tokens(b, fu_defs, {})), {**constants(ROOT), **fu_local}, params(fu_text, fu_name))
    ops = [op for op in difflib.SequenceMatcher(None, ta, tb, autojunk=False).get_opcodes() if op[0] != 'equal']
    return ops, ta, tb


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    everything = '--tout' in sys.argv
    summary_only = '--resume' in sys.argv
    rename = equivalences()
    known = classes()
    cache, per_file, to_read = {}, {}, []
    LEARNED.update(learned_renames(divergent(), rename, cache))
    for rf_file, name, kanto in divergent():
        if args and rf_file not in args:
            continue
        stats = per_file.setdefault(rf_file, {'total': 0, 'meme': 0, 'famille': 0, 'classees': 0, 'a_lire': 0,
                                              'absent': 0})
        stats['total'] += 1
        result = compare(rf_file, name, rename, cache)
        if result is None:
            stats['absent'] += 1
            if name not in known:
                to_read.append((rf_file, name, kanto, 'corps introuvable dans la fusion (déplacé ?)', []))
            continue
        ops, ta, tb = result
        if not ops:
            stats['meme'] += 1
            continue
        if name in known:
            stats['classees'] += 1
            continue
        markers = sorted({t for t in ta if KANTO_MARKERS.match(t)} - set(tb))
        family = next((rule for rule in FAMILY_RULES if re.search(rule[0], rf_file)), None)
        if family and not markers:
            stats['famille'] += 1
            continue
        stats['a_lire'] += 1
        samples = []
        for tag, i1, i2, j1, j2 in ops[:None if everything else 4]:
            ctx = ' '.join(ta[max(0, i1 - 3):i1])
            samples.append(f'… {ctx} | RF « {" ".join(ta[i1:i2])[:120]} » / fusion « {" ".join(tb[j1:j2])[:120]} »')
        to_read.append((rf_file, name, kanto, f'{len(ops)} différence(s)'
                        + (f" ; marqueurs de RF absents de la fusion : {', '.join(markers)}" if markers else ''),
                        samples))

    lines = ['# Tri des fonctions divergentes (RF / fusion)', '',
             '> Généré par `tools/carto_divergentes.py` — ne pas éditer à la main. Classement : `tools/carto_divergentes.txt`.',
             '', 'Règles de famille (`FAMILY_RULES`, sauf marqueur propre à Kanto dans le corps de RF) :', '']
    lines += [f'- `{pattern}` : {category} — {proof}' for pattern, category, proof in FAMILY_RULES]
    lines += ['', '| Fichier RF | Divergentes | Même code une fois normalisé | Par règle de famille | Classées | À lire | '
              'Corps introuvable |', '|---|---|---|---|---|---|---|']
    tot = {'total': 0, 'meme': 0, 'famille': 0, 'classees': 0, 'a_lire': 0, 'absent': 0}
    for f, s in sorted(per_file.items(), key=lambda kv: -kv[1]['a_lire']):
        lines.append(f"| {f} | {s['total']} | {s['meme']} | {s['famille']} | {s['classees']} | {s['a_lire']} | "
                     f"{s['absent']} |")
        for k in tot:
            tot[k] += s[k]
    lines.append(f"| **total** | {tot['total']} | {tot['meme']} | {tot['famille']} | {tot['classees']} | "
                 f"{tot['a_lire']} | {tot['absent']} |")
    lines += ['', '## À lire', '']
    for rf_file, name, kanto, what, samples in to_read:
        lines.append(f"- `{rf_file}` **{name}**{' ✓' if kanto else ''} : {what}")
    if not args:
        with open(OUT, 'w', encoding='utf-8') as out:
            out.write('\n'.join(lines) + '\n')
    print(f"{tot['total']} divergentes : {tot['meme']} même code une fois normalisé, {tot['famille']} par règle de "
          f"famille, {tot['classees']} classées, {tot['a_lire']} à lire, {tot['absent']} corps introuvable")
    if summary_only:
        for f, s in sorted(per_file.items(), key=lambda kv: -kv[1]['a_lire']):
            print(f"  {f} : {s['a_lire']} à lire / {s['total']}")
        return
    for rf_file, name, kanto, what, samples in to_read:
        print(f"{rf_file} {name}{' ✓' if kanto else ''} : {what}")
        for s in samples:
            print('    ' + s)


if __name__ == '__main__':
    main()
