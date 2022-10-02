#include "my.ponygame.h"

#include "../globals.h"

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

	int item_count = 70;

	for(int i = 0; i < item_count; ++i) {
		int item_type = rand_range(0, 20);
		if(item_type > 12) {
			if(item_type > 18) {
				item_type = 2;
			}
			else {
				item_type = 1;
			}
		}
		else {
			item_type = 0;
		}

		if(item_type == 0) {
			Rock *rock = new(Rock);
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			set_lpos(rock, pos);
			reparent(rock, self);
		}
		else if(item_type == 1) {
			Plant *rock = new(Plant);
			plant_texture(rock);
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			set_lpos(rock, pos);
			reparent(rock, self);
		}
		else {
			Tree *rock = new(Tree);
			tree_texture(rock);
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			set_lpos(rock, pos);
			reparent(rock, self);
		}
	}
}

// void destruct_Planet(Planet *self) { }

void tick_Planet(Planet *self, PlanetTree *tree) {
	tree->ship_prompt->visible = length(get_gpos(player)) < 20;
	if(tree->ship_prompt->visible) {
		if(keys.E.just_pressed) {
			reparent(new(Ship), root);
			node_destroy(self);
		}
	}
}

