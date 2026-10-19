#!/usr/bin/env python3
"""Importe tous les sprites de PNJ (object events) de Rouge Feu.

Usage : gen_objects.py FR_DIR EM_DIR

Les fichiers src/data/object_events/*.h de RF sont repris tels quels, chaque symbole
qu'ils définissent étant préfixé « Kanto » (gObjectEventPic_X -> gKantoObjectEventPic_X…).
Produit :
  include/constants/kanto_event_objects.h   OBJ_EVENT_GFX_KANTO_X = KANTO_OBJ_EVENT_GFX_START + id RF
  src/data/object_events/kanto_object_events.h          images, tables, animations, infos, pointeurs
  src/data/object_events/kanto_object_event_palettes.h  entrées de sObjectEventSpritePalettes
  graphics/object_events/kanto/...                       images et palettes copiées de RF
Les identifiants sont sur 16 bits (graphicsId), donc sans collision avec Émeraude.
"""
import os, re, shutil, sys

fr, em = sys.argv[1], sys.argv[2]
OBJ = 'src/data/object_events'
FILES = ['object_event_graphics.h', 'object_event_pic_tables.h', 'object_event_anims.h',
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


def kantoize(t):
    t = re.sub(r'\b([gs])([A-Z]\w*)\b', lambda m: m.group(1) + 'Kanto' + m.group(2) if m.group(0) in defined else m.group(0), t)
    t = re.sub(r'\bOBJ_EVENT_PAL_TAG_(?!NONE\b)(\w+)', r'OBJ_EVENT_PAL_TAG_KANTO_\1', t)
    return t


def gfx_path(m):
    path = m.group(2)  # graphics/object_events/....4bpp ou .gbapal
    base, ext = os.path.splitext(path)
    src_png = f'{fr}/{base}.png' if ext == '.4bpp' else f'{fr}/{base}.pal'
    rel = base.replace('graphics/object_events/', 'graphics/object_events/kanto/', 1)
    dst = f'{em}/{rel}' + ('.png' if ext == '.4bpp' else '.pal')
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    shutil.copy(src_png, dst)
    if ext == '.4bpp':
        return f'INCGFX_{m.group(1)}("{rel}.png", ".4bpp")'
    return f'INCGFX_{m.group(1)}("{rel}.pal", ".gbapal")'


shutil.rmtree(f'{em}/graphics/object_events/kanto', ignore_errors=True)
out = ['// Généré par tools/kanto/gen_objects.py depuis src/data/object_events/ de Rouge Feu.',
       '// Ne pas modifier à la main.', '']
for f in FILES:
    t = kantoize(texts[f])
    t = re.sub(r'INCBIN_(U8|U16|U32)\("(graphics/object_events/[^"]+\.(?:4bpp|gbapal))"\)', gfx_path, t)
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
