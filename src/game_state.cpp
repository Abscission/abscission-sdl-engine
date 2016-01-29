#include "game_state.h"


size_t GameState::register_game_state(GameState * G) {
	states.push_back(G);
	return states.size() - 1;
}

void GameState::change_game_state(int i) {
	if (current) current->shutdown();
	current = states[i];
	current->init();
}

GameState* GameState::current;
std::vector<GameState*> GameState::states;
