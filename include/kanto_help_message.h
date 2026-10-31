#ifndef GUARD_KANTO_HELP_MESSAGE_H
#define GUARD_KANTO_HELP_MESSAGE_H

// Rouge Feu : help_message.c
void ResetHelpMessageWindowId(void);
u8 CreateHelpMessageWindow(void);
void DestroyHelpMessageWindow(u8 a0);
void DrawHelpMessageWindowTilesById(u8 windowId);
extern const u16 gHelpMessageWindow_Pal[]; // RF : GetTextWindowPalette(2)
void PrintTextOnHelpMessageWindow(const u8 *text, u8 mode);

#endif // GUARD_KANTO_HELP_MESSAGE_H
