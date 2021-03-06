#pragma once

#include <map>
#include <string>

#include "con_vars.h"
#include <sdl/SDL_keycode.h>

class InputManager {
private:
	std::map<SDL_Keycode, std::string> bindings;
	std::map<SDL_Keycode, std::string> bind_toggles;


public:
	bool keys[256];

	void bind(SDL_Keycode c, std::string binding);
	void bind_toggle(SDL_Keycode c, std::string binding);

	std::string text_input;

	bool enter;
	bool click;
	bool click_thisframe;
	int mouse_x;
	int mouse_y;

	friend void sdl_event_pump();
};

extern InputManager g_input_manager;