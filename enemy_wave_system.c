#include "stdafx.h"
#include "enemy_wave_system.h"
#include "render_obj.h"

Enemy_wave_manager* create_enemy_wave_manager(float time_between_waves, Spawner* spawner, all_renderable_text* array_of_texts)
{

	Enemy_wave_manager* enemy_wave = (Enemy_wave_manager*)(malloc(sizeof(Enemy_wave_manager)));
	enemy_wave->wave_number = 0;
	enemy_wave->time_between_waves = time_between_waves;
	enemy_wave->between_waves_timer = 0;
	enemy_wave->in_wave_timer = 0;

	enemy_wave->array_of_texts = array_of_texts;
	enemy_wave->spawner = spawner;
	change_text("enemy wave", "wave: ", 0, array_of_texts);
	change_text("enemy time wave", "time: ", enemy_wave->between_waves_timer, array_of_texts);
	return enemy_wave;
}	


static void create_wave(Enemy_wave_manager* wave_manager) {
	wave_manager->spawner->spawn_flag = 1;
	wave_manager->wave_number += 1;
	wave_manager->spawner->spawner_multipler = 1 + (wave_manager->wave_number / 5);
	change_text("enemy wave", "wave: ", wave_manager->wave_number, wave_manager->array_of_texts);
	wave_manager->between_waves_timer = 0;
}

static void stop_wave(Enemy_wave_manager* wave_manager) {
	wave_manager->in_wave_timer = 0;
	wave_manager->spawner->spawn_flag = 0;
	wave_manager->spawner->enemie_spawner_timer = 0;
}

void update_wave_timers(Enemy_wave_manager* wave_manager,float delta_time,all_renderable_objs* all_obj) {
	change_text("enemy time wave", "time: ", (int)wave_manager->between_waves_timer, wave_manager->array_of_texts);
	if (get_rendobj_of_type(BASIC_ENEMY, all_obj) == NULL && !wave_manager->spawner->spawn_flag) {
		wave_manager->between_waves_timer += delta_time / 60.0f;
		if (wave_manager->between_waves_timer >= wave_manager->time_between_waves) {
			create_wave(wave_manager);
		}
	}
	else {
		wave_manager->in_wave_timer += delta_time / 60.0f;
		if (wave_manager->in_wave_timer >= WAVETIME + 10 * wave_manager->wave_number) {
			stop_wave(wave_manager);
		}
	}
}


