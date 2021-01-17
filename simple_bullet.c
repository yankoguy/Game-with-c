#include "stdafx.h"
#include "simple_bullet.h"
#include "render_obj.h"
#include "basic_setup.h"
#include "basic_enemy.h"
#include "useful_function.h"
#include "exploading_enemy.h"
#include "shooting_enemy.h"
#include "player.h"

Bullet* create_bullet(int x, int y, int w, int h, int R, int B, int G, int high_obj_type,int low_obj_type, int layer, int array_to_collide_with[],
	int number_of_types_to_collide_with,int x_target, int y_target, float speed, int dmg, float life_time,float affect_time)
{
	renderable_obj* bullet_obj = create_renderable_obj(x, y, w, h, R, B, G, high_obj_type,low_obj_type,layer);
	Bullet* bullet = (Bullet*)(malloc(sizeof(Bullet)));
	bullet->bullet_obj = bullet_obj;
	bullet->speed = speed;
	bullet->damage = dmg;
	bullet_obj->parent = bullet;
	bullet->life_time = life_time;
	bullet->affect_time = affect_time;
	bullet->starting_x = x;
	bullet->starting_y = y;
	memcpy(bullet->array_to_collide_with, array_to_collide_with, sizeof array_to_collide_with);
	bullet->x_target = x_target;
	bullet->y_target = y_target;
	bullet->x_counter = 0;
	bullet->y_counter = 0;
	int sum_of_distance = abs(x_target - x) + abs(y_target - y);
	bullet->x_speed = (x_target - x*1.0) / sum_of_distance; //*1.0 for making it float
	bullet->y_speed = (y_target - y*1.0) / sum_of_distance; //*1.0 for making it float
	return bullet;
}





void update_bullet_timers(Bullet* bullet,float delta_time) {
	if (bullet != NULL) {
		bullet->life_time -= delta_time / 60.0f;
	}
}
void check_bullet_timers(Bullet** bullet, all_renderable_objs* all_rects_to_render) {
	if (*bullet != NULL) {
		if ((*bullet)->life_time <= 0) {
			(*bullet)->bullet_obj->dead = 1;
		}
	}
}

static float yaxis_movemnt_fix(int angle)// there is a little deviation in the bullet movment so this function fix it
{
	const float deviation = 1.05f;

	if (angle > 45.0) {
		return 1.0f / deviation;
	}
	return deviation;
}



void bullet_check_hit(Bullet** bullet, all_renderable_objs* array_of_obj_to_render) {
	if (*bullet != NULL) {
		renderable_obj** all_collisions = get_colliders((*bullet)->bullet_obj->rect, array_of_obj_to_render, 1, (*bullet)->array_to_collide_with, 1);
		if (all_collisions != NULL) {
			for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
			{
				if (all_collisions[i] == NULL) {
					break; //in all collistion all the members are one after the other so if one of them is null it is mean we are at pass the last not null member
				}
				switch (all_collisions[i]->high_object_type)
				{
				case BASIC_ENEMY:
				
					switch (all_collisions[i]->low_object_type)
					{
					case EXPLOSIVE_ENEMY:
					{
						Exploading_Enemy* exploading_Enemy = (Exploading_Enemy*)(all_collisions[i]->parent);
						enemy_take_hit((*bullet)->damage, exploading_Enemy->self,(*bullet)->affect_time,(*bullet)->bullet_obj->low_object_type);
						break;
					}

					case SHOOTING_ENEMY: 
					{
						Shooting_Enemy* shooting_enemy = (Shooting_Enemy*)(all_collisions[i]->parent);
						enemy_take_hit((*bullet)->damage, shooting_enemy->self, (*bullet)->affect_time, (*bullet)->bullet_obj->low_object_type);
						break;
					}
					}
					break;

				
				case PLAYER: 
				{
					Player* player = (Player*)all_collisions[i]->parent;
					player_take_damage(player, (*bullet)->damage);
					break;
				}
				
				}
				break;
			}
			(*bullet)->bullet_obj->dead = 1;
		}
		free(all_collisions);
	}
}



void bullet_movment(Bullet* bullet, float delta_time) {
	if (bullet != NULL) {
		bullet->x_counter += bullet->x_speed*bullet->speed*delta_time;
		bullet->y_counter += bullet->y_speed*bullet->speed*delta_time;

		if (abs((int)bullet->x_counter) >= 1) {
			bullet->bullet_obj->rect->x += (int)((bullet->x_counter));
			bullet->x_counter -= (int)((bullet->x_counter));
		}

		if (abs((int)bullet->y_counter) >= 1) {
			bullet->bullet_obj->rect->y += (int)(bullet->y_counter);
			bullet->y_counter -= (int)((bullet->y_counter));

		}
	}
}


void bullet_shock_affect(Enemy* enemy_to_shock, float affect_time, int bullet_hit_type) {
	enemy_to_shock->affect_time = affect_time;
	enemy_to_shock->affect_hit_timer = 0;
	enemy_to_shock->bullet_hit_type = bullet_hit_type;
	enemy_to_shock->is_on_affect = 1;
	switch (enemy_to_shock->enemy_obj->low_object_type)
	{
	case SHOOTING_ENEMY:
	{
		Shooting_Enemy* shooting_enemy = (Shooting_Enemy*)enemy_to_shock->enemy_obj->parent;
		shooting_enemy->shooting_enemy_gun->is_shoot = 0;
	}
	default:
		break;
	}
}

void bullet_reset_shock_affect(Enemy* enemy_to_shock) {
	enemy_to_shock->is_on_affect = 0;
	enemy_to_shock->speed = 1;
	switch (enemy_to_shock->enemy_obj->low_object_type)
	{
	case SHOOTING_ENEMY:
	{
		Shooting_Enemy* shooting_enemy = (Shooting_Enemy*)enemy_to_shock->enemy_obj->parent;
		shooting_enemy->shooting_enemy_gun->is_shoot = 1;
	}
	default:
		break;
	}
}