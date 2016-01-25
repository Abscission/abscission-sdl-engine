#include "events.h"
#include "input.h"
#include "con_vars.h"
#include <sdl\SDL.h>


void sdl_event_pump(){
	SDL_Event e;
	g_input_manager.click_thisframe = false;
	g_input_manager.enter = false;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			g_cvars.set("+quit", "true");
			break;

		case SDL_KEYDOWN: {
			g_input_manager.keys[e.key.keysym.scancode] = true;

			if (SDL_IsTextInputActive()) {
				if (e.key.keysym.sym == SDLK_BACKSPACE && g_input_manager.text_input.length()) {
					g_input_manager.text_input.pop_back();
				}

				if (e.key.keysym.sym == SDLK_RETURN && g_input_manager.text_input.length()) {
					g_input_manager.enter = true;
				}
			}
			else {
				g_cvars.set(g_input_manager.bindings[e.key.keysym.sym], "1");

				bool toggled = g_cvars.b_get(g_input_manager.bind_toggles[e.key.keysym.sym]);
				g_cvars.set(g_input_manager.bind_toggles[e.key.keysym.sym], toggled ? "" : "1");
			}
		} break;

		case SDL_KEYUP:
			g_input_manager.keys[e.key.keysym.scancode] = false;

			g_cvars.set(g_input_manager.bindings[e.key.keysym.sym], "");
			break;

		case SDL_TEXTINPUT:
			g_input_manager.text_input += e.text.text;
			break;

		case SDL_TEXTEDITING:
			//g_input_manager.text_input = e.edit.text;
			break;

		case SDL_MOUSEBUTTONDOWN:
			g_input_manager.click = true;
			g_input_manager.click_thisframe = true;
			g_input_manager.mouse_x = e.button.x;
			g_input_manager.mouse_y = e.button.y;
			break;

		case SDL_MOUSEBUTTONUP:
			g_input_manager.click = false;
			g_input_manager.mouse_x = e.button.x;
			g_input_manager.mouse_y = e.button.y;
			break;

		case SDL_MOUSEMOTION:
			g_input_manager.mouse_x = e.button.x;
			g_input_manager.mouse_y = e.button.y;
			break;
		}
	}
}
