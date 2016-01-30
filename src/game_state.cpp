#include "game_state.h"


std::deque<GameState*> GameState::gamestate_queue;

void GameState::create_game_state(GameState * G) {
	gamestate_queue.push_back(G);
	G->init();
}

void GameState::close_current_state(void* ret) {
	gamestate_queue.back()->shutdown();
	gamestate_queue.pop_back();
	gamestate_queue.back()->returned = ret;
}
