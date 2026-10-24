#!/usr/bin/env python3
"""CÂBLE LINK (PokemonNative3G) : objet qui fait évoluer un Pokémon comme un échange, en solo.

Crée ITEM_LINK_CABLE (constante, données, description, icône) et l'ajoute à la fin des listes des boutiques :
chaque boutique Pokémon (cartes *_Mart), les Ligues, l'étage des pierres de Céladopole (4e), le 2e étage de
Nénucrique (objets), les boutiques des îles Sevii, la Tour et la Colline des Dresseurs, la boutique de la Zone
de Combat. Relancer ne fait rien de plus (déjà ajouté).
Icône : linking_cord de pokeemerald-expansion (rh-hideout), copiée dans graphics/items/.
Usage : python tools/link_cable.py   (depuis la racine du projet)
"""
import glob, os, re


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


once('include/constants/items.h', '#define ITEM_OLD_SEA_MAP 376\n\n#define ITEMS_COUNT 377\n',
     '#define ITEM_OLD_SEA_MAP 376\n\n// PokemonNative3G\n#define ITEM_LINK_CABLE 377\n\n#define ITEMS_COUNT 378\n')
once('src/data/text/item_descriptions.h', 'static const u8 sFireStoneDesc[] = _(',
     'static const u8 sLinkCableDesc[] = _(\n    "Câble de jeu. Fait\\n"\n    "évoluer un POKéMON\\n"\n    "comme un échange.");\n\nstatic const u8 sFireStoneDesc[] = _(')
once('src/data/items.h', '    [ITEM_FIRE_STONE] =\n', '''    [ITEM_LINK_CABLE] = // PokemonNative3G : évolution par échange en solo
    {
        .name = _("CÂBLE LINK"),
        .itemId = ITEM_LINK_CABLE,
        .price = 2100,
        .description = sLinkCableDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_LinkCable,
    },

    [ITEM_FIRE_STONE] =
''')
once('src/data/graphics/items.h', 'const u32 gItemIcon_OldSeaMap[]',
     'const u32 gItemIcon_LinkCable[] = INCGFX_U32("graphics/items/icons/link_cable.png", ".4bpp.lz"); // pokeemerald-expansion (linking_cord)\n'
     'const u32 gItemIconPalette_LinkCable[] = INCGFX_U32("graphics/items/icon_palettes/link_cable.pal", ".gbapal.lz");\nconst u32 gItemIcon_OldSeaMap[]')
once('include/graphics.h', 'extern const u32 gItemIcon_OldSeaMap[];\n',
     'extern const u32 gItemIcon_OldSeaMap[];\nextern const u32 gItemIcon_LinkCable[];\nextern const u32 gItemIconPalette_LinkCable[];\n')
once('src/data/item_icon_table.h', '    [ITEM_OLD_SEA_MAP] = {gItemIcon_OldSeaMap, gItemIconPalette_OldSeaMap},\n',
     '    [ITEM_OLD_SEA_MAP] = {gItemIcon_OldSeaMap, gItemIconPalette_OldSeaMap},\n    [ITEM_LINK_CABLE] = {gItemIcon_LinkCable, gItemIconPalette_LinkCable},\n')

# boutiques
maps = [p for p in glob.glob('data/maps/*/scripts.inc') + glob.glob('data/kanto/data/maps/*/scripts.inc')]
wanted = re.compile(r'(_Mart|EverGrandeCity_PokemonLeague_1F|IndigoPlateau_PokemonCenter_1F|CeladonCity_DepartmentStore_4F|'
                    r'LilycoveCity_DepartmentStore_2F|^TwoIsland$|TrainerTower_Lobby|TrainerHill_Entrance)$')
added = []
for p in maps:
    name = os.path.basename(os.path.dirname(p))
    if not wanted.search(name):
        continue
    t = rd(p)
    for label in sorted(set(re.findall(r'^\s*pokemart\s+(\w+)', t, re.M))):
        m = re.search(r'^' + label + r'::?\s*\n(.*?)(^\s*(?:pokemartlistend|\.2byte ITEM_NONE)\b)', t, re.M | re.S)
        if not m or 'ITEM_LINK_CABLE' in m.group(1):
            continue
        directive = '.short' if '.short' in m.group(1) else '.2byte'
        t = t[:m.start(2)] + '\t%s ITEM_LINK_CABLE\n' % directive + t[m.start(2):]
        added.append('%s:%s' % (name, label))
    wr(p, t)
print('\n'.join(added))
