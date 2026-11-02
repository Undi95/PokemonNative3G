// PokemonNative3G : détecteurs d'anomalies (builds KANTO_DEBUG=1), voir include/debug_checks.h et docs/DEVTOOLS.md.
// Les détecteurs placés dans le code du jeu (texte coupé dans text.c, cadre de boîte dans menu.c…) appellent
// DebugChecks_Report ; ceux qui regardent l'état à chaque image sont ici (DebugChecks_OnFrame).
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "debug_tools.h"
#include "debug_checks.h"

#ifdef KANTO_DEBUG_START
#include "data.h"
#include "gpu_regs.h"
#include "main.h"
#include "sprite.h"
#include "window.h"
#ifdef PORTABLE
#include "platform/test_state.h"
#endif

#define REPORTS_KEPT 64
#define SEEN_SLOTS 2048

struct Anomaly
{
    u32 frame;
    char kind[24];
    char text[136];
};

static struct Anomaly sAnomalies[REPORTS_KEPT];
static u32 sAnomalyCount;
static u32 sSeen[SEEN_SLOTS];

static u32 HashText(u32 hash, const char *text)
{
    for (; *text != '\0'; text++)
        hash = (hash ^ (u8)*text) * 16777619u;
    return hash;
}

// Une seule fois par cause (même détecteur, même texte)
static bool32 IsNewReport(const char *kind, const char *text)
{
    u32 hash = HashText(HashText(2166136261u, kind), text) | 1;
    u32 slot = hash % SEEN_SLOTS, i;

    for (i = 0; i < SEEN_SLOTS; i++, slot = (slot + 1) % SEEN_SLOTS)
    {
        if (sSeen[slot] == hash)
            return FALSE;
        if (sSeen[slot] == 0)
        {
            sSeen[slot] = hash;
            return TRUE;
        }
    }
    return FALSE;
}

void DebugChecks_Report(const char *kind, s32 windowId, const char *format, ...)
{
    struct Anomaly *anomaly;
    char text[sizeof(anomaly->text)];
    va_list args;

    va_start(args, format);
    vsnprintf(text, sizeof(text), format, args);
    va_end(args);
    if (!IsNewReport(kind, text))
        return;
    anomaly = &sAnomalies[sAnomalyCount++ % REPORTS_KEPT];
    anomaly->frame = gMain.vblankCounter1;
    snprintf(anomaly->kind, sizeof(anomaly->kind), "%s", kind);
    snprintf(anomaly->text, sizeof(anomaly->text), "%s", text);
#ifdef PORTABLE
    TestState_OnAnomaly(kind, windowId, text);
#endif
    fprintf(stderr, "ANOMALIE %s : %s\n", kind, text);
}

void DebugChecks_Print(struct DebugToolsOutput *out)
{
    u32 first = sAnomalyCount > REPORTS_KEPT ? sAnomalyCount - REPORTS_KEPT : 0, i;

    DebugTools_Print(out, "%u anomalie(s) depuis le lancement\n", sAnomalyCount);
    for (i = first; i < sAnomalyCount; i++)
    {
        const struct Anomaly *anomaly = &sAnomalies[i % REPORTS_KEPT];

        DebugTools_Print(out, "image %u, %s : %s\n", anomaly->frame, anomaly->kind, anomaly->text);
    }
}

// --- Sprites de Pokémon figés ---------------------------------------------------------------------------------
// Les images d'un Pokémon : 0 = repos, 1 = l'autre image de son animation. Un Pokémon qui garde l'image 1 n'a pas
// fini son animation (table d'animations d'une image fixe à la place de celle de l'espèce, animation coupée).

#define MON_PIC_STILL_FRAMES 120

static const union AnimCmd *const *sCheckedAnims[MAX_SPRITES];
static bool8 sIsMonPic[MAX_SPRITES];
static u16 sStillFrames[MAX_SPRITES];

static bool32 IsMonPicAnims(const union AnimCmd *const *anims)
{
    u32 i;

    if (anims == gAnims_MonPic)
        return TRUE;
    for (i = 0; i < NUM_SPECIES; i++)
    {
        if (gMonFrontAnimsPtrTable[i] == anims)
            return TRUE;
    }
    return FALSE;
}

// L'image affichée : la dernière commande d'image jouée de l'animation en cours
static s32 GetShownImage(const struct Sprite *sprite)
{
    const union AnimCmd *anim = sprite->anims[sprite->animNum];
    s32 image = -1;
    u32 i;

    for (i = 0; i <= sprite->animCmdIndex; i++)
    {
        if (anim[i].type == -1)
            break;
        if (anim[i].type >= 0)
            image = anim[i].frame.imageValue;
    }
    return image;
}

static void CheckMonPics(void)
{
    u32 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        const struct Sprite *sprite = &gSprites[i];
        s32 image;

        if (!sprite->inUse || sprite->invisible || sprite->anims == NULL)
        {
            sStillFrames[i] = 0;
            continue;
        }
        if (sprite->anims != sCheckedAnims[i])
        {
            sCheckedAnims[i] = sprite->anims;
            sIsMonPic[i] = IsMonPicAnims(sprite->anims);
            sStillFrames[i] = 0;
        }
        if (!sIsMonPic[i])
            continue;
        image = GetShownImage(sprite);
        if (image <= 0)
        {
            sStillFrames[i] = 0;
            continue;
        }
        if (++sStillFrames[i] == MON_PIC_STILL_FRAMES)
            DebugChecks_Report("Pokémon figé", -1, "sprite %u garde l'image %d (animation %d, cb @%lld, ecran @%lld)", i,
                               image, sprite->animNum, DebugTools_Offset(sprite->callback),
                               DebugTools_Offset(gMain.callback2));
    }
}

// --- Cadres de boîte de dialogue -------------------------------------------------------------------------------
// Les tiles de la boîte (LoadMessageBoxGfx : celles d'Émeraude ou de RF selon l'option DIALOGUE) sont notées à leur
// chargement ; un cadre dessiné ensuite avec la disposition de l'autre style (bug de l'intro avec DIALOGUE = KANTO)
// utilise une tile que ce style ne place jamais. Les tiles remplacées depuis (autre écran) ne sont plus regardées.

#define MESSAGE_BOX_TILES 14
#define FRAME_CHECK_INTERVAL 8

struct MessageBoxGfx
{
    u32 frame;
    u32 checksum;
    u16 base;
    u8 bg;
    bool8 kanto;
    bool8 active;
};

static struct MessageBoxGfx sMessageBoxGfx[8];

// Tiles placées par chaque disposition (menu.c : WindowFunc_DrawDialogueFrame, DrawKantoDialogueFrame)
static const u16 sEmeraldFrameTiles = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 9) | (1 << 10);
static const u16 sKantoFrameTiles = 0x3FFF & ~(1 << 7);

static u32 MessageBoxChecksum(const struct MessageBoxGfx *gfx)
{
    u16 cnt = GetGpuReg(REG_OFFSET_BG0CNT + 2 * gfx->bg);
    const u8 *tiles = (const u8 *)VRAM + ((cnt >> 2) & 3) * 0x4000 + gfx->base * 32;
    u32 sum = 0, i;

    if (((cnt >> 2) & 3) * 0x4000 + (gfx->base + MESSAGE_BOX_TILES) * 32 > 0x10000)
        return 0;
    for (i = 0; i < MESSAGE_BOX_TILES * 32; i++)
        sum = sum * 31 + tiles[i];
    return sum;
}

void DebugChecks_OnMessageBoxGfx(u8 bg, u16 base, bool8 kanto)
{
    u32 i, slot = ARRAY_COUNT(sMessageBoxGfx) - 1;

    for (i = 0; i < ARRAY_COUNT(sMessageBoxGfx); i++)
    {
        if (!sMessageBoxGfx[i].active || (sMessageBoxGfx[i].bg == bg && sMessageBoxGfx[i].base == base))
        {
            slot = i;
            break;
        }
    }
    sMessageBoxGfx[slot].bg = bg;
    sMessageBoxGfx[slot].base = base;
    sMessageBoxGfx[slot].kanto = kanto;
    sMessageBoxGfx[slot].frame = gMain.vblankCounter1;
    sMessageBoxGfx[slot].checksum = 0;
    sMessageBoxGfx[slot].active = TRUE;
}

static void CheckMessageBoxFrames(void)
{
    u32 i, x, y;

    if (gMain.vblankCounter1 % FRAME_CHECK_INTERVAL != 0)
        return;
    for (i = 0; i < ARRAY_COUNT(sMessageBoxGfx); i++)
    {
        struct MessageBoxGfx *gfx = &sMessageBoxGfx[i];
        u16 cnt, allowed;
        const u16 *map;

        if (!gfx->active)
            continue;
        // Les tiles arrivent en VRAM à la fin de l'image de leur chargement
        if (gfx->checksum == 0)
        {
            if (gMain.vblankCounter1 > gfx->frame + 1)
                gfx->checksum = MessageBoxChecksum(gfx) | 1;
            continue;
        }
        if ((MessageBoxChecksum(gfx) | 1) != gfx->checksum)
        {
            gfx->active = FALSE;
            continue;
        }
        if (!(GetGpuReg(REG_OFFSET_DISPCNT) & (DISPCNT_BG0_ON << gfx->bg)))
            continue;
        cnt = GetGpuReg(REG_OFFSET_BG0CNT + 2 * gfx->bg);
        map = (const u16 *)((const u8 *)VRAM + ((cnt >> 8) & 0x1F) * 0x800);
        allowed = gfx->kanto ? sKantoFrameTiles : sEmeraldFrameTiles;
        for (y = 0; y < 32; y++)
        {
            for (x = 0; x < 32; x++)
            {
                u32 tile = map[y * 32 + x] & 0x3FF;

                if (tile >= gfx->base && tile < gfx->base + MESSAGE_BOX_TILES && !(allowed & (1 << (tile - gfx->base))))
                {
                    DebugChecks_Report("cadre de boîte", -1, "BG%d case %u,%u : tile %u du style %s jamais placee par lui (cadre de l'autre style ?), ecran @%lld",
                                       gfx->bg, x, y, tile - gfx->base, gfx->kanto ? "Kanto" : "Emeraude",
                                       DebugTools_Offset(gMain.callback2));
                    return;
                }
            }
        }
    }
}

void DebugChecks_OnFrame(void)
{
    CheckMonPics();
    CheckMessageBoxFrames();
}

// --- Texte superposé ----------------------------------------------------------------------------------------------
// Un tableau par fenêtre (malloc du PC : rien dans le tas du jeu), à la taille de la fenêtre

static u32 *sTextOwners[WINDOWS_MAX];
static u32 sTextOwnerSizes[WINDOWS_MAX];

static u32 GetWindowPixelCount(u8 windowId)
{
    return gWindows[windowId].window.width * gWindows[windowId].window.height * 64;
}

u32 *DebugChecks_GetTextOwners(u8 windowId)
{
    u32 size;

    if (windowId >= WINDOWS_MAX || gWindows[windowId].tileData == NULL)
        return NULL;
    size = GetWindowPixelCount(windowId);
    if (size == 0)
        return NULL;
    if (sTextOwnerSizes[windowId] != size)
    {
        free(sTextOwners[windowId]);
        sTextOwners[windowId] = malloc(size * sizeof(u32));
        sTextOwnerSizes[windowId] = sTextOwners[windowId] != NULL ? size : 0;
        if (sTextOwners[windowId] != NULL)
            memset(sTextOwners[windowId], 0xFF, size * sizeof(u32));
    }
    return sTextOwners[windowId];
}

void DebugChecks_ClearTextOwners(u8 windowId, s32 x, s32 y, s32 width, s32 height)
{
    s32 windowWidth, windowHeight, row;

    if (windowId >= WINDOWS_MAX || sTextOwners[windowId] == NULL)
        return;
    if (sTextOwnerSizes[windowId] != GetWindowPixelCount(windowId))
    {
        free(sTextOwners[windowId]);
        sTextOwners[windowId] = NULL;
        sTextOwnerSizes[windowId] = 0;
        return;
    }
    if (width < 0)
    {
        memset(sTextOwners[windowId], 0xFF, sTextOwnerSizes[windowId] * sizeof(u32));
        return;
    }
    windowWidth = gWindows[windowId].window.width * 8;
    windowHeight = gWindows[windowId].window.height * 8;
    if (x < 0)
        width += x, x = 0;
    if (y < 0)
        height += y, y = 0;
    if (x + width > windowWidth)
        width = windowWidth - x;
    for (row = y; row < y + height && row < windowHeight; row++)
    {
        if (width > 0)
            memset(&sTextOwners[windowId][row * windowWidth + x], 0xFF, width * sizeof(u32));
    }
}

#endif // KANTO_DEBUG_START
