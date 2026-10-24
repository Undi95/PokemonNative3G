#!/usr/bin/env python3
"""Météorite de Kanto (PokemonNative3G, 2026-10-24) : Émeraude (Mt Chimney -> Cozmo) et RF (Léo à l'Île 1 -> Île 2)
donnaient le même ITEM_METEORITE : les deux quêtes se mélangeaient (METEORITE x2, l'une pouvant servir à l'autre).
Crée ITEM_KANTO_METEORITE (même nom et même icône, identique dans les deux jeux ; description de RF) et l'utilise
dans les scripts de Kanto. Relancer ne fait rien de plus.
Usage : python tools/kanto_meteorite.py   (depuis la racine du projet)
"""


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b, cnt=1):
    t = rd(p)
    if b in t:
        return
    assert t.count(a) == cnt, (p, a)
    wr(p, t.replace(a, b))


once('include/constants/items.h', '#define ITEM_POKE_MONTURE 378\n\n#define ITEMS_COUNT 379\n',
     '#define ITEM_POKE_MONTURE 378\n#define ITEM_KANTO_METEORITE 379\n\n#define ITEMS_COUNT 380\n')
once('src/data/text/item_descriptions.h', 'static const u8 sRoom1KeyDesc[] = _(',
     'static const u8 sKantoMeteoriteDesc[] = _( // RF\n    "Météorite qui s\'est jadis\\n"\n    "écrasé sur le SITE METEORE.");\n\nstatic const u8 sRoom1KeyDesc[] = _(')
once('src/data/items.h', '    [ITEM_FIRE_STONE] =\n', '''    [ITEM_KANTO_METEORITE] = // PokemonNative3G : celle de RF (Île 1 -> Île 2), distincte de celle d'Émeraude
    {
        .name = _("METEORITE"),
        .itemId = ITEM_KANTO_METEORITE,
        .price = 0,
        .description = sKantoMeteoriteDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_FIRE_STONE] =
''')
once('src/data/item_icon_table.h', '    [ITEM_POKE_MONTURE] = {gItemIcon_PokeMonture, gItemIconPalette_PokeMonture},\n',
     '    [ITEM_POKE_MONTURE] = {gItemIcon_PokeMonture, gItemIconPalette_PokeMonture},\n'
     '    [ITEM_KANTO_METEORITE] = {gItemIcon_Meteorite, gItemIconPalette_Meteorite}, // même icône dans RF\n')
for p in ('data/kanto/data/maps/OneIsland_PokemonCenter_1F/scripts.inc', 'data/kanto/data/maps/TwoIsland_JoyfulGameCorner/scripts.inc'):
    t = rd(p)
    wr(p, t.replace('ITEM_METEORITE', 'ITEM_KANTO_METEORITE').replace('ITEM_KANTO_KANTO_METEORITE', 'ITEM_KANTO_METEORITE'))
print('ok')
