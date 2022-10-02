#include "my.ponygame.h"

#include "../text.h"
#include "../globals.h"

// Automatically copied header lines. May not be useful.

void construct_UpgradeMenu(UpgradeMenu *self) { 
	self->visible = false;
}

// void destruct_UpgradeMenu(UpgradeMenu *self) { }

AnimHandle* resource_icons[] = {
	&res.resources.ore_tex.loop,
	&res.resources.plant_tex.loop,
	&res.resources.wood_tex.loop,
	&res.resources.nebula_tex.loop,
	&res.resources.meteor_tex.loop,
	&res.resources.neutron_tex.loop,
};

bool draw_button(UpgradeMenu *self, vec2 mouse_pos, int x, int y) {
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
		&res.ui.upgrade_button_tex.loop.frames[hover].texture,
		vxy(-x, -y),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 1,
		true
	};
	render_tex_on_node(tr);

	return hover > 0;
}

bool draw_back_button(UpgradeMenu *self, vec2 mouse_pos, int x, int y) {
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
}

typedef struct {
	int kind;
	int amount;
} UpgradeRequirement;



void reset_upreq(UpgradeRequirement out[3]) {
	out[0].kind = -1;
	out[1].kind = -1;
	out[2].kind = -1;
}

UpgradeRequirement req(int kind, int amount) {
	return (UpgradeRequirement){ kind, amount };
}

int res_count(int kind) {
	switch(kind) {
		case ORE: return ore_count;
		case PLANT: return plant_count;
		case WOOD: return wood_count;
		case NEBULA: return nebula_count;
		case METEOR: return meteor_count;
		case NEUTRON: return neutron_count;
		default: return 0;
	}
}

void res_add(int kind, int amount) {
	switch(kind) {
		case ORE:  ore_count += amount; break;
		case PLANT:  plant_count += amount; break;
		case WOOD:  wood_count += amount; break;
		case NEBULA:  nebula_count += amount; break;
		case METEOR:  meteor_count += amount; break;
		case NEUTRON:  neutron_count += amount; break;
		default: return;
	}
}

void get_upreq_engine(int level, UpgradeRequirement out[3]) {
	if(level == 1) {
		out[0] = req(ORE, 20);
		out[1] = req(WOOD, 12);
		out[2] = req(NEUTRON, 3);
	}
	else {
		int x = level - 1;
		int y = level - 4;
		if(y < 0) y = 0;
		out[0] = req(ORE, 20 + x * (5 + y));
		out[1] = req(WOOD, 12 + x * (3 + y));
		out[2] = req(NEUTRON, 3 + x * 3);
	}
}

void get_upreq_battery(int level, UpgradeRequirement out[3]) {
	if(level == 1) {
		out[0] = req(ORE, 30);
	}
	if(level == 2) {
		out[0] = req(ORE, 40);
		out[1] = req(NEBULA, 10);
		out[2] = req(METEOR, 10);
	}
}

void get_upreq_solar(int level, UpgradeRequirement out[3]) {
	if(level == 1) {
		out[0] = req(PLANT, 30);
		out[1] = req(NEBULA, 8);
	}
	if(level == 2) {
		out[0] = req(PLANT, 35);
		out[1] = req(NEBULA, 12);
		out[2] = req(NEUTRON, 1);
	}
	if(level == 3) {
		out[0] = req(PLANT, 40);
		out[1] = req(NEBULA, 12);
		out[2] = req(NEUTRON, 3);
	}
	if(level == 4) {
		out[0] = req(PLANT, 60);
		out[1] = req(NEBULA, 20);
		out[2] = req(NEUTRON, 10);
	}
}

void get_upreq_wrench(int level, UpgradeRequirement out[3]) {
	if(level == 1) {
		out[0] = req(ORE, 40);
	}
	else if(level == 2) {
		out[0] = req(ORE, 40);
		out[1] = req(METEOR, 10);
	}
	else if(level == 3) {
		out[0] = req(ORE, 40);
		out[1] = req(WOOD, 20);
		out[2] = req(METEOR, 10);
	}
	else {
		int x = level - 3;
		int y = level - 8;
		if(y < 0) y = 0;
		out[0] = req(ORE, 40 + x * 5);
		out[1] = req(WOOD, 20 + x * 10);
		out[2] = req(METEOR, 10 + x * (1 + y));
	}
}

bool draw_upgrade_reqs(UpgradeMenu *self, int y, UpgradeRequirement arr[3]) {
	int x = -42 + 5;
	
	bool can_upgrade = true;

	for(int i = 0; i < 3; ++i) {
		if(arr[i].kind >= 0 && arr[i].kind <= 5) {
			bool enough = arr[i].amount <= res_count(arr[i].kind);
			if(!enough) can_upgrade = false;
			draw_resource_icon(self, x, y, arr[i].kind, arr[i].amount, enough);
			x += 35;
		}
	}

	return can_upgrade;
}

void draw_num_or_max(UpgradeMenu *self, int x, int y, int level, int max) {
	if(level >= max) {
		TexRenderer tr = {
			self, self,
			&res.ui.max_tex.loop.frames[0].texture, // texture
			vxy(-x, -y),
			SNAP_EVEN, // Need to use even snapping for some reason
			SNAP_EVEN,
			1, 1, 1, 1,
			true
		};
		render_tex_on_node(tr);
		return;
	}

	draw_number(self, level, x, y, color_black);
}

void spend_reqs(UpgradeRequirement arr[3]) {
	for(int i = 0; i < 3; ++i) {
		res_add(arr[i].kind, -arr[i].amount);
	}
}

void tick_UpgradeMenu(UpgradeMenu *self, UpgradeMenuTree *tree) {
	if(keys.Escape.just_pressed) {
		self->visible = false;
	}

	tree->sprite->visible = self->visible;
	if(!self->visible) return;



	draw_num_or_max(self, -76, 42, engine_level, MAX_ENGINE);
	draw_num_or_max(self, -76, 42 - 31, battery_level, MAX_BATTERY);
	draw_num_or_max(self, -76, 42 - 2 * 31, solar_level, MAX_SOLAR);
	draw_num_or_max(self, -76, 42 - 3 * 31, wrench_level, MAX_WRENCH);

	UpgradeRequirement arr[3];

	vec2 m = mouse_screen();

	reset_upreq(arr);
	get_upreq_engine(engine_level, arr);
	if(draw_upgrade_reqs(self, 42, arr) && (engine_level < MAX_ENGINE)) {
		if(draw_button(self, m, 60, 44)) {
			if(mouse.left.just_released) {
				spend_reqs(arr);
				engine_level += 1;
				if(engine_level > MAX_ENGINE) engine_level = MAX_ENGINE;
			}
		}
	}

	reset_upreq(arr);
	get_upreq_battery(battery_level, arr);
	if(draw_upgrade_reqs(self, 42 - 31, arr) && (battery_level < MAX_BATTERY)) {
		if(draw_button(self, m, 60, 44 - 31)) {
			if(mouse.left.just_released) {
				spend_reqs(arr);
				battery_level += 1;
				if(battery_level > MAX_BATTERY) battery_level = MAX_BATTERY;
			}
		}
	}

	reset_upreq(arr);
	get_upreq_solar(solar_level, arr);
	if(draw_upgrade_reqs(self, 42 - 31 * 2, arr) && (solar_level < MAX_SOLAR)) {
		if(draw_button(self, m, 60, 44 - 31 * 2)) {
			if(mouse.left.just_released) {
				spend_reqs(arr);
				solar_level += 1;
				if(solar_level > MAX_SOLAR) solar_level = MAX_SOLAR;
			}
		}
	}

	reset_upreq(arr);
	get_upreq_wrench(wrench_level, arr);
	if(draw_upgrade_reqs(self, 42 - 31 * 3, arr) && (wrench_level < MAX_WRENCH)) {
		if(draw_button(self, m, 60, 44 - 31 * 3)) {
			if(mouse.left.just_released) {
				spend_reqs(arr);
				wrench_level += 1; 
				if(wrench_level > MAX_WRENCH) wrench_level = MAX_WRENCH;
			}
		}
	}

	if(draw_back_button(self, m, -28, -80)) {
		if(mouse.left.just_released) {
			self->visible = false;
		}
	}
}

