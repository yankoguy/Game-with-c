#include "stdafx.h"
#include "events.h"
#include "render_obj.h"
#include "basic_enetity.h"

renderable_obj * create_entity(int x, int y, int w, int h, int R, int B, int G, int speed,void(*movmnet_func)(renderable_obj,All_Events)){
	SDL_Rect* player_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	player_rect->x = x;
	player_rect->y = y;
	player_rect->w = w;
	player_rect->h = h;

	renderable_obj* player_obj = (renderable_obj*)malloc(sizeof(renderable_obj));
	player_obj->rect = player_rect;
	player_obj->R = R;
	player_obj->B = B;
	player_obj->G = G;
	player_obj->speed = speed;
	player_obj->movment_fucnction = movmnet_func;
	return player_obj;
}



void active_movment_fucntion(all_renderable_objs* all_renderable_objects) {
	for (int i = 0; i < all_renderable_objects->number_of_rects; i++)
	{
		if (all_renderable_objects->array_of_objects_to_render[i] != NULL) {
			if (all_renderable_objects->array_of_objects_to_render[i]->movment_fucnction != NULL) {
				all_renderable_objects->array_of_objects_to_render[i]->movment_fucnction(
					all_renderable_objects->array_of_objects_to_render[i]);
			}
		}
	}
}
