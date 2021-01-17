#include "stdafx.h"
#include "render_obj.h"
#include <stdio.h>
#include "player.h"
#include "basic_enemy.h"
#include "simple_bullet.h"
#include "events.h"
#include "exploading_enemy.h"
#include "shooting_enemy.h"
#include <SDL_ttf.h>

renderable_obj* create_renderable_obj(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer) {
	SDL_Rect* enetity_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	enetity_rect->x = x;
	enetity_rect->y = y;
	enetity_rect->w = w;
	enetity_rect->h = h;

	renderable_obj* entity_obj = (renderable_obj*)malloc(sizeof(renderable_obj));
	entity_obj->rect = enetity_rect;
	entity_obj->R = R;
	entity_obj->B = B;
	entity_obj->G = G;
	entity_obj->high_object_type = high_type;
	entity_obj->low_object_type = low_type;

	entity_obj->dead = 0;
	entity_obj->layer = layer;
	return entity_obj;

}


renderable_text* create_renderable_text(int font_size, char* text, int R, int B, int G, int x, int y, int w, int h,int layer,char* name)
{

	SDL_Rect* enetity_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	enetity_rect->x = x;
	enetity_rect->y = y;
	enetity_rect->w = w;
	enetity_rect->h = h;

	renderable_text* entity_text = (renderable_text*)malloc(sizeof(renderable_text));
	entity_text->rect = enetity_rect;
	entity_text->R = R;
	entity_text->B = B;
	entity_text->G = G;

	entity_text->font_size = font_size;
	entity_text->text = text;
	entity_text->dead = 0;
	entity_text->font = TTF_OpenFont("Sans.ttf", font_size);
	entity_text->layer = layer;
	entity_text->name = name;
	return entity_text;
}




int static is_in_array(int arr_lenght, int arr[], int val_to_find) //should be in userful_function.c
{
	for (int i = 0; i < arr_lenght; i++)
	{
		if (arr[i] == val_to_find) {
			return 1;
		}
	}
	return 0;
}

static void quick_sort_renderable_obj(all_renderable_objs* all_rects_to_render, int size_of_array) {
	void* holder;
	int swaped = 0;
	for (int i = 1; i < size_of_array; i++)
	{
		if (all_rects_to_render->array_of_objects_to_render[i] != NULL && all_rects_to_render->array_of_objects_to_render[i - 1] != NULL) {
			if (all_rects_to_render->array_of_objects_to_render[i]->layer < all_rects_to_render->array_of_objects_to_render[i - 1]->layer)
			{
				all_rects_to_render->array_of_objects_to_render[i]->index_in_array -= 1; //change index in arr
				all_rects_to_render->array_of_objects_to_render[i - 1]->index_in_array += 1;//change index in arr


				holder = all_rects_to_render->array_of_objects_to_render[i - 1];
				all_rects_to_render->array_of_objects_to_render[i - 1] = all_rects_to_render->array_of_objects_to_render[i];
				all_rects_to_render->array_of_objects_to_render[i] = holder;
				swaped = 1;
			}
		}
	}
	if (swaped == 0) {
		return;
	}
	quick_sort_renderable_obj(all_rects_to_render, size_of_array);
}


static void quick_sort_renderable_texts(all_renderable_text* all_texts_to_render, int size_of_array) {
	void* holder;
	int swaped = 0;
	for (int i = 1; i < size_of_array; i++)
	{
		if (all_texts_to_render->array_of_texts_to_render[i] != NULL && all_texts_to_render->array_of_texts_to_render[i - 1] != NULL) {
			if (all_texts_to_render->array_of_texts_to_render[i]->layer < all_texts_to_render->array_of_texts_to_render[i - 1]->layer)
			{
				all_texts_to_render->array_of_texts_to_render[i]->index_in_array -= 1; //change index in arr
				all_texts_to_render->array_of_texts_to_render[i - 1]->index_in_array += 1;//change index in arr


				holder = all_texts_to_render->array_of_texts_to_render[i - 1];
				all_texts_to_render->array_of_texts_to_render[i - 1] = all_texts_to_render->array_of_texts_to_render[i];
				all_texts_to_render->array_of_texts_to_render[i] = holder;
				swaped = 1;
			}
		}
	}
	if (swaped == 0) {
		return;
	}
	quick_sort_renderable_texts(all_texts_to_render, size_of_array);
}








renderable_obj** get_colliders(SDL_Rect* checker, all_renderable_objs* renderable_objects, int only_one,
	int types_to_collide_with[], int number_of_types)
	//checker is the rect that check if it collide with something
	//if only_one = 0 so it check all collisions, if only_one = 1 it only returns 1 object (if there is any) 
	//types_to_collide_with is an array of all the the types you can collide with 
{
	int number_of_collisions = 0;

	renderable_obj** all_collisions = (renderable_obj**)(malloc(sizeof(renderable_obj*)*MAX_RECTS_IN_GAME));

	for (int i = 0; i < MAX_RECTS_IN_GAME; i++) //loop throught all rects
	{
		all_collisions[i] = NULL; //inillize array
	}
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++) //loop throught all rects
	{
		if (renderable_objects->array_of_objects_to_render[i] != NULL) {
			if (SDL_HasIntersection(checker, renderable_objects->array_of_objects_to_render[i]->rect) &&
				checker != renderable_objects->array_of_objects_to_render[i]->rect)
			{
				if (is_in_array(number_of_types, types_to_collide_with, renderable_objects->array_of_objects_to_render[i]->high_object_type)) {

					all_collisions[number_of_collisions] = renderable_objects->array_of_objects_to_render[i]; // all_collisions[number_of_collisions] is pointer to the object pointer by renderable_objects->array_of_objects_to_render[i]

					number_of_collisions += 1;
					if (only_one) { break; }
				}

			}
		}
	}


	if (number_of_collisions == 0) {
		return NULL;
	}
	return all_collisions;
}


renderable_obj* get_rendobj_of_type(int type, all_renderable_objs* renderable_objects)
{
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++) //loop throught all rects
	{
		if (renderable_objects->array_of_objects_to_render[i] != NULL)
		{
;			if (type == renderable_objects->array_of_objects_to_render[i]->high_object_type) {
				return(renderable_objects->array_of_objects_to_render[i]);
			}
		}
	}
	return NULL;
}


renderable_text* get_rendtext_by_name(char* name, all_renderable_text* renderable_texts) {
	for (int i = 0; i < MAX_TEXTS_IN_GAME; i++) //loop throught all rects
	{
		if (renderable_texts->array_of_texts_to_render[i] != NULL)
		{
			if (name == renderable_texts->array_of_texts_to_render[i]->name)	
			{
				return(renderable_texts->array_of_texts_to_render[i]);
			}
		}
	}

	return NULL;
}



static void remove_obj_from_render_array(void** parent, renderable_obj* obj_to_render, all_renderable_objs* renderable_objects) 
{
	renderable_objects->number_of_rects -= 1;
	renderable_objects->array_of_objects_to_render[obj_to_render->index_in_array] = NULL;
	if (obj_to_render->high_object_type == BASIC_ENEMY) {
	
		if (obj_to_render->low_object_type == SHOOTING_ENEMY) {
			renderable_objects->array_of_objects_to_render[((Shooting_Enemy*)obj_to_render->parent)->shooting_enemy_gun->gun_obj->index_in_array] = NULL;

			Shooting_Enemy* f = ((Shooting_Enemy*)obj_to_render->parent);
			destroy_shooting_enemy_gun(((Shooting_Enemy*)obj_to_render->parent));
			free(((Shooting_Enemy*)obj_to_render->parent)->self);
			((Shooting_Enemy*)obj_to_render->parent)->self = NULL;
			free(*parent);
			*parent = NULL;
			free(obj_to_render->rect);
			free(obj_to_render);
		}
	}

	else {
		free(*parent);
		*parent = NULL;
		free(obj_to_render->rect);
		free(obj_to_render);
	}
}

static void remove_text_from_render_array(renderable_text* text_to_render, all_renderable_text* renderable_texts)
{
	renderable_texts->number_of_texts -= 1;
	renderable_texts->array_of_texts_to_render[text_to_render->index_in_array] = NULL;
	free(text_to_render->rect);
	free(text_to_render);
}




static void kill_all_dead_objects(all_renderable_objs* renderable_objects) {
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++) //loop throught all rects
	{
		if (renderable_objects->array_of_objects_to_render[i] != NULL) {
			if (renderable_objects->array_of_objects_to_render[i]->dead) {
				remove_obj_from_render_array(&(renderable_objects->array_of_objects_to_render[i]->parent),
					renderable_objects->array_of_objects_to_render[i], renderable_objects);
			}
		}
	}
}



static void kill_all_dead_texts(all_renderable_text* renderable_texts) {
	for (int i = 0; i < MAX_TEXTS_IN_GAME; i++) //loop throught all rects
	{
		if (renderable_texts->array_of_texts_to_render[i] != NULL) {
			if (renderable_texts->array_of_texts_to_render[i]->dead) {
				remove_text_from_render_array(renderable_texts->array_of_texts_to_render[i], renderable_texts);
			}
		}
	}
}





void add_render_obj(renderable_obj* obj_to_render, all_renderable_objs* renderable_objects)
{
	if (renderable_objects->number_of_rects < MAX_RECTS_IN_GAME) {
		renderable_objects->number_of_rects += 1;
		for (int i = 0; i < MAX_RECTS_IN_GAME; i++) //loop throught all rects
		{
			if (renderable_objects->array_of_objects_to_render[i] == NULL) //search if where can place another obj
			{
				renderable_objects->array_of_objects_to_render[i] = obj_to_render;
				renderable_objects->array_of_objects_to_render[i]->index_in_array = i;
				renderable_objects->index_of_last_rect_created = i;
				break;
			}
		}
		quick_sort_renderable_obj(renderable_objects,MAX_RECTS_IN_GAME);
	}
}

	
void add_render_text(renderable_text* text_to_render, all_renderable_text* renderable_texts)
{
	if (renderable_texts->number_of_texts < MAX_TEXTS_IN_GAME) {
		renderable_texts->number_of_texts += 1;
		for (int i = 0; i < MAX_TEXTS_IN_GAME; i++) //loop throught all rects
		{
			if (renderable_texts->array_of_texts_to_render[i] == NULL) //search if where can place another obj
			{
				renderable_texts->array_of_texts_to_render[i] = text_to_render;
				renderable_texts->array_of_texts_to_render[i]->index_in_array = i;
				renderable_texts->index_of_last_text_created = i;
				break;
			}
		}
		quick_sort_renderable_texts(renderable_texts, MAX_TEXTS_IN_GAME);

	}
}






all_renderable_objs* create_render_obj_chain() {

	all_renderable_objs* renderable_objects = (all_renderable_objs*)malloc(sizeof(all_renderable_objs));
	renderable_objects->number_of_rects = 0;
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
	{
		renderable_objects->array_of_objects_to_render[i] = NULL;
	}
	return renderable_objects;
}


all_renderable_text* create_render_text_chain() {

	all_renderable_text* renderable_texts = (all_renderable_text*)malloc(sizeof(all_renderable_text));
	renderable_texts->number_of_texts = 0;
	for (int i = 0; i < MAX_TEXTS_IN_GAME; i++)
	{
		renderable_texts->array_of_texts_to_render[i] = NULL;
	}
	return renderable_texts;
}




void active_object_functions(all_renderable_objs* all_rects_to_render, clicked_keys * keys, float delta_time) {
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
	{
		if (all_rects_to_render->array_of_objects_to_render[i] != NULL) {
			switch (all_rects_to_render->array_of_objects_to_render[i]->high_object_type) {
			case PLAYER:
			{
				//can add here check for player low type - for now he is 0
				Player* player = (Player*)all_rects_to_render->array_of_objects_to_render[i]->parent;
				player_movemnt(player, keys, delta_time);
				player_shoot(player, all_rects_to_render, keys);
				player_collision(player, all_rects_to_render);
				break;
			}
			case BASIC_ENEMY: {

				switch (all_rects_to_render->array_of_objects_to_render[i]->low_object_type)
				{
				case EXPLOSIVE_ENEMY: {
					Exploading_Enemy* exploading_Enemy = (Exploading_Enemy*)all_rects_to_render->array_of_objects_to_render[i]->parent;
					update_enemy_timers(exploading_Enemy->self, delta_time);
					apply_enemy_affect(exploading_Enemy->self);
					explosion_enemy_collistion(exploading_Enemy, all_rects_to_render);
					if (exploading_Enemy->is_exploding) {
						exploda_enemy_start_explode(exploading_Enemy, delta_time);
					}
					else {
						if (exploading_Enemy->is_touching) {
							exploading_Enemy->is_touching = 0;//set back the touching flag
							exploding_enemy_pre_expload(exploading_Enemy, delta_time);
						}
						else {
							exploading_Enemy->explision_timer = 0;
							exploding_enemy_reset_color(exploading_Enemy);
							enemy_movment(exploading_Enemy->self, delta_time, 0);
						}

					}
				
					break;
				}
				case SHOOTING_ENEMY: {
					Shooting_Enemy* shooting_enemy = (Shooting_Enemy*)all_rects_to_render->array_of_objects_to_render[i]->parent;
					update_enemy_timers(shooting_enemy->self, delta_time);
					apply_enemy_affect(shooting_enemy->self);
					enemy_movment(shooting_enemy->self, delta_time, shooting_enemy->dis_until_stop);
					shooting_enemy_shoot(shooting_enemy, all_rects_to_render);
					break;
				}
				}
				break;
			}

			case BULLET: {
				Bullet* bullet = (Bullet*)all_rects_to_render->array_of_objects_to_render[i]->parent;
				bullet_movment(bullet, delta_time);
				update_bullet_timers(bullet, delta_time);
				check_bullet_timers(&bullet, all_rects_to_render);
				bullet_check_hit(&bullet, all_rects_to_render);

				break;
			}

			case GUN: {
				Gun* gun = (Gun*)all_rects_to_render->array_of_objects_to_render[i]->parent;
				update_gun_timers(gun, delta_time);
				gun_change_position(gun);
				break;
			}
			default:
				break;
			}
		}
	}
	kill_all_dead_objects(all_rects_to_render);
}

void render(SDL_Renderer* renderer, all_renderable_objs* all_rects_to_render, all_renderable_text* all_texts_to_render)
{																	
	for (int i = 0; i < MAX_RECTS_IN_GAME; i++)
	{
		if (all_rects_to_render->array_of_objects_to_render[i] != NULL) 
		{

			SDL_SetRenderDrawColor(renderer, all_rects_to_render->array_of_objects_to_render[i]->R,
				all_rects_to_render->array_of_objects_to_render[i]->B,
				all_rects_to_render->array_of_objects_to_render[i]->G,
				255);

			SDL_RenderFillRect(renderer, all_rects_to_render->array_of_objects_to_render[i]->rect);

		}
	}

	for (int i = 0; i < MAX_TEXTS_IN_GAME; i++)
	{
		SDL_Surface* surfaceMessage;
		SDL_Texture* Message;
		SDL_Color color;
		if (all_texts_to_render->array_of_texts_to_render[i] != NULL)
		{

			color.r = all_texts_to_render->array_of_texts_to_render[i]->R;
			color.b = all_texts_to_render->array_of_texts_to_render[i]->B;
			color.g= all_texts_to_render->array_of_texts_to_render[i]->G;

			surfaceMessage = TTF_RenderText_Solid(all_texts_to_render->array_of_texts_to_render[i]->font, all_texts_to_render->array_of_texts_to_render[i]->text, color);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //convert surface it into a texture

			SDL_RenderCopy(renderer, Message, NULL, all_texts_to_render->array_of_texts_to_render[i]->rect);

			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(Message);
		}
	}
	SDL_RenderPresent(renderer);
	kill_all_dead_texts(all_texts_to_render);
}


void change_text(char* text_name, char* text, int value, all_renderable_text* array_of_texts)
{
	char* buffer = (char*)malloc(strlen(text) + sizeof(int) + 1);
	sprintf(buffer, "%d", value);
	char* result = concat(text, buffer);
	get_rendtext_by_name(text_name, array_of_texts)->text = concat(text, buffer);
	free(result);
	free(buffer);
}