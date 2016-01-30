#pragma once

#include "game_state.h"

enum turn_phase {
	TURN_PHASE_DRAW,
	TURN_PHASE_CARD,
	TURN_PHASE_ATTACK,
	TURN_PHASE_END
};

enum target_mode {
	TARGET_OWN_HAND,
	TARGET_OWN_FIELD,
	TARGET_ENEMY_HAND,
	TARGET_ENEMY_FIELD
};

class CardState : public GameState {
private:
	Player player_a;
	Player player_b;

	bool player_turn;
	static Image card_back;

	Image background;

	turn_phase phase;
	target_mode t_mode;

	u64* hand_card = 0;
	Card* hand_card_c = 0;

	Card* player_a_monster_battle;
	Card* player_b_monster_battle;


	int hand_card_selected = -1;
	int field_card_selected = -1;

	bool in_battle;

public:
	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};