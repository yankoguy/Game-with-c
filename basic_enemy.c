#include "stdafx.h"
#include <SDL.h>
#include "render_obj.h"
#include <malloc.h>
#include "basic_enemy.h"
#include "player.h"
#include "simple_bullet.h"
#include "shooting_enemy.h"
Enemy* create_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type,int low_type, int layer,
	float speed, int health, renderable_obj* target)
{
	renderable_obj* enemy_obj = create_renderable_obj(x, y, w, h, R, B, G, high_type,low_type,layer);

	Enemy* enemy = (Enemy*)(malloc(sizeof(Enemy)));
	enemy->enemy_obj = enemy_obj;
	enemy->speed = speed;
	enemy->health = health;
	enemy->x_speed = 0;
	enemy->y_speed = 0;
	enemy->affect_hit_timer = 0;
	enemy->affect_time = 0;
	enemy->target = target;
	enemy->bullet_hit_type = -1;
	enemy->enemy_obj->parent = enemy;
	return enemy;
}

void enemy_take_hit(int damage, Enemy* enemy,float affect_time,int bullet_hit_type)
{
	enemy->health -= damage;
	if (enemy->health <= 0) {
		enemy->enemy_obj->dead = 1;
	}
	else {
		if (affect_time != 0) 
		{ //set new affect
			bullet_shock_affect(enemy, affect_time, bullet_hit_type);
		}
	}
}

static void enemy_walk_to_target(Enemy* enemy,float delta_time){
	int x_offset = enemy->enemy_obj->rect->x - enemy->target->rect->x;
	int y_offset = enemy->enemy_obj->rect->y - enemy->target->rect->y;

	double sum = abs(x_offset) + abs(y_offset);
	enemy->x_speed += enemy->speed*delta_time*(x_offset / sum);
	enemy->y_speed += enemy->speed*delta_time*(y_offset / sum);

	if (abs((int)enemy->x_speed) >= 1) {
		enemy->enemy_obj->rect->x -= (int)(enemy->x_speed);
		enemy->x_speed -= (int)(enemy->x_speed);
	}

	if (abs((int)enemy->y_speed) >= 1) {
		enemy->enemy_obj->rect->y -= (int)(enemy->y_speed);
		enemy->y_speed -= (int)(enemy->y_speed);
	}
}

void enemy_movment(Enemy* enemy, float delta_time, float distane_until_stop) {
	//set distane_until_stop to zero if you want him to keep walking
	double distance_to_target = sqrt(pow(enemy->enemy_obj->rect->x - enemy->target->rect->x,2) + pow(enemy->enemy_obj->rect->y - enemy->target->rect->y,2));
	if (distance_to_target > distane_until_stop) {
		enemy_walk_to_target(enemy, delta_time);
	}
}

void enemy_deal_dmg(Enemy* enemy, int damage) {
	player_take_damage((Player*)enemy->target->parent, damage);
}


void apply_enemy_affect(Enemy* enemy) {
	if (enemy->is_on_affect) {
		switch (enemy->bullet_hit_type)
		{
		case SHOCK_BULLET_PLAYER:
			enemy->speed = 0;
			break;
		default:
			break;
		}
	}
}

void update_enemy_timers(Enemy* enemy, float delta_time) {
	enemy->affect_hit_timer += delta_time / 60.0f;
	if (enemy->affect_hit_timer >= enemy->affect_time) {
		bullet_reset_shock_affect(enemy);
	}
}

