#include <stdlib.h>
#include <time.h>

#include "my.ponygame.h"
#include "pony.main.h"

#include "render/render_context.h"

bool on_planet;

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

int get_drop_count() {
	if(wrench_level == 1) {
		return 1;
	}

	int a = rand_range(1, wrench_level + 1);
	int b = rand_range(1, wrench_level + 1);
	return a < b ? a : b;
}

Player *player;
UpgradeMenu *upgrade_menu;
NavMenu *nav_menu;
Hud *hud;
Ship *ship;

float color_white[4] = {1, 1, 1, 1};
float color_black[4] = {0, 0, 0, 1};
float color_red[4] = {1, 0,0, 1};

impl_begin {
	srand(time(NULL));

	clear_color[0] = 0;
	clear_color[1] = 0;
	clear_color[2] = 0;
	clear_color[3] = 1.0;

	// Configure screen size
	ctx.screen.target_width = 360;
	ctx.screen.target_height = 220;

	ship = new(Ship);
	reparent(ship, root);
	on_planet = false;

	

	player = new(Player);
	reparent(player, root);

	//reparent(new(Ship), root);
	hud = new(Hud);
	reparent(hud, root);

	upgrade_menu = new(UpgradeMenu);
	reparent(upgrade_menu, root);

	nav_menu = new(NavMenu);
	reparent(nav_menu, root);

	//reparent(new(Cursor), root)
	// Initial planet options
	generate_new_options();

	//reparent(new(Planet), root);
	//on_planet = true;
}

impl_tick_start {
	
}

impl_tick_end {
	
}
