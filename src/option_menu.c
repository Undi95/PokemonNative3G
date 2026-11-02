#include "global.h"
#include "constants/songs.h"
#include "sound.h"
#include "event_data.h"
#include "constants/kanto.h"
#include "option_menu.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "field_screen_effect.h"
#include "kanto_help_message.h"
#include "malloc.h"
#include "overworld.h"
#include "string_util.h"
#include "kanto_bag_compat.h" // LoadStdWindowGfxOnBg (cadre standard de RF) ; en dernier : ses #define

#define tMenuSelection data[0]
#define tTextSpeed data[1]
#define tBattleSceneOff data[2]
#define tBattleStyle data[3]
#define tSound data[4]
#define tButtonMode data[5]
#define tWindowFrameType data[6]
#define tCharacter data[7]
#define tTitleScreen data[8]
#define tDialogStyle data[9]
#define tBattleUI data[10]
#define tPokedexStyle data[11]
#define tMenuStyle data[12]
#define tBagStyle data[13]
#define tIntro data[14]
#define tMonSprites data[15]

enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_DAYNIGHT,
    // page 2 : choix HOENN / KANTO, par ordre d'importance
    MENUITEM_CHARACTER,
    MENUITEM_MONSPRITES,
    MENUITEM_DIALOGSTYLE,
    MENUITEM_FONT,
    MENUITEM_BATTLEUI,
    MENUITEM_MENUSTYLE,
    MENUITEM_BAGSTYLE,
    MENUITEM_POKEDEXSTYLE,
    MENUITEM_TITLESCREEN,
    MENUITEM_INTRO,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

enum
{
    WIN_HEADER,
    WIN_OPTIONS
};

// Le menu défile : MAX_VISIBLE_ITEMS lignes affichées à partir de sScrollOffset
#define MAX_VISIBLE_ITEMS 7
#define OPTION_YPOS(item) ((OptionRow(item) - sScrollOffset) * 16)

// PokemonNative3G : le menu a deux pages (L/R) : page 1 = réglages d'Émeraude, page 2 = choix HOENN / KANTO.
// RETOUR est sur chaque page.
#define OPTION_PAGE_COUNT 2
#define OPTION_PAGE_FIRST_REGION_ITEM MENUITEM_CHARACTER
EWRAM_DATA static u8 sOptionPage = 0;

static u8 GetOptionPage(u8 item)
{
    return item >= OPTION_PAGE_FIRST_REGION_ITEM ? 1 : 0;
}

// PokemonNative3G : options masquées tant qu'elles ne sont pas débloquées en jeu
// (POKéDEX : vue KANTO débloquée quand le Prof. Chen donne le Pokédex), ou sur l'autre page
static bool8 IsOptionHidden(u8 item)
{
    if (item != MENUITEM_CANCEL && GetOptionPage(item) != sOptionPage)
        return TRUE;
    if (item == MENUITEM_POKEDEXSTYLE)
        return !FlagGet(FLAG_KANTO_SYS_POKEDEX_GET);
    return FALSE;
}

// Ligne affichée d'une option (les options masquées ne prennent pas de ligne)
static u8 OptionRow(u8 item)
{
    u8 i, row = 0;

    for (i = 0; i < item; i++)
    {
        if (!IsOptionHidden(i))
            row++;
    }
    return row;
}

#define IS_OPTION_ROW_VISIBLE(item) (!IsOptionHidden(item) && OptionRow(item) >= sScrollOffset && OptionRow(item) < sScrollOffset + MAX_VISIBLE_ITEMS)
#define YPOS_TEXTSPEED    OPTION_YPOS(MENUITEM_TEXTSPEED)
#define YPOS_BATTLESCENE  OPTION_YPOS(MENUITEM_BATTLESCENE)
#define YPOS_BATTLESTYLE  OPTION_YPOS(MENUITEM_BATTLESTYLE)
#define YPOS_SOUND        OPTION_YPOS(MENUITEM_SOUND)
#define YPOS_BUTTONMODE   OPTION_YPOS(MENUITEM_BUTTONMODE)
#define YPOS_FRAMETYPE    OPTION_YPOS(MENUITEM_FRAMETYPE)
#define YPOS_DAYNIGHT     OPTION_YPOS(MENUITEM_DAYNIGHT)
#define YPOS_CHARACTER    OPTION_YPOS(MENUITEM_CHARACTER)
#define YPOS_TITLESCREEN  OPTION_YPOS(MENUITEM_TITLESCREEN)
#define YPOS_DIALOGSTYLE  OPTION_YPOS(MENUITEM_DIALOGSTYLE)
#define YPOS_FONT         OPTION_YPOS(MENUITEM_FONT)
#define YPOS_BATTLEUI     OPTION_YPOS(MENUITEM_BATTLEUI)
#define YPOS_MONSPRITES   OPTION_YPOS(MENUITEM_MONSPRITES)
#define YPOS_POKEDEXSTYLE OPTION_YPOS(MENUITEM_POKEDEXSTYLE)
#define YPOS_MENUSTYLE    OPTION_YPOS(MENUITEM_MENUSTYLE)
#define YPOS_BAGSTYLE     OPTION_YPOS(MENUITEM_BAGSTYLE)
#define YPOS_INTRO        OPTION_YPOS(MENUITEM_INTRO)

static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void HighlightOptionMenuItem(u8 selection);
static u8 TextSpeed_ProcessInput(u8 selection);
static void TextSpeed_DrawChoices(u8 selection);
static u8 BattleScene_ProcessInput(u8 selection);
static void BattleScene_DrawChoices(u8 selection);
static u8 BattleStyle_ProcessInput(u8 selection);
static void BattleStyle_DrawChoices(u8 selection);
static u8 Sound_ProcessInput(u8 selection);
static void Sound_DrawChoices(u8 selection);
static u8 FrameType_ProcessInput(u8 selection);
static void FrameType_DrawChoices(u8 selection);
static u8 ButtonMode_ProcessInput(u8 selection);
static void ButtonMode_DrawChoices(u8 selection);
static u8 Character_ProcessInput(u8 selection);
static void Character_DrawChoices(u8 selection);
static void TitleScreen_DrawChoices(u8 selection);
static void Region_DrawChoices(u8 selection, u8 y);
static void DayNight_DrawChoices(u8 selection);
static void DrawOptionMenuChoices(u8 taskId);
static void ScrollOptionMenu(u8 taskId);
static void ChangeOptionMenuPage(u8 taskId);
static void DrawHeaderText(void);
static void DrawOptionMenuTexts(void);
static void DrawBgWindowFrames(void);

EWRAM_DATA static bool8 sArrowPressed = FALSE;
EWRAM_DATA static u8 sScrollOffset = 0;
EWRAM_DATA static u8 sDayNight = 0; // option JOUR/NUIT (les 16 données de la tâche sont prises)
EWRAM_DATA static u8 sFont = 0;     // option POLICE

static const u16 sOptionMenuText_Pal[] = INCGFX_U16("graphics/interface/option_menu_text.pal", ".gbapal");
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCGFX_U8("graphics/interface/option_menu_equals_sign.png", ".4bpp");

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_DAYNIGHT]    = gText_DayNight,
    [MENUITEM_CHARACTER]   = gText_Character,
    [MENUITEM_TITLESCREEN] = gText_TitleScreen,
    [MENUITEM_DIALOGSTYLE] = gText_DialogStyle,
    [MENUITEM_FONT]        = gText_Font,
    [MENUITEM_BATTLEUI] = gText_BattleUI,
    [MENUITEM_MONSPRITES] = gText_MonSprites,
    [MENUITEM_POKEDEXSTYLE] = gText_PokedexStyle,
    [MENUITEM_MENUSTYLE] = gText_MenuStyle,
    [MENUITEM_BAGSTYLE] = gText_BagStyle,
    [MENUITEM_INTRO] = gText_Intro,
    [MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitOptionMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        if (gSaveBlock2Ptr->optionsMenuStyle) // PokemonNative3G : MENUS = KANTO, l'écran de Rouge Feu (plus bas)
        {
            CB2_OptionsMenuFromStartMenu();
            return;
        }
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 10:
    {
        u8 taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        gTasks[taskId].tMenuSelection = 0;
        gTasks[taskId].tTextSpeed = gSaveBlock2Ptr->optionsTextSpeed;
        gTasks[taskId].tBattleSceneOff = gSaveBlock2Ptr->optionsBattleSceneOff;
        gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
        gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
        gTasks[taskId].tButtonMode = gSaveBlock2Ptr->optionsButtonMode;
        gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
        gTasks[taskId].tCharacter = gSaveBlock2Ptr->optionsPlayerCharacter;
        gTasks[taskId].tTitleScreen = gSaveBlock2Ptr->optionsTitleScreen;
        gTasks[taskId].tDialogStyle = gSaveBlock2Ptr->optionsDialogStyle;
        gTasks[taskId].tBattleUI = gSaveBlock2Ptr->optionsBattleUI;
        gTasks[taskId].tMonSprites = gSaveBlock2Ptr->optionsMonSprites;
        gTasks[taskId].tPokedexStyle = gSaveBlock2Ptr->optionsPokedexStyle;
        gTasks[taskId].tMenuStyle = gSaveBlock2Ptr->optionsMenuStyle;
        gTasks[taskId].tBagStyle = gSaveBlock2Ptr->optionsBagStyle;
        gTasks[taskId].tIntro = !gSaveBlock2Ptr->optionsIntroHoenn; // 1 = KANTO dans le menu
        sDayNight = gSaveBlock2Ptr->optionsDayNight;
        sFont = gSaveBlock2Ptr->optionsFont;

        DrawOptionMenuChoices(taskId);
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    }
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        if (gTasks[taskId].tMenuSelection == MENUITEM_CANCEL)
            gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        do
        {
            if (gTasks[taskId].tMenuSelection > 0)
                gTasks[taskId].tMenuSelection--;
            else
                gTasks[taskId].tMenuSelection = MENUITEM_CANCEL;
        } while (IsOptionHidden(gTasks[taskId].tMenuSelection));
        ScrollOptionMenu(taskId);
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        do
        {
            if (gTasks[taskId].tMenuSelection < MENUITEM_CANCEL)
                gTasks[taskId].tMenuSelection++;
            else
                gTasks[taskId].tMenuSelection = 0;
        } while (IsOptionHidden(gTasks[taskId].tMenuSelection));
        ScrollOptionMenu(taskId);
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else if (JOY_NEW(L_BUTTON) || JOY_NEW(R_BUTTON)) // PokemonNative3G : page suivante
    {
        ChangeOptionMenuPage(taskId);
    }
    else
    {
        u8 previousOption;

        switch (gTasks[taskId].tMenuSelection)
        {
        case MENUITEM_TEXTSPEED:
            previousOption = gTasks[taskId].tTextSpeed;
            gTasks[taskId].tTextSpeed = TextSpeed_ProcessInput(gTasks[taskId].tTextSpeed);

            if (previousOption != gTasks[taskId].tTextSpeed)
                TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
            break;
        case MENUITEM_BATTLESCENE:
            previousOption = gTasks[taskId].tBattleSceneOff;
            gTasks[taskId].tBattleSceneOff = BattleScene_ProcessInput(gTasks[taskId].tBattleSceneOff);

            if (previousOption != gTasks[taskId].tBattleSceneOff)
                BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
            break;
        case MENUITEM_BATTLESTYLE:
            previousOption = gTasks[taskId].tBattleStyle;
            gTasks[taskId].tBattleStyle = BattleStyle_ProcessInput(gTasks[taskId].tBattleStyle);

            if (previousOption != gTasks[taskId].tBattleStyle)
                BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
            break;
        case MENUITEM_SOUND:
            previousOption = gTasks[taskId].tSound;
            gTasks[taskId].tSound = Sound_ProcessInput(gTasks[taskId].tSound);

            if (previousOption != gTasks[taskId].tSound)
                Sound_DrawChoices(gTasks[taskId].tSound);
            break;
        case MENUITEM_BUTTONMODE:
            previousOption = gTasks[taskId].tButtonMode;
            gTasks[taskId].tButtonMode = ButtonMode_ProcessInput(gTasks[taskId].tButtonMode);

            if (previousOption != gTasks[taskId].tButtonMode)
                ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
            break;
        case MENUITEM_FRAMETYPE:
            previousOption = gTasks[taskId].tWindowFrameType;
            gTasks[taskId].tWindowFrameType = FrameType_ProcessInput(gTasks[taskId].tWindowFrameType);

            if (previousOption != gTasks[taskId].tWindowFrameType)
                FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
            break;
        case MENUITEM_CHARACTER:
            previousOption = gTasks[taskId].tCharacter;
            gTasks[taskId].tCharacter = Character_ProcessInput(gTasks[taskId].tCharacter);

            if (previousOption != gTasks[taskId].tCharacter)
                Character_DrawChoices(gTasks[taskId].tCharacter);
            break;
        case MENUITEM_TITLESCREEN:
            previousOption = gTasks[taskId].tTitleScreen;
            gTasks[taskId].tTitleScreen = Character_ProcessInput(gTasks[taskId].tTitleScreen);

            if (previousOption != gTasks[taskId].tTitleScreen)
                TitleScreen_DrawChoices(gTasks[taskId].tTitleScreen);
            break;
        case MENUITEM_DIALOGSTYLE:
            previousOption = gTasks[taskId].tDialogStyle;
            gTasks[taskId].tDialogStyle = Character_ProcessInput(gTasks[taskId].tDialogStyle);

            if (previousOption != gTasks[taskId].tDialogStyle)
                Region_DrawChoices(gTasks[taskId].tDialogStyle, YPOS_DIALOGSTYLE);
            break;
        case MENUITEM_FONT:
            previousOption = sFont;
            sFont = Character_ProcessInput(sFont);

            if (previousOption != sFont)
                Region_DrawChoices(sFont, YPOS_FONT);
            break;
        case MENUITEM_BATTLEUI:
            previousOption = gTasks[taskId].tBattleUI;
            gTasks[taskId].tBattleUI = Character_ProcessInput(gTasks[taskId].tBattleUI);

            if (previousOption != gTasks[taskId].tBattleUI)
                Region_DrawChoices(gTasks[taskId].tBattleUI, YPOS_BATTLEUI);
            break;
        case MENUITEM_MONSPRITES:
            previousOption = gTasks[taskId].tMonSprites;
            gTasks[taskId].tMonSprites = Character_ProcessInput(gTasks[taskId].tMonSprites);

            if (previousOption != gTasks[taskId].tMonSprites)
                Region_DrawChoices(gTasks[taskId].tMonSprites, YPOS_MONSPRITES);
            break;
        case MENUITEM_POKEDEXSTYLE:
            previousOption = gTasks[taskId].tPokedexStyle;
            gTasks[taskId].tPokedexStyle = Character_ProcessInput(gTasks[taskId].tPokedexStyle);

            if (previousOption != gTasks[taskId].tPokedexStyle)
                Region_DrawChoices(gTasks[taskId].tPokedexStyle, YPOS_POKEDEXSTYLE);
            break;
        case MENUITEM_MENUSTYLE:
            previousOption = gTasks[taskId].tMenuStyle;
            gTasks[taskId].tMenuStyle = Character_ProcessInput(gTasks[taskId].tMenuStyle);

            if (previousOption != gTasks[taskId].tMenuStyle)
                Region_DrawChoices(gTasks[taskId].tMenuStyle, YPOS_MENUSTYLE);
            break;
        case MENUITEM_DAYNIGHT:
            previousOption = sDayNight;
            sDayNight = BattleScene_ProcessInput(sDayNight);

            if (previousOption != sDayNight)
                DayNight_DrawChoices(sDayNight);
            break;
        case MENUITEM_INTRO:
            previousOption = gTasks[taskId].tIntro;
            gTasks[taskId].tIntro = Character_ProcessInput(gTasks[taskId].tIntro);

            if (previousOption != gTasks[taskId].tIntro)
                Region_DrawChoices(gTasks[taskId].tIntro, YPOS_INTRO);
            break;
        case MENUITEM_BAGSTYLE:
            previousOption = gTasks[taskId].tBagStyle;
            gTasks[taskId].tBagStyle = Character_ProcessInput(gTasks[taskId].tBagStyle);

            if (previousOption != gTasks[taskId].tBagStyle)
                Region_DrawChoices(gTasks[taskId].tBagStyle, YPOS_BAGSTYLE);
            break;
        default:
            return;
        }

        if (sArrowPressed)
        {
            sArrowPressed = FALSE;
            CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
        }
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = gTasks[taskId].tTextSpeed;
    gSaveBlock2Ptr->optionsBattleSceneOff = gTasks[taskId].tBattleSceneOff;
    gSaveBlock2Ptr->optionsBattleStyle = gTasks[taskId].tBattleStyle;
    gSaveBlock2Ptr->optionsSound = gTasks[taskId].tSound;
    gSaveBlock2Ptr->optionsButtonMode = gTasks[taskId].tButtonMode;
    gSaveBlock2Ptr->optionsWindowFrameType = gTasks[taskId].tWindowFrameType;
    gSaveBlock2Ptr->optionsPlayerCharacter = gTasks[taskId].tCharacter;
    gSaveBlock2Ptr->optionsTitleScreen = gTasks[taskId].tTitleScreen;
    gSaveBlock2Ptr->optionsDialogStyle = gTasks[taskId].tDialogStyle;
    gSaveBlock2Ptr->optionsBattleUI = gTasks[taskId].tBattleUI;
    gSaveBlock2Ptr->optionsMonSprites = gTasks[taskId].tMonSprites;
    gSaveBlock2Ptr->optionsPokedexStyle = gTasks[taskId].tPokedexStyle;
    gSaveBlock2Ptr->optionsMenuStyle = gTasks[taskId].tMenuStyle;
    gSaveBlock2Ptr->optionsBagStyle = gTasks[taskId].tBagStyle;
    gSaveBlock2Ptr->optionsIntroHoenn = !gTasks[taskId].tIntro;
    gSaveBlock2Ptr->optionsDayNight = sDayNight;
    gSaveBlock2Ptr->optionsFont = sFont;
    sScrollOffset = 0;
    sOptionPage = 0;

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    index = OptionRow(index) - sScrollOffset;
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(index * 16 + 40, index * 16 + 56));
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style)
{
    u8 dst[16];
    u16 i;

    for (i = 0; *text != EOS && i < ARRAY_COUNT(dst) - 1; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = TEXT_COLOR_RED;
        dst[5] = TEXT_COLOR_LIGHT_RED;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, dst, x, y + 1, TEXT_SKIP_DRAW, NULL);
}

static u8 TextSpeed_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void TextSpeed_DrawChoices(u8 selection)
{
    u8 styles[3];
    s32 widthSlow, widthMid, widthFast, xMid;

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_TextSpeedSlow, 104, YPOS_TEXTSPEED, styles[0]);

    widthSlow = GetStringWidth(FONT_NORMAL, gText_TextSpeedSlow, 0);
    widthMid = GetStringWidth(FONT_NORMAL, gText_TextSpeedMid, 0);
    widthFast = GetStringWidth(FONT_NORMAL, gText_TextSpeedFast, 0);

    widthMid -= 94;
    xMid = (widthSlow - widthMid - widthFast) / 2 + 104;
    DrawOptionMenuChoice(gText_TextSpeedMid, xMid, YPOS_TEXTSPEED, styles[1]);

    DrawOptionMenuChoice(gText_TextSpeedFast, GetStringRightAlignXOffset(FONT_NORMAL, gText_TextSpeedFast, 198), YPOS_TEXTSPEED, styles[2]);
}

static u8 BattleScene_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleScene_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, YPOS_BATTLESCENE, styles[0]);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), YPOS_BATTLESCENE, styles[1]);
}

static u8 BattleStyle_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleStyle_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, YPOS_BATTLESTYLE, styles[0]);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), YPOS_BATTLESTYLE, styles[1]);
}

static u8 Sound_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        SetPokemonCryStereo(selection);
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Sound_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, YPOS_SOUND, styles[0]);
    DrawOptionMenuChoice(gText_SoundStereo, GetStringRightAlignXOffset(FONT_NORMAL, gText_SoundStereo, 198), YPOS_SOUND, styles[1]);
}

static u8 FrameType_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    return selection;
}

static void FrameType_DrawChoices(u8 selection)
{
    u8 text[16];
    u8 n = selection + 1;
    u16 i;
    u32 width; //!< French Difference

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = CHAR_SPACER;
        i++;
    }

    text[i] = EOS;

    //!< French Difference
    width = GetStringWidth(1, gText_FrameType, 0);
    DrawOptionMenuChoice(gText_FrameType, 104, YPOS_FRAMETYPE, 0);
    DrawOptionMenuChoice(text, width + 107, YPOS_FRAMETYPE, 1);
}

static u8 ButtonMode_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void ButtonMode_DrawChoices(u8 selection)
{
    s32 widthNormal, widthLR, widthLA, xLR;
    u8 styles[3];

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ButtonTypeNormal, 104, YPOS_BUTTONMODE, styles[0]);

    widthNormal = GetStringWidth(FONT_NORMAL, gText_ButtonTypeNormal, 0);
    widthLR = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLR, 0);
    widthLA = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLEqualsA, 0);

    widthLR -= 94;
    xLR = (widthNormal - widthLR - widthLA) / 2 + 104;
    DrawOptionMenuChoice(gText_ButtonTypeLR, xLR, YPOS_BUTTONMODE, styles[1]);

    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(FONT_NORMAL, gText_ButtonTypeLEqualsA, 198), YPOS_BUTTONMODE, styles[2]);
}

// Sans « PAGE » : avec les espaces de la police de RF (POLICE = KANTO), le titre recouvrait « OPTIONS »
static const u8 sText_OptionPage1[] = _("{L_BUTTON}{R_BUTTON} 1/2 : JEU");
static const u8 sText_OptionPage2[] = _("{L_BUTTON}{R_BUTTON} 2/2 : HOENN/KANTO");

static void DrawHeaderText(void)
{
    const u8 *page = sOptionPage == 0 ? sText_OptionPage1 : sText_OptionPage2;

    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
    // PokemonNative3G : la page affichée, et les touches pour changer de page
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, page, GetStringRightAlignXOffset(FONT_NORMAL, page, 26 * 8) - 4, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < MENUITEM_COUNT; i++)
        if (IS_OPTION_ROW_VISIBLE(i))
            AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sOptionMenuItemsNames[i], 8, OPTION_YPOS(i) + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}

// PokemonNative3G : choix du personnage (Brice/Flora d'Émeraude ou Red/Leaf de Rouge Feu)
static u8 Character_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Character_DrawChoices(u8 selection)
{
    u8 styles[2];
    const u8 *hoenn = gSaveBlock2Ptr->playerGender == MALE ? gText_CharacterBrendan : gText_CharacterMay;
    const u8 *kanto = gSaveBlock2Ptr->playerGender == MALE ? gText_CharacterRed : gText_CharacterLeaf;

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(hoenn, 104, YPOS_CHARACTER, styles[0]);
    DrawOptionMenuChoice(kanto, GetStringRightAlignXOffset(FONT_NORMAL, kanto, 198), YPOS_CHARACTER, styles[1]);
}

// PokemonNative3G : écran titre d'Émeraude ou de Rouge Feu
static void TitleScreen_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_TitleScreenEmerald, 104, YPOS_TITLESCREEN, styles[0]);
    DrawOptionMenuChoice(gText_TitleScreenFireRed, GetStringRightAlignXOffset(FONT_NORMAL, gText_TitleScreenFireRed, 198), YPOS_TITLESCREEN, styles[1]);
}

// PokemonNative3G : cycle jour/nuit (day_night.c) : NON / OUI
static void DayNight_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOff, 104, YPOS_DAYNIGHT, styles[0]);
    DrawOptionMenuChoice(gText_BattleSceneOn, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOn, 198), YPOS_DAYNIGHT, styles[1]);
}

// PokemonNative3G : choix HOENN (Émeraude) / KANTO (Rouge Feu)
static void Region_DrawChoices(u8 selection, u8 y)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_RegionHoenn, 104, y, styles[0]);
    DrawOptionMenuChoice(gText_RegionKanto, GetStringRightAlignXOffset(FONT_NORMAL, gText_RegionKanto, 198), y, styles[1]);
}

// Choix des lignes visibles (défilement)
static void DrawOptionMenuChoices(u8 taskId)
{
    u8 i;

    for (i = 0; i < MENUITEM_COUNT; i++)
    {
        if (!IS_OPTION_ROW_VISIBLE(i))
            continue;
        switch (i)
        {
        case MENUITEM_TEXTSPEED:
            TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
            break;
        case MENUITEM_BATTLESCENE:
            BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
            break;
        case MENUITEM_BATTLESTYLE:
            BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
            break;
        case MENUITEM_SOUND:
            Sound_DrawChoices(gTasks[taskId].tSound);
            break;
        case MENUITEM_BUTTONMODE:
            ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
            break;
        case MENUITEM_FRAMETYPE:
            FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
            break;
        case MENUITEM_CHARACTER:
            Character_DrawChoices(gTasks[taskId].tCharacter);
            break;
        case MENUITEM_TITLESCREEN:
            TitleScreen_DrawChoices(gTasks[taskId].tTitleScreen);
            break;
        case MENUITEM_DIALOGSTYLE:
            Region_DrawChoices(gTasks[taskId].tDialogStyle, YPOS_DIALOGSTYLE);
            break;
        case MENUITEM_FONT:
            Region_DrawChoices(sFont, YPOS_FONT);
            break;
        case MENUITEM_BATTLEUI:
            Region_DrawChoices(gTasks[taskId].tBattleUI, YPOS_BATTLEUI);
            break;
        case MENUITEM_MONSPRITES:
            Region_DrawChoices(gTasks[taskId].tMonSprites, YPOS_MONSPRITES);
            break;
        case MENUITEM_POKEDEXSTYLE:
            Region_DrawChoices(gTasks[taskId].tPokedexStyle, YPOS_POKEDEXSTYLE);
            break;
        case MENUITEM_MENUSTYLE:
            Region_DrawChoices(gTasks[taskId].tMenuStyle, YPOS_MENUSTYLE);
            break;
        case MENUITEM_BAGSTYLE:
            Region_DrawChoices(gTasks[taskId].tBagStyle, YPOS_BAGSTYLE);
            break;
        case MENUITEM_INTRO:
            Region_DrawChoices(gTasks[taskId].tIntro, YPOS_INTRO);
            break;
        case MENUITEM_DAYNIGHT:
            DayNight_DrawChoices(sDayNight);
            break;
        }
    }
}

static void ScrollOptionMenu(u8 taskId)
{
    u8 selection = OptionRow(gTasks[taskId].tMenuSelection);
    u8 offset = sScrollOffset;

    if (selection < offset)
        offset = selection;
    else if (selection >= offset + MAX_VISIBLE_ITEMS)
        offset = selection - MAX_VISIBLE_ITEMS + 1;
    if (offset == sScrollOffset)
        return;
    sScrollOffset = offset;
    DrawOptionMenuTexts();
    DrawOptionMenuChoices(taskId);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

// PokemonNative3G : L/R change de page ; le curseur va sur la première ligne de la nouvelle page
static void ChangeOptionMenuPage(u8 taskId)
{
    sOptionPage = (sOptionPage + 1) % OPTION_PAGE_COUNT;
    gTasks[taskId].tMenuSelection = 0;
    while (IsOptionHidden(gTasks[taskId].tMenuSelection))
        gTasks[taskId].tMenuSelection++;
    sScrollOffset = 0;
    PlaySE(SE_SELECT);
    DrawHeaderText();
    DrawOptionMenuTexts();
    DrawOptionMenuChoices(taskId);
    HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

// ---- Rouge Feu (option_menu.c de RF) : l'écran Options avec Options > MENUS = KANTO (choix user 2026-11-02) ----
// Aspect de RF : cadre standard de RF autour du titre, cadre de l'option FENETRE autour de la liste, bandeau
// « CHOIX / CHANGER / ANNUL. », une valeur par ligne (lignes de 13 px), la ligne choisie éclairée (WIN0). Il garde les
// options de la fusion et leurs deux pages (L/R, défilement, POKéDEX masqué : comme l'écran d'Émeraude plus haut) ;
// la fenêtre de RF montre 7 lignes. L'aide de RF (MODE BOUTONS = AIDE, SetHelpContext) est écartée : la valeur 0 du
// mode des boutons est NORMAL, comme Émeraude. FONT_NORMAL de RF = FONT_KANTO ; GetUserWindowGraphics de RF =
// GetWindowFrameTilesPal ; GetTextWindowPalette(2) de RF = gHelpMessageWindow_Pal ; le CB2 et la VBlank de RF ont le
// code de MainCB2 et VBlankCB.

#define WIN_TEXT_OPTION WIN_HEADER // RF : WIN_TEXT_OPTION, WIN_OPTIONS (les mêmes numéros)

// RAM symbols
struct OptionMenu
{
    u16 option[MENUITEM_COUNT];
    u16 cursorPos;
    u8 loadState;
    u8 state;
    u8 loadPaletteState;
};

static EWRAM_DATA struct OptionMenu *sOptionMenuPtr = NULL;

static void OptionMenu_InitCallbacks(void);
static void OptionMenu_SetVBlankCallback(void);
static void CB2_OptionMenu(void);
static void SetOptionMenuTask(void);
static void InitOptionMenuBg(void);
static void OptionMenu_PickSwitchCancel(void);
static void OptionMenu_ResetSpriteData(void);
static bool8 LoadOptionMenuPalette(void);
static void Task_OptionMenu(u8 taskId);
static u8 OptionMenu_ProcessInput(void);
static void BufferOptionMenuString(u8 selection);
static void CloseAndSaveOptionMenu(u8 taskId);
static void PrintOptionMenuHeader(void);
static void DrawOptionMenuBg(void);
static void LoadOptionMenuItemNames(void);
static void UpdateSettingSelectionDisplay(u16 selection);
static void Localize_BufferOptionMenuString(void);

// Fenêtres et fonds de RF (noms d'Émeraude déjà pris : sKanto…)
static const struct WindowTemplate sKantoOptionMenuWinTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 7,
        .width = 26,
        .height = 12,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x16e
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sKantoOptionMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 2,
       .charBaseIndex = 1,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
       .baseTile = 0
   },
};

static const u16 sOptionMenuPalette[] = INCGFX_U16("graphics/kanto/misc/option_menu.pal", ".gbapal");
// Nombre de valeurs de chaque option (RF : {3, 2, 2, 2, 3, 10, 0}) ; les cadres sont ceux des deux jeux
static const u16 sOptionMenuItemCounts[MENUITEM_COUNT] = {
    [MENUITEM_TEXTSPEED] = 3,
    [MENUITEM_BATTLESCENE] = 2,
    [MENUITEM_BATTLESTYLE] = 2,
    [MENUITEM_SOUND] = 2,
    [MENUITEM_BUTTONMODE] = 3,
    [MENUITEM_FRAMETYPE] = WINDOW_FRAMES_COUNT,
    [MENUITEM_DAYNIGHT] = 2,
    [MENUITEM_CHARACTER] = 2,
    [MENUITEM_MONSPRITES] = 2,
    [MENUITEM_DIALOGSTYLE] = 2,
    [MENUITEM_FONT] = 2,
    [MENUITEM_BATTLEUI] = 2,
    [MENUITEM_MENUSTYLE] = 2,
    [MENUITEM_BAGSTYLE] = 2,
    [MENUITEM_POKEDEXSTYLE] = 2,
    [MENUITEM_TITLESCREEN] = 2,
    [MENUITEM_INTRO] = 2,
    [MENUITEM_CANCEL] = 0,
};

// Valeurs, sans couleur dans le texte (RF les colore : sOptionMenuTextColor) ; textes de RF (strings_*_fr.h)
static const u8 sKText_Text_TextSpeedSlow[] = _("1");
static const u8 sKText_Text_TextSpeedMid[] = _("2");
static const u8 sKText_Text_TextSpeedFast[] = _("3");
static const u8 sKText_Text_BattleSceneOn[] = _("OUI");
static const u8 sKText_Text_BattleSceneOff[] = _("NON");
static const u8 sKText_Text_BattleStyleShift[] = _("CHOIX");
static const u8 sKText_Text_BattleStyleSet[] = _("DEFINI");
static const u8 sKText_Text_SoundMono[] = _("MONO");
static const u8 sKText_Text_SoundStereo[] = _("STEREO");
static const u8 sKText_Text_ButtonTypeNormal[] = _("NORMAL"); // « AIDE » de RF : aide écartée, NORMAL d'Émeraude
static const u8 sKText_Text_ButtonTypeLR[] = _("LR");
static const u8 sKText_Text_ButtonTypeLEqualsA[] = _("L=A");
static const u8 sKText_Text_FrameType[] = _("TYPE");
static const u8 sKText_Text_PickSwitchCancel[] = _("{DPAD_UPDOWN}CHOIX {DPAD_LEFTRIGHT}CHANGER {A_BUTTON}{B_BUTTON}ANNUL.");
// Valeurs des options de la fusion (mêmes mots que l'écran d'Émeraude, sans sa couleur)
static const u8 sKText_RegionHoenn[] = _("HOENN");
static const u8 sKText_RegionKanto[] = _("KANTO");
static const u8 sKText_CharacterBrendan[] = _("BRICE");
static const u8 sKText_CharacterMay[] = _("FLORA");
static const u8 sKText_CharacterRed[] = _("RED");
static const u8 sKText_CharacterLeaf[] = _("LEAF");
static const u8 sKText_TitleScreenEmerald[] = _("ÉMERAUDE");
static const u8 sKText_TitleScreenFireRed[] = _("R.FEU");

static const u8 *const sTextSpeedOptions[] =
{
    sKText_Text_TextSpeedSlow,
    sKText_Text_TextSpeedMid,
    sKText_Text_TextSpeedFast
};

static const u8 *const sBattleSceneOptions[] =
{
    sKText_Text_BattleSceneOn,
    sKText_Text_BattleSceneOff
};

static const u8 *const sBattleStyleOptions[] =
{
    sKText_Text_BattleStyleShift,
    sKText_Text_BattleStyleSet
};

static const u8 *const sSoundOptions[] =
{
    sKText_Text_SoundMono,
    sKText_Text_SoundStereo
};

static const u8 *const sButtonTypeOptions[] =
{
    sKText_Text_ButtonTypeNormal,
    sKText_Text_ButtonTypeLR,
    sKText_Text_ButtonTypeLEqualsA
};

// JOUR/NUIT : 0 = NON (option_menu.c de la fusion : DayNight_DrawChoices)
static const u8 *const sDayNightOptions[] =
{
    sKText_Text_BattleSceneOff,
    sKText_Text_BattleSceneOn
};

static const u8 *const sRegionOptions[] =
{
    sKText_RegionHoenn,
    sKText_RegionKanto
};

static const u8 *const sTitleScreenOptions[] =
{
    sKText_TitleScreenEmerald,
    sKText_TitleScreenFireRed
};

static const u8 sOptionMenuPickSwitchCancelTextColor[] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sOptionMenuTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED};

void CB2_OptionsMenuFromStartMenu(void)
{
    u8 i;

    if (gMain.savedCallback == NULL)
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
    sOptionMenuPtr = AllocZeroed(sizeof(struct OptionMenu));
    sOptionMenuPtr->loadState = 0;
    sOptionMenuPtr->loadPaletteState = 0;
    sOptionMenuPtr->state = 0;
    sOptionMenuPtr->cursorPos = 0;
    sOptionMenuPtr->option[MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
    sOptionMenuPtr->option[MENUITEM_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
    sOptionMenuPtr->option[MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
    sOptionMenuPtr->option[MENUITEM_SOUND] = gSaveBlock2Ptr->optionsSound;
    sOptionMenuPtr->option[MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
    sOptionMenuPtr->option[MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;
    // PokemonNative3G : les options de la fusion (Task_OptionMenuSave plus haut)
    sOptionMenuPtr->option[MENUITEM_DAYNIGHT] = gSaveBlock2Ptr->optionsDayNight;
    sOptionMenuPtr->option[MENUITEM_CHARACTER] = gSaveBlock2Ptr->optionsPlayerCharacter;
    sOptionMenuPtr->option[MENUITEM_MONSPRITES] = gSaveBlock2Ptr->optionsMonSprites;
    sOptionMenuPtr->option[MENUITEM_DIALOGSTYLE] = gSaveBlock2Ptr->optionsDialogStyle;
    sOptionMenuPtr->option[MENUITEM_FONT] = gSaveBlock2Ptr->optionsFont;
    sOptionMenuPtr->option[MENUITEM_BATTLEUI] = gSaveBlock2Ptr->optionsBattleUI;
    sOptionMenuPtr->option[MENUITEM_MENUSTYLE] = gSaveBlock2Ptr->optionsMenuStyle;
    sOptionMenuPtr->option[MENUITEM_BAGSTYLE] = gSaveBlock2Ptr->optionsBagStyle;
    sOptionMenuPtr->option[MENUITEM_POKEDEXSTYLE] = gSaveBlock2Ptr->optionsPokedexStyle;
    sOptionMenuPtr->option[MENUITEM_TITLESCREEN] = gSaveBlock2Ptr->optionsTitleScreen;
    sOptionMenuPtr->option[MENUITEM_INTRO] = !gSaveBlock2Ptr->optionsIntroHoenn; // 1 = KANTO dans le menu

    for (i = 0; i < MENUITEM_COUNT - 1; i++)
    {
        if (sOptionMenuPtr->option[i] > (sOptionMenuItemCounts[i]) - 1)
            sOptionMenuPtr->option[i] = 0;
    }
    sOptionPage = 0;
    sScrollOffset = 0;
    SetMainCallback2(CB2_OptionMenu);
}

static void OptionMenu_InitCallbacks(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void OptionMenu_SetVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB); // VBlankCB_OptionMenu de RF
}

static void CB2_OptionMenu(void)
{
    u8 i, state;
    state = sOptionMenuPtr->state;
    switch (state)
    {
    case 0:
        OptionMenu_InitCallbacks();
        break;
    case 1:
        InitOptionMenuBg();
        break;
    case 2:
        OptionMenu_ResetSpriteData();
        break;
    case 3:
        if (LoadOptionMenuPalette() != TRUE)
            return;
        break;
    case 4:
        PrintOptionMenuHeader();
        break;
    case 5:
        DrawOptionMenuBg();
        break;
    case 6:
        LoadOptionMenuItemNames();
        break;
    case 7:
        for (i = 0; i < MENUITEM_COUNT; i++)
            BufferOptionMenuString(i);
        break;
    case 8:
        UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
        break;
    case 9:
        OptionMenu_PickSwitchCancel();
        break;
    default:
        SetOptionMenuTask();
        break;
    }
    sOptionMenuPtr->state++;
}

static void SetOptionMenuTask(void)
{
    CreateTask(Task_OptionMenu, 0);
    SetMainCallback2(MainCB2); // CB2_InitOptionMenu de RF
}

static void InitOptionMenuBg(void)
{
    void *dest = (void *)VRAM;
    DmaClearLarge16(3, dest, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sKantoOptionMenuBgTemplates, ARRAY_COUNT(sKantoOptionMenuBgTemplates));
    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    ChangeBgX(2, 0, BG_COORD_SET);
    ChangeBgY(2, 0, BG_COORD_SET);
    ChangeBgX(3, 0, BG_COORD_SET);
    ChangeBgY(3, 0, BG_COORD_SET);
    InitWindows(sKantoOptionMenuWinTemplates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_EFFECT_LIGHTEN);
    SetGpuReg(REG_OFFSET_BLDY, BLDCNT_TGT1_BG1);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_CLR);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
}

static void OptionMenu_PickSwitchCancel(void)
{
    s32 x;
    x = 0xE4 - GetStringWidth(FONT_SMALL, sKText_Text_PickSwitchCancel, 0);
    FillWindowPixelBuffer(2, PIXEL_FILL(15));
    AddTextPrinterParameterized3(2, FONT_SMALL, x, 0, sOptionMenuPickSwitchCancelTextColor, 0, sKText_Text_PickSwitchCancel);
    PutWindowTilemap(2);
    CopyWindowToVram(2, COPYWIN_FULL);
}

static void OptionMenu_ResetSpriteData(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static bool8 LoadOptionMenuPalette(void)
{
    switch (sOptionMenuPtr->loadPaletteState)
    {
    case 0:
        LoadBgTiles(1, GetWindowFrameTilesPal(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
        break;
    case 1:
        LoadPalette(GetWindowFrameTilesPal(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->pal, BG_PLTT_ID(2), PLTT_SIZE_4BPP);
        break;
    case 2:
        LoadPalette(sOptionMenuPalette, BG_PLTT_ID(1), sizeof(sOptionMenuPalette));
        LoadPalette(gHelpMessageWindow_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case 3:
        LoadStdWindowGfxOnBg(1, 0x1B3, BG_PLTT_ID(3));
        break;
    default:
        return TRUE;
    }
    sOptionMenuPtr->loadPaletteState++;
    return FALSE;
}

static void Task_OptionMenu(u8 taskId)
{
    switch (sOptionMenuPtr->loadState)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        OptionMenu_SetVBlankCallback();
        sOptionMenuPtr->loadState++;
        break;
    case 1:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 2:
        if (((bool32)IsActiveOverworldLinkBusy()) == TRUE)
            break;
        switch (OptionMenu_ProcessInput())
        {
        case 0:
            break;
        case 1:
            sOptionMenuPtr->loadState++;
            break;
        case 2:
            LoadBgTiles(1, GetWindowFrameTilesPal(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
            LoadPalette(GetWindowFrameTilesPal(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->pal, BG_PLTT_ID(2), PLTT_SIZE_4BPP);
            Localize_BufferOptionMenuString();
            break;
        case 3:
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        case 4:
            Localize_BufferOptionMenuString();
            break;
        case 5: // PokemonNative3G : autre page ou défilement : titre, noms, valeurs, ligne choisie
            PrintOptionMenuHeader();
            LoadOptionMenuItemNames();
            Localize_BufferOptionMenuString();
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        }
        break;
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        sOptionMenuPtr->loadState++;
        break;
    case 4:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 5:
        CloseAndSaveOptionMenu(taskId);
        break;
    }
}

// PokemonNative3G : ligne choisie dans la fenêtre (ScrollOptionMenu plus haut) ; TRUE si la liste a défilé
static bool8 KantoOptionMenu_Scroll(void)
{
    u8 row = OptionRow(sOptionMenuPtr->cursorPos);
    u8 offset = sScrollOffset;

    if (row < offset)
        offset = row;
    else if (row >= offset + MAX_VISIBLE_ITEMS)
        offset = row - MAX_VISIBLE_ITEMS + 1;
    if (offset == sScrollOffset)
        return FALSE;
    sScrollOffset = offset;
    return TRUE;
}

static u8 OptionMenu_ProcessInput(void)
{
    u16 current;
    u16 *curr;
    if (sOptionMenuPtr->cursorPos != MENUITEM_CANCEL && JOY_REPEAT(DPAD_RIGHT)) // RETOUR n'a pas de valeur
    {
        current = sOptionMenuPtr->option[(sOptionMenuPtr->cursorPos)];
        if (current == (sOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
            sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = 0;
        else
            sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = current + 1;
        if (sOptionMenuPtr->cursorPos == MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
    else if (sOptionMenuPtr->cursorPos != MENUITEM_CANCEL && JOY_REPEAT(DPAD_LEFT))
    {
        curr = &sOptionMenuPtr->option[sOptionMenuPtr->cursorPos];
        if (*curr == 0)
            *curr = sOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
        else
            --*curr;

        if (sOptionMenuPtr->cursorPos == MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
    else if (JOY_REPEAT(DPAD_UP))
    {
        // PokemonNative3G : les options de l'autre page et masquées sont sautées
        do
        {
            if (sOptionMenuPtr->cursorPos == MENUITEM_TEXTSPEED)
                sOptionMenuPtr->cursorPos = MENUITEM_CANCEL;
            else
                sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
        } while (IsOptionHidden(sOptionMenuPtr->cursorPos));
        return KantoOptionMenu_Scroll() ? 5 : 3;
    }
    else if (JOY_REPEAT(DPAD_DOWN))
    {
        do
        {
            if (sOptionMenuPtr->cursorPos == MENUITEM_CANCEL)
                sOptionMenuPtr->cursorPos = MENUITEM_TEXTSPEED;
            else
                sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
        } while (IsOptionHidden(sOptionMenuPtr->cursorPos));
        return KantoOptionMenu_Scroll() ? 5 : 3;
    }
    else if (JOY_NEW(L_BUTTON) || JOY_NEW(R_BUTTON)) // PokemonNative3G : page suivante (ChangeOptionMenuPage plus haut)
    {
        sOptionPage = (sOptionPage + 1) % OPTION_PAGE_COUNT;
        sOptionMenuPtr->cursorPos = 0;
        while (IsOptionHidden(sOptionMenuPtr->cursorPos))
            sOptionMenuPtr->cursorPos++;
        sScrollOffset = 0;
        PlaySE(SE_SELECT);
        return 5;
    }
    else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// PokemonNative3G : la valeur affichée d'une option (RF : un tableau par option)
static const u8 *KantoOptionMenu_ValueText(u8 selection)
{
    u16 value = sOptionMenuPtr->option[selection];

    switch (selection)
    {
    case MENUITEM_TEXTSPEED:
        return sTextSpeedOptions[value];
    case MENUITEM_BATTLESCENE:
        return sBattleSceneOptions[value];
    case MENUITEM_BATTLESTYLE:
        return sBattleStyleOptions[value];
    case MENUITEM_SOUND:
        return sSoundOptions[value];
    case MENUITEM_BUTTONMODE:
        return sButtonTypeOptions[value];
    case MENUITEM_DAYNIGHT:
        return sDayNightOptions[value];
    case MENUITEM_CHARACTER:
        if (gSaveBlock2Ptr->playerGender == MALE)
            return value ? sKText_CharacterRed : sKText_CharacterBrendan;
        return value ? sKText_CharacterLeaf : sKText_CharacterMay;
    case MENUITEM_TITLESCREEN:
        return sTitleScreenOptions[value];
    case MENUITEM_MONSPRITES:
    case MENUITEM_DIALOGSTYLE:
    case MENUITEM_FONT:
    case MENUITEM_BATTLEUI:
    case MENUITEM_MENUSTYLE:
    case MENUITEM_BAGSTYLE:
    case MENUITEM_POKEDEXSTYLE:
    case MENUITEM_INTRO:
        return sRegionOptions[value];
    default:
        return NULL;
    }
}

static void BufferOptionMenuString(u8 selection)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y;
    const u8 *text;

    if (!IS_OPTION_ROW_VISIBLE(selection)) // PokemonNative3G : autre page, masquée, ou hors de la fenêtre
        return;
    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT) - 1) * (OptionRow(selection) - sScrollOffset)) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT));

    if (selection == MENUITEM_FRAMETYPE)
    {
        StringCopy(str, sKText_Text_FrameType);
        ConvertIntToDecimalStringN(buf, sOptionMenuPtr->option[selection] + 1, 1, 2);
        StringAppendN(str, buf, 3);
        AddTextPrinterParameterized3(1, FONT_KANTO, x, y, dst, -1, str);
    }
    else if ((text = KantoOptionMenu_ValueText(selection)) != NULL)
    {
        AddTextPrinterParameterized3(1, FONT_KANTO, x, y, dst, -1, text);
    }
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

// RF : toutes les valeurs de nouveau (après un changement de valeur ou de cadre) ; ici, celles des lignes visibles
static void Localize_BufferOptionMenuString(void)
{
    u8 i;
    u8 rowHeight = GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT) - 1;

    FillWindowPixelRect(1, 1, 0x82, 2, 0x46, GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT) + rowHeight * (MAX_VISIBLE_ITEMS - 1));
    for (i = 0; i < MENUITEM_COUNT; i++)
        BufferOptionMenuString(i);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static void CloseAndSaveOptionMenu(u8 taskId)
{
    gFieldCallback = FieldCB_DefaultWarpExit;
    SetMainCallback2(gMain.savedCallback);
    FreeAllWindowBuffers();
    gSaveBlock2Ptr->optionsTextSpeed = sOptionMenuPtr->option[MENUITEM_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleSceneOff = sOptionMenuPtr->option[MENUITEM_BATTLESCENE];
    gSaveBlock2Ptr->optionsBattleStyle = sOptionMenuPtr->option[MENUITEM_BATTLESTYLE];
    gSaveBlock2Ptr->optionsSound = sOptionMenuPtr->option[MENUITEM_SOUND];
    gSaveBlock2Ptr->optionsButtonMode = sOptionMenuPtr->option[MENUITEM_BUTTONMODE];
    gSaveBlock2Ptr->optionsWindowFrameType = sOptionMenuPtr->option[MENUITEM_FRAMETYPE];
    // PokemonNative3G : les options de la fusion (Task_OptionMenuSave plus haut)
    gSaveBlock2Ptr->optionsDayNight = sOptionMenuPtr->option[MENUITEM_DAYNIGHT];
    gSaveBlock2Ptr->optionsPlayerCharacter = sOptionMenuPtr->option[MENUITEM_CHARACTER];
    gSaveBlock2Ptr->optionsMonSprites = sOptionMenuPtr->option[MENUITEM_MONSPRITES];
    gSaveBlock2Ptr->optionsDialogStyle = sOptionMenuPtr->option[MENUITEM_DIALOGSTYLE];
    gSaveBlock2Ptr->optionsFont = sOptionMenuPtr->option[MENUITEM_FONT];
    gSaveBlock2Ptr->optionsBattleUI = sOptionMenuPtr->option[MENUITEM_BATTLEUI];
    gSaveBlock2Ptr->optionsMenuStyle = sOptionMenuPtr->option[MENUITEM_MENUSTYLE];
    gSaveBlock2Ptr->optionsBagStyle = sOptionMenuPtr->option[MENUITEM_BAGSTYLE];
    gSaveBlock2Ptr->optionsPokedexStyle = sOptionMenuPtr->option[MENUITEM_POKEDEXSTYLE];
    gSaveBlock2Ptr->optionsTitleScreen = sOptionMenuPtr->option[MENUITEM_TITLESCREEN];
    gSaveBlock2Ptr->optionsIntroHoenn = !sOptionMenuPtr->option[MENUITEM_INTRO];
    sScrollOffset = 0;
    sOptionPage = 0;
    SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
    FREE_AND_SET_NULL(sOptionMenuPtr);
    DestroyTask(taskId);
}

static void PrintOptionMenuHeader(void)
{
    // PokemonNative3G : la page et ses touches à droite (DrawHeaderText plus haut)
    const u8 *page = sOptionPage == 0 ? sText_OptionPage1 : sText_OptionPage2;

    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_TEXT_OPTION, FONT_KANTO, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_TEXT_OPTION, FONT_KANTO, page, GetStringRightAlignXOffset(FONT_KANTO, page, 26 * 8) - 4, 1, TEXT_SKIP_DRAW, NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void DrawOptionMenuBg(void)
{
    u8 h;
    h = 2;

    FillBgTilemapBufferRect(1, 0x1B3, 1, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B4, 2, 2, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B5, 0x1C, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B6, 1, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B8, 0x1C, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B9, 1, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BA, 2, 5, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BB, 0x1C, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1AA, 1, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AB, 2, 6, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1AC, 0x1C, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AD, 1, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1AF, 0x1C, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1B0, 1, 0x13, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1B1, 2, 0x13, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1B2, 0x1C, 0x13, 1, 1, h);
    CopyBgTilemapBufferToVram(1);
}

static void LoadOptionMenuItemNames(void)
{
    u8 i;

    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    for (i = 0; i < MENUITEM_COUNT; i++)
    {
        if (IS_OPTION_ROW_VISIBLE(i)) // PokemonNative3G : la page, les lignes visibles
            AddTextPrinterParameterized(WIN_OPTIONS, FONT_KANTO, sOptionMenuItemsNames[i], 8, (u8)(((OptionRow(i) - sScrollOffset) * (GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - (OptionRow(i) - sScrollOffset), TEXT_SKIP_DRAW, NULL);
    }
}

static void UpdateSettingSelectionDisplay(u16 selection)
{
    u16 maxLetterHeight, y;

    maxLetterHeight = GetFontAttribute(FONT_KANTO, FONTATTR_MAX_LETTER_HEIGHT);
    y = (OptionRow(selection) - sScrollOffset) * (maxLetterHeight - 1) + 0x3A;
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(y, y + maxLetterHeight));
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0x10, 0xE0));
}
