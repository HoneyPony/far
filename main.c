#include "my.ponygame.h"
#include "pony.main.h"

#include "render/render_context.h"

int engine_level = 1;
int battery_level = 1;
int solar_level = 1;
int wrench_level = 1;

int ore_count = 0;
int plant_count = 0;
int wood_count = 0;
int nebula_count = 0;
int meteor_count = 0;
int neutron_count = 0;

Player *player;
UpgradeMenu *upgrade_menu;

 float color_white[4] = {1, 1, 1, 1};
 float color_black[4] = {0, 0, 0, 1};
 float color_red[4] = {1, 0,0, 1};

impl_begin {
	clear_color[0] = 0;
	clear_color[1] = 0;
	clear_color[2] = 0;
	clear_color[3] = 1.0;

	// Configure screen size
	ctx.screen.target_width = 360;
	ctx.screen.target_height = 220;

	reparent(new(Planet), root);

	player = new(Player);
	reparent(player, root);

	//reparent(new(Ship), root);

	reparent(new(Hud), root);

	upgrade_menu = new(UpgradeMenu);
	reparent(upgrade_menu, root);

	//reparent(new(Cursor), root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}
