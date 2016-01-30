#include "gs_menu.h"
#include "gs_cardgame.h"
#include "gs_options.h"
#include "renderer.h"
#include "audio.h"
#include "input.h"
#include "console.h"
#include "abscission_math.h"


void MenuState::init() {
	//TODO(Xwing); Start main menu music
	g_sound_manager.play_file_loop("assets/Dream World.ogg");
	

}

void MenuState::shutdown() {
}

void MenuState::update() {
	
}

void MenuState::draw() {
	g_renderer->draw_rect(0, 0, g_renderer->width, g_renderer->height, SDL_Color{ 0, 208, 42, 255 });
	SDL_Rect play_hitbox = g_renderer->draw_text("Play", g_renderer->width / 20, int(0.75f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });
	SDL_Rect options_hitbox = g_renderer->draw_text("Options", g_renderer->width / 20, int(0.8f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });
	SDL_Rect credits_hitbox = g_renderer->draw_text("Credits", g_renderer->width / 20, int(0.85f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });
	SDL_Rect quit_hitbox = g_renderer->draw_text("Quit", g_renderer->width / 20, int(0.9f * g_renderer->height), 20, SDL_Color{ 255, 255, 255, 255 });

	if (g_input_manager.click_thisframe) {
		if (is_mouse_over(play_hitbox)) {
			CardState* c = new CardState;
			GameState::create_game_state(c);
		}
		if (is_mouse_over(options_hitbox)) {
			OptionState* o = new OptionState;
			GameState::create_game_state(o);
		}
		if (is_mouse_over(credits_hitbox)) {
			//credits
		}
		if (is_mouse_over(quit_hitbox)) {
			console.run_command("quit");
		}
	}

}
