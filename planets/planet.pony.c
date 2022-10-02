#include "my.ponygame.h"


Sprite *new_tile(int i, int j) {
	AnimHandle* options[] = { &res.planets.tile1_tex.loop, &res.planets.tile2_tex.loop };
	Sprite *tile = new(Sprite);
	set_gpos(tile, vxy(16 * i, 14 * j));
	sprite_play(tile, options[rand_range(0,1)]);

	return tile;
}

#define RADIUS 50

void construct_Planet(Planet *self) {
	for(int i = -RADIUS; i <= RADIUS; ++i) {
		for(int j = -RADIUS; j <= RADIUS; ++j) {
	//for(int i = 0; i <= 0; ++i) { for(int j = 0; j <= 0; ++j) {
			Sprite *tile = new_tile(i, j);
			tile->z_index = -100;

			reparent(tile, self);
		}
	}

	for(int i = 0; i < 50; ++i) {
		Rock *rock = new(Rock);
		vec2 pos;
		pos.x = rand_range(-30, 30) * 16;
		pos.y = rand_range(-30, 30) * 14;
		set_lpos(rock, pos);
		reparent(rock, self);
	}
}

// void destruct_Planet(Planet *self) { }

// void tick_Planet(Planet *self, PlanetTree *tree) { }

