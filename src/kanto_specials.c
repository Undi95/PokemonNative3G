// Specials de Rouge Feu portés depuis le décomp RF (field_specials.c, help_system.c…).
// Les fonctions qui renvoient une valeur sont en u16 (lue par specialvar), comme les autres specials.
// Les noms RF des variables / flags / métatuiles sont préfixés KANTO_ (import_scripts.py) ;
// les numéros de métatuiles de RF sont conservés à l'import (tools/kanto/import_kanto.py).
#include "global.h"
#include "berry_powder.h"
#include "data.h"
#include "hall_of_fame.h"
#include "money.h"
#include "palette.h"
#include "party_menu.h"
#include "script_menu.h"
#include "start_menu.h"
#include "save_location.h"
#include "script.h"
#include "event_data.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "mail.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "tv.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/maps.h"
#include "constants/moves.h"
#include "constants/species.h"
#include "constants/songs.h"
#include "constants/kanto/metatile_labels.h"
#include "constants/kanto/move_tutors.h"
#include "constants/kanto/seagallop.h"

u8 GetLeadMonIndex(void);

// field_specials.c
void NullFieldSpecial(void)
{

}

// help_system.c : l'aide de RF (bouton L/R) n'existe pas dans Émeraude ; ces specials ne
// font que choisir la page d'aide affichée, ils sont donc sans effet ici.
void Script_SetHelpContext(void)
{
}

void BackupHelpContext(void)
{
}

void RestoreHelpContext(void)
{
}

void SetHelpContextForMap(void)
{
}

void HelpSystem_Disable(void)
{
}

void HelpSystem_Enable(void)
{
}

// quest_log_events.c : journal de RF non importé (cf. QuestLog_CutRecording).
void QuestLog_StartRecordingInputsAfterDeferredEvent(void)
{
}

// field_specials.c
#define tState data[0]
#define tTimer data[1]

static void PcTurnOnUpdateMetatileId(bool16 flickerOff)
{
    u16 metatileId = 0;
    s8 deltaX = 0;
    s8 deltaY = 0;
    u8 direction = GetPlayerFacingDirection();

    switch (direction)
    {
    case DIR_NORTH:
        deltaX = 0;
        deltaY = -1;
        break;
    case DIR_WEST:
        deltaX = -1;
        deltaY = -1;
        break;
    case DIR_EAST:
        deltaX = 1;
        deltaY = -1;
        break;
    }
    if (flickerOff)
    {
        if (gSpecialVar_0x8004 == 0)
            metatileId = METATILE_Building_PCOff;
        else if (gSpecialVar_0x8004 == 1)
            metatileId = METATILE_GenericBuilding1_PlayersPCOff;
        else if (gSpecialVar_0x8004 == 2)
            metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    }
    else
    {
        if (gSpecialVar_0x8004 == 0)
            metatileId = METATILE_Building_PCOn;
        else if (gSpecialVar_0x8004 == 1)
            metatileId = METATILE_GenericBuilding1_PlayersPCOn;
        else if (gSpecialVar_0x8004 == 2)
            metatileId = METATILE_GenericBuilding1_PlayersPCOn;
    }
    MapGridSetMetatileIdAt(gSaveBlock1Ptr->pos.x + deltaX + MAP_OFFSET, gSaveBlock1Ptr->pos.y + deltaY + MAP_OFFSET, metatileId | MAPGRID_COLLISION_MASK);
}

static void Task_AnimatePcTurnOn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (tTimer == 6)
    {
        PcTurnOnUpdateMetatileId(tState & 1);
        DrawWholeMapView();
        tTimer = 0;
        tState++;
        if (tState == 5)
            DestroyTask(taskId);
    }
    tTimer++;
}

void AnimatePcTurnOn(void)
{
    u8 taskId;

    if (FuncIsActiveTask(Task_AnimatePcTurnOn) != TRUE)
    {
        taskId = CreateTask(Task_AnimatePcTurnOn, 8);
        gTasks[taskId].tState = 0;
        gTasks[taskId].tTimer = 0;
    }
}

#undef tState
#undef tTimer

void AnimatePcTurnOff(void)
{
    u16 metatileId = 0;
    s8 deltaX = 0;
    s8 deltaY = 0;
    u8 direction = GetPlayerFacingDirection();

    switch (direction)
    {
    case DIR_NORTH:
        deltaX = 0;
        deltaY = -1;
        break;
    case DIR_WEST:
        deltaX = -1;
        deltaY = -1;
        break;
    case DIR_EAST:
        deltaX = 1;
        deltaY = -1;
        break;
    }
    if (gSpecialVar_0x8004 == 0)
        metatileId = METATILE_Building_PCOff;
    else if (gSpecialVar_0x8004 == 1)
        metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    else if (gSpecialVar_0x8004 == 2)
        metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    MapGridSetMetatileIdAt(gSaveBlock1Ptr->pos.x + deltaX + MAP_OFFSET, gSaveBlock1Ptr->pos.y + deltaY + MAP_OFFSET, metatileId | MAPGRID_COLLISION_MASK);
    DrawWholeMapView();
}

// RF : SetHelpContext(HELPCONTEXT_SURFING) en plus (aide de RF absente)
void ForcePlayerToStartSurfing(void)
{
    SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_SURFING);
}

static const u8 sMartMaps[][3] = {
    {MAP_GROUP(MAP_VIRIDIAN_CITY_MART),   MAP_NUM(MAP_VIRIDIAN_CITY_MART),   1},
    {MAP_GROUP(MAP_PEWTER_CITY_MART),     MAP_NUM(MAP_PEWTER_CITY_MART),     3},
    {MAP_GROUP(MAP_CERULEAN_CITY_MART),   MAP_NUM(MAP_CERULEAN_CITY_MART),   1},
    {MAP_GROUP(MAP_LAVENDER_TOWN_MART),   MAP_NUM(MAP_LAVENDER_TOWN_MART),   1},
    {MAP_GROUP(MAP_VERMILION_CITY_MART),  MAP_NUM(MAP_VERMILION_CITY_MART),  1},
    {MAP_GROUP(MAP_FUCHSIA_CITY_MART),    MAP_NUM(MAP_FUCHSIA_CITY_MART),    1},
    {MAP_GROUP(MAP_CINNABAR_ISLAND_MART), MAP_NUM(MAP_CINNABAR_ISLAND_MART), 1},
    {MAP_GROUP(MAP_SAFFRON_CITY_MART),    MAP_NUM(MAP_SAFFRON_CITY_MART),    1},
    {MAP_GROUP(MAP_THREE_ISLAND_MART),    MAP_NUM(MAP_THREE_ISLAND_MART),    1},
    {MAP_GROUP(MAP_FOUR_ISLAND_MART),     MAP_NUM(MAP_FOUR_ISLAND_MART),     1},
    {MAP_GROUP(MAP_SEVEN_ISLAND_MART),    MAP_NUM(MAP_SEVEN_ISLAND_MART),    1},
    {MAP_GROUP(MAP_SIX_ISLAND_MART),      MAP_NUM(MAP_SIX_ISLAND_MART),      1}
};

u16 GetMartClerkObjectId(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sMartMaps); i++)
    {
        if (gSaveBlock1Ptr->location.mapGroup == sMartMaps[i][0] && gSaveBlock1Ptr->location.mapNum == sMartMaps[i][1])
            return sMartMaps[i][2];
    }
    return 1;
}

u16 CheckAddCoins(void)
{
    if (gSpecialVar_Result + gSpecialVar_0x8006 > 9999)
        return FALSE;
    else
        return TRUE;
}

u16 NameRaterWasNicknameChanged(void)
{
    struct Pokemon *pokemon = &gPlayerParty[gSpecialVar_0x8004];
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    if (StringCompare(gStringVar3, gStringVar1) == 0)
        return FALSE;
    else
        return TRUE;
}

static const u8 sSlotMachineIndices[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5
};

u16 GetRandomSlotMachineId(void)
{
    u16 rval = Random() % ARRAY_COUNT(sSlotMachineIndices);
    return sSlotMachineIndices[rval];
}

void UpdateLoreleiDollCollection(void)
{
    u32 numHofClears = GetGameStat(GAME_STAT_ENTERED_HOF);
    if (numHofClears >= 25)
    {
        FlagClear(FLAG_KANTO_HIDE_LORELEI_HOUSE_MEOWTH_DOLL);
        if (numHofClears >= 50)
            FlagClear(FLAG_KANTO_HIDE_LORELEI_HOUSE_CHANSEY_DOLL);
        if (numHofClears >= 75)
            FlagClear(FLAG_KANTO_HIDE_LORELEIS_HOUSE_NIDORAN_F_DOLL);
        if (numHofClears >= 100)
            FlagClear(FLAG_KANTO_HIDE_LORELEI_HOUSE_JIGGLYPUFF_DOLL);
        if (numHofClears >= 125)
            FlagClear(FLAG_KANTO_HIDE_LORELEIS_HOUSE_NIDORAN_M_DOLL);
        if (numHofClears >= 150)
            FlagClear(FLAG_KANTO_HIDE_LORELEIS_HOUSE_FEAROW_DOLL);
        if (numHofClears >= 175)
            FlagClear(FLAG_KANTO_HIDE_LORELEIS_HOUSE_PIDGEOT_DOLL);
        if (numHofClears >= 200)
            FlagClear(FLAG_KANTO_HIDE_LORELEIS_HOUSE_LAPRAS_DOLL);
    }
}

u16 StickerManGetBragFlags(void)
{
    u16 result = 0;
    u32 numEggs;
    gSpecialVar_0x8004 = GetGameStat(GAME_STAT_ENTERED_HOF);
    numEggs = GetGameStat(GAME_STAT_HATCHED_EGGS);
    gSpecialVar_0x8006 = GetGameStat(GAME_STAT_LINK_BATTLE_WINS);
    if (numEggs > 0xFFFF)
        gSpecialVar_0x8005 = 0xFFFF;
    else
        gSpecialVar_0x8005 = numEggs;
    if (gSpecialVar_0x8004 != 0)
        result |= 1 << 0;
    if (gSpecialVar_0x8005 != 0)
        result |= 1 << 1;
    if (gSpecialVar_0x8006 != 0)
        result |= 1 << 2;
    return result;
}

void UpdateTrainerCardPhotoIcons(void)
{
    u16 species[PARTY_SIZE];
    u32 personality[PARTY_SIZE];
    u8 i;
    u8 partyCount;
    for (i = 0; i < PARTY_SIZE; i++)
        species[i] = SPECIES_NONE;
    partyCount = CalculatePlayerPartyCount();
    for (i = 0; i < partyCount; i++)
    {
        species[i] = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL);
        personality[i] = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY, NULL);
    }
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_1, SpeciesToMailSpecies(species[0], personality[0]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_2, SpeciesToMailSpecies(species[1], personality[1]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_3, SpeciesToMailSpecies(species[2], personality[2]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_4, SpeciesToMailSpecies(species[3], personality[3]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_5, SpeciesToMailSpecies(species[4], personality[4]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_6, SpeciesToMailSpecies(species[5], personality[5]));
    VarSet(VAR_KANTO_TRAINER_CARD_MON_ICON_TINT_IDX, gSpecialVar_0x8004);
}

static void Task_WingFlapSound(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    data[1]++;
    if (data[1] == gSpecialVar_0x8005)
    {
        data[0]++;
        data[1] = 0;
        PlaySE(SE_M_WING_ATTACK);
    }
    if (data[0] == gSpecialVar_0x8004 - 1)
        DestroyTask(taskId);
}

void LoopWingFlapSound(void)
{
    // 8004 = Num flaps
    // 8005 = Frame delay between flaps
    CreateTask(Task_WingFlapSound, 8);
    PlaySE(SE_M_WING_ATTACK);
}

void SetVermilionTrashCans(void)
{
    u16 idx = (Random() % 15) + 1;
    gSpecialVar_0x8004 = idx;
    gSpecialVar_0x8005 = idx;
    switch (gSpecialVar_0x8004)
    {
    case 1:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 += 5;
        break;
    case 2:
    case 3:
    case 4:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 += 1;
        else if (idx == 1)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 5:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 6:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 += 5;
        break;
    case 7:
    case 8:
    case 9:
        idx = Random() % 4;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else if (idx == 2)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 10:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 11:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else
            gSpecialVar_0x8005 += 1;
        break;
    case 12:
    case 13:
    case 14:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 15:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    }
    if (gSpecialVar_0x8005 > 15)
    {
        if (gSpecialVar_0x8004 % 5 == 1)
            gSpecialVar_0x8005 = gSpecialVar_0x8004 + 1;
        else if (gSpecialVar_0x8004 % 5 == 0)
            gSpecialVar_0x8005 = gSpecialVar_0x8004 - 1;
        else
            gSpecialVar_0x8005 = gSpecialVar_0x8004 + 1;
    }
}

static const u16 sResortGorgeousDeluxeRewards[] = {
    ITEM_BIG_PEARL,
    ITEM_PEARL,
    ITEM_STARDUST,
    ITEM_STAR_PIECE,
    ITEM_NUGGET,
    ITEM_RARE_CANDY
};

// Appelé à chaque pas (field_control_avatar.c)
void IncrementResortGorgeousStepCounter(void)
{
    u16 var4035 = VarGet(VAR_KANTO_RESORT_GOREGEOUS_STEP_COUNTER);
    if (VarGet(VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON) != SPECIES_NONE)
    {
        var4035++;
        if (var4035 >= 250)
        {
            VarSet(VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON, 0xFFFF);
            VarSet(VAR_KANTO_RESORT_GOREGEOUS_STEP_COUNTER, 0);
        }
        else
        {
            VarSet(VAR_KANTO_RESORT_GOREGEOUS_STEP_COUNTER, var4035);
        }
    }
}

static u16 SampleResortGorgeousMon(void)
{
    u16 i;
    u16 species;
    for (i = 0; i < 100; i++)
    {
        species = (Random() % (NUM_SPECIES - 1)) + 1;
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) == TRUE)
            return species;
    }
    while (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) != TRUE)
    {
        if (species == SPECIES_BULBASAUR)
            species = NUM_SPECIES - 1;
        else
            species--;
    }
    return species;
}

static u16 SampleResortGorgeousReward(void)
{
    if ((Random() % 100) >= 30)
        return ITEM_LUXURY_BALL;
    else
        return sResortGorgeousDeluxeRewards[Random() % ARRAY_COUNT(sResortGorgeousDeluxeRewards)];
}

void SampleResortGorgeousMonAndReward(void)
{
    u16 requestedSpecies = VarGet(VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON);
    if (requestedSpecies == SPECIES_NONE || requestedSpecies == 0xFFFF)
    {
        VarSet(VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON, SampleResortGorgeousMon());
        VarSet(VAR_KANTO_RESORT_GORGEOUS_REWARD, SampleResortGorgeousReward());
        VarSet(VAR_KANTO_RESORT_GOREGEOUS_STEP_COUNTER, 0);
    }
    StringCopy(gStringVar1, gSpeciesNames[VarGet(VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON)]);
}

// Appelé à chaque pas (field_control_avatar.c)
void RunMassageCooldownStepCounter(void)
{
    u16 count = VarGet(VAR_KANTO_MASSAGE_COOLDOWN_STEP_COUNTER);
    if (count < 500)
        VarSet(VAR_KANTO_MASSAGE_COOLDOWN_STEP_COUNTER, count + 1);
}

void DaisyMassageServices(void)
{
    AdjustFriendship(&gPlayerParty[gSpecialVar_0x8004], FRIENDSHIP_EVENT_MASSAGE);
    VarSet(VAR_KANTO_MASSAGE_COOLDOWN_STEP_COUNTER, 0);
}

static const u8 sCapeBrinkCompatibleSpecies[] = {
    SPECIES_VENUSAUR,
    SPECIES_CHARIZARD,
    SPECIES_BLASTOISE
};

u16 CapeBrinkGetMoveToTeachLeadPokemon(void)
{
    // Returns:
    //   8005 = Move tutor index
    //   8006 = Num moves known by lead mon
    //   8007 = Index of lead mon
    //   to specialvar = whether a move can be taught in the first place
    u8 tutorMonId = 0;
    u8 numMovesKnown = 0;
    u8 leadMonSlot = GetLeadMonIndex();
    u8 i;
    gSpecialVar_0x8007 = leadMonSlot;
    for (i = 0; i < ARRAY_COUNT(sCapeBrinkCompatibleSpecies); i++)
    {
        if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_SPECIES_OR_EGG, NULL) == sCapeBrinkCompatibleSpecies[i])
        {
            tutorMonId = i;
            break;
        }
    }
    if (i == ARRAY_COUNT(sCapeBrinkCompatibleSpecies) || GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_FRIENDSHIP) != 255)
        return FALSE;
    if (tutorMonId == 0)
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_FRENZY_PLANT]);
        gSpecialVar_0x8005 = MOVETUTOR_FRENZY_PLANT;
        if (FlagGet(FLAG_KANTO_TUTOR_FRENZY_PLANT) == TRUE)
            return FALSE;
    }
    else if (tutorMonId == 1)
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_BLAST_BURN]);
        gSpecialVar_0x8005 = MOVETUTOR_BLAST_BURN;
        if (FlagGet(FLAG_KANTO_TUTOR_BLAST_BURN) == TRUE)
            return FALSE;
    }
    else
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_HYDRO_CANNON]);
        gSpecialVar_0x8005 = MOVETUTOR_HYDRO_CANNON;
        if (FlagGet(FLAG_KANTO_TUTOR_HYDRO_CANNON) == TRUE)
            return FALSE;
    }
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE1) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE2) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE3) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE4) != MOVE_NONE)
        numMovesKnown++;
    gSpecialVar_0x8006 = numMovesKnown;
    return TRUE;
}

u16 HasLearnedAllMovesFromCapeBrinkTutor(void)
{
    // 8005 is set by CapeBrinkGetMoveToTeachLeadPokemon
    u8 r4 = 0;
    if (gSpecialVar_0x8005 == MOVETUTOR_FRENZY_PLANT)
        FlagSet(FLAG_KANTO_TUTOR_FRENZY_PLANT);
    else if (gSpecialVar_0x8005 == MOVETUTOR_BLAST_BURN)
        FlagSet(FLAG_KANTO_TUTOR_BLAST_BURN);
    else
        FlagSet(FLAG_KANTO_TUTOR_HYDRO_CANNON);
    if (FlagGet(FLAG_KANTO_TUTOR_FRENZY_PLANT) == TRUE)
        r4++;
    if (FlagGet(FLAG_KANTO_TUTOR_BLAST_BURN) == TRUE)
        r4++;
    if (FlagGet(FLAG_KANTO_TUTOR_HYDRO_CANNON) == TRUE)
        r4++;
    if (r4 == 3)
        return TRUE;
    else
        return FALSE;
}

// berry_powder.c de RF : HasEnoughBerryPowder / TakeBerryPowder d'Émeraude lisent déjà gSpecialVar_0x8004
u16 Script_HasEnoughBerryPowder(void)
{
    return HasEnoughBerryPowder();
}

u16 Script_TakeBerryPowder(void)
{
    return TakeBerryPowder();
}

// item.c
void RegisteredItemHandleBikeSwap(void)
{
    switch (gSaveBlock1Ptr->registeredItem)
    {
    case ITEM_MACH_BIKE:
        gSaveBlock1Ptr->registeredItem = ITEM_ACRO_BIKE;
        break;
    case ITEM_ACRO_BIKE:
        gSaveBlock1Ptr->registeredItem = ITEM_MACH_BIKE;
        break;
    }
}

// save_location.c
void SetPostgameFlags(void)
{
    gSaveBlock2Ptr->specialSaveWarpFlags |= CHAMPION_SAVEWARP;
    gSaveBlock2Ptr->gcnLinkFlags |= (1 << 1);
    gSaveBlock2Ptr->gcnLinkFlags |= (1 << 2);
    gSaveBlock2Ptr->gcnLinkFlags |= (1 << 3);
    gSaveBlock2Ptr->gcnLinkFlags |= (1 << 15);
}

// overworld.c : argent perdu après un K.O. (texte de white_out.inc)
static const u8 sWhiteOutMoneyLossMultipliers[] = {
     2,
     4,
     6,
     9,
    12,
    16,
    20,
    25,
    30
};

static const u16 sWhiteOutMoneyLossBadgeFlagIDs[] = {
    FLAG_KANTO_BADGE01_GET,
    FLAG_KANTO_BADGE02_GET,
    FLAG_KANTO_BADGE03_GET,
    FLAG_KANTO_BADGE04_GET,
    FLAG_KANTO_BADGE05_GET,
    FLAG_KANTO_BADGE06_GET,
    FLAG_KANTO_BADGE07_GET,
    FLAG_KANTO_BADGE08_GET
};

static u8 CountBadgesForOverworldWhiteOutLossCalculation(void)
{
    int i;
    u8 nbadges = 0;
    for (i = 0; i < ARRAY_COUNT(sWhiteOutMoneyLossBadgeFlagIDs); i++)
    {
        if (FlagGet(sWhiteOutMoneyLossBadgeFlagIDs[i]))
            nbadges++;
    }
    return nbadges;
}

// pokemon.c de RF
static u8 GetPlayerPartyHighestLevel(void)
{
    s32 slot;
    u8 level, monLevel;

    level = 1;
    for (slot = 0; slot < PARTY_SIZE; ++slot)
    {
        if (GetMonData(&gPlayerParty[slot], MON_DATA_SANITY_HAS_SPECIES, NULL) == 1 && !GetMonData(&gPlayerParty[slot], MON_DATA_SANITY_IS_EGG, NULL))
        {
            monLevel = GetMonData(&gPlayerParty[slot], MON_DATA_LEVEL, NULL);
            if (monLevel > level)
                level = monLevel;
        }
    }
    return level;
}

u32 ComputeWhiteOutMoneyLoss(void)
{
    u8 nbadges = CountBadgesForOverworldWhiteOutLossCalculation();
    u8 toplevel = GetPlayerPartyHighestLevel();
    u32 losings = toplevel * 4 * sWhiteOutMoneyLossMultipliers[nbadges];
    u32 money = GetMoney(&gSaveBlock1Ptr->money);
    if (losings > money)
        losings = money;
    return losings;
}

void OverworldWhiteOutGetMoneyLoss(void)
{
    u32 losings = ComputeWhiteOutMoneyLoss();
    ConvertIntToDecimalStringN(gStringVar1, losings, STR_CONV_MODE_LEFT_ALIGN, CountDigits(losings));
}

// hof_pc.c : RF ouvre son propre écran (CB2_InitHofPC) ; ici celui d'Émeraude (CB2_DoHallOfFamePC),
// en attendant le choix des graphismes en options.
static void Task_WaitFadeAndSetCallback(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2(CB2_DoHallOfFamePC);
    }
}

void HallOfFamePCBeginFade(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    LockPlayerFieldControls();
    CreateTask(Task_WaitFadeAndSetCallback, 0);
}

// party_menu_specials.c : RF ouvre son résumé en PSS_MODE_FORGET_MOVE ; même rôle que
// MoveDeleterChooseMoveToForget d'Émeraude (résumé en SUMMARY_MODE_SELECT_MOVE)
void SelectMoveDeleterMove(void)
{
    MoveDeleterChooseMoveToForget();
}

// start_menu.c : Field_AskSaveTheGame de RF = special SaveGame d'Émeraude (même dialogue de sauvegarde)
void Field_AskSaveTheGame(void)
{
    SaveGame();
}

// script_menu.c : CreatePCMenu de RF = ScriptMenu_CreatePCMultichoice d'Émeraude
u16 CreatePCMenu(void)
{
    return ScriptMenu_CreatePCMultichoice();
}

// seagallop.c
u16 IsPlayerLeftOfVermilionSailor(void)
{
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_VERMILION_CITY)
       && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_VERMILION_CITY)
       && gSaveBlock1Ptr->pos.x < 24)
        return TRUE;

    return FALSE;
}

// field_specials.c
u16 GetSeagallopNumber(void)
{
    u16 originId, destId;

    originId = gSpecialVar_0x8004;
    destId = gSpecialVar_0x8006;

    if (originId == SEAGALLOP_CINNABAR_ISLAND || destId == SEAGALLOP_CINNABAR_ISLAND)
        return 1;

    if (originId == SEAGALLOP_VERMILION_CITY || destId == SEAGALLOP_VERMILION_CITY)
        return 7;

    if (originId == SEAGALLOP_NAVEL_ROCK || destId == SEAGALLOP_NAVEL_ROCK)
        return 10;

    if (originId == SEAGALLOP_BIRTH_ISLAND || destId == SEAGALLOP_BIRTH_ISLAND)
        return 12;

    if ((originId == SEAGALLOP_ONE_ISLAND
      || originId == SEAGALLOP_TWO_ISLAND
      || originId == SEAGALLOP_THREE_ISLAND)
      && (destId == SEAGALLOP_ONE_ISLAND
       || destId == SEAGALLOP_TWO_ISLAND
       || destId == SEAGALLOP_THREE_ISLAND))
        return 2;

    if ((originId == SEAGALLOP_FOUR_ISLAND
      || originId == SEAGALLOP_FIVE_ISLAND)
      && (destId == SEAGALLOP_FOUR_ISLAND
       || destId == SEAGALLOP_FIVE_ISLAND))
        return 3;

    if ((originId == SEAGALLOP_SIX_ISLAND
      || originId == SEAGALLOP_SEVEN_ISLAND)
      && (destId == SEAGALLOP_SIX_ISLAND
       || destId == SEAGALLOP_SEVEN_ISLAND))
        return 5;

    return 6;
}
