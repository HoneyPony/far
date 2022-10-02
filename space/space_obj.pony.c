#include "my.ponygame.h"

#include "../globals.h"

static AnimHandle *space_obj_sprites[] = {
	&res.space.nebula_s_tex.loop,
	&res.space.meteor_s_tex.loop,
	&res.space.neutron_s_tex.loop
};

// Automatically copied header lines. May not be useful.
void space_obj_roll(SpaceObj *obj) {
	int x = rand_range(0, 20);
	int type = NEBULA;
	if(x > 10) type = METEOR;
	if(x > 16) type = NEUTRON;

	obj->type = type;
	sprite_play(obj->tree.sprite, space_obj_sprites[type - NEBULA]);
}

// void construct_SpaceObj(SpaceObj *self) { }

// void destruct_SpaceObj(SpaceObj *self) { }

void tick_SpaceObj(SpaceObj *self, SpaceObjTree *tree) {
	ltranslate(self, vxy(-60 * get_dt(), 0));

	if(on_planet) {
		node_destroy(self);
		return;
	}

	if(get_lpos(self).x < -1020) {
		node_destroy(self);
		return;
	}

	vec2 pos = get_lpos(self);
	if(pos.x < 575 && pos.x > -350) {
		if(pos.y < 225 && pos.y > -240) {
			return;
		}
	}

	if(player->tool_anim > TOOL_ANIM_BREAK_POINT) {
		vec2 dif = sub(get_gpos(player->tree.wrench), get_gpos(self));
		if(length(dif) < 20) {
			int drops = get_drop_count();
			for(int i = 0; i < drops; ++i) {
				ResDrop *drop = new(ResDrop);
				res_drop_set_type(drop, self->type);
				
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

