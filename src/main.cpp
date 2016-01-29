
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_TTF.h>

#include "sprite.h"
#include "renderer.h"
#include "audio.h"
#include "con_vars.h"
#include "events.h"
#include "input.h"
#include "console.h"
#include "windowing.h"
#include "config.h"

#include "database.h"
#include "card.h"

//game states
#include "game_state.h"
#include "gs_menu.h"
#include "gs_cardgame.h"

Renderer* g_renderer;

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_StopTextInput();

	Config c("config.cfg");
	c.Reload();

	Renderer r;
	g_renderer = &r;

	console.run_command("bind escape +quit");

	console.run_command("bind left +left");
	console.run_command("bind a +left");

	console.run_command("bind right +right");
	console.run_command("bind d +right");

	console.run_command("bindtoggle tilde +console");

	g_input_manager.load_bindings("bindings.cfg");
	g_input_manager.save_bindings("bindings.cfg");

	g_sound_manager.init();

	Card a("Generic Monster", "This fearsome beast will be so generic it makes you cringe.", 800);
	a.picture.load(r.renderer, "assets/generic monster.agi");

	Card b("Yellow Monster", "This beast is much better than the Generic Monster because of its apealing yellow colour.");
	b.picture.load(r.renderer, "assets/yellow monster.agi");
	
	Card d("Sword of Cutting", "This is a pretty generic equipment card. It would prbably go well with the Generic Monster.", 0, 0, 0, ct_equipment);
	d.picture.load(r.renderer, "assets/sword.agi");
	d.e = e_attackboost;
	d.attack_boost = 100;

	g_card_db.set(a);
	g_card_db.set(b);
	g_card_db.set(d);

	MenuState menu_state;
	size_t menu_state_id = GameState::register_game_state((GameState*)&menu_state);

	CardState cardgame_state;
	size_t cardgame_state_id = GameState::register_game_state((GameState*)&cardgame_state);
	if (menu_state_id) 1;

	GameState::change_game_state((int)cardgame_state_id);

	//g_sound_manager.play_file_loop("assets/Town_-_Quiet_Country_Village.mp3");

	while (!g_cvars.b_get("+quit")) {
		sdl_event_pump();

		GameState::current->update();
		GameState::current->draw();

		console.draw();
		r.refresh();
	}

	g_input_manager.save_bindings("bindings.cfg");

	TTF_Quit();
	SDL_Quit();
	return 0;
}