# Exécuté par tools/kanto_travel.py (mêmes helpers rd/wr/once).
# PC : POKéMON de Hoenn (lieu de rencontre hors Kanto) grisés et refusés dans l'équipe tant que le voyage à Kanto
# est en cours (FLAG_FUSION_KANTO_VISITED et pas encore CanFlyBetweenRegions) ; au départ, l'équipe part au PC.

once('include/fusion_events.h', 'u32 ShinyCharm_EggPersonality(u32 personality);\n',
     'u32 ShinyCharm_EggPersonality(u32 personality);\nbool8 Fusion_IsBoxMonLockedInHoenn(struct BoxPokemon *mon);\n')
once('src/fusion_events.c', '#include "item.h"\n', '#include "item.h"\n#include "kanto_region_map.h"\n')
t = rd('src/fusion_events.c')
if 'Fusion_IsBoxMonLockedInHoenn' not in t:
    t = t.rstrip('\n') + '''

// POKéMON de Hoenn pendant le voyage à Kanto : grisés au PC, ils ne peuvent pas rejoindre l'équipe tant que la Ligue
// de Kanto n'est pas finie et le Rubis/Saphir rendu à CILEO (comme le vol entre régions). « De Hoenn » = rencontré
// hors de Kanto (oeufs de Hoenn compris), sauf échanges et rencontres spéciales.
bool8 Fusion_IsBoxMonLockedInHoenn(struct BoxPokemon *mon)
{
    u8 location;

    if (!FlagGet(FLAG_FUSION_KANTO_VISITED) || CanFlyBetweenRegions())
        return FALSE;
    if (GetBoxMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
        return FALSE;
    location = GetBoxMonData(mon, MON_DATA_MET_LOCATION);
    return location < KANTO_MAPSEC_START || (location > KANTO_MAPSEC_END && location < METLOC_SPECIAL_EGG);
}
'''
    wr('src/fusion_events.c', t)

# départ : l'équipe au PC (pokemon.c, à côté de CopyMonToPC)
once('include/pokemon.h', 'u8 CalculatePlayerPartyCount(void);\n',
     'u8 CalculatePlayerPartyCount(void);\nvoid Fusion_StorePartyInPC(void);\n')
once('src/pokemon.c', '''u8 CalculatePlayerPartyCount(void)
{''', '''// PokemonNative3G : premier départ pour Kanto, toute l'équipe part au PC (ceux qui n'y tiennent pas restent)
void Fusion_StorePartyInPC(void)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
            continue;
        if (CopyMonToPC(&gPlayerParty[i]) == MON_GIVEN_TO_PC)
            ZeroMonData(&gPlayerParty[i]);
    }
    CompactPartySlots();
    CalculatePlayerPartyCount();
}

u8 CalculatePlayerPartyCount(void)
{''')

S = 'src/pokemon_storage_system.c'
once(S, '#include "global.h"\n', '#include "global.h"\n#include "fusion_events.h"\n')
once(S, '    MSG_CANT_STORE_MAIL,\n};', '    MSG_CANT_STORE_MAIL,\n    MSG_HOENN_LOCKED, // PokemonNative3G\n};')
once(S, '    [MSG_PARTY_FULL]           = {gText_YourPartysFull,          MSG_VAR_NONE},\n',
     '    [MSG_PARTY_FULL]           = {gText_YourPartysFull,          MSG_VAR_NONE},\n'
     '    [MSG_HOENN_LOCKED]         = {sText_HoennLocked,             MSG_VAR_NONE}, // PokemonNative3G\n')
t = rd(S)
i = t.index('static const struct StorageMessage sMessages[]') if 'static const struct StorageMessage sMessages[]' in t else None
assert i is not None
once(S, 'static const struct StorageMessage sMessages[]',
     '// PokemonNative3G : POKéMON de Hoenn pendant le voyage à Kanto (Fusion_IsBoxMonLockedInHoenn)\n'
     'static const u8 sText_HoennLocked[] = _("Aucun lien avec HOENN!");\n\n'
     'static const struct StorageMessage sMessages[]')
# icônes grisées (transparentes, comme le mode objets)
once(S, '''                personality = GetBoxMonDataAt(boxId, boxPosition, MON_DATA_PERSONALITY);
                sStorage->boxMonsSprites[count] = CreateMonIconSprite(species, personality, 8 * (3 * j) + 100, 8 * (3 * i) + 44, 2, 19 - j);
''', '''                personality = GetBoxMonDataAt(boxId, boxPosition, MON_DATA_PERSONALITY);
                sStorage->boxMonsSprites[count] = CreateMonIconSprite(species, personality, 8 * (3 * j) + 100, 8 * (3 * i) + 44, 2, 19 - j);
                if (sStorage->boxMonsSprites[count] != NULL && Fusion_IsBoxMonLockedInHoenn(GetBoxedMonPtr(boxId, boxPosition))) // PokemonNative3G
                    sStorage->boxMonsSprites[count]->oam.objMode = ST_OAM_OBJ_BLEND;
''')
once(S, '''        sStorage->boxMonsSprites[boxPosition] = CreateMonIconSprite(species, personality, x, y, 2, 19 - (boxPosition % IN_BOX_COLUMNS));
        if (sStorage->boxOption == OPTION_MOVE_ITEMS)
''', '''        sStorage->boxMonsSprites[boxPosition] = CreateMonIconSprite(species, personality, x, y, 2, 19 - (boxPosition % IN_BOX_COLUMNS));
        if (sStorage->boxMonsSprites[boxPosition] != NULL && Fusion_IsBoxMonLockedInHoenn(GetBoxedMonPtr(StorageGetCurrentBox(), boxPosition))) // PokemonNative3G
            sStorage->boxMonsSprites[boxPosition]->oam.objMode = ST_OAM_OBJ_BLEND;
        if (sStorage->boxOption == OPTION_MOVE_ITEMS)
''')
once(S, '''                    sStorage->boxMonsSprites[boxPosition]->callback = SpriteCB_BoxMonIconScrollIn;
                    iconsCreated++;
''', '''                    sStorage->boxMonsSprites[boxPosition]->callback = SpriteCB_BoxMonIconScrollIn;
                    if (Fusion_IsBoxMonLockedInHoenn(GetBoxedMonPtr(sStorage->incomingBoxId, boxPosition))) // PokemonNative3G
                        sStorage->boxMonsSprites[boxPosition]->oam.objMode = ST_OAM_OBJ_BLEND;
                    iconsCreated++;
''')
once(S, '''static void SetMonIconTransparency(void)
{
    if (sStorage->boxOption == OPTION_MOVE_ITEMS)
    {''', '''static void SetMonIconTransparency(void)
{
    // PokemonNative3G : aussi hors mode objets, pour les POKéMON de Hoenn grisés
    {''')
# refus : RETIRER, et POSER / ÉCHANGER dans l'équipe
once(S, '''    case 0:
        if (CalculatePlayerPartyCount() == PARTY_SIZE)
        {
            PrintMessage(MSG_PARTY_FULL);
            sStorage->state = 1;
        }''', '''    case 0:
        if (Fusion_IsBoxMonLockedInHoenn(GetBoxedMonPtr(StorageGetCurrentBox(), sCursorPosition))) // PokemonNative3G
        {
            PlaySE(SE_FAILURE);
            PrintMessage(MSG_HOENN_LOCKED);
            sStorage->state = 1;
        }
        else if (CalculatePlayerPartyCount() == PARTY_SIZE)
        {
            PrintMessage(MSG_PARTY_FULL);
            sStorage->state = 1;
        }''')
for task, change in (('Task_PlaceMon', 'CHANGE_PLACE'), ('Task_ShiftMon', 'CHANGE_SHIFT')):
    once(S, f'''static void {task}(u8 taskId)
{{
    switch (sStorage->state)
    {{
    case 0:
        InitMonPlaceChange({change});
        sStorage->state++;
        break;
''', f'''static void {task}(u8 taskId)
{{
    switch (sStorage->state)
    {{
    case 0:
        if (sCursorArea == CURSOR_AREA_IN_PARTY && Fusion_IsBoxMonLockedInHoenn(&sStorage->movingMon.box)) // PokemonNative3G
        {{
            PlaySE(SE_FAILURE);
            PrintMessage(MSG_HOENN_LOCKED);
            sStorage->state = 10;
            break;
        }}
        InitMonPlaceChange({change});
        sStorage->state++;
        break;
    case 10:
        if (JOY_NEW(A_BUTTON | B_BUTTON | DPAD_ANY))
        {{
            ClearBottomWindow();
            if (sInPartyMenu)
                SetPokeStorageTask(Task_HandleMovingMonFromParty);
            else
                SetPokeStorageTask(Task_PokeStorageMain);
        }}
        break;
''')
