#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_CoreParticle(CoreParticle *self) { }

// void destruct_CoreParticle(CoreParticle *self) { }

void core_par_spawn(CoreParticle *self) {
	self->tree.sprite->texture = &res.core.particle_tex.loop.frames[rand_range(0, 3)].texture;
	self->radius = randf_range(40, 900);
	self->t = randf_range(0, 6.28);
	self->rate = (randf_range(0, 1) * 40) / self->radius;
	

	//float dec_scale = clamp(self->radius / 400.0, 0.0, 1.0);
	//dec_scale = 2.0 - dec_scale;

	float scale = randf_range(0.1, 0.3);
	set_lscale(self, vxy(scale, scale));

	set_lrot(self, randf_range(0, 6.28));
}

void tick_CoreParticle(CoreParticle *self, CoreParticleTree *tree) {
	self->t += self->rate * get_dt();
	while(self->t > 2 * PI) {
		self->t -= 2 * PI;
	}

	vec2 pos = vxy(cos(self->t) * self->radius, sin(self->t) * self->radius);

	set_lpos(self, add(CORE_CENTER, pos));
	//tree->sprite->a = 0.2;
}

