#include "my.ponygame.h"

#include "../globals.h"
// Automatically copied header lines. May not be useful.

// void construct_NavPrompt(NavPrompt *self) { }

// void destruct_NavPrompt(NavPrompt *self) { }

void tick_NavPrompt(NavPrompt *self, NavPromptTree *tree) {
	if(has_won) {
		tree->prompt->visible = false;
		return;
	}

	vec2 dif = sub(get_gpos(self), get_gpos(player));
	//float dist = length(dif);

	//logf_info("dif = %f %f", dif.x, dif.y);

	tree->prompt->visible = (abs(dif.x) < 100) && (abs(dif.y) < 24);

	if(keys.E.just_pressed && tree->prompt->visible) {
		nav_menu->visible = true;
	}
}

