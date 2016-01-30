#include "game_state.h"

<<<<<<< HEAD
size_t GameState::register_game_state(GameState * G) {
	states.push_back(G);
	return states.size() - 1;
=======
std::deque<GameState*> GameState::gamestate_queue;

void GameState::create_game_state(GameState * G) {
	gamestate_queue.push_back(G);
	G->init();
>>>>>>> 4730a19a0e50164c54e2d7df0993e5982f4ab2f0
}

void GameState::close_current_state(void* ret) {
	gamestate_queue.back()->shutdown();
	gamestate_queue.pop_back();
	gamestate_queue.back()->returned = ret;
}
