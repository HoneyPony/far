#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_BookPrompt(BookPrompt *self) { }

// void destruct_BookPrompt(BookPrompt *self) { }

void tick_BookPrompt(BookPrompt *self, BookPromptTree *tree) {
	if(has_won) {
		tree->prompt->visible = false;
		return;
	}

	vec2 dif = sub(get_gpos(self), get_gpos(player));
	//float dist = length(dif);

	//logf_info("dif = %f %f", dif.x, dif.y);

	tree->prompt->visible = (abs(dif.x) < 24) && (abs(dif.y) < 24);

	if(keys.E.just_pressed && tree->prompt->visible) {
		book_menu->visible = true;
	}
	//logf_verbose("visible: 
}

