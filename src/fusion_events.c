// PokemonNative3G : événements propres à la fusion (pas dans Émeraude ni dans RF).
#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/flags.h"
#include "constants/kanto_flags_vars.h"
#include "constants/species.h"
#include "constants/vars.h"

// Œufs des starters manquants : un assistant dans chaque pension (Route 117 à Hoenn, Île 4 à Kanto) donne,
// après la Ligue de sa région, un œuf de chaque starter jamais attrapé. Hoenn : starters de Hoenn, et ceux de
// Johto une fois celui du PROF. SEKO reçu (avant, ses trois Poké Balls l'attendent encore).
#define STARTER_EGGS_NOT_YET 0xFFFF

static const u16 sKantoStarterEggs[] = {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE};
static const u16 sHoennStarterEggs[] = {SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP,
                                        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE};

// bits de VAR_STARTER_EGGS_GIVEN : 0-2 Kanto, 3-8 Hoenn (dans l'ordre des tableaux)
static u16 StarterEggBit(u16 species)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sKantoStarterEggs); i++)
        if (sKantoStarterEggs[i] == species)
            return 1 << i;
    for (i = 0; i < ARRAY_COUNT(sHoennStarterEggs); i++)
        if (sHoennStarterEggs[i] == species)
            return 1 << (ARRAY_COUNT(sKantoStarterEggs) + i);
    return 0;
}

// VAR_0x8004 : 0 = Kanto, 1 = Hoenn. Rend l'espèce de l'œuf à donner, SPECIES_NONE s'il n'y en a plus,
// STARTER_EGGS_NOT_YET avant la Ligue de la région.
u16 GetStarterEggToGive(void)
{
    const u16 *list;
    u32 i, count;

    if (gSpecialVar_0x8004 == 0)
    {
        if (!FlagGet(FLAG_KANTO_SYS_GAME_CLEAR))
            return STARTER_EGGS_NOT_YET;
        list = sKantoStarterEggs;
        count = ARRAY_COUNT(sKantoStarterEggs);
    }
    else
    {
        if (!FlagGet(FLAG_SYS_GAME_CLEAR))
            return STARTER_EGGS_NOT_YET;
        list = sHoennStarterEggs;
        count = VarGet(VAR_DEX_UPGRADE_JOHTO_STARTER_STATE) >= 6 ? ARRAY_COUNT(sHoennStarterEggs) : 3;
    }
    for (i = 0; i < count; i++)
    {
        if (VarGet(VAR_STARTER_EGGS_GIVEN) & StarterEggBit(list[i]))
            continue;
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(list[i]), FLAG_GET_CAUGHT))
            continue;
        return list[i];
    }
    return SPECIES_NONE;
}

// VAR_0x8005 : l'espèce de l'œuf donné
void SetStarterEggGiven(void)
{
    VarSet(VAR_STARTER_EGGS_GIVEN, VarGet(VAR_STARTER_EGGS_GIVEN) | StarterEggBit(gSpecialVar_0x8005));
}
