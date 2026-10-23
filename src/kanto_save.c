#include "global.h"
#include "kanto_save.h"
#include "constants/kanto/trainer_tower.h"
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
#endif
}

// --- Poches agrandies du sac ---------------------------------------------------
#define BAG_SAVE_MAGIC 0x42414731 // "BAG1"

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

// Sauvegarde sans ce bloc (antérieure) : on reprend les poches d'origine de SaveBlock1
// (quantités chiffrées avec la même clé, copiées telles quelles).
void BagSave_Read(void)
{
#ifdef PORTABLE
    if (Platform_ReadExtraSaveAt(SAVEBLOCK_BAG_OFFSET, &gSaveBlockBag, sizeof(gSaveBlockBag))
     && gSaveBlockBag.magic == BAG_SAVE_MAGIC
     && gSaveBlockBag.checksum == BagSave_Checksum())
        return;
#endif
    memset(&gSaveBlockBag, 0, sizeof(gSaveBlockBag));
    memcpy(gSaveBlockBag.items, gSaveBlock1Ptr->bagPocket_Items, sizeof(gSaveBlock1Ptr->bagPocket_Items));
    memcpy(gSaveBlockBag.keyItems, gSaveBlock1Ptr->bagPocket_KeyItems, sizeof(gSaveBlock1Ptr->bagPocket_KeyItems));
}

// Panthéon de Kanto (src/kanto_hall_of_fame.c) : ses équipes, à part de celles de Hoenn,
// écrites après le sac dans le bloc annexe
#define KANTO_HOF_OFFSET 8192
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
