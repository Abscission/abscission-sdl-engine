#pragma once

#include "card.h"
#include "renderer.h"
#include "game_state.h"
#include "types.h"

class BattleState : public GameState {
	Card* card_a;
	Card* card_b;

	Image monster_a;
	Image monster_b;

	v2 monster_a_position;
	v2 monster_b_position;

	SDL_Color bg;

public:
	BattleState(Card* a, Card* b);

	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};