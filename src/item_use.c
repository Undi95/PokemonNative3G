#include "global.h"
#include "fusion_events.h" // PokemonNative3G : POKé MONTURE
#include "region_map.h"
#include "overworld.h"
#include "constants/moves.h"
#include "kanto_vs_seeker.h"
void ItemUseOnFieldCB_Itemfinder(u8 taskId); // Rouge Feu (kanto_itemfinder.c)
#include "constants/map_types.h"
#include "item_use.h"
#include "battle.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "berry.h"
#include "berry_powder.h"
#include "bike.h"
#include "coins.h"
#include "data.h"
#include "event_data.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "mail.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "constants/event_bg.h"
#include "constants/event_objects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/songs.h"

static void SetUpItemUseCallback(u8);
static void FieldCB_UseItemOnField(void);
static void Task_CallItemUseOnFieldCallback(u8);
static void Task_OpenRegisteredPokeblockCase(u8);
static void ItemUseOnFieldCB_Bike(u8);
static void ItemUseOnFieldCB_Rod(u8);
static void ItemUseOnFieldCB_Berry(u8);
static void ItemUseOnFieldCB_WailmerPailBerry(u8);
static void ItemUseOnFieldCB_WailmerPailSudowoodo(u8);
static bool8 TryToWaterSudowoodo(void);
static void BootUpSoundTMHM(u8);
static void Task_ShowTMHMContainedMessage(u8);
static void UseTMHMYesNo(u8);
static void UseTMHM(u8);
static void Task_StartUseRepel(u8);
static void Task_UseRepel(u8);
static void Task_CloseCantUseKeyItemMessage(u8);
static void CB2_OpenPokeblockFromBag(void);

// EWRAM variables
EWRAM_DATA static TaskFunc sItemUseOnFieldCB = NULL;

// Below is set TRUE by UseRegisteredKeyItemOnField
#define tUsingRegisteredKeyItem  data[3]

// UB here if an item with type ITEM_USE_MAIL or ITEM_USE_BAG_MENU uses SetUpItemUseCallback
// Never occurs in vanilla, but can occur with improperly created items
static const MainCallback sItemUseCallbacks[] =
{
    [ITEM_USE_PARTY_MENU - 1]  = CB2_ShowPartyMenuForItemUse,
    [ITEM_USE_FIELD - 1]       = CB2_ReturnToField,
    [ITEM_USE_PBLOCK_CASE - 1] = NULL,
};


static const struct YesNoFuncTable sUseTMHMYesNoFuncTable =
{
    .yesFunc = UseTMHM,
    .noFunc = CloseItemMessage,
};

#define tEnigmaBerryType data[4]
static void SetUpItemUseCallback(u8 taskId)
{
    u8 type;
    if (gSpecialVar_ItemId == ITEM_ENIGMA_BERRY)
        type = gTasks[taskId].tEnigmaBerryType - 1;
    else
        type = GetItemType(gSpecialVar_ItemId) - 1;
    if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
    {
        SetBagMenuNewScreenCallback(sItemUseCallbacks[type]);
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        gPyramidBagMenu->newScreenCallback = sItemUseCallbacks[type];
        CloseBattlePyramidBag(taskId);
    }
}

static void SetUpItemUseOnFieldCallback(u8 taskId)
{
    if (gTasks[taskId].tUsingRegisteredKeyItem != TRUE)
    {
        gFieldCallback = FieldCB_UseItemOnField;
        SetUpItemUseCallback(taskId);
    }
    else
    {
        sItemUseOnFieldCB(taskId);
    }
}

static void FieldCB_UseItemOnField(void)
{
    FadeInFromBlack();
    CreateTask(Task_CallItemUseOnFieldCallback, 8);
}

static void Task_CallItemUseOnFieldCallback(u8 taskId)
{
    if (IsWeatherNotFadingIn() == 1)
        sItemUseOnFieldCB(taskId);
}

static void DisplayCannotUseItemMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField, const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    if (!isUsingRegisteredKeyItemOnField)
    {
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, CloseItemMessage);
        else
            DisplayItemMessageInBattlePyramid(taskId, gText_DadsAdvice, Task_CloseBattlePyramidBagMessage);
    }
    else
    {
        DisplayItemMessageOnField(taskId, gStringVar4, Task_CloseCantUseKeyItemMessage);
    }
}

static void DisplayDadsAdviceCannotUseItemMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField)
{
    DisplayCannotUseItemMessage(taskId, isUsingRegisteredKeyItemOnField, gText_DadsAdvice);
}

static void DisplayCannotDismountBikeMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField)
{
    DisplayCannotUseItemMessage(taskId, isUsingRegisteredKeyItemOnField, gText_CantDismountBike);
}

static void Task_CloseCantUseKeyItemMessage(u8 taskId)
{
    ClearDialogWindowAndFrame(0, TRUE);
    DestroyTask(taskId);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
}

u8 CheckIfItemIsTMHMOrEvolutionStone(u16 itemId)
{
    if (GetItemFieldFunc(itemId) == ItemUseOutOfBattle_TMHM)
        return ITEM_IS_TM_HM;
    else if (GetItemFieldFunc(itemId) == ItemUseOutOfBattle_EvolutionStone)
        return ITEM_IS_EVOLUTION_STONE;
    else
        return ITEM_IS_OTHER;
}

// Mail in the bag menu can't have a message but it can be checked (view the mail background, no message)
static void CB2_CheckMail(void)
{
    struct Mail mail;
    mail.itemId = gSpecialVar_ItemId;
    ReadMail(&mail, CB2_ReturnToBagMenuPocket, FALSE);
}

void ItemUseOutOfBattle_Mail(u8 taskId)
{
    SetBagMenuNewScreenCallback(CB2_CheckMail);
    Task_FadeAndCloseBagMenu(taskId);
}

void ItemUseOutOfBattle_Bike(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s16 coordsY;
    s16 coordsX;
    u8 behavior;
    PlayerGetDestCoords(&coordsX, &coordsY);
    behavior = MapGridGetMetatileBehaviorAt(coordsX, coordsY);
    if (FlagGet(FLAG_SYS_CYCLING_ROAD) == TRUE || FlagGet(FLAG_KANTO_SYS_ON_CYCLING_ROAD) == TRUE // Rouge Feu
     || MetatileBehavior_IsVerticalRail(behavior) == TRUE || MetatileBehavior_IsHorizontalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedVerticalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedHorizontalRail(behavior) == TRUE)
    {
        DisplayCannotDismountBikeMessage(taskId, tUsingRegisteredKeyItem);
    }
    else if (Overworld_IsBikingAllowed() == TRUE && IsBikingDisallowedByPlayer() == 0)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_Bike;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, tUsingRegisteredKeyItem);
    }
}

static void ItemUseOnFieldCB_Bike(u8 taskId)
{
    if (GetItemSecondaryId(gSpecialVar_ItemId) == MACH_BIKE)
        GetOnOffBike(PLAYER_AVATAR_FLAG_MACH_BIKE);
    else // ACRO_BIKE
        GetOnOffBike(PLAYER_AVATAR_FLAG_ACRO_BIKE);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
    DestroyTask(taskId);
}

static bool32 CanFish(void)
{
    s16 x, y;
    u16 tileBehavior;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (MetatileBehavior_IsWaterfall(tileBehavior))
        return FALSE;

    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_UNDERWATER))
        return FALSE;

    if (!TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        if (IsPlayerFacingSurfableFishableWater())
            return TRUE;
    }
    else
    {
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior) && MapGridGetCollisionAt(x, y) == 0)
            return TRUE;
        if (MetatileBehavior_IsBridgeOverWaterNoEdge(tileBehavior) == TRUE)
            return TRUE;
    }

    return FALSE;
}

void ItemUseOutOfBattle_Rod(u8 taskId)
{
    if (CanFish() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_Rod;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}

static void ItemUseOnFieldCB_Rod(u8 taskId)
{
    StartFishing(GetItemSecondaryId(gSpecialVar_ItemId));
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_Itemfinder(u8 var)
{
    IncrementGameStat(GAME_STAT_USED_ITEMFINDER);
    sItemUseOnFieldCB = ItemUseOnFieldCB_Itemfinder; // Rouge Feu, dans tout le jeu (flèches vers l'objet)
    SetUpItemUseOnFieldCallback(var);
}

void ItemUseOutOfBattle_PokeblockCase(u8 taskId)
{
    if (MenuHelpers_IsLinkActive() == TRUE)
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
    else if (gTasks[taskId].tUsingRegisteredKeyItem != TRUE)
    {
        SetBagMenuNewScreenCallback(CB2_OpenPokeblockFromBag);
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        gFieldCallback = FieldCB_ReturnToFieldNoScript;
        FadeScreen(FADE_TO_BLACK, 0);
        gTasks[taskId].func = Task_OpenRegisteredPokeblockCase;
    }
}

static void CB2_OpenPokeblockFromBag(void)
{
    OpenPokeblockCase(PBLOCK_CASE_FIELD, CB2_ReturnToBagMenuPocket);
}

static void Task_OpenRegisteredPokeblockCase(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        OpenPokeblockCase(PBLOCK_CASE_FIELD, CB2_ReturnToField);
        DestroyTask(taskId);
    }
}

void ItemUseOutOfBattle_CoinCase(u8 taskId)
{
    ConvertIntToDecimalStringN(gStringVar1, GetCoins(), STR_CONV_MODE_LEFT_ALIGN, 4);
    StringExpandPlaceholders(gStringVar4, gText_CoinCase);

    if (!gTasks[taskId].tUsingRegisteredKeyItem)
    {
        DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, CloseItemMessage);
    }
    else
    {
        DisplayItemMessageOnField(taskId, gStringVar4, Task_CloseCantUseKeyItemMessage);
    }
}

void ItemUseOutOfBattle_PowderJar(u8 taskId)
{
    ConvertIntToDecimalStringN(gStringVar1, GetBerryPowder(), STR_CONV_MODE_LEFT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, gText_PowderQty);

    if (!gTasks[taskId].tUsingRegisteredKeyItem)
    {
        DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, CloseItemMessage);
    }
    else
    {
        DisplayItemMessageOnField(taskId, gStringVar4, Task_CloseCantUseKeyItemMessage);
    }
}

void ItemUseOutOfBattle_Berry(u8 taskId)
{
    if (IsPlayerFacingEmptyBerryTreePatch() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_Berry;
        gFieldCallback = FieldCB_UseItemOnField;
        SetBagMenuNewScreenCallback(CB2_ReturnToField);
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        GetItemFieldFunc(gSpecialVar_ItemId)(taskId);
    }
}

static void ItemUseOnFieldCB_Berry(u8 taskId)
{
    RemoveBagItem(gSpecialVar_ItemId, 1);
    LockPlayerFieldControls();
    ScriptContext_SetupScript(BerryTree_EventScript_ItemUsePlantBerry);
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_WailmerPail(u8 taskId)
{
    if (TryToWaterSudowoodo() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_WailmerPailSudowoodo;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else if (TryToWaterBerryTree() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_WailmerPailBerry;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}

static void ItemUseOnFieldCB_WailmerPailBerry(u8 taskId)
{
    LockPlayerFieldControls();
    ScriptContext_SetupScript(BerryTree_EventScript_ItemUseWailmerPail);
    DestroyTask(taskId);
}

static bool8 TryToWaterSudowoodo(void)
{
    s16 x, y;
    u8 elevation;
    u8 objId;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    elevation = PlayerGetElevation();
    objId = GetObjectEventIdByPosition(x, y, elevation);
    if (objId == OBJECT_EVENTS_COUNT || gObjectEvents[objId].graphicsId != OBJ_EVENT_GFX_SUDOWOODO)
        return FALSE;
    else
        return TRUE;
}

static void ItemUseOnFieldCB_WailmerPailSudowoodo(u8 taskId)
{
    LockPlayerFieldControls();
    ScriptContext_SetupScript(BattleFrontier_OutsideEast_EventScript_WaterSudowoodo);
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_Medicine(u8 taskId)
{
    gItemUseCB = gSaveBlock2Ptr->optionsBagStyle ? KantoItemUseCB_Medicine : ItemUseCB_Medicine; // sac de RF : scène de RF
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_ReduceEV(u8 taskId)
{
    gItemUseCB = ItemUseCB_ReduceEV;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_SacredAsh(u8 taskId)
{
    gItemUseCB = ItemUseCB_SacredAsh;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_PPRecovery(u8 taskId)
{
    gItemUseCB = ItemUseCB_PPRecovery;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_PPUp(u8 taskId)
{
    gItemUseCB = ItemUseCB_PPUp;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_RareCandy(u8 taskId)
{
    gItemUseCB = gSaveBlock2Ptr->optionsBagStyle ? KantoItemUseCB_RareCandy : ItemUseCB_RareCandy; // sac de RF : scène de RF
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_TMHM(u8 taskId)
{
    if (gSpecialVar_ItemId >= ITEM_HM01)
        DisplayItemMessage(taskId, FONT_NORMAL, gText_BootedUpHM, BootUpSoundTMHM); // HM
    else
        DisplayItemMessage(taskId, FONT_NORMAL, gText_BootedUpTM, BootUpSoundTMHM); // TM
}

static void BootUpSoundTMHM(u8 taskId)
{
    PlaySE(SE_PC_LOGIN);
    gTasks[taskId].func = Task_ShowTMHMContainedMessage;
}

static void Task_ShowTMHMContainedMessage(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        StringCopy(gStringVar1, gMoveNames[ItemIdToBattleMoveId(gSpecialVar_ItemId)]);
        StringExpandPlaceholders(gStringVar4, gText_TMHMContainedVar1);
        DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, UseTMHMYesNo);
    }
}

static void UseTMHMYesNo(u8 taskId)
{
    BagMenu_YesNo(taskId, ITEMWIN_YESNO_HIGH, &sUseTMHMYesNoFuncTable);
}

static void UseTMHM(u8 taskId)
{
    gItemUseCB = gSaveBlock2Ptr->optionsBagStyle ? KantoItemUseCB_TMHM : ItemUseCB_TMHM; // sac de RF : scène de RF
    SetUpItemUseCallback(taskId);
}

static void RemoveUsedItem(void)
{
    RemoveBagItem(gSpecialVar_ItemId, 1);
    CopyItemName(gSpecialVar_ItemId, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gText_PlayerUsedVar2);
    if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
    {
        UpdatePocketItemList(GetItemPocket(gSpecialVar_ItemId));
        UpdatePocketListPosition(GetItemPocket(gSpecialVar_ItemId));
    }
    else
    {
        UpdatePyramidBagList();
        UpdatePyramidBagCursorPos();
    }
}

void ItemUseOutOfBattle_Repel(u8 taskId)
{
    if (VarGet(VAR_REPEL_STEP_COUNT) == 0)
        gTasks[taskId].func = Task_StartUseRepel;
    else if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
        DisplayItemMessage(taskId, FONT_NORMAL, gText_RepelEffectsLingered, CloseItemMessage);
    else
        DisplayItemMessageInBattlePyramid(taskId, gText_RepelEffectsLingered, Task_CloseBattlePyramidBagMessage);
}

static void Task_StartUseRepel(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (++data[8] > 7)
    {
        data[8] = 0;
        PlaySE(SE_REPEL);
        gTasks[taskId].func = Task_UseRepel;
    }
}

static void Task_UseRepel(u8 taskId)
{
    if (!IsSEPlaying())
    {
        VarSet(VAR_REPEL_STEP_COUNT, GetItemHoldEffectParam(gSpecialVar_ItemId));
        VarSet(VAR_AUTO_REPEL_LAST, gSpecialVar_ItemId); // PokemonNative3G : AUTO-REPOUSSE
        RemoveUsedItem();
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, CloseItemMessage);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, Task_CloseBattlePyramidBagMessage);
    }
}

static void Task_UsedBlackWhiteFlute(u8 taskId)
{
    if(++gTasks[taskId].data[8] > 7)
    {
        PlaySE(SE_GLASS_FLUTE);
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, CloseItemMessage);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, Task_CloseBattlePyramidBagMessage);
    }
}

void ItemUseOutOfBattle_BlackWhiteFlute(u8 taskId)
{
    CopyItemName(gSpecialVar_ItemId, gStringVar2);
    if (gSpecialVar_ItemId == ITEM_WHITE_FLUTE)
    {
        FlagSet(FLAG_SYS_ENC_UP_ITEM);
        FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
        StringExpandPlaceholders(gStringVar4, gText_UsedVar2WildLured);
    }
    else
    {
        FlagSet(FLAG_SYS_ENC_DOWN_ITEM);
        FlagClear(FLAG_SYS_ENC_UP_ITEM);
        StringExpandPlaceholders(gStringVar4, gText_UsedVar2WildRepelled);
    }
    gTasks[taskId].data[8] = 0;
    gTasks[taskId].func = Task_UsedBlackWhiteFlute;
}

void Task_UseDigEscapeRopeOnField(u8 taskId)
{
    ResetInitialPlayerAvatarState();
    StartEscapeRopeFieldEffect();
    DestroyTask(taskId);
}

static void ItemUseOnFieldCB_EscapeRope(u8 taskId)
{
    Overworld_ResetStateAfterDigEscRope();
    RemoveUsedItem();
    gTasks[taskId].data[0] = 0;
    DisplayItemMessageOnField(taskId, gStringVar4, Task_UseDigEscapeRopeOnField);
}

bool8 CanUseDigOrEscapeRopeOnCurMap(void)
{
    if (gMapHeader.allowEscaping)
        return TRUE;
    else
        return FALSE;
}

void ItemUseOutOfBattle_EscapeRope(u8 taskId)
{
    if (CanUseDigOrEscapeRopeOnCurMap() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_EscapeRope;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}

// PokemonNative3G : POKé MONTURE (remplace les CS données à Kanto, fusion_events.c). Depuis le sac : FLASH dans une
// grotte sombre, sinon VOL ; les autres capacités se déclenchent en interagissant (arbre, eau, rocher…).
static void ItemUseOnFieldCB_PokeMontureFlash(u8 taskId)
{
    DestroyTask(taskId);
    PokeMonture_StartFlash();
}

void ItemUseOutOfBattle_PokeMonture(u8 taskId)
{
    if (PokeMonture_CanUse(MOVE_FLASH) && HasBadgeForFieldMove(FIELD_MOVE_FLASH)
     && gMapHeader.cave == TRUE && !FlagGet(FLAG_SYS_USE_FLASH))
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_PokeMontureFlash;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else if (PokeMonture_CanUse(MOVE_FLY) && HasBadgeForFieldMove(FIELD_MOVE_FLY)
          && Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE
          && !gTasks[taskId].tUsingRegisteredKeyItem)
    {
        PokeMonture_SetMove(MOVE_FLY);
        gPartyMenu.slotId = FIELD_MOVE_HELPER_SLOT;
        SetBagMenuNewScreenCallback(CB2_OpenFlyMapOfRegion);
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}

// PokemonNative3G : CÂBLE LINK, évolution par échange en solo
void ItemUseOutOfBattle_LinkCable(u8 taskId)
{
    gItemUseCB = ItemUseCB_LinkCable;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_EvolutionStone(u8 taskId)
{
    gItemUseCB = gSaveBlock2Ptr->optionsBagStyle ? KantoItemUseCB_EvolutionStone : ItemUseCB_EvolutionStone; // sac de RF : scène de RF
    SetUpItemUseCallback(taskId);
}

void ItemUseInBattle_PokeBall(u8 taskId)
{
    if (IsPlayerPartyAndPokemonStorageFull() == FALSE) // have room for mon?
    {
        RemoveBagItem(gSpecialVar_ItemId, 1);
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            Task_FadeAndCloseBagMenu(taskId);
        else
            CloseBattlePyramidBag(taskId);
    }
    else if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
    {
        DisplayItemMessage(taskId, FONT_NORMAL, gText_BoxFull, CloseItemMessage);
    }
    else
    {
        DisplayItemMessageInBattlePyramid(taskId, gText_BoxFull, Task_CloseBattlePyramidBagMessage);
    }
}

static void Task_CloseStatIncreaseMessage(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            Task_FadeAndCloseBagMenu(taskId);
        else
            CloseBattlePyramidBag(taskId);
    }
}

static void Task_UseStatIncreaseItem(u8 taskId)
{
    if(++gTasks[taskId].data[8] > 7)
    {
        PlaySE(SE_USE_ITEM);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, UseStatIncreaseItem(gSpecialVar_ItemId), Task_CloseStatIncreaseMessage);
        else
            DisplayItemMessageInBattlePyramid(taskId, UseStatIncreaseItem(gSpecialVar_ItemId), Task_CloseStatIncreaseMessage);
    }
}

// e.g. X Attack, Guard Spec
void ItemUseInBattle_StatIncrease(u8 taskId)
{
    u16 partyId = gBattlerPartyIndexes[gBattlerInMenuId];

    if (ExecuteTableBasedItemEffect(&gPlayerParty[partyId], gSpecialVar_ItemId, partyId, 0) != FALSE)
    {
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, gText_WontHaveEffect, CloseItemMessage);
        else
            DisplayItemMessageInBattlePyramid(taskId, gText_WontHaveEffect, Task_CloseBattlePyramidBagMessage);
    }
    else
    {
        gTasks[taskId].func = Task_UseStatIncreaseItem;
        gTasks[taskId].data[8] = 0;
    }
}

static void ItemUseInBattle_ShowPartyMenu(u8 taskId)
{
    if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
    {
        SetBagMenuNewScreenCallback(ChooseMonForInBattleItem);
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        gPyramidBagMenu->newScreenCallback = ChooseMonForInBattleItem;
        CloseBattlePyramidBag(taskId);
    }
}

void ItemUseInBattle_Medicine(u8 taskId)
{
    gItemUseCB = ItemUseCB_Medicine;
    ItemUseInBattle_ShowPartyMenu(taskId);
}

// Unused. Sacred Ash cannot be used in battle
void ItemUseInBattle_SacredAsh(u8 taskId)
{
    gItemUseCB = ItemUseCB_SacredAsh;
    ItemUseInBattle_ShowPartyMenu(taskId);
}

void ItemUseInBattle_PPRecovery(u8 taskId)
{
    gItemUseCB = ItemUseCB_PPRecovery;
    ItemUseInBattle_ShowPartyMenu(taskId);
}

// Fluffy Tail / Poke Doll
void ItemUseInBattle_Escape(u8 taskId)
{

    if((gBattleTypeFlags & BATTLE_TYPE_TRAINER) == FALSE)
    {
        RemoveUsedItem();
        if (CurrentBattlePyramidLocation() == PYRAMID_LOCATION_NONE)
            DisplayItemMessage(taskId, FONT_NORMAL, gStringVar4, Task_FadeAndCloseBagMenu);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, CloseBattlePyramidBag);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}

void ItemUseOutOfBattle_EnigmaBerry(u8 taskId)
{
    switch (GetItemEffectType(gSpecialVar_ItemId))
    {
    case ITEM_EFFECT_HEAL_HP:
    case ITEM_EFFECT_CURE_POISON:
    case ITEM_EFFECT_CURE_SLEEP:
    case ITEM_EFFECT_CURE_BURN:
    case ITEM_EFFECT_CURE_FREEZE:
    case ITEM_EFFECT_CURE_PARALYSIS:
    case ITEM_EFFECT_CURE_ALL_STATUS:
    case ITEM_EFFECT_ATK_EV:
    case ITEM_EFFECT_HP_EV:
    case ITEM_EFFECT_SPATK_EV:
    case ITEM_EFFECT_SPDEF_EV:
    case ITEM_EFFECT_SPEED_EV:
    case ITEM_EFFECT_DEF_EV:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_PARTY_MENU;
        ItemUseOutOfBattle_Medicine(taskId);
        break;
    case ITEM_EFFECT_SACRED_ASH:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_PARTY_MENU;
        ItemUseOutOfBattle_SacredAsh(taskId);
        break;
    case ITEM_EFFECT_RAISE_LEVEL:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_PARTY_MENU;
        ItemUseOutOfBattle_RareCandy(taskId);
        break;
    case ITEM_EFFECT_PP_UP:
    case ITEM_EFFECT_PP_MAX:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_PARTY_MENU;
        ItemUseOutOfBattle_PPUp(taskId);
        break;
    case ITEM_EFFECT_HEAL_PP:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_PARTY_MENU;
        ItemUseOutOfBattle_PPRecovery(taskId);
        break;
    default:
        gTasks[taskId].tEnigmaBerryType = ITEM_USE_BAG_MENU;
        ItemUseOutOfBattle_CannotUse(taskId);
        break;
    }
}

void ItemUseInBattle_EnigmaBerry(u8 taskId)
{
    switch (GetItemEffectType(gSpecialVar_ItemId))
    {
    case ITEM_EFFECT_X_ITEM:
        ItemUseInBattle_StatIncrease(taskId);
        break;
    case ITEM_EFFECT_HEAL_HP:
    case ITEM_EFFECT_CURE_POISON:
    case ITEM_EFFECT_CURE_SLEEP:
    case ITEM_EFFECT_CURE_BURN:
    case ITEM_EFFECT_CURE_FREEZE:
    case ITEM_EFFECT_CURE_PARALYSIS:
    case ITEM_EFFECT_CURE_ALL_STATUS:
    case ITEM_EFFECT_CURE_CONFUSION:
    case ITEM_EFFECT_CURE_INFATUATION:
        ItemUseInBattle_Medicine(taskId);
        break;
    case ITEM_EFFECT_HEAL_PP:
        ItemUseInBattle_PPRecovery(taskId);
        break;
    default:
        ItemUseOutOfBattle_CannotUse(taskId);
        break;
    }
}

void ItemUseOutOfBattle_CannotUse(u8 taskId)
{
    DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
}

#undef tUsingRegisteredKeyItem

// ---- Rouge Feu (item_use.c) : Cherche VS, sur les routes et dans les villes ----
void ItemUseOutOfBattle_VsSeeker(u8 taskId)
{
    if ((gMapHeader.mapType != MAP_TYPE_ROUTE
      && gMapHeader.mapType != MAP_TYPE_TOWN
      && gMapHeader.mapType != MAP_TYPE_CITY)
     || (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_VIRIDIAN_FOREST)
      && (gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_VIRIDIAN_FOREST)
       || gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_MT_EMBER_EXTERIOR)
       || gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_THREE_ISLAND_BERRY_FOREST)
       || gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_SIX_ISLAND_PATTERN_BUSH))))
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
    }
    else
    {
        sItemUseOnFieldCB = Task_VsSeeker_0;
        SetUpItemUseOnFieldCallback(taskId);
    }
}

void Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker(u8 taskId)
{
    Task_CloseCantUseKeyItemMessage(taskId);
}

// ---- Rouge Feu (item_use.c) : Poké Flûte (réveille les Pokémon endormis de l'équipe) ----
static const u8 sKText_PlayedPokeFluteCatchy[] = _("Vous jouez de la POKéFLUTE.\pSuper!!! Ça c'est du refrain!{PAUSE_UNTIL_PRESS}");
static const u8 sKText_PlayedPokeFlute[] = _("Vous jouez de la POKéFLUTE.");
static const u8 sKText_PokeFluteAwakenedMon[] = _("La POKéFLUTE a réveillé le\nPOKéMON endormi.");
static void Task_PlayPokeFlute(u8 taskId);
static void Task_DisplayPokeFluteMessage(u8 taskId);

void ItemUseOutOfBattle_PokeFlute(u8 taskId)
{
    bool8 wokeSomeoneUp = FALSE;
    u8 i;

    for (i = 0; i < CalculatePlayerPartyCount(); i++)
    {
        if (!ExecuteTableBasedItemEffect(&gPlayerParty[i], ITEM_AWAKENING, i, 0))
            wokeSomeoneUp = TRUE;
    }

    if (wokeSomeoneUp)
    {
        if (!gTasks[taskId].data[3] /* tUsingRegisteredKeyItem */)
            DisplayItemMessage(taskId, FONT_NORMAL, sKText_PlayedPokeFlute, Task_PlayPokeFlute);
        else
            DisplayItemMessageOnField(taskId, sKText_PlayedPokeFlute, Task_PlayPokeFlute);
    }
    else
    {
        if (!gTasks[taskId].data[3] /* tUsingRegisteredKeyItem */)
            DisplayItemMessage(taskId, FONT_NORMAL, sKText_PlayedPokeFluteCatchy, CloseItemMessage);
        else
            DisplayItemMessageOnField(taskId, sKText_PlayedPokeFluteCatchy, Task_CloseCantUseKeyItemMessage);
    }
}

static void Task_PlayPokeFlute(u8 taskId)
{
    PlayFanfareByFanfareNum(FANFARE_RG_POKE_FLUTE);
    gTasks[taskId].func = Task_DisplayPokeFluteMessage;
}

static void Task_DisplayPokeFluteMessage(u8 taskId)
{
    if (WaitFanfare(FALSE))
    {
        if (!gTasks[taskId].data[3] /* tUsingRegisteredKeyItem */)
            DisplayItemMessage(taskId, FONT_NORMAL, sKText_PokeFluteAwakenedMon, CloseItemMessage);
        else
            DisplayItemMessageOnField(taskId, sKText_PokeFluteAwakenedMon, Task_CloseCantUseKeyItemMessage);
    }
}

// Rouge Feu : BattleUseFunc_PokeFlute (le combat joue BattleScript_UsePokeFlute)
void ItemUseInBattle_PokeFlute(u8 taskId)
{
    Task_FadeAndCloseBagMenu(taskId);
}
