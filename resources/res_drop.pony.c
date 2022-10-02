#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

void res_drop_set_type(ResDrop *drop, int type) {
	Sprite *sprite = drop->tree.sprite;

	sprite_play(sprite, resource_icons[type]);
	drop->kind = type;
}

void construct_ResDrop(ResDrop *self) {
	self->lerp_str = -0.2;
}

// void destruct_ResDrop(ResDrop *self) { }

extern bool should_pop;

void tick_ResDrop(ResDrop *self, ResDropTree *tree) {
	vec2 pos = get_gpos(self);
	pos = add(pos, mul(sub(get_gpos(player), pos), clamp(self->lerp_str, 0.0, 1.0)));
	set_gpos(self, pos);

	float dist = length(sub(get_gpos(player), pos));
	float t = dist / 2;
	t = clamp(t, 0.0, 1.0);
	set_lscale(tree->sprite, vxy(t, t));

	self->lerp_str += get_dt() * 1.0;
	self->lerp_str = clamp(self->lerp_str, -1.0, 1.0);

	if(dist < 1 || self->lerp_str > 0.40) {
		res_add(self->kind, 1);
		should_pop = true;
		node_destroy(self);
	}
}

