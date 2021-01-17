#ifndef SPAWNER_H
#define SPAWNER_H

#include "render_obj.h"
#include "basic_enemy.h"

#define ENEMIE_SPAWNER_TIME 6.2f
#define HEAL_PACKS_SPAWNER_TIME 5.0f
#define AMMO_BOX_SPAWNER_TIME 3.0f

typedef struct {
	float enemie_spawner_timer;
	float health_packs_spawner_timer;
	float ammo_box_spawner_timer;
	int spawn_flag; //0 for no spawn 1 for spawn
	float spawner_multipler;
}Spawner; //always one in game. always in game

Spawner* create_spawner();

void update_spawner_timers(Spawner* spawner, all_renderable_objs* array_of_obj_to_render, float delta_time);

#endif