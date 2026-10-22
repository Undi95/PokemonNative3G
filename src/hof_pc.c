#include "global.h"
#include "hall_of_fame.h"
#include "main.h"
#include "palette.h"
#include "overworld.h"
#include "script.h"
#include "script_menu.h"
#include "task.h"
#include "constants/rgb.h"
#include "event_data.h"
#include "kanto_field_door.h"
#include "constants/flags.h"
#include "constants/kanto_flags_vars.h"

static void ReshowPCMenuAfterHallOfFamePC(void);
static void Task_WaitForPaletteFade(u8);

// PokemonNative3G : chaque région montre son Panthéon (Kanto : celui de Rouge Feu, src/kanto_hall_of_fame.c)
bool8 HasHallOfFameInThisRegion(void)
{
    if (IsKantoTilesetMap())
        return FlagGet(FLAG_KANTO_SYS_GAME_CLEAR);
    return FlagGet(FLAG_SYS_GAME_CLEAR);
}

void AccessHallOfFamePC(void)
{
    if (IsKantoTilesetMap())
        SetMainCallback2(KantoCB2_InitHofPC);
    else
        SetMainCallback2(CB2_DoHallOfFamePC);
    LockPlayerFieldControls();
}

void ReturnFromHallOfFamePC(void)
{
    SetMainCallback2(CB2_ReturnToField);
    gFieldCallback = ReshowPCMenuAfterHallOfFamePC;
}

static void ReshowPCMenuAfterHallOfFamePC(void)
{
    LockPlayerFieldControls();
    Overworld_PlaySpecialMapMusic();
    ScriptMenu_CreatePCMultichoice();
    ScriptMenu_DisplayPCStartupPrompt();
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
    CreateTask(Task_WaitForPaletteFade, 10);
}

static void Task_WaitForPaletteFade(u8 taskId)
{
    if (!gPaletteFade.active)
        DestroyTask(taskId);
}
