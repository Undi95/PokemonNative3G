// PokemonNative3G : événements propres à la fusion (pas dans Émeraude ni dans RF).
#include "global.h"
#include "data.h"
#include "string_util.h"
#include "random.h"
#include "overworld.h"
#include "constants/game_stat.h"
#include "event_data.h"
#include "fusion_events.h"
#include "item.h"
#include "kanto_field_door.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
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

// POKé MONTURE (remplace les CS données à Kanto) : chaque CS de RF reçue (flags de RF) ajoute une capacité. Sans
// POKéMON de l'équipe qui la connaît, un POKéMON des environs vient l'utiliser (un pour Kanto, un pour Hoenn, qui
// peuvent tous apprendre la CS) ; les badges restent exigés (HasBadgeForFieldMove, scripts de RF). Partout.
static const struct {
    u16 move;
    u16 flag;
    u16 kantoHelper;
    u16 hoennHelper;
} sPokeMontureMoves[] = {
    {MOVE_CUT,        FLAG_KANTO_GOT_HM01, SPECIES_SCYTHER,  SPECIES_ABSOL},
    {MOVE_FLY,        FLAG_KANTO_GOT_HM02, SPECIES_PIDGEOT,  SPECIES_ALTARIA},
    {MOVE_SURF,       FLAG_KANTO_GOT_HM03, SPECIES_LAPRAS,   SPECIES_WAILORD},
    {MOVE_STRENGTH,   FLAG_KANTO_GOT_HM04, SPECIES_MACHAMP,  SPECIES_HARIYAMA},
    {MOVE_FLASH,      FLAG_KANTO_GOT_HM05, SPECIES_PIKACHU,  SPECIES_MANECTRIC},
    {MOVE_ROCK_SMASH, FLAG_KANTO_GOT_HM06, SPECIES_GOLEM,    SPECIES_AGGRON},
    {MOVE_WATERFALL,  FLAG_KANTO_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_HM07, SPECIES_SEAKING, SPECIES_MILOTIC},
};

static u16 sPokeMontureMove; // capacité en cours (pour l'image et le nom du POKéMON appelé)

static s32 PokeMonture_Find(u16 move)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sPokeMontureMoves); i++)
    {
        if (sPokeMontureMoves[i].move == move)
            return i;
    }
    return -1;
}

bool32 PokeMonture_CanUse(u16 move)
{
    s32 i = PokeMonture_Find(move);

    return i >= 0 && FlagGet(sPokeMontureMoves[i].flag) && CheckBagHasItem(ITEM_POKE_MONTURE, 1);
}

void PokeMonture_SetMove(u16 move)
{
    sPokeMontureMove = move;
}

u16 PokeMonture_HelperSpecies(void)
{
    s32 i = PokeMonture_Find(sPokeMontureMove);

    if (i < 0)
        i = 0;
    return IsKantoTilesetMap() ? sPokeMontureMoves[i].kantoHelper : sPokeMontureMoves[i].hoennHelper;
}


// Chaîne de pêche (cannes améliorées par les pêcheurs de Kanto, à la place d'une 2e canne) : chaque POKéMON remonté
// au même endroit, avec la même canne améliorée, donne un tirage chromatique de plus à la prise suivante (comme les
// chaînes de pêche de X/Y). La série se brise si rien ne mord (ou s'il s'échappe), si le joueur fait un pas ou
// change de carte, ou s'il change de canne.
#define FISHING_CHAIN_MAX 40

static const u16 sRodUpgradeFlags[] = {
    [OLD_ROD]   = FLAG_OLD_ROD_UPGRADED,
    [GOOD_ROD]  = FLAG_GOOD_ROD_UPGRADED,
    [SUPER_ROD] = FLAG_SUPER_ROD_UPGRADED,
};

static struct {
    u8 count;
    u8 rod;
    s8 mapGroup, mapNum;
    u32 steps;
} sFishingChain;

static u8 sFishingRerolls; // tirages en plus pour la prise en cours

// début de la pêche (StartFishing) : garde ou brise la série
void FishingChain_Start(u8 rod)
{
    u32 steps = GetGameStat(GAME_STAT_STEPS);

    if (rod >= ARRAY_COUNT(sRodUpgradeFlags) || !FlagGet(sRodUpgradeFlags[rod])
     || sFishingChain.rod != rod || sFishingChain.steps != steps
     || sFishingChain.mapGroup != gSaveBlock1Ptr->location.mapGroup
     || sFishingChain.mapNum != gSaveBlock1Ptr->location.mapNum)
        sFishingChain.count = 0;
    sFishingChain.rod = rod;
    sFishingChain.steps = steps;
    sFishingChain.mapGroup = gSaveBlock1Ptr->location.mapGroup;
    sFishingChain.mapNum = gSaveBlock1Ptr->location.mapNum;
    sFishingRerolls = 0;
}

// rien n'a mordu, ou il s'est échappé
void FishingChain_Break(void)
{
    sFishingChain.count = 0;
}

// un POKéMON est remonté (Fishing_StartEncounter, avant FishingWildEncounter)
void FishingChain_Hooked(void)
{
    sFishingRerolls = sFishingChain.count;
    if (sFishingChain.count < FISHING_CHAIN_MAX)
        sFishingChain.count++;
}

// FishingWildEncounter, après la création du POKéMON : tirages en plus ; s'il en gagne un, il est recréé
// chromatique avec la même espèce, le même niveau et la même nature
void FishingChain_TryShiny(struct Pokemon *mon)
{
    u32 otId, personality, hi;
    u16 species;
    u8 level, nature, i, rerolls = sFishingRerolls;

    sFishingRerolls = 0;
    if (CheckBagHasItem(ITEM_SHINY_CHARM, 1)) // CHARME CHROMA : 2 tirages de plus, comme dans les jeux suivants
        rerolls += 2;
    otId = GetMonData(mon, MON_DATA_OT_ID);
    personality = GetMonData(mon, MON_DATA_PERSONALITY);
    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_UNOWN) // sa lettre dépend de la personnalité
        return;
    if (rerolls == 0 || GET_SHINY_VALUE(otId, personality) < SHINY_ODDS)
        return;
    for (i = 0; i < rerolls; i++)
    {
        if ((Random() % (0x10000 / SHINY_ODDS)) == 0) // même chance que le tirage normal (8/65536)
            break;
    }
    if (i == rerolls)
        return;
    species = GetMonData(mon, MON_DATA_SPECIES);
    level = GetMonData(mon, MON_DATA_LEVEL);
    nature = GetNature(mon);
    do
    {
        hi = Random();
        personality = (hi << 16) | (HIHALF(otId) ^ LOHALF(otId) ^ hi ^ (Random() % SHINY_ODDS));
    } while (GetNatureFromPersonality(personality) != nature);
    CreateMon(mon, species, level, USE_RANDOM_IVS, TRUE, personality, OT_ID_PLAYER_ID, 0);
}



// OVO-CHRONO : les cycles d'éclosion comptent double (s'ajoute à Corps Ardent / Armumagma)
u8 OvoChrono_EggCycles(u8 toSub)
{
    if (CheckBagHasItem(ITEM_OVO_CHRONO, 1))
        return toSub * 2;
    return toSub;
}

// CHARME CHROMA sur les OEUFS de la PENSION : 2 tirages de plus ; s'il en gagne un, nouvelle personnalité
// chromatique (pour le dresseur) avec la même nature
u32 ShinyCharm_EggPersonality(u32 personality)
{
    u32 otId = T1_READ_32(gSaveBlock2Ptr->playerTrainerId), hi, newPersonality;
    u8 i, nature = GetNatureFromPersonality(personality);

    if (!CheckBagHasItem(ITEM_SHINY_CHARM, 1) || GET_SHINY_VALUE(otId, personality) < SHINY_ODDS)
        return personality;
    for (i = 0; i < 2; i++)
    {
        if ((Random() % (0x10000 / SHINY_ODDS)) == 0)
            break;
    }
    if (i == 2)
        return personality;
    do
    {
        hi = Random();
        newPersonality = (hi << 16) | (HIHALF(otId) ^ LOHALF(otId) ^ hi ^ (Random() % SHINY_ODDS));
    } while (newPersonality == 0 || GetNatureFromPersonality(newPersonality) != nature);
    return newPersonality;
}

// CHARME OVALE : chances de trouver un OEUF à la PENSION, valeurs des jeux suivants (20 -> 40, 50 -> 80, 70 -> 88)
u8 OvalCharm_Compatibility(u8 compatibility)
{
    if (!CheckBagHasItem(ITEM_OVAL_CHARM, 1))
        return compatibility;
    if (compatibility >= 70)
        return 88;
    if (compatibility >= 50)
        return 80;
    if (compatibility >= 20)
        return 40;
    return compatibility;
}

// AUTO-REPOUSSE (à la place du Cherch'Objet de Kanto) : VAR_RESULT = un REPOUSSE du sac (le plus faible d'abord), ou
// ITEM_NONE ; son nom dans STR_VAR_1
u16 AutoRepel_Check(void)
{
    // le même que le dernier utilisé, sinon un plus faible ; aucun : rien
    static const u16 sRepels[] = {ITEM_REPEL, ITEM_SUPER_REPEL, ITEM_MAX_REPEL};
    s32 i, start = ARRAY_COUNT(sRepels) - 1;

    if (!CheckBagHasItem(ITEM_AUTO_REPEL, 1))
        return ITEM_NONE;
    while (start > 0 && sRepels[start] != VarGet(VAR_AUTO_REPEL_LAST))
        start--;
    for (i = start; i >= 0; i--)
    {
        if (CheckBagHasItem(sRepels[i], 1))
        {
            CopyItemName(sRepels[i], gStringVar1);
            VarSet(VAR_AUTO_REPEL_LAST, sRepels[i]);
            return sRepels[i];
        }
    }
    return ITEM_NONE;
}

// VAR_0x8004 = le REPOUSSE choisi par AutoRepel_Check
void AutoRepel_Use(void)
{
    RemoveBagItem(gSpecialVar_0x8004, 1);
    VarSet(VAR_REPEL_STEP_COUNT, GetItemHoldEffectParam(gSpecialVar_0x8004));
}

// easter-egg de la Boîte Jetons (Céladopole) : LEVEINARD chromatique N.25
void GiveShinyChansey(void)
{
    struct Pokemon mon;
    u32 otId = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    u32 hi = Random();
    u32 personality = (hi << 16) | (HIHALF(otId) ^ LOHALF(otId) ^ hi ^ (Random() % SHINY_ODDS));

    CreateMon(&mon, SPECIES_CHANSEY, 25, USE_RANDOM_IVS, TRUE, personality, OT_ID_PLAYER_ID, 0);
    GiveMonToPlayer(&mon);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_CHANSEY), FLAG_SET_SEEN);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_CHANSEY), FLAG_SET_CAUGHT);
}
