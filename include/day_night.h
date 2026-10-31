#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

// PokemonNative3G : cycle jour/nuit, purement visuel (option JOUR/NUIT). La nuit d'évolution (Mentali/Noctali)
// suit les mêmes heures, voir IsDayNightHourNight.
#define DAY_NIGHT_NIGHT_BEGIN 20
#define DAY_NIGHT_NIGHT_END   6

bool8 IsDayNightHourNight(u8 hours);
void DayNight_TintPltt(void);

#endif // GUARD_DAY_NIGHT_H
