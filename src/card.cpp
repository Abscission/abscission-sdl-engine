
#include <sstream>

#include "card.h"
#include "game_state.h"
#include "renderer.h"

Card::Card(std::string name, std::string description, int attack, int defence, int atk_speed, int mv_speed, card_type t) {
	this->name = name;
	this->description = description;

	s_attack = attack;
	s_defence = defence;
	s_atk_speed = atk_speed;
	s_mv_speed = mv_speed;

	type = t;
}

void Card::attack(Card& other) {
	//GameState::change_game_state(2);
	other.name.c_str();
}

void Card::render(int x, int y, float scale, bool flip) {
	if (!card_template_monster.loaded) {
		card_template_monster.load(g_renderer->renderer, "assets/card template monster.agi");
	}

	if (!card_template_equip.loaded) {
		card_template_equip.load(g_renderer->renderer, "assets/card template equipment.agi");
	}

	Image& background = type == ct_monster ? card_template_monster : card_template_equip;

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

	std::stringstream attk;
	std::stringstream def;
	std::stringstream agi;

	attk << s_attack;
	def << s_defence;
	agi << s_agility;

	if (flip) {
		g_renderer->draw_sprite(background, x, y, scale, 180);
		g_renderer->draw_sprite(picture, x + int(4.0f * scale), y + int(card_size_y * scale) - int(246 * scale) - int(41.f * scale), scale, 180);

		g_renderer->draw_text(name.c_str(), x + int(card_size_x * scale) - int(4.f * scale), y + int(card_size_y * scale) - int(26.f * scale), int(24.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale + 0.5), true, ALIGN_RIGHT);

		if (type == ct_monster) {
			g_renderer->draw_text(attk.str().c_str(), x + int(card_size_x * scale) - int(45.f * scale), y + int(13.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale), true, ALIGN_RIGHT);
			g_renderer->draw_text(def.str().c_str(), x + int(card_size_x * scale) - int(177.f * scale), y + int(13.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale), true, ALIGN_RIGHT);
			g_renderer->draw_text(agi.str().c_str(), x + int(card_size_x * scale) - int(312.f * scale), y + int(13.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale), true, ALIGN_RIGHT);
		}
	}
	else {
		g_renderer->draw_sprite(background, x, y, scale);
		g_renderer->draw_sprite(picture, x + int(4.0f * scale), y + int(41.f * scale), scale);

		g_renderer->draw_text(name.c_str(), x + int(4.f * scale), y + int(2.f * scale), int(24.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));
		g_renderer->draw_text(description.c_str(), x + int(4.f * scale), y + int(293.f * scale), int(18.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));

		if (type == ct_monster) {
			g_renderer->draw_text(attk.str().c_str(), x + int(45.f * scale), y + int(card_size_y * scale) - int(52.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));
			g_renderer->draw_text(def.str().c_str(), x + int(177.f * scale), y + int(card_size_y * scale) - int(52.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));
			g_renderer->draw_text(agi.str().c_str(), x + int(312.f * scale), y + int(card_size_y * scale) - int(52.f * scale), int(28.f * scale), SDL_Color{ 255,255,255,255 }, int(380.f * scale));
		}

	}
}


Image Card::card_template_equip;
Image Card::card_template_monster;