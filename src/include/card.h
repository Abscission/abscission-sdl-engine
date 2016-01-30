#pragma once

#include <string>
#include "sprite.h"

const int card_size_x = 384;
const int card_size_y = 512;

enum card_type {
	ct_monster,
	ct_equipment,
	ct_potion
};

enum equipment_effect {
	e_attackboost = 1 << 0,
	e_defenceboost = 1 << 1,
	e_agiboost = 1 << 2
};

class Card {
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	float surface_scale = 0.0f;

	static Image card_template_monster;
	static Image card_template_equip;

public:
	Card(std::string name, std::string description, int attack = 400, int defence = 200, int atk_speed = 200, int mv_speed = 200, card_type = ct_monster);

	std::string name;
	std::string description;
	Image picture;
	card_type type;
	equipment_effect e;

	//monster card stats
	int s_attack;
	int s_defence;
	int s_mv_speed;
	int s_atk_speed;

	//equipment stats
	int attack_boost;
	int defence_boost;
	int s_mv_speed_boost;
	int s_atk_speed_boost;

	float mv_speed;
	float atk_speed;


	void attack(Card& other);
	void render(int x, int y, float scale, bool flip = false);
};
