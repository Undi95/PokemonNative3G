// Rouge Feu : pc_screen_effect.h (fonctions dans kanto_hall_of_fame.c)
#ifndef GUARD_KANTO_PC_SCREEN_EFFECT_H
#define GUARD_KANTO_PC_SCREEN_EFFECT_H

void BeginPCScreenEffect_TurnOn(u16 xspeed, u16 yspeed, u8 priority);
void BeginPCScreenEffect_TurnOff(u16 xspeed, u16 yspeed, u8 priority);
bool8 IsPCScreenEffectRunning_TurnOff(void);
bool8 IsPCScreenEffectRunning_TurnOn(void);

#endif // GUARD_KANTO_PC_SCREEN_EFFECT_H
