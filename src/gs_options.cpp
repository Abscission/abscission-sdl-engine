#include "gs_options.h"
#include "renderer.h"
#include "input.h"
#include "console.h"
#include "abscission_math.h"


void OptionState::init() {

}

void OptionState::shutdown() {

}

void OptionState::update() {

}

void OptionState::draw() {

	g_renderer->draw_text("Resolution", g_renderer->width / 5, int(0.35f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });
	
	SDL_Rect back_hitbox = g_renderer->draw_text("Back", g_renderer->width / 15, int(0.9f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });

	if (g_input_manager.click_thisframe) {
		if (is_mouse_over(back_hitbox)) {
			GameState::close_current_state(0);
		}
	}

}
