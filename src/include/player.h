#pragma once

#include "types.h"
#include "card.h"
#include <list>
#include <vector>
#include <deque>
class Player {
public:
	bool ai;

	std::list<u64> hand;
	std::vector<u64> deck;
	std::list<Card> on_board;
	std::list<u64> discarded;

	Player();

	void shuffle();
	u64 draw();
};