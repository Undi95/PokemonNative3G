// Menu de debug (builds KANTO_DEBUG=1 uniquement), ouvert depuis le menu Start.
// Téléportation, traverser les murs, rencontres sauvages, soin de l'équipe.
#include "global.h"
#include "debug_menu.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "window.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/items.h"
#include "constants/species.h"
#include "event_data.h"
#include "pokemon.h"

bool8 gDebugNoClip = FALSE;
bool8 gDebugNoEncounters = FALSE;

#ifdef KANTO_DEBUG_START

enum {
    DEBUG_WARP,
    DEBUG_NOCLIP,
    DEBUG_ENCOUNTERS,
    DEBUG_HEAL,
    DEBUG_GIVE_MON,
    DEBUG_CLOSE,
    DEBUG_COUNT
};

struct DebugWarp
{
    const u8 *name;
    u8 group, num;
    s8 x, y;
};

static const u8 sWarpName_PalletTown[] = _("BOURG PALETTE");
static const u8 sWarpName_Viridian[] = _("JADIELLE");
static const u8 sWarpName_Pewter[] = _("ARGENTA");
static const u8 sWarpName_Route4[] = _("ROUTE 4");
static const u8 sWarpName_Cerulean[] = _("AZURIA");
static const u8 sWarpName_Route10[] = _("ROUTE 10");
static const u8 sWarpName_Lavender[] = _("LAVANVILLE");
static const u8 sWarpName_Vermilion[] = _("CARMIN SUR MER");
static const u8 sWarpName_Celadon[] = _("CÉLADOPOLE");
static const u8 sWarpName_Saffron[] = _("SAFRANIA");
static const u8 sWarpName_Fuchsia[] = _("PARMANIE");
static const u8 sWarpName_Cinnabar[] = _("CRAMOIS'ÎLE");
static const u8 sWarpName_Indigo[] = _("PLATEAU INDIGO");
static const u8 sWarpName_OneIsland[] = _("ÎLE 1");
static const u8 sWarpName_TwoIsland[] = _("ÎLE 2");
static const u8 sWarpName_ThreeIsland[] = _("ÎLE 3");
static const u8 sWarpName_FourIsland[] = _("ÎLE 4");
static const u8 sWarpName_FiveIsland[] = _("ÎLE 5");
static const u8 sWarpName_SixIsland[] = _("ÎLE 6");
static const u8 sWarpName_SevenIsland[] = _("ÎLE 7");
static const u8 sWarpName_Littleroot[] = _("BOURG-EN-VOL");
static const u8 sWarpName_Lilycove[] = _("NÉNUCRIQUE");

// Kanto : points d'arrivée du Vol de Rouge Feu (heal_locations.json)
static const struct DebugWarp sDebugWarps[] =
{
    {sWarpName_PalletTown, MAP_GROUP(MAP_PALLET_TOWN), MAP_NUM(MAP_PALLET_TOWN), 6, 8},
    {sWarpName_Viridian, MAP_GROUP(MAP_VIRIDIAN_CITY), MAP_NUM(MAP_VIRIDIAN_CITY), 26, 27},
    {sWarpName_Pewter, MAP_GROUP(MAP_PEWTER_CITY), MAP_NUM(MAP_PEWTER_CITY), 17, 26},
    {sWarpName_Route4, MAP_GROUP(MAP_ROUTE4), MAP_NUM(MAP_ROUTE4), 12, 6},
    {sWarpName_Cerulean, MAP_GROUP(MAP_CERULEAN_CITY), MAP_NUM(MAP_CERULEAN_CITY), 22, 20},
    {sWarpName_Route10, MAP_GROUP(MAP_ROUTE10), MAP_NUM(MAP_ROUTE10), 13, 21},
    {sWarpName_Lavender, MAP_GROUP(MAP_LAVENDER_TOWN), MAP_NUM(MAP_LAVENDER_TOWN), 6, 6},
    {sWarpName_Vermilion, MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY), 15, 7},
    {sWarpName_Celadon, MAP_GROUP(MAP_CELADON_CITY), MAP_NUM(MAP_CELADON_CITY), 48, 12},
    {sWarpName_Saffron, MAP_GROUP(MAP_SAFFRON_CITY), MAP_NUM(MAP_SAFFRON_CITY), 24, 39},
    {sWarpName_Fuchsia, MAP_GROUP(MAP_FUCHSIA_CITY), MAP_NUM(MAP_FUCHSIA_CITY), 25, 32},
    {sWarpName_Cinnabar, MAP_GROUP(MAP_CINNABAR_ISLAND), MAP_NUM(MAP_CINNABAR_ISLAND), 14, 12},
    {sWarpName_Indigo, MAP_GROUP(MAP_INDIGO_PLATEAU_EXTERIOR), MAP_NUM(MAP_INDIGO_PLATEAU_EXTERIOR), 11, 7},
    {sWarpName_OneIsland, MAP_GROUP(MAP_ONE_ISLAND), MAP_NUM(MAP_ONE_ISLAND), 14, 6},
    {sWarpName_TwoIsland, MAP_GROUP(MAP_TWO_ISLAND), MAP_NUM(MAP_TWO_ISLAND), 21, 8},
    {sWarpName_ThreeIsland, MAP_GROUP(MAP_THREE_ISLAND), MAP_NUM(MAP_THREE_ISLAND), 14, 28},
    {sWarpName_FourIsland, MAP_GROUP(MAP_FOUR_ISLAND), MAP_NUM(MAP_FOUR_ISLAND), 18, 21},
    {sWarpName_FiveIsland, MAP_GROUP(MAP_FIVE_ISLAND), MAP_NUM(MAP_FIVE_ISLAND), 18, 7},
    {sWarpName_SixIsland, MAP_GROUP(MAP_SIX_ISLAND), MAP_NUM(MAP_SIX_ISLAND), 11, 12},
    {sWarpName_SevenIsland, MAP_GROUP(MAP_SEVEN_ISLAND), MAP_NUM(MAP_SEVEN_ISLAND), 12, 4},
    {sWarpName_Littleroot, MAP_GROUP(MAP_LITTLEROOT_TOWN), MAP_NUM(MAP_LITTLEROOT_TOWN), 10, 10},
    {sWarpName_Lilycove, MAP_GROUP(MAP_LILYCOVE_CITY), MAP_NUM(MAP_LILYCOVE_CITY), 20, 20},
};

static const u8 sText_Warp[] = _("Téléportation");
static const u8 sText_NoClipOn[] = _("Murs : ignorés");
static const u8 sText_NoClipOff[] = _("Murs : normaux");
static const u8 sText_EncOn[] = _("Rencontres : OUI");
static const u8 sText_EncOff[] = _("Rencontres : NON");
static const u8 sText_Heal[] = _("Soigner l'équipe");
static const u8 sText_GiveMon[] = _("Recevoir MEWTWO");
static const u8 sText_Close[] = _("Fermer");

#define tListTaskId data[0]
#define tWindowId   data[1]
#define tInWarpList data[2]

static EWRAM_DATA struct ListMenuItem *sItems = NULL;

static void Task_DebugMenu(u8 taskId);

static void DebugMenu_Draw(u8 taskId, bool8 warpList)
{
    struct Task *task = &gTasks[taskId];
    struct ListMenuTemplate t = {0};
    struct WindowTemplate win;
    u8 i, count, shown;

    if (sItems == NULL)
        sItems = AllocZeroed(sizeof(struct ListMenuItem) * ARRAY_COUNT(sDebugWarps));

    if (warpList)
    {
        count = ARRAY_COUNT(sDebugWarps);
        for (i = 0; i < count; i++)
        {
            sItems[i].name = sDebugWarps[i].name;
            sItems[i].id = i;
        }
    }
    else
    {
        count = DEBUG_COUNT;
        sItems[DEBUG_WARP].name = sText_Warp;
        sItems[DEBUG_NOCLIP].name = gDebugNoClip ? sText_NoClipOn : sText_NoClipOff;
        sItems[DEBUG_ENCOUNTERS].name = gDebugNoEncounters ? sText_EncOff : sText_EncOn;
        sItems[DEBUG_HEAL].name = sText_Heal;
        sItems[DEBUG_GIVE_MON].name = sText_GiveMon;
        sItems[DEBUG_CLOSE].name = sText_Close;
        for (i = 0; i < count; i++)
            sItems[i].id = i;
    }
    shown = count > 6 ? 6 : count;

    win = CreateWindowTemplate(0, 1, 1, 14, shown * 2, 0xF, 0x64);
    task->tWindowId = AddWindow(&win);
    SetStandardWindowBorderStyle(task->tWindowId, FALSE);

    t.items = sItems;
    t.moveCursorFunc = ListMenuDefaultCursorMoveFunc;
    t.totalItems = count;
    t.maxShowed = shown;
    t.windowId = task->tWindowId;
    t.item_X = 8;
    t.upText_Y = 1;
    t.cursorPal = 2;
    t.fillValue = 1;
    t.cursorShadowPal = 3;
    t.lettersSpacing = 1;
    t.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    t.fontId = FONT_NORMAL;
    t.cursorKind = CURSOR_BLACK_ARROW;
    task->tListTaskId = ListMenuInit(&t, 0, 0);
    task->tInWarpList = warpList;
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
    ScheduleBgCopyTilemapToVram(0);
}

static void DebugMenu_Erase(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    DestroyListMenuTask(task->tListTaskId, NULL, NULL);
    ClearStdWindowAndFrame(task->tWindowId, TRUE);
    RemoveWindow(task->tWindowId);
}

static void DebugMenu_Close(u8 taskId)
{
    DebugMenu_Erase(taskId);
    FREE_AND_SET_NULL(sItems);
    DestroyTask(taskId);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
}

static void Task_DebugMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 input = ListMenu_ProcessInput(task->tListTaskId);

    if (input == LIST_NOTHING_CHOSEN)
        return;
    PlaySE(SE_SELECT);

    if (task->tInWarpList)
    {
        if (input == LIST_CANCEL)
        {
            DebugMenu_Erase(taskId);
            DebugMenu_Draw(taskId, FALSE);
            return;
        }
        DebugMenu_Erase(taskId);
        FREE_AND_SET_NULL(sItems);
        DestroyTask(taskId);
        SetWarpDestination(sDebugWarps[input].group, sDebugWarps[input].num, WARP_ID_NONE,
                           sDebugWarps[input].x, sDebugWarps[input].y);
        DoWarp();
        return;
    }

    switch (input)
    {
    case DEBUG_WARP:
        DebugMenu_Erase(taskId);
        DebugMenu_Draw(taskId, TRUE);
        break;
    case DEBUG_NOCLIP:
        gDebugNoClip ^= TRUE;
        DebugMenu_Erase(taskId);
        DebugMenu_Draw(taskId, FALSE);
        break;
    case DEBUG_ENCOUNTERS:
        gDebugNoEncounters ^= TRUE;
        DebugMenu_Erase(taskId);
        DebugMenu_Draw(taskId, FALSE);
        break;
    case DEBUG_HEAL:
        HealPlayerParty();
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_GIVE_MON:
        if (ScriptGiveMon(SPECIES_MEWTWO, 70, ITEM_NONE, 0, 0, 0) == MON_GIVEN_TO_PARTY)
        {
            // PSYKO (4e attaque) en premier : les tests headless attaquent en appuyant sur A
            struct Pokemon *mon = &gPlayerParty[CalculatePlayerPartyCount() - 1];
            u16 move1 = GetMonData(mon, MON_DATA_MOVE1), move4 = GetMonData(mon, MON_DATA_MOVE4);
            u8 pp1 = GetMonData(mon, MON_DATA_PP1), pp4 = GetMonData(mon, MON_DATA_PP4);
            SetMonData(mon, MON_DATA_MOVE1, &move4);
            SetMonData(mon, MON_DATA_PP1, &pp4);
            SetMonData(mon, MON_DATA_MOVE4, &move1);
            SetMonData(mon, MON_DATA_PP4, &pp1);
        }
        FlagSet(FLAG_SYS_POKEMON_GET);
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_CLOSE:
    case LIST_CANCEL:
        DebugMenu_Close(taskId);
        break;
    }
}

void DebugMenu_Open(void)
{
    u8 taskId = CreateTask(Task_DebugMenu, 80);
    DebugMenu_Draw(taskId, FALSE);
}

#endif // KANTO_DEBUG_START
