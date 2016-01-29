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

	g_renderer->draw_sprite(background, x, y, scale);
	g_renderer->draw_text(name.c_str(), x + int(4.f * scale), y + int(2.f * scale), int(24.f * scale));
	g_renderer->draw_text(description.c_str(), x + int(4.f * scale), y + int(293.f * scale), int(18.f * scale));

	g_renderer->draw_sprite(picture, x + int(4.0f * scale), y + int(41.f * scale), scale);
}
