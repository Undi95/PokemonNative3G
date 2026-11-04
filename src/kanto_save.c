#include "global.h"
#include "kanto_save.h"
#include "constants/kanto/trainer_tower.h"
#include "constants/kanto_flags_vars.h"
#include "platform.h"
#include "save.h"
#include "string_util.h"

#define KANTO_SAVE_MAGIC 0x4B414E54 // "KANT"

// Nom du rival de Kanto en attendant la scène de RF où on le choisit (oak_speech.c)
static const u8 sText_KantoRivalDefaultName[] = _("BLUE");

EWRAM_DATA struct SaveBlockKanto gSaveBlockKanto = {0};

static u32 KantoSave_Checksum(void)
{
    const u8 *p = (const u8 *)&gSaveBlockKanto;
    u32 sum = 0x811C9DC5, i;
    for (i = 0; i < offsetof(struct SaveBlockKanto, checksum); i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}

void KantoSave_Clear(void)
{
    memset(&gSaveBlockKanto, 0, sizeof(gSaveBlockKanto));
    StringCopy(gSaveBlockKanto.rivalName, sText_KantoRivalDefaultName);
}

// Temps record de la Tour des Dresseurs (chiffrés avec la clé de SaveBlock2, cf. load_save.c) : une sauvegarde
// d'avant leur import n'a que des zéros, que RF n'a jamais (ResetTrainerTowerResults à la nouvelle partie)
static void KantoSave_InitTrainerTowerTimes(void)
{
    s32 i;

    for (i = 0; i < NUM_TOWER_CHALLENGE_TYPES; i++)
    {
        if (gSaveBlockKanto.trainerTower[i].bestTime == 0 && gSaveBlockKanto.trainerTower[i].unk9 == 0)
            gSaveBlockKanto.trainerTower[i].bestTime = TRAINER_TOWER_MAX_TIME ^ gSaveBlock2Ptr->encryptionKey;
    }
}

// Records de taille de SCARHINO et MAGICARPE : RF les met à 0 à la nouvelle partie ; jusqu'au 2026-11-04, la fusion y
// mettait 0x8000 (la valeur d'Émeraude : un record de 90 cm pour MAGICARPE). Un vrai record de 0x8000 tout juste est
// une chance sur 65 536 : pris pour l'ancienne valeur par défaut
static void KantoSave_FixSizeRecords(void)
{
    u16 *heracross = &gSaveBlockKanto.vars[VAR_KANTO_HERACROSS_SIZE_RECORD - KANTO_VARS_START];
    u16 *magikarp = &gSaveBlockKanto.vars[VAR_KANTO_MAGIKARP_SIZE_RECORD - KANTO_VARS_START];

    if (*heracross == 0x8000)
        *heracross = 0;
    if (*magikarp == 0x8000)
        *magikarp = 0;
}

void KantoSave_Write(void)
{
#ifdef PORTABLE
    gSaveBlockKanto.magic = KANTO_SAVE_MAGIC;
    gSaveBlockKanto.saveCounter = gSaveCounter;
    gSaveBlockKanto.checksum = KantoSave_Checksum();
    Platform_WriteExtraSave(&gSaveBlockKanto, sizeof(gSaveBlockKanto));
#endif
}

void KantoSave_Read(void)
{
#ifdef PORTABLE
    // Une sauvegarde sans bloc Kanto (ancienne, ou partie jamais allée à Kanto) le laisse vide.
    if (!Platform_ReadExtraSave(&gSaveBlockKanto, sizeof(gSaveBlockKanto))
     || gSaveBlockKanto.magic != KANTO_SAVE_MAGIC
     || gSaveBlockKanto.checksum != KantoSave_Checksum())
        KantoSave_Clear();
    KantoSave_InitTrainerTowerTimes();
    KantoSave_FixSizeRecords();
#endif
}

// --- Poches du sac sans limite ---------------------------------------------------
#define BAG_SAVE_MAGIC 0x42414732 // "BAG2"

// L'ancien bloc (jusqu'au 2026-11-04), à SAVEBLOCK_OLD_BAG_OFFSET
#define OLD_BAG_SAVE_MAGIC 0x42414731 // "BAG1"
struct OldSaveBlockBag
{
    u32 magic;
    struct ItemSlot items[160];
    struct ItemSlot keyItems[80];
    u32 checksum;
};

EWRAM_DATA struct SaveBlockBag gSaveBlockBag = {0};

static u32 BagSave_Checksum(void)
{
    const u8 *p = (const u8 *)&gSaveBlockBag;
    u32 sum = 0x811C9DC5, i;
    for (i = 0; i < offsetof(struct SaveBlockBag, checksum); i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}

void BagSave_Write(void)
{
#ifdef PORTABLE
    gSaveBlockBag.magic = BAG_SAVE_MAGIC;
    gSaveBlockBag.checksum = BagSave_Checksum();
    Platform_WriteExtraSaveAt(SAVEBLOCK_BAG_OFFSET, &gSaveBlockBag, sizeof(gSaveBlockBag));
#endif
}

#ifdef PORTABLE
static u32 OldBagSave_Checksum(const struct OldSaveBlockBag *bag)
{
    const u8 *p = (const u8 *)bag;
    u32 sum = 0x811C9DC5, i;
    for (i = 0; i < offsetof(struct OldSaveBlockBag, checksum); i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}
#endif

// Sauvegarde d'avant ce bloc : les Objets et Objets rares de l'ancien bloc « BAG1 », ou, plus ancienne, les poches
// d'origine de SaveBlock1 ; les Balls viennent toujours de SaveBlock1 (quantités chiffrées avec la même clé, copiées
// telles quelles). Le bloc est écrit à la sauvegarde suivante.
void BagSave_Read(void)
{
#ifdef PORTABLE
    struct OldSaveBlockBag old;

    if (Platform_ReadExtraSaveAt(SAVEBLOCK_BAG_OFFSET, &gSaveBlockBag, sizeof(gSaveBlockBag))
     && gSaveBlockBag.magic == BAG_SAVE_MAGIC
     && gSaveBlockBag.checksum == BagSave_Checksum())
        return;
#endif
    memset(&gSaveBlockBag, 0, sizeof(gSaveBlockBag));
#ifdef PORTABLE
    if (Platform_ReadExtraSaveAt(SAVEBLOCK_OLD_BAG_OFFSET, &old, sizeof(old))
     && old.magic == OLD_BAG_SAVE_MAGIC
     && old.checksum == OldBagSave_Checksum(&old))
    {
        memcpy(gSaveBlockBag.items, old.items, sizeof(old.items));
        memcpy(gSaveBlockBag.keyItems, old.keyItems, sizeof(old.keyItems));
    }
    else
#endif
    {
        memcpy(gSaveBlockBag.items, gSaveBlock1Ptr->bagPocket_Items, sizeof(gSaveBlock1Ptr->bagPocket_Items));
        memcpy(gSaveBlockBag.keyItems, gSaveBlock1Ptr->bagPocket_KeyItems, sizeof(gSaveBlock1Ptr->bagPocket_KeyItems));
    }
    memcpy(gSaveBlockBag.pokeBalls, gSaveBlock1Ptr->bagPocket_PokeBalls, sizeof(gSaveBlock1Ptr->bagPocket_PokeBalls));
}

// Panthéon de Kanto (src/kanto_hall_of_fame.c) : ses équipes, à part de celles de Hoenn, écrites dans le bloc annexe
// à KANTO_HOF_OFFSET (kanto_save.h), avant le sac (STATIC_ASSERT dans kanto_hall_of_fame.c)
#define KANTO_HOF_MAGIC  0x464F484B // "KHOF"

static u32 KantoHallOfFame_Checksum(const void *data, u32 size)
{
    const u8 *p = data;
    u32 sum = 0x811C9DC5, i;

    for (i = 0; i < size; i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}

void KantoHallOfFame_Write(const void *data, u32 size)
{
#ifdef PORTABLE
    u32 header[2] = {KANTO_HOF_MAGIC, KantoHallOfFame_Checksum(data, size)};

    Platform_WriteExtraSaveAt(KANTO_HOF_OFFSET, header, sizeof(header));
    Platform_WriteExtraSaveAt(KANTO_HOF_OFFSET + sizeof(header), data, size);
#endif
}

// Toujours TRUE : sans Panthéon de Kanto enregistré, les équipes sont vides
bool8 KantoHallOfFame_Read(void *data, u32 size)
{
#ifdef PORTABLE
    u32 header[2];

    if (Platform_ReadExtraSaveAt(KANTO_HOF_OFFSET, header, sizeof(header)) && header[0] == KANTO_HOF_MAGIC
     && Platform_ReadExtraSaveAt(KANTO_HOF_OFFSET + sizeof(header), data, size)
     && header[1] == KantoHallOfFame_Checksum(data, size))
        return TRUE;
#endif
    memset(data, 0, size);
    return TRUE;
}
