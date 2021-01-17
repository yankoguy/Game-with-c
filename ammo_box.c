#include "stdafx.h"
#include <SDL.h>
#include "render_obj.h"
#include "ammo_box.h"


Ammo_box* create_ammo_box(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer,
	int ammo)
{
	renderable_obj* self = create_renderable_obj(x, y, w, h, R, B, G, high_type, low_type, layer);
	Ammo_box* ammo_box = (Ammo_box*)malloc(sizeof(Ammo_box));
	ammo_box->self = self;
	ammo_box->ammo = ammo;
	ammo_box->self->parent = ammo_box;

	return ammo_box;
}