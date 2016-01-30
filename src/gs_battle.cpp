
#include "gs_battle.h"
#include "con_vars.h"
#include "audio.h"
#include "database.h"

#include "SDL2/SDL.h"

BattleState::BattleState(Card* a, Card* b) {
	card_a = a;
	card_b = b;
}

void BattleState::init() {
	//monster_a.load(g_renderer->renderer, card_a.picture);
	//monster_b.load(g_renderer->renderer, "assets/yellow monster.agi");

	int screen_height = g_renderer->height;
	int screen_width = g_renderer->width;

	monster_a_position.x = float(screen_width / 2);
	monster_a_position.y = float(screen_height / 2);
}


void BattleState::shutdown() {
	
}

void BattleState::update() {
	static u64 last_time;
	static u64 this_time;

	last_time = this_time;
	this_time = SDL_GetPerformanceCounter();

	u64 performance_frequency = SDL_GetPerformanceFrequency();
	double delta_time = double(double((this_time - last_time) * 1000) / performance_frequency);

	card_a->mv_speed = float(card_a->s_mv_speed + card_a->s_mv_speed_boost) * 0.01f;
	card_a->atk_speed = (card_a->s_atk_speed + card_a->s_atk_speed_boost) * 0.01f;

	if (card_a->atk_speed) 1;

	if (g_cvars.b_get("+left")) {
		monster_a_position.x -= float(card_a->mv_speed * delta_time);
	}

	if (g_cvars.b_get("+right")) {
		monster_a_position.x += float(card_a->mv_speed * delta_time);
	}

	if (g_cvars.b_get("+up")) {
		monster_a_position.y -= float(card_a->mv_speed * delta_time);

	}

	if (g_cvars.b_get("+down")){
		monster_a_position.y += float(card_a->mv_speed * delta_time);

	}

	if (card_b->s_defence <= 0) {
		bool* player_a_won = new bool;
		*player_a_won = true;

	}

}

void BattleState::draw() {
	g_renderer->draw_sprite(card_a->picture, int(monster_a_position.x), int(monster_a_position.y), 0.5f);
}