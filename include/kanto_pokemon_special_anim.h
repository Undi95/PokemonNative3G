// Rouge Feu : pokemon_special_anim.h (scène de l'objet utilisé sur un Pokémon, option SAC = KANTO)
#ifndef GUARD_KANTO_POKEMON_SPECIAL_ANIM_H
#define GUARD_KANTO_POKEMON_SPECIAL_ANIM_H

#include "global.h"
#include "main.h"

void CreateLevelUpVerticalSpritesTask(u16 x, u16 y, u16 tileTag, u16 paletteTag, u16 priority, u16 subpriority);
bool8 LevelUpVerticalSpritesTaskIsRunning(void);
void KPSA_GetMonLevelUpWindowStats(struct Pokemon *mon, u16 *currStats);
void KPSA_DrawLevelUpWindowPg1(u16 windowId, u16 *statsBefore, u16 *statsAfter, u8 bgClr, u8 fgClr, u8 shadowClr);
void KPSA_DrawLevelUpWindowPg2(u16 windowId, u16 *currStats, u8 bgClr, u8 fgClr, u8 shadowClr);
void StartUseItemAnim_Normal(u8 slotId, u16 itemId, MainCallback callback);
void StartUseItemAnim_CantEvolve(u8 slotId, u16 itemId, MainCallback callback);
bool32 PSA_IsCancelDisabled(void);
void StartUseItemAnim_ForgetMoveAndLearnTMorHM(u8 slotId, u16 itemId, u16 moveId, MainCallback callback);

#endif // GUARD_KANTO_POKEMON_SPECIAL_ANIM_H
