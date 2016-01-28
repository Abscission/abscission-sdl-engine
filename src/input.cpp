#include "input.h"
#include "config.h"
#include <fstream>

void InputManager::bind(SDL_Keycode c, std::string binding) {
	bindings[c] = binding;
}

void InputManager::bind_toggle(SDL_Keycode c, std::string binding){
	bind_toggles[c] = binding;

}

void InputManager::save_bindings(std::string filename) {
	std::ofstream file(filename);

 	for (auto binding : bindings) {
		if (binding.second != "") {
			file << "bind " << binding.first << ' ' << binding.second << '\n';
		}
	}

	for (auto binding : bind_toggles) {
		if (binding.second != "") {
			file << "bind " << binding.first << ' ' << binding.second << '\n';
		}
	}

	file.flush();
	file.close();
}

void InputManager::load_bindings(std::string filename) {
	Config bind_config(filename);
	return;
}


InputManager g_input_manager;



