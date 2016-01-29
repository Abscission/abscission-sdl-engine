
#include "game_state.h"
#include "database.h"
#include "con_vars.h"

void CardState::init() {
	player_a = Player();
	player_b = Player();
	player_b.ai = true;
}

void CardState::shutdown() {

}

void CardState::update() {
	if (player_turn) {
		if (g_cvars.b_get("+end")) player_turn = false;
	}
	else {
		if (player_b.ai) {
			//do an ai turn

			//draw
			player_b.draw();

			//play cards
			//for (auto card = player_b.on_board.begin(), end = player_b.on_board.end(); card != end; ++card) {
			for (auto& card : player_b.on_board) {
				Card c = g_card_db.get(card);

				//check if card is playable

				//if so, play it
				player_b.hand.remove(card);
				player_b.on_board.push_back(card);
				if (1) break;
			}

			//attack

			//play cards again?

			//end
			player_turn = !player_turn;
		}

	}
}

void CardState::draw() {
	int i = 0;

	for (auto card = player_b.on_board.begin(), end = player_b.on_board.end(); card != end; ++card) {
		Card c = g_card_db.get(*card);
		c.render(i * 250, 10, 0.4f);
	}

	i = 0;

	for (u64 card : player_a.hand) {
		Card c = g_card_db.get(card);
		c.render(i++ * 200, 200, 0.5f);
	}
}