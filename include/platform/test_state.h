#ifndef GUARD_PLATFORM_TEST_STATE_H
#define GUARD_PLATFORM_TEST_STATE_H

#include <stdio.h>
#include "gba/types.h"

extern bool8 gTestStateEnabled;
extern s8 gTestFont;

void WriteTestState(FILE *file, u32 frame);
void RunTestCommand(FILE *file, const char *line);
void TestState_OnText(u8 windowId, const u8 *text);
void TestState_OnTextClipped(u8 windowId);
void TestState_OnFrame(u32 frame);

#endif // GUARD_PLATFORM_TEST_STATE_H
