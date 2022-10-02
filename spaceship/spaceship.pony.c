#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

void try_spawn(float negative) {
	int should_star = rand_range(0, 6) < 2;
	if(should_star) {
		Star *star = new(Star);
		set_lpos(star, vxy(1200 - negative, rand_range(-900, 900)));
		reparent(star, root);
	}

	int should_obj = rand_range(0, 80) < 3;
	if(should_obj) {
		SpaceObj *obj = new(SpaceObj);
		space_obj_roll(obj);
		set_lpos(obj, vxy(1200 - negative, rand_range(-800, 800)));
		reparent(obj, root);
	}
}

void construct_Ship(Ship *self) {

	
	// Pretend the ship had existed for 200 frames
	float t = 0;
	for(int i = 0; i < 3000; ++i) {
		try_spawn(t);
		t += 1;
	}
}

// void destruct_Ship(Ship *self) { }



void tick_Ship(Ship *self, ShipTree *tree) { 
	if(has_won)  {
		return; // No spawning stars after won
	}

	try_spawn(0);
}

