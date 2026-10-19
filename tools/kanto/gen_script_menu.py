#!/usr/bin/env python3
"""Importe les menus à choix multiples et les chaînes standard de Rouge Feu.

Usage : gen_script_menu.py FR_DIR EM_DIR

Les identifiants RF (MULTICHOICE_X, STDSTRING_X propres à RF) ne correspondent pas aux
tables d'Émeraude : les entrées RF sont ajoutées à la FIN des tables d'Émeraude.
  KANTO_MULTICHOICE_X = KANTO_MULTICHOICE_START + id RF   (START = nombre de MULTI_* d'Émeraude)
  STDSTRING_KANTO_X   = KANTO_STDSTRING_START + n         (chaînes RF absentes d'Émeraude)
Les textes français utilisés sont copiés de RF (src/data/text/*_fr.h) en gKanto…
Produit include/constants/kanto_script_menu.h et src/data/kanto_script_menu*.h.
"""
import re, subprocess, sys

fr, em = sys.argv[1], sys.argv[2]


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, text):
    with open(p, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)


def cpp_defines(root, header, prefix):
    out = subprocess.run(['cpp', '-dM', '-I', f'{root}/include', f'{root}/include/{header}'],
                         capture_output=True, text=True, check=True).stdout
    return {n: int(v, 0) for n, v in re.findall(r'#define (' + prefix + r'\w*) (\d+|0x[0-9A-Fa-f]+)\s*$', out, re.M)}


import os
# script_menu.h d'Émeraude inclut notre en-tête : version vide au premier passage
if not os.path.exists(f'{em}/include/constants/kanto_script_menu.h'):
    write(f'{em}/include/constants/kanto_script_menu.h', '// (vide : généré par tools/kanto)\n')

fr_menu = cpp_defines(fr, 'constants/menu.h', 'MULTICHOICE_')
fr_std = cpp_defines(fr, 'constants/menu.h', 'STDSTRING_')
em_multi = cpp_defines(em, 'constants/script_menu.h', 'MULTI_')
em_std = cpp_defines(em, 'constants/script_menu.h', 'STDSTRING_')
em_multi.pop('MULTI_B_PRESSED', None)
multi_start = max(em_multi.values()) + 1
std_start = max(em_std.values()) + 1

src = read(f'{fr}/src/script_menu.c')
lists = dict(re.findall(r'static const struct MenuAction (sMultichoiceList_\w+)\[\]\s*=\s*\{(.*?)\};', src, re.S))
entries = re.findall(r'\[(MULTICHOICE_\w+)\]\s*=\s*MULTICHOICE\((\w+)\)', src)
std_ptrs = re.findall(r'\[(STDSTRING_\w+)\]\s*=\s*(\w+)', src[src.index('gStdStringPtrs'):])
std_new = [(n, t) for n, t in std_ptrs if n not in em_std]

# textes RF référencés -> définitions RF renommées gKanto…
texts = {}
for p in ('src/data/text/strings_1_fr.h', 'src/data/text/strings_2_fr.h', 'src/data/text/strings_3_fr.h'):
    for name, body in re.findall(r'const u8 (\w+)\[\]\s*=\s*(_\(.*?\));', read(f'{fr}/{p}'), re.S):
        texts[name] = body
used = set()
for body in lists.values():
    used |= set(re.findall(r'\b(g\w+)\b', body))
used |= {t for _, t in std_new}
missing = sorted(u for u in used if u not in texts)
if missing:
    print('textes introuvables :', missing)

def k(name):
    return 'gKanto' + name[1:]

out = ['// Généré par tools/kanto/gen_script_menu.py depuis src/script_menu.c de Rouge Feu.', '']
for t in sorted(used):
    if t in texts:
        out.append(f'static const u8 {k(t)}[] = {texts[t]};')
out.append('')
for name, body in lists.items():
    body = re.sub(r'\b(g\w+)\b', lambda m: k(m.group(1)) if m.group(1) in texts else m.group(1), body)
    out.append(f'static const struct MenuAction sKanto{name[1:]}[] = {{{body}}};')
write(f'{em}/src/data/kanto_script_menu.h', '\n'.join(out) + '\n')

write(f'{em}/src/data/kanto_script_menu_entries.h',
      '// Généré par tools/kanto/gen_script_menu.py — entrées RF de sMultichoiceLists\n'
      + ''.join(f'    [KANTO_{n}] = MULTICHOICE(sKanto{l[1:]}),\n' for n, l in entries))
write(f'{em}/src/data/kanto_std_strings_entries.h',
      '// Généré par tools/kanto/gen_script_menu.py — chaînes standard RF ajoutées à gStdStrings\n'
      + ''.join(f'    [{n.replace("STDSTRING_", "STDSTRING_KANTO_")}] = {k(t)},\n' for n, t in std_new))

c = ['// Généré par tools/kanto/gen_script_menu.py', '#ifndef GUARD_CONSTANTS_KANTO_SCRIPT_MENU_H',
     '#define GUARD_CONSTANTS_KANTO_SCRIPT_MENU_H', '', f'#define KANTO_MULTICHOICE_START {multi_start}']
c += [f'#define KANTO_{n} (KANTO_MULTICHOICE_START + {v})' for n, v in sorted(fr_menu.items(), key=lambda x: x[1])]
c += ['', f'#define KANTO_STDSTRING_START {std_start}']
c += [f'#define {n.replace("STDSTRING_", "STDSTRING_KANTO_")} (KANTO_STDSTRING_START + {i})' for i, (n, _) in enumerate(std_new)]
c += ['', '#endif', '']
write(f'{em}/include/constants/kanto_script_menu.h', '\n'.join(c))
print(f'{len(entries)} menus RF (à partir de {multi_start}), {len(std_new)} chaînes standard RF (à partir de {std_start})')
print('STDSTRING RF propres :', [n for n, _ in std_new])

# --- échanges en jeu de RF : ajoutés à la fin de sIngameTrades / sIngameTradeMail -------------
em_trade = read(f'{em}/src/data/trade.h')
em_trades = cpp_defines(em, 'constants/trade.h', 'INGAME_TRADE_')
trade_start = max(em_trades.values()) + 1
mail_block = em_trade[em_trade.index('sIngameTradeMail['):]
mail_block = mail_block[:mail_block.index('\n};')]
mail_start = len(re.findall(r'^\s{4}\{', mail_block, re.M))
fr_trade = read(f'{fr}/src/data/ingame_trades.h')
defines = ''.join(l + '\n' for l in fr_trade.splitlines() if l.startswith('#define TEXT_INGAME_TRADE_'))
body = fr_trade[fr_trade.index('sInGameTrades[] = {') + len('sInGameTrades[] = {'):]
body = body[:body.index('\n};')]
body = re.sub(r'\[INGAME_TRADE_', '[KANTO_INGAME_TRADE_', body)
body = re.sub(r'\.mailNum = (\d+)', lambda m: f'.mailNum = {m.group(1) if m.group(1) == "255" else int(m.group(1)) + mail_start}', body)
mails = fr_trade[fr_trade.index('sInGameTradeMailMessages[][10] = {') + len('sInGameTradeMailMessages[][10] = {'):]
mails = mails[:mails.index('\n};')]
fr_trades = cpp_defines(fr, 'constants/trade.h', 'INGAME_TRADE_')
write(f'{em}/src/data/kanto_ingame_trades_entries.h',
      '// Généré par tools/kanto/gen_script_menu.py — échanges en jeu de Rouge Feu (fin de sIngameTrades)\n'
      '#include "constants/kanto_script_menu.h"\n#define FIRERED\n' + defines + body.rstrip().rstrip(',') + ',\n#undef FIRERED\n')
write(f'{em}/src/data/kanto_ingame_trade_mail_entries.h',
      '// Généré par tools/kanto/gen_script_menu.py — lettres des échanges de Rouge Feu (fin de sIngameTradeMail)\n'
      + mails.rstrip().rstrip(',').replace('EC_POKEMON2(', 'EC_POKEMON(') + ',\n')
with open(f'{em}/include/constants/kanto_script_menu.h', encoding='utf-8') as f:
    c = f.read().replace('\n#endif\n', '')
c += f'\n#define KANTO_INGAME_TRADE_START {trade_start}\n'
c += ''.join(f'#define KANTO_{n} (KANTO_INGAME_TRADE_START + {v})\n' for n, v in sorted(fr_trades.items(), key=lambda x: x[1]) if n != 'INGAME_TRADE_COUNT')
c += '\n#endif\n'
write(f'{em}/include/constants/kanto_script_menu.h', c)
print(f'{len(fr_trades)} échanges RF (à partir de {trade_start}), lettres à partir de {mail_start}')
