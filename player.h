#ifndef PLAYER_H
#define PLAYER_H

#include "render_obj.h"
#include "events.h"
#include "basic_setup.h"
#include "basic_gun.h"
typedef struct 
{
	float speed; //the speed of the player
	int health; //current health of the player
	int man_health; //player's max health
	renderable_obj* player_obj; //the renderable_obj of the player
	Gun* player_gun; //the gun the player hold, same gun for the rest of the game
	all_renderable_text* array_of_texts;
	int array_to_collide_with[20];
	int number_of_layers_to_collide_with;
}Player;

Player* create_player(int x, int y, int w, int h, int R, int B, int G, int high_type,int low_type, int layer,
	all_renderable_objs* array_of_obj_to_render, all_renderable_text* array_of_texts,float speed, int health, int array_to_collide_with[],int number_of_layers_to_collide_with);
void player_movemnt(Player* player,clicked_keys* keys, float delta_time);
void player_shoot(Player* player,all_renderable_objs* array_of_obj_to_render, clicked_keys* keys);
void player_take_damage(Player* player,int damage);
void player_collision(Player* player, all_renderable_objs* array_of_obj_to_render);

#endif
