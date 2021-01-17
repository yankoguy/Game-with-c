#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include "render_obj.h"

typedef enum {
	EXPLOSIVE_ENEMY,
	SHOOTING_ENEMY
}enemy_type;


typedef struct Enemy
{
	float speed;
	int health;
	float x_speed;
	float y_speed;
	float affect_hit_timer;
	float affect_time;
	int bullet_hit_type;
	int is_on_affect; //1 if the enemy got hit by bullet with affect and he still on the bullet affect and 0 for not 
	renderable_obj* target;
	renderable_obj* enemy_obj;
}Enemy;

Enemy* create_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type,int low_type, int layer,
	float speed, int health,renderable_obj* target);

void enemy_take_hit(int damage, Enemy* enemy, float affect_timer,int bullet_hit_type);
void apply_enemy_affect(Enemy* enemy);
void enemy_deal_dmg(Enemy* enemy,int damage);
void enemy_movment(Enemy* enemy, float delta_time, float distane_until_stop);
void update_enemy_timers(Enemy* enemy,float delta_time);
#endif 
