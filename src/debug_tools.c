// PokemonNative3G : outils de debug (builds KANTO_DEBUG=1), voir include/debug_tools.h et docs/DEVTOOLS.md.
// Chaque commande lit l'état réel du jeu (pas ce que le code devrait faire) et l'écrit en texte, une information par
// ligne. Les adresses de fonctions et de données sont écrites « @N » (distance à AgbMain) : le banc et la console
// (test/headless/dev.py) les remplacent par leur nom, lu dans les symboles de la build.
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "debug_tools.h"

#ifdef KANTO_DEBUG_START
#include "gba/m4a_internal.h"
#include "battle.h"
#include "battle_setup.h"
#include "day_night.h"
#include "debug_menu.h"
#include "debug_checks.h"
#ifdef PORTABLE
#include "platform/devtools.h"
#endif
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "fusion_region.h"
#include "gpu_regs.h"
#include "item.h"
#include "m4a.h"
#include "main.h"
#include "metatile_behavior.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "random.h"
#include "region_map.h"
#include "roamer.h"
#include "rtc.h"
#include "safari_zone.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "start_menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/characters.h"
#include "constants/moves.h"
#include "constants/flags.h"
#include "constants/game_stat.h"
#include "constants/vars.h"
#include "constants/kanto.h"
#include "constants/kanto_flags_vars.h"
#include "constants/opponents.h"
#include "constants/kanto_trainers.h"

// Les noms des drapeaux, variables et dresseurs (tools/debug_names.py), par catégorie
enum { DEBUG_NAME_FLAG, DEBUG_NAME_VAR, DEBUG_NAME_TRAINER };

struct DebugName
{
    u16 id;             // le drapeau, la variable, ou le numéro du dresseur (son drapeau : HasTrainerBeenFought)
    u8 category;        // sDebugNameCategories
    u8 kind;            // DEBUG_NAME_*
    const char *name;
};

#include "data/debug_names.h"
#include "data/debug_states.h"

extern void AgbMain(void);

void DebugTools_Print(struct DebugToolsOutput *out, const char *format, ...)
{
    va_list args;
    int length;

    if (out->length + 1 >= out->size)
        return;
    va_start(args, format);
    length = vsnprintf(out->text + out->length, out->size - out->length, format, args);
    va_end(args);
    if (length < 0)
        return;
    out->length += length;
    if (out->length >= out->size)
        out->length = out->size - 1;
}

long long DebugTools_Offset(const void *address)
{
    return address == NULL ? 0 : (long long)((uintptr_t)address - (uintptr_t)AgbMain);
}

// --- Texte du jeu <-> UTF-8 -----------------------------------------------------------------------------------

static const struct { const char *utf8; u8 game; } sTextChars[] =
{
    {" ", CHAR_SPACE}, {"!", CHAR_EXCL_MARK}, {"?", CHAR_QUESTION_MARK}, {".", CHAR_PERIOD}, {"-", CHAR_HYPHEN},
    {",", CHAR_COMMA}, {"/", CHAR_SLASH}, {":", CHAR_COLON}, {";", CHAR_SEMICOLON}, {"(", 0x5C}, {")", 0x5D},
    {"%", 0x5B}, {"&", 0x2D}, {"+", 0x2E}, {"=", 0x35}, {"<", 0x85}, {">", 0x86}, {"'", 0xB4}, {"\"", 0xB1},
    {"é", 0x1B}, {"è", 0x1A}, {"ê", 0x1C}, {"ë", 0x1D}, {"à", 0x16}, {"â", 0x68}, {"ä", 0xF4}, {"î", 0x20},
    {"ï", 0x21}, {"ô", 0x24}, {"ö", 0xF5}, {"ù", 0x26}, {"û", 0x28}, {"ü", 0xF6}, {"ç", 0x19}, {"É", 0x06},
    {"È", 0x05}, {"Ê", 0x07}, {"À", 0x01}, {"Â", 0x03}, {"Î", 0x0B}, {"Ô", 0x0F}, {"Ù", 0x11}, {"Û", 0x13},
    {"Ç", 0x04}, {"_", CHAR_SPACE}, {"@", CHAR_QUESTION_MARK},
};

void DebugTools_ToGameText(u8 *dest, const char *src, u32 destSize)
{
    u32 n = 0, i;

    while (*src != '\0' && n + 1 < destSize)
    {
        if (*src == '\n')
        {
            dest[n++] = CHAR_NEWLINE;
            src++;
            continue;
        }
        if (*src >= '0' && *src <= '9')
        {
            dest[n++] = CHAR_0 + (*src++ - '0');
            continue;
        }
        if (*src >= 'A' && *src <= 'Z')
        {
            dest[n++] = CHAR_A + (*src++ - 'A');
            continue;
        }
        if (*src >= 'a' && *src <= 'z')
        {
            dest[n++] = CHAR_a + (*src++ - 'a');
            continue;
        }
        for (i = 0; i < ARRAY_COUNT(sTextChars); i++)
        {
            u32 length = strlen(sTextChars[i].utf8);

            if (strncmp(src, sTextChars[i].utf8, length) == 0)
            {
                dest[n++] = sTextChars[i].game;
                src += length;
                break;
            }
        }
        if (i == ARRAY_COUNT(sTextChars))
        {
            dest[n++] = CHAR_QUESTION_MARK;
            // Le reste du caractère UTF-8
            for (src++; (*src & 0xC0) == 0x80; src++)
                ;
        }
    }
    dest[n] = EOS;
}

// Texte du jeu -> UTF-8 (noms, surnoms, textes des anomalies) ; les caractères sans équivalent deviennent « ? »
void DebugTools_GameTextToUtf8(char *dest, const u8 *src, u32 destSize)
{
    u32 n = 0, i;

    for (; *src != EOS && n + 4 < destSize; src++)
    {
        if (*src >= CHAR_0 && *src <= CHAR_9)
            dest[n++] = '0' + (*src - CHAR_0);
        else if (*src >= CHAR_A && *src <= CHAR_Z)
            dest[n++] = 'A' + (*src - CHAR_A);
        else if (*src >= CHAR_a && *src <= CHAR_z)
            dest[n++] = 'a' + (*src - CHAR_a);
        else if (*src == CHAR_NEWLINE || *src == CHAR_PROMPT_SCROLL || *src == CHAR_PROMPT_CLEAR)
            dest[n++] = ' ';
        else if (*src == CHAR_KEYPAD_ICON && src[1] != EOS)
        {
            static const char *const sButtons[] = {"A", "B", "L", "R", "START", "SELECT"};

            src++;
            n += snprintf(dest + n, destSize - n, "[%s]", *src < ARRAY_COUNT(sButtons) ? sButtons[*src] : "+");
        }
        else if (*src == EXT_CTRL_CODE_BEGIN && src[1] != EOS)
        {
            // Couleur, police, pause… : rien à lire, ses arguments sont sautés
            u32 length = GetExtCtrlCodeLength(src[1]);

            for (i = 0; i < length && src[1] != EOS; i++)
                src++;
        }
        else if ((*src == PLACEHOLDER_BEGIN || *src == CHAR_EXTRA_SYMBOL) && src[1] != EOS)
        {
            src++;
            n += snprintf(dest + n, destSize - n, "{%02X}", *src);
        }
        else
        {
            for (i = 0; i < ARRAY_COUNT(sTextChars); i++)
            {
                if (sTextChars[i].game == *src)
                {
                    n += snprintf(dest + n, destSize - n, "%s", sTextChars[i].utf8);
                    break;
                }
            }
            if (i == ARRAY_COUNT(sTextChars))
                dest[n++] = '?';
        }
    }
    if (n >= destSize)      // snprintf a tronqué : n compte ce qu'il aurait écrit
        n = destSize - 1;
    dest[n] = '\0';
}

// --- Commandes : jeu ------------------------------------------------------------------------------------------

static void Cmd_GameState(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    DebugTools_Print(out, "image %u\n", gMain.vblankCounter1);
    DebugTools_Print(out, "cb1 @%lld\ncb2 @%lld\nvblank @%lld\nhblank @%lld\n", DebugTools_Offset(gMain.callback1),
                     DebugTools_Offset(gMain.callback2), DebugTools_Offset(gMain.vblankCallback),
                     DebugTools_Offset(gMain.hblankCallback));
    DebugTools_Print(out, "combat %d, fondu %d (y %d -> %d), controles bloques %d, script %d\n", gMain.inBattle,
                     gPaletteFade.active, gPaletteFade.y, gPaletteFade.targetY, ArePlayerFieldControlsLocked(),
                     ScriptContext_IsEnabled());
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (gTasks[i].isActive)
            DebugTools_Print(out, "tache %u @%lld prio %d data %d %d %d %d\n", i, DebugTools_Offset(gTasks[i].func),
                             gTasks[i].priority, gTasks[i].data[0], gTasks[i].data[1], gTasks[i].data[2],
                             gTasks[i].data[3]);
    }
}

enum
{
    OPTION_TEXT_SPEED,
    OPTION_FRAME,
    OPTION_SOUND,
    OPTION_BATTLE_STYLE,
    OPTION_BATTLE_SCENE_OFF,
    OPTION_BUTTON_MODE,
    OPTION_PLAYER_CHARACTER,
    OPTION_TITLE_SCREEN,
    OPTION_DIALOG_STYLE,
    OPTION_FONT,
    OPTION_POKEDEX_STYLE,
    OPTION_MENU_STYLE,
    OPTION_BATTLE_UI,
    OPTION_BAG_STYLE,
    OPTION_MON_SPRITES,
    OPTION_INTRO_HOENN,
    OPTION_DAY_NIGHT,
    OPTION_COUNT,
};

static const char *const sOptionNames[OPTION_COUNT] =
{
    [OPTION_TEXT_SPEED]       = "VITESSE TEXTE",
    [OPTION_FRAME]            = "FENETRE",
    [OPTION_SOUND]            = "SON",
    [OPTION_BATTLE_STYLE]     = "STYLE COMBAT",
    [OPTION_BATTLE_SCENE_OFF] = "ANIM. COMBAT (1 = non)",
    [OPTION_BUTTON_MODE]      = "TOUCHES",
    [OPTION_PLAYER_CHARACTER] = "PERSO (1 = Red/Leaf)",
    [OPTION_TITLE_SCREEN]     = "TITRE (1 = R.Feu)",
    [OPTION_DIALOG_STYLE]     = "DIALOGUE (1 = Kanto)",
    [OPTION_FONT]             = "POLICE (1 = Kanto)",
    [OPTION_POKEDEX_STYLE]    = "POKEDEX (1 = Kanto)",
    [OPTION_MENU_STYLE]       = "MENUS (1 = Kanto)",
    [OPTION_BATTLE_UI]        = "BOITES COMBAT (1 = Kanto)",
    [OPTION_BAG_STYLE]        = "SAC (1 = Kanto)",
    [OPTION_MON_SPRITES]      = "POKEMON (1 = Kanto)",
    [OPTION_INTRO_HOENN]      = "INTRO (1 = Hoenn)",
    [OPTION_DAY_NIGHT]        = "JOUR/NUIT",
};

static s32 GetOption(u32 option)
{
    switch (option)
    {
    case OPTION_TEXT_SPEED:       return gSaveBlock2Ptr->optionsTextSpeed;
    case OPTION_FRAME:            return gSaveBlock2Ptr->optionsWindowFrameType;
    case OPTION_SOUND:            return gSaveBlock2Ptr->optionsSound;
    case OPTION_BATTLE_STYLE:     return gSaveBlock2Ptr->optionsBattleStyle;
    case OPTION_BATTLE_SCENE_OFF: return gSaveBlock2Ptr->optionsBattleSceneOff;
    case OPTION_BUTTON_MODE:      return gSaveBlock2Ptr->optionsButtonMode;
    case OPTION_PLAYER_CHARACTER: return gSaveBlock2Ptr->optionsPlayerCharacter;
    case OPTION_TITLE_SCREEN:     return gSaveBlock2Ptr->optionsTitleScreen;
    case OPTION_DIALOG_STYLE:     return gSaveBlock2Ptr->optionsDialogStyle;
    case OPTION_FONT:             return gSaveBlock2Ptr->optionsFont;
    case OPTION_POKEDEX_STYLE:    return gSaveBlock2Ptr->optionsPokedexStyle;
    case OPTION_MENU_STYLE:       return gSaveBlock2Ptr->optionsMenuStyle;
    case OPTION_BATTLE_UI:        return gSaveBlock2Ptr->optionsBattleUI;
    case OPTION_BAG_STYLE:        return gSaveBlock2Ptr->optionsBagStyle;
    case OPTION_MON_SPRITES:      return gSaveBlock2Ptr->optionsMonSprites;
    case OPTION_INTRO_HOENN:      return gSaveBlock2Ptr->optionsIntroHoenn;
    case OPTION_DAY_NIGHT:        return gSaveBlock2Ptr->optionsDayNight;
    }
    return 0;
}

static void SetOption(u32 option, s32 value)
{
    switch (option)
    {
    case OPTION_TEXT_SPEED:       gSaveBlock2Ptr->optionsTextSpeed = value; break;
    case OPTION_FRAME:            gSaveBlock2Ptr->optionsWindowFrameType = value; break;
    case OPTION_SOUND:            gSaveBlock2Ptr->optionsSound = value; break;
    case OPTION_BATTLE_STYLE:     gSaveBlock2Ptr->optionsBattleStyle = value; break;
    case OPTION_BATTLE_SCENE_OFF: gSaveBlock2Ptr->optionsBattleSceneOff = value; break;
    case OPTION_BUTTON_MODE:      gSaveBlock2Ptr->optionsButtonMode = value; break;
    case OPTION_PLAYER_CHARACTER: gSaveBlock2Ptr->optionsPlayerCharacter = value; break;
    case OPTION_TITLE_SCREEN:     gSaveBlock2Ptr->optionsTitleScreen = value; break;
    case OPTION_DIALOG_STYLE:     gSaveBlock2Ptr->optionsDialogStyle = value; break;
    case OPTION_FONT:             gSaveBlock2Ptr->optionsFont = value; break;
    case OPTION_POKEDEX_STYLE:    gSaveBlock2Ptr->optionsPokedexStyle = value; break;
    case OPTION_MENU_STYLE:       gSaveBlock2Ptr->optionsMenuStyle = value; break;
    case OPTION_BATTLE_UI:        gSaveBlock2Ptr->optionsBattleUI = value; break;
    case OPTION_BAG_STYLE:        gSaveBlock2Ptr->optionsBagStyle = value; break;
    case OPTION_MON_SPRITES:      gSaveBlock2Ptr->optionsMonSprites = value; break;
    case OPTION_INTRO_HOENN:      gSaveBlock2Ptr->optionsIntroHoenn = value; break;
    case OPTION_DAY_NIGHT:        gSaveBlock2Ptr->optionsDayNight = value; break;
    }
}

static void Cmd_Options(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    if (argCount >= 2 && (u32)args[0] < OPTION_COUNT)
        SetOption(args[0], args[1]);
    for (i = 0; i < OPTION_COUNT; i++)
        DebugTools_Print(out, "%u %s = %d\n", i, sOptionNames[i], GetOption(i));
}

// Les réglages du menu DEBUG (debug_menu.c) : [V] = 1 oui, 0 non
static void Cmd_NoClip(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (argCount >= 1)
        gDebugNoClip = args[0] != 0;
    DebugTools_Print(out, "traverser les murs : %d\n", gDebugNoClip);
}

static void Cmd_Encounters(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (argCount >= 1)
        gDebugNoEncounters = args[0] == 0;
    DebugTools_Print(out, "rencontres sauvages : %d\n", !gDebugNoEncounters);
}

static void Cmd_Safari(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (argCount >= 1)
        gSafariZoneStepCounter = args[0];
    if (argCount >= 2)
        gNumSafariBalls = args[1];
    DebugTools_Print(out, "safari %d, pas restants %d, balls %d\n", GetSafariZoneFlag() != FALSE,
                     gSafariZoneStepCounter, gNumSafariBalls);
}

// 1 : InitRoamer (les vagabonds de la région, comme leur script) ; 2 : les mettre sur la carte du joueur
static void Cmd_Roamers(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    if (argCount >= 1 && args[0] == 1)
        InitRoamer();
    if (argCount >= 1 && args[0] == 2)
        Roamer_DebugPlaceHere();
    for (i = 0; i < Roamer_DebugCount(); i++)
    {
        u8 group, num;
        const struct Roamer *roamer = Roamer_DebugGet(i, &group, &num);
        DebugTools_Print(out, "errant %u espece %d niveau %d actif %d carte %d.%d PV %d\n", i, roamer->species,
                         roamer->level, roamer->active, group, num, roamer->hp);
    }
}

// Statistique de jeu N (GAME_STAT_*), mise à V si donné (entrées au Panthéon, œufs éclos, victoires en link...)
static void Cmd_GameStatistic(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (args[0] < 0 || args[0] >= NUM_GAME_STATS)
    {
        DebugTools_Print(out, "statistique %d inconnue (0 a %d)\n", args[0], NUM_GAME_STATS - 1);
        return;
    }
    if (argCount >= 2)
        SetGameStat(args[0], args[1]);
    DebugTools_Print(out, "statistique %d = %u\n", args[0], GetGameStat(args[0]));
}

// --- Carte ----------------------------------------------------------------------------------------------------

static const char *const sDirectionNames[] = {"", "sud", "nord", "ouest", "est", "plongee", "emersion"};

static void Cmd_MapInfo(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    const struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];
    u8 name[32];
    char text[48];
    s32 i;

    GetMapName(name, gMapHeader.regionMapSectionId, 0);
    DebugTools_GameTextToUtf8(text, name, sizeof(text));
    DebugTools_Print(out, "carte %d.%d (%s, section %d), %s\n", gSaveBlock1Ptr->location.mapGroup,
                     gSaveBlock1Ptr->location.mapNum, text, gMapHeader.regionMapSectionId,
                     Fusion_IsInKanto() ? "Kanto" : "Hoenn");
    DebugTools_Print(out, "disposition %d (%dx%d), type %d, meteo %d, musique %d\n", gMapHeader.mapLayoutId,
                     gMapHeader.mapLayout->width, gMapHeader.mapLayout->height, gMapHeader.mapType,
                     gMapHeader.weather, gMapHeader.music);
    DebugTools_Print(out, "joueur %d,%d niveau %d, regarde %d, avatar %#x, case %#x\n",
                     player->currentCoords.x - MAP_OFFSET, player->currentCoords.y - MAP_OFFSET,
                     player->currentElevation, player->facingDirection, gPlayerAvatar.flags,
                     MapGridGetMetatileBehaviorAt(player->currentCoords.x, player->currentCoords.y));
    if (gMapHeader.connections != NULL)
    {
        for (i = 0; i < gMapHeader.connections->count; i++)
        {
            const struct MapConnection *connection = &gMapHeader.connections->connections[i];

            DebugTools_Print(out, "connexion %s vers %d.%d, decalage %d\n",
                             connection->direction < ARRAY_COUNT(sDirectionNames) ? sDirectionNames[connection->direction] : "?",
                             connection->mapGroup, connection->mapNum, (s32)connection->offset);
        }
    }
}

static void Cmd_MapObjects(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        const struct ObjectEvent *object = &gObjectEvents[i];

        if (!object->active)
            continue;
        DebugTools_Print(out, "objet %u id %d gfx %#x en %d,%d mouvement %d regarde %d sprite %d%s%s%s\n", i,
                         object->localId, object->graphicsId, object->currentCoords.x - MAP_OFFSET,
                         object->currentCoords.y - MAP_OFFSET, object->movementType, object->facingDirection,
                         object->spriteId, object->isPlayer ? " joueur" : "", object->invisible ? " invisible" : "",
                         object->frozen ? " fige" : "");
    }
}

// Une case de la grille, avec les lettres de test/headless/maps.py
static char GetGridTile(s32 x, s32 y)
{
    u8 behavior = MapGridGetMetatileBehaviorAt(x, y);

    // Un rebord se saute même avec le bit de collision (CheckForObjectEventCollision teste ShouldJumpLedge avant) :
    // c'est le cas des rebords des étages du Mont Combat et de beaucoup de routes de Kanto
    if (MetatileBehavior_IsJumpEast(behavior))
        return '>';
    if (MetatileBehavior_IsJumpWest(behavior))
        return '<';
    if (MetatileBehavior_IsJumpNorth(behavior))
        return '^';
    if (MetatileBehavior_IsJumpSouth(behavior))
        return 'v';
    if (MapGridGetCollisionAt(x, y))
        return '#';
    if (MetatileBehavior_IsTallGrass(behavior) || MetatileBehavior_IsLongGrass(behavior))
        return 'g';
    if (MetatileBehavior_IsSurfableWaterOrUnderwater(behavior) || MetatileBehavior_IsWaterfall(behavior))
        return '~';
    return '.';
}

// La grille de la carte telle qu'elle est en jeu : les étages générés (Mont Combat, Pyramide) et les cases changées
// par les scripts (setmetatile : portes, puzzles), que les fichiers de la carte ne montrent pas
static void Cmd_MapGrid(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    s32 x, y;
    s32 width = gMapHeader.mapLayout->width, height = gMapHeader.mapLayout->height;

    DebugTools_Print(out, "grille %dx%d\n", width, height);
    for (y = 0; y < height; y++)
    {
        char row[256 + 2];
        s32 n = 0;

        for (x = 0; x < width && n < 256; x++)
            row[n++] = GetGridTile(x + MAP_OFFSET, y + MAP_OFFSET);
        row[n++] = '\n';
        row[n] = '\0';
        DebugTools_Print(out, "%s", row);
    }
}

// --- Scripts --------------------------------------------------------------------------------------------------

static void PrintScriptContext(struct DebugToolsOutput *out, const char *name, const struct ScriptContext *ctx)
{
    u32 i;

    DebugTools_Print(out, "%s : mode %d, script @%lld, natif @%lld, pile %d", name, ctx->mode,
                     DebugTools_Offset(ctx->scriptPtr), DebugTools_Offset(ctx->nativePtr), ctx->stackDepth);
    for (i = 0; i < ctx->stackDepth && i < ARRAY_COUNT(ctx->stack); i++)
        DebugTools_Print(out, " @%lld", DebugTools_Offset(ctx->stack[i]));
    DebugTools_Print(out, "\n");
}

static void Cmd_ScriptContext(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u8 status;
    const struct ScriptContext *global = GetGlobalScriptContext(&status);

    DebugTools_Print(out, "contexte global : etat %d (0 en cours, 1 en attente, 2 arrete)\n", status);
    PrintScriptContext(out, "global", global);
    PrintScriptContext(out, "immediat", GetImmediateScriptContext());
}

// Lance un script de carte (son adresse : distance à AgbMain, que les symboles de la build donnent par son nom),
// comme si le joueur avait parlé à quelqu'un ; seulement quand il est libre sur la carte
static void Cmd_RunScript(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (gMain.callback2 != CB2_Overworld || ScriptContext_IsEnabled() || ArePlayerFieldControlsLocked())
    {
        DebugTools_Print(out, "refuse : le joueur n'est pas libre sur la carte\n");
        return;
    }
    ScriptContext_SetupScript((const u8 *)((uintptr_t)AgbMain + (intptr_t)args[0]));
    DebugTools_Print(out, "script @%d lance\n", args[0]);
}

// --- Drapeaux, variables et dresseurs, par nom et par catégorie ----------------------------------------------------

static s32 GetNameState(const struct DebugName *entry)
{
    switch (entry->kind)
    {
    case DEBUG_NAME_FLAG:    return FlagGet(entry->id);
    case DEBUG_NAME_VAR:     return VarGet(entry->id);
    default:                 return HasTrainerBeenFought(entry->id);
    }
}

// Le nom sans « FLAG_ », « VAR_ », « TRAINER_ » ni « KANTO_ » (la catégorie dit déjà la région)
static const char *ShortName(const char *name)
{
    static const char *const sPrefixes[] = {"FLAG_KANTO_", "VAR_KANTO_", "TRAINER_KANTO_", "FLAG_", "VAR_", "TRAINER_"};
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sPrefixes); i++)
    {
        if (strncmp(name, sPrefixes[i], strlen(sPrefixes[i])) == 0)
            return name + strlen(sPrefixes[i]);
    }
    return name;
}

// La N-ième entrée de la catégorie, ou NULL
static const struct DebugName *GetCategoryEntry(u32 category, u32 index)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDebugNames); i++)
    {
        if (sDebugNames[i].category == category && index-- == 0)
            return &sDebugNames[i];
    }
    return NULL;
}

// Sans argument : les catégories (combien sont à ON, ou non nulles). [CAT] : chaque drapeau (ON / --), dresseur
// (battu / --) ou variable (= valeur) de la catégorie. Dans le menu, A les bascule (L / R : variable -1 / +1)
static void Cmd_Names(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i, category, count, set;
    const struct DebugName *entry;

    if (argCount == 0)
    {
        for (category = 0; category < ARRAY_COUNT(sDebugNameCategories); category++)
        {
            for (count = 0, set = 0, i = 0; i < ARRAY_COUNT(sDebugNames); i++)
            {
                if (sDebugNames[i].category != category)
                    continue;
                count++;
                set += GetNameState(&sDebugNames[i]) != 0;
            }
            DebugTools_Print(out, "%s : %u (%u ON)\n", sDebugNameCategories[category], count, set);
        }
        return;
    }
    for (i = 0; (entry = GetCategoryEntry(args[0], i)) != NULL; i++)
    {
        if (entry->kind == DEBUG_NAME_VAR)
            DebugTools_Print(out, "%.34s = %d\n", ShortName(entry->name), GetNameState(entry));
        else
            DebugTools_Print(out, "%.38s %s\n", ShortName(entry->name), GetNameState(entry) ? "ON" : "--");
    }
}

// Menu DEBUG, A (delta 0) ou L / R (delta -1 / +1) sur une ligne : une catégorie s'ouvre ; un drapeau ou un
// dresseur bascule ; une variable change de delta (A : remise à 0)
static void Select_Names(s32 *args, u32 *argCount, u32 line, s32 delta)
{
    const struct DebugName *entry;

    if (*argCount == 0)
    {
        if (line < ARRAY_COUNT(sDebugNameCategories) && delta == 0)
        {
            args[0] = line;
            *argCount = 1;
        }
        return;
    }
    if ((entry = GetCategoryEntry(args[0], line)) == NULL)
        return;
    switch (entry->kind)
    {
    case DEBUG_NAME_FLAG:
        FlagGet(entry->id) ? FlagClear(entry->id) : FlagSet(entry->id);
        break;
    case DEBUG_NAME_VAR:
        VarSet(entry->id, delta == 0 ? 0 : VarGet(entry->id) + delta);
        break;
    default:
        HasTrainerBeenFought(entry->id) ? ClearTrainerFlag(entry->id) : SetTrainerFlag(entry->id);
        break;
    }
}

// Les histoires finies (tools/debug_states.py, déduites des scripts) : sans argument la liste ; [N] pose l'état N
static void Cmd_Story(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    static const char *const sStoryNames[] = {"Hoenn : histoire finie", "Kanto : histoire finie",
                                              "Hoenn et Kanto : histoires finies"};
    u32 i, flags = 0, vars = 0;

    if (argCount == 0 || (u32)args[0] >= ARRAY_COUNT(sStoryNames))
    {
        for (i = 0; i < ARRAY_COUNT(sStoryNames); i++)
            DebugTools_Print(out, "%u %s\n", i, sStoryNames[i]);
        return;
    }
    if (args[0] != 1)
    {
        for (i = 0; i < ARRAY_COUNT(sStoryFlags_Hoenn); i++, flags++)
            FlagSet(sStoryFlags_Hoenn[i]);
        for (i = 0; i < ARRAY_COUNT(sStoryVars_Hoenn); i++, vars++)
            VarSet(sStoryVars_Hoenn[i][0], sStoryVars_Hoenn[i][1]);
    }
    if (args[0] != 0)
    {
        for (i = 0; i < ARRAY_COUNT(sStoryFlags_Kanto); i++, flags++)
            FlagSet(sStoryFlags_Kanto[i]);
        for (i = 0; i < ARRAY_COUNT(sStoryVars_Kanto); i++, vars++)
            VarSet(sStoryVars_Kanto[i][0], sStoryVars_Kanto[i][1]);
    }
    DebugTools_Print(out, "fait : %s (%u drapeaux, %u variables)\n", sStoryNames[args[0]], flags, vars);
}

// Menu DEBUG : A sur une histoire la pose (le résultat le dit) ; B revient à la liste
static void Select_Story(s32 *args, u32 *argCount, u32 line, s32 delta)
{
    if (*argCount == 0 && delta == 0)
    {
        args[0] = line;
        *argCount = 1;
    }
}

// Un nom de drapeau, de variable ou de dresseur (« FLAG_SYS_GAME_CLEAR ») -> son numéro ; FALSE s'il n'existe pas
static bool8 GetNameValue(const char *name, s32 *value)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDebugNames); i++)
    {
        if (strcmp(sDebugNames[i].name, name) == 0)
        {
            *value = sDebugNames[i].id;
            return TRUE;
        }
    }
    return FALSE;
}

// Le nom d'un drapeau ou d'une variable, « ? » sans nom
static const char *GetIdName(u8 kind, u16 id)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDebugNames); i++)
    {
        if (sDebugNames[i].kind == kind && sDebugNames[i].id == id)
            return sDebugNames[i].name;
    }
    return "?";
}

static void Cmd_Flag(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (argCount >= 2)
        args[1] ? FlagSet(args[0]) : FlagClear(args[0]);
    DebugTools_Print(out, "flag %d %s = %d\n", args[0], GetIdName(DEBUG_NAME_FLAG, args[0]), FlagGet(args[0]));
}

static void Cmd_Var(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    if (argCount >= 2)
        VarSet(args[0], args[1]);
    DebugTools_Print(out, "var %#x %s = %d\n", args[0], GetIdName(DEBUG_NAME_VAR, args[0]), VarGet(args[0]));
}

// --- Joueur ---------------------------------------------------------------------------------------------------

static void Cmd_Party(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u8 nickname[POKEMON_NAME_BUFFER_SIZE];
        char text[48];

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            continue;
        GetMonData(mon, MON_DATA_NICKNAME, nickname);
        DebugTools_GameTextToUtf8(text, nickname, sizeof(text));
        DebugTools_Print(out, "%u %s espece %d N.%d PV %d/%d statut %#x objet %d\n", i, text,
                         GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_LEVEL),
                         GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP),
                         GetMonData(mon, MON_DATA_STATUS), GetMonData(mon, MON_DATA_HELD_ITEM));
        DebugTools_Print(out, "  DO %u (joueur %u), lieu %d, jeu %d, N.rencontre %d, oeuf %d, perso %#x\n",
                         GetMonData(mon, MON_DATA_OT_ID),
                         (u32)gSaveBlock2Ptr->playerTrainerId[0] | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
                       | (gSaveBlock2Ptr->playerTrainerId[2] << 16) | ((u32)gSaveBlock2Ptr->playerTrainerId[3] << 24),
                         GetMonData(mon, MON_DATA_MET_LOCATION), GetMonData(mon, MON_DATA_MET_GAME),
                         GetMonData(mon, MON_DATA_MET_LEVEL), GetMonData(mon, MON_DATA_IS_EGG),
                         GetMonData(mon, MON_DATA_PERSONALITY));
    }
}

// Donne une capacité (avec ses PP) au Pokémon N de l'équipe, à la place P (0 à 3)
static void Cmd_SetMove(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    struct Pokemon *mon;

    if ((u32)args[0] >= PARTY_SIZE || (u32)args[1] >= MAX_MON_MOVES || (u32)args[2] >= MOVES_COUNT)
    {
        DebugTools_Print(out, "refuse : equipe 0-5, place 0-3, capacite < %d\n", MOVES_COUNT);
        return;
    }
    mon = &gPlayerParty[args[0]];
    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
    {
        DebugTools_Print(out, "refuse : pas de Pokemon en %d\n", args[0]);
        return;
    }
    SetMonMoveSlot(mon, args[2], args[1]);
    DebugTools_Print(out, "Pokemon %d : capacite %d en place %d, PP %d\n", args[0], GetMonData(mon, MON_DATA_MOVE1 + args[1]),
                     args[1], GetMonData(mon, MON_DATA_PP1 + args[1]));
}

static void Cmd_Bag(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 pocket, i;

    DebugTools_Print(out, "argent %u\n", GetMoney(&gSaveBlock1Ptr->money));
    for (pocket = 0; pocket < POCKETS_COUNT; pocket++)
    {
        DebugTools_Print(out, "poche %u :", pocket + 1);
        for (i = 0; i < gBagPockets[pocket].capacity; i++)
        {
            const struct ItemSlot *slot = &gBagPockets[pocket].itemSlots[i];

            if (slot->itemId != ITEM_NONE)
                DebugTools_Print(out, " %d x%d", slot->itemId, gSaveBlock2Ptr->encryptionKey ^ slot->quantity);
        }
        DebugTools_Print(out, "\n");
    }
}

// --- Combat ---------------------------------------------------------------------------------------------------

static void Cmd_Battle(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    DebugTools_Print(out, "en combat %d, type %#x, combattants %d, principal @%lld\n", gMain.inBattle,
                     gBattleTypeFlags, gBattlersCount, DebugTools_Offset(gBattleMainFunc));
    if (!gMain.inBattle)
        return;
    for (i = 0; i < gBattlersCount && i < MAX_BATTLERS_COUNT; i++)
        DebugTools_Print(out, "combattant %u position %d espece %d PV %d/%d controleur @%lld\n", i,
                         gBattlerPositions[i], gBattleMons[i].species, gBattleMons[i].hp, gBattleMons[i].maxHP,
                         DebugTools_Offset(gBattlerControllerFuncs[i]));
}

// --- Graphismes -----------------------------------------------------------------------------------------------

static void Cmd_Sprites(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        const struct Sprite *sprite = &gSprites[i];

        if (!sprite->inUse)
            continue;
        DebugTools_Print(out, "sprite %u en %d,%d (+%d,%d) tile %d pal %d prio %d sous %d anim %d etape %d%s%s%s cb @%lld\n",
                         i, sprite->x, sprite->y, sprite->x2, sprite->y2, sprite->oam.tileNum, sprite->oam.paletteNum,
                         sprite->oam.priority, sprite->subpriority, sprite->animNum, sprite->animCmdIndex,
                         sprite->animEnded ? " finie" : "", sprite->animPaused ? " pause" : "",
                         sprite->invisible ? " invisible" : "", DebugTools_Offset(sprite->callback));
    }
}

static void Cmd_Palette(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 base = (args[0] ? 256 : 0) + (args[1] & 15) * 16, i;

    DebugTools_Print(out, "palette %s %d (non fondue / fondue / ecran)\n", args[0] ? "OBJ" : "BG", args[1] & 15);
    for (i = 0; i < 16; i++)
        DebugTools_Print(out, "%2u %04x %04x %04x\n", i, gPlttBufferUnfaded[base + i], gPlttBufferFaded[base + i],
                         ((u16 *)PLTT)[base + i]);
}

static void Cmd_Backgrounds(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u16 dispcnt = GetGpuReg(REG_OFFSET_DISPCNT);
    u32 bg;

    DebugTools_Print(out, "DISPCNT %04x BLDCNT %04x BLDALPHA %04x BLDY %04x WININ %04x WINOUT %04x\n", dispcnt,
                     GetGpuReg(REG_OFFSET_BLDCNT), GetGpuReg(REG_OFFSET_BLDALPHA), GetGpuReg(REG_OFFSET_BLDY),
                     GetGpuReg(REG_OFFSET_WININ), GetGpuReg(REG_OFFSET_WINOUT));
    for (bg = 0; bg < 4; bg++)
    {
        u16 cnt = GetGpuReg(REG_OFFSET_BG0CNT + 2 * bg);

        DebugTools_Print(out, "BG%u %s prio %d tiles %#x carte %#x taille %d decalage %d,%d\n", bg,
                         (dispcnt & (DISPCNT_BG0_ON << bg)) ? "visible" : "cache", cnt & 3, ((cnt >> 2) & 3) * 0x4000,
                         ((cnt >> 8) & 0x1F) * 0x800, cnt >> 14, GetGpuReg(REG_OFFSET_BG0HOFS + 4 * bg),
                         GetGpuReg(REG_OFFSET_BG0VOFS + 4 * bg));
    }
}

// Une rangée de la carte d'un BG en VRAM : tile:palette (h/v = retourné)
static void Cmd_BackgroundRow(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u16 cnt = GetGpuReg(REG_OFFSET_BG0CNT + 2 * (args[0] & 3));
    const u16 *map = (const u16 *)((u8 *)VRAM + ((cnt >> 8) & 0x1F) * 0x800);
    u32 x;

    for (x = 0; x < 32; x++)
    {
        u16 entry = map[(args[1] & 31) * 32 + x];

        DebugTools_Print(out, "%x:%x%s%s ", entry & 0x3FF, entry >> 12, (entry & 0x400) ? "h" : "",
                         (entry & 0x800) ? "v" : "");
    }
    DebugTools_Print(out, "\n");
}

// Un tile 4bpp en VRAM : 8 rangées d'indices de couleur
static void Cmd_Tile(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    const u8 *tile = (u8 *)VRAM + (args[0] & 3) * 0x4000 + (args[1] & 0x3FF) * 32;
    u32 y, x;

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
            DebugTools_Print(out, "%x", (tile[y * 4 + x / 2] >> ((x & 1) * 4)) & 0xF);
        DebugTools_Print(out, "\n");
    }
}

static void Cmd_Windows(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < WINDOWS_MAX; i++)
    {
        const struct WindowTemplate *window = &gWindows[i].window;

        if (window->bg == 0xFF)
            continue;
        DebugTools_Print(out, "fenetre %u BG%d en %d,%d taille %dx%d pal %d tiles %#x\n", i, window->bg,
                         window->tilemapLeft, window->tilemapTop, window->width, window->height, window->paletteNum,
                         window->baseBlock);
    }
}

// --- Texte ----------------------------------------------------------------------------------------------------

static void Cmd_TextPrinters(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < WINDOWS_MAX; i++)
    {
        const struct TextPrinter *printer = GetTextPrinter(i);

        if (!printer->active)
            continue;
        DebugTools_Print(out, "fenetre %u police %d couleurs %d/%d/%d en %d,%d etat %d vitesse %d texte @%lld\n", i,
                         printer->printerTemplate.fontId, printer->printerTemplate.fgColor,
                         printer->printerTemplate.bgColor, printer->printerTemplate.shadowColor,
                         printer->printerTemplate.currentX, printer->printerTemplate.currentY, printer->state,
                         printer->textSpeed, DebugTools_Offset(printer->printerTemplate.currentChar));
    }
}

// Les actions du menu DEBUG ; [N] : fait l'action N (celles sans écran : soins, objets, drapeaux de fin de jeu…)
static void Cmd_DebugAction(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    const u8 *name;
    char utf8[64];
    u32 i;

    if (argCount >= 1)
    {
        name = DebugMenu_GetActionName(args[0]);
        DebugTools_GameTextToUtf8(utf8, name != NULL ? name : (const u8 *)"\xFF", sizeof(utf8));
        if ((u32)args[0] < 256 && DebugMenu_ApplyAction(args[0]))
            DebugTools_Print(out, "fait : %d %s\n", args[0], utf8);
        else
            DebugTools_Print(out, "refuse : %d %s a besoin du menu\n", args[0], utf8);
        return;
    }
    for (i = 0; (name = DebugMenu_GetActionName(i)) != NULL; i++)
    {
        DebugTools_GameTextToUtf8(utf8, name, sizeof(utf8));
        DebugTools_Print(out, "%u %s\n", i, utf8);
    }
}

// Le menu Start : ses entrées (MENU_ACTION_* de start_menu.c) et le curseur, pour y aller sans compter
static void Cmd_StartMenu(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    const u8 *actions;
    u8 cursor, count, i;
    u8 text[64];
    char utf8[96];

    count = StartMenu_GetActions(&actions, &cursor);
    DebugTools_Print(out, "%u entrees, curseur %u\n", count, cursor);
    for (i = 0; i < count; i++)
    {
        const u8 *name = StartMenu_GetActionText(actions[i]);

        if (name != NULL)
        {
            StringExpandPlaceholders(text, name);
            DebugTools_GameTextToUtf8(utf8, text, sizeof(utf8));
        }
        else
        {
            strcpy(utf8, "?");
        }
        DebugTools_Print(out, "%u action %u %s\n", i, actions[i], utf8);
    }
}

// --- Son ------------------------------------------------------------------------------------------------------

static void Cmd_Sound(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    DebugTools_Print(out, "musique %d, carte %d\n", GetPlayerSong(&gMPlayInfo_BGM), GetCurrentMapMusic());
    DebugTools_Print(out, "effets %d %d %d\n", GetPlayerSong(&gMPlayInfo_SE1), GetPlayerSong(&gMPlayInfo_SE2),
                     GetPlayerSong(&gMPlayInfo_SE3));
}

// --- Système --------------------------------------------------------------------------------------------------

static void Cmd_System(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u16 r, g, b, gray, light;

    RtcCalcLocalTime();
    DayNight_GetTint(&r, &g, &b, &gray, &light);
    DebugTools_Print(out, "RNG %08x %08x\n", gRngValue, gRng2Value);
    DebugTools_Print(out, "heure du jeu : jour %d, %02d:%02d:%02d\n", gLocalTime.days, gLocalTime.hours,
                     gLocalTime.minutes, gLocalTime.seconds);
    DebugTools_Print(out, "jour/nuit : option %d, teinte %d %d %d, gris %d, fenetres %d, rendu %d\n",
                     gSaveBlock2Ptr->optionsDayNight, r, g, b, gray, light, gDayNightRender.active);
}

static void Cmd_Anomalies(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    DebugChecks_Print(out);
}

// Rapport de bug rejouable (src/platform/devtools.c) : l'archive tar du dossier des rapports
static void Cmd_Report(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
#ifdef PORTABLE
    char name[64];

    if (DevTools_WriteReport(name, sizeof(name)))
        DebugTools_Print(out, "Rapport enregistre :\n%s\ndans %s\n\nEnvoie ce fichier : il contient la sauvegarde du "
                         "lancement, toutes les touches, l'etat du jeu et la capture. test/headless/replay.py le "
                         "rejoue.\n", name, DevTools_GetReportDir());
    else
        DebugTools_Print(out, "Rapport impossible a ecrire dans %s\n", DevTools_GetReportDir());
#endif
}

static void Cmd_Help(const s32 *args, u32 argCount, struct DebugToolsOutput *out)
{
    u32 i;

    for (i = 0; i < gDebugToolsCount; i++)
        DebugTools_Print(out, "%s (%d arg.) : %s\n", gDebugTools[i].id, gDebugTools[i].argCount, gDebugTools[i].help);
}

// --- Registre -------------------------------------------------------------------------------------------------

static const u8 sName_GameState[] = _("État du moteur");
static const u8 sName_Options[] = _("Options");
static const u8 sName_NoClip[] = _("Traverser les murs");
static const u8 sName_Encounters[] = _("Rencontres sauvages");
static const u8 sName_Safari[] = _("Parc Safari");
static const u8 sName_Roamers[] = _("Pokémon errants");
static const u8 sName_GameStatistic[] = _("Statistique de jeu");
static const u8 sName_StartMenu[] = _("Menu Start");
static const u8 sName_DebugAction[] = _("Actions du menu DEBUG");
static const u8 sName_MapInfo[] = _("Carte");
static const u8 sName_MapObjects[] = _("Objets de la carte");
static const u8 sName_MapGrid[] = _("Grille de la carte");
static const u8 sName_ScriptContext[] = _("Scripts en cours");
static const u8 sName_RunScript[] = _("Lancer un script");
static const u8 sName_Flag[] = _("Flag");
static const u8 sName_Var[] = _("Variable");
static const u8 sName_Names[] = _("Drapeaux et variables");
static const u8 sName_Story[] = _("Histoires finies");
static const u8 sName_Party[] = _("Équipe");
static const u8 sName_Bag[] = _("Sac et argent");
static const u8 sName_SetMove[] = _("Donner une capacité");
static const u8 sName_Battle[] = _("Combat");
static const u8 sName_Sprites[] = _("Sprites");
static const u8 sName_Palette[] = _("Palette");
static const u8 sName_Backgrounds[] = _("BG et écran");
static const u8 sName_BackgroundRow[] = _("Rangée de BG");
static const u8 sName_Tile[] = _("Tile");
static const u8 sName_Windows[] = _("Fenêtres");
static const u8 sName_TextPrinters[] = _("Textes en cours");
static const u8 sName_Sound[] = _("Musique et effets");
static const u8 sName_System[] = _("RNG, heure, jour/nuit");
static const u8 sName_Anomalies[] = _("Anomalies vues");
static const u8 sName_Report[] = _("Rapport de bug");
static const u8 sName_Help[] = _("Liste des commandes");

const struct DebugTool gDebugTools[] =
{
    {"jeu.etat", DEBUG_TOOLS_GAME, sName_GameState, "callbacks, fondu, verrous, taches actives", 0, Cmd_GameState},
    {"jeu.options", DEBUG_TOOLS_GAME, sName_Options, "toutes les options ; [N V] met l'option N a V", 0, Cmd_Options},
    {"jeu.murs", DEBUG_TOOLS_GAME, sName_NoClip, "[1|0] : traverser les murs (comme le menu DEBUG)", 0, Cmd_NoClip},
    {"jeu.rencontres", DEBUG_TOOLS_GAME, sName_Encounters, "[1|0] : Pokemon sauvages oui / non", 0, Cmd_Encounters},
    {"jeu.safari", DEBUG_TOOLS_GAME, sName_Safari, "[PAS [BALLS]] : pas restants et SAFARI BALLS du Parc Safari", 0, Cmd_Safari},
    {"jeu.errants", DEBUG_TOOLS_GAME, sName_Roamers, "[1|2] : vagabonds de la region ; 1 les lache, 2 les met sur cette carte", 0, Cmd_Roamers},
    {"jeu.stat", DEBUG_TOOLS_GAME, sName_GameStatistic, "N [V] : statistique de jeu GAME_STAT_* (Pantheon, oeufs...), mise a V", 1, Cmd_GameStatistic},
    {"jeu.menustart", DEBUG_TOOLS_GAME, sName_StartMenu, "entrees du menu Start et curseur", 0, Cmd_StartMenu},
    {"jeu.debug", DEBUG_TOOLS_GAME, sName_DebugAction, "actions du menu DEBUG ; [N] fait l'action N", 0, Cmd_DebugAction},
    {"carte.info", DEBUG_TOOLS_MAP, sName_MapInfo, "carte, region, joueur, connexions", 0, Cmd_MapInfo},
    {"carte.objets", DEBUG_TOOLS_MAP, sName_MapObjects, "objets actifs de la carte", 0, Cmd_MapObjects},
    {"carte.grille", DEBUG_TOOLS_MAP, sName_MapGrid, "la carte en jeu : # bloque, g herbe, ~ eau, <>^v rebord", 0, Cmd_MapGrid},
    {"scripts.contexte", DEBUG_TOOLS_SCRIPT, sName_ScriptContext, "contextes de script global et immediat", 0, Cmd_ScriptContext},
    {"scripts.lancer", DEBUG_TOOLS_SCRIPT, sName_RunScript, "@ADRESSE : lance ce script (game.script(NOM) dans le banc)", 1, Cmd_RunScript},
    {"scripts.flag", DEBUG_TOOLS_SCRIPT, sName_Flag, "FLAG [VALEUR] : lit ou met un flag", 1, Cmd_Flag},
    {"scripts.var", DEBUG_TOOLS_SCRIPT, sName_Var, "VAR [VALEUR] : lit ou met une variable", 1, Cmd_Var},
    {"scripts.histoire", DEBUG_TOOLS_SCRIPT, sName_Story, "[N] : histoire finie (0 Hoenn, 1 Kanto, 2 les deux), deduite des scripts", 0, Cmd_Story, Select_Story},
    {"scripts.drapeaux", DEBUG_TOOLS_SCRIPT, sName_Names, "[CAT] : drapeaux, dresseurs, variables par categorie ; menu : A bascule, L/R -/+", 0, Cmd_Names, Select_Names},
    {"joueur.equipe", DEBUG_TOOLS_PLAYER, sName_Party, "equipe : espece, PV, dresseur d'origine, lieu de rencontre", 0, Cmd_Party},
    {"joueur.sac", DEBUG_TOOLS_PLAYER, sName_Bag, "argent et poches du sac", 0, Cmd_Bag},
    {"joueur.capacite", DEBUG_TOOLS_PLAYER, sName_SetMove, "N PLACE CAPACITE : donne la capacite (et ses PP)", 3, Cmd_SetMove},
    {"combat.etat", DEBUG_TOOLS_BATTLE, sName_Battle, "type, combattants, controleurs", 0, Cmd_Battle},
    {"gfx.sprites", DEBUG_TOOLS_GFX, sName_Sprites, "sprites utilises : position, tile, palette, animation", 0, Cmd_Sprites},
    {"gfx.palette", DEBUG_TOOLS_GFX, sName_Palette, "TYPE BANQUE (0 BG, 1 OBJ) : couleurs non fondues, fondues, a l'ecran", 2, Cmd_Palette},
    {"gfx.bg", DEBUG_TOOLS_GFX, sName_Backgrounds, "registres d'affichage et des 4 BG", 0, Cmd_Backgrounds},
    {"gfx.bgligne", DEBUG_TOOLS_GFX, sName_BackgroundRow, "BG RANGEE : 32 cases tile:palette de la carte en VRAM", 2, Cmd_BackgroundRow},
    {"gfx.tile", DEBUG_TOOLS_GFX, sName_Tile, "BLOC TILE : indices de couleur d'un tile 4bpp", 2, Cmd_Tile},
    {"gfx.fenetres", DEBUG_TOOLS_GFX, sName_Windows, "fenetres ouvertes", 0, Cmd_Windows},
    {"texte.imprimantes", DEBUG_TOOLS_TEXT, sName_TextPrinters, "textes en train de s'ecrire", 0, Cmd_TextPrinters},
    {"son.etat", DEBUG_TOOLS_SOUND, sName_Sound, "musique et effets en cours", 0, Cmd_Sound},
    {"sys.etat", DEBUG_TOOLS_SYSTEM, sName_System, "RNG, heure du jeu, teinte jour/nuit", 0, Cmd_System},
    {"sys.anomalies", DEBUG_TOOLS_SYSTEM, sName_Anomalies, "anomalies vues par les detecteurs (src/debug_checks.c)", 0, Cmd_Anomalies},
    {"sys.rapport", DEBUG_TOOLS_SYSTEM, sName_Report, "rapport de bug rejouable (sauvegarde, touches, etat, capture)", 0, Cmd_Report},
    {"aide", DEBUG_TOOLS_SYSTEM, sName_Help, "liste des commandes", 0, Cmd_Help},
};

const u32 gDebugToolsCount = ARRAY_COUNT(gDebugTools);

static const u8 sCategory_Game[] = _("Jeu");
static const u8 sCategory_Map[] = _("Carte");
static const u8 sCategory_Script[] = _("Scripts");
static const u8 sCategory_Player[] = _("Joueur");
static const u8 sCategory_Battle[] = _("Combat");
static const u8 sCategory_Gfx[] = _("Graphismes");
static const u8 sCategory_Text[] = _("Texte");
static const u8 sCategory_Sound[] = _("Son");
static const u8 sCategory_System[] = _("Système");

const u8 *const gDebugToolsCategoryNames[DEBUG_TOOLS_CATEGORY_COUNT] =
{
    [DEBUG_TOOLS_GAME]   = sCategory_Game,
    [DEBUG_TOOLS_MAP]    = sCategory_Map,
    [DEBUG_TOOLS_SCRIPT] = sCategory_Script,
    [DEBUG_TOOLS_PLAYER] = sCategory_Player,
    [DEBUG_TOOLS_BATTLE] = sCategory_Battle,
    [DEBUG_TOOLS_GFX]    = sCategory_Gfx,
    [DEBUG_TOOLS_TEXT]   = sCategory_Text,
    [DEBUG_TOOLS_SOUND]  = sCategory_Sound,
    [DEBUG_TOOLS_SYSTEM] = sCategory_System,
};

const struct DebugTool *DebugTools_Find(const char *id)
{
    u32 i;

    for (i = 0; i < gDebugToolsCount; i++)
    {
        if (strcmp(gDebugTools[i].id, id) == 0)
            return &gDebugTools[i];
    }
    return NULL;
}

bool8 DebugTools_RunLine(const char *line, struct DebugToolsOutput *out)
{
    char id[32] = "";
    char words[DEBUG_TOOLS_MAX_ARGS][64];
    s32 args[DEBUG_TOOLS_MAX_ARGS] = {0};
    int count = sscanf(line, "%31s %63s %63s %63s %63s", id, words[0], words[1], words[2], words[3]) - 1;
    const struct DebugTool *tool;
    int i;

    out->length = 0;
    out->text[0] = '\0';
    tool = DebugTools_Find(id);
    if (tool == NULL)
    {
        DebugTools_Print(out, "commande inconnue : %s (aide = la liste)", id);
        return FALSE;
    }
    if (count < tool->argCount)
    {
        DebugTools_Print(out, "%s : %d argument(s) attendu(s) : %s", id, tool->argCount, tool->help);
        return FALSE;
    }
    // Un argument est un nombre, ou le nom d'un drapeau, d'une variable ou d'un dresseur (FLAG_SYS_GAME_CLEAR)
    for (i = 0; i < count && i < DEBUG_TOOLS_MAX_ARGS; i++)
    {
        char *end;

        args[i] = strtol(words[i], &end, 0);
        if (*end != '\0' && !GetNameValue(words[i], &args[i]))
        {
            DebugTools_Print(out, "%s : ni un nombre ni un nom connu (FLAG_, VAR_, TRAINER_)", words[i]);
            return FALSE;
        }
    }
    tool->run(args, count < 0 ? 0 : count, out);
    return TRUE;
}

#endif // KANTO_DEBUG_START
