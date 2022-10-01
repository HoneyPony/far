#include "my.ponygame.h"


Sprite *new_tile(int i, int j) {
	AnimHandle* options[] = { &res.planets.tile1_tex.loop, &res.planets.tile2_tex.loop };
	Sprite *tile = new(Sprite);
	set_gpos(tile, vxy(16 * i, 14 * j));
	sprite_play(tile, options[rand_range(0,1)]);

	return tile;
}

void construct_Planet(Planet *self) {
	for(int i = -30; i <= 30; ++i) {
		for(int j = -30; j <= 30; ++j) {
	//for(int i = 0; i <= 0; ++i) { for(int j = 0; j <= 0; ++j) {
			Sprite *tile = new_tile(i, j);
			
			reparent(tile, self);
		}
	}
}

// void destruct_Planet(Planet *self) { }

// void tick_Planet(Planet *self, PlanetTree *tree) { }
