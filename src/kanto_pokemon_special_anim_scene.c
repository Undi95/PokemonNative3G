// Rouge Feu : pokemon_special_anim_scene.c
#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "dynamic_placeholder_text_util.h"
#include "gpu_regs.h"
#include "item.h"
#include "item_use.h"
#include "kanto_pokemon_special_anim_internal.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "random.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trig.h"
#include "window.h"
#include "constants/items.h"
#include "constants/kanto/pokemon_special_anim.h"
#include "constants/songs.h"

#define FONT_NORMAL FONT_KANTO // police de RF (écran de RF)
#include "constants/rgb.h"
#include "dma3.h"
#include "kanto_bag_internal.h" // noms de RF (sac de RF) : AddItemIconObject, GetTextSpeedSetting, ItemId_GetName...
#define DMA3_32BIT 1 // RF : dma3.h (même valeur pour RequestDma3Fill d'Émeraude)

// Rouge Feu (strings_*_fr.h)
static const u8 sKText_Text_And[] = _("Et…\p");
static const u8 sKText_Text_Counting_1[] = _("1, ");
static const u8 sKText_Text_Counting_2And[] = _("2, et… … …");
static const u8 sKText_Text_Huh[] = _("Hein?");
static const u8 sKText_Text_LevelRoseTo[] = _("{STR_VAR_1} monte\nau N. {STR_VAR_2}.");
static const u8 sKText_Text_LevelUp_Attack[] = _("ATTAQUE");
static const u8 sKText_Text_LevelUp_Defense[] = _("DEFENSE");
static const u8 sKText_Text_LevelUp_MaxHP[] = _("{FONT_SMALL}PV{FONT_NORMAL} MAX.");
static const u8 sKText_Text_LevelUp_Minus[] = _("{FONT_SMALL}-{FONT_NORMAL}");
static const u8 sKText_Text_LevelUp_Plus[] = _("{FONT_SMALL}{PLUS}{FONT_NORMAL}");
static const u8 sKText_Text_LevelUp_SpAtk[] = _("ATQ. SPE.");
static const u8 sKText_Text_LevelUp_SpDef[] = _("DEF. SPE.");
static const u8 sKText_Text_LevelUp_Speed[] = _("VITESSE");
static const u8 sKText_Text_MachineSet[] = _("Capsule enclenchée!\p");
static const u8 sKText_Text_MonForgotMove[] = _("{DYNAMIC 0x00} ne sait plus comment\nutiliser {DYNAMIC 0x01}.\p");
static const u8 sKText_Text_MonLearnedTMHM[] = _("{DYNAMIC 0x00} apprend\n{DYNAMIC 0x01}!");
static const u8 sKText_Text_Poof[] = _("Tadaa!\p");
static const u8 sKText_Text_WasUsedOn[] = _("{STR_VAR_2} est utilisé\nsur {STR_VAR_1}.");



// ---- Rouge Feu (menu2.c) : position du Pokémon et de l'objet pour chaque espèce ----
enum
{
    PSA_MON_ATTR_TMHM_X_POS,
    PSA_MON_ATTR_TMHM_Y_POS,
    PSA_MON_ATTR_Y_OFFSET,
    PSA_MON_ATTR_ITEM_X_POS,
    PSA_MON_ATTR_ITEM_Y_POS,
    PSA_MON_ATTR_COUNT
};

// Not actually "old" given these were introduced in Gen 3,
// but they're used as equivalents here alongside the other OLD_UNOWN
#define SPECIES_OLD_UNOWN_EMARK (NUM_SPECIES + 0)
#define SPECIES_OLD_UNOWN_QMARK (NUM_SPECIES + 1)


static const u8 sMonPosAttributes[][PSA_MON_ATTR_COUNT] = {
                                  // TMHM_X, TMHM_Y, Y_OFFSET, ITEM_X, ITEM_Y
    [SPECIES_BULBASAUR       - 1] = {22, 27, 48, 22, 41},
    [SPECIES_IVYSAUR         - 1] = {20, 27, 48, 21, 42},
    [SPECIES_VENUSAUR        - 1] = {27, 32, 32, 27, 51},
    [SPECIES_CHARMANDER      - 1] = {20, 15, 56, 19, 30},
    [SPECIES_CHARMELEON      - 1] = {13, 17, 48, 15, 34},
    [SPECIES_CHARIZARD       - 1] = {27,  7, 40, 26, 25},
    [SPECIES_SQUIRTLE        - 1] = {25, 19, 48, 26, 34},
    [SPECIES_WARTORTLE       - 1] = {22, 19, 48, 23, 33},
    [SPECIES_BLASTOISE       - 1] = {18,  8, 40, 21, 25},
    [SPECIES_CATERPIE        - 1] = {21, 20, 48, 19, 36},
    [SPECIES_METAPOD         - 1] = {19, 29, 48, 24, 42},
    [SPECIES_BUTTERFREE      - 1] = {18, 27,  8, 18, 42},
    [SPECIES_WEEDLE          - 1] = {22, 28, 48, 21, 43},
    [SPECIES_KAKUNA          - 1] = {25, 19, 48, 26, 36},
    [SPECIES_BEEDRILL        - 1] = {25, 22,  8, 25, 37},
    [SPECIES_PIDGEY          - 1] = {21, 18, 48, 18, 30},
    [SPECIES_PIDGEOTTO       - 1] = {36, 14, 48, 31, 30},
    [SPECIES_PIDGEOT         - 1] = {12, 19,  8, 10, 35},
    [SPECIES_RATTATA         - 1] = {23, 30, 48, 24, 45},
    [SPECIES_RATICATE        - 1] = {18, 20, 48, 16, 38},
    [SPECIES_SPEAROW         - 1] = {21, 20, 48, 21, 31},
    [SPECIES_FEAROW          - 1] = {12, 39,  0, 11, 63},
    [SPECIES_EKANS           - 1] = {17, 15, 48, 20, 29},
    [SPECIES_ARBOK           - 1] = {27,  1, 40, 29, 16},
    [SPECIES_PIKACHU         - 1] = {25, 19, 48, 26, 31},
    [SPECIES_RAICHU          - 1] = {25, 20, 40, 28, 34},
    [SPECIES_SANDSHREW       - 1] = {23, 22, 48, 24, 37},
    [SPECIES_SANDSLASH       - 1] = {17, 19, 40, 19, 34},
    [SPECIES_NIDORAN_F       - 1] = {22, 21, 48, 24, 33},
    [SPECIES_NIDORINA        - 1] = {31, 23, 48, 30, 40},
    [SPECIES_NIDOQUEEN       - 1] = {16, 11, 40, 19, 28},
    [SPECIES_NIDORAN_M       - 1] = {21, 34, 40, 21, 49},
    [SPECIES_NIDORINO        - 1] = {19, 30, 40, 27, 45},
    [SPECIES_NIDOKING        - 1] = {18, 21, 40, 19, 39},
    [SPECIES_CLEFAIRY        - 1] = {25, 20, 48, 27, 36},
    [SPECIES_CLEFABLE        - 1] = {28, 18, 48, 29, 33},
    [SPECIES_VULPIX          - 1] = {16, 22, 48, 14, 37},
    [SPECIES_NINETALES       - 1] = {40, 16, 40, 39, 30},
    [SPECIES_JIGGLYPUFF      - 1] = {29, 21, 48, 30, 37},
    [SPECIES_WIGGLYTUFF      - 1] = {26, 18, 48, 28, 34},
    [SPECIES_ZUBAT           - 1] = {20, 29,  8, 20, 41},
    [SPECIES_GOLBAT          - 1] = {35, 26,  0, 33, 46},
    [SPECIES_ODDISH          - 1] = {29, 32, 40, 29, 43},
    [SPECIES_GLOOM           - 1] = {28, 24, 40, 28, 39},
    [SPECIES_VILEPLUME       - 1] = {28, 30, 40, 29, 42},
    [SPECIES_PARAS           - 1] = {29, 26, 48, 28, 39},
    [SPECIES_PARASECT        - 1] = {30, 28, 40, 32, 46},
    [SPECIES_VENONAT         - 1] = {27, 22, 16, 26, 41},
    [SPECIES_VENOMOTH        - 1] = {18, 25,  8, 22, 39},
    [SPECIES_DIGLETT         - 1] = {30, 22, 48, 28, 35},
    [SPECIES_DUGTRIO         - 1] = {26, 17, 48, 26, 31},
    [SPECIES_MEOWTH          - 1] = {28, 22, 48, 28, 35},
    [SPECIES_PERSIAN         - 1] = {19, 19, 48, 19, 33},
    [SPECIES_PSYDUCK         - 1] = {28, 19, 48, 23, 41},
    [SPECIES_GOLDUCK         - 1] = {23, 18, 40, 23, 34},
    [SPECIES_MANKEY          - 1] = {28, 21, 48, 27, 35},
    [SPECIES_PRIMEAPE        - 1] = {30, 22, 48, 26, 39},
    [SPECIES_GROWLITHE       - 1] = {20, 23, 48, 20, 36},
    [SPECIES_ARCANINE        - 1] = {15,  9, 40, 12, 25},
    [SPECIES_POLIWAG         - 1] = {21, 20, 48, 19, 31},
    [SPECIES_POLIWHIRL       - 1] = {31, 16, 48, 30, 23},
    [SPECIES_POLIWRATH       - 1] = {34, 12, 48, 33, 24},
    [SPECIES_ABRA            - 1] = {31, 19, 48, 31, 33},
    [SPECIES_KADABRA         - 1] = {27, 18, 48, 28, 37},
    [SPECIES_ALAKAZAM        - 1] = {28, 17, 40, 29, 38},
    [SPECIES_MACHOP          - 1] = {27, 17, 48, 27, 30},
    [SPECIES_MACHOKE         - 1] = {29, 17, 48, 29, 31},
    [SPECIES_MACHAMP         - 1] = {26, 13, 40, 28, 27},
    [SPECIES_BELLSPROUT      - 1] = {21, 14, 48, 14, 28},
    [SPECIES_WEEPINBELL      - 1] = {26, 28, 16, 21, 50},
    [SPECIES_VICTREEBEL      - 1] = {30, 15, 48, 28, 27},
    [SPECIES_TENTACOOL       - 1] = {26, 21, 48, 30, 38},
    [SPECIES_TENTACRUEL      - 1] = {27, 16, 40, 28, 38},
    [SPECIES_GEODUDE         - 1] = {28, 32, 40, 29, 45},
    [SPECIES_GRAVELER        - 1] = {29, 25, 40, 30, 38},
    [SPECIES_GOLEM           - 1] = {25, 27, 40, 28, 39},
    [SPECIES_PONYTA          - 1] = {15, 17, 48, 14, 35},
    [SPECIES_RAPIDASH        - 1] = {47, 15, 40, 43, 30},
    [SPECIES_SLOWPOKE        - 1] = {20, 31, 40, 21, 47},
    [SPECIES_SLOWBRO         - 1] = {14, 13, 40, 12, 31},
    [SPECIES_MAGNEMITE       - 1] = {32, 27, 16, 31, 41},
    [SPECIES_MAGNETON        - 1] = {31, 20,  8, 31, 34},
    [SPECIES_FARFETCHD       - 1] = {22, 20, 48, 22, 41},
    [SPECIES_DODUO           - 1] = {17, 22, 48, 13, 44},
    [SPECIES_DODRIO          - 1] = {29,  4, 40, 14, 7},
    [SPECIES_SEEL            - 1] = {27, 36, 32, 23, 53},
    [SPECIES_DEWGONG         - 1] = {18, 10, 48, 14, 26},
    [SPECIES_GRIMER          - 1] = {31, 16, 48, 29, 37},
    [SPECIES_MUK             - 1] = {23, 15, 48, 25, 34},
    [SPECIES_SHELLDER        - 1] = {26, 24, 48, 23, 41},
    [SPECIES_CLOYSTER        - 1] = {25, 30, 40, 29, 44},
    [SPECIES_GASTLY          - 1] = {26, 31,  8, 25, 48},
    [SPECIES_HAUNTER         - 1] = {32, 20,  8, 29, 38},
    [SPECIES_GENGAR          - 1] = {26, 22, 48, 25, 40},
    [SPECIES_ONIX            - 1] = {31, 36, 32, 40, 54},
    [SPECIES_DROWZEE         - 1] = {26, 14, 48, 26, 30},
    [SPECIES_HYPNO           - 1] = {28, 18, 48, 25, 36},
    [SPECIES_KRABBY          - 1] = {29, 29, 48, 26, 43},
    [SPECIES_KINGLER         - 1] = {30, 31, 40, 28, 48},
    [SPECIES_VOLTORB         - 1] = {28, 27, 48, 27, 43},
    [SPECIES_ELECTRODE       - 1] = {28, 24, 48, 29, 46},
    [SPECIES_EXEGGCUTE       - 1] = {33, 23, 48, 32, 36},
    [SPECIES_EXEGGUTOR       - 1] = {28, 23, 40, 27, 37},
    [SPECIES_CUBONE          - 1] = {27, 18, 48, 27, 34},
    [SPECIES_MAROWAK         - 1] = {20, 15, 48, 17, 35},
    [SPECIES_HITMONLEE       - 1] = {46, 17, 48, 40, 34},
    [SPECIES_HITMONCHAN      - 1] = {34, 14, 48, 30, 29},
    [SPECIES_LICKITUNG       - 1] = {20, 17, 48, 20, 36},
    [SPECIES_KOFFING         - 1] = {30, 20, 16, 29, 32},
    [SPECIES_WEEZING         - 1] = {17, 13, 16, 15, 28},
    [SPECIES_RHYHORN         - 1] = {14, 35, 32, 20, 51},
    [SPECIES_RHYDON          - 1] = {13, 18, 40, 23, 34},
    [SPECIES_CHANSEY         - 1] = {26, 13, 48, 26, 26},
    [SPECIES_TANGELA         - 1] = {28, 24, 48, 29, 41},
    [SPECIES_KANGASKHAN      - 1] = {27,  6, 40, 28, 20},
    [SPECIES_HORSEA          - 1] = {28, 20, 48, 22, 35},
    [SPECIES_SEADRA          - 1] = {16, 23, 48,  9, 42},
    [SPECIES_GOLDEEN         - 1] = {22, 35, 32, 21, 52},
    [SPECIES_SEAKING         - 1] = {22, 15, 48, 16, 24},
    [SPECIES_STARYU          - 1] = {28, 24, 48, 26, 38},
    [SPECIES_STARMIE         - 1] = {29, 19, 48, 27, 32},
    [SPECIES_MR_MIME         - 1] = {36, 17, 48, 37, 30},
    [SPECIES_SCYTHER         - 1] = {16, 25, 40, 18, 39},
    [SPECIES_JYNX            - 1] = {27, 15, 48, 25, 28},
    [SPECIES_ELECTABUZZ      - 1] = {20, 17, 48, 23, 32},
    [SPECIES_MAGMAR          - 1] = {16, 14, 48, 11, 25},
    [SPECIES_PINSIR          - 1] = {29, 28, 40, 32, 43},
    [SPECIES_TAUROS          - 1] = {17, 29, 40, 19, 46},
    [SPECIES_MAGIKARP        - 1] = {22, 21, 48, 19, 35},
    [SPECIES_GYARADOS        - 1] = {11, 24, 40, 22, 41},
    [SPECIES_LAPRAS          - 1] = {22,  8, 40, 21, 22},
    [SPECIES_DITTO           - 1] = {36, 18, 48, 31, 32},
    [SPECIES_EEVEE           - 1] = {22, 22, 48, 22, 35},
    [SPECIES_VAPOREON        - 1] = {24, 35, 40, 24, 48},
    [SPECIES_JOLTEON         - 1] = {20, 27, 48, 22, 40},
    [SPECIES_FLAREON         - 1] = {22, 23, 48, 20, 37},
    [SPECIES_PORYGON         - 1] = {24, 18, 48, 16, 35},
    [SPECIES_OMANYTE         - 1] = {29, 29, 48, 28, 43},
    [SPECIES_OMASTAR         - 1] = {22, 26, 48, 25, 45},
    [SPECIES_KABUTO          - 1] = {27, 22, 48, 26, 39},
    [SPECIES_KABUTOPS        - 1] = {21, 17, 48, 21, 31},
    [SPECIES_AERODACTYL      - 1] = {19, 29,  0, 20, 48},
    [SPECIES_SNORLAX         - 1] = {53,  9, 48, 46, 20},
    [SPECIES_ARTICUNO        - 1] = {24, 11, 24, 23, 23},
    [SPECIES_ZAPDOS          - 1] = {14, 14, 16,  4, 40},
    [SPECIES_MOLTRES         - 1] = {11, 42,  8, 11, 56},
    [SPECIES_DRATINI         - 1] = {13, 18, 48, 11, 33},
    [SPECIES_DRAGONAIR       - 1] = {24, 14, 48, 19, 28},
    [SPECIES_DRAGONITE       - 1] = {27,  7, 24, 25, 23},
    [SPECIES_MEWTWO          - 1] = {43,  9, 40, 44, 24},
    [SPECIES_MEW             - 1] = {25, 20, 16, 31, 33},
    [SPECIES_CHIKORITA       - 1] = {27, 23, 48, 27, 36},
    [SPECIES_BAYLEEF         - 1] = {29, 16, 48, 32, 29},
    [SPECIES_MEGANIUM        - 1] = { 5, 13, 40, 13, 27},
    [SPECIES_CYNDAQUIL       - 1] = {17, 27, 48, 20, 39},
    [SPECIES_QUILAVA         - 1] = {37, 24, 48, 39, 38},
    [SPECIES_TYPHLOSION      - 1] = { 9, 16, 40, 16, 28},
    [SPECIES_TOTODILE        - 1] = {22, 16, 48, 25, 32},
    [SPECIES_CROCONAW        - 1] = {22, 16, 48, 24, 33},
    [SPECIES_FERALIGATR      - 1] = {14, 10, 40,  8, 26},
    [SPECIES_SENTRET         - 1] = {30, 10, 48, 29, 21},
    [SPECIES_FURRET          - 1] = {33, 14, 48, 33, 25},
    [SPECIES_HOOTHOOT        - 1] = {29, 21, 48, 28, 36},
    [SPECIES_NOCTOWL         - 1] = {25, 14, 48, 24, 28},
    [SPECIES_LEDYBA          - 1] = {27, 21, 48, 28, 36},
    [SPECIES_LEDIAN          - 1] = {24, 18, 16, 28, 33},
    [SPECIES_SPINARAK        - 1] = {32, 32, 40, 32, 45},
    [SPECIES_ARIADOS         - 1] = {23, 35, 40, 21, 48},
    [SPECIES_CROBAT          - 1] = {34, 30,  8, 35, 43},
    [SPECIES_CHINCHOU        - 1] = {31, 29, 48, 31, 41},
    [SPECIES_LANTURN         - 1] = {16, 35, 40, 25, 51},
    [SPECIES_PICHU           - 1] = {30, 23, 48, 30, 36},
    [SPECIES_CLEFFA          - 1] = {28, 24, 48, 30, 38},
    [SPECIES_IGGLYBUFF       - 1] = {31, 25, 48, 31, 36},
    [SPECIES_TOGEPI          - 1] = {33, 21, 48, 31, 32},
    [SPECIES_TOGETIC         - 1] = {27, 16, 48, 28, 28},
    [SPECIES_NATU            - 1] = {28, 23, 48, 21, 33},
    [SPECIES_XATU            - 1] = {27,  8, 48, 25, 20},
    [SPECIES_MAREEP          - 1] = {22, 21, 48, 21, 36},
    [SPECIES_FLAAFFY         - 1] = {25, 18, 48, 24, 33},
    [SPECIES_AMPHAROS        - 1] = {15, 10, 48, 16, 27},
    [SPECIES_BELLOSSOM       - 1] = {31, 19, 48, 31, 32},
    [SPECIES_MARILL          - 1] = {29, 21, 48, 29, 34},
    [SPECIES_AZUMARILL       - 1] = {26, 18, 48, 23, 31},
    [SPECIES_SUDOWOODO       - 1] = {32, 16, 48, 32, 31},
    [SPECIES_POLITOED        - 1] = {29, 15, 48, 30, 32},
    [SPECIES_HOPPIP          - 1] = {35, 37,  8, 37, 51},
    [SPECIES_SKIPLOOM        - 1] = {30, 24,  8, 28, 39},
    [SPECIES_JUMPLUFF        - 1] = {29, 33,  8, 32, 47},
    [SPECIES_AIPOM           - 1] = {30, 41, 24, 30, 53},
    [SPECIES_SUNKERN         - 1] = {31, 32,  8, 36, 46},
    [SPECIES_SUNFLORA        - 1] = {28, 12, 48, 27, 25},
    [SPECIES_YANMA           - 1] = {27, 40,  8, 22, 53},
    [SPECIES_WOOPER          - 1] = {29, 19, 48, 31, 33},
    [SPECIES_QUAGSIRE        - 1] = {21,  9, 48, 18, 24},
    [SPECIES_ESPEON          - 1] = {17, 27, 48, 17, 41},
    [SPECIES_UMBREON         - 1] = {35, 21, 48, 35, 34},
    [SPECIES_MURKROW         - 1] = {36, 19, 48, 32, 34},
    [SPECIES_SLOWKING        - 1] = {30, 19, 40, 29, 37},
    [SPECIES_MISDREAVUS      - 1] = {40, 33,  8, 38, 46},
    [SPECIES_UNOWN           - 1] = {32, 23,  8, 31, 33},
    [SPECIES_WOBBUFFET       - 1] = {29,  9, 48, 29, 26},
    [SPECIES_GIRAFARIG       - 1] = {11, 13, 40, 17, 29},
    [SPECIES_PINECO          - 1] = {29, 18, 16, 25, 37},
    [SPECIES_FORRETRESS      - 1] = {25, 23,  8, 30, 38},
    [SPECIES_DUNSPARCE       - 1] = {16, 27, 48, 12, 45},
    [SPECIES_GLIGAR          - 1] = {30, 19,  8, 29, 35},
    [SPECIES_STEELIX         - 1] = {12, 13, 40, 13, 28},
    [SPECIES_SNUBBULL        - 1] = {27, 21, 48, 26, 35},
    [SPECIES_GRANBULL        - 1] = {28,  9, 48, 25, 24},
    [SPECIES_QWILFISH        - 1] = {31, 38, 32, 29, 51},
    [SPECIES_SCIZOR          - 1] = {21, 15, 16, 26, 26},
    [SPECIES_SHUCKLE         - 1] = {37, 10, 48, 36, 24},
    [SPECIES_HERACROSS       - 1] = {24, 25, 40, 26, 38},
    [SPECIES_SNEASEL         - 1] = {28, 19, 48, 29, 36},
    [SPECIES_TEDDIURSA       - 1] = {30, 18, 48, 27, 35},
    [SPECIES_URSARING        - 1] = {30,  4, 40, 29, 20},
    [SPECIES_SLUGMA          - 1] = {32, 24, 48, 32, 40},
    [SPECIES_MAGCARGO        - 1] = {22, 17, 48, 23, 35},
    [SPECIES_SWINUB          - 1] = {28, 24, 48, 27, 37},
    [SPECIES_PILOSWINE       - 1] = {24, 35, 32, 24, 54},
    [SPECIES_CORSOLA         - 1] = {25, 29, 40, 25, 43},
    [SPECIES_REMORAID        - 1] = {21, 31, 40, 19, 43},
    [SPECIES_OCTILLERY       - 1] = {28, 17, 48, 26, 32},
    [SPECIES_DELIBIRD        - 1] = {29, 17, 48, 27, 31},
    [SPECIES_MANTINE         - 1] = {22, 30, 40, 31, 39},
    [SPECIES_SKARMORY        - 1] = {30,  0, 40, 19, 7},
    [SPECIES_HOUNDOUR        - 1] = {37, 17, 48, 37, 31},
    [SPECIES_HOUNDOOM        - 1] = {13, 19, 48, 13, 36},
    [SPECIES_KINGDRA         - 1] = {14, 19, 40, 10, 44},
    [SPECIES_PHANPY          - 1] = {27, 17, 48, 25, 36},
    [SPECIES_DONPHAN         - 1] = {17, 21, 48, 25, 44},
    [SPECIES_PORYGON2        - 1] = {24, 17, 48, 17, 32},
    [SPECIES_STANTLER        - 1] = {21, 21, 40, 23, 40},
    [SPECIES_SMEARGLE        - 1] = {24, 16, 48, 27, 37},
    [SPECIES_TYROGUE         - 1] = {30, 18, 48, 31, 31},
    [SPECIES_HITMONTOP       - 1] = {26, 57, 16, 26, 43},
    [SPECIES_SMOOCHUM        - 1] = {32, 24, 48, 33, 38},
    [SPECIES_ELEKID          - 1] = {29, 20, 48, 29, 35},
    [SPECIES_MAGBY           - 1] = {28, 21, 48, 26, 36},
    [SPECIES_MILTANK         - 1] = {24, 14, 48, 24, 30},
    [SPECIES_BLISSEY         - 1] = {29,  9, 48, 29, 25},
    [SPECIES_RAIKOU          - 1] = {41, 12, 40, 39, 30},
    [SPECIES_ENTEI           - 1] = { 8,  9, 40, 11, 24},
    [SPECIES_SUICUNE         - 1] = {35, 29, 40, 38, 44},
    [SPECIES_LARVITAR        - 1] = {28, 24, 48, 26, 36},
    [SPECIES_PUPITAR         - 1] = {27, 25, 48, 27, 40},
    [SPECIES_TYRANITAR       - 1] = { 6, 11, 40, 13, 25},
    [SPECIES_LUGIA           - 1] = { 8, 42,  8, 20, 52},
    [SPECIES_HO_OH           - 1] = {13, 37,  8, 14, 52},
    [SPECIES_CELEBI          - 1] = {21, 33,  8, 26, 43},
    [SPECIES_OLD_UNOWN_B     - 1] = {31, 18,  8, 30, 28},
    [SPECIES_OLD_UNOWN_C     - 1] = {32, 23,  8, 31, 33},
    [SPECIES_OLD_UNOWN_D     - 1] = {28, 25,  8, 27, 35},
    [SPECIES_OLD_UNOWN_E     - 1] = {33, 25,  8, 32, 35},
    [SPECIES_OLD_UNOWN_F     - 1] = {27, 19,  8, 26, 29},
    [SPECIES_OLD_UNOWN_G     - 1] = {32, 22,  8, 31, 33},
    [SPECIES_OLD_UNOWN_H     - 1] = {32, 25,  8, 31, 35},
    [SPECIES_OLD_UNOWN_I     - 1] = {32, 25,  8, 31, 35},
    [SPECIES_OLD_UNOWN_J     - 1] = {32, 22,  8, 31, 32},
    [SPECIES_OLD_UNOWN_K     - 1] = {29, 26,  8, 28, 36},
    [SPECIES_OLD_UNOWN_L     - 1] = {32, 22,  8, 31, 31},
    [SPECIES_OLD_UNOWN_M     - 1] = {32, 28,  8, 31, 38},
    [SPECIES_OLD_UNOWN_N     - 1] = {32, 26,  8, 31, 35},
    [SPECIES_OLD_UNOWN_O     - 1] = {32, 26,  8, 31, 35},
    [SPECIES_OLD_UNOWN_P     - 1] = {32, 22,  8, 31, 32},
    [SPECIES_OLD_UNOWN_Q     - 1] = {29, 22,  8, 28, 32},
    [SPECIES_OLD_UNOWN_R     - 1] = {32, 21,  8, 31, 31},
    [SPECIES_OLD_UNOWN_S     - 1] = {32, 25,  8, 31, 35},
    [SPECIES_OLD_UNOWN_T     - 1] = {32, 30,  8, 31, 40},
    [SPECIES_OLD_UNOWN_U     - 1] = {32, 23,  8, 31, 33},
    [SPECIES_OLD_UNOWN_V     - 1] = {30, 30,  8, 29, 40},
    [SPECIES_OLD_UNOWN_W     - 1] = {32, 29,  8, 31, 39},
    [SPECIES_OLD_UNOWN_X     - 1] = {32, 25,  8, 31, 35},
    [SPECIES_OLD_UNOWN_Y     - 1] = {32, 21,  8, 31, 31},
    [SPECIES_OLD_UNOWN_Z     - 1] = {32, 25,  8, 31, 35},
    [SPECIES_TREECKO         - 1] = {26, 15, 48, 25, 32},
    [SPECIES_GROVYLE         - 1] = {13,  5, 16,  5, 19},
    [SPECIES_SCEPTILE        - 1] = {16,  4, 40, 12, 18},
    [SPECIES_TORCHIC         - 1] = {23, 24, 48, 21, 37},
    [SPECIES_COMBUSKEN       - 1] = {32, 18, 40, 30, 32},
    [SPECIES_BLAZIKEN        - 1] = {26,  7, 40, 29, 19},
    [SPECIES_MUDKIP          - 1] = {27, 29, 40, 25, 44},
    [SPECIES_MARSHTOMP       - 1] = {29, 17, 48, 28, 32},
    [SPECIES_SWAMPERT        - 1] = {27, 17, 40, 27, 35},
    [SPECIES_POOCHYENA       - 1] = {20, 18, 48, 15, 32},
    [SPECIES_MIGHTYENA       - 1] = { 9, 13, 40,  9, 28},
    [SPECIES_ZIGZAGOON       - 1] = {11, 26, 48,  9, 43},
    [SPECIES_LINOONE         - 1] = {13, 40, 24, 11, 55},
    [SPECIES_WURMPLE         - 1] = {33, 23, 48, 31, 38},
    [SPECIES_SILCOON         - 1] = {19, 28, 48, 17, 42},
    [SPECIES_BEAUTIFLY       - 1] = {15, 27,  8, 14, 40},
    [SPECIES_CASCOON         - 1] = {20, 29, 48, 17, 44},
    [SPECIES_DUSTOX          - 1] = {20, 25,  8, 22, 38},
    [SPECIES_LOTAD           - 1] = {25, 37, 40, 23, 50},
    [SPECIES_LOMBRE          - 1] = {34, 16, 48, 41, 29},
    [SPECIES_LUDICOLO        - 1] = {28, 15, 40, 27, 36},
    [SPECIES_SEEDOT          - 1] = {27, 23, 48, 24, 40},
    [SPECIES_NUZLEAF         - 1] = {32, 13, 48, 26, 29},
    [SPECIES_SHIFTRY         - 1] = {50, 17, 40, 46, 35},
    [SPECIES_NINCADA         - 1] = {24, 26, 48, 23, 40},
    [SPECIES_NINJASK         - 1] = {23, 33,  0, 23, 47},
    [SPECIES_SHEDINJA        - 1] = {22, 25,  8, 24, 42},
    [SPECIES_TAILLOW         - 1] = {23, 16, 48, 20, 30},
    [SPECIES_SWELLOW         - 1] = {12, 10, 40,  5, 22},
    [SPECIES_SHROOMISH       - 1] = {31, 22, 48, 29, 35},
    [SPECIES_BRELOOM         - 1] = {37, 12, 48, 35, 25},
    [SPECIES_SPINDA          - 1] = {33, 22, 48, 31, 39},
    [SPECIES_WINGULL         - 1] = {26, 22, 16, 21, 38},
    [SPECIES_PELIPPER        - 1] = {29, 10, 16,  9, 27},
    [SPECIES_SURSKIT         - 1] = {29, 22, 48, 28, 37},
    [SPECIES_MASQUERAIN      - 1] = {26, 33,  8, 20, 48},
    [SPECIES_WAILMER         - 1] = {23, 23, 48, 22, 40},
    [SPECIES_WAILORD         - 1] = {23,  3, 48,  9, 19},
    [SPECIES_SKITTY          - 1] = {36, 26, 48, 34, 42},
    [SPECIES_DELCATTY        - 1] = {30, 18, 48, 28, 33},
    [SPECIES_KECLEON         - 1] = {25, 16, 48, 19, 30},
    [SPECIES_BALTOY          - 1] = {29, 21, 48, 27, 34},
    [SPECIES_CLAYDOL         - 1] = {30, 13, 40, 29, 36},
    [SPECIES_NOSEPASS        - 1] = {31, 16, 48, 21, 35},
    [SPECIES_TORKOAL         - 1] = {14, 25, 40, 10, 39},
    [SPECIES_SABLEYE         - 1] = {30, 22, 48, 29, 39},
    [SPECIES_BARBOACH        - 1] = {23, 18, 48, 21, 30},
    [SPECIES_WHISCASH        - 1] = {24, 32, 40, 23, 49},
    [SPECIES_LUVDISC         - 1] = {25, 15, 48, 19, 28},
    [SPECIES_CORPHISH        - 1] = {31, 20, 48, 29, 35},
    [SPECIES_CRAWDAUNT       - 1] = {20, 12, 40, 24, 35},
    [SPECIES_FEEBAS          - 1] = {24, 30, 40, 22, 47},
    [SPECIES_MILOTIC         - 1] = {32, 12, 40, 31, 29},
    [SPECIES_CARVANHA        - 1] = {22, 25, 48, 19, 34},
    [SPECIES_SHARPEDO        - 1] = {25, 12, 40, 23, 39},
    [SPECIES_TRAPINCH        - 1] = {41, 19, 48, 23, 24},
    [SPECIES_VIBRAVA         - 1] = {16, 39, 32, 14, 52},
    [SPECIES_FLYGON          - 1] = {34,  7, 16, 33, 19},
    [SPECIES_MAKUHITA        - 1] = {34, 19, 48, 28, 35},
    [SPECIES_HARIYAMA        - 1] = {36, 15, 40, 38, 28},
    [SPECIES_ELECTRIKE       - 1] = {17, 24, 48, 20, 39},
    [SPECIES_MANECTRIC       - 1] = {47, 24, 40, 46, 41},
    [SPECIES_NUMEL           - 1] = {16, 26, 48, 13, 42},
    [SPECIES_CAMERUPT        - 1] = {13, 34, 40, 14, 54},
    [SPECIES_SPHEAL          - 1] = {30, 15, 48, 24, 31},
    [SPECIES_SEALEO          - 1] = {28,  9, 48, 26, 24},
    [SPECIES_WALREIN         - 1] = {25,  1, 40, 16, 22},
    [SPECIES_CACNEA          - 1] = {31, 23, 48, 29, 41},
    [SPECIES_CACTURNE        - 1] = {29, 14, 40, 29, 27},
    [SPECIES_SNORUNT         - 1] = {30, 22, 48, 30, 38},
    [SPECIES_GLALIE          - 1] = {26, 28,  8, 26, 49},
    [SPECIES_LUNATONE        - 1] = {28, 22,  8, 25, 44},
    [SPECIES_SOLROCK         - 1] = {24, 24, 16, 23, 49},
    [SPECIES_AZURILL         - 1] = {27, 16, 48, 24, 31},
    [SPECIES_SPOINK          - 1] = {33, 20, 48, 27, 40},
    [SPECIES_GRUMPIG         - 1] = {20, 16, 48, 21, 32},
    [SPECIES_PLUSLE          - 1] = {28, 22,  8, 29, 37},
    [SPECIES_MINUN           - 1] = {33, 22,  8, 31, 38},
    [SPECIES_MAWILE          - 1] = {45, 20, 48, 47, 36},
    [SPECIES_MEDITITE        - 1] = {31, 23, 48, 30, 37},
    [SPECIES_MEDICHAM        - 1] = {33, 15, 40, 30, 29},
    [SPECIES_SWABLU          - 1] = {27, 22, 16, 23, 35},
    [SPECIES_ALTARIA         - 1] = {29, 11, 16, 26, 26},
    [SPECIES_WYNAUT          - 1] = {26, 21, 48, 27, 38},
    [SPECIES_DUSKULL         - 1] = {16, 24,  8, 20, 46},
    [SPECIES_DUSCLOPS        - 1] = {28, 15, 48, 26, 40},
    [SPECIES_ROSELIA         - 1] = {30, 17, 48, 29, 32},
    [SPECIES_SLAKOTH         - 1] = {25, 30, 48, 24, 47},
    [SPECIES_VIGOROTH        - 1] = {16, 18, 40, 20, 36},
    [SPECIES_SLAKING         - 1] = {55, 15, 48, 41, 33},
    [SPECIES_GULPIN          - 1] = {27, 24, 48, 23, 38},
    [SPECIES_SWALOT          - 1] = {31,  6, 48, 21, 19},
    [SPECIES_TROPIUS         - 1] = {24, 10, 40, 32, 24},
    [SPECIES_WHISMUR         - 1] = {31, 25, 48, 29, 41},
    [SPECIES_LOUDRED         - 1] = {28, 18, 40, 34, 39},
    [SPECIES_EXPLOUD         - 1] = {16, 16, 40, 26, 42},
    [SPECIES_CLAMPERL        - 1] = {32, 26, 48, 30, 38},
    [SPECIES_HUNTAIL         - 1] = {19, 30, 40, 21, 51},
    [SPECIES_GOREBYSS        - 1] = {13, 31, 40,  3, 50},
    [SPECIES_ABSOL           - 1] = {42, 17, 40, 42, 34},
    [SPECIES_SHUPPET         - 1] = {22, 25,  8, 23, 39},
    [SPECIES_BANETTE         - 1] = {28, 20,  8, 27, 35},
    [SPECIES_SEVIPER         - 1] = {14, 13, 48, 11, 30},
    [SPECIES_ZANGOOSE        - 1] = {24, 12, 40, 21, 26},
    [SPECIES_RELICANTH       - 1] = {12, 31, 48,  9, 45},
    [SPECIES_ARON            - 1] = {24, 28, 48, 26, 44},
    [SPECIES_LAIRON          - 1] = {11, 33, 48, 18, 47},
    [SPECIES_AGGRON          - 1] = {16, 11, 40, 22, 27},
    [SPECIES_CASTFORM        - 1] = {29, 24,  8, 27, 38},
    [SPECIES_VOLBEAT         - 1] = {37, 21,  8, 33, 37},
    [SPECIES_ILLUMISE        - 1] = {32, 18,  8, 31, 32},
    [SPECIES_LILEEP          - 1] = {30, 17, 48, 31, 30},
    [SPECIES_CRADILY         - 1] = {18, 22, 40, 21, 40},
    [SPECIES_ANORITH         - 1] = {28, 30, 48, 27, 43},
    [SPECIES_ARMALDO         - 1] = {21,  5, 40, 20, 19},
    [SPECIES_RALTS           - 1] = {31, 23, 48, 32, 35},
    [SPECIES_KIRLIA          - 1] = {28, 18, 48, 31, 30},
    [SPECIES_GARDEVOIR       - 1] = {53,  7, 40, 50, 20},
    [SPECIES_BAGON           - 1] = {23, 19, 48, 22, 38},
    [SPECIES_SHELGON         - 1] = {25, 27, 48, 25, 44},
    [SPECIES_SALAMENCE       - 1] = { 9, 17, 48, 10, 33},
    [SPECIES_BELDUM          - 1] = {22, 25,  8, 24, 35},
    [SPECIES_METANG          - 1] = {34, 15, 16, 31, 33},
    [SPECIES_METAGROSS       - 1] = {36, 27, 40, 34, 43},
    [SPECIES_REGIROCK        - 1] = {22,  7, 40, 20, 18},
    [SPECIES_REGICE          - 1] = {25, 12, 40, 23, 25},
    [SPECIES_REGISTEEL       - 1] = {25, 13, 40, 25, 25},
    [SPECIES_KYOGRE          - 1] = {14, 25, 40, 11, 38},
    [SPECIES_GROUDON         - 1] = { 4, 11, 40, 10, 25},
    [SPECIES_RAYQUAZA        - 1] = {12, 14, 16, 14, 31},
    [SPECIES_LATIAS          - 1] = {30, 12, 16, 35, 25},
    [SPECIES_LATIOS          - 1] = { 5, 14, 16,  5, 29},
    [SPECIES_JIRACHI         - 1] = {28, 21,  8, 30, 34},
#if 1 // PokemonNative3G : Rouge Feu
    [SPECIES_DEOXYS          - 1] = {27,  8, 40, 28, 22},
#elif defined(LEAFGREEN)
    [SPECIES_DEOXYS          - 1] = {26,  9, 40, 26, 23},
#endif
    [SPECIES_CHIMECHO        - 1] = {29, 12,  8, 28, 26},
    [SPECIES_OLD_UNOWN_EMARK - 1] = {32, 33,  8, 32, 43},
    [SPECIES_OLD_UNOWN_QMARK - 1] = {32, 35,  8, 32, 45}
};

// Rouge Feu (wild_encounter.c)
static u8 GetUnownLetterByPersonalityLoByte(u32 personality)
{
    return GET_UNOWN_LETTER(personality);
}

static u8 Menu2_GetMonPosAttribute(u16 species, u32 personality, u8 attributeId)
{
    if (species == SPECIES_UNOWN)
    {
        u8 unownLetter = GetUnownLetterByPersonalityLoByte(personality);
        switch (unownLetter)
        {
        case 0:
            break;
        case 26:
            species = SPECIES_OLD_UNOWN_EMARK;
            break;
        case 27:
            species = SPECIES_OLD_UNOWN_QMARK;
            break;
        default:
            species = SPECIES_OLD_UNOWN_B + unownLetter - 1;
            break;
        }
    }
    if (species != SPECIES_NONE && species - 1 < ARRAY_COUNT(sMonPosAttributes) && attributeId < PSA_MON_ATTR_COUNT) // PokemonNative3G : espèces ajoutées hors table
    {
        species--;
        if (sMonPosAttributes[species][attributeId] != 0xFF)
            return sMonPosAttributes[species][attributeId];
    }
    return 32;
}

static s8 Menu2_GetStarSpritePosAttribute(u16 species, u32 personality, u8 attributeId)
{
    return Menu2_GetMonPosAttribute(species, personality, attributeId) - 32;
}

static void LoadBgGfxByAnimType(u16 animType);
static u8 Menu2_GetMonPosAttribute(u16 species, u32 personality, u8 attributeId);
static s8 Menu2_GetStarSpritePosAttribute(u16 species, u32 personality, u8 attributeId);
static void Task_ZoomAnim(u8 taskId);
static void SetSpriteWithCloseness(struct Sprite *sprite, u8 closeness);
static bool8 IsZoomSpriteCBActive(struct Sprite *sprite);
static void MonSpriteZoom_UpdateYPos(struct Sprite *sprite, u8 closeness);
static void ItemSpriteZoom_UpdateYPos(struct Sprite *sprite, u8 closeness);
static void StartMonWiggleAnim(struct PokemonSpecialAnimScene * scene, u8 frameLen, u8 niter, u8 amplitude);
static void StopMonWiggleAnim(struct PokemonSpecialAnimScene * scene);
static void SpriteCallback_MonSpriteWiggle(struct Sprite *sprite);
static void LoadMonSpriteGraphics(u16 *tilees, u16 *palette);
static struct Sprite *PSA_CreateItemIconObject(u16 itemId);
static u16 GetBlendColorByItemId(u16 itemId);
static void Task_ItemUseOnMonAnim(u8 taskId);
static void CreateSprites_UseItem_OutwardSpiralDots(u8 taskId, s16 *data, struct Sprite *sprite);
static void SpriteCB_OutwardSpiralDots(struct Sprite *sprite);
static void InitItemIconSpriteState(struct PokemonSpecialAnimScene * scene, struct Sprite *sprite, u8 closeness);
static void MachineSetWobbleInit(void);
static void MachineSetWobble_SetCB(struct Sprite *sprite);
static bool8 MachineSetWobbleCBIsRunning(void);
static void SpriteCB_MachineSetWobble(struct Sprite *sprite);
static void StartZoomOutAnimForUseTM(u8 closeness);
static void CreateStarSprites(struct PokemonSpecialAnimScene * scene);
static bool8 AnyStarSpritesActive(void);
static void SpriteCB_Star(struct Sprite *sprite);
static void PSAScene_SeedRandomInTask(struct PokemonSpecialAnimScene * scene);
static void StopMakingOutwardSpiralDots(void);
static void Task_UseItem_OutwardSpiralDots(u8 taskId);
static u16 PSAScene_RandomFromTask(u8 taskId);
static void SpriteCallback_UseItem_OutwardSpiralDots(struct Sprite *sprite);
static void LoadOutwardSpiralDotsGfx(void);
static bool32 IsOutwardSpiralDotsTaskRunning(void);
static void Task_LevelUpVerticalSprites(u8 taskId);
static void CreateLevelUpVerticalSprite(u8 taskId, s16 *data);
static void SpriteCB_LevelUpVertical(struct Sprite *sprite);

static const u16 sBg_Pal[] = INCGFX_U16("graphics/kanto/pokemon_special_anim/bg.pal", ".gbapal");
static const u16 sBg_TmHm_Pal[] = INCGFX_U16("graphics/kanto/pokemon_special_anim/bg_tm_hm.pal", ".gbapal");
static const u32 sBg_Gfx[] = INCGFX_U32("graphics/kanto/pokemon_special_anim/bg.png", ".4bpp.lz");
static const u32 sBg_Tilemap[] = INCGFX_U32("graphics/kanto/pokemon_special_anim/bg.bin", ".lz");
static const u16 sLevelUp_Pal[] = INCGFX_U16("graphics/kanto/pokemon_special_anim/level_up.png", ".gbapal");
static const u32 sLevelUp_Gfx[] = INCGFX_U32("graphics/kanto/pokemon_special_anim/level_up.png", ".4bpp.lz");
static const u16 sStar_Pal[] = INCGFX_U16("graphics/kanto/pokemon_special_anim/star.png", ".gbapal");
static const u32 sStar_Gfx[] = INCGFX_U32("graphics/kanto/pokemon_special_anim/star.png", ".4bpp.lz");
static const u16 sOutwardSpiralDots_Pal[] = INCGFX_U16("graphics/kanto/pokemon_special_anim/outward_spiral_dots.png", ".gbapal");
static const u32 sOutwardSpiralDots_Gfx[] = INCGFX_U32("graphics/kanto/pokemon_special_anim/outward_spiral_dots.png", ".4bpp.lz");

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x001
    }, {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x000
    }
};

static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x00a
    }, DUMMY_WIN_TEMPLATE
};

static const u8 *const s1_2_and_Poof_textPtrs[] = {
    sKText_Text_Counting_1,
    sKText_Text_Counting_2And,
    sKText_Text_Poof,
};

static const u16 sUnusedArray[] = {
    0, 16, 68
};

static const u16 sAffineScales[] = {
    0x100,
    0x155,
    0x1AA,
    0x200
};

static const s8 sStarCoordOffsets[][2] = {
    {-8,  -8},
    { 6, -13},
    { 8,  -8}
};

static const struct CompressedSpriteSheet sSpriteSheet_Star = {
    sStar_Gfx,
    0x80,
    2
};

static const struct SpritePalette sSpritePalette_Star = {
    sStar_Pal,
    2
};

static const struct CompressedSpriteSheet sSpriteSheet_UseItem_OutwardSpiralDots = {
    sOutwardSpiralDots_Gfx,
    0x60,
    5
};

static const struct SpritePalette sSpritePalette_UseItem_OutwardSpiralDots = {
    sOutwardSpiralDots_Pal,
    5
};

static const struct OamData sOamData_MonSprite = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0x000,
    .priority = 1,
    .paletteNum = 0
};


static const union AffineAnimCmd sAffineAnim_Zoom_0[] = {
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_Zoom_1[] = {
    AFFINEANIMCMD_FRAME(0x155, 0x155, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_Zoom_2[] = {
    AFFINEANIMCMD_FRAME(0x1AA, 0x1AA, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_Zoom_3[] = {
    AFFINEANIMCMD_FRAME(0x200, 0x200, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sAffineAnimTable_Zoom[] = {
    sAffineAnim_Zoom_0,
    sAffineAnim_Zoom_1,
    sAffineAnim_Zoom_2,
    sAffineAnim_Zoom_3
};

static const struct SpriteTemplate sSpriteTemplate_MonSprite = {
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_MonSprite,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = sAffineAnimTable_Zoom,
    .callback = SpriteCallbackDummy
};

static const union AffineAnimCmd sAffineAnim_ItemZoom_0[] = {
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME(-28, -28, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_ItemZoom_1[] = {
    AFFINEANIMCMD_FRAME(0x155, 0x155, 0, 0),
    AFFINEANIMCMD_FRAME(-37, -37, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_ItemZoom_2[] = {
    AFFINEANIMCMD_FRAME(0x1AA, 0x1AA, 0, 0),
    AFFINEANIMCMD_FRAME(-47, -47, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_ItemZoom_3[] = {
    AFFINEANIMCMD_FRAME(0x200, 0x200, 0, 0),
    AFFINEANIMCMD_FRAME(-56, -56, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sAffineAnimTable_ItemZoom[] = {
    sAffineAnim_ItemZoom_0,
    sAffineAnim_ItemZoom_1,
    sAffineAnim_ItemZoom_2,
    sAffineAnim_ItemZoom_3
};

static const struct OamData sOamData_LevelUpVertical = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_BLEND,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x16),
    .tileNum = 0x000,
    .priority = 1,
    .paletteNum = 0
};

static const union AnimCmd sAnim_LevelUpVertical[] = {
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_END
};

static const union AnimCmd *const sAnimTable_LevelUpVertical[] = {
    sAnim_LevelUpVertical
};

static const struct SpriteTemplate sSpriteTemplate_LevelUpVertical = {
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_LevelUpVertical,
    .anims = sAnimTable_LevelUpVertical,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_LevelUpVertical
};

static const struct OamData sOamData_Star = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0x000,
    .priority = 1,
    .paletteNum = 0
};

static const struct SpriteTemplate sSpriteTemplate_Star = {
    .tileTag = 2,
    .paletteTag = 2,
    .oam = &sOamData_Star,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Star
};

static const struct OamData sOamData_UseItem_OutwardSpiralDots = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0x000,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sAnim_UseItem_OutwardSpiralDots_0[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_FRAME(1,  8),
    ANIMCMD_FRAME(2,  4),
    ANIMCMD_END
};

static const union AnimCmd sAnim_UseItem_OutwardSpiralDots_1[] = {
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END
};

static const union AnimCmd *const sAnimTable_UseItem_OutwardSpiralDots[] = {
    sAnim_UseItem_OutwardSpiralDots_0,
    sAnim_UseItem_OutwardSpiralDots_1
};

static const struct SpriteTemplate sSpriteTemplate_UseItem_OutwardSpiralDots = {
    .tileTag = 5,
    .paletteTag = 5,
    .oam = &sOamData_UseItem_OutwardSpiralDots,
    .anims = sAnimTable_UseItem_OutwardSpiralDots,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallback_UseItem_OutwardSpiralDots
};

void InitPokemonSpecialAnimScene(struct PokemonSpecialAnimScene * buffer, u16 animType)
{
    FreeAllWindowBuffers();
    ResetTempTileDataBuffers();
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    ResetBgsAndClearDma3BusyFlags(FALSE);
    InitBgsFromTemplates(0, sBgTemplates, NELEMS(sBgTemplates));
    InitWindows(sWindowTemplates);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    SetBgTilemapBuffer(0, buffer->field_0914);
    SetBgTilemapBuffer(3, buffer->field_1914);
    RequestDma3Fill(0, (void *)BG_VRAM, 0x20, DMA3_32BIT);
    FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 0, 32, 32);
    LoadBgGfxByAnimType(animType);
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    LoadUserWindowGfx(0, 0x000, BG_PLTT_ID(14));
    CopyWindowToVram(0, COPYWIN_FULL);
    ShowBg(0);
    ShowBg(3);
    HideBg(1);
    HideBg(2);
    CopyBgTilemapBufferToVram(0);
    CopyBgTilemapBufferToVram(3);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

bool8 PokemonSpecialAnimSceneInitIsNotFinished(void)
{
    if (!FreeTempTileDataBuffersIfPossible())
        return IsDma3ManagerBusyWithBgCopy();
    else
        return TRUE;
}

void PSA_FreeWindowBuffers(void)
{
    FreeAllWindowBuffers();
}

void PSA_ShowMessageWindow(void)
{
    PutWindowTilemap(0);
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    DrawTextBorderOuter(0, 0x001, 14);
    CopyWindowToVram(0, COPYWIN_FULL);
}

void PSA_HideMessageWindow(void)
{
    ClearWindowTilemap(0);
    ClearStdWindowAndFrameToTransparent(0, FALSE);
    CopyWindowToVram(0, COPYWIN_MAP);
}

void PSA_PrintMessage(u8 messageId)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    u16 itemId = PSA_GetItemId();
    u16 strWidth = 0;
    u8 textSpeed = GetTextSpeedSetting();
    struct Pokemon * pokemon = PSA_GetPokemon();
    u16 level;
    u8 *str;

    switch (messageId)
    {
    case 0: // Item was used on Mon
        StringCopy(gStringVar2, ItemId_GetName(itemId));
        GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
        StringExpandPlaceholders(scene->textBuf, sKText_Text_WasUsedOn);
        break;
    case 1: // Mon's level was elevated to level
        level = GetMonData(pokemon, MON_DATA_LEVEL);
        GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
        if (level < MAX_LEVEL)
            level++;
        ConvertIntToDecimalStringN(gStringVar2, level, STR_CONV_MODE_LEFT_ALIGN, level < MAX_LEVEL ? 2 : 3);
        StringExpandPlaceholders(scene->textBuf, sKText_Text_LevelRoseTo);
        break;
    case 9: // Mon learned move
        DynamicPlaceholderTextUtil_Reset();
        DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, PSA_GetMonNickname());
        DynamicPlaceholderTextUtil_SetPlaceholderPtr(1, PSA_GetNameOfMoveToTeach());
        DynamicPlaceholderTextUtil_ExpandPlaceholders(scene->textBuf, sKText_Text_MonLearnedTMHM);
        break;
    case 4:
        strWidth += GetStringWidth(FONT_NORMAL, sKText_Text_Counting_2And, -1);
        // fallthrough
    case 3:
        strWidth += GetStringWidth(FONT_NORMAL, sKText_Text_Counting_1, -1);
        // fallthrough
    case 2: // 1
        StringCopy(scene->textBuf, s1_2_and_Poof_textPtrs[messageId - 2]);
        textSpeed = 1;
        break;
    case 5:
        DynamicPlaceholderTextUtil_Reset();
        DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, PSA_GetMonNickname());
        DynamicPlaceholderTextUtil_SetPlaceholderPtr(1, PSA_GetNameOfMoveForgotten());
        DynamicPlaceholderTextUtil_ExpandPlaceholders(scene->textBuf, sKText_Text_MonForgotMove);
        break;
    case 6:
        StringCopy(scene->textBuf, sKText_Text_And);
        break;
    case 7:
        StringCopy(scene->textBuf, sKText_Text_MachineSet);
        break;
    case 8:
        StringCopy(scene->textBuf, sKText_Text_Huh);
        break;
    default:
        return;
    }

    AddTextPrinterParameterized5(0, FONT_NORMAL, scene->textBuf, strWidth, 0, textSpeed, NULL, 0, 4);
}

void PSA_AfterPoof_ClearMessageWindow(void)
{
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    CopyWindowToVram(0, COPYWIN_GFX);
}

bool8 PSA_IsMessagePrintTaskActive(void)
{
    return IsTextPrinterActive(0);
}

void PSA_DarkenMonSprite(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    scene->state = 0;
    BlendPalettes((0x10000 << IndexOfSpritePaletteTag(0)) | 4, 16, RGB_BLACK);
    CreateStarSprites(scene);
}

bool8 PSA_RunPoofAnim(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();

    switch (scene->state)
    {
    case 0:
        if (!AnyStarSpritesActive())
        {
            BeginNormalPaletteFade((0x10000 << IndexOfSpritePaletteTag(0)) | 4, -1, 16, 0, RGB_BLACK);
            scene->state++;
        }
        break;
    case 1:
        if (!gPaletteFade.active)
            return FALSE;
        break;
    }
    return TRUE;
}

void PSA_UseTM_SetUpZoomOutAnim(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    scene->state = 0;
}

void PSA_UseTM_CleanUpForCancel(void)
{
    StopMakingOutwardSpiralDots();
    ResetPaletteFadeControl();
}

bool8 PSA_UseTM_RunZoomOutAnim(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    switch (scene->state)
    {
    case 0:
        StartZoomOutAnimForUseTM(0);
        scene->state++;
        break;
    case 1:
        if (!PSA_IsZoomTaskActive())
        {
            scene->field_0004 = 0;
            scene->state++;
        }
        break;
    case 2:
        scene->field_0004++;
        if (scene->field_0004 > 20)
            scene->state++;
        break;
    case 3:
        StartMonWiggleAnim(scene, 1, 0, 1);
        scene->field_0004 = 0;
        scene->state++;
        break;
    case 4:
        scene->field_0004++;
        if (scene->field_0004 > 0)
        {
            scene->field_0004 = 0;
            PlaySE(SE_M_MEGA_KICK);
            BeginNormalPaletteFade(0x00000001, 2, 0, 12, RGB(8, 13, 31));
            PSAScene_SeedRandomInTask(scene);
            scene->state++;
        }
        break;
    case 5:
        scene->field_0004++;
        if (scene->field_0004 > 70)
        {
            StopMonWiggleAnim(scene);
            BeginNormalPaletteFade(0x00000001, 6, 12, 0, RGB(8, 13, 31));
            scene->field_0004 = 0;
            scene->state++;
        }
        break;
    case 6:
        scene->field_0004++;
        if (!IsOutwardSpiralDotsTaskRunning() && scene->field_0004 > 40)
        {
            scene->field_0004 = 0;
            scene->state++;
        }
        break;
    case 7:
        scene->field_0004++;
        if (scene->field_0004 > 20)
        {
            scene->state++;
        }
        break;
    case 8:
        PlaySE(SE_EXP_MAX);
        DestroySprite(scene->itemIconSprite);
        scene->state++;
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

void PSA_UseTM_SetUpMachineSetWobble(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    scene->state = 0;
}

bool8 PSA_UseTM_RunMachineSetWobble(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();

    switch (scene->state)
    {
    case 0:
        MachineSetWobbleInit();
        PlaySE(SE_SWITCH);
        scene->state++;
        break;
    case 1:
        return MachineSetWobbleCBIsRunning();
    }
    return TRUE;
}

// There may once have been plans to put the battle level up
// anim in with using Rare Candy, but they were scrapped
// at a later stage of development

// Unused
void PSA_CreateLevelUpVerticalSpritesTask(void)
{
    CreateLevelUpVerticalSpritesTask(120, 56, 4, 4, 2, 0);
}

bool8 PSA_LevelUpVerticalSpritesTaskIsRunning(void)
{
    return LevelUpVerticalSpritesTaskIsRunning();
}

// Unused
void PSA_DrawLevelUpWindowPg1(u16 *statsBefore, u16 *statsAfter)
{
    DrawTextBorderOuter(1, 0x001, 14);
    KPSA_DrawLevelUpWindowPg1(1, statsBefore, statsAfter, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

// Unused
void PSA_DrawLevelUpWindowPg2(u16 *currStats)
{
    KPSA_DrawLevelUpWindowPg2(1, currStats, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY);
    CopyWindowToVram(1, COPYWIN_GFX);
}

// Unused
bool8 PSA_IsCopyingLevelUpWindowToVram(void)
{
    return IsDma3ManagerBusyWithBgCopy();
}

static void LoadBgGfxByAnimType(u16 animType)
{
    CopyToBgTilemapBuffer(3, sBg_Tilemap, 0, 0x000);
    DecompressAndCopyTileDataToVram(3, sBg_Gfx, 0, 0x000, 0);
    if (animType != PSA_ITEM_ANIM_TYPE_TMHM)
        LoadPalette(sBg_Pal, BG_PLTT_ID(0), sizeof(sBg_Pal));
    else
        LoadPalette(sBg_TmHm_Pal, BG_PLTT_ID(0), sizeof(sBg_TmHm_Pal));
}

void PSA_CreateMonSpriteAtCloseness(u8 closeness)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    struct Pokemon * pokemon = PSA_GetPokemon();
    u16 species = GetMonData(pokemon, MON_DATA_SPECIES);
    u32 personality = GetMonData(pokemon, MON_DATA_PERSONALITY);
    u8 yOffset = Menu2_GetMonPosAttribute(species, personality, PSA_MON_ATTR_Y_OFFSET);
    void *monPicBuffer;
    void *unusedBuffer;
    void *monPalBuffer;
    u8 spriteId;

    if (yOffset != 0xFF)
    {
        scene->monSpriteY1 = 72;
        scene->monSpriteY2 = yOffset + 48;
    }
    else
    {
        scene->monSpriteY1 = 72;
        scene->monSpriteY2 = 96;
    }

    monPicBuffer = Alloc(MON_PIC_SIZE * MAX_MON_PIC_FRAMES);
    unusedBuffer = Alloc(0x2000);
    monPalBuffer = Alloc(0x100);
    if (monPicBuffer != NULL && unusedBuffer != NULL && monPalBuffer != NULL)
    {
        HandleLoadSpecialPokePic(&gMonFrontPicTable[species], monPicBuffer, species, personality);
        LZ77UnCompWram(GetMonFrontSpritePal(pokemon), monPalBuffer);
        LoadMonSpriteGraphics(monPicBuffer, monPalBuffer);
        spriteId = CreateSprite(&sSpriteTemplate_MonSprite, 120, scene->monSpriteY1, 4);
        if (spriteId != MAX_SPRITES)
        {
            scene->monSprite = &gSprites[spriteId];
            MonSpriteZoom_UpdateYPos(scene->monSprite, closeness);
        }
        else
            scene->monSprite = NULL;
        scene->lastCloseness = closeness;
    }
    if (monPicBuffer != NULL) Free(monPicBuffer);
    if (unusedBuffer != NULL) Free(unusedBuffer);
    if (monPalBuffer != NULL) Free(monPalBuffer);
}

#define tState          data[0]
#define tCurrCloseness  data[1]
#define tFinalCloseness data[2]
#define tDeltaCloseness data[3]
#define tTimer          data[4]
#define tDelay          data[5]
#define tOff_MonSprite  6
#define tHasItemSprite  data[8]
#define tOff_ItemSprite 9

void PSA_SetUpZoomAnim(u8 closeness)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    u8 taskId;
    if (closeness != scene->lastCloseness)
    {
        taskId = CreateTask(Task_ZoomAnim, 4);
        SetWordTaskArg(taskId, tOff_MonSprite, (uintptr_t)scene->monSprite);
        gTasks[taskId].tCurrCloseness = scene->lastCloseness;
        gTasks[taskId].tFinalCloseness = closeness;
        gTasks[taskId].tDelay = 6;
        if (closeness > scene->lastCloseness)
            gTasks[taskId].tDeltaCloseness = 1;
        else
            gTasks[taskId].tDeltaCloseness = -1;
    }
}

bool8 PSA_IsZoomTaskActive(void)
{
    return FuncIsActiveTask(Task_ZoomAnim);
}

static void Task_ZoomAnim(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Sprite *sprite = (void *)GetWordTaskArg(taskId, tOff_MonSprite);
    switch (tState)
    {
    case 0:
        SetSpriteWithCloseness(sprite, tCurrCloseness);
        if (tHasItemSprite)
            SetSpriteWithCloseness((void *)GetWordTaskArg(taskId, tOff_ItemSprite), tCurrCloseness);
        tCurrCloseness += tDeltaCloseness;
        tState++;
        break;
    case 1:
        if (!IsZoomSpriteCBActive(sprite))
        {
            PlaySE(SE_BALL_TRAY_EXIT);
            MonSpriteZoom_UpdateYPos(sprite, tCurrCloseness);
            if (tHasItemSprite)
                ItemSpriteZoom_UpdateYPos((void *)GetWordTaskArg(taskId, tOff_ItemSprite), tCurrCloseness);
            if (tCurrCloseness == tFinalCloseness)
            {
                PSA_GetSceneWork()->lastCloseness = tFinalCloseness;
                DestroyTask(taskId);
            }
            else
            {
                tTimer = 0;
                tState = 2;
            }
        }
        break;
    case 2:
        tTimer++;
        if (tTimer > tDelay)
            tState = 0;
        break;
    }
}

static void SetSpriteWithCloseness(struct Sprite *sprite, u8 closeness)
{
    sprite->data[0] = 0;
    sprite->data[1] = 0;
    sprite->data[2] = closeness;
}

static bool8 IsZoomSpriteCBActive(struct Sprite *sprite)
{
    return sprite->callback != SpriteCallbackDummy;
}

static s16 GetSpriteOffsetByScale(s16 pos, u8 closeness)
{
    return (pos * sAffineScales[closeness]) >> 8;
}

// FIXME: better math
static u16 GetYPosByScale(u16 pos)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    s32 v = ((((((scene->monSpriteY2 - scene->monSpriteY1) << 16) >> 8) / 256 * (pos - 256)) << 8) >> 16);
    return v += scene->monSpriteY1;
}

static void MonSpriteZoom_UpdateYPos(struct Sprite *sprite, u8 closeness)
{
    if (closeness > 3)
        closeness = 3;
    PSA_GetSceneWork(); // return value not used
    StartSpriteAffineAnim(sprite, closeness);
    sprite->y = GetYPosByScale(sAffineScales[closeness]);
}

static void ItemSpriteZoom_UpdateYPos(struct Sprite *sprite, u8 closeness)
{
    MonSpriteZoom_UpdateYPos(sprite, closeness);
    sprite->x2 = GetSpriteOffsetByScale(sprite->data[6] - 32, closeness);
    sprite->y2 = GetSpriteOffsetByScale(sprite->data[7] - 32, closeness);
}

static void StartMonWiggleAnim(struct PokemonSpecialAnimScene * scene, u8 frameLen, u8 niter, u8 amplitude)
{
    // frameLen: frame duration
    // niter = 0: iterate ad infinitum
    scene->monSprite->data[0] = frameLen;
    scene->monSprite->data[1] = niter;
    scene->monSprite->data[2] = amplitude;
    scene->monSprite->callback = SpriteCallback_MonSpriteWiggle;
}

static void StopMonWiggleAnim(struct PokemonSpecialAnimScene * scene)
{
    scene->monSprite->x2 = 0;
    scene->monSprite->callback = SpriteCallbackDummy;
}

static void SpriteCallback_MonSpriteWiggle(struct Sprite *sprite)
{
    sprite->data[7]++;
    if (sprite->data[7] > sprite->data[0])
    {
        sprite->data[7] = 0;
        sprite->data[6]++;
        if (sprite->data[1] != 0 && sprite->data[6] >= sprite->data[1])
        {
            sprite->x2 = 0;
            sprite->callback = SpriteCallbackDummy;
        }
        else if (sprite->data[6] & 1)
            sprite->x2 = sprite->data[2];
        else
            sprite->x2 = -sprite->data[2];
    }
}

static void LoadMonSpriteGraphics(u16 *tiles, u16 *palette)
{
    struct SpriteSheet spriteSheet;
    struct SpritePalette spritePalette;

    spriteSheet.data = tiles;
    spriteSheet.size = MON_PIC_SIZE;
    spriteSheet.tag = 0;
    spritePalette.data = palette;
    spritePalette.tag = 0;
    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
}

#undef tOff_ItemSprite
#undef tHasItemSprite
#undef tOff_MonSprite
#undef tDelay
#undef tTimer
#undef tDeltaCloseness
#undef tFinalCloseness
#undef tCurrCloseness
#undef tState

#define tState           data[0]
#define tTimer           data[1]
#define tCloseness       data[2]
#define tYpos            data[3]
#define tOff_ItemSprite  4
#define tData6           data[6]
#define tData7           data[7]
#define tActiveSprCt     data[8]
#define tBlendColor      data[9]
#define tTimerReset      data[10]
#define tSuppressDots    data[11]

void PSA_SetUpItemUseOnMonAnim(u16 itemId, u8 closeness, bool32 a2)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    u8 taskId;
    scene->itemIconSprite = PSA_CreateItemIconObject(itemId);
    if (scene->itemIconSprite != NULL)
    {
        InitItemIconSpriteState(scene, scene->itemIconSprite, closeness);
        StartSpriteAffineAnim(scene->itemIconSprite, closeness);
        scene->itemIconSprite->invisible = TRUE;
        taskId = CreateTask(Task_ItemUseOnMonAnim, 2);
        SetWordTaskArg(taskId, tOff_ItemSprite, (uintptr_t)scene->itemIconSprite);
        gTasks[taskId].tCloseness = closeness;
        gTasks[taskId].tYpos = GetYPosByScale(sAffineScales[closeness]);
        gTasks[taskId].tData6 = a2;
        gTasks[taskId].tBlendColor = GetBlendColorByItemId(itemId);
    }
}

static u16 GetBlendColorByItemId(u16 itemId)
{
    return RGB_WHITE;
}

void CreateItemIconSpriteAtMaxCloseness(u16 itemId)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    scene->itemIconSprite = PSA_CreateItemIconObject(itemId);
    if (scene->itemIconSprite != NULL)
    {
        StartSpriteAffineAnim(scene->itemIconSprite, 3);
        InitItemIconSpriteState(scene, scene->itemIconSprite, 3);
    }
}

static struct Sprite *PSA_CreateItemIconObject(u16 itemId)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = AddItemIconObject(1, 1, itemId);
    if (spriteId == MAX_SPRITES)
        return NULL;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_DOUBLE;
    gSprites[spriteId].oam.priority = 1;
    gSprites[spriteId].subpriority = 1;
    gSprites[spriteId].affineAnims = sAffineAnimTable_Zoom;
    gSprites[spriteId].callback = SpriteCallbackDummy;
    InitSpriteAffineAnim(&gSprites[spriteId]);
    return &gSprites[spriteId];
}

bool8 PSA_IsItemUseOnMonAnimActive(void)
{
    return FuncIsActiveTask(Task_ItemUseOnMonAnim);
}

static void Task_ItemUseOnMonAnim(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Sprite *sprite = (void *)GetWordTaskArg(taskId, tOff_ItemSprite);
    switch (tState)
    {
    case 0:
        tTimer++;
        if (tTimer > 20)
        {
            tTimer = 0;
            PlaySE(SE_M_SWAGGER2);
            sprite->invisible = FALSE;
            if (!tSuppressDots)
                LoadOutwardSpiralDotsGfx();
            tState = 1;
        }
        break;
    case 1:
        tTimer++;
        if (tTimer > 30)
        {
            tTimer = 0;
            sprite->affineAnims = sAffineAnimTable_ItemZoom;
            StartSpriteAffineAnim(sprite, tCloseness);
            BeginNormalPaletteFade(0x10000 << IndexOfSpritePaletteTag(1), -2, 0, 12, tBlendColor);
            tState = 2;
            PlaySE(SE_M_MILK_DRINK);
        }
        break;
    case 2:
        if (sprite->affineAnimEnded)
        {
            sprite->invisible = TRUE;
            tTimerReset = 20;
            tState = 3;
        }
        break;
    case 3:
        tTimer++;
        if (tTimer > tTimerReset)
        {
            tTimer = 0;
            if (!tSuppressDots)
                CreateSprites_UseItem_OutwardSpiralDots(taskId, data, sprite);
            if (tData7 == 0)
                PlaySE(SE_M_REVERSAL);
            tData7++;
            if (tData7 > 2)
                tState = 4;
            else
                tTimerReset = 8;
        }
        break;
    case 4:
        if (tActiveSprCt == 0)
        {
            if (tData6)
                DestroySprite(sprite);
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateSprites_UseItem_OutwardSpiralDots(u8 taskId, s16 *data, struct Sprite *sprite)
{
    int x = sprite->x + sprite->x2 - 4;
    int y = sprite->y + sprite->y2 - 4;
    u8 spriteId;
    int i;
    BlendPalettes(0x10000 << IndexOfSpritePaletteTag(5), 16, tBlendColor);
    for (i = 0; i < 15; i++)
    {
        spriteId = CreateSprite(&sSpriteTemplate_UseItem_OutwardSpiralDots, x, y, 0);
        if (spriteId != MAX_SPRITES)
        {
            gSprites[spriteId].data[1] = i << 4;
            gSprites[spriteId].data[7] = taskId;
            gSprites[spriteId].callback = SpriteCB_OutwardSpiralDots;
            StartSpriteAnim(&gSprites[spriteId], 1);
            tActiveSprCt++;
        }
    }
}

static void SpriteCB_OutwardSpiralDots(struct Sprite *sprite)
{
    s16 *data = sprite->data;
    if (data[0] < 16)
    {
        data[0]++;
        data[1] += 7;
        data[1] &= 0xFF;
        data[2] += 4;
        sprite->x2 = (data[2] * gSineTable[data[1] + 0x40]) >> 8;
        sprite->y2 = (data[2] * gSineTable[data[1]])        >> 8;
    }
    else
    {
        gTasks[data[7]].tActiveSprCt--;
        DestroySprite(sprite);
    }
}

void PSA_UseItem_CleanUpForCancel(void)
{
    u8 taskId = FindTaskIdByFunc(Task_ItemUseOnMonAnim);
    if (taskId != 0xFF)
    {
        gTasks[taskId].tSuppressDots = TRUE;
    }
}

static void InitItemIconSpriteState(struct PokemonSpecialAnimScene * scene, struct Sprite *sprite, u8 closeness)
{
    u16 species, x, y;
    u32 personality;
    if (closeness == 3)
    {
        sprite->x = 120;
        sprite->y = scene->monSpriteY2;
    }
    else
    {
        sprite->x = 120;
        sprite->y = scene->monSpriteY1;
    }
    sprite->x += 4;
    sprite->y += 4;
    species = PSA_GetMonSpecies();
    personality = PSA_GetMonPersonality();
    switch (PSA_GetAnimType())
    {
        case PSA_ITEM_ANIM_TYPE_TMHM:
        {
            x = Menu2_GetMonPosAttribute(species, personality, PSA_MON_ATTR_TMHM_X_POS);
            y = Menu2_GetMonPosAttribute(species, personality, PSA_MON_ATTR_TMHM_Y_POS);
            if (x == 0xFF)
                x = 0;
            if (y == 0xFF)
                y = 0;
            sprite->data[6] = x;
            sprite->data[7] = y;
            break;
        }
        default:
        {
            x = Menu2_GetMonPosAttribute(species, personality, PSA_MON_ATTR_ITEM_X_POS);
            y = Menu2_GetMonPosAttribute(species, personality, PSA_MON_ATTR_ITEM_Y_POS);
            if (x == 0xFF)
                x = 0;
            if (y == 0xFF)
                y = 0;
            sprite->data[6] = x;
            sprite->data[7] = y;
            break;
        }
    }
    ItemSpriteZoom_UpdateYPos(sprite, closeness);
}

#undef tSuppressDots
#undef tTimerReset
#undef tBlendColor
#undef tActiveSprCt
#undef tData7
#undef tData6
#undef tOff_ItemSprite
#undef tYpos
#undef tCloseness
#undef tTimer
#undef tState

static void MachineSetWobbleInit(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    MachineSetWobble_SetCB(scene->monSprite);
    MachineSetWobble_SetCB(scene->itemIconSprite);
}

static void MachineSetWobble_SetCB(struct Sprite *sprite)
{
    sprite->data[0] = 0;
    sprite->data[1] = 0;
    sprite->callback = SpriteCB_MachineSetWobble;
}

static bool8 MachineSetWobbleCBIsRunning(void)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    return scene->monSprite->callback != SpriteCallbackDummy;
}

static void SpriteCB_MachineSetWobble(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->x += 3;
        sprite->data[0]++;
        break;
    case 1:
        sprite->data[1]++;
        if (sprite->data[1] > 30)
        {
            sprite->x -= 3;
            sprite->callback = SpriteCallbackDummy;
        }
        break;
    }
}

// Redefined from above
#define tState          data[0]
#define tCurrCloseness  data[1]
#define tFinalCloseness data[2]
#define tDeltaCloseness data[3]
#define tTimer          data[4]
#define tDelay          data[5]
#define tOff_MonSprite  6
#define tHasItemSprite  data[8]
#define tOff_ItemSprite 9

static void StartZoomOutAnimForUseTM(u8 closeness)
{
    struct PokemonSpecialAnimScene * scene = PSA_GetSceneWork();
    u8 taskId;
    if (closeness != scene->lastCloseness)
    {
        taskId = CreateTask(Task_ZoomAnim, 1);
        SetWordTaskArg(taskId, tOff_MonSprite, (uintptr_t)scene->monSprite);
        SetWordTaskArg(taskId, tOff_ItemSprite, (uintptr_t)scene->itemIconSprite);
        gTasks[taskId].tCurrCloseness = scene->lastCloseness;
        gTasks[taskId].tFinalCloseness = closeness;
        gTasks[taskId].tHasItemSprite = 1;
        gTasks[taskId].tDelay = 6;
        if (closeness > scene->lastCloseness)
            gTasks[taskId].tDeltaCloseness = 1;
        else
            gTasks[taskId].tDeltaCloseness = -1;
    }
}

#undef tOff_ItemSprite
#undef tHasItemSprite
#undef tOff_MonSprite
#undef tDelay
#undef tTimer
#undef tDeltaCloseness
#undef tFinalCloseness
#undef tCurrCloseness
#undef tState

static void CreateStarSprites(struct PokemonSpecialAnimScene * scene)
{
    int i;
    u8 spriteId;
    u16 species;
    u32 personality;
    LoadCompressedSpriteSheet(&sSpriteSheet_Star);
    LoadSpritePalette(&sSpritePalette_Star);
    scene->field_0002 = 0;
    for (i = 0; i < 3; i++)
    {
        spriteId = CreateSprite(&sSpriteTemplate_Star, 120 + sStarCoordOffsets[i][0],  scene->monSpriteY2 + sStarCoordOffsets[i][1], 2);
        if (spriteId != MAX_SPRITES)
        {
            species = PSA_GetMonSpecies();
            personality = PSA_GetMonPersonality();
            gSprites[spriteId].data[3] = sStarCoordOffsets[i][0] * 8;
            gSprites[spriteId].data[4] = sStarCoordOffsets[i][1] * 8;
            gSprites[spriteId].x += GetSpriteOffsetByScale(Menu2_GetStarSpritePosAttribute(species, personality, PSA_MON_ATTR_TMHM_X_POS), 3);
            gSprites[spriteId].y += GetSpriteOffsetByScale(Menu2_GetStarSpritePosAttribute(species, personality, PSA_MON_ATTR_TMHM_Y_POS), 3);
            scene->field_0002++;
        }
    }
}

static u8 AnyStarSpritesActive(void)
{
    return PSA_GetSceneWork()->field_0002;
}

static void SpriteCB_Star(struct Sprite *sprite)
{
    sprite->data[0]++;
    if (sprite->data[0] < 10)
    {
        sprite->data[1] += sprite->data[3];
        sprite->data[2] += sprite->data[4];
        sprite->x2 = sprite->data[1] >> 4;
        sprite->y2 = sprite->data[2] >> 4;
    }
    else
    {
        PSA_GetSceneWork()->field_0002--;
        DestroySprite(sprite);
    }
}

// ========================================================

#define tState        data[0]
#define tTimer        data[1]
#define tActiveSprCt  data[2]
#define tOff_RngState 3
#define tAngle        data[5]
#define tMadeSprCt    data[6]

#define tsRadius   data[0]
#define tsSpeed    data[1]
#define tsXinit    data[2]
#define tsYinit    data[3]
#define tsXorig    data[4]
#define tsYorig    data[5]
#define tsTaskId   data[6]

static void PSAScene_SeedRandomInTask(struct PokemonSpecialAnimScene * scene)
{
    u8 taskId;
    LoadOutwardSpiralDotsGfx();
    taskId = CreateTask(Task_UseItem_OutwardSpiralDots, 1);
    SetWordTaskArg(taskId, tOff_RngState, 2022069025);
    gTasks[taskId].tAngle = 0xE0;
}

static void StopMakingOutwardSpiralDots(void)
{
    u8 taskId = FindTaskIdByFunc(Task_UseItem_OutwardSpiralDots);
    if (taskId != 0xFF)
        gTasks[taskId].tState = 1;
}

static void Task_UseItem_OutwardSpiralDots(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (tTimer == 0)
        {
            u32 spriteId, x, y, x2, y2, ampl;
            struct Sprite *sprite = PSA_GetSceneWork()->itemIconSprite;
            x = sprite->x + sprite->x2;
            y = sprite->y + sprite->y2;
            ampl = (PSAScene_RandomFromTask(taskId) % 21) + 70;
            x2 = x + ((u32)(gSineTable[tAngle + 0x40] * ampl) >> 8);
            y2 = y + ((u32)(gSineTable[tAngle       ] * ampl) >> 8);
            tAngle += 0x4C;
            tAngle &= 0xFF;
            spriteId = CreateSprite(&sSpriteTemplate_UseItem_OutwardSpiralDots, x2, y2, 0);
            if (spriteId != MAX_SPRITES)
            {
                gSprites[spriteId].tsRadius = 0;
                gSprites[spriteId].tsSpeed = (PSAScene_RandomFromTask(taskId) & 1) + 6;
                gSprites[spriteId].tsXinit = x2;
                gSprites[spriteId].tsYinit = y2;
                gSprites[spriteId].tsXorig = x;
                gSprites[spriteId].tsYorig = y;
                gSprites[spriteId].tsTaskId = taskId;
                tActiveSprCt++;
            }
            tMadeSprCt++;
            if (tMadeSprCt > 47)
                tState++;
        }
        else
            tTimer--;
        break;
    case 1:
        if (tActiveSprCt == 0)
            DestroyTask(taskId);
        break;
    }
}

static u16 PSAScene_RandomFromTask(u8 taskId)
{
    u32 state = GetWordTaskArg(taskId, tOff_RngState);
    state = ISO_RANDOMIZE1(state);
    SetWordTaskArg(taskId, tOff_RngState, state);
    return state >> 16;
}

static void SpriteCallback_UseItem_OutwardSpiralDots(struct Sprite *sprite)
{
    int x;
    int y;
    sprite->tsRadius += sprite->tsSpeed;
    if (sprite->tsRadius > 255)
    {
        gTasks[sprite->tsTaskId].tActiveSprCt--;
        DestroySprite(sprite);
    }
    else
    {
        x = (sprite->tsXorig - sprite->tsXinit) * sprite->tsRadius;
        y = (sprite->tsYorig - sprite->tsYinit) * sprite->tsRadius;
        sprite->x = (x >> 8) + sprite->tsXinit;
        sprite->y = (y >> 8) + sprite->tsYinit;
    }
}

static void LoadOutwardSpiralDotsGfx(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_UseItem_OutwardSpiralDots);
    LoadSpritePalette(&sSpritePalette_UseItem_OutwardSpiralDots);
}

static bool32 IsOutwardSpiralDotsTaskRunning(void)
{
    return FuncIsActiveTask(Task_UseItem_OutwardSpiralDots);
}

#undef tsTaskId
#undef tsYorig
#undef tsXorig
#undef tsYinit
#undef tsXinit
#undef tsSpeed
#undef tsRadius

#undef tMadeSprCt
#undef tAngle
#undef tOff_RngState
#undef tActiveSprCt
#undef tTimer
#undef tState

// ========================================================

#define tState       data[0]
#define tActiveSprCt data[1]
#define tMadeSprCt   data[2]
#define tTimer       data[3]
#define tXpos        data[4]
#define tYpos        data[5]
#define tTileTag     data[6]
#define tPaletteTag  data[7]
#define tPriority    data[8]
#define tSubpriority data[9]

#define tsYsubpixel data[1]
#define tsSpeed     data[2]
#define tsTaskId    data[7]

void CreateLevelUpVerticalSpritesTask(u16 x, u16 y, u16 tileTag, u16 paletteTag, u16 priority, u16 subpriority)
{
    static struct CompressedSpriteSheet spriteSheet;
    static struct SpritePalette spritePalette;
    u8 taskId;
    spriteSheet.tag = tileTag;
    spriteSheet.data = sLevelUp_Gfx;
    spriteSheet.size = sLevelUp_Gfx[0] >> 8;
    spritePalette.data = sLevelUp_Pal;
    spritePalette.tag = paletteTag;
    LoadCompressedSpriteSheet(&spriteSheet);
    LoadSpritePalette(&spritePalette);
    taskId = CreateTask(Task_LevelUpVerticalSprites, 0);
    gTasks[taskId].tXpos = x - 32;
    gTasks[taskId].tYpos = y + 32;
    gTasks[taskId].tTileTag = tileTag;
    gTasks[taskId].tPaletteTag = paletteTag;
    gTasks[taskId].tPriority = priority;
    gTasks[taskId].tSubpriority = subpriority;
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_NONE  | BLDCNT_TGT2_ALL);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(12, 6));
}

bool8 LevelUpVerticalSpritesTaskIsRunning(void)
{
    return FuncIsActiveTask(Task_LevelUpVerticalSprites);
}

static void Task_LevelUpVerticalSprites(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (tState)
    {
    case 0:
        if (tTimer == 0)
        {
            tTimer++;
            CreateLevelUpVerticalSprite(taskId, data);
            if (tMadeSprCt > 17)
                tState++;
        }
        else
        {
            tTimer++;
            if (tTimer == 2)
                tTimer = 0;
        }
        break;
    case 1:
        if (tActiveSprCt == 0)
        {
            FreeSpriteTilesByTag(tTileTag);
            FreeSpritePaletteByTag(tPaletteTag);
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateLevelUpVerticalSprite(u8 taskId, s16 *data)
{
    u8 spriteId;
    struct SpriteTemplate template = sSpriteTemplate_LevelUpVertical;
    template.tileTag = tTileTag;
    template.paletteTag = tPaletteTag;
    tMadeSprCt++;
    spriteId = CreateSprite(&template, ((tMadeSprCt * 219) & 0x3F) + tXpos, tYpos, tSubpriority);
    if (spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].oam.priority = tPriority;
        gSprites[spriteId].tsYsubpixel = 0;
        gSprites[spriteId].tsSpeed = (ISO_RANDOMIZE1(tMadeSprCt) & 0x3F) + 0x20;
        gSprites[spriteId].tsTaskId = taskId;
        tActiveSprCt++;
    }
}

static void SpriteCB_LevelUpVertical(struct Sprite *sprite)
{
    sprite->tsYsubpixel -= sprite->tsSpeed;
    sprite->y2 = sprite->tsYsubpixel >> 4;
    if (sprite->y2 < -0x40)
    {
        gTasks[sprite->tsTaskId].tActiveSprCt--;
        DestroySprite(sprite);
    }
}

#undef tsTaskId
#undef tsSpeed
#undef tsYsubpixel

#undef tSubpriority
#undef tPriority
#undef tPaletteTag
#undef tTileTag
#undef tYpos
#undef tXpos
#undef tTimer
#undef tMadeSprCt
#undef tActiveSprCt
#undef tState

// ========================================================

static const u8 *const sLevelUpWindowStatNames[] = {
    sKText_Text_LevelUp_MaxHP,
    sKText_Text_LevelUp_Attack,
    sKText_Text_LevelUp_Defense,
    sKText_Text_LevelUp_SpAtk,
    sKText_Text_LevelUp_SpDef,
    sKText_Text_LevelUp_Speed
};

void KPSA_DrawLevelUpWindowPg1(u16 windowId, u16 *beforeStats, u16 *afterStats, u8 bgColor, u8 fgColor, u8 shadowColor)
{
    s16 diffStats[6];
    u8 textbuf[12];
    u8 textColor[3];
    u16 i;
    u8 x;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(bgColor));

    diffStats[0] = afterStats[0] - beforeStats[0];
    diffStats[1] = afterStats[1] - beforeStats[1];
    diffStats[2] = afterStats[2] - beforeStats[2];
    diffStats[3] = afterStats[4] - beforeStats[4];
    diffStats[4] = afterStats[5] - beforeStats[5];
    diffStats[5] = afterStats[3] - beforeStats[3];

    textColor[0] = bgColor;
    textColor[1] = fgColor;
    textColor[2] = shadowColor;

    for (i = 0; i < 6; i++)
    {
        AddTextPrinterParameterized3(windowId, FONT_NORMAL, 0, i * 15, textColor, TEXT_SKIP_DRAW, sLevelUpWindowStatNames[i]);
        StringCopy(textbuf, diffStats[i] >= 0 ? sKText_Text_LevelUp_Plus : sKText_Text_LevelUp_Minus);
        AddTextPrinterParameterized3(windowId, FONT_NORMAL, 56, i * 15, textColor, TEXT_SKIP_DRAW, textbuf);
        textbuf[0] = CHAR_SPACE;
        x = abs(diffStats[i]) < 10 ? 12 : 6;
        ConvertIntToDecimalStringN(textbuf + 1, abs(diffStats[i]), STR_CONV_MODE_LEFT_ALIGN, 2);
        AddTextPrinterParameterized3(windowId, FONT_NORMAL, x + 56, i * 15, textColor, TEXT_SKIP_DRAW, textbuf);
    }
}

void KPSA_DrawLevelUpWindowPg2(u16 windowId, u16 *currStats, u8 bgColor, u8 fgColor, u8 shadowColor)
{
    s16 statsRearrange[6];
    u8 textbuf[12];
    u8 textColor[3];
    u16 i;
    u8 ndigits;
    u16 x;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(bgColor));

    statsRearrange[0] = currStats[0];
    statsRearrange[1] = currStats[1];
    statsRearrange[2] = currStats[2];
    statsRearrange[3] = currStats[4];
    statsRearrange[4] = currStats[5];
    statsRearrange[5] = currStats[3];

    textColor[0] = bgColor;
    textColor[1] = fgColor;
    textColor[2] = shadowColor;

    for (i = 0; i < 6; i++)
    {
        if (statsRearrange[i] >= 100)
            ndigits = 3;
        else if (statsRearrange[i] >= 10)
            ndigits = 2;
        else
            ndigits = 1;
        ConvertIntToDecimalStringN(textbuf, statsRearrange[i], STR_CONV_MODE_LEFT_ALIGN, ndigits);
        x = 6 * (4 - ndigits);
        AddTextPrinterParameterized3(windowId, FONT_NORMAL, 0, i * 15, textColor, TEXT_SKIP_DRAW, sLevelUpWindowStatNames[i]);
        AddTextPrinterParameterized3(windowId, FONT_NORMAL, 56 + x, i * 15, textColor, TEXT_SKIP_DRAW, textbuf);
    }
}
