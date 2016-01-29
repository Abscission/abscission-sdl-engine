#pragma once

#include <SDL2/SDL.h>

inline SDL_Cursor* get_cursor() {
	return SDL_GetCursor();
}

inline void set_cursor(SDL_SystemCursor sc) {
	static SDL_Cursor* cursors[SDL_SYSTEM_CURSOR_HAND];

	if(!cursors[sc])
		cursors[sc] = SDL_CreateSystemCursor(sc);

	SDL_SetCursor(cursors[sc]);
}