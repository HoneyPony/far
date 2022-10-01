#include "my.ponygame.h"
#include "pony.main.h"

#include "render/render_context.h"

Player *player;

impl_begin {
	// Configure screen size
	ctx.screen.target_width = 360;
	ctx.screen.target_height = 220;

	reparent(new(Ship), root);

	player = new(Player);
	reparent(player, root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}
