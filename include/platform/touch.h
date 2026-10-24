#ifndef GUARD_PLATFORM_TOUCH_H
#define GUARD_PLATFORM_TOUCH_H

#include <stdbool.h>
#include <SDL2/SDL.h>

// Touch controls drawn over the screen (src/platform/touch.c)
void Touch_Init(void);
void Touch_HandleEvent(const SDL_Event *event, SDL_Window *window);
// The GBA keys (KEYINPUT bits) held on the screen
u16 Touch_GetButtons(void);
// True once when the RESET button has been held long enough
bool Touch_ResetRequested(void);
bool Touch_FastForward(void);
void Touch_Draw(SDL_Renderer *renderer, SDL_Window *window);

#endif // GUARD_PLATFORM_TOUCH_H
