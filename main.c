#include <stdlib.h>
#include <time.h>

#include "my.ponygame.h"
#include "pony.main.h"

#include "../globals.h"

#include "render/render_context.h"

const char *game_title = "Far";

bool on_planet;
bool has_won = false;

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

/*int ore_count = 999;
int plant_count = 999;
int wood_count = 999;
int nebula_count = 999;
int meteor_count = 999;
int neutron_count = 999;
*/

int get_drop_count() {
	if(wrench_level == 1) {
		return 1;
	}

	int a = rand_range(1, wrench_level + 1);
	int b = rand_range(1, wrench_level + 1);
	return a < b ? a : b;
}

int ly_speed() {
	int speeds[] = { 1, 3, 7, 15, 40, 90, 181, 375, 797,
		2550, 4949, 17208, 65726, 122535, 244099, 450898, 998765, 2531329, 5023937, 10249308 };

	return speeds[engine_level - 1];// * 100;
}

float get_battery_timer() {
	float timers[] = { 3.0, 2.2, 1.4, 0.8, 0.4 };
	return timers[battery_level - 1];
}

Player *player;
UpgradeMenu *upgrade_menu;
NavMenu *nav_menu;
Hud *hud;
Ship *ship;
Fade *fade;
Planet *planet;
BookMenu *book_menu;

bool should_pop = false;

Intro *intro;

float color_white[4] = {1, 1, 1, 1};
float color_black[4] = {0, 0, 0, 1};
float color_red[4] = {1, 0,0, 1};

double ly_left;
float increase_timer = 10.0;

bool in_game = false;

void start_game() {
	in_game = true;

	node_destroy(intro);

	ship = new(Ship);
	reparent(ship, root);
	on_planet = false;

	player = new(Player);
	set_gpos(player, vxy(-224 + 6, 100 - 4));
	reparent(player, root);

	//reparent(new(Ship), root);
	hud = new(Hud);
	reparent(hud, root);

	upgrade_menu = new(UpgradeMenu);
	reparent(upgrade_menu, root);
	//set_gpos(upgrade_menu, vxy(0, -10));

	nav_menu = new(NavMenu);
	reparent(nav_menu, root);
	//set_gpos(nav_menu, vxy(0, -10));

	book_menu = new(BookMenu);
	reparent(book_menu, root);
	//set_gpos(book_menu, vxy(0, -10));

	

	//reparent(new(Cursor), root)
	// Initial planet options
	generate_new_options();

	music_play(res.reaper.ship_snd);
}


impl_begin {
	ly_left = 1291503127;

	srand(time(NULL));

	clear_color[0] = 0;
	clear_color[1] = 0;
	clear_color[2] = 0;
	clear_color[3] = 1.0;

	// Configure screen size
	ctx.screen.target_width = 360;
	ctx.screen.target_height = 230;

	intro = new(Intro);
	reparent(intro, root);
	music_play_once(res.reaper.intro_snd);
	//start_game();

	fade = new(Fade);
	reparent(fade, root);

	//reparent(new(Planet), root);
	//on_planet = true;
}

impl_tick_start {
	should_pop = false;

	if(!in_game) {
		if(mouse.left.just_pressed && intro->t >= 7) {
			fade_spec(fade, FADE_FROM_INTRO);
		}
		return;
	}

	if(!on_planet) {
		ly_left -= (double)ly_speed() / 60.0;
		if(ly_left < 0) {
			ly_left = 0;
			if(!has_won) {
				Core *core = new(Core);
				set_gpos(core, CORE_CENTER);
				reparent(core, root);

				music_play_once(res.reaper.victory_snd);
			}
			has_won = true;
		}
	}
	increase_timer -= get_dt();
	if(increase_timer < 0) {
		ly_left += 10;
		increase_timer = 10;
	}
}

impl_tick_end {
	if(should_pop) {
		sound_play(res.sound.pop_snd);
	}
}
