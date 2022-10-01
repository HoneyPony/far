#include "my.ponygame.h"
#include "pony.main.h"

#include "render/render_context.h"

Player *player;

impl_begin {
	clear_color[0] = 0;
	clear_color[1] = 0;
	clear_color[2] = 0;
	clear_color[3] = 1.0;

	// Configure screen size
	ctx.screen.target_width = 360;
	ctx.screen.target_height = 220;

	reparent(new(Ship), root);

	player = new(Player);
	reparent(player, root);

	reparent(new(Hud), root);

	//reparent(new(Cursor), root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}
