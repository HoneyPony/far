#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Core(Core *self) {
	for(int i = 0; i < 3000; ++i) {
		CoreParticle *p = new(CoreParticle);
		core_par_spawn(p);
		reparent(p, root);
	}
}

// void destruct_Core(Core *self) { }

// void tick_Core(Core *self, CoreTree *tree) { }

