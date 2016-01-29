#pragma once

#include "game_state.h"

class MenuState : public GameState {
public:
	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};