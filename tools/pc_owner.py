#!/usr/bin/env python3
"""Nom du PC (PokemonNative3G, 2026-10-24) : « PC de ??? » devient « PC de LÉO » à Kanto (après lui avoir parlé,
FLAG_KANTO_SYS_NOT_SOMEONES_PC) et « PC d'ANNETTE » à Hoenn (FLAG_SYS_PC_LANETTE) : menu du PC, connexion, transfert
d'un POKéMON attrapé (combat) ou reçu (écran de nom). Kanto = carte avec les tilesets de RF (IsKantoTilesetMap).
Aussi : menu START sans « POKéMON » quand l'équipe est vide (arrivée à Kanto, avant le starter).
Relancer ne fait rien de plus.
Usage : python tools/pc_owner.py   (depuis la racine du projet)
"""


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


once('include/fusion_events.h', 'bool8 Fusion_IsBoxMonLockedInHoenn(struct BoxPokemon *mon);\n',
     'bool8 Fusion_IsBoxMonLockedInHoenn(struct BoxPokemon *mon);\nu8 Fusion_GetPCOwner(void);\n'
     '#define PC_OWNER_UNKNOWN 0\n#define PC_OWNER_LANETTE 1\n#define PC_OWNER_BILL    2\n')
once('src/fusion_events.c', '#include "kanto_region_map.h"\n', '#include "kanto_region_map.h"\n#include "kanto_field_door.h"\n')
t = rd('src/fusion_events.c')
if 'Fusion_GetPCOwner' not in t:
    t = t.rstrip('\n') + '''

// Propriétaire du PC selon la région : LÉO à Kanto (une fois rencontré), ANNETTE à Hoenn (idem), sinon « ??? »
u8 Fusion_GetPCOwner(void)
{
    if (IsKantoTilesetMap())
        return FlagGet(FLAG_KANTO_SYS_NOT_SOMEONES_PC) ? PC_OWNER_BILL : PC_OWNER_UNKNOWN;
    return FlagGet(FLAG_SYS_PC_LANETTE) ? PC_OWNER_LANETTE : PC_OWNER_UNKNOWN;
}
'''
    wr('src/fusion_events.c', t)

# textes
once('src/strings.c', 'const u8 gText_LanettesPC[] = _("PC d\'ANNETTE");\n',
     'const u8 gText_LanettesPC[] = _("PC d\'ANNETTE");\nconst u8 gText_BillsPC[] = _("PC de LÉO"); // PokemonNative3G\n')
once('include/strings.h', 'extern const u8 gText_LanettesPC[];\n', 'extern const u8 gText_LanettesPC[];\nextern const u8 gText_BillsPC[];\n')
once('data/text/pc.inc', 'gText_AccessedLanettesPC::\n    .string "PC d\'ANNETTE connecté.$"\n',
     'gText_AccessedLanettesPC::\n    .string "PC d\'ANNETTE connecté.$"\n\n'
     'gText_AccessedBillsPC:: @ PokemonNative3G\n    .string "PC de LÉO connecté.$"\n')
once('data/text/pc_transfer.inc', 'gText_PkmnTransferredSomeonesPCBoxFull::', '''gText_PkmnTransferredBillsPC:: @ PokemonNative3G
    .string "{STR_VAR_2} a été transféré sur le\\n"
    .string "PC de LÉO.\\p"
    .string "Il a été placé dans la BOITE\\n"
    .string "appelée “{STR_VAR_1}”.$"

gText_PkmnTransferredBillsPCBoxFull:: @ PokemonNative3G
    .string "La BOITE “{STR_VAR_3}” sur le PC\\n"
    .string "de LÉO est pleine.\\p"
    .string "{STR_VAR_2} a été placé dans la\\n"
    .string "BOITE appelée “{STR_VAR_1}”.$"

gText_PkmnTransferredSomeonesPCBoxFull::''')

# menu du PC
once('src/script_menu.c', '''    if (FlagGet(FLAG_SYS_PC_LANETTE))
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_LanettesPC, x, 1, TEXT_SKIP_DRAW, NULL);
''', '''    if (Fusion_GetPCOwner() == PC_OWNER_BILL) // PokemonNative3G : LÉO à Kanto
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_BillsPC, x, 1, TEXT_SKIP_DRAW, NULL);
    else if (Fusion_GetPCOwner() == PC_OWNER_LANETTE)
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_LanettesPC, x, 1, TEXT_SKIP_DRAW, NULL);
''')
if '#include "fusion_events.h"' not in rd('src/script_menu.c'):
    once('src/script_menu.c', '#include "global.h"\n', '#include "global.h"\n#include "fusion_events.h"\n')
once('data/specials.inc', '\tdef_special CanFlyBetweenRegions @ PokemonNative3G\n',
     '\tdef_special CanFlyBetweenRegions @ PokemonNative3G\n\tdef_special Fusion_GetPCOwner @ PokemonNative3G\n')
once('data/scripts/pc.inc', '''	call_if_unset FLAG_SYS_PC_LANETTE, EventScript_AccessSomeonesPC
	call_if_set FLAG_SYS_PC_LANETTE, EventScript_AccessLanettesPC
''', '''	specialvar VAR_RESULT, Fusion_GetPCOwner @ PokemonNative3G : LÉO à Kanto, ANNETTE à Hoenn
	call_if_eq VAR_RESULT, 0, EventScript_AccessSomeonesPC
	call_if_eq VAR_RESULT, 1, EventScript_AccessLanettesPC
	call_if_eq VAR_RESULT, 2, EventScript_AccessBillsPC
''')
once('data/scripts/pc.inc', '''EventScript_AccessLanettesPC::
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
	return
''', '''EventScript_AccessLanettesPC::
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
	return

EventScript_AccessBillsPC::
	msgbox gText_AccessedBillsPC, MSGBOX_DEFAULT
	return
''')

# combat : POKéMON attrapé envoyé au PC ({B_PC_CREATOR_NAME} et choix du message)
once('src/battle_message.c', 'static const u8 sText_Lanettes[] = _("d\'ANNETTE");\n',
     'static const u8 sText_Lanettes[] = _("d\'ANNETTE");\nstatic const u8 sText_Bills[] = _("de LÉO"); // PokemonNative3G\n')
once('src/battle_message.c', '''            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;''', '''            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (Fusion_GetPCOwner() == PC_OWNER_BILL) // PokemonNative3G
                    toCpy = sText_Bills;
                else if (Fusion_GetPCOwner() == PC_OWNER_LANETTE)
                    toCpy = sText_Lanettes;''')
once('src/battle_message.c', '''    [STRINGID_PKMNTRANSFERREDLANETTESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPC,
''', '''    [STRINGID_PKMNTRANSFERREDLANETTESPC - BATTLESTRINGS_TABLE_START] = sText_PkmnTransferredOwnersPC, // PokemonNative3G
''')
once('src/battle_message.c', '''    [STRINGID_PKMNBOXLANETTESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPCBoxFull,
''', '''    [STRINGID_PKMNBOXLANETTESPCFULL - BATTLESTRINGS_TABLE_START] = sText_PkmnTransferredOwnersPCBoxFull, // PokemonNative3G
''')
once('src/battle_message.c', 'static const u8 sText_Bills[] = _("de LÉO"); // PokemonNative3G\n', '''static const u8 sText_Bills[] = _("de LÉO"); // PokemonNative3G
// PokemonNative3G : comme gText_PkmnTransferredLanettesPC(BoxFull), avec le nom du propriétaire (ANNETTE ou LÉO)
static const u8 sText_PkmnTransferredOwnersPC[] = _("{STR_VAR_2} a été transféré sur le\\nPC {B_PC_CREATOR_NAME}.\\pIl a été placé dans la BOITE\\nappelée “{STR_VAR_1}”.");
static const u8 sText_PkmnTransferredOwnersPCBoxFull[] = _("La BOITE “{STR_VAR_3}” sur le PC\\n{B_PC_CREATOR_NAME} est pleine.\\p{STR_VAR_2} a été placé dans la\\nBOITE appelée “{STR_VAR_1}”.");
''')
if '#include "fusion_events.h"' not in rd('src/battle_message.c'):
    once('src/battle_message.c', '#include "global.h"\n', '#include "global.h"\n#include "fusion_events.h"\n')
once('src/battle_script_commands.c', '''        // Change to B_MSG_SENT_LANETTES_PC or B_MSG_LANETTES_BOX_FULL
        if (FlagGet(FLAG_SYS_PC_LANETTE))''', '''        // Change to B_MSG_SENT_LANETTES_PC or B_MSG_LANETTES_BOX_FULL
        if (Fusion_GetPCOwner() != PC_OWNER_UNKNOWN) // PokemonNative3G : LÉO à Kanto''')
if '#include "fusion_events.h"' not in rd('src/battle_script_commands.c'):
    once('src/battle_script_commands.c', '#include "global.h"\n', '#include "global.h"\n#include "fusion_events.h"\n')

# écran de nom (POKéMON reçu, équipe pleine)
once('src/naming_screen.c', '''    if (FlagGet(FLAG_SYS_PC_LANETTE))
        stringToDisplay++;

    StringExpandPlaceholders(gStringVar4, sTransferredToPCMessages[stringToDisplay]);''', '''    if (Fusion_GetPCOwner() != PC_OWNER_UNKNOWN) // PokemonNative3G : LÉO à Kanto
        stringToDisplay++;

    if (Fusion_GetPCOwner() == PC_OWNER_BILL)
        StringExpandPlaceholders(gStringVar4, stringToDisplay == 1 ? gText_PkmnTransferredBillsPC : gText_PkmnTransferredBillsPCBoxFull);
    else
    StringExpandPlaceholders(gStringVar4, sTransferredToPCMessages[stringToDisplay]);''')
once('include/strings.h', 'extern const u8 gText_BillsPC[];\n',
     'extern const u8 gText_BillsPC[];\nextern const u8 gText_PkmnTransferredBillsPC[];\nextern const u8 gText_PkmnTransferredBillsPCBoxFull[];\n')
if '#include "fusion_events.h"' not in rd('src/naming_screen.c'):
    once('src/naming_screen.c', '#include "global.h"\n', '#include "global.h"\n#include "fusion_events.h"\n')

# menu START : pas de POKéMON avec une équipe vide
once('src/start_menu.c', '''    if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE)
    {
        AddStartMenuAction(MENU_ACTION_POKEMON);
    }''', '''    if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE && CalculatePlayerPartyCount() != 0) // PokemonNative3G : équipe vide (Kanto)
    {
        AddStartMenuAction(MENU_ACTION_POKEMON);
    }''')
print('ok')
