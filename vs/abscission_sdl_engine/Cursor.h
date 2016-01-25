#pragma once

#include <sdl/SDL.h>

inline void set_cursor(SDL_SystemCursor sc) {
	SDL_Cursor* c = SDL_CreateSystemCursor(sc);
	SDL_SetCursor(c);
	SDL_FreeCursor(c);
}