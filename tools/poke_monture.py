#!/usr/bin/env python3
"""POKé MONTURE (PokemonNative3G) : objet rare qui remplace les CS données à Kanto (décision du 2026-10-24).

Les CS restent à Hoenn ; à Kanto, le premier don de CS donne la POKé MONTURE, et chaque don suivant lui ajoute la
capacité (flags FLAG_KANTO_GOT_HM01..06, ramassage de la CS07). Elle appelle un POKéMON des environs qui utilise la
capacité, sans l'apprendre à l'équipe ; elle marche partout (src/fusion_events.c, data/scripts/fusion_poke_monture.inc).
Crée ITEM_POKE_MONTURE (constante, données, description, icône dessinée pour la fusion). Relancer ne fait rien de plus.
Usage : python tools/poke_monture.py   (depuis la racine du projet)
"""


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b):
    t = rd(p)
    if b in t:
        return
    assert t.count(a) == 1, (p, a)
    wr(p, t.replace(a, b))


once('include/constants/items.h', '#define ITEM_LINK_CABLE 377\n\n#define ITEMS_COUNT 378\n',
     '#define ITEM_LINK_CABLE 377\n#define ITEM_POKE_MONTURE 378\n\n#define ITEMS_COUNT 379\n')
once('src/data/text/item_descriptions.h', 'static const u8 sFireStoneDesc[] = _(',
     'static const u8 sPokeMontureDesc[] = _(\n    "Appelle un POKéMON\\n"\n    "des environs pour une\\n"\n    "capacité de terrain.");\n\nstatic const u8 sFireStoneDesc[] = _(')
once('src/data/items.h', '    [ITEM_FIRE_STONE] =\n', '''    [ITEM_POKE_MONTURE] = // PokemonNative3G : remplace les CS données à Kanto
    {
        .name = _("POKé MONTURE"),
        .itemId = ITEM_POKE_MONTURE,
        .price = 0,
        .description = sPokeMontureDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_PokeMonture,
    },

    [ITEM_FIRE_STONE] =
''')
once('src/data/graphics/items.h', 'const u32 gItemIcon_OldSeaMap[]',
     'const u32 gItemIcon_PokeMonture[] = INCGFX_U32("graphics/items/icons/poke_monture.png", ".4bpp.lz"); // dessinée pour la fusion\n'
     'const u32 gItemIconPalette_PokeMonture[] = INCGFX_U32("graphics/items/icon_palettes/poke_monture.pal", ".gbapal.lz");\nconst u32 gItemIcon_OldSeaMap[]')
once('include/graphics.h', 'extern const u32 gItemIcon_OldSeaMap[];\n',
     'extern const u32 gItemIcon_OldSeaMap[];\nextern const u32 gItemIcon_PokeMonture[];\nextern const u32 gItemIconPalette_PokeMonture[];\n')
once('src/data/item_icon_table.h', '    [ITEM_LINK_CABLE] = {gItemIcon_LinkCable, gItemIconPalette_LinkCable},\n',
     '    [ITEM_LINK_CABLE] = {gItemIcon_LinkCable, gItemIconPalette_LinkCable},\n    [ITEM_POKE_MONTURE] = {gItemIcon_PokeMonture, gItemIconPalette_PokeMonture},\n')
print('ok')
