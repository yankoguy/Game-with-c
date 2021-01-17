#ifndef GUN_H
#define GUN_H

#include "simple_bullet.h"
#include "render_obj.h"

typedef struct {
	float shoot_time;  //time btween shoots
	float shoot_timer;//the timer
	int bullet_type;
	renderable_obj* gun_obj;
	renderable_obj* gun_holder;
	int holder_type;
	int x_offset;
	int y_offset;
	int ammo; //set to -1 for infinity ammo
	int max_ammo; // set to -1 for inifinity max ammo
	int is_shoot; //1 for the can shoot and 0 for gun cant shoot
}Gun;

Gun* create_gun(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer,
	float shoot_time, int bullet_type, int starting_ammo, int max_ammo, renderable_obj* gun_holder, int holder_type, int x_offset, int y_offset);

void chagne_gun_shoot_timer(Gun* gun, float new_shoot_time);
void gun_change_position(Gun* gun);
void chagne_gun_bullet_type(Gun* gun, int new_bullet_type);
void gun_shoot(Gun* gun, all_renderable_objs* array_of_obj_to_render, int array_of_layers_the_bullet_collide_with[], int number_of_layers_bullet_to_collide_with, int x_target,int y_target);
void update_gun_timers(Gun* gun, float delta_time);

#endif