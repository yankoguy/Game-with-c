#ifndef BULLET_H
#define BULLET_H

#include "render_obj.h"
#include "basic_enemy.h"

#define SHOCK_TIME 0.5f
#define NO_AFFECT_TIMER 0.0f

enum BULLET_TYPE {
	NORMAL_BULLET_PLAYER,
	NORMAL_BULLET_SHOOTING_ENEMIE,

	SHOCK_BULLET_PLAYER,
};

typedef struct
{
	float speed;
	float life_time;
	int starting_x;
	int starting_y;
	double x_speed; //the speed in x axis
	double y_speed;//the speed in y axis
	double x_counter; //the counter of how much bullet need to move in x (count until it bigger or qeual to 1 and then reduce 1)
	double y_counter; //the counter of how much bullet need to move in y (count until it bigger or qeual to 1 and then reduce 1)
	int y_target;
	int x_target;
	int damage;
	double shoot_angle;
	int array_to_collide_with[20];
	float affect_time;

	renderable_obj* bullet_obj;
}Bullet;


Bullet* create_bullet(int x, int y, int w, int h, int R, int B, int G, int high_obj_type,int low_obj_type, int layer, int array_to_collide_with[],
	int number_of_types_to_collide_with,int x_target,int y_target ,float speed, int dmg, float life_time,float affect_time);
void bullet_movment(Bullet* bullet, float delta_time);
void update_bullet_timers(Bullet* bullet, float delta_time);
void check_bullet_timers(Bullet** bullet, all_renderable_objs* all_rects_to_render);
void bullet_check_hit(Bullet** bullet, all_renderable_objs* array_of_obj_to_render);

void bullet_shock_affect(Enemy* enemy_to_shock, float affect_time, int bullet_hit_type);

#endif