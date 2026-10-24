#!/usr/bin/env python3
"""Objets de confort (PokemonNative3G, 2026-10-24), icônes : tools/fusion_icons.py
- OVO-CHRONO (président du Fan Club de Carmin, à la place du BON COMMANDE) : les OEUFS éclosent deux fois plus vite ;
- CHARME CHROMA (concepteur de Nénucrique, POKéDEX NATIONAL complet) : 2 tirages chromatiques de plus (sauvages) ;
- CHARME OVALE (concepteur de Céladopole, POKéDEX NATIONAL complet) : la PENSION trouve des OEUFS plus souvent.
Relancer ne fait rien de plus.
Usage : python tools/fusion_charms.py   (depuis la racine du projet)
"""
K = 'data/kanto/data/maps/'


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b, cnt=1):
    t = rd(p)
    if '\r\n' in t:
        a, b = a.replace('\n', '\r\n'), b.replace('\n', '\r\n')
    if b in t:
        return
    assert t.count(a) == cnt, (p, a)
    wr(p, t.replace(a, b))


ITEMS = [  # constante, n°, nom, description, icône
    ('OVO_CHRONO', 382, 'OVO-CHRONO', 'sOvoChronoDesc', 'OvoChrono', 'ovo_chrono',
     '"Les OEUFS de\\n"\n    "l\'équipe éclosent\\n"\n    "deux fois plus vite."'),
    ('SHINY_CHARM', 383, 'CHARME CHROMA', 'sShinyCharmDesc', 'ShinyCharm', 'shiny_charm',
     '"Charme qui attire\\n"\n    "les POKéMON aux\\n"\n    "couleurs rares."'),
    ('OVAL_CHARM', 384, 'CHARME OVALE', 'sOvalCharmDesc', 'OvalCharm', 'oval_charm',
     '"La PENSION trouve\\n"\n    "des OEUFS plus\\n"\n    "souvent."'),
]

once('include/constants/items.h', '#define ITEM_AUTO_REPEL 381\n\n#define ITEMS_COUNT 382\n',
     '#define ITEM_AUTO_REPEL 381\n' + ''.join(f'#define ITEM_{c} {n}\n' for c, n, *_ in ITEMS)
     + f'\n#define ITEMS_COUNT {ITEMS[-1][1] + 1}\n')
for c, n, name, desc, icon, f, text in ITEMS:
    once('src/data/text/item_descriptions.h', 'static const u8 sOceanPassDesc[] = _(',
         f'static const u8 {desc}[] = _( // PokemonNative3G\n    {text});\n\nstatic const u8 sOceanPassDesc[] = _(')
    once('src/data/items.h', '    [ITEM_FIRE_STONE] =\n', f'''    [ITEM_{c}] = // PokemonNative3G (tools/fusion_charms.py)
    {{
        .name = _("{name}"),
        .itemId = ITEM_{c},
        .price = 0,
        .description = {desc},
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    }},

    [ITEM_FIRE_STONE] =
''')
    once('src/data/item_icon_table.h', '    [ITEMS_COUNT] =',
         f'    [ITEM_{c}] = {{gItemIcon_{icon}, gItemIconPalette_{icon}}},\n    [ITEMS_COUNT] =')
    once('include/graphics.h', 'extern const u32 gItemIcon_OceanPass[];\n',
         f'extern const u32 gItemIcon_OceanPass[];\nextern const u32 gItemIcon_{icon}[];\nextern const u32 gItemIconPalette_{icon}[];\n')
    once('src/data/graphics/items.h',
         'const u32 gItemIconPalette_OceanPass[] = INCGFX_U32("graphics/items/icon_palettes/ocean_pass.pal", ".gbapal.lz");\n',
         'const u32 gItemIconPalette_OceanPass[] = INCGFX_U32("graphics/items/icon_palettes/ocean_pass.pal", ".gbapal.lz");\n'
         f'const u32 gItemIcon_{icon}[] = INCGFX_U32("graphics/items/icons/{f}.png", ".4bpp.lz"); // PokemonNative3G\n'
         f'const u32 gItemIconPalette_{icon}[] = INCGFX_U32("graphics/items/icon_palettes/{f}.pal", ".gbapal.lz");\n')

once('include/constants/flags.h', '#define FLAG_UNUSED_0x02A    0x2A // Unused Flag\n#define FLAG_UNUSED_0x02B    0x2B // Unused Flag\n',
     '#define FLAG_GOT_SHINY_CHARM 0x2A // PokemonNative3G\n#define FLAG_GOT_OVAL_CHARM  0x2B // PokemonNative3G\n')

# --- effets (src/fusion_events.c)
once('include/fusion_events.h', 'void FishingChain_TryShiny(struct Pokemon *mon);\n',
     'void FishingChain_TryShiny(struct Pokemon *mon);\nu8 OvoChrono_EggCycles(u8 toSub);\nu8 OvalCharm_Compatibility(u8 compatibility);\n')
once('src/fusion_events.c', '''    u8 level, nature, i, rerolls = sFishingRerolls;

    sFishingRerolls = 0;
    otId = GetMonData(mon, MON_DATA_OT_ID);
    personality = GetMonData(mon, MON_DATA_PERSONALITY);
    if (rerolls == 0 ||''', '''    u8 level, nature, i, rerolls = sFishingRerolls;

    sFishingRerolls = 0;
    if (CheckBagHasItem(ITEM_SHINY_CHARM, 1)) // CHARME CHROMA : 2 tirages de plus, comme dans les jeux suivants
        rerolls += 2;
    otId = GetMonData(mon, MON_DATA_OT_ID);
    personality = GetMonData(mon, MON_DATA_PERSONALITY);
    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_UNOWN) // sa lettre dépend de la personnalité
        return;
    if (rerolls == 0 ||''')
once('src/fusion_events.c', '''// AUTO-REPOUSSE (à la place''', '''// OVO-CHRONO : les cycles d'éclosion comptent double (s'ajoute à Corps Ardent / Armumagma)
u8 OvoChrono_EggCycles(u8 toSub)
{
    if (CheckBagHasItem(ITEM_OVO_CHRONO, 1))
        return toSub * 2;
    return toSub;
}

// CHARME OVALE : chances de trouver un OEUF à la PENSION, valeurs des jeux suivants (20 -> 40, 50 -> 80, 70 -> 88)
u8 OvalCharm_Compatibility(u8 compatibility)
{
    if (!CheckBagHasItem(ITEM_OVAL_CHARM, 1))
        return compatibility;
    if (compatibility >= 70)
        return 88;
    if (compatibility >= 50)
        return 80;
    if (compatibility >= 20)
        return 40;
    return compatibility;
}

// AUTO-REPOUSSE (à la place''')
once('src/daycare.c', '#include "overworld.h"\n', '#include "overworld.h"\n#include "fusion_events.h"\n')
once('src/daycare.c', '        u8 compatibility = GetDaycareCompatibilityScore(daycare);\n',
     '        u8 compatibility = OvalCharm_Compatibility(GetDaycareCompatibilityScore(daycare)); // PokemonNative3G\n')
once('src/daycare.c', '        u8 toSub = GetEggCyclesToSubtract();\n',
     '        u8 toSub = OvoChrono_EggCycles(GetEggCyclesToSubtract()); // PokemonNative3G\n')
# CHARME CHROMA : tous les POKéMON sauvages (la chaîne de pêche passe aussi par là)
once('src/wild_encounter.c', 'static void CreateWildMon(u16 species, u8 level)\n{\n    bool32 checkCuteCharm;\n',
     '''static void CreateWildMon_Base(u16 species, u8 level);

// PokemonNative3G : tirages chromatiques en plus (CHARME CHROMA, chaîne de pêche : src/fusion_events.c)
static void CreateWildMon(u16 species, u8 level)
{
    CreateWildMon_Base(species, level);
    FishingChain_TryShiny(&gEnemyParty[0]);
}

static void CreateWildMon_Base(u16 species, u8 level)
{
    bool32 checkCuteCharm;
''')
once('src/wild_encounter.c', '    FishingChain_TryShiny(&gEnemyParty[0]); // PokemonNative3G : chaîne de pêche\n', '')

# --- qui les donne
once('data/specials.inc', '\tdef_special HasAllHoennMons\n', '\tdef_special HasAllHoennMons\n\tdef_special HasAllMons @ PokemonNative3G\n')
once('data/maps/LilycoveCity_CoveLilyMotel_2F/scripts.inc', '''LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message''', '''LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	call Fusion_EventScript_TryGiveShinyCharm @ PokemonNative3G : data/scripts/fusion_charms.inc
	message''')
once(K + 'CeladonCity_Condominiums_3F/scripts.inc', '''CeladonCity_Condominiums_3F_EventScript_ShowDiploma::
	message''', '''CeladonCity_Condominiums_3F_EventScript_ShowDiploma::
	call Fusion_EventScript_TryGiveOvalCharm @ PokemonNative3G : data/scripts/fusion_charms.inc
	message''')
fc = K + 'VermilionCity_PokemonFanClub/'
once(fc + 'scripts.inc', '''	checkitemspace ITEM_BIKE_VOUCHER
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher
	setflag FLAG_KANTO_GOT_BIKE_VOUCHER
	giveitem_msg VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman, ITEM_BIKE_VOUCHER, 1, MUS_RG_OBTAIN_KEY_ITEM
''', '''	checkitemspace ITEM_OVO_CHRONO @ PokemonNative3G : OVO-CHRONO à la place du BON COMMANDE (un seul vélo, celui de Hoenn)
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher
	setflag FLAG_KANTO_GOT_BIKE_VOUCHER
	giveitem_msg VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman, ITEM_OVO_CHRONO, 1, MUS_RG_OBTAIN_KEY_ITEM
''')
once(fc + 'text_fr.inc', '''VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman::
	.string "{PLAYER} reçoit le\\n"
	.string "BON COMMANDE!$"''', '''VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman::
	.string "{PLAYER} reçoit l'\\n"
	.string "OVO-CHRONO!$"''')
t = rd(fc + 'text_fr.inc')
a = t.index('VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher::')
b = t.index('$"', a) + 3
new = '''VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher::
	.string "Garde un OEUF dans ton équipe\\n"
	.string "avec ça, et il éclora deux fois\\l"
	.string "plus vite!\\p"
	.string "Mon GALOPA est né comme ça,\\n"
	.string "il y a bien longtemps…\\p"
	.string "Moi, je n'en ai plus besoin!\\n"
	.string "Prends-en soin!$"
'''
if 'OVO' not in t[a:b] and 'Garde un OEUF' not in t:
    wr(fc + 'text_fr.inc', t[:a] + new.replace('\n', '\r\n' if '\r\n' in t else '\n') + t[b:].lstrip('\r\n'))
once('data/event_scripts.s', '\t.include "data/scripts/fusion_bike.inc"\n',
     '\t.include "data/scripts/fusion_bike.inc"\n\t.include "data/scripts/fusion_charms.inc"\n')
print('ok')
