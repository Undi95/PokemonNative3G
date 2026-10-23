#ifndef GUARD_KANTO_VS_SEEKER_H
#define GUARD_KANTO_VS_SEEKER_H

// Rouge Feu (vs_seeker.h) : Cherche VS, revanches des dresseurs de Kanto
void Task_VsSeeker_0(u8 taskId);
void KantoClearRematchStateByTrainerId(void);
void KantoClearRematchStateOfLastTalked(void);
int KantoGetRematchTrainerId(u16 trainerId);
bool8 UpdateVsSeekerStepCounter(void);
void KantoMapResetTrainerRematches(u16 mapGroup, u16 mapNum);
bool8 KantoShouldTryRematchBattle(void);
bool8 KantoIsTrainerReadyForRematch(void);
void Task_ItemUse_CloseMessageBoxAndReturnToField_VsSeeker(u8 taskId);
void HoennVsSeekerClearRematchStateOfLastTalked(void);

// battle_setup.c (PokemonNative3G) : revanches du PokéNav déclenchées par le Cherche VS à Hoenn
bool8 HoennVsSeekerCanRematch(u16 trainerId);
bool8 HoennVsSeekerWantsRematch(u16 trainerId);
void HoennVsSeekerSetRematch(u16 trainerId);

#endif // GUARD_KANTO_VS_SEEKER_H
