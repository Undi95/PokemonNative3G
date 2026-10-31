#ifdef PORTABLE
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "global.fieldmap.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "fieldmap.h"
#include "item.h"
#include "kanto_save.h"
#include "main.h"
#include "m4a.h"
#include "money.h"
#include "new_game.h"
#include "overworld.h"
#include "palette.h"
#include "save.h"
#include "pokemon.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sprite.h"
#include "task.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "platform/test_state.h"
#include "rtc.h"
#include "day_night.h"

extern void AgbMain(void);

// What happened since the last state, written with it as "events": text that
// was printed, and flags, variables and items that changed. Lets the tests
// check what the game did without looking at the screen.
static char sEvents[32768];
static size_t sEventsLength;
static bool8 sEventsOverflowed;

// What the flags, variables and bag held at the last state, to find changes
static u8 sLastFlags[NUM_FLAG_BYTES];
static u16 sLastVars[VARS_COUNT];
static u8 sLastKantoFlags[KANTO_FLAG_BYTES];
static u16 sLastKantoVars[KANTO_VARS_COUNT];
static u16 sLastItems[ITEMS_COUNT];
static bool8 sHaveLast;

// Set by the test mode when it writes the state: the events cost nothing otherwise
bool8 gTestStateEnabled;

static void AddEvent(const char *format, ...) __attribute__((format(printf, 1, 2)));

static void AddEvent(const char *format, ...)
{
    va_list args;
    int length;

    if (sEventsOverflowed)
        return;
    va_start(args, format);
    length = vsnprintf(sEvents + sEventsLength, sizeof(sEvents) - sEventsLength, format, args);
    va_end(args);
    // Keeps room for the last event's comma
    if (length < 0 || sEventsLength + length + 2 >= sizeof(sEvents))
    {
        sEvents[sEventsLength] = '\0';
        sEventsOverflowed = TRUE;
        return;
    }
    sEventsLength += length;
    sEvents[sEventsLength++] = ',';
    sEvents[sEventsLength] = '\0';
}

// Called when a text printer starts, with the text in the game's charset, as
// hex: the tests decode it with charmap.txt
void TestState_OnText(u8 windowId, const u8 *text)
{
    char hex[2 * 400 + 1];
    int i;

    if (!gTestStateEnabled || text == NULL)
        return;
    for (i = 0; i < 400 && text[i] != 0xFF; i++)
        sprintf(hex + 2 * i, "%02x", text[i]);
    hex[2 * i] = '\0';
    AddEvent("{\"t\": \"text\", \"win\": %d, \"hex\": \"%s\"}", windowId, hex);
}

static void ReadItems(u16 *items)
{
    memset(items, 0, ITEMS_COUNT * sizeof(u16));
    for (int pocket = 0; pocket < POCKETS_COUNT; pocket++)
    {
        for (int i = 0; i < gBagPockets[pocket].capacity; i++)
        {
            u16 id = gBagPockets[pocket].itemSlots[i].itemId;

            if (id != ITEM_NONE && id < ITEMS_COUNT)
                items[id] += gSaveBlock2Ptr->encryptionKey ^ gBagPockets[pocket].itemSlots[i].quantity;
        }
    }
}

// Adds the flags, variables and items that changed since the last state. A
// lot of changes at once is a save being loaded or a new game, and only
// their number is written.
static void FindChanges(void)
{
    static u16 sItems[ITEMS_COUNT];
    int changes = 0;

    if (gSaveBlock1Ptr == NULL || gSaveBlock2Ptr == NULL || gBagPockets[0].itemSlots == NULL)
        return;
    ReadItems(sItems);
    if (sHaveLast)
    {
        for (int i = 0; i < NUM_FLAG_BYTES; i++)
            changes += __builtin_popcount(sLastFlags[i] ^ gSaveBlock1Ptr->flags[i]);
        for (int i = 0; i < KANTO_FLAG_BYTES; i++)
            changes += __builtin_popcount(sLastKantoFlags[i] ^ gSaveBlockKanto.flags[i]);
        for (int i = 0; i < VARS_COUNT; i++)
            changes += sLastVars[i] != gSaveBlock1Ptr->vars[i];
        for (int i = 0; i < KANTO_VARS_COUNT; i++)
            changes += sLastKantoVars[i] != gSaveBlockKanto.vars[i];
        for (int i = 0; i < ITEMS_COUNT; i++)
            changes += sLastItems[i] != sItems[i];
    }

    if (sHaveLast && changes > 64)
    {
        AddEvent("{\"t\": \"bulk\", \"n\": %d}", changes);
    }
    else if (sHaveLast && changes > 0)
    {
        for (int i = 0; i < NUM_FLAG_BYTES * 8; i++)
        {
            if ((sLastFlags[i / 8] ^ gSaveBlock1Ptr->flags[i / 8]) & (1 << (i % 8)))
                AddEvent("{\"t\": \"flag\", \"id\": %d, \"v\": %d}", i, (gSaveBlock1Ptr->flags[i / 8] >> (i % 8)) & 1);
        }
        for (int i = 0; i < KANTO_FLAG_BYTES * 8; i++)
        {
            if ((sLastKantoFlags[i / 8] ^ gSaveBlockKanto.flags[i / 8]) & (1 << (i % 8)))
                AddEvent("{\"t\": \"flag\", \"id\": %d, \"v\": %d}", KANTO_FLAGS_START + i,
                         (gSaveBlockKanto.flags[i / 8] >> (i % 8)) & 1);
        }
        for (int i = 0; i < VARS_COUNT; i++)
        {
            if (sLastVars[i] != gSaveBlock1Ptr->vars[i])
                AddEvent("{\"t\": \"var\", \"id\": %d, \"v\": %d}", VARS_START + i, gSaveBlock1Ptr->vars[i]);
        }
        for (int i = 0; i < KANTO_VARS_COUNT; i++)
        {
            if (sLastKantoVars[i] != gSaveBlockKanto.vars[i])
                AddEvent("{\"t\": \"var\", \"id\": %d, \"v\": %d}", KANTO_VARS_START + i, gSaveBlockKanto.vars[i]);
        }
        for (int i = 0; i < ITEMS_COUNT; i++)
        {
            if (sLastItems[i] != sItems[i])
                AddEvent("{\"t\": \"item\", \"id\": %d, \"n\": %d}", i, sItems[i]);
        }
    }

    memcpy(sLastFlags, gSaveBlock1Ptr->flags, sizeof(sLastFlags));
    memcpy(sLastKantoFlags, gSaveBlockKanto.flags, sizeof(sLastKantoFlags));
    memcpy(sLastVars, gSaveBlock1Ptr->vars, sizeof(sLastVars));
    memcpy(sLastKantoVars, gSaveBlockKanto.vars, sizeof(sLastKantoVars));
    memcpy(sLastItems, sItems, sizeof(sLastItems));
    sHaveLast = TRUE;
}

// The song the BGM player is playing, or -1
static int GetBgmSong(void)
{
    if (gMPlayInfo_BGM.songHeader == NULL || (gMPlayInfo_BGM.status & MUSICPLAYER_STATUS_PAUSE)
     || !(gMPlayInfo_BGM.status & MUSICPLAYER_STATUS_TRACK))
        return -1;
    // PH_NURSE_SOLO is the last song in the table
    for (int i = 0; i <= PH_NURSE_SOLO; i++)
    {
        if (gSongTable[i].header == gMPlayInfo_BGM.songHeader)
            return i;
    }
    return -1;
}

// A function as its distance from AgbMain, which the tests turn into its name
// with the symbols of the build (see docker/build.sh)
static long long FunctionOffset(void (*func)(void))
{
    return func == NULL ? 0 : (long long)((uintptr_t)func - (uintptr_t)AgbMain);
}

// Called after every frame of the test mode: notes when the music, the main
// callback or the map changes, with the frame, since a test can wait a long
// time between two states
void TestState_OnFrame(u32 frame)
{
    static int sLastBgm = -2;
    static void (*sLastCallback2)(void);
    int bgm;

    if (!gTestStateEnabled)
        return;
    bgm = GetBgmSong();
    if (bgm != sLastBgm)
    {
        sLastBgm = bgm;
        AddEvent("{\"t\": \"bgm\", \"f\": %u, \"v\": %d}", frame, bgm);
    }
    if (gMain.callback2 != sLastCallback2)
    {
        sLastCallback2 = gMain.callback2;
        AddEvent("{\"t\": \"cb2\", \"f\": %u, \"v\": %lld}", frame, FunctionOffset(gMain.callback2));
    }
}

static void WriteParty(FILE *file, const char *name, struct Pokemon *party, int count)
{
    fprintf(file, ", \"%s\": [", name);
    for (int i = 0; i < count; i++)
    {
        u16 species = GetMonData(&party[i], MON_DATA_SPECIES);

        if (species == SPECIES_NONE)
            break;
        fprintf(file, "%s[%d, %d, %d, %d, %d, %d, %u]", i == 0 ? "" : ", ", species, GetMonData(&party[i], MON_DATA_LEVEL),
                GetMonData(&party[i], MON_DATA_HP), GetMonData(&party[i], MON_DATA_MAX_HP),
                GetMonData(&party[i], MON_DATA_STATUS), GetMonData(&party[i], MON_DATA_IS_EGG),
                GetMonData(&party[i], MON_DATA_PERSONALITY));
    }
    fprintf(file, "]");
}

// What the headless tests' driver needs to know to play: where the player is,
// whether they can move, and what's going on, as one line of JSON
void WriteTestState(FILE *file, u32 frame)
{
    const struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];
    bool32 first = TRUE;
    // There's no save block until a game is started or continued
    s8 mapGroup = gSaveBlock1Ptr != NULL ? gSaveBlock1Ptr->location.mapGroup : -1;
    s8 mapNum = gSaveBlock1Ptr != NULL ? gSaveBlock1Ptr->location.mapNum : -1;

    FindChanges();

    fprintf(file, "{\"frame\": %u, \"map\": [%d, %d], \"pos\": [%d, %d], \"facing\": %d, \"moving\": %d, "
                  "\"overworld\": %d, \"locked\": %d, \"script\": %d, \"battle\": %d, \"fade\": %d, \"bgm\": %d, \"objects\": [",
            frame, mapGroup, mapNum,
            player->currentCoords.x - MAP_OFFSET, player->currentCoords.y - MAP_OFFSET, player->facingDirection,
            gPlayerAvatar.tileTransitionState, gMain.callback2 == CB2_Overworld, ArePlayerFieldControlsLocked(),
            ScriptContext_IsEnabled(), gMain.inBattle, gPaletteFade.active, GetBgmSong());

    // Where the other people and things are, since they block the way
    for (int i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        const struct ObjectEvent *object = &gObjectEvents[i];

        if (!object->active || object->isPlayer || object->invisible)
            continue;
        fprintf(file, "%s[%d, %d]", first ? "" : ", ", object->currentCoords.x - MAP_OFFSET,
                object->currentCoords.y - MAP_OFFSET);
        first = FALSE;
    }
    fprintf(file, "]");

    // How the player gets around (PLAYER_AVATAR_FLAG_*: on foot, bike, surfing...)
    fprintf(file, ", \"avatar\": %d", gPlayerAvatar.flags);

    // What the game is running: its callbacks and tasks, which tell a menu or a
    // freeze apart
    fprintf(file, ", \"cb1\": %lld, \"cb2\": %lld, \"tasks\": [", FunctionOffset(gMain.callback1),
            FunctionOffset(gMain.callback2));
    first = TRUE;
    for (int i = 0; i < NUM_TASKS; i++)
    {
        if (!gTasks[i].isActive)
            continue;
        fprintf(file, "%s%lld", first ? "" : ", ", FunctionOffset((void (*)(void))gTasks[i].func));
        first = FALSE;
    }
    fprintf(file, "]");

    if (gSaveBlock1Ptr != NULL)
    {
        WriteParty(file, "party", gPlayerParty, gPlayerPartyCount < PARTY_SIZE ? gPlayerPartyCount : PARTY_SIZE);
        fprintf(file, ", \"money\": %u", GetMoney(&gSaveBlock1Ptr->money));
    }
    if (gMain.inBattle)
    {
        WriteParty(file, "foe", gEnemyParty, PARTY_SIZE);
        fprintf(file, ", \"battle_type\": %u, \"trainer\": %d", gBattleTypeFlags, gTrainerBattleOpponent_A);
    }
    fprintf(file, ", \"outcome\": %d", gBattleOutcome);

#ifdef KANTO_DEBUG_START
    // Build de test de Kanto : sprite de chaque objet (graphicsId, spriteId, inUse, invisible,
    // priorité, palette, x, y, tuile)
    fprintf(file, ", \"sprites\": [");
    first = TRUE;
    for (int i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        const struct ObjectEvent *object = &gObjectEvents[i];
        const struct Sprite *sprite;

        if (!object->active)
            continue;
        sprite = &gSprites[object->spriteId];
        u32 tileSum = 0, palSum = 0;
        // Up to the end of the sprites' VRAM (OBJ_VRAM0_SIZE)
        for (int j = 0; j < 8 * 32 && sprite->oam.tileNum * 32 + j < 0x8000; j++)
            tileSum += ((u8 *)OBJ_VRAM0)[sprite->oam.tileNum * 32 + j];
        for (int j = 1; j < 16; j++)
            palSum += ((u16 *)OBJ_PLTT)[sprite->oam.paletteNum * 16 + j];
        fprintf(file, "%s[%d, %d, %d, %d, %d, %d, %d, %d, %d, %u, %u, %d, %d]", first ? "" : ", ", object->graphicsId,
                object->spriteId, sprite->inUse, sprite->invisible, sprite->oam.priority,
                sprite->oam.paletteNum, sprite->x + sprite->x2 + sprite->centerToCornerVecX,
                sprite->y + sprite->y2 + sprite->centerToCornerVecY, sprite->oam.tileNum, tileSum, palSum,
                sprite->subspriteMode, sprite->subspriteTableNum);
        first = FALSE;
    }
    fprintf(file, "]");
#endif

    if (sEventsLength > 0)
        sEvents[sEventsLength - 1] = '\0'; // the last comma
    fprintf(file, ", \"events\": [%s%s]}\n", sEvents,
            sEventsOverflowed ? (sEventsLength > 0 ? ", {\"t\": \"overflow\"}" : "{\"t\": \"overflow\"}") : "");
    sEventsLength = 0;
    sEvents[0] = '\0';
    sEventsOverflowed = FALSE;
    fflush(file);
}

// A test command, a line starting with '!' in the test input: reads or sets
// part of the game's state, to check what a scenario did or to set one up
// quickly. Writes its answer as a line of JSON, {"reply": ...}.
void RunTestCommand(FILE *file, const char *line)
{
    char name[32] = "";
    long args[4] = {0};
    int count = sscanf(line, "!%31s %li %li %li %li", name, &args[0], &args[1], &args[2], &args[3]) - 1;

    if (count < 0)
    {
        fprintf(file, "{\"reply\": null, \"error\": \"empty command\"}\n");
    }
    else if (strcmp(name, "flag") == 0 && count >= 1)
    {
        if (count >= 2)
            args[1] ? FlagSet(args[0]) : FlagClear(args[0]);
        fprintf(file, "{\"reply\": %d}\n", FlagGet(args[0]));
    }
    else if (strcmp(name, "var") == 0 && count >= 1)
    {
        if (count >= 2)
            VarSet(args[0], args[1]);
        fprintf(file, "{\"reply\": %d}\n", VarGet(args[0]));
    }
    else if (strcmp(name, "item") == 0 && count >= 1)
    {
        // With a count, adds (or removes) that many
        if (count >= 2 && args[1] > 0)
            AddBagItem(args[0], args[1]);
        else if (count >= 2 && args[1] < 0)
            RemoveBagItem(args[0], -args[1]);
        fprintf(file, "{\"reply\": %d}\n", CountTotalItemQuantityInBag(args[0]));
    }
    else if (strcmp(name, "money") == 0)
    {
        if (count >= 1)
            SetMoney(&gSaveBlock1Ptr->money, args[0]);
        fprintf(file, "{\"reply\": %u}\n", GetMoney(&gSaveBlock1Ptr->money));
    }
    else if (strcmp(name, "givemon") == 0 && count >= 2)
    {
        fprintf(file, "{\"reply\": %d}\n", ScriptGiveMon(args[0], args[1], count >= 3 ? args[2] : ITEM_NONE, 0, 0, 0));
    }
    else if (strcmp(name, "clock") == 0 && count >= 2)
    {
        // Heure locale du jeu (heures, minutes), comme le réglage de l'horloge
        RtcInitLocalTimeOffset(args[0], args[1]);
        fprintf(file, "{\"reply\": 1}\n");
    }
    else if (strcmp(name, "daynight") == 0 && count >= 1)
    {
        // 2 : vitres éclairées la nuit marquées en magenta (tools/day_night_lights.py)
        gSaveBlock2Ptr->optionsDayNight = args[0] != 0;
        DayNight_SetMarkLights(args[0] == 2);
        fprintf(file, "{\"reply\": 1}\n");
    }
    else if (strcmp(name, "heal") == 0)
    {
        HealPlayerParty();
        fprintf(file, "{\"reply\": 1}\n");
    }
    else if ((strcmp(name, "warp") == 0 && count >= 4) || strcmp(name, "save") == 0)
    {
        // Like the DEBUG menu's warps and the start menu's SAVE: only from the
        // overworld, with the player free
        if (gMain.callback2 != CB2_Overworld || ArePlayerFieldControlsLocked() || ScriptContext_IsEnabled())
        {
            fprintf(file, "{\"reply\": 0, \"error\": \"not free in the overworld\"}\n");
        }
        else if (name[0] == 's')
        {
            u8 status;

            // InitSave and SaveDoSaveCallback
            SaveMapView();
            IncrementGameStat(GAME_STAT_SAVED_GAME);
            status = TrySavingData(gDifferentSaveFile ? SAVE_OVERWRITE_DIFFERENT_FILE : SAVE_NORMAL);
            gDifferentSaveFile = FALSE;
            fprintf(file, "{\"reply\": %d}\n", status == SAVE_STATUS_OK);
        }
        else
        {
            SetWarpDestination(args[0], args[1], WARP_ID_NONE, args[2], args[3]);
            DoWarp();
            fprintf(file, "{\"reply\": 1}\n");
        }
    }
    else
    {
        fprintf(file, "{\"reply\": null, \"error\": \"unknown command\"}\n");
    }
    fflush(file);
}
#endif // PORTABLE
