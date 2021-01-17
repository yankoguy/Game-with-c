// circle_shooter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "basic_setup.h"
#include <string.h>
#include <errno.h>
#include <SDL.h>
#include <SDL_image.h>
#include "events.h"
#include "render_obj.h"
#include "player.h"
#include "basic_enemy.h"
#include "spawner_manager.h"
#include <time.h>
#include <stdlib.h>
#include "exploading_enemy.h"
#include <SDL_ttf.h>
#include "enemy_wave_system.h"
#include "enemy_wave_system.h"

void clear_window(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
	SDL_RenderClear(renderer);
}
int create_window_render(SDL_Window** win , SDL_Renderer** renderer) {
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
		return -1;
	}
	if ((*win = SDL_CreateWindow("GAME", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCRENN_HIGHT, 0)) == NULL) {
		printf("error create window: %s\n", SDL_GetError());
		return -1;
	}
	if (TTF_Init() != 0) {
		printf("TTF ERROR : %s", TTF_GetError());

	}
	if ((*renderer =  SDL_CreateRenderer(*win, -1, render_flags)) == NULL) {
		printf("error create renderer: %s\n", SDL_GetError());
		return -1;
	}
	return 0;
}

void proccess_game_event(clicked_keys* keys) {
	if (keys[SDLK_ESCAPE].state== KEY_PRESS) {
		printf("quit");
	}
}

void quit_game(Core_objects* core_object) {
	
    
	SDL_DestroyRenderer(core_object->renderer);
	SDL_DestroyWindow(core_object->win);
}

void main_loop(Core_objects* core_object) {
	int finished = 0;
	float last_tick_time = 0;
	float delta = 0;
	Spawner* spawner =create_spawner();
	Enemy_wave_manager* enemy_wave_manager = create_enemy_wave_manager(5,spawner,core_object->array_of_text_to_render);

	clicked_keys *keys;
	do {
		float tick_time = SDL_GetTicks();
		delta = tick_time - last_tick_time;
		last_tick_time = tick_time;
		delta /= 12.0f;
		core_object->delta_time = delta;

		keys = get_keyboard_events();
		proccess_game_event(keys);
		clear_window(core_object->renderer);
		active_object_functions(core_object->array_of_obj_to_render, keys,core_object->delta_time);
		render(core_object->renderer, core_object->array_of_obj_to_render,core_object->array_of_text_to_render);

		update_wave_timers(enemy_wave_manager,core_object->delta_time,core_object->array_of_obj_to_render);
		update_spawner_timers(spawner, core_object->array_of_obj_to_render,core_object->delta_time);

		SDL_Delay(1000 / FRAMES_PER_SEC);

	} while (keys[SDLK_ESCAPE].state==UP);
	quit_game(core_object);
}


static void create_first_all_objects(Core_objects* core_obj) {
	int array_of_layers_bullet_collide_with[] = {POWER_UPS };

	Player* player = create_player(0, 5, 30, 30, 30, 100, 100, PLAYER, NO_TYPE, PLAYER_LAYER, core_obj->array_of_obj_to_render, core_obj->array_of_text_to_render, 2.0f, 50,
		array_of_layers_bullet_collide_with,sizeof(array_of_layers_bullet_collide_with));
	add_render_obj(player->player_obj, core_obj->array_of_obj_to_render);
	
	Exploading_Enemy* exploading_Enemy = create_running_enemy(100, 100, 12, 12, 120, 30, 0, BASIC_ENEMY,ENEMIE_LAYER, 1.0f, 50,player->player_obj,3.0f,1.0f,2.0f);
	add_render_obj(exploading_Enemy->self->enemy_obj, core_obj->array_of_obj_to_render);
}

static void create_first_all_text(Core_objects* core_obj) {
	renderable_text* player_health_text = create_renderable_text(24, "", 255, 255, 255, 0, 0, 150, 30, 4,"player health");
	add_render_text(player_health_text, core_obj->array_of_text_to_render);
	renderable_text* player_ammo_text = create_renderable_text(18, "", 0, 0, 0, 700, 0, 100, 20, 3,"ammo");
	add_render_text(player_ammo_text, core_obj->array_of_text_to_render);
	renderable_text* enemy_wave_text = create_renderable_text(20, "", 255, 255, 255, 350, 0, 100, 50, 3, "enemy wave");
	add_render_text(enemy_wave_text, core_obj->array_of_text_to_render);
	renderable_text* enemy_time_wave_text = create_renderable_text(30, "", 0, 0, 0, 350, 50, 100, 50, 3, "enemy time wave");
	add_render_text(enemy_time_wave_text, core_obj->array_of_text_to_render);

}

int start(Core_objects* core_obj) {
	srand(time(NULL));  // Initialization of random, should only be called once.
	create_window_render(&(core_obj->win), &(core_obj->renderer));
	core_obj->array_of_obj_to_render = create_render_obj_chain();
	core_obj->array_of_text_to_render=create_render_text_chain();

	create_first_all_text(core_obj);
	create_first_all_objects(core_obj);
	return 0;
}



int main(int argc, char* argcv[])
{
	Core_objects core_object;
	start(&core_object);
	main_loop(&core_object);
	return 0;
}

