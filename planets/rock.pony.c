#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_Rock(Rock *self) { }

// void destruct_Rock(Rock *self) { }

void rock_texture(Rock *self) {
	AnimHandle* list[] = {&res.planets.rock1_tex.loop, &res.planets.rock2_tex.loop, &res.planets.rock3_tex.loop};

	sprite_play(self->tree.sprite, list[rand_range(0, 2)]);
}

void tick_Rock(Rock *self, RockTree *tree) {
	tree->sprite->z_index = 700 - (int)get_gpos(self).y;

	if(player->tool_anim > TOOL_ANIM_BREAK_POINT) {
		vec2 dif = sub(get_gpos(player->tree.wrench), get_gpos(self));
		if(length(dif) < 15) {
			int drops = get_drop_count();
			for(int i = 0; i < drops; ++i) {
				ResDrop *drop = new(ResDrop);
				res_drop_set_type(drop, 0);
				
				vec2 pos = get_gpos(self);
				pos.x += randf_range(-6, 6);
				pos.y += randf_range(-6, 6);
				set_lpos(drop, pos);
				reparent(drop, root);
			}
			node_destroy(self);
		}
	}
}

