#ifndef GUARD_PLATFORM_TEST_STATE_H
#define GUARD_PLATFORM_TEST_STATE_H

#include <stdio.h>
#include "gba/types.h"

extern bool8 gTestStateEnabled;
extern s8 gTestFont;

void WriteTestState(FILE *file, u32 frame);
void RunTestCommand(FILE *file, const char *line);
void TestState_OnText(u8 windowId, u8 fontId, u8 fgColor, const u8 *text);
void TestState_OnAnomaly(const char *kind, s32 windowId, const char *text);
void TestState_OnSong(u16 songNum);
void TestState_OnFrame(u32 frame);

#endif // GUARD_PLATFORM_TEST_STATE_H
