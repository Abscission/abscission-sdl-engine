#include "windowing.h"
#include "renderer.h"
#include "input.h"
#include "cursor.h"
#include "abscission_math.h"

void Window::open() {
	_open = true;
}

void Window::close() {
	_open = false;
}

void Window::toggle_open() {
	_open = !_open;
}

void Window::update_and_draw() {
	Renderer& r = *g_renderer;

	if (_open) {
		const SDL_Rect win_pos = { x, y, width, height };
	
		bool can_resize_x = (g_input_manager.mouse_x > x + width - 4 && g_input_manager.mouse_x < x + width + 4);
		bool can_resize_y = (g_input_manager.mouse_y > y + height - 4 && g_input_manager.mouse_y < y + height + 4);
		bool can_move = g_input_manager.mouse_y > y && g_input_manager.mouse_y < y + 10 && g_input_manager.mouse_x > x && g_input_manager.mouse_x < x + 780;

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
		else if (can_move) {
			set_cursor(SDL_SYSTEM_CURSOR_HAND);
		}
		else {
			set_cursor(SDL_SYSTEM_CURSOR_ARROW);
		}


		if (g_input_manager.click) {

			if (resizing_x) {
				width = MAX(g_input_manager.mouse_x - x, 100);
			}

			if (!resizing_x && g_input_manager.mouse_x > x + width - 4 && g_input_manager.mouse_x < x + width + 4) {
				resizing_x = true;
			}

			if (resizing_y) {
				height = MAX(g_input_manager.mouse_y - y, 100);
			}

			if (!resizing_y && g_input_manager.mouse_y > y + height - 4 && g_input_manager.mouse_y < y + height + 4) {
				resizing_y = true;
			}
			if (dragging) {
				x = g_input_manager.mouse_x - drag_x;
				y = g_input_manager.mouse_y - drag_y;
			}
			if (!dragging && g_input_manager.mouse_y > y && g_input_manager.mouse_y < y + 10
				&& g_input_manager.mouse_x > x && g_input_manager.mouse_x < x + 780) {
				dragging = true;
				drag_x = g_input_manager.mouse_x - x;
				drag_y = g_input_manager.mouse_y - y;
			}
		}
		else {
			dragging = false;
			resizing_x = false;
			resizing_y = false;
		}

		if (g_input_manager.click_thisframe) {
			
		}

		SDL_SetRenderDrawColor(r.renderer, 150, 150, 150, 200);
		SDL_RenderFillRect(r.renderer, &win_pos);
	}

}
