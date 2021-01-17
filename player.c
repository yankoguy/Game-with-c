#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "render_obj.h"
#include <malloc.h>
#include "player.h"
#include "events.h"
#include "basic_setup.h"
#include "simple_bullet.h"
#include "basic_enemy.h"
#include "render_obj.h"
#include <string.h>
#include "useful_function.h"
#include "health_packs.h"
#include "ammo_box.h"

Player* create_player(int x, int y, int w, int h, int R, int B, int G, int high_obj_type, int low_obj_type, int layer,
	all_renderable_objs* array_of_obj_to_render, all_renderable_text* array_of_texts,float speed, int health,int array_to_collide_with[], int number_of_layers_to_collide_with)
{
	renderable_obj* player_obj = create_renderable_obj(x, y, w, h, R, B, G, high_obj_type, low_obj_type,layer);

	Player* player = (Player*)(malloc(sizeof(Player)));

	player->player_obj = player_obj;

	player->speed = speed;
	player->health = health;
	player_obj->parent = player;
	player->array_of_texts = array_of_texts;
	memcpy(player->array_to_collide_with, array_to_collide_with, sizeof array_to_collide_with);
	player->number_of_layers_to_collide_with = number_of_layers_to_collide_with;
	player->player_gun = create_gun(x,y,10,10,255,255,255,GUN, NO_TYPE,layer + 1 ,0.2f,SHOCK_BULLET_PLAYER,10,30,player->player_obj,PLAYER,10,10);
	add_render_obj(player->player_gun->gun_obj, array_of_obj_to_render);

	change_text("player health", "player health: ",health, array_of_texts);
	change_text("ammo", "ammo: ", player->player_gun->ammo, array_of_texts);

	return player;

}



void player_collision(Player* player, all_renderable_objs* array_of_obj_to_render) {
	renderable_obj** all_collisions = get_colliders(player->player_obj->rect, array_of_obj_to_render, 0, player->array_to_collide_with,
		player->number_of_layers_to_collide_with); //change with one to 0
	if (all_collisions != NULL) {
		for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
		{
			if (all_collisions[i] == NULL) {
				break; //in all collistion all the members are one after the other so if one of them is null it is mean we are at pass the last not null member
			}
			switch (all_collisions[i]->high_object_type)
			{
			case POWER_UPS:

				switch (all_collisions[i]->low_object_type)
				{
				case HEALTH_PACK:
				{
					Health_pack* health_pack = (Health_pack*)(all_collisions[i]->parent);
					player->health += health_pack->health;
					change_text("player health", "player health: ", player->health, player->array_of_texts);
					health_pack->self->dead = 1;

					break;
				}

				case AMMO_BOX:
				{
					Ammo_box* ammo_box = (Ammo_box*)(all_collisions[i]->parent);
					player->player_gun->ammo += ammo_box->ammo;
					change_text("ammo", "ammo: ", player->player_gun->ammo, player->array_of_texts);
					ammo_box->self->dead = 1;
					break;
				}
				}
				break;
				break;
			}
		}
		free(all_collisions);

	}
}


void player_movemnt(Player* player, clicked_keys* keys, float delta_time) {
	if (keys[SDLK_a].state!=UP) {
		player->player_obj->rect->x -= (int)(player->speed*delta_time);
	}
	if (keys[SDLK_d].state != UP) {
		player->player_obj->rect->x += (int)(player->speed*delta_time);
	}
	if (keys[SDLK_w].state != UP) {
		player->player_obj->rect->y -= (int)(player->speed*delta_time);
	}
	if (keys[SDLK_s].state != UP) {
		player->player_obj->rect->y += (int)(player->speed*delta_time);
	}
}

void player_shoot(Player* player, all_renderable_objs* array_of_obj_to_render, clicked_keys* keys){
	if (keys[SDLK_SPACE].state == DOWN && keys[SDLK_SPACE].number_of_frames == 2) {
		int array_of_layers_bullet_collide_with[] = { BASIC_ENEMY };
		int x_target, y_target;
		SDL_GetMouseState(&x_target, &y_target);
		gun_shoot(player->player_gun, array_of_obj_to_render, array_of_layers_bullet_collide_with,1, x_target,y_target);
		change_text("ammo", "ammo: ", player->player_gun->ammo, player->array_of_texts);
	}
}

static void player_death() {
	printf("player died");
}

void player_take_damage(Player* player,int damage) {
	player->health -= damage;
	if (player->health <= 0) {
		player_death();
	}
	change_text("player health","player health: ",player->health,player->array_of_texts);

}

