#include "renderer.h"
#include "con_vars.h"

#include <sdl/SDL_ttf.h>

Renderer::Renderer(const char * title) {
	init(title);
}

void Renderer::init(const char * title) {
	this->width = atoi(g_cvars.get("r_resolution_x").c_str());
	this->height = atoi(g_cvars.get("r_resolution_y").c_str());
	if (window) {
		SDL_SetWindowSize(window, this->width, this->height);
	}
	else {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, 0);
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

void Renderer::draw_sprite(Image & spr, int x, int y, float scale, double angle) {
	SDL_Rect dst = { x, y, int(spr.width * scale), int(spr.height * scale) };
	SDL_RenderCopyEx(renderer, spr.texture, 0, &dst, angle, 0, SDL_FLIP_NONE);
}

void Renderer::draw_rect(int x, int y, int w, int h, SDL_Color c) {
	SDL_Rect r{ x, y, w, h };
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer, &r);
}

static TTF_Font *fonts[100];

SDL_Rect Renderer::draw_text(const char * text, int x, int y, int font_size, SDL_Color c, int wrap_length, bool flip, text_align align) {

	SDL_Surface *text_surface = draw_text_to_surface(text, font_size, c, wrap_length);
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	int iW, iH;
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);

	SDL_Rect rect{ (align == ALIGN_RIGHT) ? x - iW : x, y, iW, iH };

	SDL_RenderCopyEx(renderer, texture, 0, &rect, flip ? 180 : 0, 0, SDL_FLIP_NONE);
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);

	return rect;
}

SDL_Surface* Renderer::draw_text_to_surface(const char * text, int font_size, SDL_Color c, int wrap_length) {
	if (fonts[font_size] == nullptr) {
		fonts[font_size] = TTF_OpenFont("open_sans.ttf", font_size);
	}

	SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(fonts[font_size], text, c, wrap_length);

	return text_surface;
}
