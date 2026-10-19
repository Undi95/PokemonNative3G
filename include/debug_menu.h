#ifndef GUARD_DEBUG_MENU_H
#define GUARD_DEBUG_MENU_H

// Menu de debug : compilé uniquement avec KANTO_DEBUG=1 (voir src/debug_menu.c).
extern bool8 gDebugNoClip;
extern bool8 gDebugNoEncounters;

void DebugMenu_Open(void);

#endif // GUARD_DEBUG_MENU_H
