#include "stdafx.h"
#include "spawner_manager.h"
#include "basic_enemy.h"
#include <stdlib.h>
#include "basic_setup.h"
#include "exploading_enemy.h"
#include "shooting_enemy.h"
#include "health_packs.h"
#include "ammo_box.h"

static void spawn_enemie(Spawner* spawner, all_renderable_objs* array_of_obj_to_render) {
	int random_x_pos = rand() % SCREEN_WIDTH;
	int random_y_pos = rand() % SCRENN_HIGHT;

	Shooting_Enemy* shotting_enemy = create_shooting_enemy(random_x_pos, random_y_pos, 12, 12, 200, 100, 10, BASIC_ENEMY, ENEMIE_LAYER,array_of_obj_to_render ,1.0f, 50
		, get_rendobj_of_type(PLAYER, array_of_obj_to_render), 300.0f ,4);

	add_render_obj(shotting_enemy->self->enemy_obj, array_of_obj_to_render);
	spawner->enemie_spawner_timer = ENEMIE_SPAWNER_TIME;
}

static void spawn_health_pack(Spawner* spawner, all_renderable_objs* array_of_obj_to_render) {
	int random_x_pos = rand() % SCREEN_WIDTH;
	int random_y_pos = rand() % SCRENN_HIGHT;
	Health_pack* health_pack = create_health_pack(random_x_pos, random_y_pos, 20, 20, 255, 0, 0, POWER_UPS, HEALTH_PACK, POWER_UPS_LAYER,10);

	add_render_obj(health_pack->self, array_of_obj_to_render);
	spawner->health_packs_spawner_timer = HEAL_PACKS_SPAWNER_TIME;
}

static void spawn_ammo_box(Spawner* spawner, all_renderable_objs* array_of_obj_to_render) {
	int random_x_pos = rand() % SCREEN_WIDTH;
	int random_y_pos = rand() % SCRENN_HIGHT;
	
	Ammo_box* ammo_box = create_ammo_box(random_x_pos, random_y_pos, 10, 10, 0,255, 0, POWER_UPS, AMMO_BOX, POWER_UPS_LAYER, 5);

	add_render_obj(ammo_box->self, array_of_obj_to_render);
	spawner->ammo_box_spawner_timer = AMMO_BOX_SPAWNER_TIME;
}

Spawner* create_spawner() {
	Spawner* spawner = (Spawner*)(malloc(sizeof(Spawner)));
	spawner->enemie_spawner_timer = 0;
	spawner->health_packs_spawner_timer  = 0;
	spawner->ammo_box_spawner_timer = 0;
	spawner->spawn_flag = 0;
	spawner->spawner_multipler = 1;
	return spawner;
}

void update_spawner_timers(Spawner* spawner, all_renderable_objs* array_of_obj_to_render, float delta_time) {
	if (spawner->spawn_flag) {
		spawner->enemie_spawner_timer -= delta_time / 60.0f * spawner->spawner_multipler;
		if (spawner->enemie_spawner_timer <= 0) {
			spawn_enemie(spawner, array_of_obj_to_render);
		}
		spawner->health_packs_spawner_timer -= delta_time / 60.0f;
		if (spawner->health_packs_spawner_timer <= 0) {
			spawn_health_pack(spawner, array_of_obj_to_render);
		}
		spawner->ammo_box_spawner_timer -= delta_time / 60.0f;
		if (spawner->ammo_box_spawner_timer <= 0) {
			spawn_ammo_box(spawner, array_of_obj_to_render);
		}
	}
}

