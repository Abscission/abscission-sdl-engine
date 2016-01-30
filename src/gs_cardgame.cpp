
#include "gs_cardgame.h"
#include "gs_battle.h"

#include "console.h"
#include "database.h"
#include "con_vars.h"
#include "renderer.h"
#include "input.h"
#include "abscission_math.h"
#include "audio.h"

void CardState::init() {
	player_a = Player();
	player_b = Player();
	player_b.ai = true;

	phase = TURN_PHASE_DRAW;

	card_back.load(g_renderer->renderer, "assets/card back.agi");
	background.load(g_renderer->renderer, "assets/wood.agi");

	g_sound_manager.play_file_loop("assets/Town_-_Quiet_Country_Village.mp3");
}

void CardState::shutdown() {
	
}

void CardState::update() {

	if (in_battle) {
		//just finished a battle

		phase = TURN_PHASE_DRAW;
		player_turn = !player_turn;

		bool player_won = *(bool*)GameState::returned;
		if (player_won) {
			console.run_command("echo you won\n");
			//player_b.on_board.erase(player_b.on_board.begin() + i);
		}
	}

	static bool end_was_down;
	static bool draw_was_down;

	if (player_turn) {
		if (g_cvars.b_get("+end")) {
			if (!end_was_down) {
				phase = TURN_PHASE_DRAW;
				player_turn = false;
			}
			
			end_was_down = true;
		}
		else {
			end_was_down = false;
		}

		if (phase == TURN_PHASE_DRAW) {
			if (g_cvars.b_get("+draw")) {
				if (!draw_was_down) player_a.draw();
				draw_was_down = true;
				phase = TURN_PHASE_CARD;
				t_mode = TARGET_OWN_HAND;
			}
			else {
				draw_was_down = false;
			}
		}
		if (phase == TURN_PHASE_CARD) {
			if (g_input_manager.click_thisframe) {
				if (t_mode == TARGET_OWN_HAND) {
					int i = 0;
					for (auto card_id = player_a.hand.begin(), end = player_a.hand.end(); card_id != end; ++card_id) {
						SDL_Rect r = { 20 + int(card_size_x * 0.5 + 20) * i , g_renderer->height - 276, int(card_size_x * 0.5), int(card_size_y * 0.5) };
						if (is_mouse_over(r)) {
							Card _card = g_card_db.get(*card_id);

							if (_card.type == ct_monster) {
								player_a.hand.erase(card_id);
								player_a.on_board.push_back(_card);

								phase = TURN_PHASE_ATTACK;
								t_mode = TARGET_OWN_FIELD;
							}
							else if (_card.type == ct_equipment) {
								hand_card_selected = i;
								hand_card = &*card_id;
								t_mode = TARGET_OWN_FIELD;
							}
							break;

						}
						i++;
						hand_card_selected = -1;
					}
				}
				else if (t_mode == TARGET_OWN_FIELD) {
					int i = 0;
					for (auto card_id = player_a.on_board.begin(), end = player_a.on_board.end(); card_id != end; ++card_id) {
						SDL_Rect card_hitbox = SDL_Rect{ 20 + i * int(card_size_x * 0.5f + 20), g_renderer->height - 276 - 20 - int(card_size_y * 0.5f), card_size_x / 2, card_size_y / 2 };
						if (is_mouse_over(card_hitbox)) {
							//the card has been clicked on
							Card _hand_card = g_card_db.get(*hand_card);
							Card* _field_card = &*card_id;

							if ((_hand_card.e & e_attackboost) == e_attackboost) {
								//boost attack
								_field_card->s_attack += _hand_card.attack_boost;
							}

							auto it = player_a.hand.begin();
							for (int j = 0; j < hand_card_selected; j++) {
								it++;
							}
							player_a.hand.erase(it);
							hand_card_selected = -1;

							phase = TURN_PHASE_ATTACK;
							t_mode = TARGET_OWN_FIELD;
						}
						i++;
					}
				}
			}
		}

		if (phase == TURN_PHASE_ATTACK) {
			if (g_input_manager.click_thisframe) {
				if (t_mode == TARGET_OWN_FIELD) {
					int i = 0;
					for (auto card = player_a.on_board.begin(), end = player_a.on_board.end(); card != end; ++card) {
						SDL_Rect r = { 20 + i * int(card_size_x * 0.5f + 20), g_renderer->height - 276 - 20 - int(card_size_y * 0.5f), card_size_x / 2, card_size_y / 2 };
						if (is_mouse_over(r)) {

							if (card->type == ct_monster) {
								field_card_selected = i;
								hand_card_c = &*card;

								t_mode = TARGET_ENEMY_FIELD;
							}

							break;
						}
						i++;
						field_card_selected = -1;
					}
				}
				else if (t_mode == TARGET_ENEMY_FIELD) {
					int i = 0;
					for (auto card_id = player_b.on_board.begin(), end = player_b.on_board.end(); card_id != end; ++card_id) {
						SDL_Rect card_hitbox = SDL_Rect{ 20 + i * int(card_size_x * 0.5f + 20), card_size_y / 4 + 20, card_size_x / 2, card_size_y / 2 };
						if (is_mouse_over(card_hitbox)) {
							//the card has been clicked on
							Card* _own_card = hand_card_c;
							Card* _enemy_card = &*card_id;

							in_battle = true;

							//TODO: OPEN A BATTLE
							BattleState* bs = new BattleState(_own_card, _enemy_card);
							GameState::create_game_state(bs);
							break;

							/*
							auto it = player_a.hand.begin();
							for (int j = 0; j < hand_card_selected; j++) {
								it++;
							}
							player_a.hand.erase(it);
							field_card_selected = -1;
							
							player_turn = false;
							phase = TURN_PHASE_DRAW;
							t_mode = TARGET_OWN_HAND;
							break;
							*/
						}
						i++;
					}
				}
			}
		}
	}
	else {
		if (player_b.ai) {
			//do an ai turn

			//draw
			player_b.draw();

			//play cards
			for (auto card = player_b.hand.begin(), end = player_b.hand.end(); card != end; ++card) {
				Card crd = g_card_db.get(*card);

				//check if card is playable
				

				if (crd.type == ct_monster) {
					//if so, play it
					player_b.hand.erase(card);
					player_b.on_board.push_back(crd);
					break;
				}
			}

			//attack

			//play cards again?

			//end
			phase = TURN_PHASE_DRAW;
			player_turn = true;
		}

	}
}

void CardState::draw() {
	g_renderer->draw_sprite(background, 0, 0, 1.0f);

	const char * phase_name;
	if (phase == TURN_PHASE_DRAW) phase_name = "Draw Phase";
	else if (phase == TURN_PHASE_CARD) phase_name = "Card Phase";
	else if (phase == TURN_PHASE_ATTACK) phase_name = "Attack Phase";
	else if (phase == TURN_PHASE_END) phase_name = "End Phase";
	else phase_name = "Unkown Phase";

	g_renderer->draw_rect(g_renderer->width - 500, 20, 480, 32, SDL_Color{ 101,154,252,255 });
	g_renderer->draw_text(phase_name, g_renderer->width - 498, 22, 28);

	const char * target_name;
	if (t_mode == TARGET_OWN_HAND) target_name = "Own Hand";
	else if (t_mode == TARGET_OWN_FIELD) target_name = "Own Field";
	else if (t_mode == TARGET_ENEMY_HAND) target_name = "Opponent Hand";
	else if (t_mode == TARGET_ENEMY_FIELD) target_name = "Opponent Field";
	else target_name = "Unkown Phase";

	g_renderer->draw_rect(g_renderer->width - 500, 60, 480, 32, SDL_Color{ 101,154,252,255 });
	g_renderer->draw_text(target_name, g_renderer->width - 498, 62, 28);

	g_renderer->draw_rect(g_renderer->width - 300, 100, 280, 300, SDL_Color{ 255, 255, 255, 60 });

	int i = 0;

	//Draw the played cards for player a
	for (auto card = player_a.on_board.begin(), end = player_a.on_board.end(); card != end; ++card) {
		if (field_card_selected == i) {
			SDL_Rect outline_rect = { 20 + i * int(card_size_x * 0.5f + 20), g_renderer->height - 276 - 20 - int(card_size_y * 0.5f), int(card_size_x / 2) + 6, int(card_size_y / 2) + 6 };
			g_renderer->draw_rect(outline_rect.x, outline_rect.y, outline_rect.w, outline_rect.h, SDL_Color{ 0, 255, 0, 255 });
		}

		(*card).render(20 + i * int(card_size_x * 0.5f + 20), g_renderer->height - 276 - 20 - int(card_size_y * 0.5f), 0.5f);
		i++;
	}

	i = 0;

	//Draw the played cards for player b
	for (auto card = player_b.on_board.begin(), end = player_b.on_board.end(); card != end; ++card) {
		Card c = *card;
		c.render(20 + i * int(card_size_x * 0.5f + 20), card_size_y / 4 + 20 , 0.5f, true);
		i++;
	}

	i = 0;

	//Draw the players hand
	for (u64 card : player_a.hand) {
		Card c = g_card_db.get(card);

		float scale = .5f;

		SDL_Rect r = { 20 + int(card_size_x * scale + 20) * i++ , g_renderer->height - 276, int(card_size_x * scale), int(card_size_y * scale) };

		if (g_input_manager.mouse_x > r.x && g_input_manager.mouse_x < r.x + r.w &&
			g_input_manager.mouse_y > r.y && g_input_manager.mouse_y < r.y + r.h) {
			
			scale = 0.55f;
			r.x -= int((r.h * scale) - (r.h * .5f));
			r.y -= int((r.w * scale) - (r.w * .5f));
		}

		if (hand_card_selected == i) {
			SDL_Rect outline_rect = { 17 + int(card_size_x * scale + 20) * i , g_renderer->height - 279, int(card_size_x * scale) + 6, int(card_size_y * scale) + 6 };
			g_renderer->draw_rect(outline_rect.x, outline_rect.y, outline_rect.w, outline_rect.h, SDL_Color{ 0, 255, 0, 255 });
		}
		c.render(r.x, r.y, scale);
	}

	//Draw the enemies hand
	size_t number_enemy_cards = player_b.hand.size();

	for (i = 0; i < number_enemy_cards; i++) {
		float scale = .5f;

		g_renderer->draw_sprite(card_back, 20 + int((card_size_x * scale + 20) * i), -(int(card_size_y * scale) / 2), scale);
	}
}

Image CardState::card_back;