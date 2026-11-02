// PokemonNative3G : les outils de debug dans le menu DEBUG (builds KANTO_DEBUG=1), voir include/debug_tools.h.
// Catégories, puis commandes, puis leurs nombres (HAUT/BAS change le chiffre, GAUCHE/DROITE choisit le chiffre), puis
// le résultat, qui défile : HAUT/BAS une ligne, GAUCHE/DROITE une page, A relance la commande (état en direct),
// B revient en arrière. Les mêmes commandes que le banc headless (« !dev ») et la console du PC.
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "debug_tools.h"

#ifdef KANTO_DEBUG_START
#include "debug_menu.h"
#include "platform/devtools.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/songs.h"

#define tState      data[0]
#define tWindowId   data[1]
#define tListTaskId data[2]
#define tCategory   data[3]
#define tTool       data[4]
#define tArg        data[5]
#define tDigit      data[6]
#define tScroll     data[7]
#define tFromDebug  data[8] // ouvert sur un résultat depuis le menu DEBUG : B y revient

enum
{
    STATE_CATEGORIES,
    STATE_TOOLS,
    STATE_ARGS,
    STATE_RESULT,
};

#define ARG_DIGITS 5
#define RESULT_WIDTH 28
#define RESULT_HEIGHT 14
#define RESULT_LINE_HEIGHT 12
#define RESULT_LINES_SHOWN ((RESULT_HEIGHT * 8 - RESULT_LINE_HEIGHT - 1) / RESULT_LINE_HEIGHT)
#define MAX_LINES 600
#define LINE_SIZE 80

static struct ListMenuItem sItems[DEBUG_TOOLS_CATEGORY_COUNT > 32 ? DEBUG_TOOLS_CATEGORY_COUNT : 32];
static u8 sItemTools[32];
static s32 sArgs[DEBUG_TOOLS_MAX_ARGS];
static char sOutput[16384];
static u8 sLines[MAX_LINES][LINE_SIZE];
static u16 sLineCount;
static u16 sCategoryRow, sToolRow;

static const u8 sHeaderColors[] = {TEXT_COLOR_WHITE, TEXT_COLOR_BLUE, TEXT_COLOR_LIGHT_BLUE};
// Les lignes du résultat, sur fond transparent : espacées de 12 px, les jambages (g, p, y) de la police SMALL
// descendent dans la ligne suivante, dont le fond les effaçait (détecteur « texte superposé »)
static const u8 sLineColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};

static void Task_DebugToolsMenu(u8 taskId);

// --- Listes (catégories, commandes) ---------------------------------------------------------------------------

static void DrawList(u8 taskId, u32 count, u16 selectedRow)
{
    struct Task *task = &gTasks[taskId];
    struct ListMenuTemplate t = {0};
    struct WindowTemplate win;
    u8 shown = count > 6 ? 6 : count;

    // Comme le menu DEBUG : 18 colonnes, tiles 0x64 et suivants (avant les cadres des boîtes, en 0x200)
    win = CreateWindowTemplate(0, 1, 1, 18, shown * 2, 0xF, 0x64);
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
    if (selectedRow >= count)
        selectedRow = 0;
    task->tListTaskId = ListMenuInit(&t, selectedRow >= shown ? selectedRow - shown + 1 : 0,
                                     selectedRow >= shown ? shown - 1 : selectedRow);
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
    ScheduleBgCopyTilemapToVram(0);
}

static u16 EraseList(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u16 scroll, row;

    DestroyListMenuTask(task->tListTaskId, &scroll, &row);
    ClearStdWindowAndFrame(task->tWindowId, TRUE);
    RemoveWindow(task->tWindowId);
    return scroll + row;
}

static void EraseWindow(u8 taskId)
{
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);
}

static void ShowCategories(u8 taskId)
{
    u32 i;

    for (i = 0; i < DEBUG_TOOLS_CATEGORY_COUNT; i++)
    {
        sItems[i].name = gDebugToolsCategoryNames[i];
        sItems[i].id = i;
    }
    gTasks[taskId].tState = STATE_CATEGORIES;
    DrawList(taskId, DEBUG_TOOLS_CATEGORY_COUNT, sCategoryRow);
}

static void ShowTools(u8 taskId)
{
    u32 i, count = 0;

    for (i = 0; i < gDebugToolsCount && count < ARRAY_COUNT(sItemTools); i++)
    {
        if (gDebugTools[i].category != gTasks[taskId].tCategory)
            continue;
        sItems[count].name = gDebugTools[i].name;
        sItems[count].id = count;
        sItemTools[count++] = i;
    }
    gTasks[taskId].tState = STATE_TOOLS;
    DrawList(taskId, count, sToolRow);
}

// --- Saisie des nombres ---------------------------------------------------------------------------------------

static void DrawArgs(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    const struct DebugTool *tool = &gDebugTools[task->tTool];
    char text[64];
    u8 gameText[64];
    s32 value = sArgs[task->tArg];
    u32 x;

    snprintf(text, sizeof(text), "Nombre %d/%d : %05d", task->tArg + 1, tool->argCount, (int)value);
    DebugTools_ToGameText(gameText, text, sizeof(gameText));
    FillWindowPixelBuffer(task->tWindowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(task->tWindowId, FONT_NORMAL, tool->name, 2, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(task->tWindowId, FONT_NORMAL, gameText, 2, 17, TEXT_SKIP_DRAW, NULL);
    // Le chiffre choisi : une flèche sous lui (chiffres de 6 pixels dans les deux polices)
    snprintf(text, sizeof(text), "Nombre %d/%d : ", task->tArg + 1, tool->argCount);
    DebugTools_ToGameText(gameText, text, sizeof(gameText));
    x = 2 + GetStringWidth(FONT_NORMAL, gameText, 0) + task->tDigit * 6;
    gameText[0] = CHAR_UP_ARROW;
    gameText[1] = EOS;
    AddTextPrinterParameterized(task->tWindowId, FONT_SMALL, gameText, x, 31, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
}

static void ShowArgs(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct WindowTemplate win = CreateWindowTemplate(0, 1, 1, 24, 6, 0xF, 0x64);

    task->tWindowId = AddWindow(&win);
    SetStandardWindowBorderStyle(task->tWindowId, FALSE);
    task->tState = STATE_ARGS;
    task->tArg = 0;
    task->tDigit = ARG_DIGITS - 1;
    memset(sArgs, 0, sizeof(sArgs));
    DrawArgs(taskId);
    ScheduleBgCopyTilemapToVram(0);
}

// --- Résultat -------------------------------------------------------------------------------------------------

static void AddLine(const u8 *text, u32 length)
{
    if (sLineCount >= MAX_LINES)
        return;
    if (length >= LINE_SIZE)
        length = LINE_SIZE - 1;
    memcpy(sLines[sLineCount], text, length);
    sLines[sLineCount++][length] = EOS;
}

// Le texte de la commande (adresses nommées), en lignes du jeu assez courtes pour la fenêtre (coupées aux espaces)
static void SplitOutput(void)
{
    static u8 sGameLine[512];
    static char sNamed[20000];
    char line[512];
    const char *start = sNamed;

    DevTools_NameAddresses(sNamed, sOutput, sizeof(sNamed));
    u32 maxWidth = RESULT_WIDTH * 8 - 4;

    sLineCount = 0;
    while (*start != '\0' && sLineCount < MAX_LINES)
    {
        const char *end = strchr(start, '\n');
        u32 length = end != NULL ? (u32)(end - start) : strlen(start);
        u32 i, lineStart = 0, lastSpace = 0, width = 0;

        if (length >= sizeof(line))
            length = sizeof(line) - 1;
        memcpy(line, start, length);
        line[length] = '\0';
        DebugTools_ToGameText(sGameLine, line, sizeof(sGameLine));
        for (i = 0; sGameLine[i] != EOS; i++)
        {
            u8 glyph[2] = {sGameLine[i], EOS};

            if (sGameLine[i] == CHAR_SPACE)
                lastSpace = i;
            width += GetStringWidth(FONT_SMALL, glyph, 0);
            if (width > maxWidth || i - lineStart >= LINE_SIZE - 2)
            {
                u32 cut = lastSpace > lineStart ? lastSpace : i;

                AddLine(&sGameLine[lineStart], cut - lineStart);
                lineStart = sGameLine[cut] == CHAR_SPACE ? cut + 1 : cut;
                lastSpace = lineStart;
                width = 0;
                i = lineStart - 1;
            }
        }
        if (i > lineStart || length == 0)
            AddLine(&sGameLine[lineStart], i - lineStart);
        start = end != NULL ? end + 1 : start + length;
    }
}

static void DrawResult(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    char header[64];
    u8 gameText[LINE_SIZE];
    u32 i;

    FillWindowPixelBuffer(task->tWindowId, PIXEL_FILL(1));
    snprintf(header, sizeof(header), "%s  %d-%d/%d  A:relancer B:retour", gDebugTools[task->tTool].id,
             sLineCount == 0 ? 0 : task->tScroll + 1, min(task->tScroll + RESULT_LINES_SHOWN, sLineCount), sLineCount);
    DebugTools_ToGameText(gameText, header, sizeof(gameText));
    AddTextPrinterParameterized3(task->tWindowId, FONT_SMALL, 2, 0, sHeaderColors, TEXT_SKIP_DRAW, gameText);
    for (i = 0; i < RESULT_LINES_SHOWN && task->tScroll + i < sLineCount; i++)
        AddTextPrinterParameterized3(task->tWindowId, FONT_SMALL, 2, RESULT_LINE_HEIGHT + 1 + i * RESULT_LINE_HEIGHT,
                                     sLineColors, TEXT_SKIP_DRAW, sLines[task->tScroll + i]);
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
}

static void RunTool(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    const struct DebugTool *tool = &gDebugTools[task->tTool];
    struct DebugToolsOutput out = {sOutput, sizeof(sOutput), 0};
    char line[96];
    u32 i, length;

    length = snprintf(line, sizeof(line), "%s", tool->id);
    for (i = 0; i < tool->argCount && length < sizeof(line); i++)
        length += snprintf(line + length, sizeof(line) - length, " %d", (int)sArgs[i]);
    DebugTools_RunLine(line, &out);
    SplitOutput();
    if (task->tScroll + RESULT_LINES_SHOWN > sLineCount)
        task->tScroll = sLineCount > RESULT_LINES_SHOWN ? sLineCount - RESULT_LINES_SHOWN : 0;
}

static void ShowResult(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct WindowTemplate win = CreateWindowTemplate(0, 1, 1, RESULT_WIDTH, RESULT_HEIGHT, 0xF, 0x64);

    task->tWindowId = AddWindow(&win);
    SetStandardWindowBorderStyle(task->tWindowId, FALSE);
    task->tState = STATE_RESULT;
    task->tScroll = 0;
    RunTool(taskId);
    DrawResult(taskId);
    ScheduleBgCopyTilemapToVram(0);
}

// --- Tâche ----------------------------------------------------------------------------------------------------

static void ScrollResult(u8 taskId, s32 lines)
{
    struct Task *task = &gTasks[taskId];
    s32 scroll = task->tScroll + lines;
    s32 last = sLineCount > RESULT_LINES_SHOWN ? sLineCount - RESULT_LINES_SHOWN : 0;

    if (scroll > last)
        scroll = last;
    if (scroll < 0)
        scroll = 0;
    if (scroll != task->tScroll)
    {
        task->tScroll = scroll;
        DrawResult(taskId);
    }
}

static void HandleArgsInput(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 power = 1, digit, i;

    for (i = 0; i < ARG_DIGITS - 1 - task->tDigit; i++)
        power *= 10;
    digit = (sArgs[task->tArg] / power) % 10;
    if (JOY_REPEAT(DPAD_UP))
        sArgs[task->tArg] += digit == 9 ? -9 * power : power;
    else if (JOY_REPEAT(DPAD_DOWN))
        sArgs[task->tArg] += digit == 0 ? 9 * power : -power;
    else if (JOY_REPEAT(DPAD_LEFT) && task->tDigit > 0)
        task->tDigit--;
    else if (JOY_REPEAT(DPAD_RIGHT) && task->tDigit < ARG_DIGITS - 1)
        task->tDigit++;
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (++task->tArg < gDebugTools[task->tTool].argCount)
        {
            task->tDigit = ARG_DIGITS - 1;
        }
        else
        {
            EraseWindow(taskId);
            ShowResult(taskId);
            return;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        EraseWindow(taskId);
        ShowTools(taskId);
        return;
    }
    else
    {
        return;
    }
    DrawArgs(taskId);
}

static void Task_DebugToolsMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 input;

    switch (task->tState)
    {
    case STATE_CATEGORIES:
        input = ListMenu_ProcessInput(task->tListTaskId);
        if (input == LIST_NOTHING_CHOSEN)
            return;
        PlaySE(SE_SELECT);
        sCategoryRow = EraseList(taskId);
        if (input == LIST_CANCEL)
        {
            DestroyTask(taskId);
            DebugMenu_Open();
            return;
        }
        task->tCategory = input;
        sToolRow = 0;
        ShowTools(taskId);
        break;
    case STATE_TOOLS:
        input = ListMenu_ProcessInput(task->tListTaskId);
        if (input == LIST_NOTHING_CHOSEN)
            return;
        PlaySE(SE_SELECT);
        sToolRow = EraseList(taskId);
        if (input == LIST_CANCEL)
        {
            ShowCategories(taskId);
            return;
        }
        task->tTool = sItemTools[input];
        if (gDebugTools[task->tTool].argCount != 0)
            ShowArgs(taskId);
        else
            ShowResult(taskId);
        break;
    case STATE_ARGS:
        HandleArgsInput(taskId);
        break;
    case STATE_RESULT:
        if (JOY_REPEAT(DPAD_DOWN))
            ScrollResult(taskId, 1);
        else if (JOY_REPEAT(DPAD_UP))
            ScrollResult(taskId, -1);
        else if (JOY_REPEAT(DPAD_RIGHT))
            ScrollResult(taskId, RESULT_LINES_SHOWN);
        else if (JOY_REPEAT(DPAD_LEFT))
            ScrollResult(taskId, -RESULT_LINES_SHOWN);
        else if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            RunTool(taskId);
            DrawResult(taskId);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            EraseWindow(taskId);
            if (task->tFromDebug)
            {
                DestroyTask(taskId);
                DebugMenu_Open();
                return;
            }
            ShowTools(taskId);
        }
        break;
    }
}

void DebugToolsMenu_Open(void)
{
    u8 taskId = CreateTask(Task_DebugToolsMenu, 80);

    ShowCategories(taskId);
}

void DebugToolsMenu_OpenResult(const char *id)
{
    u8 taskId = CreateTask(Task_DebugToolsMenu, 80);
    const struct DebugTool *tool = DebugTools_Find(id);

    if (tool == NULL)
    {
        ShowCategories(taskId);
        return;
    }
    gTasks[taskId].tTool = tool - gDebugTools;
    gTasks[taskId].tFromDebug = TRUE;
    ShowResult(taskId);
}

#endif // KANTO_DEBUG_START
