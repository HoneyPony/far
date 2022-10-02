#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.
void fade_spec(Fade *self, int what) {
	if(self->t < 2) return;

	self->what_to_do = what;
	self->t = 0;
	self->fired = false;

	//logf_verbose("SET FAD!");
}

void fire_to_planet() {
	node_destroy(ship);
	ship = NULL; // Floating reference = bad news
	planet = new(Planet);
	reparent(planet, root);
	set_gpos(player, vxy(0, 0));
	on_planet = true;
	hud->battery_charges = 0;
}

void fire_to_ship() {
	// Always generate new planets when we return to the ship.
	node_destroy(planet);
	generate_new_options();
	ship = new(Ship);
	planet = NULL;
	on_planet = false;
	reparent(ship, root);
	
}

// void construct_Fade(Fade *self) { }

// void destruct_Fade(Fade *self) { }

extern void start_game();

void tick_Fade(Fade *self, FadeTree *tree) {
	//logf_verbose("fade t = %f", self->t);

	if(self->t >= 2) {
		tree->sprite->visible = false;
		return;
	} 

	

	tree->sprite->visible = true;
	self->t += get_dt() * 4.0;
	if(self->t >= 1) {
		if(!self->fired) {
			self->fired = true;
			if(self->what_to_do == FADE_TO_PLANET) {
				fire_to_planet();
			}
			else if(self->what_to_do == FADE_TO_SHIP) {
				fire_to_ship();
			}
			else if(self->what_to_do == FADE_FROM_INTRO) {
				start_game();
			}
		}
	}




	float a = 1 - abs(self->t - 1);
	tree->sprite->a = a;
}

