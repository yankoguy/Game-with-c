#ifndef BASIC_SETUP_H
#define BASIC_SETUP_H

#include <SDL.h>
#include "render_obj.h"
#include "events.h"

#define SCREEN_WIDTH 840
#define SCRENN_HIGHT 840
#define FRAMES_PER_SEC 60

typedef struct Core_objects {
	all_renderable_objs* array_of_obj_to_render;
	all_renderable_text* array_of_text_to_render;
	SDL_Window* win;
	SDL_Renderer* renderer;
	float delta_time;
}Core_objects;

#endif
