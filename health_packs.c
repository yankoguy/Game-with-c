#include "stdafx.h"
#include <SDL.h>
#include "render_obj.h"
#include "health_packs.h"

Health_pack* create_health_pack(int x, int y, int w, int h, int R, int B, int G, int high_type, int low_type, int layer,
	int health)
{
	renderable_obj* self = create_renderable_obj(x, y, w, h, R, B, G, high_type, low_type, layer);
	Health_pack* health_pack = (Health_pack*)malloc(sizeof(Health_pack));
	health_pack->self = self;
	health_pack->health = health;
	health_pack->self->parent = health_pack;
	
	return health_pack;
}