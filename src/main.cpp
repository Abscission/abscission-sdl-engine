
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

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
#include "gs_battle.h"

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

	Card a("Generic Monster", "This fearsome beast will be so generic it makes you cringe.", 400, 200, 200, 200);
	a.picture.load(r.renderer, "assets/generic monster.agi");
	a.in_game.load(r.renderer, "assets/red monster top.agi");

	Card b("Yellow Monster", "This beast is much better than the Generic Monster because of its apealing yellow colour.", 400, 200, 200, 200);
	b.picture.load(r.renderer, "assets/yellow monster.agi");
	b.in_game.load(r.renderer, "assets/yellow monster top.agi");

	Card d("Sword of Cutting", "This is a pretty generic equipment card. It would prbably go well with the Generic Monster.", 0, 0, 0, ct_equipment);
	d.type = ct_equipment;
	d.picture.load(r.renderer, "assets/sword.agi");
	d.e = e_attackboost;
	d.attack_boost = 100;

	g_card_db.set(a);
	g_card_db.set(b);
	g_card_db.set(d);

	MenuState menu_state;
	GameState::create_game_state((GameState*)&menu_state);

	while (!g_cvars.b_get("+quit")) {
		sdl_event_pump();

		GameState::gamestate_queue.back()->update();
		GameState::gamestate_queue.back()->draw();

		console.draw();
		r.refresh();
	}

	g_input_manager.save_bindings("bindings.cfg");

	TTF_Quit();
	SDL_Quit();
	return 0;
}