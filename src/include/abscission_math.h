#pragma once

#include "input.h"
#include "SDL2/SDL.h"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

inline bool is_mouse_over(SDL_Rect& a) {
	return (g_input_manager.mouse_x > a.x && g_input_manager.mouse_x < a.x + a.w &&
		g_input_manager.mouse_y > a.y && g_input_manager.mouse_y < a.y + a.h);
}

inline bool is_colliding(SDL_Rect& a, SDL_Rect& b) {
	return (a.x < (b.x + b.w) && (a.x + a.w )> b.x &&
		(a.y > b.y) + b.h && (a.y + a.h) < b.y);
}