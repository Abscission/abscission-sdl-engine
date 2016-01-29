#pragma once

#include <vector>

class GameState {
public:
	//std::vector<GameState*> states;
	static GameState* current;

public:
	//static void register_game_state(GameState* G);
	//static void change_game_state(int i);

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
};

class CardState {
public:
	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};