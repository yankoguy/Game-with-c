#include "stdafx.h"
#include "basic_enemy.h"
#include "exploading_enemy.h"
#include "useful_function.h"
#include "player.h"

Exploading_Enemy* create_running_enemy(int x, int y, int w, int h, int R, int B, int G, int high_type, int layer,
	float speed, int health, renderable_obj* target, float time_until_explod, float time_to_cancel_explode, float explosion_time)
{
	Exploading_Enemy* exploading_Enemy = (Exploading_Enemy*)(malloc(sizeof(Exploading_Enemy)));
	Enemy* enemy = create_enemy(x, y, w, h, R, B, G, high_type, EXPLOSIVE_ENEMY, layer, speed, health, target);
	enemy->enemy_obj->parent = exploading_Enemy;
	exploading_Enemy->self = enemy;
	exploading_Enemy->explision_timer = 0;
	exploading_Enemy->is_touching = 0;
	exploading_Enemy->time_until_explod = time_until_explod;
	exploading_Enemy->time_to_cancel_explode = time_to_cancel_explode;
	exploading_Enemy->explosion_time = explosion_time;
	exploading_Enemy->is_exploding = 0;
	int color[3] = { R,B,G };
	memcpy(exploading_Enemy->color_holder, color, sizeof color);
	return exploading_Enemy;
}



static void exploding_enemy_expload(Exploading_Enemy* exploading_Enemy) {
	//add effect
	if (get_absulute_distance(exploading_Enemy->self->enemy_obj->rect->x, exploading_Enemy->self->enemy_obj->rect->y,
		exploading_Enemy->self->target->rect->x, exploading_Enemy->self->target->rect->y) < EXPLOSIOTN_DISTNACE)
	{	
		player_take_damage((Player*)(exploading_Enemy->self->target->parent), EXPLOSIOTN_DAMAGE);
	}
	exploading_Enemy->self->enemy_obj->dead = 1;
}



void exploda_enemy_start_explode(Exploading_Enemy* exploading_Enemy,float delta_time) {
	exploading_Enemy->explision_timer += delta_time / 60.0f;
	exploading_Enemy->self->enemy_obj->R = 60;
	exploading_Enemy->self->enemy_obj->B = 60;
	exploading_Enemy->self->enemy_obj->G = 60;
	if (exploading_Enemy->explision_timer >= exploading_Enemy->time_until_explod + exploading_Enemy->explosion_time) {
		exploding_enemy_expload(exploading_Enemy);
	}
}


void exploding_enemy_pre_expload(Exploading_Enemy* exploading_Enemy,float delta_time) 
{
	exploading_Enemy->self->enemy_obj->R = 255;
	exploading_Enemy->self->enemy_obj->B = 255;
	exploading_Enemy->self->enemy_obj->G = 255;
	exploading_Enemy->explision_timer += delta_time/60.0f;
	if (exploading_Enemy->explision_timer >= exploading_Enemy->time_until_explod) {
		exploading_Enemy->is_exploding = 1;
	}
}




void exploding_enemy_reset_color(Exploading_Enemy* exploading_Enemy) {
	exploading_Enemy->self->enemy_obj->R = exploading_Enemy->color_holder[0];
	exploading_Enemy->self->enemy_obj->B = exploading_Enemy->color_holder[1];
	exploading_Enemy->self->enemy_obj->G = exploading_Enemy->color_holder[2];
}


void explosion_enemy_collistion(Exploading_Enemy* exploading_Enemy, all_renderable_objs* array_of_obj_to_render) {
	int array_to_collide_with[] = { PLAYER };
	renderable_obj** all_collisions = get_colliders(exploading_Enemy->self->enemy_obj->rect, array_of_obj_to_render, 0, array_to_collide_with,1);
	if (all_collisions != NULL) {
		for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
		{
			if (all_collisions[i] == NULL) {
				break; //in all collistion all the members are one after the other so if one of them is null it is mean we are at pass the last not null member
			}
			switch (all_collisions[i]->high_object_type)
			{
				case PLAYER:
				{
					exploading_Enemy->is_touching = 1;
					break;
				}
				}
				break;
				break;
			}
		}
		free(all_collisions);

}
