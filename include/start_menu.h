#ifndef GUARD_START_MENU_H
#define GUARD_START_MENU_H

extern bool8 (*gMenuCallback)(void);

void ShowReturnToFieldStartMenu(void);
void Task_ShowStartMenu(u8 taskId);
void ShowStartMenu(void);
void ShowBattlePyramidStartMenu(void);
void SaveGame(void);
void CB2_SetUpSaveAfterLinkBattle(void);
void SaveForBattleTowerLink(void);
void HideStartMenu(void);
void AppendToList(u8 *list, u8 *pos, u8 newEntry);
// Outils de debug (menu.start) : les entrées du menu Start et la position du curseur ; renvoie leur nombre
u8 StartMenu_GetActions(const u8 **actions, u8 *cursorPos);
const u8 *StartMenu_GetActionText(u8 action);

#endif // GUARD_START_MENU_H
