#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void construct_UpgradePrompt(UpgradePrompt *self) { }

// void destruct_UpgradePrompt(UpgradePrompt *self) { }

void tick_UpgradePrompt(UpgradePrompt *self, UpgradePromptTree *tree) {
	vec2 dif = sub(get_gpos(self), get_gpos(player));
	//float dist = length(dif);

	//logf_info("dif = %f %f", dif.x, dif.y);

	tree->prompt->visible = (abs(dif.x) < 24) && (abs(dif.y) < 24);

	if(keys.E.just_pressed && tree->prompt->visible) {
		upgrade_menu->visible = true;
	}
	//logf_verbose("visible: %d", self->visible);
}

