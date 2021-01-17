#ifndef AMMO_BOX_H
#define AMMO_BOX_H

#include "stdafx.h"
#include <SDL.h>
#include "render_obj.h"

typedef struct
{
	renderable_obj* self;
	int ammo;
}Ammo_box;

Ammo_box* create_ammo_box(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer, int ammo);

#endif