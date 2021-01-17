#ifndef RUNNING_ENEMY_H
#define RUNNING_ENEMY_H

#include "stdafx.h"
#include "basic_enemy.h"

#define EXPLOSIOTN_DISTNACE 100
#define EXPLOSIOTN_DAMAGE 500

typedef struct
{
	Enemy* self;
	int is_touching;
	float explision_timer; //timer that track the time in second of the explosion
	float time_until_explod;	//time_until_explod - how much time does it take from collide to start explostion
	float time_to_cancel_explode; //time_to_cancel_explode - how much time does it take from no collide to cancel explode
	float explosion_time;//time it take explode from starting explosion
	int color_holder[3];
	int is_exploding;
}Exploading_Enemy;

Exploading_Enemy* create_running_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type, int layer,
	float speed, int health, renderable_obj* target,float time_until_explod, float time_to_cancel_explode, float explosion_time);

void explosion_enemy_collistion(Exploading_Enemy* exploading_Enemy, all_renderable_objs* array_of_obj_to_render);

void exploding_enemy_pre_expload(Exploading_Enemy* exploading_Enemy, float deltatime);

void exploding_enemy_reset_color(Exploading_Enemy* exploading_Enemy);

void exploda_enemy_start_explode(Exploading_Enemy* exploading_Enemy, float delta_time);

#endif