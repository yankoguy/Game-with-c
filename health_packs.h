#ifndef HEALTH_PACK_H
#define HEALTH_PACK_H

#include "stdafx.h"
#include <SDL.h>
#include "render_obj.h"


typedef struct
{
	renderable_obj* self;
	int health;
}Health_pack;


Health_pack* create_health_pack(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer, int health);

#endif