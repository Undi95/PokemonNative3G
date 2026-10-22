#ifndef GUARD_KANTO_CREDITS_H
#define GUARD_KANTO_CREDITS_H

// Rouge Feu (credits.h, overworld.h) : crédits de Kanto, qui défilent sur des cartes de Kanto
#define CREDITSOVWLDCMD_FB 0xFB
#define CREDITSOVWLDCMD_FC 0xFC
#define CREDITSOVWLDCMD_END 0xFD
#define CREDITSOVWLDCMD_LOADMAP 0xFE
#define CREDITSOVWLDCMD_FF 0xFF

#define CREDITSOVWLDLOADMAP(_map, _x, _y, _delay)           \
    { CREDITSOVWLDCMD_LOADMAP, MAP_GROUP(_map), MAP_NUM(_map) }, \
    { _x, _y, _delay }

#define CREDITSOVWLDSCROLL(_xspeed, _yspeed, _length) \
    { _xspeed, _yspeed, _length }

#define CREDITSOVWLDEND \
    { CREDITSOVWLDCMD_END, CREDITSOVWLDCMD_END, CREDITSOVWLDCMD_END }

struct CreditsOverworldCmd
{
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
};

void Overworld_CreditsMainCB(void);
bool32 Overworld_DoScrollSceneForCredits(u8 *state, const struct CreditsOverworldCmd *script, u8 tintMode);

#endif // GUARD_KANTO_CREDITS_H
