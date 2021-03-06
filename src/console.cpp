
#include <map>
#include <sstream>

#include <sdl/SDL.h>
#include <sdl/SDL_keycode.h>

#include "abscission_math.h"
#include "console.h"
#include "types.h"
#include "input.h"
#include "con_vars.h"
#include "renderer.h"
#include "cursor.h"


void Console::draw() {
	Renderer& r = *g_renderer;
	static std::string console_backlog = "";

	if (g_cvars.b_get("+console")) {

		const SDL_Rect con_pos = { console_x, console_y, console_width, console_height };
		const SDL_Rect textbox_pos = { console_x + 10, console_y + console_height - 30, console_width - 20, 20 };
		const SDL_Rect backlog_pos = { console_x + 10, console_y + 10, console_width - 20, console_height - 50 };

		if (!open) {
			open = true;
			g_input_manager.text_input = "";
			textbox_active = true;
			SDL_StartTextInput();
		}

		bool can_resize_x = (g_input_manager.mouse_x > console_x + console_width - 4 && g_input_manager.mouse_x < console_x + console_width + 4);
		bool can_resize_y = (g_input_manager.mouse_y > console_y + console_height - 4 && g_input_manager.mouse_y < console_y + console_height + 4);
		bool in_text_box = g_input_manager.mouse_x > textbox_pos.x && g_input_manager.mouse_x < textbox_pos.x + textbox_pos.w && g_input_manager.mouse_y > textbox_pos.y && g_input_manager.mouse_y < textbox_pos.y + textbox_pos.h;
		bool can_move = g_input_manager.mouse_y > console_y && g_input_manager.mouse_y < console_y + 10	&& g_input_manager.mouse_x > console_x && g_input_manager.mouse_x < console_x + console_width;

		if (can_resize_x) {
			if (can_resize_y) {
				set_cursor(SDL_SYSTEM_CURSOR_SIZENWSE);
			}
			else {
				set_cursor(SDL_SYSTEM_CURSOR_SIZEWE);
			}
		}
		else if (can_resize_y) {
			set_cursor(SDL_SYSTEM_CURSOR_SIZENS);
		}
		else if (in_text_box) {
			set_cursor(SDL_SYSTEM_CURSOR_IBEAM);
		}
		else if (can_move) {
			set_cursor(SDL_SYSTEM_CURSOR_HAND);
		}
		else {
			set_cursor(SDL_SYSTEM_CURSOR_ARROW);
		}


		if (g_input_manager.click) {

			if (resizing_x) {
				console_width = MAX(g_input_manager.mouse_x - console_x, 100);
			}

			if (!resizing_x && g_input_manager.mouse_x > console_x + console_width - 4 && g_input_manager.mouse_x < console_x + console_width + 4) {
				resizing_x = true;
			}

			if (resizing_y) {
				console_height = MAX(g_input_manager.mouse_y - console_y, 100);
			}

			if (!resizing_y && g_input_manager.mouse_y > console_y + console_height - 4 && g_input_manager.mouse_y < console_y + console_height + 4) {
				resizing_y = true;
			}
			if (dragging) {
				console_x = g_input_manager.mouse_x - drag_x;
				console_y = g_input_manager.mouse_y - drag_y;
			}
			if (!dragging && g_input_manager.mouse_y > console_y && g_input_manager.mouse_y < console_y + 10
				&& g_input_manager.mouse_x > console_x && g_input_manager.mouse_x < console_x + 780) {
				dragging = true;
				drag_x = g_input_manager.mouse_x - console_x;
				drag_y = g_input_manager.mouse_y - console_y;
			}
		}
		else {
			dragging = false;
			resizing_x = false;
			resizing_y = false;
		}

		if (g_input_manager.click_thisframe) {
			if (g_input_manager.mouse_x > textbox_pos.x && g_input_manager.mouse_x < textbox_pos.x + textbox_pos.w
				&& g_input_manager.mouse_y > textbox_pos.y && g_input_manager.mouse_y < textbox_pos.y + textbox_pos.h) {
				textbox_active = true;
				SDL_StartTextInput();

			}
			else {
				textbox_active = false;
				SDL_StopTextInput();
			}
		}

		SDL_SetRenderDrawColor(r.renderer, 150, 150, 150, 200);
		SDL_RenderFillRect(r.renderer, &con_pos);

		SDL_SetRenderDrawColor(r.renderer, 200, 200, 200, 200);
		SDL_RenderFillRect(r.renderer, &backlog_pos);
		SDL_RenderFillRect(r.renderer, &textbox_pos);

		r.draw_text(console_backlog.c_str(), backlog_pos.x + 2, backlog_pos.y + 2, 16, SDL_Color{ 0, 0, 0, 255 });
		SDL_Rect text_r = r.draw_text(g_input_manager.text_input.c_str(), textbox_pos.x + 2, textbox_pos.y + 2, 16, SDL_Color{ 0, 0, 0, 255 });

		if (textbox_active && SDL_GetTicks() / 500 % 2 == 0) {
			SDL_SetRenderDrawColor(r.renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(r.renderer, text_r.x + text_r.w + 2, text_r.y, text_r.x + text_r.w + 2, text_r.y + text_r.h);
		}

		if (g_input_manager.enter && textbox_active) {
			console_backlog.append(g_input_manager.text_input + "\n");
			console_backlog.append(run_command(g_input_manager.text_input));
			g_input_manager.text_input = "";
		}
	}
	else {
		if (open) {
			open = false;
			textbox_active = false;
			SDL_StopTextInput();
		}
	}
}


std::string Console::run_command(std::string command) {	
	const static std::map <std::string, SDL_Keycode> keys{
		{ "q", SDLK_q },{ "w", SDLK_w},{ "e", SDLK_e },{ "r", SDLK_r },{ "t", SDLK_t },{ "y", SDLK_y },{ "u", SDLK_u },{ "i", SDLK_i },{ "o", SDLK_o },{ "p", SDLK_p },
		{ "a", SDLK_a },{ "s", SDLK_s },{ "d", SDLK_d },{ "f",SDLK_f },{ "g", SDLK_g },{ "h",SDLK_h },{ "j", SDLK_j },{ "k", SDLK_k },{ "l", SDLK_l },
		{ "z", SDLK_z },{ "x", SDLK_x },{ "c", SDLK_c },{ "v", SDLK_v },{ "b", SDLK_b },{ "n", SDLK_n },{ "m", SDLK_m },{ "comma", SDLK_COMMA },{ "period", SDLK_PERIOD },
		{ "f1", SDLK_F1  },{ "f2", SDLK_F2 },{ "f3", SDLK_F3 },{ "f4", SDLK_F4 },{ "f5", SDLK_F5 },{ "f6", SDLK_F6 },{ "f7", SDLK_F7 },{ "f8", SDLK_F8 },{ "f9", SDLK_F9 },{ "f10", SDLK_F10 },{ "f11", SDLK_F11 },{ "f12", SDLK_F12 },
		{ "space", SDLK_SPACE },{ "shift", SDLK_LSHIFT },{ "left_shift", SDLK_LSHIFT },{ "right_shift", SDLK_RSHIFT },
		{ "ctrl", SDLK_LCTRL },{ "control", SDLK_LCTRL },{ "left_ctrl", SDLK_LCTRL },{ "right_ctrl", SDLK_RCTRL },
		{ "left_control", SDLK_LCTRL },{ "right_control", SDLK_RCTRL },{ "tab", SDLK_TAB },
		{ "up", SDLK_UP },{ "down", SDLK_DOWN },{ "left", SDLK_LEFT },{ "right", SDLK_RIGHT }, {"escape", SDLK_ESCAPE}, {"tilde", SDLK_BACKQUOTE}
	};

	std::stringstream output;

	u64 delim = command.find(" ");
	std::string cmd = command.substr(0, delim);
	std::string params = command.substr(delim + 1);

	if (cmd == "bind") {
		delim = params.find(" ");
		std::string key = params.substr(0, delim);
		std::string binding = params.substr(delim + 1);
		g_input_manager.bind(keys.at(key), binding);

		output << "Binding " << key << " to " << binding;
		
	}
	else if (cmd == "bindtoggle") {
		delim = params.find(" ");
		std::string key = params.substr(0, delim);
		std::string binding = params.substr(delim + 1);
		g_input_manager.bind_toggle(keys.at(key), binding);
	}
	else if (cmd == "c") {
		delim = params.find(" ");
		std::string cmd2 = params.substr(0, delim);
		std::string params2 = params.substr(delim + 1);

		if (cmd2 == "reset") {
			if (params2 == "renderer") {
				g_renderer->init();
			}
		}
		else {
			output << "Unrecognized command " << cmd2;
		}
	}
	else if (cmd == "exit" || cmd == "quit") {
		g_cvars.set("+quit", "1");
	}
	else if (cmd[0] == '-') {
		cmd[0] = '+';
		g_cvars.set(cmd, "");
	}
	else {
		g_cvars.set(cmd, params);
	}

	return output.str();
}

Console console;