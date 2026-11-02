#ifndef GUARD_DEBUG_MENU_H
#define GUARD_DEBUG_MENU_H

// Menu de debug : compilé uniquement avec KANTO_DEBUG=1 (voir src/debug_menu.c).
extern bool8 gDebugNoClip;
extern bool8 gDebugNoEncounters;

void DebugMenu_Open(void);
// Une action du menu qui change la partie sans écran (soins, objets, drapeaux…), par son rang dans le menu : FALSE
// si elle a besoin du menu (téléport, carte de vol…). Outil jeu.debug (src/debug_tools.c)
bool8 DebugMenu_ApplyAction(u8 action);
const u8 *DebugMenu_GetActionName(u8 action);

#endif // GUARD_DEBUG_MENU_H
