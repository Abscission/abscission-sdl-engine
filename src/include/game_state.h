#pragma once

#include <vector>
#include <deque>
#include "player.h"


class GameState {
private:
	void* returned;

public:
	static std::deque<GameState*> gamestate_queue;

	static void create_game_state(GameState* G);
	static void close_current_state(void* ret);

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
};

