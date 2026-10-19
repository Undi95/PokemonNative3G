// Specials de Rouge Feu portés depuis le décomp RF (field_specials.c, fame_checker.c, quest_log.c).
#include "global.h"
#include "event_data.h"
#include "kanto_save.h"
#include "constants/kanto/fame_checker.h"

// Journal (Quest Log) de RF : le système n'est pas encore importé, il n'enregistre ni ne rejoue
// rien, donc son état reste 0 (ni enregistrement ni lecture).
EWRAM_DATA u8 gQuestLogState = 0;

// quest_log.c
void GetQuestLogState(void)
{
    gSpecialVar_Result = gQuestLogState;
}

// field_specials.c : SetQuestLogEvent(QL_EVENT_USED_PKMN_CENTER, NULL), sans effet tant que le
// journal n'est pas importé.
void SetUsedPkmnCenterQuestLogEvent(void)
{
}

// field_specials.c
bool8 IsPlayerNotInTrainerTowerLobby(void)
{
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TRAINER_TOWER_LOBBY) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TRAINER_TOWER_LOBBY))
        return FALSE;
    else
        return TRUE;
}

// fame_checker.c (données dans gSaveBlockKanto au lieu de SaveBlock1)
void UpdatePickStateFromSpecialVar8005(void)
{
    if (gSpecialVar_0x8004 < NUM_FAMECHECKER_PERSONS && gSpecialVar_0x8005 < 3)
    {
        if (gSpecialVar_0x8005 == FCPICKSTATE_NO_DRAW)
            return;
        if (   gSpecialVar_0x8005 == FCPICKSTATE_SILHOUETTE
            && gSaveBlockKanto.fameChecker[gSpecialVar_0x8004].pickState == FCPICKSTATE_COLORED
           )
            return;
        gSaveBlockKanto.fameChecker[gSpecialVar_0x8004].pickState = gSpecialVar_0x8005;
    }
}

void SetFlavorTextFlagFromSpecialVars(void)
{
    if (gSpecialVar_0x8004 < NUM_FAMECHECKER_PERSONS && gSpecialVar_0x8005 < 6)
    {
        gSaveBlockKanto.fameChecker[gSpecialVar_0x8004].flavorTextFlags |= (1 << gSpecialVar_0x8005);
        gSpecialVar_0x8005 = FCPICKSTATE_SILHOUETTE;
        UpdatePickStateFromSpecialVar8005();
    }
}
