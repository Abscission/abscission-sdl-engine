#include "player.h"
#include <random>
#include <algorithm>

Player::Player() {
	deck.push_back(1);
	deck.push_back(0);
	deck.push_back(0);
	deck.push_back(1);
	deck.push_back(2);
	deck.push_back(0);

	shuffle();

	draw();
	draw();
	draw();
	draw();
	draw();

}

void Player::shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(deck.begin(), deck.end(), g);
}

u64 Player::draw() {
	if (deck.size()) {
		u64 ret = deck.back();
		deck.pop_back();
		hand.push_back(ret);
		return ret;
	}
	return 0xffffffffffffffff;
}