#include "game_state.h"


void GameState::register_game_state(GameState * G) {
	states.push_back(G);
	
}

void GameState::change_game_state(int i) {
	if (current) current->shutdown();
	current = states[i];
	current->init();
}

GameState* GameState::current;
std::vector<GameState*> GameState::states;
