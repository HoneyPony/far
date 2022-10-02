#include "my.ponygame.h"

#include "../globals.h"

Sprite *new_tile(int i, int j) {
	AnimHandle* options[] = { &res.planets.tile1_tex.loop, &res.planets.tile2_tex.loop };
	Sprite *tile = new(Sprite);
	set_gpos(tile, vxy(16 * i, 14 * j));
	sprite_play(tile, options[rand_range(0,1)]);

	float *color = get_planet_info()->color;
	tile->r = color[0];
	tile->g = color[1];
	tile->b = color[2];

	return tile;
}

#define RADIUS 50

void construct_Planet(Planet *self) {
	PlanetInfo *info = get_planet_info();

	for(int i = -RADIUS; i <= RADIUS; ++i) {
		for(int j = -RADIUS; j <= RADIUS; ++j) {
	//for(int i = 0; i <= 0; ++i) { for(int j = 0; j <= 0; ++j) {
			Sprite *tile = new_tile(i, j);
			tile->z_index = -100;

			reparent(tile, self);
		}
	}

	int a = rand_range(60, get_planet_info()->how_full);
	int b = rand_range(60, get_planet_info()->how_full);
	int item_count = a > b ? a : b;

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
		if(item_type == 0 && !info->has_rocks) { item_type = 1; }
		if(item_type == 1 && !info->has_plants) { item_type = 2; }
		if(item_type == 2 && !info->has_trees) { item_type = 0; }
		if(item_type == 0 && !info->has_rocks) { item_type = 1; }
		if(item_type == 1 && !info->has_plants) { item_type = 2; }
		if(item_type == 2 && !info->has_trees) { item_type = 0; } // Two loops through should handle most (all?) cases

		if(item_type == 0) {
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			if(length(pos) < 64) continue;

			Rock *rock = new(Rock);
			rock_texture(rock);
			set_lpos(rock, pos);
			reparent(rock, self);
		}
		else if(item_type == 1) {
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			if(length(pos) < 64) continue;
			Plant *rock = new(Plant);
			plant_texture(rock);
			
			set_lpos(rock, pos);
			reparent(rock, self);
		}
		else {
			vec2 pos;
			pos.x = rand_range(-24, 24) * 16;
			pos.y = rand_range(-30, 30) * 14;
			if(length(pos) < 64) continue;

			Tree *rock = new(Tree);
			tree_texture(rock);
			
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
			fade_spec(fade, FADE_TO_SHIP);
		}
	}
}

