#pragma once

#include <vector>
#include "player.h"


class GameState {
public:
	static GameState* current;
	static std::vector<GameState*> states;

public:
	static size_t register_game_state(GameState* G);
	static void change_game_state(int i);

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
};

