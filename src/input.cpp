#include "input.h"

void InputManager::bind(SDL_Keycode c, std::string binding) {
	bindings[c] = binding;
}

void InputManager::bind_toggle(SDL_Keycode c, std::string binding){
	bind_toggles[c] = binding;

}


InputManager g_input_manager;