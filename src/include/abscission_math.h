#pragma once

#include "input.h"
#include "sdl/SDL.h"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

inline bool is_mouse_over(SDL_Rect& a) {
	return (g_input_manager.mouse_x > a.x && g_input_manager.mouse_x < a.x + a.w &&
		g_input_manager.mouse_y > a.y && g_input_manager.mouse_y < a.y + a.h);
}