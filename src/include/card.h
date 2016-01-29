#pragma once

#include <string>
#include "sprite.h"

class Card {
private:
	//card stats
	int s_attack;
	int s_defence;
	int s_agility;

public:
	Card(std::string name, std::string description);

	std::string name;
	std::string description;
	Image picture;

	void attack(Card& other);
	void render(int x, int y, float scale);
};
