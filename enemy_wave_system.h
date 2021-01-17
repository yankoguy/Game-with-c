#ifndef ENEMY_WAVE_STSTEM_H
#define ENEMY_WAVE_STSTEM_H

#include "basic_enemy.h"
#include "spawner_manager.h"

#define WAVETIME 10

typedef struct //each wave this struct changes
{
	int wave_number;
	Spawner* spawner;
	all_renderable_text* array_of_texts;
	float between_waves_timer;
	float in_wave_timer;
	float time_between_waves; //time after the current wave is finnished (all enemies are died) to create a new wave
}Enemy_wave_manager;


Enemy_wave_manager* create_enemy_wave_manager(float time_between_waves, Spawner* spawner, all_renderable_text* array_of_texts);

void update_wave_timers(Enemy_wave_manager* wave, float delta_time,all_renderable_objs* all_obj);

#endif 
