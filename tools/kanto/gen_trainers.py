#!/usr/bin/env python3
"""Importe les dresseurs de Rouge Feu (version française).

Usage : gen_trainers.py FR_DIR EM_DIR

Les dresseurs, classes et portraits RF sont ajoutés après ceux d'Émeraude :
  TRAINER_KANTO_X       = KANTO_TRAINERS_START + id RF        (gTrainers)
  TRAINER_CLASS_KANTO_X = KANTO_TRAINER_CLASS_START + id RF   (noms, argent)
  TRAINER_PIC_KANTO_X   = KANTO_TRAINER_PIC_START + id RF     (portraits)
Produit :
  include/constants/kanto_trainers.h        constantes
  include/kanto_trainer_graphics.h          déclarations des images
  src/data/graphics/kanto_trainers.h        images (inclus par graphics.c)
  src/data/kanto/trainer_*.h                entrées incluses dans les tables d'Émeraude (data.c, battle_main.c)
  graphics/kanto/trainers/...               images et palettes copiées de RF
"""
import json, os, re, shutil, sys

fr, em = sys.argv[1], sys.argv[2]

# Après les tables d'Émeraude (MAX_TRAINERS_COUNT, TRAINER_CLASS_RS_PROTAG + 1, TRAINER_PIC_RS_MAY + 1)
KANTO_TRAINERS_START = 864
KANTO_TRAINER_CLASS_START = 0x42
KANTO_TRAINER_PIC_START = 93


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, text):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)


def defines(path, prefix):
    return {n: int(v, 0) for n, v in re.findall(rf'#define ({prefix}\w+)\s+(0x[0-9A-Fa-f]+|\d+)\b', read(path))}


trainer_ids = defines(f'{fr}/include/constants/opponents.h', 'TRAINER_')
for k in ('TRAINERS_COUNT', 'MAX_TRAINERS_COUNT'):
    trainer_ids.pop(k, None)
consts = read(f'{fr}/include/constants/trainers.h')
classes = {n: int(v, 0) for n, v in re.findall(r'#define (TRAINER_CLASS_\w+)\s+(0x[0-9A-Fa-f]+|\d+)\b', consts)}
pics = {n: int(v, 0) for n, v in re.findall(r'#define (TRAINER_PIC_\w+)\s+(0x[0-9A-Fa-f]+|\d+)\b', consts)}


def k_trainer(n):
    return 'TRAINER_KANTO_' + n[len('TRAINER_'):]


def k_class(n):
    return 'TRAINER_CLASS_KANTO_' + n[len('TRAINER_CLASS_'):]


def k_pic(n):
    return 'TRAINER_PIC_KANTO_' + n[len('TRAINER_PIC_'):]


def rename_consts(t):
    t = re.sub(r'\bTRAINER_CLASS_(\w+)', lambda m: k_class(m.group(0)) if m.group(0) in classes else m.group(0), t)
    t = re.sub(r'\bTRAINER_PIC_(\w+)', lambda m: k_pic(m.group(0)) if m.group(0) in pics else m.group(0), t)
    return t


# 1. constantes
c = ['// Généré par tools/kanto/gen_trainers.py — dresseurs de Rouge Feu.',
     '#ifndef GUARD_CONSTANTS_KANTO_TRAINERS_H', '#define GUARD_CONSTANTS_KANTO_TRAINERS_H', '',
     '#include "constants/kanto.h"', '',
     f'#define KANTO_TRAINERS_START {KANTO_TRAINERS_START} // MAX_TRAINERS_COUNT d\'Émeraude',
     f'#define KANTO_TRAINER_CLASS_START {KANTO_TRAINER_CLASS_START}',
     f'#define KANTO_TRAINER_PIC_START {KANTO_TRAINER_PIC_START}',
     f'#define KANTO_TRAINERS_COUNT {max(trainer_ids.values()) + 1}',
     '#define IS_KANTO_TRAINER(trainerId) ((trainerId) >= KANTO_TRAINERS_START)',
     '// Drapeaux « battu » : ceux de RF (TRAINER_FLAGS_START 0x500 de RF) dans le bloc Kanto',
     '#define KANTO_TRAINER_FLAGS_START (KANTO_FLAGS_START + 0x500)', '']
c += [f'#define {k_trainer(n)} (KANTO_TRAINERS_START + {v})' for n, v in sorted(trainer_ids.items(), key=lambda x: x[1])]
c += ['']
c += [f'#define {k_class(n)} (KANTO_TRAINER_CLASS_START + {v})' for n, v in sorted(classes.items(), key=lambda x: x[1])]
c += ['']
c += [f'#define {k_pic(n)} (KANTO_TRAINER_PIC_START + {v})' for n, v in sorted(pics.items(), key=lambda x: x[1])]
c += ['', '#endif', '']
write(f'{em}/include/constants/kanto_trainers.h', '\n'.join(c))

# 2. équipes
parties = read(f'{fr}/src/data/trainer_parties.h')
parties = re.sub(r'\bsParty_', 'sKantoParty_', parties)
parties = re.sub(r'#define (DUMMY_\w+)', r'#define KANTO_\1', parties)
parties = re.sub(r'\b(DUMMY_TRAINER_\w+)', r'KANTO_\1', parties).replace('#define KANTO_KANTO_', '#define KANTO_')
write(f'{em}/src/data/kanto/trainer_parties.h', '// Généré par tools/kanto/gen_trainers.py depuis src/data/trainer_parties.h de Rouge Feu.\n' + parties)

# 3. dresseurs (version française)
out = ['// Généré par tools/kanto/gen_trainers.py depuis src/data/trainers.json de Rouge Feu.',
       '// Entrées de gTrainers (incluses par src/data/trainers.h).']
for t in json.load(open(f'{fr}/src/data/trainers.json', encoding='utf-8'))['trainers']:
    tid = k_trainer(t['id'])
    if t['id'] == 'TRAINER_NONE':
        out.append(f'    [{tid}] = {{\n        .trainerName = _(""),\n    }},')
        continue
    party = re.sub(r'\bsParty_', 'sKantoParty_', t['party'])
    out.append(f'''    [{tid}] = {{
        .trainerClass = {rename_consts(t['trainerClass'])},
        .encounterMusic_gender = {t['encounterMusic_gender']},
        .trainerPic = {rename_consts(t['trainerPic'])},
        .trainerName = _("{t['trainerName_french']}"),
        .items = {{ {t['items']} }},
        .doubleBattle = {t['doubleBattle']},
        .aiFlags = {t['aiFlags']},
        .party = {party},
    }},''')
write(f'{em}/src/data/kanto/trainers.h', '\n'.join(out) + '\n')

# 4. noms de classes et argent
names = re.findall(r'^\s*\[(TRAINER_CLASS_\w+)\]\s*=\s*(_\("[^"]*"\)),', read(f'{fr}/src/data/text/trainer_class_names.h'), re.M)
write(f'{em}/src/data/kanto/trainer_class_names.h', '// Généré par tools/kanto/gen_trainers.py — noms des classes RF (entrées de gTrainerClassNames).\n'
      + ''.join(f'    [{k_class(n)}] = {s},\n' for n, s in names))
money_block = re.search(r'gTrainerMoneyTable\[\] =\s*\{(.*?)\n\};', read(f'{fr}/src/battle_main.c'), re.S).group(1)
money = re.findall(r'\{\s*(TRAINER_CLASS_\w+),\s*(\d+)\s*\}', money_block)
write(f'{em}/src/data/kanto/trainer_money.h', '// Généré par tools/kanto/gen_trainers.py — argent des classes RF (entrées de gTrainerMoneyTable).\n'
      + ''.join(f'    {{{k_class(n)}, {v}}},\n' for n, v in money))

# 5. portraits : images
gfx_src = read(f'{fr}/src/data/graphics/trainers.h')
gfx, decl = [], []
for sym, path in re.findall(r'^const u32 (gTrainer(?:FrontPic|Palette)_\w+)\[\] = INCBIN_U32\("([^"]+)"\);', gfx_src, re.M):
    if path.endswith('.4bpp.lz'):
        src, ext = path[:-len('.4bpp.lz')] + '.png', '.4bpp.lz'
    else:
        src, ext = path[:-len('.gbapal.lz')] + '.pal', '.gbapal.lz'
    dest = 'graphics/kanto/' + src[len('graphics/'):]
    os.makedirs(os.path.dirname(f'{em}/{dest}'), exist_ok=True)
    shutil.copy(f'{fr}/{src}', f'{em}/{dest}')
    ksym = sym.replace('gTrainer', 'gKantoTrainer', 1)
    gfx.append(f'const u32 {ksym}[] = INCGFX_U32("{dest}", "{ext}");')
    decl.append(f'extern const u32 {ksym}[];')
write(f'{em}/src/data/graphics/kanto_trainers.h', '// Généré par tools/kanto/gen_trainers.py — portraits des dresseurs RF.\n' + '\n'.join(gfx) + '\n')
write(f'{em}/include/kanto_trainer_graphics.h', '// Généré par tools/kanto/gen_trainers.py\n#ifndef GUARD_KANTO_TRAINER_GRAPHICS_H\n'
      '#define GUARD_KANTO_TRAINER_GRAPHICS_H\n\n' + '\n'.join(decl) + '\n\n#endif\n')


def kgfx(t):
    return re.sub(r'\bgTrainer(FrontPic|Palette)_', r'gKantoTrainer\1_', t)


# 6. portraits : tables (coordonnées, images, palettes, animations)
tables = read(f'{fr}/src/data/trainer_graphics/front_pic_tables.h')
coords = re.findall(r'\{\s*\.size = (\d+),\s*\.y_offset = (\d+)\s*\}', re.search(r'gTrainerFrontPicCoords\[\] =\s*\{(.*?)\n\};', tables, re.S).group(1))
pic_order = [n for n, _ in sorted(pics.items(), key=lambda x: x[1])]
assert len(coords) == len(pic_order), (len(coords), len(pic_order))
write(f'{em}/src/data/kanto/trainer_front_pic_coords.h', '// Généré par tools/kanto/gen_trainers.py\n'
      + ''.join(f'    [{k_pic(n)}] = {{.size = {s}, .y_offset = {y}}},\n' for n, (s, y) in zip(pic_order, coords)))
sheets = re.findall(r'TRAINER_SPRITE\((\w+), (\w+), (\w+)\)', tables)
write(f'{em}/src/data/kanto/trainer_front_pics.h', '// Généré par tools/kanto/gen_trainers.py\n'
      + ''.join(f'    [{k_pic("TRAINER_PIC_" + p)}] = {{{kgfx(s)}, {size}, {k_pic("TRAINER_PIC_" + p)}}},\n' for p, s, size in sheets))
pals = re.findall(r'TRAINER_PAL\((\w+), (\w+)\)', tables)
write(f'{em}/src/data/kanto/trainer_front_pic_palettes.h', '// Généré par tools/kanto/gen_trainers.py\n'
      + ''.join(f'    [{k_pic("TRAINER_PIC_" + p)}] = {{{kgfx(s)}, {k_pic("TRAINER_PIC_" + p)}}},\n' for p, s in pals))
anims = read(f'{fr}/src/data/trainer_graphics/front_pic_anims.h')
head, table = anims.split('const union AnimCmd *const *const gTrainerFrontAnimsPtrTable[] =')
defined = set(re.findall(r'\b(s[A-Z]\w*)\s*\[\]\s*=', head))
head = re.sub(r'\b(s[A-Z]\w*)\b', lambda m: 'sKanto' + m.group(1)[1:] if m.group(1) in defined else m.group(1), head)
entries = re.findall(r'\[(TRAINER_PIC_\w+)\]\s*=\s*(\w+),', table)
write(f'{em}/src/data/kanto/trainer_front_pic_anim_defs.h', '// Généré par tools/kanto/gen_trainers.py\n' + head)
write(f'{em}/src/data/kanto/trainer_front_pic_anims.h', '// Généré par tools/kanto/gen_trainers.py\n'
      + ''.join(f'    [{k_pic(p)}] = {"sKanto" + a[1:] if a in defined else a},\n' for p, a in entries))
print(f'{len(trainer_ids)} dresseurs, {len(classes)} classes ({len(names)} noms, {len(money)} gains), '
      f'{len(pics)} portraits ({len(gfx)} images)')
