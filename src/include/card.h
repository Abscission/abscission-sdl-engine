#pragma once

#include <string>
#include "sprite.h"

const int card_size_x = 324;
const int card_size_y = 512;


class Card {
private:
	//card stats
	int s_attack;
	int s_defence;
	int s_agility;

	SDL_Surface* surface;
	SDL_Texture* texture;
	float surface_scale = 0.0f;
public:
	Card(std::string name, std::string description);

	std::string name;
	std::string description;
	Image picture;

	void attack(Card& other);
	void render(int x, int y, float scale);
};
