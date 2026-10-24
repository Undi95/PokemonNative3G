// Menu de debug (builds KANTO_DEBUG=1 uniquement), ouvert depuis le menu Start.
// Téléportation, traverser les murs, rencontres sauvages, soin de l'équipe.
#include "global.h"
#include "constants/kanto_flags_vars.h"
#include "debug_menu.h"
#include "coins.h"
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
#include "pokedex.h"
#include "constants/kanto.h"
#include "item.h"
#include "constants/characters.h"
#include "field_weather.h"
#include "kanto_field_door.h"
#include "kanto_region_map.h"
#include "palette.h"
#include "region_map.h"
#include "battle_setup.h"
#include "kanto_save.h"
#include "constants/rematches.h"

void FullyUnlockFameChecker(void); // kanto_fame_checker.c

bool8 gDebugNoClip = FALSE;
bool8 gDebugNoEncounters = FALSE;

#ifdef KANTO_DEBUG_START

enum {
    DEBUG_WARP,
    DEBUG_NOCLIP,
    DEBUG_ENCOUNTERS,
    DEBUG_HEAL,
    DEBUG_GIVE_MON,
    DEBUG_GIVE_ITEMS,
    DEBUG_UNLOCK_DEXES,
    DEBUG_FLY_MAP,
    DEBUG_HOENN_REMATCHES,
    DEBUG_SEVII_PASSES,
    DEBUG_SS_ANNE,
    DEBUG_KANTO_DEX_FULL,
    DEBUG_FAME_CHECKER,
    DEBUG_BOTH_LEAGUES,
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
static const u8 sWarpName_Route102[] = _("ROUTE 102");
static const u8 sWarpName_SaffronGym[] = _("ARÈNE SAFRANIA");
static const u8 sWarpName_KantoHof[] = _("PANTHÉON KANTO");
static const u8 sWarpName_PokemonTower3F[] = _("TOUR POKéMON 3");
static const u8 sWarpName_PokemonTower6F[] = _("TOUR POKéMON 6");
static const u8 sWarpName_RocketHideout[] = _("REPAIRE ROCKET");
static const u8 sWarpName_OneIslandHarbor[] = _("PORT ÎLE 1");
static const u8 sWarpName_GameFreak[] = _("GAME FREAK");
static const u8 sWarpName_PewterMuseum[] = _("MUSÉE ARGENTA");
static const u8 sWarpName_LoreleisRoom[] = _("LIGUE : OLGA");
static const u8 sWarpName_TrainerTower[] = _("TOUR DRESSEURS");
static const u8 sWarpName_BerryForest[] = _("FORÊT BAIES");
static const u8 sWarpName_MeteorFalls[] = _("CHUTES MÉTÉORE");

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
    {sWarpName_Route102, MAP_GROUP(MAP_ROUTE102), MAP_NUM(MAP_ROUTE102), 31, 14}, // à côté de Calvin (revanche)
    {sWarpName_SaffronGym, MAP_GROUP(MAP_SAFFRON_CITY_GYM), MAP_NUM(MAP_SAFFRON_CITY_GYM), 14, 22}, // téléporteurs
    {sWarpName_KantoHof, MAP_GROUP(MAP_POKEMON_LEAGUE_HALL_OF_FAME), MAP_NUM(MAP_POKEMON_LEAGUE_HALL_OF_FAME), 6, 19},
    {sWarpName_PokemonTower3F, MAP_GROUP(MAP_POKEMON_TOWER_3F), MAP_NUM(MAP_POKEMON_TOWER_3F), 17, 12}, // SPECTRES sauvages
    {sWarpName_PokemonTower6F, MAP_GROUP(MAP_POKEMON_TOWER_6F), MAP_NUM(MAP_POKEMON_TOWER_6F), 12, 13}, // 3 pas vers le bas : Ossatueur
    {sWarpName_RocketHideout, MAP_GROUP(MAP_ROCKET_HIDEOUT_B4F), MAP_NUM(MAP_ROCKET_HIDEOUT_B4F), 19, 5}, // sous Giovanni (Scope Sylph)
    {sWarpName_OneIslandHarbor, MAP_GROUP(MAP_ONE_ISLAND_HARBOR), MAP_NUM(MAP_ONE_ISLAND_HARBOR), 8, 5}, // au-dessus du marin du Seagallop (arrivée du ferry)
    {sWarpName_GameFreak, MAP_GROUP(MAP_CELADON_CITY_CONDOMINIUMS_3F), MAP_NUM(MAP_CELADON_CITY_CONDOMINIUMS_3F), 3, 9}, // sous le designer (diplôme)
    {sWarpName_PewterMuseum, MAP_GROUP(MAP_PEWTER_CITY_MUSEUM_1F), MAP_NUM(MAP_PEWTER_CITY_MUSEUM_1F), 4, 5}, // sous le fossile d'Ptéra
    {sWarpName_LoreleisRoom, MAP_GROUP(MAP_POKEMON_LEAGUE_LORELEIS_ROOM), MAP_NUM(MAP_POKEMON_LEAGUE_LORELEIS_ROOM), 6, 11}, // éclairage de la Ligue
    {sWarpName_TrainerTower, MAP_GROUP(MAP_TRAINER_TOWER_LOBBY), MAP_NUM(MAP_TRAINER_TOWER_LOBBY), 9, 10}, // Tour des Dresseurs (Île 7)
    {sWarpName_BerryForest, MAP_GROUP(MAP_THREE_ISLAND_BERRY_FOREST), MAP_NUM(MAP_THREE_ISLAND_BERRY_FOREST), 43, 7}, // autel de Celebi
    {sWarpName_MeteorFalls, MAP_GROUP(MAP_METEOR_FALLS_B1F_2R), MAP_NUM(MAP_METEOR_FALLS_B1F_2R), 6, 4}, // météorite de Jirachi
};

// Tous les objets du jeu (Hoenn + Kanto) : 99 de chaque (1 pour les objets rares et les CS).
// Les poches du sac sont limitées : ce qui ne rentre pas va dans le PC (s'il reste de la place).
static void DebugMenu_GiveAllItems(void)
{
    u16 i, count;
    for (i = 1; i < ITEMS_COUNT; i++)
    {
        const u8 *name = GetItemName(i);
        u8 pocket = GetItemPocket(i);
        if (name[0] == CHAR_QUESTION_MARK || pocket == POCKET_NONE)
            continue;
        if (pocket == POCKET_KEY_ITEMS || (i >= ITEM_HM01 && i <= ITEM_HM08))
            count = 1;
        else
            count = 99;
        if (CheckBagHasItem(i, count))
            continue;
        if (!AddBagItem(i, count))
            AddPCItem(i, count);
    }
}

static const u8 sText_Warp[] = _("Téléportation");
static const u8 sText_NoClipOn[] = _("Murs : ignorés");
static const u8 sText_NoClipOff[] = _("Murs : normaux");
static const u8 sText_EncOn[] = _("Rencontres : OUI");
static const u8 sText_EncOff[] = _("Rencontres : NON");
static const u8 sText_Heal[] = _("Soigner l'équipe");
static const u8 sText_GiveMon[] = _("MEWTWO + KADABRA");
static const u8 sText_GiveItems[] = _("Ajout objets");
static const u8 sText_UnlockDexes[] = _("Débloquer les 2 POKéDEX");
static const u8 sText_FlyMap[] = _("Carte VOL (2 régions)");
static const u8 sText_HoennRematches[] = _("Revanches PokéNav");
static const u8 sText_SeviiPasses[] = _("Pass îles Sevii");
static const u8 sText_SSAnne[] = _("Départ S.S. Anne");
static const u8 sText_KantoDexFull[] = _("POKéDEX Kanto complet");
static const u8 sText_FameChecker[] = _("MEMORYDEX complet");
static const u8 sText_BothLeagues[] = _("Deux Ligues finies");
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
        sItems[DEBUG_GIVE_ITEMS].name = sText_GiveItems;
        sItems[DEBUG_UNLOCK_DEXES].name = sText_UnlockDexes;
        sItems[DEBUG_FLY_MAP].name = sText_FlyMap;
        sItems[DEBUG_HOENN_REMATCHES].name = sText_HoennRematches;
        sItems[DEBUG_SEVII_PASSES].name = sText_SeviiPasses;
        sItems[DEBUG_SS_ANNE].name = sText_SSAnne;
        sItems[DEBUG_KANTO_DEX_FULL].name = sText_KantoDexFull;
        sItems[DEBUG_FAME_CHECKER].name = sText_FameChecker;
        sItems[DEBUG_BOTH_LEAGUES].name = sText_BothLeagues;
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

// Carte de vol de la région où l'on est (Kanto : Rouge Feu, Hoenn : Émeraude), sans Pokémon ni badge
static void Task_DebugOpenFlyMap(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(IsKantoTilesetMap() ? KantoCB2_OpenFlyMap : CB2_OpenFlyMap);
        DestroyTask(taskId);
    }
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
        ScriptGiveMon(SPECIES_KADABRA, 30, ITEM_NONE, 0, 0, 0); // CÂBLE LINK : évolution par échange
        FlagSet(FLAG_SYS_POKEMON_GET);
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_UNLOCK_DEXES:
        // Pokédex de Hoenn (Prof. Seko) et de Kanto (Prof. Chen : vue KANTO dans les options) ;
        // pour les tests : les 151 de Kanto vus, un sur deux attrapé
        FlagSet(FLAG_SYS_POKEDEX_GET);
        FlagSet(FLAG_KANTO_SYS_POKEDEX_GET);
        {
            u16 i;
            for (i = 1; i <= KANTO_DEX_COUNT; i++)
            {
                GetSetPokedexFlag(i, FLAG_SET_SEEN);
                if (i % 2)
                    GetSetPokedexFlag(i, FLAG_SET_CAUGHT);
            }
        }
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_GIVE_ITEMS:
        DebugMenu_GiveAllItems();
        FlagSet(FLAG_KANTO_GOT_COIN_CASE); // étui à jetons de Kanto (Casino de Céladopole)
        if (GetCoins() < 500)
            SetCoins(500);
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_FLY_MAP:
        // conditions du Vol entre régions (SELECT sur la carte) : Ligue de Kanto finie, Rubis/Saphir rendus
        FlagSet(FLAG_KANTO_SYS_GAME_CLEAR);
        FlagSet(FLAG_KANTO_SYS_CAN_LINK_WITH_RS);
        DebugMenu_Close(taskId);
        LockPlayerFieldControls();
        FadeScreen(FADE_TO_BLACK, 0);
        CreateTask(Task_DebugOpenFlyMap, 0);
        break;
    case DEBUG_HOENN_REMATCHES:
        // Cherche VS à Hoenn : dresseurs de la table des revanches combattus et inscrits au PokéNav, Cherche VS chargé
        {
            u16 i;
            for (i = 0; i <= REMATCH_SPECIAL_TRAINER_START; i++)
            {
                FlagSet(TRAINER_FLAGS_START + gRematchTable[i].trainerIds[0]);
                FlagSet(TRAINER_REGISTERED_FLAGS_START + i);
            }
        }
        if (!CheckBagHasItem(ITEM_VS_SEEKER, 1))
            AddBagItem(ITEM_VS_SEEKER, 1);
        gSaveBlockKanto.trainerRematchStepCounter = (gSaveBlockKanto.trainerRematchStepCounter & 0xFF00) | 100;
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_SEVII_PASSES:
        // Seagallop : Carmin sur Mer accessible (Tri-Pass) et toutes les îles (Rainbow Pass, menu des destinations)
        VarSet(VAR_KANTO_MAP_SCENE_CINNABAR_ISLAND, 4);
        VarSet(VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5);
        if (!CheckBagHasItem(ITEM_TRI_PASS, 1))
            AddBagItem(ITEM_TRI_PASS, 1);
        if (!CheckBagHasItem(ITEM_RAINBOW_PASS, 1))
            AddBagItem(ITEM_RAINBOW_PASS, 1);
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_SS_ANNE:
        // CS Coupe reçue : en sortant sur le pont, le S.S. Anne quitte le port (cinématique de RF)
        VarSet(VAR_KANTO_MAP_SCENE_VERMILION_CITY, 1);
        DebugMenu_Erase(taskId);
        FREE_AND_SET_NULL(sItems);
        DestroyTask(taskId);
        SetWarpDestination(MAP_GROUP(MAP_SSANNE_EXTERIOR), MAP_NUM(MAP_SSANNE_EXTERIOR), WARP_ID_NONE, 32, 13);
        DoWarp();
        return;
    case DEBUG_KANTO_DEX_FULL:
        // diplôme de Game Freak (Céladopole) : les 151 de Kanto vus et attrapés
        FlagSet(FLAG_SYS_POKEDEX_GET);
        FlagSet(FLAG_KANTO_SYS_POKEDEX_GET);
        {
            u16 i;
            for (i = 1; i <= KANTO_DEX_COUNT; i++)
            {
                GetSetPokedexFlag(i, FLAG_SET_SEEN);
                GetSetPokedexFlag(i, FLAG_SET_CAUGHT);
            }
        }
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_FAME_CHECKER:
        // MEMORYDEX (Fame Checker) : toutes les personnes et toutes les fiches (FullyUnlockFameChecker de RF)
        AddBagItem(ITEM_FAME_CHECKER, 1);
        FullyUnlockFameChecker();
        PlaySE(SE_USE_ITEM);
        break;
    case DEBUG_BOTH_LEAGUES:
        // événements d'après les deux Ligues (Celebi, Jirachi, œufs de starters…)
        FlagSet(FLAG_SYS_GAME_CLEAR);
        FlagSet(FLAG_KANTO_SYS_GAME_CLEAR);
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
