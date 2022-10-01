#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

#define LIFETIME 0.6

extern Player *player;

void construct_PlayerRing(PlayerRing *self) {
	self->life = LIFETIME;
}

// void destruct_PlayerRing(PlayerRing *self) { }

void tick_PlayerRing(PlayerRing *self, PlayerRingTree *tree) {
	self->life -= get_dt();
	if(self->life < 0) {
		node_destroy(self);
		return;
	}

	float t = self->life / LIFETIME;
	tree->sprite->a = t;
	// TODO: Y sort...
	tree->sprite->z_index = 4;
	t = 1 - t;
	t = t * t * t;
	t = 1 - t;
	set_lscale(self, vxy(t, t));
	
	//self->y -= 30 * get_dt();
	ltranslate(self, vxy(0, -15 * get_dt()));


	//vec2 pos = get_gpos(self);
	//vec2 ppos = add(get_gpos(player), vxy(0, 12 + self->y));
	//pos.y += (ppos.y - pos.y) * 0.5 * t;
	//pos = add(pos, mul(sub(ppos, pos), t * 0.2));
	//set_gpos(self, pos);
}

