#include "renderer.h"
#include "con_vars.h"

#include <sdl/SDL_ttf.h>

Renderer::Renderer(int width, int height, const char * title) {
	init(width, height, title);
}

void Renderer::init(int width, int height, const char * title) {
	width = atoi(g_cvars.get("r_resolution_x").c_str());
	height = atoi(g_cvars.get("r_resolution_y").c_str());
	if (window) {
		SDL_SetWindowSize(window, width, height);
	}
	else {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	}
	if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Renderer::refresh() {
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::draw_sprite(Image & spr, int x, int y, float scale) {
	SDL_Rect dst = { x, y, int(spr.width * scale), int(spr.height * scale) };
	SDL_RenderCopy(renderer, spr.texture, 0, &dst);
}

SDL_Rect Renderer::draw_text(const char * text, int x, int y, int font_size, SDL_Color c) {
	static TTF_Font *fonts[50];
	if (fonts[font_size] == nullptr) {
		fonts[font_size] = TTF_OpenFont("arial.ttf", font_size);
	}

	SDL_Surface *text_surface;
	text_surface = TTF_RenderText_Blended_Wrapped(fonts[font_size], text, c, 500);
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	int iW, iH;
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);

	SDL_Rect rect{ x, y, iW, iH };

	SDL_RenderCopy(renderer, texture, 0, &rect);
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);

	return rect;
}
