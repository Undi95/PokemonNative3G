#include "global.h"
#include "random.h"

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
COMMON_DATA u32 gRngValue = 0;
COMMON_DATA u32 gRng2Value = 0;

#ifdef KANTO_DEBUG_START
// PokemonNative3G (outil de debug jeu.hasard.appels) : les derniers appelants de Random() et leur nombre, pour
// trouver ce qui consomme le hasard (une référence d'écran qui change, un rapport de bug rejoué)
const void *gRandomCallers[RANDOM_CALLERS_COUNT];
u32 gRandomCallCount;
#endif

u16 Random(void)
{
#ifdef KANTO_DEBUG_START
    gRandomCallers[gRandomCallCount++ % RANDOM_CALLERS_COUNT] = __builtin_return_address(0);
#endif
    gRngValue = ISO_RANDOMIZE1(gRngValue);
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}
