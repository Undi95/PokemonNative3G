#!/usr/bin/env python3
"""Importe tous les sprites de PNJ (object events) de Rouge Feu.

Usage : gen_objects.py FR_DIR EM_DIR

Les fichiers src/data/object_events/*.h de RF sont repris tels quels, chaque symbole
qu'ils définissent étant préfixé « Kanto » (gObjectEventPic_X -> gKantoObjectEventPic_X…).
Produit :
  include/constants/kanto_event_objects.h   OBJ_EVENT_GFX_KANTO_X = KANTO_OBJ_EVENT_GFX_START + id RF
  src/data/object_events/kanto_object_events.h          images, tables, animations, infos, pointeurs
  src/data/object_events/kanto_object_event_palettes.h  entrées de sObjectEventSpritePalettes
  graphics/kanto/...                                     images et palettes copiées de RF
Les identifiants sont sur 16 bits (graphicsId), donc sans collision avec Émeraude.
"""
import os, re, shutil, sys

fr, em = sys.argv[1], sys.argv[2]
OBJ = 'src/data/object_events'
FILES = ['base_oam.h', 'object_event_graphics.h', 'object_event_pic_tables.h', 'object_event_anims.h',
         'object_event_subsprites.h', 'object_event_graphics_info.h']
KANTO_PAL_TAG_BASE = 0x1180


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, text):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)


# 1. identifiants des sprites RF
gfx_ids = {}
for line in read(f'{fr}/include/constants/event_objects.h').splitlines():
    m = re.match(r'#define (OBJ_EVENT_GFX_\w+)\s+(\d+)', line)
    if m and not m.group(1).startswith('OBJ_EVENT_GFX_VAR'):
        gfx_ids[m.group(1)] = int(m.group(2))
num = max(gfx_ids.values()) + 1

# 2. tags de palette RF (définis dans event_object_movement.c)
fr_eom = read(f'{fr}/src/event_object_movement.c')
pal_tags = {n: int(v, 16) for n, v in re.findall(r'#define (OBJ_EVENT_PAL_TAG_\w+)\s+(0x[0-9A-Fa-f]+)', fr_eom)}
pal_tags.pop('OBJ_EVENT_PAL_TAG_NONE')

# 3. fichiers de données RF, symboles préfixés
texts = {f: read(f'{fr}/{OBJ}/{f}') for f in FILES}
defined = set()
for t in texts.values():
    defined |= set(re.findall(r'\b([gs][A-Z]\w*)\s*(?:\[[^\]]*\])*\s*=', t))
    defined |= set(re.findall(r'^(?:static )?const [^=;]*?\b([gs][A-Z]\w*)\s*\[', t, re.M))


# Constantes d'animation (ANIM_*) de RF : celles absentes d'Émeraude sont définies avec la
# valeur RF, celles qui existent avec une autre valeur sont renommées KANTO_ANIM_*.
def anim_consts(path):
    vals = {}
    for n, expr in re.findall(r'#define (ANIM_\w+)\s+(.+)', read(path)):
        expr = expr.split('//')[0].strip()
        try:
            vals[n] = eval(expr.replace('ANIM_STD_COUNT', str(vals.get('ANIM_STD_COUNT', 20))))
        except Exception:
            pass
    return vals
fr_anims = anim_consts(f'{fr}/include/constants/event_object_movement.h')
em_anims = anim_consts(f'{em}/include/constants/event_object_movement.h')
anim_rename = {n for n in fr_anims if n in em_anims and fr_anims[n] != em_anims[n]}
anim_missing = {n for n in fr_anims if n not in em_anims}


def kantoize(t):
    t = re.sub(r'ANIM_\w+', lambda m: 'KANTO_' + m.group(0) if m.group(0) in anim_rename else m.group(0), t)
    t = re.sub(r'\b([gs])([A-Z]\w*)\b', lambda m: m.group(1) + 'Kanto' + m.group(2) if m.group(0) in defined else m.group(0), t)
    t = re.sub(r'\bOBJ_EVENT_PAL_TAG_(?!NONE\b)(\w+)', r'OBJ_EVENT_PAL_TAG_KANTO_\1', t)
    return t


def gfx_path(m):
    """Copie l'image/palette RF sous graphics/kanto/ et renvoie l'INCGFX équivalent."""
    path = m.group(2)
    base, ext = os.path.splitext(path)
    # une palette .gbapal vient d'un .pal, ou à défaut de la palette du .png
    src_ext = '.png' if ext in ('.4bpp', '.8bpp') or not os.path.exists(f'{fr}/{base}.pal') else '.pal'
    rel = 'graphics/kanto/' + base[len('graphics/'):]
    os.makedirs(os.path.dirname(f'{em}/{rel}'), exist_ok=True)
    shutil.copy(f'{fr}/{base}{src_ext}', f'{em}/{rel}{src_ext}')
    return f'INCGFX_{m.group(1)}("{rel}{src_ext}", "{ext}")'


shutil.rmtree(f'{em}/graphics/kanto', ignore_errors=True)
out = ['// Généré par tools/kanto/gen_objects.py depuis src/data/object_events/ de Rouge Feu.',
       '// Ne pas modifier à la main.', '']
for n in sorted(anim_missing, key=lambda n: fr_anims[n]):
    out.append(f'#define {n} {fr_anims[n]}')
for n in sorted(anim_rename):
    out.append(f'#define KANTO_{n} {fr_anims[n]}')
out.append('')
for f in FILES:
    t = kantoize(texts[f])
    t = re.sub(r'INCBIN_(U8|U16|U32)\("(graphics/[^"]+\.(?:4bpp|8bpp|gbapal))"\)', gfx_path, t)
    out += [f'// ---- {f} ----', t, '']

# 4. table des pointeurs Kanto
ptr = read(f'{fr}/{OBJ}/object_event_graphics_info_pointers.h')
entries = re.findall(r'\[(OBJ_EVENT_GFX_\w+)\]\s*=\s*&(gObjectEventGraphicsInfo_\w+)', ptr)
out.append(f'const struct ObjectEventGraphicsInfo *const gKantoObjectEventGraphicsInfoPointers[NUM_KANTO_OBJ_EVENT_GFX] = {{')
for gid, info in entries:
    out.append(f'    [{gid.replace("OBJ_EVENT_GFX_", "OBJ_EVENT_GFX_KANTO_")} - KANTO_OBJ_EVENT_GFX_START] = &{kantoize(info)},')
out.append('};')
write(f'{em}/{OBJ}/kanto_object_events.h', '\n'.join(out) + '\n')

# 5. palettes : entrées de la table d'Émeraude + tags
pals = re.findall(r'\{\s*(gObjectEventPal_\w+),\s*(OBJ_EVENT_PAL_TAG_\w+)\s*\}', fr_eom)
write(f'{em}/{OBJ}/kanto_object_event_palettes.h',
      '// Généré par tools/kanto/gen_objects.py — palettes des sprites de Rouge Feu.\n'
      + ''.join(f'    {{{kantoize(p)}, {kantoize(t)}}},\n' for p, t in pals if t != 'OBJ_EVENT_PAL_TAG_NONE'))

# 6. constantes
c = ['// Généré par tools/kanto/gen_objects.py — sprites de Rouge Feu (graphicsId 16 bits).',
     '#ifndef GUARD_CONSTANTS_KANTO_EVENT_OBJECTS_H', '#define GUARD_CONSTANTS_KANTO_EVENT_OBJECTS_H', '',
     '#define KANTO_OBJ_EVENT_GFX_START 0x100', '']
for n, v in sorted(gfx_ids.items(), key=lambda x: x[1]):
    c.append(f'#define {n.replace("OBJ_EVENT_GFX_", "OBJ_EVENT_GFX_KANTO_")} (KANTO_OBJ_EVENT_GFX_START + {v})')
c += ['', f'#define NUM_KANTO_OBJ_EVENT_GFX {num}', '']
for n, v in sorted(pal_tags.items(), key=lambda x: x[1]):
    c.append(f'#define {n.replace("OBJ_EVENT_PAL_TAG_", "OBJ_EVENT_PAL_TAG_KANTO_")} 0x{KANTO_PAL_TAG_BASE + v - 0x1100:X}')
c += ['', '#endif', '']
write(f'{em}/include/constants/kanto_event_objects.h', '\n'.join(c))
print(f'{len(entries)} sprites, {len(pals)} palettes, NUM_KANTO_OBJ_EVENT_GFX={num}')
