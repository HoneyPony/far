#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_Star(Star *self) { }

// void destruct_Star(Star *self) { }

void tick_Star(Star *self, StarTree *tree) {
	if(on_planet) {
		node_destroy(self);
		return;
	}

	ltranslate(self, vxy(-60 * get_dt(), 0));

	if(get_lpos(self).x < -1000) {
		node_destroy(self);
	}
}

