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
import json, os, re, subprocess

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
        FR_TRAINER_IDS.update(re.findall(r'#define (TRAINER_\w+)\s+\d+',
                                         read(f'{self.fr}/include/constants/opponents.h')))
        self.names = Names(self.fr, self.em)
        self.labels_rename = {}
        self.missing = {}

    def note(self, kind, what):
        self.missing.setdefault(kind, set()).add(what)

    # --- lecture de la partie scripts de event_scripts.s ----------------------------
    def collect(self):
        self.prepare_fr_headers()
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
        # noms définis localement par .equ / .set : jamais renommés
        self.local_names = set()
        for t in [self.master] + list(self.files.values()):
            self.local_names |= set(re.findall(r'^\s*\.(?:equ|set)\s+(\w+)\s*,', t, re.M))
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
        if t in self.local_names:
            return t
        if t in self.labels_rename:
            return self.labels_rename[t]
        if t in self.const_rename:
            return self.const_rename[t]
        if t.startswith('MULTICHOICE_') or t.startswith('INGAME_TRADE_'):
            return 'KANTO_' + t
        if t.startswith('STDSTRING_') and t not in self.em_std:
            return 'STDSTRING_KANTO_' + t[len('STDSTRING_'):]
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
        if t in FR_TRAINER_IDS:
            return 'TRAINER_KANTO_' + t[len('TRAINER_'):]
        return t

    def transform(self, text):
        out = []
        for line in text.splitlines():
            s = line.lstrip()
            if s.startswith('.string') or s.startswith('.braille'):
                # musiques citées dans le texte ({PLAY_BGM MUS_X}) : même correspondance
                out.append(re.sub(r'\{(PLAY_BGM|PLAY_FANFARE) (MUS_\w+)\}',
                                  lambda m: '{' + m.group(1) + ' ' + self.imp.music(m.group(2)) + '}', line))
                continue
            code, comment = line, ''
            ci = line.find('@')
            if ci >= 0:
                code, comment = line[:ci], line[ci + 1:].strip()
            code = re.sub(r'\b[A-Za-z_]\w*\b', self.token, code)
            # l'assembleur x86 coupe les arguments de macro aux espaces : pas d'espaces dans ( )
            code = re.sub(r'\(([^()]*)\)', lambda m: '(' + m.group(1).replace(' ', '') + ')', code)
            code = re.sub(r'\)\s+([-+*/|&])\s+(?=[\w(])', r')\1', code)
            m = re.match(r'^(\s*)\.4byte\s+([A-Za-z_]\w*)\s*$', code)
            if m and m.group(2) in self.fr_labels | set(self.labels_rename.values()):
                code = f'{m.group(1)}ptrvalue {m.group(2)}'
            code = re.sub(r'^(\s*)\.align\s+2\s*$', r'\1ptr_align', code)
            # RF : virgule oubliée (« call_if_not_defeated TRAINER_X Label »)
            code = re.sub(r'^(\s*call_if_(?:not_)?defeated\s+[^\s,]+)\s+(\w+)\s*$', r'\1, \2', code)
            # RF : « hideobjectat id, 0 » = carte courante ; Émeraude exige une carte
            code = re.sub(r'^(\s*(?:hide|show)objectat\s+[^,]+,\s*)0\s*$', r'\1MAP_UNDEFINED', code)
            if comment:
                code = f'{code}/* {comment} */' if code.strip() else f'/* {comment} */'
            out.append(code)
        return '\n'.join(out) + '\n'

    # --- en-têtes de constantes propres à RF -------------------------------------------
    def prepare_fr_headers(self):
        """Copie les en-têtes RF absents d'Émeraude dans include/constants/kanto/ ; une constante
        qui existe aussi dans Émeraude (avec un autre sens) y est préfixée KANTO_."""
        em_defs = set()
        for h in os.listdir(f'{self.em}/include/constants'):
            if h.endswith('.h'):
                em_defs |= set(re.findall(r'#define\s+([A-Za-z_]\w*)', read(f'{self.em}/include/constants/{h}')))
        self.const_rename = {}
        for h in FR_ONLY_HEADERS:
            text = read(f'{self.fr}/include/constants/{h}')
            if h == 'menu.h':  # menus et chaînes : tools/kanto/gen_script_menu.py
                text = re.sub(r'^#define (MULTICHOICE|STDSTRING)_\w+.*\n', '', text, flags=re.M)
            names = set(re.findall(r'#define\s+([A-Za-z_]\w*)', text)) | set(re.findall(r'^\s+([A-Z][A-Z0-9_]+)\s*[,=]', text, re.M))
            for n in names:
                if n in em_defs and not n.startswith('GUARD_'):
                    self.const_rename[n] = 'KANTO_' + n
            text = re.sub(r'\b[A-Za-z_]\w*\b', lambda m: self.const_rename.get(m.group(0), m.group(0)), text)
            text = text.replace('GUARD_CONSTANTS_', 'GUARD_CONSTANTS_KANTO_').replace('GUARD_METATILE_LABELS_H', 'GUARD_KANTO_METATILE_LABELS_H')
            write(f'{self.em}/include/constants/kanto/{h}', '// Copié de Rouge Feu par tools/kanto/import_scripts.py\n' + text)
        tutors = re.findall(r'^#define MOVETUTOR_\w+\s+\d+', read(f'{self.fr}/include/constants/moves.h'), re.M)
        write(f'{self.em}/include/constants/kanto/move_tutors.h', '// Copié de Rouge Feu\n' + '\n'.join(tutors) + '\n// Poche de CT de RF = poche CT/CS d\'Émeraude\n#define POCKET_TM_CASE POCKET_TM_HM\n#define POCKET_BERRY_POUCH POCKET_BERRIES\n')
        # lieux de soin de RF : ajoutés à la fin de la table d'Émeraude (sans le PNJ de réanimation)
        heal = json.load(open(f'{self.fr}/src/data/heal_locations.json', encoding='utf-8'))['heal_locations']
        hp = f'{self.em}/src/data/heal_locations.json'
        hj = json.load(open(hp, encoding='utf-8'))
        rf_ids = {h['id'] for h in heal}
        hj['heal_locations'] = [h for h in hj['heal_locations'] if h['id'] not in rf_ids] + \
            [{k: v for k, v in h.items() if k != 'respawn_npc'} for h in heal]
        with open(hp, 'w', encoding='utf-8', newline='\n') as f:
            json.dump(hj, f, indent=2, ensure_ascii=False)
            f.write('\n')
        # alias RF -> Émeraude utilisés par les scripts de Kanto
        write(f'{self.em}/include/constants/kanto/script_aliases.h', '// Alias RF -> Émeraude (tools/kanto/import_scripts.py)\n'
              '#define NPC_TEXT_COLOR_MALE 0\n#define NPC_TEXT_COLOR_FEMALE 1\n#define NPC_TEXT_COLOR_MON 2\n#define NPC_TEXT_COLOR_NEUTRAL 3\n'
              '#define SE_RS_DOOR SE_DOOR\n#define SE_RS_SHOP SE_SHOP\n'
              '#define MOVEMENT_TYPE_WANDER_AROUND_SLOWER MOVEMENT_TYPE_WANDER_AROUND\n'
              '#define STEP_CB_ICE STEP_CB_DUMMY // TODO Kanto : glace de la Grotte Glaciale\n')
        em_std = set(re.findall(r'#define (STDSTRING_\w+)', read(f'{self.em}/include/constants/script_menu.h')))
        self.em_std = em_std

    # --- specials de RF ------------------------------------------------------------------
    def write_specials(self):
        """data/kanto/kanto_specials.inc : def_special des specials RF absents d'Émeraude.
        src/kanto_specials_stubs.c : fonctions PROVISOIRES pour ceux qui n'existent pas en C
        dans Émeraude (à remplacer par le code RF porté)."""
        fr_sp = re.findall(r'def_special\s+(\w+)', read(f'{self.fr}/data/specials.inc'))
        em_sp = set(re.findall(r'def_special\s+(\w+)', read(f'{self.em}/data/specials.inc')))
        new = [n for n in dict.fromkeys(fr_sp) if n not in em_sp]
        em_c = ''
        for d in ('src',):
            for f in os.listdir(f'{self.em}/{d}'):
                if f.endswith('.c') and f != 'kanto_specials_stubs.c':
                    em_c += read(f'{self.em}/{d}/{f}')
        defined = set(re.findall(r'^(?!static\b)[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{]*\)\s*\{', em_c, re.M))
        stubs = [n for n in new if n not in defined]
        write(f'{self.em}/data/kanto/kanto_specials.inc',
              '/* Specials de Rouge Feu (tools/kanto/import_scripts.py) */\n'
              + ''.join(f'\tdef_special {n}\n' for n in new))
        c = ['// Généré par tools/kanto/import_scripts.py — PROVISOIRE : specials de Rouge Feu',
             '// pas encore portés. Chaque appel est signalé dans la console.', '#include "global.h"', '',
             '#ifdef PORTABLE', '#include <stdio.h>',
             'static void KantoSpecialStub(const char *name) { fprintf(stderr, "[Kanto] special RF non porte : %s\\n", name); }',
             '#else', 'static void KantoSpecialStub(const char *name) { }', '#endif', '']
        c += [f'u16 {n}(void) {{ KantoSpecialStub("{n}"); return 0; }}' for n in stubs]
        write(f'{self.em}/src/kanto_specials_stubs.c', '\n'.join(c) + '\n')
        print(f'specials RF : {len(new)} ajoutés, dont {len(stubs)} provisoires (src/kanto_specials_stubs.c)')

    def run(self):
        self.collect()
        self.plan_labels()
        for path, text in self.files.items():
            write(f'{self.em}/data/kanto/{path}', self.transform(text))
        header = ('/* Scripts et textes de Kanto, convertis depuis data/event_scripts.s de Rouge Feu\n'
                  '   par tools/kanto/import_scripts.py — ne pas modifier à la main. */\n')
        master = self.transform(self.master)
        # Kanto vient après Hoenn : le Pokédex est déjà acquis, les exemplaires du labo restent cachés
        master = master.replace('Kanto_EventScript_ResetAllMapFlags::
',
                                'Kanto_EventScript_ResetAllMapFlags::
	setflag FLAG_KANTO_HIDE_POKEDEX
', 1)
        write(f'{self.em}/data/kanto/scripts.inc', header + master)
        write(f'{self.em}/include/constants/kanto_flags_vars.h', self.names.kanto_header())
        self.write_specials()
        # Dresseurs : include/constants/kanto_trainers.h est écrit par tools/kanto/gen_trainers.py
        print(f'scripts : {len(self.files)} fichiers, {len(self.labels_rename)} labels renommés')
        for k, v in list(self.names.problems.items()) + list(self.missing.items()):
            print(f'{k} ({len(v)}) : {sorted(v)[:12]}{" …" if len(v) > 12 else ""}')


# En-têtes de constantes de RF absents d'Émeraude (copiés dans include/constants/kanto/)
FR_ONLY_HEADERS = ['fame_checker.h', 'help_system.h', 'menu.h', 'metatile_labels.h', 'quest_log.h', 'seagallop.h',
                   'trainer_card.h', 'trainer_fan_club.h', 'trainer_tower.h']

# Dresseurs de RF (les autres constantes TRAINER_* gardent leur nom)
FR_TRAINER_IDS = set()


# Constantes TRAINER_* qui ne sont pas des dresseurs
KEEP_TRAINER_TOKENS = {
    'TRAINER_TYPE_NONE', 'TRAINER_TYPE_NORMAL', 'TRAINER_TYPE_SEE_ALL_DIRECTIONS', 'TRAINER_TYPE_BURIED',
    'TRAINER_BATTLE_SINGLE', 'TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC', 'TRAINER_BATTLE_CONTINUE_SCRIPT',
    'TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT', 'TRAINER_BATTLE_DOUBLE', 'TRAINER_BATTLE_REMATCH',
    'TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE', 'TRAINER_BATTLE_REMATCH_DOUBLE',
    'TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC', 'TRAINER_BATTLE_PYRAMID', 'TRAINER_BATTLE_SET_TRAINER_A',
    'TRAINER_BATTLE_SET_TRAINER_B', 'TRAINER_BATTLE_HILL', 'TRAINER_BATTLE_EARLY_RIVAL', 'TRAINER_NONE',
}
