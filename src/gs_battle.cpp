
#include "gs_battle.h"
#include "con_vars.h"
#include "audio.h"
#include "database.h"
#include "abscission_math.h"

#include "SDL2/SDL.h"

#include <malloc.h>
#include <list>
#include <math.h>

struct Bullet {
	v2 position;
	v2 velocity;
	bool player;
};

static std::list<Bullet*> bullets;

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
	monster_a_position.y = float((screen_height / 4) * 3);

	monster_b_position.x = float(screen_width / 2);
	monster_b_position.y = float(screen_height / 4);


	bg = g_renderer->get_background_color();
	g_renderer->set_background_color(SDL_Color{ 80, 80, 80, 255 });
}


void BattleState::shutdown() {
	g_renderer->set_background_color(bg);
}

bool isOffscreen(Bullet* b){
	if (b->position.x < 0 || b->position.x > g_renderer->width ||
		b->position.y < 0 || b->position.y > g_renderer->height) {
		free(b);
		return true;
	}
	else {
		return false;
	}
}

void BattleState::update() {
	static u64 last_time = SDL_GetPerformanceCounter();
	static u64 this_time = SDL_GetPerformanceCounter();

	last_time = this_time;
	this_time = SDL_GetPerformanceCounter();

	u64 performance_frequency = SDL_GetPerformanceFrequency();
	double delta_time = double(double((this_time - last_time) * 1000) / performance_frequency);

	card_a->mv_speed = float(card_a->s_mv_speed + card_a->s_mv_speed_boost) * 0.005f;
	card_a->atk_speed = (card_a->s_atk_speed + card_a->s_atk_speed_boost) * 0.005f;

	card_b->mv_speed = float(card_b->s_mv_speed + card_b->s_mv_speed_boost) * 0.005f;
	card_b->atk_speed = (card_b->s_atk_speed + card_b->s_atk_speed_boost) * 0.005f;

	if (card_a->atk_speed) 1;

	if (g_cvars.b_get("+left")) {
		monster_a_position.x -= float(card_a->mv_speed * delta_time);
		monster_a_position.x = MAX(monster_a_position.x, 0);
	}

	if (g_cvars.b_get("+right")) {
		monster_a_position.x += float(card_a->mv_speed * delta_time);
		monster_a_position.x = MIN(monster_a_position.x, g_renderer->width - card_a->in_game.width);

	}

	if (g_cvars.b_get("+up")) {
		monster_a_position.y -= float(card_a->mv_speed * delta_time);
		monster_a_position.y = MAX(monster_a_position.y, 0);


	}

	if (g_cvars.b_get("+down")){
		monster_a_position.y += float(card_a->mv_speed * delta_time);
		monster_a_position.y = MIN(monster_a_position.y, g_renderer->height - card_a->in_game.height);

	}

	static double firedelay = 0.0;

	if (firedelay > 0) {
		firedelay -= delta_time;
	}
	else {
		if (g_cvars.b_get("+shoot")) {
			float shoot_offset = float(card_a->in_game.width) / 2 - 8;
			float shoot_angle_offset = g_cvars.b_get("+left") ? -0.5f : 0 + g_cvars.b_get("+right") ? 0.5f : 0;
			float shoot_speed_offset = g_cvars.b_get("+down") ? card_a->mv_speed : 0.f + g_cvars.b_get("+up") ? -card_a->mv_speed : 0.f;

			Bullet* b = (Bullet*)malloc(sizeof(Bullet));
			b->position = monster_a_position;
			b->position.x += shoot_offset;
			b->velocity = { 0 + shoot_angle_offset, -1 };
			b->velocity.y += shoot_speed_offset;
			b->player = true;

			Bullet* b2 = (Bullet*)malloc(sizeof(Bullet));
			b2->position = monster_a_position;
			b2->position.x += shoot_offset;

			b2->velocity = { -0.3827f + shoot_angle_offset, -0.9808f };
			b2->velocity.y += shoot_speed_offset;
			b2->player = true;

			Bullet* b3 = (Bullet*)malloc(sizeof(Bullet));
			b3->position = monster_a_position;
			b3->position.x += shoot_offset;

			b3->velocity = { 0.3827f + shoot_angle_offset, -0.9808f };
			b3->velocity.y += shoot_speed_offset;
			b3->player = true;

			bullets.push_back(b3);
			bullets.push_back(b2);
			bullets.push_back(b);

			firedelay = 200;
		}
	}


	//THIS BE AI NAO

	//MOve?

	static float x = 0;
	static float y = 0;

	if (monster_b_position.x < 400) {
		x = 1;
	}
	else if (monster_b_position.x > 800) {
		x = -1;
	}


	monster_b_position.x += x *float(card_a->mv_speed * delta_time);
	monster_b_position.y += y * float(card_a->mv_speed * delta_time);


	//Sh00t

	static double enemy_firedelay;


	if (enemy_firedelay > 0) {
		enemy_firedelay -= delta_time;
	}
	else {
		float shoot_offset = float(card_b->in_game.width) / 2 - 8;
		
		Bullet* b = (Bullet*)malloc(sizeof(Bullet));
		b->position = monster_b_position;
		b->position.x += shoot_offset;
		b->velocity = { 0, 1 };


		Bullet* b2 = (Bullet*)malloc(sizeof(Bullet));
		b2->position = monster_b_position;
		b2->position.x += shoot_offset;

		b2->velocity = { -0.3827f, 0.9808f };

		Bullet* b3 = (Bullet*)malloc(sizeof(Bullet));
		b3->position = monster_b_position;
		b3->position.x += shoot_offset;

		b3->velocity = { 0.3827f, 0.9808f };

		bullets.push_back(b3);
		bullets.push_back(b2);
		bullets.push_back(b);

		enemy_firedelay = 200;
	}

	if (!g_cvars.b_get("+paused")) {
		for (auto bullet : bullets) {
			bullet->position.x += bullet->velocity.x * (float)delta_time;
			bullet->position.y += bullet->velocity.y * (float)delta_time;

			SDL_Rect Bullet{ int(bullet->position.x), int(bullet->position.y), 16, 16 };
			static SDL_Rect player_a_hitbox{ int(monster_a_position.x), int(monster_a_position.y), int(card_a->in_game.width), int(card_a->in_game.height) };
			static SDL_Rect player_b_hitbox{ int(monster_b_position.x), int(monster_b_position.y), int(card_b->in_game.width), int(card_b->in_game.height) };

			if (bullet->player) {
				if (is_colliding(Bullet, player_b_hitbox)) {
					bool* result = new bool();
					*result = true;
					GameState::close_current_state(result);
				}
			}
			else {

			}

		}
	}

	bullets.remove_if(isOffscreen);
}

void BattleState::draw() {
	static Image bulletImage;
	if (!bulletImage.loaded) {
		bulletImage.load(g_renderer->renderer, "assets/fireball.agi");
	}

	for (auto bullet : bullets) {
		
		double angle = atan(bullet->velocity.x / bullet->velocity.y);
		angle *= (180.0 / 3.1415926);

		if (bullet->velocity.y >= 0) angle = -angle;
		g_renderer->draw_sprite(bulletImage, int(bullet->position.x), int(bullet->position.y), 1.0f, -angle);
	}

	g_renderer->draw_sprite(card_a->in_game, int(monster_a_position.x), int(monster_a_position.y));
	g_renderer->draw_sprite(card_b->in_game, int(monster_b_position.x), int(monster_b_position.y), 1.0f, 180);

}
