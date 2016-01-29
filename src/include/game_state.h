#pragma once

#include <vector>
#include "player.h"


class GameState {
public:
	static GameState* current;
	static std::vector<GameState*> states;

public:
	static void register_game_state(GameState* G);
	static void change_game_state(int i);

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
};

class CardState : public GameState {
private:
	Player player_a;
	Player player_b;

	bool player_turn;

public:
	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};