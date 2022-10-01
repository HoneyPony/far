#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_Rock(Rock *self) { }

// void destruct_Rock(Rock *self) { }

void tick_Rock(Rock *self, RockTree *tree) {
	if(player->tool_anim > TOOL_ANIM_BREAK_POINT) {
		vec2 dif = sub(get_gpos(player->tree.wrench), get_gpos(self));
		if(length(dif) < 15) {
			for(int i = 0; i < 1; ++i) {
				ResDrop *drop = new(ResDrop);
				res_drop_set_type(drop, 0);
				
				vec2 pos = get_gpos(self);
				pos.x += randf_range(-4, 4);
				pos.y += randf_range(-4, 4);
				set_lpos(drop, pos);
				reparent(drop, root);
			}
			node_destroy(self);
		}
	}
}

