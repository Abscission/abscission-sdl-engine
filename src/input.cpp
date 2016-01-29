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

	std::map <std::string, SDL_Keycode> key_map{
		//Top row
		{ "escape", SDLK_ESCAPE },{ "f1", SDLK_F1 },{ "f2", SDLK_F2 },{ "f3", SDLK_F3 },{ "f4", SDLK_F4 },{ "f5", SDLK_F5 },{ "f6", SDLK_F6 },{ "f7", SDLK_F7 },{ "f8", SDLK_F8 },{ "f9", SDLK_F9 },{ "f10", SDLK_F10 },{ "f11", SDLK_F11 },{ "f12", SDLK_F12 },
		//Second row
		{ "tilde", SDLK_BACKQUOTE },{ "1", SDLK_1 },{ "2", SDLK_2 },{ "3", SDLK_3 },{ "4", SDLK_4 },{ "5", SDLK_5 },{ "6", SDLK_6 },{ "7", SDLK_7 },{ "8", SDLK_8 },{ "9", SDLK_9 },{ "0", SDLK_0 },{ "-", SDLK_MINUS },{ "=", SDLK_PLUS },{ "backspace", SDLK_BACKSPACE },
		//Third row
		{ "tab", SDLK_TAB },{ "q", SDLK_q },{ "w", SDLK_w },{ "e", SDLK_e },{ "r", SDLK_r },{ "t", SDLK_t },{ "y", SDLK_y },{ "u", SDLK_u },{ "i", SDLK_i },{ "o", SDLK_o },{ "p", SDLK_p },{ "[", SDLK_LEFTBRACKET },{ "]", SDLK_RIGHTBRACKET },{ "\\", SDLK_BACKSLASH },
		//Forth row
		{ "capslock", SDLK_CAPSLOCK },{ "a", SDLK_a },{ "s", SDLK_s },{ "d", SDLK_d },{ "f",SDLK_f },{ "g", SDLK_g },{ "h",SDLK_h },{ "j", SDLK_j },{ "k", SDLK_k },{ "l", SDLK_l },{ ";", SDLK_SEMICOLON },{ "'", SDLK_QUOTE },{ "enter", SDLK_KP_ENTER },
		//Fifth row
		{ "shift", SDLK_LSHIFT },{ "left_shift", SDLK_LSHIFT },{ "z", SDLK_z },{ "x", SDLK_x },{ "c", SDLK_c },{ "v", SDLK_v },{ "b", SDLK_b },{ "n", SDLK_n },{ "m", SDLK_m },{ "comma", SDLK_COMMA },{ ",", SDLK_COMMA },{ "period", SDLK_PERIOD },{ ".", SDLK_PERIOD },{ "/", SDLK_SLASH },{ "right_shift", SDLK_RSHIFT },
		//Bottom row
		{ "control", SDLK_LCTRL },{ "ctrl", SDLK_LCTRL },{ "left_control", SDLK_LCTRL },{ "left_ctrl", SDLK_LCTRL },{ "windowskey", SDLK_APPLICATION },{ "windows", SDLK_APPLICATION },{ "win", SDLK_APPLICATION },{ "alt", SDLK_LALT },{ "left_alt", SDLK_LALT },{ "space", SDLK_SPACE },{ "right_alt", SDLK_RALT },{ "right_ctrl", SDLK_RCTRL },{ "right_control", SDLK_RCTRL },
		//Arrow keys
		{ "up", SDLK_UP },{ "down", SDLK_DOWN },{ "left", SDLK_LEFT },{ "right", SDLK_RIGHT },
		//Numberpad num
		{ "kp0", SDLK_KP_0 },{ "kp00", SDLK_KP_00 },{ "kp1", SDLK_KP_1 },{ "kp2", SDLK_KP_2 },{ "kp3", SDLK_KP_3 },{ "kp4", SDLK_KP_4 },{ "kp5", SDLK_KP_5 },{ "kp6", SDLK_KP_6 },{ "kp7", SDLK_KP_7 },{ "kp8", SDLK_KP_8 },{ "kp9", SDLK_KP_9 },
		//Numberpad other
		{ "numlock", SDLK_NUMLOCKCLEAR },{ "kp/", SDLK_KP_DIVIDE },{ "kp*", SDLK_KP_MULTIPLY },{ "kp-", SDLK_KP_MINUS },{ "kp+", SDLK_KP_PLUS },{ "kp.", SDLK_KP_PERIOD },{ "kpenter", SDLK_KP_ENTER },
		//Other keys
		{ "ins", SDLK_INSERT },{ "insert", SDLK_INSERT },{ "home", SDLK_HOME },{ "pgup", SDLK_PAGEUP },{ "pageup", SDLK_PAGEUP },{ "pgdn", SDLK_PAGEDOWN },{ "pgdown", SDLK_PAGEDOWN },{ "pagedown", SDLK_PAGEDOWN },{ "del", SDLK_DELETE },{ "delete", SDLK_DELETE },{ "end", SDLK_END },{ "scrlk", SDLK_SCROLLLOCK },{ "scrolllock", SDLK_SCROLLLOCK },{ "pause", SDLK_PAUSE }
	};

	std::ofstream file(filename);

 	for (auto binding : bindings) {
		if (binding.second != "") {
			std::string ret;
			for (auto k : key_map) {
				if (k.second == binding.first) {
					ret = k.first;
				}
			}
			if (ret != "") file << "bind " << ret << ' ' << binding.second << '\n';
		}
	}

	for (auto binding : bind_toggles) {
		std::string ret;
		for (auto k : key_map) {
			if (k.second == binding.first) {
				ret = k.first;
			}
		}
		if (ret != "") file << "bindtoggle " << ret << ' ' << binding.second << '\n';
	}

	file.flush();
	file.close();
}

void InputManager::load_bindings(std::string filename) {
	Config bind_config(filename);
	return;
}


InputManager g_input_manager;



