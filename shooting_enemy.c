#include "stdafx.h"
#include "basic_enemy.h"
#include "shooting_enemy.h"
#include "basic_gun.h"

Shooting_Enemy* create_shooting_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type, int layer,
	all_renderable_objs* array_of_obj_to_render,float speed, int health, renderable_obj* target, float dis_until_stop, int shoot_damage)
{	

	Shooting_Enemy* shooting_enemy = (Shooting_Enemy*)(malloc(sizeof(Shooting_Enemy)));
	Enemy* enemy = create_enemy(x, y, w, h, R, B, G, high_type, SHOOTING_ENEMY, layer, speed, health, target);
	enemy->enemy_obj->parent = shooting_enemy;
	shooting_enemy->self = enemy;
	shooting_enemy->shoot_damage = shoot_damage;
	shooting_enemy->dis_until_stop = dis_until_stop;
	shooting_enemy->shooting_enemy_gun = create_gun(x, y , 8, 8, 44, 22, 123, GUN, NO_TYPE, layer + 1, 1.0f, NORMAL_BULLET_SHOOTING_ENEMIE, -1, -1,enemy->enemy_obj, SHOOTING_ENEMY,2,2);
	add_render_obj(shooting_enemy->shooting_enemy_gun->gun_obj, array_of_obj_to_render);

	return shooting_enemy;
}

void shooting_enemy_shoot(Shooting_Enemy* enemy, all_renderable_objs* array_of_obj_to_render){
	int array_of_layers_bullet_collide_with[] = { PLAYER };
	gun_shoot(enemy->shooting_enemy_gun, array_of_obj_to_render, array_of_layers_bullet_collide_with,1,enemy->self->target->rect->x, enemy->self->target->rect->y);
}

void destroy_shooting_enemy_gun(Shooting_Enemy* enemy) {
 	free(enemy->shooting_enemy_gun);
	enemy->shooting_enemy_gun = NULL;
}