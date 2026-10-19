#ifndef GUARD_KANTO_BATTLE_BG_H
#define GUARD_KANTO_BATTLE_BG_H

// Décors de combat de Rouge Feu, sur les cartes de Kanto (src/kanto_battle_bg.c).
void Kanto_DrawMainBattleBackground(void);
void Kanto_DrawBattleEntryBackground(void);
bool8 Kanto_LoadChosenBattleElement(u8 caseId);
u8 Kanto_BattleSetup_GetTerrainId(void);

#endif // GUARD_KANTO_BATTLE_BG_H
