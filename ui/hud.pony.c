#include <stdio.h>

#include "my.ponygame.h"

#include "../text.h"

#include "render/render_context.h"

// Automatically copied header lines. May not be useful.

// void construct_Hud(Hud *self) { }

// void destruct_Hud(Hud *self) { }

#define SPRITE_HEIGHT 30

void draw_number(Node *on, int number, float x, float y, float color[4]) {
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

void draw_number_rjust(Node *on, int number, float x, float y, float color[4]) {
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

int sdf = 1000;

void tick_Hud(Hud *self, HudTree *tree) {
	int y = ctx.frame_height / 2 - SPRITE_HEIGHT * 0.5;

	set_lpos(self, vxy(0, y));

	draw_number_rjust(self, sdf, -130, 4, color_white);
	draw_number_rjust(self, 5, -130, -8, color_white);
	sdf += 10000;
}
