
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

Renderer* g_renderer;

int main(int, char**) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_StopTextInput();

	console.run_command("r_resolution_x 800");
	console.run_command("r_resolution_y 600");

	Renderer r;
	g_renderer = &r;

	Sprite s;
	s.load(r.renderer, "test.agi");

	console.run_command("bind escape +quit");

	console.run_command("bind left +left");
	console.run_command("bind a +left");

	console.run_command("bind right +right");
	console.run_command("bind d +right");

	console.run_command("bindtoggle tilde +console");

	float pos = 100;

	while (!g_cvars.b_get("+quit")) {
		sdl_event_pump();

		if (g_cvars.b_get("+left")) {
			pos-= 0.01f;
		}

		if (g_cvars.b_get("+right")) {
			pos += 0.01f;
		}

		r.draw_text("Hello, World!\ntest", 100, 100, 25);

		r.draw_sprite(s, (int)pos, 10, 50);

		console.draw();

		r.refresh();
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}