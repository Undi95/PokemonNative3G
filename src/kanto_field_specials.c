// Specials de Rouge Feu portés depuis le décomp RF (field_specials.c, fame_checker.c, quest_log.c).
#include "global.h"
#include "constants/event_objects.h"
#include "constants/kanto_event_objects.h"
#include "constants/easy_chat.h"
#include "random.h"
#include "easy_chat.h"
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
#include "text.h"

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

// field_specials.c (RF)
static EWRAM_DATA u8 sBrailleTextCursorSpriteID = 0;

void BrailleCursorToggle(void)
{
    // 8004 = x - 27
    // 8005 = y
    // 8006 = action (0 = create, 1 = delete)
    u16 x;
    // PokemonNative3G : la position est celle de la boîte de dialogue de RF (option DIALOGUE = KANTO) ;
    // dans la fenêtre d'Émeraude, pas de flèche, comme dans Émeraude
    if (IsBrailleInDialogueBox())
    {
        x = gSpecialVar_0x8004 + 27;
        if (gSpecialVar_0x8006 == 0)
            sBrailleTextCursorSpriteID = CreateTextCursorSprite(0, x, gSpecialVar_0x8005, 0, 0);
        else
            DestroyTextCursorSprite(sBrailleTextCursorSpriteID);
    }
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
    Overworld_SetSavedMusic(MUS_RG_CYCLING); // MUS_CYCLING de RF (MUS_CYCLING d'Émeraude : le vélo de Hoenn)
    Overworld_ChangeMusicTo(MUS_RG_CYCLING);
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

// ---- Rouge Feu (easy_chat.c) ----
// ShowEasyChatMessage : le ShowEasyChatProfile d'Émeraude sous son nom de RF (club Mystery Event)
void ShowEasyChatProfile(void); // easy_chat.c (special d'Émeraude, sans déclaration)
void ShowEasyChatMessage(void)
{
    ShowEasyChatProfile();
}

// GetRandomWordFromAnyGroup de RF = GetRandomEasyChatWordFromUnlockedGroup d'Émeraude (aucun script de RF ne l'appelle)
void BufferRandomHobbyOrLifestyleString(void)
{
    int groupId = Random() & 1 ? EC_GROUP_HOBBIES : EC_GROUP_LIFESTYLE;
    u16 easyChatWord = GetRandomEasyChatWordFromUnlockedGroup(groupId);
    CopyEasyChatWord(gStringVar2, easyChatWord);
}

// ---- PokemonNative3G : couleur du texte des PNJ de Rouge Feu (field_specials.c, dynamic_placeholder_text_util.c de RF) ----
// Avec l'option DIALOGUE = KANTO : texte bleu (homme), rouge (femme) ou gris (Pokémon, objets, panneaux). Seuls les sprites
// de Rouge Feu ont une couleur dans la table ; ceux d'Émeraude restent neutres.
// Indices = sprites de RF (OBJ_EVENT_GFX_KANTO_x - KANTO_OBJ_EVENT_GFX_START) ; certains ne sont pas importés.
#define COLORS(a, b)((a) | (b << 4))

static const u8 sTextColorTable[] =
{
 // [LOW_NYBBLE / 2]                            = 0xXY, // HIGH_NYBBLE
    [0 / 2] /* RED_NORMAL */              = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // RED_BIKE
    [2 / 2] /* RED_SURF */                = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // RED_FIELD_MOVE
    [4 / 2] /* RED_FISH */                = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // RED_VS_SEEKER
    [6 / 2] /* RED_VS_SEEKER_BIKE */      = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // GREEN_NORMAL
    [8 / 2] /* GREEN_BIKE */              = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // GREEN_SURF
    [10 / 2] /* GREEN_FIELD_MOVE */        = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // GREEN_FISH
    [12 / 2] /* GREEN_VS_SEEKER */         = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // GREEN_VS_SEEKER_BIKE
    [14 / 2] /* RS_BRENDAN */              = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // RS_MAY
    [16 / 2] /* LITTLE_BOY */              = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // LITTLE_GIRL
    [18 / 2] /* YOUNGSTER */               = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // BOY
    [20 / 2] /* BUG_CATCHER */             = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // SITTING_BOY
    [22 / 2] /* LASS */                    = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // WOMAN_1
    [24 / 2] /* CRUSH_GIRL */             = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // MAN
    [26 / 2] /* ROCKER */                  = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // FAT_MAN
    [28 / 2] /* WOMAN_2 */                 = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // BEAUTY
    [30 / 2] /* BALDING_MAN */             = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // WOMAN_3
    [32 / 2] /* OLD_MAN_1 */               = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // OLD_MAN_2
    [34 / 2] /* OLD_MAN_LYING_DOWN */      = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // OLD_WOMAN
    [36 / 2] /* TUBER_M_WATER */           = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // TUBER_F
    [38 / 2] /* TUBER_M_LAND */            = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // CAMPER
    [40 / 2] /* PICNICKER */               = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // COOLTRAINER_M
    [42 / 2] /* COOLTRAINER_F */           = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // SWIMMER_M_WATER
    [44 / 2] /* SWIMMER_F_WATER */         = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // SWIMMER_M_LAND
    [46 / 2] /* SWIMMER_F_LAND */          = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // WORKER_M
    [48 / 2] /* WORKER_F */                = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // ROCKET_M
    [50 / 2] /* ROCKET_F */                = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // GBA_KID
    [52 / 2] /* POKE_MANIAC */              = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // BIKER
    [54 / 2] /* BLACK_BELT */               = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // SCIENTIST
    [56 / 2] /* HIKER */                   = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // FISHER
    [58 / 2] /* CHANNELER */               = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // CHEF
    [60 / 2] /* POLICEMAN */               = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // GENTLEMAN
    [62 / 2] /* SAILOR */                  = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // CAPTAIN
    [64 / 2] /* NURSE */                   = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // CABLE_CLUB_RECEPTIONIST
    [66 / 2] /* UNION_ROOM_RECEPTIONIST */ = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // UNUSED_MALE_RECEPTIONIST
    [68 / 2] /* CLERK */                   = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // MG_DELIVERYMAN
    [70 / 2] /* TRAINER_TOWER_DUDE */      = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // PROF_OAK
    [72 / 2] /* BLUE */                    = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // BILL
    [74 / 2] /* LANCE */                   = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // AGATHA
    [76 / 2] /* DAISY */                   = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_FEMALE), // LORELEI
    [78 / 2] /* MR_FUJI */                 = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // BRUNO
    [80 / 2] /* BROCK */                   = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // MISTY
    [82 / 2] /* LT_SURGE */                = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // ERIKA
    [84 / 2] /* KOGA */                    = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_FEMALE), // SABRINA
    [86 / 2] /* BLAINE */                  = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // GIOVANNI
    [88 / 2] /* MOM */                     = COLORS(NPC_TEXT_COLOR_FEMALE, NPC_TEXT_COLOR_MALE), // CELIO
    [90 / 2] /* TEACHY_TV_HOST */          = COLORS(NPC_TEXT_COLOR_MALE, NPC_TEXT_COLOR_MALE), // GYM_GUY
    [92 / 2] /* ITEM_BALL */               = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // TOWN_MAP
    [94 / 2] /* POKEDEX */                 = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // CUT_TREE
    [96 / 2] /* ROCK_SMASH_ROCK */         = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // PUSHABLE_BOULDER
    [98 / 2] /* FOSSIL */                  = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // RUBY
    [100 / 2] /* SAPPHIRE */                = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // OLD_AMBER
    [102 / 2] /* GYM_SIGN */                = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // SIGN
    [104 / 2] /* TRAINER_TIPS */            = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // CLIPBOARD
    [106 / 2] /* METEORITE */               = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_NEUTRAL), // LAPRAS_DOLL
    [108 / 2] /* SEAGALLOP */               = COLORS(NPC_TEXT_COLOR_NEUTRAL, NPC_TEXT_COLOR_MON), // SNORLAX
    [110 / 2] /* SPEAROW */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // CUBONE
    [112 / 2] /* POLIWRATH */               = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // CLEFAIRY
    [114 / 2] /* PIDGEOT */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // JIGGLYPUFF
    [116 / 2] /* PIDGEY */                  = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // CHANSEY
    [118 / 2] /* OMANYTE */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // KANGASKHAN
    [120 / 2] /* PIKACHU */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // PSYDUCK
    [122 / 2] /* NIDORAN_F */               = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // NIDORAN_M
    [124 / 2] /* NIDORINO */                = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // MEOWTH
    [126 / 2] /* SEEL */                    = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // VOLTORB
    [128 / 2] /* SLOWPOKE */                = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // SLOWBRO
    [130 / 2] /* MACHOP */                  = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // WIGGLYTUFF
    [132 / 2] /* DODUO */                   = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // FEAROW
    [134 / 2] /* MACHOKE */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // LAPRAS
    [136 / 2] /* ZAPDOS */                  = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // MOLTRES
    [138 / 2] /* ARTICUNO */                = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // MEWTWO
    [140 / 2] /* MEW */                     = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // ENTEI
    [142 / 2] /* SUICUNE */                 = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // RAIKOU
    [144 / 2] /* LUGIA */                   = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // HO_OH
    [146 / 2] /* CELEBI */                  = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // KABUTO
    [148 / 2] /* DEOXYS_D */                = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_MON), // DEOXYS_A
    [150 / 2] /* DEOXYS_N */                = COLORS(NPC_TEXT_COLOR_MON, NPC_TEXT_COLOR_NEUTRAL), // SS_ANNE
};

#undef COLORS

static u8 GetColorFromTextColorTable(u16 graphicId)
{
    u32 test = graphicId >> 1;
    u32 shift = (graphicId & 1) << 2;

    if (test >= ARRAY_COUNT(sTextColorTable))
        return NPC_TEXT_COLOR_NEUTRAL;
    else
        return (sTextColorTable[graphicId >> 1] >> shift) & 0xF;
}

void ResetContextNpcTextColor(void)
{
    gSelectedObjectEvent = 0;
    gSpecialVar_TextColor = NPC_TEXT_COLOR_DEFAULT;
}

u8 ContextNpcGetTextColor(void)
{
    u16 gfxId;
    if (gSpecialVar_TextColor != NPC_TEXT_COLOR_DEFAULT)
    {
        // A text color has been specified, use that
        return gSpecialVar_TextColor;
    }
    else if (gSelectedObjectEvent == 0)
    {
        // No text color specified and no object selected, use neutral
        return NPC_TEXT_COLOR_NEUTRAL;
    }
    else
    {
        // An object is selected and no color has been specified.
        // Use the text color normally associated with this object's sprite.
        gfxId = gObjectEvents[gSelectedObjectEvent].graphicsId;
        if (gfxId >= OBJ_EVENT_GFX_VARS && gfxId <= OBJ_EVENT_GFX_VARS + 0xF)
            gfxId = VarGetObjectEventGraphicsId(gfxId - OBJ_EVENT_GFX_VARS);
        if (gfxId < KANTO_OBJ_EVENT_GFX_START)
            return NPC_TEXT_COLOR_NEUTRAL; // PokemonNative3G : sprite d'Émeraude
        return GetColorFromTextColorTable(gfxId - KANTO_OBJ_EVENT_GFX_START);
    }
}
