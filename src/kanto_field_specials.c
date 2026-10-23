// Specials de Rouge Feu portés depuis le décomp RF (field_specials.c, fame_checker.c, quest_log.c).
#include "global.h"
#include "field_message_box.h"
#include "constants/kanto_flags_vars.h"
#include "event_data.h"
#include "kanto_save.h"
#include "constants/kanto/fame_checker.h"
#include "constants/songs.h"
#include "data.h"
#include "field_specials.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "bike.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"

// Journal (Quest Log) de RF : le système n'est pas encore importé, il n'enregistre ni ne rejoue
// rien, donc son état reste 0 (ni enregistrement ni lecture).
EWRAM_DATA u8 gQuestLogState = 0;

// quest_log.c
void GetQuestLogState(void)
{
    gSpecialVar_Result = gQuestLogState;
}

// field_specials.c : SetQuestLogEvent(QL_EVENT_USED_PKMN_CENTER, NULL), sans effet tant que le
// journal n'est pas importé.
void SetUsedPkmnCenterQuestLogEvent(void)
{
}

// quest_log.c : coupe l'enregistrement en cours ; sans effet tant que le journal n'est pas importé.
void QuestLog_CutRecording(void)
{
}

// field_specials.c
bool8 IsPlayerNotInTrainerTowerLobby(void)
{
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TRAINER_TOWER_LOBBY) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TRAINER_TOWER_LOBBY))
        return FALSE;
    else
        return TRUE;
}

u16 GetKantoPokedexCount(u8 caseID);

// field_specials.c (RF)
#define tXtrans   data[0]
#define tTimer    data[1]
#define tNremain  data[2]
#define tDuration data[3]
#define tYtrans   data[4]

static void Task_ShakeScreen(u8 taskId);
static void Task_EndScreenShake(u8 taskId);

u16 ShakeScreen(void)
{
    /*
     * 0x8004 = x translation
     * 0x8005 = y translation
     * 0x8006 = num interations
     * 0x8007 = duration of an iteration
     */
    u8 taskId = CreateTask(Task_ShakeScreen, 9);
    gTasks[taskId].tXtrans = gSpecialVar_0x8005;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tNremain = gSpecialVar_0x8006;
    gTasks[taskId].tDuration = gSpecialVar_0x8007;
    gTasks[taskId].tYtrans = gSpecialVar_0x8004;
    SetCameraPanningCallback(NULL);
    PlaySE(SE_M_STRENGTH);
    return 0;
}

static void Task_ShakeScreen(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tTimer++;
    if (tTimer % tDuration == 0)
    {
        tTimer = 0;
        tNremain--;
        tXtrans = -tXtrans;
        tYtrans = -tYtrans;
        SetCameraPanning(tXtrans, tYtrans);
        if (tNremain == 0)
        {
            Task_EndScreenShake(taskId);
            InstallCameraPanAheadCallback();
        }
    }
}

static void Task_EndScreenShake(u8 taskId)
{
    DestroyTask(taskId);
    ScriptContext_Enable();
}

#undef tYtrans
#undef tDuration
#undef tNremain
#undef tTimer
#undef tXtrans

u16 GetPokedexCount(void)
{
    if (gSpecialVar_0x8004 == 0)
    {
        gSpecialVar_0x8005 = GetKantoPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetKantoPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }
    return IsNationalPokedexEnabled();
}

u16 SetSeenMon(void)
{
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(gSpecialVar_0x8004), FLAG_SET_SEEN);
    return 0;
}

u16 DoesPlayerPartyContainSpecies(void)
{
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < partyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) == gSpecialVar_0x8004)
            return TRUE;
    }
    return FALSE;
}

u16 GetPartyMonSpecies(void)
{
    return GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES_OR_EGG, NULL);
}

u16 GetLeadMonFriendship(void)
{
    struct Pokemon *pokemon = &gPlayerParty[GetLeadMonIndex()];
    if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) == 255)
        return 6;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 200)
        return 5;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 150)
        return 4;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 100)
        return 3;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 50)
        return 2;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) > 0)
        return 1;
    else
        return 0;
}

u16 ForcePlayerOntoBike(void)
{
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT)
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_MACH_BIKE);
    Overworld_SetSavedMusic(MUS_CYCLING);
    Overworld_ChangeMusicTo(MUS_CYCLING);
    return 0;
}

u16 BufferBigGuyOrBigGirlString(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        StringCopy(gStringVar1, gText_BigGuy);
    else
        StringCopy(gStringVar1, gText_BigGirl);
    return 0;
}

u16 BufferSonOrDaughterString(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        StringCopy(gStringVar1, gText_Daughter);
    else
        StringCopy(gStringVar1, gText_Son);
    return 0;
}

static const u16 sStarterSpecies[] = {
    SPECIES_BULBASAUR,
    SPECIES_SQUIRTLE,
    SPECIES_CHARMANDER
};

static u16 GetStarterSpeciesById(u16 idx)
{
    if (idx >= ARRAY_COUNT(sStarterSpecies))
        idx = 0;
    return sStarterSpecies[idx];
}

u16 GetStarterSpecies(void)
{
    return GetStarterSpeciesById(VarGet(VAR_KANTO_STARTER_MON)); // starter de Kanto (VAR_STARTER_MON = celui de Hoenn)
}

u16 IsStarterFirstStageInParty(void)
{
    u16 species = GetStarterSpeciesById(VarGet(VAR_KANTO_STARTER_MON)); // starter de Kanto (VAR_STARTER_MON = celui de Hoenn)
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < partyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) == species)
            return TRUE;
    }
    return FALSE;
}

u16 IsThereRoomInAnyBoxForMorePokemon(void)
{
    u16 i;
    u16 j;
    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            if (GetBoxMonDataAt(i, j, MON_DATA_SPECIES) == SPECIES_NONE)
                return TRUE;
        }
    }
    return FALSE;
}

u16 IsMonOTNameNotPlayers(void)
{
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_OT_NAME, gStringVar1);

    if (!StringCompare(gSaveBlock2Ptr->playerName, gStringVar1))
        return FALSE;
    else
        return TRUE;
}

u16 PlayerPartyContainsSpeciesWithPlayerID(void)
{
    // 8004 = species
    u8 playerCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < playerCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) == gSpecialVar_0x8004
            && T1_READ_32(gSaveBlock2Ptr->playerTrainerId) == GetMonData(&gPlayerParty[i], MON_DATA_OT_ID, NULL))
            return TRUE;
    }
    return FALSE;
}

u16 AreLeadMonEVsMaxedOut(void)
{
    u8 leadMonIndex = GetLeadMonIndex();
    if (GetMonEVCount(&gPlayerParty[leadMonIndex]) >= 510)
        return TRUE;
    else
        return FALSE;
}

u16 PlayerHasGrassPokemonInParty(void)
{
    u8 i;
    struct Pokemon *pokemon;
    u16 species;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        pokemon = &gPlayerParty[i];
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES)
         && !GetMonData(pokemon, MON_DATA_IS_EGG))
        {
            species = GetMonData(pokemon, MON_DATA_SPECIES);
            if (gSpeciesInfo[species].types[0] == TYPE_GRASS || gSpeciesInfo[species].types[1] == TYPE_GRASS)
                return TRUE;
        }
    }
    return FALSE;
}

static bool8 HasMonBeenRenamed(u8 idx)
{
    struct Pokemon *pokemon = &gPlayerParty[idx];
    u8 language;
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    language = GetMonData(pokemon, MON_DATA_LANGUAGE, &language);
    if (language != GAME_LANGUAGE)
        return TRUE;
    else if (StringCompare(gSpeciesNames[GetMonData(pokemon, MON_DATA_SPECIES, NULL)], gStringVar1) != 0)
        return TRUE;
    else
        return FALSE;
}

u16 HasLeadMonBeenRenamed(void)
{
    return HasMonBeenRenamed(GetLeadMonIndex());
}

u16 GetPlayerXY(void)
{
    gSpecialVar_0x8004 = gSaveBlock1Ptr->pos.x;
    gSpecialVar_0x8005 = gSaveBlock1Ptr->pos.y;
    return 0;
}

// Rouge Feu (prof_pc.c) : note du Pokédex de Kanto par le Prof. Chen (PC, en personne, ses aides)
extern const u8 PokedexRating_Text_LessThan10[];
extern const u8 PokedexRating_Text_LessThan20[];
extern const u8 PokedexRating_Text_LessThan30[];
extern const u8 PokedexRating_Text_LessThan40[];
extern const u8 PokedexRating_Text_LessThan50[];
extern const u8 PokedexRating_Text_LessThan60[];
extern const u8 PokedexRating_Text_LessThan70[];
extern const u8 PokedexRating_Text_LessThan80[];
extern const u8 PokedexRating_Text_LessThan90[];
extern const u8 PokedexRating_Text_LessThan100[];
extern const u8 PokedexRating_Text_LessThan110[];
extern const u8 PokedexRating_Text_LessThan120[];
extern const u8 PokedexRating_Text_LessThan130[];
extern const u8 PokedexRating_Text_LessThan140[];
extern const u8 PokedexRating_Text_LessThan150[];
extern const u8 PokedexRating_Text_Complete[];

static const u8 *GetProfOaksRatingMessageByCount(u16 count)
{
    gSpecialVar_Result = FALSE;

    if (count < 10)
        return PokedexRating_Text_LessThan10;

    if (count < 20)
        return PokedexRating_Text_LessThan20;

    if (count < 30)
        return PokedexRating_Text_LessThan30;

    if (count < 40)
        return PokedexRating_Text_LessThan40;

    if (count < 50)
        return PokedexRating_Text_LessThan50;

    if (count < 60)
        return PokedexRating_Text_LessThan60;

    if (count < 70)
        return PokedexRating_Text_LessThan70;

    if (count < 80)
        return PokedexRating_Text_LessThan80;

    if (count < 90)
        return PokedexRating_Text_LessThan90;

    if (count < 100)
        return PokedexRating_Text_LessThan100;

    if (count < 110)
        return PokedexRating_Text_LessThan110;

    if (count < 120)
        return PokedexRating_Text_LessThan120;

    if (count < 130)
        return PokedexRating_Text_LessThan130;

    if (count < 140)
        return PokedexRating_Text_LessThan140;

    if (count < 150)
        return PokedexRating_Text_LessThan150;

    if (count == KANTO_DEX_COUNT - 1)
    {
        // Mew doesn't count for completing the pokedex
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_MEW), 1))
            return PokedexRating_Text_LessThan150;

        gSpecialVar_Result = TRUE;
        return PokedexRating_Text_Complete;
    }

    if (count == KANTO_DEX_COUNT)
    {
        gSpecialVar_Result = TRUE;
        return PokedexRating_Text_Complete;
    }

    return PokedexRating_Text_LessThan10;
}

void GetProfOaksRatingMessage(void)
{
    ShowFieldMessage(GetProfOaksRatingMessageByCount(gSpecialVar_0x8004));
}
