#ifndef GUARD_KANTO_SUMMARY_SCREEN_H
#define GUARD_KANTO_SUMMARY_SCREEN_H

// Rouge Feu : pokemon_summary_screen.h (option MENUS = KANTO)
enum PokemonSummaryScreenMode
{
    PSS_MODE_NORMAL,
    PSS_MODE_UNK1,
    PSS_MODE_SELECT_MOVE,
    PSS_MODE_FORGET_MOVE,
    PSS_MODE_TRADE,
    PSS_MODE_BOX,
};

void KantoShowPokemonSummaryScreen(struct Pokemon * party, u8 cursorPos, u8 lastIdx, MainCallback savedCallback, u8 mode);
void KantoShowSelectMovePokemonSummaryScreen(struct Pokemon * party, u8 cursorPos, u8 lastIdx, MainCallback savedCallback, u16 a4);
u8 KantoGetMoveSlotToReplace(void);
u8 KantoGetLastViewedMonIndex(void);
void KantoSetPokemonSummaryScreenMode(u8 mode);

#endif // GUARD_KANTO_SUMMARY_SCREEN_H
