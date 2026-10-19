#ifndef GUARD_PLATFORM_H
#define GUARD_PLATFORM_H

#include "global.h"
#include "siirtc.h"

void Platform_StoreSaveFile(void);
// Données hors flash GBA (bloc Kanto), après les 128 Ko du fichier .sav
void Platform_WriteExtraSave(const void *data, u32 size);
bool8 Platform_ReadExtraSave(void *data, u32 size);
void Platform_WriteExtraSaveAt(u32 offset, const void *data, u32 size);
bool8 Platform_ReadExtraSaveAt(u32 offset, void *data, u32 size);
void Platform_ReadFlash(u16 sectorNum, u32 offset, u8 *dest, u32 size);
void Platform_QueueAudio(float *audioBuffer, s32 samplesPerFrame);
u16 Platform_GetKeyInput(void);
void Platform_GetStatus(struct SiiRtcInfo *rtc);
void Platform_SetStatus(struct SiiRtcInfo *rtc);
static void UpdateInternalClock(void);
void Platform_GetDateTime(struct SiiRtcInfo *rtc);
void Platform_SetDateTime(struct SiiRtcInfo *rtc);
void Platform_GetTime(struct SiiRtcInfo *rtc);
void Platform_SetTime(struct SiiRtcInfo *rtc);
void Platform_SetAlarm(u8 *alarmData);

#endif