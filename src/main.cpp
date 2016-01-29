
#include <cstdio>

#include <sdl/SDL.h>
#include <sdl/SDL_render.h>
#include <sdl/SDL_TTF.h>

#include "sprite.h"
#include "renderer.h"
#include "con_vars.h"
#include "events.h"
#include "input.h"
#include "console.h"
#include "windowing.h"
#include "config.h"

#include "database.h"
#include "card.h"
#include "game_state.h"


Renderer* g_renderer;

int main(int, char**) {



	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_StopTextInput();

	Config c("test.cfg");
	c.Reload();

	Renderer r;
	g_renderer = &r;

	console.run_command("bind escape +quit");

	console.run_command("bind left +left");
	console.run_command("bind a +left");

	console.run_command("bind right +right");
	console.run_command("bind d +right");

	console.run_command("bindtoggle tilde +console");

	g_input_manager.save_bindings("bindings.cfg");

	Card a("Generic Monster", "This fearsome beast will be so generic it makes you cringe.");
	a.picture.load(r.renderer, "assets/generic monster.agi");

	Card b("Yellow Monster", "This beast is much better than the Generic Monster because of its apealing yellow colour.");
	b.picture.load(r.renderer, "assets/yellow monster.agi");

	g_card_db.set(a);
	g_card_db.set(b);

	CardState cgs;
	GameState::register_game_state((GameState*)&cgs);
	GameState::change_game_state(0);

	while (!g_cvars.b_get("+quit")) {
		sdl_event_pump();

		GameState::current->update();
		GameState::current->draw();

		console.draw();
		r.refresh();
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}