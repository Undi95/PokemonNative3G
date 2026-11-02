#include "global.h"
#include "day_night.h"
#include "debug_checks.h"
#include "debug_tools.h"
#include "fieldmap.h"
#include "main.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "tilesets.h"
#include "constants/rgb.h"

// PokemonNative3G : cycle jour/nuit, purement visuel. Les couleurs envoyées au matériel (PLTT) sont teintées selon
// l'heure, après les fondus et la météo (gPlttBufferFaded n'est pas touché) : seulement sur le terrain, dehors, et
// seulement les palettes de la carte (BG 0-12) et des objets ; boîtes de texte et menus (BG 13-15) restent intacts.
// Les vitres des tilesets (src/data/day_night_lights.h) s'allument en jaune le soir et la nuit, dégradés compris.

struct DayNightKey
{
    u16 minute; // minute de la journée
    u16 r, g, b; // multiplicateurs sur 256
    u16 gray;    // désaturation (vision de nuit : les fleurs ne brillent pas), sur 256
    u16 light;   // fenêtres allumées, sur 256
};

static const struct DayNightKey sDayNightKeys[] =
{
    {  0 * 60, 120, 130, 190, 140, 256 }, // nuit
    {  5 * 60, 120, 130, 190, 140, 256 },
    {  7 * 60, 245, 215, 200,   0,   0 }, // matin
    {  9 * 60, 256, 256, 256,   0,   0 }, // jour
    { 17 * 60, 256, 256, 256,   0,   0 },
    { 19 * 60, 256, 180, 130,  40, 128 }, // coucher de soleil
    { 21 * 60, 120, 130, 190, 140, 256 }, // nuit
    { 24 * 60, 120, 130, 190, 140, 256 },
};

struct DayNightLights
{
    const struct Tileset *tileset;
    u16 colors[NUM_PALS_TOTAL]; // couleurs de vitre, par palette
    const u8 (*tileLights)[8];  // pixels de vitre, par tile du tileset
};

#include "data/day_night_lights.h"

static u16 sTintR = 256, sTintG = 256, sTintB = 256, sGray = 0, sLight = 0;
static u32 sLastUpdate = 0xFFFFFFFF;
static const struct MapLayout *sLightsLayout;
struct DayNightRender gDayNightRender;
static bool8 sMarkLights; // banc de test : vitres en magenta
// Animation des portes (field_door.c) : ses images sont copiées dans les 16 derniers tiles, à la place de ceux de
// la carte ; pendant ce temps leurs pixels allumés viennent de DayNight_DoorAnimMetatile (la vitre qui glisse reste
// allumée, l'ouverture sombre et le logo au-dessus non)
#define DOOR_ANIM_TILES (NUM_TILES_TOTAL - 16)
static bool8 sDoorAnimTiles;
static u8 sMapDoorTiles[16][8];
static u8 sDoorAnimMasks[16][8];

bool8 IsDayNightHourNight(u8 hours)
{
    return hours >= DAY_NIGHT_NIGHT_BEGIN || hours < DAY_NIGHT_NIGHT_END;
}

// PokemonNative3G : outils de debug (debug_tools.c) : teinte en cours (256 = couleur d'origine), gris, lumière des fenêtres
void DayNight_GetTint(u16 *r, u16 *g, u16 *b, u16 *gray, u16 *light)
{
    *r = sTintR;
    *g = sTintG;
    *b = sTintB;
    *gray = sGray;
    *light = sLight;
}

void DayNight_SetMarkLights(bool8 mark)
{
    sMarkLights = mark;
}

// Indice de couleur du pixel (x, y) d'un tile de la carte, en mémoire vidéo (BG, char base 0)
static u32 TilePixel(u32 tile, u32 x, u32 y)
{
    const u8 *p = (const u8 *)VRAM + tile * TILE_SIZE_4BPP + y * 4 + x / 2;

    return (x & 1) ? *p >> 4 : *p & 0xF;
}

// Pixel du métatile (couche du haut s'il n'est pas transparent, sinon celle du bas) à la place (px, py) du quart q :
// renvoie son indice de couleur, et s'il est allumé
static u32 MetatilePixel(const u16 *entries, u32 q, u32 px, u32 py, bool32 *lit)
{
    u32 layer, color = 0;

    *lit = FALSE;
    for (layer = 0; layer < 2; layer++)
    {
        u16 entry = entries[q + 4 * (1 - layer)];
        u32 tile = entry & 0x3FF, sx = (entry & 0x400) ? 7 - px : px, sy = (entry & 0x800) ? 7 - py : py;

        color = TilePixel(tile, sx, sy);
        if (color != 0)
        {
            // Les tiles réservés aux portes peuvent servir à la carte (Dôme de Combat) : leurs pixels allumés à elle
            *lit = (((tile < DOOR_ANIM_TILES ? gDayNightRender.tiles[tile] : sMapDoorTiles[tile - DOOR_ANIM_TILES])[sy] >> sx) & 1);
            break;
        }
    }
    return color;
}

// Une image de porte est dessinée à (x, y) avec les tiles tileNum à tileNum + 3 (couche du bas du métatile). Ses
// pixels aux couleurs allumées du métatile fermé forment des zones d'un seul tenant et d'une seule couleur. Une zone
// que l'animation laisse telle quelle reste comme dans le métatile fermé (un emblème allumé en partie) ; sinon elle
// s'allume si elle ne passe par aucune place où le métatile fermé a cette couleur éteinte (le sol qui apparaît dans
// l'ouverture, le cadre, le logo) et qu'elle recouvre une place où il l'a allumée ou que cette couleur y est surtout
// allumée (la vitre, qu'elle glisse ou pivote ; pas une poignée)
void DayNight_DoorAnimMetatile(u32 tileNum, s32 x, s32 y)
{
    const struct MapLayout *layout = gMapHeader.mapLayout;
    u32 id = MapGridGetMetatileIdAt(x, y), p, i, n, litColors = 0;
    const u16 *entries;
    u8 closed[256], unlit[256], anim[256], zone[256], seen[256];
    s16 balance[16] = {0}; // par couleur : pixels allumés moins éteints du métatile fermé
    bool32 lit;

    if (id < NUM_METATILES_IN_PRIMARY)
        entries = layout->primaryTileset->metatiles + id * NUM_TILES_PER_METATILE;
    else
        entries = layout->secondaryTileset->metatiles + (id - NUM_METATILES_IN_PRIMARY) * NUM_TILES_PER_METATILE;
    // Pixels (x, y) du métatile 16x16 : p = y * 16 + x, quart (y / 8) * 2 + x / 8
    for (p = 0; p < 256; p++)
    {
        u32 q = (p / 128) * 2 + (p % 16) / 8;

        closed[p] = MetatilePixel(entries, q, p % 8, (p / 16) % 8, &lit);
        unlit[p] = !lit;
        anim[p] = TilePixel(tileNum + q, p % 8, (p / 16) % 8);
        if (lit)
            litColors |= 1 << closed[p];
        balance[closed[p]] += lit ? 1 : -1;
        seen[p] = FALSE;
    }
    // Les tiles réservés que l'animation ne dessine pas gardent ceux de la carte
    if (!sDoorAnimTiles)
        memcpy(sDoorAnimMasks, sMapDoorTiles, sizeof(sDoorAnimMasks));
    memset(sDoorAnimMasks[tileNum - DOOR_ANIM_TILES], 0, 4 * sizeof(sDoorAnimMasks[0]));
    for (p = 0; p < 256; p++)
    {
        bool32 dark = FALSE, moved = FALSE, glass = FALSE;

        if (seen[p] || !((litColors >> anim[p]) & 1))
            continue;
        // Remplissage : zone[0..n) reçoit la zone, parcourue au fur et à mesure
        seen[p] = TRUE;
        zone[0] = p;
        for (i = 0, n = 1; i < n; i++)
        {
            u32 c = zone[i], next[4], k;

            next[0] = c % 16 != 0 ? c - 1 : c;
            next[1] = c % 16 != 15 ? c + 1 : c;
            next[2] = c >= 16 ? c - 16 : c;
            next[3] = c < 240 ? c + 16 : c;
            if (closed[c] != anim[c])
                moved = TRUE;
            else if (unlit[c])
                dark = TRUE;
            else
                glass = TRUE;
            for (k = 0; k < 4; k++)
            {
                if (!seen[next[k]] && anim[next[k]] == anim[c])
                {
                    seen[next[k]] = TRUE;
                    zone[n++] = next[k];
                }
            }
        }
        if (moved && (dark || (!glass && balance[anim[p]] < 0)))
            continue;
        for (i = 0; i < n; i++)
        {
            u32 c = zone[i];

            if (!moved && unlit[c])
                continue;
            sDoorAnimMasks[tileNum + (c / 128) * 2 + (c % 16) / 8 - DOOR_ANIM_TILES][(c / 16) % 8] |= 1 << (c % 8);
        }
    }
    sDoorAnimTiles = TRUE;
    // Tout de suite : les images de la porte sont copiées en VRAM sans attendre la VBlank
    memcpy(gDayNightRender.tiles[DOOR_ANIM_TILES], sDoorAnimMasks, sizeof(sDoorAnimMasks));
}

void DayNight_DoorClosed(void)
{
    sDoorAnimTiles = FALSE;
}

static u16 Interpolate(u16 a, u16 b, u32 t, u32 span)
{
    return a + ((s32)b - a) * (s32)t / (s32)span;
}

static void UpdateTint(void)
{
    u32 i, minute, span, t;

    RtcCalcLocalTime();
    minute = gLocalTime.hours * 60 + gLocalTime.minutes;
    for (i = 1; i < ARRAY_COUNT(sDayNightKeys) - 1 && minute >= sDayNightKeys[i].minute; i++)
        ;
    span = sDayNightKeys[i].minute - sDayNightKeys[i - 1].minute;
    t = minute - sDayNightKeys[i - 1].minute;
    sTintR = Interpolate(sDayNightKeys[i - 1].r, sDayNightKeys[i].r, t, span);
    sTintG = Interpolate(sDayNightKeys[i - 1].g, sDayNightKeys[i].g, t, span);
    sTintB = Interpolate(sDayNightKeys[i - 1].b, sDayNightKeys[i].b, t, span);
    sGray = Interpolate(sDayNightKeys[i - 1].gray, sDayNightKeys[i].gray, t, span);
    sLight = Interpolate(sDayNightKeys[i - 1].light, sDayNightKeys[i].light, t, span);
}

// Vitres de la carte : primaire (palettes 0-5) et secondaire (6-12)
static void UpdateLightMasks(void)
{
    const struct MapLayout *layout = gMapHeader.mapLayout;
    u32 i, j;

    if (layout == sLightsLayout)
        return;
    sLightsLayout = layout;
    memset(gDayNightRender.masks, 0, sizeof(gDayNightRender.masks));
    memset(gDayNightRender.tiles, 0, sizeof(gDayNightRender.tiles));
    for (i = 0; i < ARRAY_COUNT(sDayNightLights); i++)
    {
        const struct DayNightLights *lights = &sDayNightLights[i];
        u32 base;

        if (lights->tileset == layout->primaryTileset)
            base = 0;
        else if (lights->tileset == layout->secondaryTileset)
            base = NUM_TILES_IN_PRIMARY;
        else
            continue;
        for (j = 0; j < NUM_PALS_TOTAL; j++)
            gDayNightRender.masks[j] |= lights->colors[j];
        memcpy(gDayNightRender.tiles[base], lights->tileLights, NUM_TILES_IN_PRIMARY * sizeof(gDayNightRender.tiles[0]));
    }
    memcpy(sMapDoorTiles, gDayNightRender.tiles[DOOR_ANIM_TILES], sizeof(sMapDoorTiles));
    sDoorAnimTiles = FALSE;
}

static u32 Desaturate(u32 x, u32 l)
{
    return (x * (256 - sGray) + l * sGray) >> 8;
}

static u32 TintColor(u32 c)
{
    u32 r = c & 0x1F, g = (c >> 5) & 0x1F, b = (c >> 10) & 0x1F;
    u32 l = (r * 77 + g * 150 + b * 29) >> 8;

    r = (Desaturate(r, l) * sTintR) >> 8;
    g = (Desaturate(g, l) * sTintG) >> 8;
    b = (Desaturate(b, l) * sTintB) >> 8;

    return RGB2(min(r, 31), min(g, 31), min(b, 31));
}

// Vitre allumée : jaune chaud, aussi clair que la couleur d'origine (fenêtres bleu nuit éclaircies, jusqu'au
// double : un écran noir pendant un fondu reste noir), mélangé à la couleur teintée selon sLight
static u32 LightColor(u32 c)
{
    u32 tinted = TintColor(c);
    u32 l = ((c & 0x1F) + ((c >> 5) & 0x1F) + ((c >> 10) & 0x1F)) / 3;
    u32 lit[3], dark[3], k, out = 0;

    if (sMarkLights)
        return RGB2(31, 0, 31);
    l = max(l, min(14, l * 2));
    lit[0] = min(l + 6, 31);
    lit[1] = min(l * 7 / 8 + 4, 31);
    lit[2] = l / 2;
    dark[0] = tinted & 0x1F;
    dark[1] = (tinted >> 5) & 0x1F;
    dark[2] = (tinted >> 10) & 0x1F;
    for (k = 0; k < 3; k++)
        out |= ((dark[k] * (256 - sLight) + lit[k] * sLight) >> 8) << (k * 5);
    return out;
}

static void TintColors(u16 *colors, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        colors[i] = TintColor(colors[i]);
}

#ifdef KANTO_DEBUG_START
// Détecteur d'anomalies : la teinte cesse alors que les couleurs du terrain sont toujours à l'écran (callback de
// l'animation de transition vers un combat oublié, par exemple) : le terrain réapparaît en couleurs de jour
static bool8 sWasTinted;
static u32 sTintedPalettes;

static u32 FieldPalettesChecksum(void)
{
    u32 sum = 0, i;

    for (i = 0; i < NUM_PALS_TOTAL * 16; i++)
        sum = sum * 31 + gPlttBufferFaded[i];
    return sum;
}

static void CheckTintCut(void)
{
    u32 i;

    if (!sWasTinted)
        return;
    sWasTinted = FALSE;
    // L'option coupée, ou d'autres couleurs (autre carte, autre écran) : normal
    if (!gSaveBlock2Ptr->optionsDayNight || FieldPalettesChecksum() != sTintedPalettes)
        return;
    for (i = 0; i < NUM_PALS_TOTAL * 16; i++)
    {
        if (gPlttBufferFaded[i] != RGB_BLACK)
        {
            DebugChecks_Report("teinte jour/nuit coupée", -1, "terrain encore a l'ecran sans teinte, ecran @%lld",
                               DebugTools_Offset(gMain.callback2));
            return;
        }
    }
}
#else
#define CheckTintCut() ((void)0)
#endif

void DayNight_TintPltt(void)
{
    u16 *pltt = (u16 *)PLTT;
    u32 pal, i;

    gDayNightRender.active = FALSE;
    // Le terrain est affiché : CB2_Overworld, ou CB2_OverworldBasic pendant l'animation de transition vers un combat
    // (BattleTransition_StartOnField)
    if (!gSaveBlock2Ptr->optionsDayNight || (gMain.callback2 != CB2_Overworld && gMain.callback2 != CB2_OverworldBasic)
     || !IsMapTypeOutdoors(gMapHeader.mapType))
    {
        CheckTintCut();
        return;
    }
    // L'heure n'est relue qu'une fois par seconde
    if (gMain.vblankCounter1 / 60 != sLastUpdate)
    {
        sLastUpdate = gMain.vblankCounter1 / 60;
        UpdateTint();
    }
    if (sTintR == 256 && sTintG == 256 && sTintB == 256 && sLight == 0 && !sMarkLights)
        return;
    UpdateLightMasks();
    if (sDoorAnimTiles)
        memcpy(gDayNightRender.tiles[DOOR_ANIM_TILES], sDoorAnimMasks, sizeof(sDoorAnimMasks));
    else
        memcpy(gDayNightRender.tiles[DOOR_ANIM_TILES], sMapDoorTiles, sizeof(sMapDoorTiles));
    gDayNightRender.active = sLight != 0 || sMarkLights;
#ifdef KANTO_DEBUG_START
    sWasTinted = TRUE;
    sTintedPalettes = FieldPalettesChecksum();
#endif
    for (pal = 0; pal < NUM_PALS_TOTAL; pal++)
    {
        for (i = 0; i < 16; i++, pltt++)
        {
            if (gDayNightRender.active && ((gDayNightRender.masks[pal] >> i) & 1))
                gDayNightRender.colors[pal * 16 + i] = LightColor(*pltt);
            *pltt = TintColor(*pltt);
        }
    }
    TintColors((u16 *)OBJ_PLTT, PLTT_SIZE / 2 / 2);
}
