#include "my.ponygame.h"

#include "../text.h"
#include "../globals.h"

// Automatically copied header lines. May not be useful.

static float color_opts[] = {
	1, 1, 1,
	0.8, 0.8, 0.8,
	0.8, 0.4, 0.4,
	0.4, 0.8, 0.4,
	0.4, 0.4, 0.8,
//	0.9, 0.6, 0.3,
	0.6, 0.3, 0.9,
//	0.9, 0.9, 0.1
};

static PlanetInfo options[3];

bool barren(PlanetInfo p) {
	return !p.has_rocks && !p.has_plants && !p.has_trees;
}

PlanetInfo *get_planet_info() {
	return &options[nav_menu->current_option];
}

void standard_planet_gen(PlanetInfo *p) {
	p->x = rand_range(-10, 10) + 10;
	p->y = rand_range(-10, 10);
	float *color = color_opts + 3 * rand_range(0, 5);
	p->color[0] = color[0];
	p->color[1] = color[1];
	p->color[2] = color[2];
	p->color[3] = 1;
}

void generate_new_options() {
	options[0].has_rocks = true;
	options[0].has_plants = rand_range(0, 10) > 7;
	options[0].has_trees = false;
	options[0].icon = rand_range(0, 4);
	options[0].how_full = rand_range(60, 80);
	standard_planet_gen(&options[0]);


	options[1].has_rocks = rand_range(0, 10) > 3;
	options[1].has_plants = rand_range(0, 10) > 3;
	options[1].has_trees = rand_range(0, 12) > 11;
	options[1].icon = rand_range(0, 4);
	options[1].how_full = rand_range(70, 100);
	if(barren(options[1])) {
		options[1].has_plants = true;
	}
	standard_planet_gen(&options[1]);

	options[2].has_rocks = rand_range(0, 10) > 4;
	options[2].has_plants = rand_range(0, 10) > 2;
	options[2].has_trees = rand_range(0, 10) > 1;
	options[2].icon = rand_range(0, 4);
	options[2].how_full = rand_range(75, 110);
	if(barren(options[2])) {
		options[2].has_trees = 2;
	}
	standard_planet_gen(&options[2]);

	nav_menu->current_option = 0;
}

void construct_NavMenu(NavMenu *self) { 
	self->visible = false;
}

// void destruct_UpgradeMenu(UpgradeMenu *self) { }

static bool draw_button(NavMenu *self, vec2 mouse_pos, int x, int y, AnimFrame *frames) {
	int hover = 0;
	if(mouse_pos.x > x && mouse_pos.x <= x + 49) {
		if(mouse_pos.y > y && mouse_pos.y <= y + 15) {
			hover = 1;

			if(mouse.left.pressed) {
				hover = 2;
			}
		}
	}

	TexRenderer tr = {
		self, self,
		&frames[hover].texture,
		vxy(-x, -y),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 1,
		true
	};
	render_tex_on_node(tr);

	return hover > 0;
}

static bool draw_back_button(UpgradeMenu *self, vec2 mouse_pos, int x, int y) {
	int hover = 0;
	if(mouse_pos.x > x && mouse_pos.x <= x + 49) {
		if(mouse_pos.y > y && mouse_pos.y <= y + 15) {
			hover = 1;

			if(mouse.left.pressed) {
				hover = 2;
			}
		}
	}

	TexRenderer tr = {
		self, self,
		&res.ui.back_button_tex.loop.frames[hover].texture,
		vxy(-x, -y),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 1,
		true
	};
	render_tex_on_node(tr);

	return hover > 0;
}

/*
void draw_resource_icon(UpgradeMenu *self, int x, int y, int type, int amount, bool enough) {
	TexRenderer tr = {
		self, self,
		&resource_icons[type]->frames[0],
		vxy(-x - 7, -y + 1),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 1,
		true
	};
	render_tex_on_node(tr);
	draw_number_rjust(self, amount, x, y, enough ? color_black : color_red);
}*/

void tick_NavMenu(NavMenu *self, NavMenuTree *tree) {
	if(keys.Escape.just_pressed) {
		self->visible = false;
	}

	tree->sprite->visible = self->visible;
	tree->icon->visible = self->visible;
	if(!self->visible) return;

	vec2 m = mouse_screen();

	if(draw_back_button(self, m, -24 + 10, -84)) {
		if(mouse.left.just_released) {
			self->visible = false;
		}
	}

	#define OPT_X -112
	#define OPT_Y 49

	if(draw_button(self, m, OPT_X, OPT_Y, res.ui.button_nav_i_tex.loop.frames)) {
		if(mouse.left.just_released) {
			self->current_option = 0;
		}
	}

	if(battery_level >= 2) {
		if(draw_button(self, m, OPT_X, OPT_Y - 18, res.ui.button_nav_ii_tex.loop.frames)) {
			if(mouse.left.just_released) {
				self->current_option = 1;
			}
		}
	}

	if(battery_level >= 3) {
		if(draw_button(self, m, OPT_X, OPT_Y - 18 * 2, res.ui.button_nav_iii_tex.loop.frames)) {
			if(mouse.left.just_released) {
				self->current_option = 2;
			}
		}
	}

	int tex_index = get_planet_info()->icon;
	tree->icon->texture = &res.planets.icon_tex.loop.frames[tex_index].texture;
	set_lpos(tree->icon, vxy(get_planet_info()->x, get_planet_info()->y));
	tree->icon->r = get_planet_info()->color[0];
	tree->icon->g = get_planet_info()->color[1];
	tree->icon->b = get_planet_info()->color[2];
	
	if(hud->battery_charges >= 11) {
		if(draw_button(self, m, 70, OPT_Y , res.ui.button_nav_fly_tex.loop.frames)) {
			if(mouse.left.just_released) {
				fade_spec(fade, FADE_TO_PLANET);
				self->visible = false;
			}
		}
	}
}

