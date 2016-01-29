#include "card.h"
#include "game_state.h"
#include "renderer.h"

Card::Card(std::string name, std::string description) {
	this->name = name;
	this->description = description;
}

void Card::attack(Card& other) {
	//GameState::change_game_state(2);
	other.name.c_str();
}

void Card::render(int x, int y, float scale) {
	static Image background;
	static bool background_loaded;
	if (!background_loaded) {
		background_loaded = true;
		background.load(g_renderer->renderer, "assets/card template.agi");
	}

	/*if (abs(scale - surface_scale) > 0.01f || !surface) {
		surface_scale = scale;

		if (surface) SDL_FreeSurface(surface);
		
		surface = SDL_CreateRGBSurface(0, 384, 512, 32, 0xff0000, 0xff00, 0xff, 0xff000000);
		SDL_Surface* title_surface = g_renderer->draw_text_to_surface(name.c_str(), int(24.f * scale), SDL_Color{ 255, 255, 255, 255 }, 200);

		

		SDL_Rect destRect = { x, y, title_surface->w, title_surface->h };
		SDL_BlitSurface(title_surface, 0, surface, &destRect);
		texture = SDL_CreateTextureFromSurface(g_renderer->renderer, surface);
	}*/


	//int iW, iH;
	//SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);


	//SDL_Rect destRect = { x, y, iW, iH };
	//SDL_RenderCopy(g_renderer->renderer, texture, 0, &destRect);

	g_renderer->draw_sprite(background, x, y, scale);
	g_renderer->draw_text(name.c_str(), x + int(4.f * scale), y + int(2.f * scale), int(24.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));
	g_renderer->draw_text(description.c_str(), x + int(4.f * scale), y + int(293.f * scale), int(18.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));

	g_renderer->draw_sprite(picture, x + int(4.0f * scale), y + int(41.f * scale), scale);

}
