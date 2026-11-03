#ifndef GUARD_FRAMEDRAW_H
#define GUARD_FRAMEDRAW_H

#include "global.h"

void DrawFrame(uint16_t *pixels);
void DrawFrame_DescribePixel(int x, int y, char *out, size_t size);
#endif