#ifdef PORTABLE
// Touch controls: a D-pad and the GBA's buttons drawn over the screen's sides,
// plus a soft reset button between SELECT and START (held for RESET_HOLD_MS : a short press, not a tap).
// Always shown on Android; elsewhere, once the screen has been touched.
#include <math.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "platform/touch.h"

#define MAX_FINGERS 10
#define RESET_HOLD_MS 300

enum { ZONE_DPAD, ZONE_A, ZONE_B, ZONE_L, ZONE_R, ZONE_SELECT, ZONE_RESET, ZONE_START, ZONE_FAST, NUM_ZONES };

struct Zone
{
    float x, y, w, h; // rectangle, or circle when round (x, y = centre, w = radius)
    bool round;
};

static struct
{
    SDL_FingerID id;
    float x, y; // window pixels
    bool down;
} sFingers[MAX_FINGERS];

static struct Zone sZones[NUM_ZONES];
static float sDpadX, sDpadY, sDpadR;
static bool sEnabled;
static u16 sHeld;
static u16 sLatched; // PokemonNative3G : touches appuyées depuis la dernière lecture (appui bref = au moins une image)
static bool sResetHeld;
static Uint32 sResetSince;
static bool sResetFired;
static bool sFastOn, sFastHeld; // PokemonNative3G : avance rapide, interrupteur

// 3x5 letters for the labels
static const char *const sGlyphs[] = {
    "A", "010101111101101", "B", "110101110101110", "C", "011100100100011",
    "E", "111100110100111", "F", "111100110100100", "L", "100100100100111", "R", "110101110101101",
    "S", "011100010001110", "T", "111010010010010",
};

static void LayOut(int w, int h)
{
    float u = h / 100.0f;
    int scale = SDL_min(w / DISPLAY_WIDTH, h / DISPLAY_HEIGHT);
    float side = (w - DISPLAY_WIDTH * SDL_max(scale, 1)) / 2.0f;
    float leftX = SDL_max(side / 2, 20 * u);
    float rightX = w - leftX;
    float r = 9 * u;

    sDpadX = leftX;
    sDpadY = 58 * u;
    sDpadR = SDL_min(SDL_max(side * 0.42f, 15 * u), 24 * u);
    sZones[ZONE_DPAD] = (struct Zone){sDpadX, sDpadY, sDpadR, 0, true};
    sZones[ZONE_A] = (struct Zone){rightX + r * 1.15f, 52 * u, r, 0, true};
    sZones[ZONE_B] = (struct Zone){rightX - r * 1.15f, 66 * u, r, 0, true};
    sZones[ZONE_L] = (struct Zone){0, 0, SDL_max(side * 0.8f, 26 * u), 11 * u, false};
    sZones[ZONE_R] = (struct Zone){w - SDL_max(side * 0.8f, 26 * u), 0, SDL_max(side * 0.8f, 26 * u), 11 * u, false};
    sZones[ZONE_SELECT] = (struct Zone){w / 2.0f - 37 * u, h - 8 * u, 22 * u, 7 * u, false};
    sZones[ZONE_RESET] = (struct Zone){w / 2.0f - 11 * u, h - 8 * u, 22 * u, 7 * u, false};
    sZones[ZONE_START] = (struct Zone){w / 2.0f + 15 * u, h - 8 * u, 22 * u, 7 * u, false};
    sZones[ZONE_FAST] = (struct Zone){w / 2.0f - 11 * u, 0, 22 * u, 9 * u, false};
}

static bool InZone(const struct Zone *zone, float x, float y, float margin)
{
    if (zone->round)
    {
        float dx = x - zone->x, dy = y - zone->y;
        return dx * dx + dy * dy < zone->w * zone->w * margin * margin;
    }
    return x >= zone->x - zone->w * (margin - 1) / 2 && x < zone->x + zone->w * (margin + 1) / 2
        && y >= zone->y - zone->h * (margin - 1) / 2 && y < zone->y + zone->h * (margin + 1) / 2;
}

static void Update(void)
{
    static const u16 sZoneKeys[NUM_ZONES] = {
        [ZONE_A] = A_BUTTON, [ZONE_B] = B_BUTTON, [ZONE_L] = L_BUTTON, [ZONE_R] = R_BUTTON,
        [ZONE_SELECT] = SELECT_BUTTON, [ZONE_START] = START_BUTTON,
    };
    bool reset = false, fast = false;

    sHeld = 0;
    for (int i = 0; i < MAX_FINGERS; i++)
    {
        float x = sFingers[i].x, y = sFingers[i].y;

        if (!sFingers[i].down)
            continue;
        // D-pad: eight directions around its centre
        if (InZone(&sZones[ZONE_DPAD], x, y, 1.5f))
        {
            float dx = x - sDpadX, dy = y - sDpadY;

            if (dx * dx + dy * dy > sDpadR * sDpadR * 0.04f)
            {
                int sector = ((int)floorf(atan2f(dy, dx) / (float)(M_PI / 4) + 0.5f) + 8) % 8;
                static const u16 sDirs[8] = {
                    DPAD_RIGHT, DPAD_RIGHT | DPAD_DOWN, DPAD_DOWN, DPAD_DOWN | DPAD_LEFT,
                    DPAD_LEFT, DPAD_LEFT | DPAD_UP, DPAD_UP, DPAD_UP | DPAD_RIGHT,
                };
                sHeld |= sDirs[sector];
                sLatched |= sDirs[sector];
            }
            continue;
        }
        for (int zone = ZONE_A; zone < NUM_ZONES; zone++)
        {
            if (InZone(&sZones[zone], x, y, zone <= ZONE_B ? 1.35f : 1.3f))
            {
                sHeld |= sZoneKeys[zone];
                sLatched |= sZoneKeys[zone];
                if (zone == ZONE_RESET)
                    reset = true;
                if (zone == ZONE_FAST)
                    fast = true;
                break;
            }
        }
    }
    if (reset && !sResetHeld)
    {
        sResetSince = SDL_GetTicks();
        sResetFired = false;
    }
    sResetHeld = reset;
    if (fast && !sFastHeld)
        sFastOn = !sFastOn;
    sFastHeld = fast;
}

bool Touch_FastForward(void)
{
    return sFastOn;
}

void Touch_Init(void)
{
#ifdef __ANDROID__
    sEnabled = true;
#endif
}

void Touch_HandleEvent(const SDL_Event *event, SDL_Window *window)
{
    int w, h, slot = -1;

    if (event->type != SDL_FINGERDOWN && event->type != SDL_FINGERMOTION && event->type != SDL_FINGERUP)
        return;
    sEnabled = true;
    SDL_GetRendererOutputSize(SDL_GetRenderer(window), &w, &h); // PokemonNative3G : pixels du rendu, comme l'image
    LayOut(w, h);
    for (int i = 0; i < MAX_FINGERS; i++)
    {
        if (sFingers[i].down && sFingers[i].id == event->tfinger.fingerId)
            slot = i;
    }
    if (slot < 0)
    {
        if (event->type != SDL_FINGERDOWN)
            return;
        for (int i = 0; i < MAX_FINGERS && slot < 0; i++)
        {
            if (!sFingers[i].down)
                slot = i;
        }
        if (slot < 0)
            return;
    }
    sFingers[slot].id = event->tfinger.fingerId;
    sFingers[slot].x = event->tfinger.x * w;
    sFingers[slot].y = event->tfinger.y * h;
    sFingers[slot].down = (event->type != SDL_FINGERUP);
    Update();
}

u16 Touch_GetButtons(void)
{
    u16 keys = sHeld | sLatched;

    sLatched = 0;
    return keys;
}

bool Touch_ResetRequested(void)
{
    if (sResetHeld && !sResetFired && SDL_GetTicks() - sResetSince >= RESET_HOLD_MS)
    {
        sResetFired = true;
        return true;
    }
    return false;
}

static void FillCircle(SDL_Renderer *renderer, float cx, float cy, float r, SDL_Color color)
{
    SDL_Vertex v[3 * 32];

    for (int i = 0; i < 32; i++)
    {
        float a0 = i * 2 * (float)M_PI / 32, a1 = (i + 1) * 2 * (float)M_PI / 32;

        v[i * 3 + 0] = (SDL_Vertex){{cx, cy}, color, {0, 0}};
        v[i * 3 + 1] = (SDL_Vertex){{cx + r * cosf(a0), cy + r * sinf(a0)}, color, {0, 0}};
        v[i * 3 + 2] = (SDL_Vertex){{cx + r * cosf(a1), cy + r * sinf(a1)}, color, {0, 0}};
    }
    SDL_RenderGeometry(renderer, NULL, v, 3 * 32, NULL, 0);
}

static void DrawLabel(SDL_Renderer *renderer, const char *text, float cx, float cy, float px)
{
    float x = cx - (strlen(text) * 4 - 1) * px / 2;

    for (; *text != '\0'; text++, x += 4 * px)
    {
        for (int g = 0; g < (int)ARRAY_COUNT(sGlyphs); g += 2)
        {
            if (sGlyphs[g][0] != *text)
                continue;
            for (int i = 0; i < 15; i++)
            {
                if (sGlyphs[g + 1][i] == '1')
                {
                    SDL_FRect dot = {x + (i % 3) * px, cy - 2.5f * px + (i / 3) * px, px, px};
                    SDL_RenderFillRectF(renderer, &dot);
                }
            }
        }
    }
}

void Touch_Draw(SDL_Renderer *renderer, SDL_Window *window)
{
    static const char *const sLabels[NUM_ZONES] = {"", "A", "B", "L", "R", "SELECT", "RESET", "START", "FAST"};
    SDL_Color idle = {255, 255, 255, 70}, pressed = {255, 255, 255, 150};
    int w, h;
    float u;

    if (!sEnabled)
        return;
    SDL_GetRendererOutputSize(SDL_GetRenderer(window), &w, &h); // PokemonNative3G : pixels du rendu, comme l'image
    LayOut(w, h);
    u = h / 100.0f;

    // Draw in window pixels, outside the game's area
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // D-pad
    {
        float r = sDpadR, t = sDpadR * 0.66f;
        SDL_FRect arms[4] = {
            {sDpadX - t / 2, sDpadY - r, t, r - t / 2}, {sDpadX - t / 2, sDpadY + t / 2, t, r - t / 2},
            {sDpadX - r, sDpadY - t / 2, r - t / 2, t}, {sDpadX + t / 2, sDpadY - t / 2, r - t / 2, t},
        };
        u16 dirs[4] = {DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT};
        SDL_FRect middle = {sDpadX - t / 2, sDpadY - t / 2, t, t};

        SDL_SetRenderDrawColor(renderer, idle.r, idle.g, idle.b, idle.a);
        SDL_RenderFillRectF(renderer, &middle);
        for (int i = 0; i < 4; i++)
        {
            SDL_Color c = (sHeld & dirs[i]) ? pressed : idle;
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_RenderFillRectF(renderer, &arms[i]);
        }
    }

    for (int zone = ZONE_A; zone < NUM_ZONES; zone++)
    {
        const struct Zone *z = &sZones[zone];
        static const u16 sKeys[NUM_ZONES] = {
            [ZONE_A] = A_BUTTON, [ZONE_B] = B_BUTTON, [ZONE_L] = L_BUTTON, [ZONE_R] = R_BUTTON,
            [ZONE_SELECT] = SELECT_BUTTON, [ZONE_START] = START_BUTTON,
        };
        bool down = (zone == ZONE_RESET) ? sResetHeld : (zone == ZONE_FAST) ? sFastOn : (sHeld & sKeys[zone]) != 0;
        SDL_Color c = down ? pressed : idle;
        float cx, cy;

        if (z->round)
        {
            FillCircle(renderer, z->x, z->y, z->w, c);
            cx = z->x, cy = z->y;
        }
        else
        {
            SDL_FRect rect = {z->x + u * 0.5f, z->y + u * 0.5f, z->w - u, z->h - u};
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_RenderFillRectF(renderer, &rect);
            cx = z->x + z->w / 2, cy = z->y + z->h / 2;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
        DrawLabel(renderer, sLabels[zone], cx, cy, zone <= ZONE_B ? 2 * u : 0.8f * u);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
#endif // PORTABLE
