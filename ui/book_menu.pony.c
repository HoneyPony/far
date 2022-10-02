#include "my.ponygame.h"

#include "../text.h"
#include "../globals.h"

// Automatically copied header lines. May not be useful.

// void destruct_UpgradeMenu(UpgradeMenu *self) { }

static bool draw_button(BookMenu *self, vec2 mouse_pos, int x, int y, AnimFrame *frames) {
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

static bool draw_back_button(BookMenu *self, vec2 mouse_pos, int x, int y) {
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



// Automatically copied header lines. May not be useful.

void construct_BookMenu(BookMenu *self) {
	self->visible = false;
}

#define LAST_INDEX 8

// void destruct_BookMenu(BookMenu *self) { }

void tick_BookMenu(BookMenu *self, BookMenuTree *tree) {
	if(keys.Escape.just_pressed) {
		self->visible = false;
	}

	if(has_won)  {
		self->visible = false;
	}

	tree->sprite->visible = self->visible;
	tree->book->visible = self->visible;
	if(!self->visible) return;

	tree->book->texture = &res.ui.manual_tex.loop.frames[self->current_page].texture;

	vec2 m = mouse_screen();

	if(draw_back_button(self, m, -24, -84)) {
		if(mouse.left.just_released) {
			self->visible = false;
		}
	}

	if(draw_button(self, m, -24 - 60, -84, res.ui.button_left_tex.loop.frames)) {
		if(mouse.left.just_released) {
			self->current_page -= 1;
			if(self->current_page < 0) {
				self->current_page = 0;
			}
		}
	}

	if(draw_button(self, m, -24 + 60, -84, res.ui.button_right_tex.loop.frames)) {
		if(mouse.left.just_released) {
			self->current_page += 1;
			if(self->current_page >= LAST_INDEX) {
				self->current_page = LAST_INDEX;
			}
		}
	}
}

