#include "stdafx.h"
#include "basic_gun.h"
#include "render_obj.h"


Gun* create_gun(int x, int y, int w, int h, int R, int B, int G, int high_type,int low_type, int layer,
	float shoot_time, int bullet_type,int starting_ammo, int max_ammo, renderable_obj* gun_holder, int holder_type, int x_offset, int y_offset)
{
	renderable_obj* gun_obj = create_renderable_obj(x, y, w, h, R, B, G, high_type,low_type, layer);
	Gun* gun = (Gun*)(malloc(sizeof(Gun)));
	gun->gun_obj = gun_obj;
	gun->gun_obj->parent = gun;
	gun->shoot_time = shoot_time;
	gun->bullet_type = bullet_type;
	gun->gun_holder = gun_holder;
	gun->holder_type = holder_type;
	gun->x_offset = x_offset;
	gun->y_offset = y_offset;
	gun->ammo = starting_ammo;
	gun->max_ammo = max_ammo;
	gun->is_shoot = 1;
	return gun;
}

void update_gun_timers(Gun* gun, float delta_time) {
	if (gun->is_shoot) {
		gun->shoot_timer -= delta_time / 60.0f;
	}
}

void chagne_gun_shoot_timer(Gun* gun, float new_shoot_time) {
	gun->shoot_time = new_shoot_time;
}

void chagne_gun_bullet_type(Gun* gun,int new_bullet_type) {
	gun->bullet_type = new_bullet_type;
}


void gun_change_position(Gun* gun) {
	gun->gun_obj->rect->x = gun->gun_holder->rect->x+gun->x_offset;
	gun->gun_obj->rect->y = gun->gun_holder->rect->y+gun->y_offset;
}

void gun_shoot(Gun* gun,all_renderable_objs* array_of_obj_to_render,int array_of_layers_the_bullet_collide_with[],int number_of_layers_bullet_collide_with,int x_target,int y_target) {
	if (gun->shoot_timer <= 0 && gun->is_shoot && ((gun->ammo>0) || gun->ammo==-1)) {
		if (gun->ammo > 0) {
			gun->ammo -= 1;
		}
		switch (gun->bullet_type)
		{
		case NORMAL_BULLET_PLAYER: {
			Bullet* bullet = create_bullet(gun->gun_obj->rect->x, gun->gun_obj->rect->y, 10, 10, 255, 255, 255, BULLET, NORMAL_BULLET_PLAYER, BULLET_LAYER, array_of_layers_the_bullet_collide_with, number_of_layers_bullet_collide_with, x_target, y_target, 4.0f, 10, 3.0f, NO_AFFECT_TIMER);
			add_render_obj(bullet->bullet_obj, array_of_obj_to_render);
			break;
		}
		case NORMAL_BULLET_SHOOTING_ENEMIE: {
			Bullet* bullet = create_bullet(gun->gun_obj->rect->x, gun->gun_obj->rect->y, 8, 8, 0, 0, 0, BULLET, NORMAL_BULLET_SHOOTING_ENEMIE, BULLET_LAYER, array_of_layers_the_bullet_collide_with, number_of_layers_bullet_collide_with, x_target, y_target, 4.0f, 10, 3.0f, NO_AFFECT_TIMER);
			add_render_obj(bullet->bullet_obj, array_of_obj_to_render);
			break;
		}
		case SHOCK_BULLET_PLAYER: { //change this to stun bullet
			Bullet* bullet = create_bullet(gun->gun_obj->rect->x, gun->gun_obj->rect->y, 12, 12, 255,255, 0, BULLET, SHOCK_BULLET_PLAYER, BULLET_LAYER, array_of_layers_the_bullet_collide_with, number_of_layers_bullet_collide_with, x_target, y_target, 4.0f, 10, 3.0f,SHOCK_TIME);
			add_render_obj(bullet->bullet_obj, array_of_obj_to_render);
			break;
		}
		default:
			break;
		}
		gun->shoot_timer = gun->shoot_time;
	}
}