"""Correspondance des noms Rouge Feu -> Émeraude pour l'import de Kanto.

Règles :
  FLAG_X  : temporaires (< 0x20) et spéciaux (>= 0x4000) gardent le nom d'Émeraude ;
            SHARED_FLAGS aussi (même sens dans les deux jeux) ; tous les autres deviennent
            FLAG_KANTO_X = KANTO_FLAGS_START + valeur RF (bloc de sauvegarde Kanto).
  VAR_X   : temporaires/graphismes (< 0x4020) et spéciales (>= 0x8000) gardent le nom ;
            les autres deviennent VAR_KANTO_X = KANTO_VARS_START + (valeur RF - 0x4000).
  OBJ_EVENT_GFX_X -> OBJ_EVENT_GFX_KANTO_X ; LOCALID_X -> LOCALID_KANTO_X (sauf PLAYER/CAMERA).
"""
import re, subprocess

# Flags RF qui ont le même sens dans Émeraude : le joueur les a déjà en arrivant de Hoenn.
SHARED_FLAGS = {
    'FLAG_SYS_POKEMON_GET', 'FLAG_SYS_POKEDEX_GET', 'FLAG_SYS_B_DASH',
}
# Mêmes flags/variables spéciaux, nommés autrement dans Émeraude
ALIASES = {
    'FLAG_DONT_SHOW_MAP_NAME_POPUP': 'FLAG_HIDE_MAP_NAME_POPUP',
    'VAR_0x8014': 'VAR_UNUSED_0x8014',
}
KEEP_LOCALIDS = {'LOCALID_PLAYER', 'LOCALID_CAMERA', 'LOCALID_NONE'}


def cpp_constants(root, header, prefix):
    """Valeurs des #define d'un en-tête (expressions évaluées), via le préprocesseur C."""
    out = subprocess.run(['cpp', '-dM', '-I', f'{root}/include', f'{root}/include/{header}'],
                         capture_output=True, text=True, check=True).stdout
    raw = dict(re.findall(r'#define (\w+) (.*)', out))
    vals = {}

    def ev(name, depth=0):
        if name in vals:
            return vals[name]
        expr = raw[name].split('//')[0]
        expr = re.sub(r'\b[A-Za-z_]\w*\b', lambda m: str(ev(m.group(0), depth + 1)) if m.group(0) in raw else m.group(0), expr)
        vals[name] = int(eval(expr))
        return vals[name]

    res = {}
    for n in raw:
        if n.startswith(prefix):
            try:
                res[n] = ev(n)
            except Exception:
                pass
    return res


class Names:
    def __init__(self, fr, em):
        self.fr_flags = cpp_constants(fr, 'constants/flags.h', 'FLAG_')
        self.em_flags = cpp_constants(em, 'constants/flags.h', 'FLAG_')
        self.fr_vars = cpp_constants(fr, 'constants/vars.h', 'VAR_')
        self.em_vars = cpp_constants(em, 'constants/vars.h', 'VAR_')
        self.problems = {}

    def problem(self, kind, what):
        self.problems.setdefault(kind, set()).add(what)

    def flag(self, name):
        if name in ALIASES:
            return ALIASES[name]
        v = self.fr_flags.get(name)
        if v is None:
            self.problem('flag RF inconnu', name)
            return name
        if v < 0x20 or v >= 0x4000 or name in SHARED_FLAGS:
            if name not in self.em_flags:
                self.problem('flag partagé absent d\'Émeraude', name)
            return name
        return 'FLAG_KANTO_' + name[len('FLAG_'):]

    def var(self, name):
        if name in ALIASES:
            return ALIASES[name]
        v = self.fr_vars.get(name)
        if v is None:
            self.problem('variable RF inconnue', name)
            return name
        if v < 0x4020 or v >= 0x8000:
            if name not in self.em_vars:
                self.problem('variable partagée absente d\'Émeraude', name)
            return name
        return 'VAR_KANTO_' + name[len('VAR_'):]

    def gfx(self, name):
        return 'OBJ_EVENT_GFX_KANTO_' + name[len('OBJ_EVENT_GFX_'):]

    def localid(self, name):
        return name if name in KEEP_LOCALIDS else 'LOCALID_KANTO_' + name[len('LOCALID_'):]

    def kanto_header(self):
        """include/constants/kanto_flags_vars.h : tous les flags/variables RF de la plage Kanto."""
        lines = ['// Généré par tools/kanto — flags et variables de Rouge Feu (bloc de sauvegarde Kanto).',
                 '#ifndef GUARD_CONSTANTS_KANTO_FLAGS_VARS_H', '#define GUARD_CONSTANTS_KANTO_FLAGS_VARS_H', '']
        seen = set()
        for n, v in sorted(self.fr_flags.items(), key=lambda x: x[1]):
            k = self.flag(n)
            if k.startswith('FLAG_KANTO_') and k not in seen and v < 0x900:
                lines.append(f'#define {k} (KANTO_FLAGS_START + 0x{v:X})')
                seen.add(k)
        lines.append('')
        for n, v in sorted(self.fr_vars.items(), key=lambda x: x[1]):
            k = self.var(n)
            if k.startswith('VAR_KANTO_') and k not in seen and 0x4000 <= v < 0x4100:
                lines.append(f'#define {k} (KANTO_VARS_START + 0x{v - 0x4000:X})')
                seen.add(k)
        lines += ['', '#endif', '']
        return '\n'.join(lines)
