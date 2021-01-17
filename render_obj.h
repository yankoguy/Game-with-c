#ifndef RENDER_OBJ_H
#define RENDER_OBJ_H

#include <SDL.h>
#include "events.h"
#include <SDL_ttf.h>

#define MAX_RECTS_IN_GAME 128
#define MAX_TEXTS_IN_GAME 16

typedef enum {
	NO_TYPE,
	STATIC_OBJ,
	BASIC_ENEMY,
	PLAYER,
	BULLET,
	GUN,
	POWER_UPS

}OBJ_TYPE;

typedef enum { //it should be in power ups file if i will create one
	HEALTH_PACK,
	AMMO_BOX
}POWER_TYPES;


typedef enum {
	PLAYER_LAYER,
	ENEMIE_LAYER,
	BULLET_LAYER,
	POWER_UPS_LAYER
}OBJ_LAYER;




typedef struct
{
	SDL_Rect* rect;
	int R;
	int B;
	int G;
	int index_in_array;
	int high_object_type; // identification of object type like: player/enemy/bullet
	int low_object_type; // identification of specifice type of this object. if the higher_object_type is enemy so this param will be running_enemy/shooting enemy...
	void * parent;
	int dead;
	int layer;
}renderable_obj;


typedef struct
{
	int number_of_rects;
	int index_of_last_rect_created;  
	int hights_index; //store the index of the rect in the hightets index
	renderable_obj *array_of_objects_to_render[MAX_RECTS_IN_GAME];
}all_renderable_objs;


typedef struct 
{
	SDL_Rect* rect;
	TTF_Font* font; 
	char* text;
	int font_size;
	int index_in_array;
	int R;
	int B;
	int G;
	int layer;
	char* name;
	int dead;
}renderable_text;


typedef struct
{
	int number_of_texts;
	int index_of_last_text_created;
	int hights_index; //store the index of the rect in the hightets index
	renderable_text *array_of_texts_to_render[MAX_TEXTS_IN_GAME];
}all_renderable_text;





renderable_obj* create_renderable_obj(int x, int y, int w, int h, int R, int B, int G,int high_obj_type,int low_obj_type, int layer);
void add_render_obj(renderable_obj* obj_to_render, all_renderable_objs* renderable_objects);
all_renderable_objs* create_render_obj_chain();

renderable_text* create_renderable_text(int font_size, char* text, int R, int B, int G, int x, int y, int w, int h, int layer, char* name);
void add_render_text(renderable_text* text_to_render, all_renderable_text* renderable_texts);
all_renderable_text* create_render_text_chain();

void render(SDL_Renderer* renderer, all_renderable_objs* all_rects_to_render, all_renderable_text* all_texts_to_render);
void active_object_functions(all_renderable_objs* all_rects_to_render, clicked_keys * keys, float delta_time);


renderable_obj* get_rendobj_of_type(int type, all_renderable_objs* renderable_objects);
renderable_text* get_rendtext_by_name(char* name, all_renderable_text* renderable_texts);

renderable_obj** get_colliders(SDL_Rect* checker, all_renderable_objs* renderable_objects, int only_one,
	int types_to_collide_with[], int number_of_types);

void change_text(char* text_name, char* text, int value, all_renderable_text* array_of_texts);

#endif