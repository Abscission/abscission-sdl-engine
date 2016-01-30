#pragma once

#include "game_state.h"

class OptionState : public GameState {
	Image background;
public:
	virtual void init() final;
	virtual void shutdown() final;

	virtual void update() final;
	virtual void draw() final;
};                     