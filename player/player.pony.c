#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Player(Player *self) {
	
}

// void destruct_Player(Player *self) { }

vec2 get_input() {
	vec2 result = vxy(0, 0);
	if(keys.A.pressed) {
		result.x -= 1;
	}
	if(keys.D.pressed) {
		result.x += 1;
	}
	if(keys.W.pressed) {
		result.y += 1;
	}
	if(keys.S.pressed) {
		result.y -= 1;
	}
	return norm(result);
}

#define RING_PARTICLE_TIME 0.15

void ring_particles(Player *self) {
	self->ring_timer += get_dt();
	if(self->ring_timer > RING_PARTICLE_TIME) {
		self->ring_timer -= RING_PARTICLE_TIME;

		PlayerRing *ring = new(PlayerRing);
		set_gpos(ring, add(get_gpos(self), vxy(0, 12)));
		reparent(ring, root);
	}
}

void tick_Player(Player *self, PlayerTree *tree) {
	// Retrive state
	// set_gpos(self, self->unrounded_pos);

	vec2 input = get_input();
	vec2 intended_vel = mul(input, 90);
	vec2 max_acc = sub(intended_vel, self->velocity);
	vec2 acc = mul(norm(max_acc), 400 * get_dt());
	if(length(acc) > length(max_acc)) {
		acc = max_acc;
	}

	self->velocity = add(self->velocity, acc);

	ltranslate(self, mul(self->velocity, get_dt()));
	//tree->sprite->a = 0.5;

	ring_particles(self);


	// Save state
	// self->unrounded_pos = get_gpos(self);
	// vec2 pos = get_gpos(self);
	// set_gpos(self, vxy(ceil(pos.x), floor(pos.y)));

	//vec2 c = get_gpos(self);
	//camera_point = add(camera_point, mul(sub(c, camera_point), 0.04));
	camera_point = get_gpos(self);
}

