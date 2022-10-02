#include <stdio.h>

#include "my.ponygame.h"

#include "../text.h"
#include "../globals.h"

#include "render/render_context.h"

// Automatically copied header lines. May not be useful.

// void construct_Hud(Hud *self) { }

// void destruct_Hud(Hud *self) { }

#define SPRITE_HEIGHT 30

void draw_number(AnyNode *on_ptr, int number, float x, float y, float color[4]) {
	Node *on = on_ptr;
	char value[128] = {0};
	snprintf(value, 128, "%d", number);
	char *ptr = value;
	while(*ptr) {
		int index = *ptr - '0';
		if(index < 0 || index > 9) continue;

		TexRenderer tr = {
			on, on,
			NULL, // texture
			/* ... */
			vxy(-x, -y),
			snap_for_dimension(6), // Need to use even snapping for some reason
			snap_for_dimension(8),
			color[0], color[1], color[2], color[3],
			true
		};

		tr.tex = &res.ui.numbers_tex.loop.frames[index].texture;
		render_tex_on_node(tr);

		x += 6;
		++ptr;
	}
}

void draw_number_rjust(AnyNode *on_ptr, int number, float x, float y, float color[4]) {
	Node *on = on_ptr;
	char value[128] = {0};
	snprintf(value, 128, "%d", number);
	
	int char_index = strlen(value) - 1;

	while(char_index >= 0) {
		int index = value[char_index] - '0';
		if(index < 0 || index > 9) continue;

		TexRenderer tr = {
			on, on,
			NULL, // texture
			/* ... */
			vxy(-x, -y),
			snap_for_dimension(6), // Need to use even snapping for some reason
			snap_for_dimension(8),
			color[0], color[1], color[2], color[3],
			true
		};

		tr.tex = &res.ui.numbers_tex.loop.frames[index].texture;
		render_tex_on_node(tr);

		x -= 6;
		char_index -= 1;
	}
}

void tick_Hud(Hud *self, HudTree *tree) {
	int y = ctx.frame_height / 2 - SPRITE_HEIGHT * 0.5;

	set_lpos(self, vxy(0, y));

	//draw_number_rjust(self, light_years, -130, 4, color_white);
	//draw_number_rjust(self, speed, -130, -8, color_white);

	draw_number(self, ore_count, 60, 5, color_black);
	draw_number(self, plant_count, 60 + 49, 5, color_black);
	draw_number(self, wood_count, 60 + 49 * 2, 5, color_black);

	draw_number(self, nebula_count, 60, -8, color_black);
	draw_number(self, meteor_count, 60 + 49, -8, color_black);
	draw_number(self, neutron_count, 60 + 49 * 2, -8, color_black);

	if(!on_planet) {
		if(self->battery_timer <= 0) {
			if(self->battery_charges < 11) {
				self->battery_charges += 1;
				tree->battery->texture = &res.ui.battery_tex.loop.frames[self->battery_charges];
			}
			self->battery_timer = 2.0;
		}
		else {
			self->battery_timer -= get_dt();
		}
	}
}
