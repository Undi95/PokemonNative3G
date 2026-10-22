#ifndef GUARD_HALL_OF_FAME_H
#define GUARD_HALL_OF_FAME_H

void CB2_DoHallOfFameScreen(void);
void CB2_DoHallOfFameScreenDontSaveData(void);
void CB2_DoHallOfFamePC(void);
void KantoCB2_InitHofPC(void);         // Rouge Feu, src/kanto_hall_of_fame.c
void KantoCB2_DoHallOfFameScreen(void); // Rouge Feu, src/kanto_hall_of_fame.c
bool8 HasHallOfFameInThisRegion(void);

// hof_pc.c
void ReturnFromHallOfFamePC(void);

#endif // GUARD_HALL_OF_FAME_H
