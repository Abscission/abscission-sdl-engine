
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

Renderer* g_renderer;

int main(int, char**) {



	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_StopTextInput();

	console.run_command("r_resolution_x 800");
	console.run_command("r_resolution_y 600");

	Renderer r;
	g_renderer = &r;

	Image s;
	s.load(r.renderer, "test.agi");

	Config c("test.cfg");
	c.Set("bind t +right");
	c.Reload();

	console.run_command("bind escape +quit");

	console.run_command("bind left +left");
	console.run_command("bind a +left");

	console.run_command("bind right +right");
	console.run_command("bind d +right");

	console.run_command("bindtoggle tilde +console");

	g_input_manager.save_bindings("bindings.cfg");

	float pos = 100;
	
	Window w;
	w.open();
	w.close();

	Card a("Generic Monster", "This fearsome beast will be so generic it\nmakes you cringe.");
	a.picture.load(r.renderer, "assets/generic monster.agi");

	Database<Card> cards;

	cards.set(a);

	float card_x = 4;
	float card_y = 4;
	float card_scale = 0.5f;

	while (!g_cvars.b_get("+quit")) {
		sdl_event_pump();

		if (g_cvars.b_get("+left")) {
			card_x-= 0.05f;
		}

		if (g_cvars.b_get("+right")) {
			card_x += 0.05f;
		}

		if (g_cvars.b_get("+scaleup")) {
			card_scale += 0.005f;
		}

		if (g_cvars.b_get("+scaledown")) {
			card_scale -= 0.005f;
		}


		r.draw_text("Hello, World!\ntest", 100, 100, 25);

		r.draw_sprite(s, (int)pos, 10, 50);

		w.update_and_draw();

		console.draw();

		a.render((int)card_x, (int)card_y, card_scale);

		r.refresh();
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}