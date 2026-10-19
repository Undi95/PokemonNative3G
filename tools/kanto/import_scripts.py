"""Conversion des scripts et textes de Rouge Feu pour le moteur d'Émeraude.

Appelé par import_kanto.py (qui fournit les renommages de cartes). Reprend la partie
« scripts » de data/event_scripts.s de RF (scripts des cartes, scripts communs, textes
français) et l'écrit sous data/kanto/, avec :
  - les labels RF en collision avec un label d'Émeraude préfixés Kanto_ (et les labels
    des cartes renommées suivent la carte : VictoryRoad_1F_X -> KantoVictoryRoad_1F_X) ;
  - les constantes passées par kanto_names.Names (flags, variables, sprites, local ids) ;
  - les cartes renommées, les musiques RF -> MUS_RG_* ;
  - les spécificités 64 bits du port : `.4byte label` -> ptrvalue, `.align 2` -> ptr_align,
    commentaires `@` -> /* */.
"""
import os, re

from kanto_names import Names

INCLUDE_RE = re.compile(r'^\s*\.include\s+"([^"]+)"')
LABEL_RE = re.compile(r'^\s*(\w+)::?', re.M)


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, text):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)


def em_unit_labels(em):
    """Labels définis dans l'unité event_scripts.s d'Émeraude (hors data/kanto/)."""
    labels, seen = set(), set()

    def walk(path):
        if path in seen or path.startswith('data/kanto/') or not os.path.exists(f'{em}/{path}'):
            return
        seen.add(path)
        for line in read(f'{em}/{path}').splitlines():
            m = INCLUDE_RE.match(line)
            if m:
                walk(m.group(1))
                continue
            m = re.match(r'^\s*(\w+)::?(?!\S)', line)
            if m:
                labels.add(m.group(1))
    walk('data/event_scripts.s')
    return labels


class ScriptConverter:
    def __init__(self, imp):
        self.imp = imp
        self.fr, self.em = imp.fr, imp.em
        # les en-têtes d'Émeraude incluent nos fichiers générés : versions vides au premier passage
        for h in ('kanto_flags_vars.h', 'kanto_trainers.h'):
            if not os.path.exists(f'{self.em}/include/constants/{h}'):
                write(f'{self.em}/include/constants/{h}', '// (vide : généré par tools/kanto)\n')
        self.names = Names(self.fr, self.em)
        self.labels_rename = {}
        self.missing = {}

    def note(self, kind, what):
        self.missing.setdefault(kind, set()).add(what)

    # --- lecture de la partie scripts de event_scripts.s ----------------------------
    def collect(self):
        text = read(f'{self.fr}/data/event_scripts.s')
        tail = text[text.index('gStdScriptsEnd::') + len('gStdScriptsEnd::'):]
        skip_dirs = tuple(f'data/maps/{m}/' for m in self.imp.skip)
        master, files = [], []
        for line in tail.splitlines():
            m = INCLUDE_RE.match(line)
            if m:
                path = m.group(1)
                if path.startswith(skip_dirs):
                    continue
                files.append(path)
                master.append(f'\t.include "data/kanto/{path}"')
            else:
                master.append(line)
        self.master = '\n'.join(master) + '\n'
        self.files = {p: read(f'{self.fr}/{p}') for p in files}

    # --- renommage des labels ---------------------------------------------------------
    def plan_labels(self):
        fr_labels = set(LABEL_RE.findall(self.master))
        for t in self.files.values():
            fr_labels |= set(LABEL_RE.findall(t))
        em_labels = em_unit_labels(self.em)
        prefixes = sorted(self.imp.map_rename.items(), key=lambda kv: -len(kv[0]))
        for lab in fr_labels:
            new = lab
            for old_map, new_map in prefixes:
                if lab.startswith(old_map + '_'):
                    new = new_map + lab[len(old_map):]
                    break
            if new in em_labels:
                new = 'Kanto_' + new
            if new != lab:
                self.labels_rename[lab] = new
        self.fr_labels = fr_labels

    def label(self, name):
        return self.labels_rename.get(name, name)

    # --- transformation d'un texte --------------------------------------------------
    def token(self, m):
        t = m.group(0)
        n = self.names
        if t in self.labels_rename:
            return self.labels_rename[t]
        if t.startswith('FLAG_'):
            return n.flag(t)
        if t.startswith('VAR_'):
            return n.var(t)
        if t.startswith('OBJ_EVENT_GFX_'):
            return t if t.startswith('OBJ_EVENT_GFX_VAR_') else n.gfx(t)
        if t.startswith('LOCALID_'):
            return n.localid(t)
        if t.startswith('MAP_'):
            return self.imp.id_rename.get(t, t)
        if t.startswith('MUS_'):
            return self.imp.music(t)
        if t.startswith('TRAINER_') and t not in KEEP_TRAINER_TOKENS:
            self.note('dresseurs (TRAINER_KANTO_* provisoires)', t)
            return 'TRAINER_KANTO_' + t[len('TRAINER_'):]
        return t

    def transform(self, text):
        out = []
        for line in text.splitlines():
            s = line.lstrip()
            if s.startswith('.string') or s.startswith('.braille'):
                out.append(line)
                continue
            code, comment = line, ''
            ci = line.find('@')
            if ci >= 0:
                code, comment = line[:ci], line[ci + 1:].strip()
            code = re.sub(r'\b[A-Za-z_]\w*\b', self.token, code)
            m = re.match(r'^(\s*)\.4byte\s+([A-Za-z_]\w*)\s*$', code)
            if m and m.group(2) in self.fr_labels | set(self.labels_rename.values()):
                code = f'{m.group(1)}ptrvalue {m.group(2)}'
            code = re.sub(r'^(\s*)\.align\s+2\s*$', r'\1ptr_align', code)
            if comment:
                code = f'{code}/* {comment} */' if code.strip() else f'/* {comment} */'
            out.append(code)
        return '\n'.join(out) + '\n'

    def run(self):
        self.collect()
        self.plan_labels()
        for path, text in self.files.items():
            write(f'{self.em}/data/kanto/{path}', self.transform(text))
        header = ('/* Scripts et textes de Kanto, convertis depuis data/event_scripts.s de Rouge Feu\n'
                  '   par tools/kanto/import_scripts.py — ne pas modifier à la main. */\n')
        write(f'{self.em}/data/kanto/scripts.inc', header + self.transform(self.master))
        write(f'{self.em}/include/constants/kanto_flags_vars.h', self.names.kanto_header())
        # Dresseurs : PROVISOIRE (TRAINER_NONE) en attendant l'import des dresseurs de RF
        trainers = sorted(self.missing.get('dresseurs (TRAINER_KANTO_* provisoires)', ()))
        write(f'{self.em}/include/constants/kanto_trainers.h',
              '// Généré par tools/kanto/import_scripts.py — PROVISOIRE : dresseurs RF pas encore importés.\n'
              '#ifndef GUARD_CONSTANTS_KANTO_TRAINERS_H\n#define GUARD_CONSTANTS_KANTO_TRAINERS_H\n\n'
              + ''.join(f'#define {"TRAINER_KANTO_" + t[len("TRAINER_"):]} TRAINER_NONE\n' for t in trainers)
              + '\n#endif\n')
        print(f'scripts : {len(self.files)} fichiers, {len(self.labels_rename)} labels renommés')
        for k, v in list(self.names.problems.items()) + list(self.missing.items()):
            print(f'{k} ({len(v)}) : {sorted(v)[:12]}{" …" if len(v) > 12 else ""}')


# Constantes TRAINER_* qui ne sont pas des dresseurs
KEEP_TRAINER_TOKENS = {
    'TRAINER_TYPE_NONE', 'TRAINER_TYPE_NORMAL', 'TRAINER_TYPE_SEE_ALL_DIRECTIONS', 'TRAINER_TYPE_BURIED',
    'TRAINER_BATTLE_SINGLE', 'TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC', 'TRAINER_BATTLE_CONTINUE_SCRIPT',
    'TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT', 'TRAINER_BATTLE_DOUBLE', 'TRAINER_BATTLE_REMATCH',
    'TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE', 'TRAINER_BATTLE_REMATCH_DOUBLE',
    'TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC', 'TRAINER_BATTLE_PYRAMID', 'TRAINER_BATTLE_SET_TRAINER_A',
    'TRAINER_BATTLE_SET_TRAINER_B', 'TRAINER_BATTLE_HILL', 'TRAINER_BATTLE_EARLY_RIVAL', 'TRAINER_NONE',
}
