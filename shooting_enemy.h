#ifndef SHOTTING_ENEMY_H
#define SHOTTING_ENEMY_H


#include "stdafx.h"
#include "basic_enemy.h"
#include "basic_gun.h"

typedef struct {
	Enemy* self;
	Gun* shooting_enemy_gun;
	float dis_until_stop;
	int shoot_damage;
}Shooting_Enemy;


Shooting_Enemy* create_shooting_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type, int layer,
	all_renderable_objs* array_of_obj_to_render,float speed, int health, renderable_obj* target, float dis_until_stop,int shoot_damage);


void shooting_enemy_shoot(Shooting_Enemy* enemy, all_renderable_objs* array_of_obj_to_render);
void destroy_shooting_enemy_gun(Shooting_Enemy* enemy);


#endif 
