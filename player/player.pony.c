#include "my.ponygame.h"

#include "../globals.h"

// Automatically copied header lines. May not be useful.

void construct_Player(Player *self) {
	
}

// void destruct_Player(Player *self) { }

vec2 get_input() {
	vec2 result = vxy(0, 0);
	if(keys.A.pressed) {
		result.x -= 1;
	}
	if(keys.D.pressed) {
		result.x += 1;
	}
	if(keys.W.pressed) {
		result.y += 1;
	}
	if(keys.S.pressed) {
		result.y -= 1;
	}
	return norm(result);
}

#define RING_PARTICLE_TIME 0.15
#define TOOL_ANIM_TIME 0.4

void ring_particles(Player *self) {
	self->ring_timer += get_dt();
	if(self->ring_timer > RING_PARTICLE_TIME) {
		self->ring_timer -= RING_PARTICLE_TIME;

		PlayerRing *ring = new(PlayerRing);
		set_gpos(ring, add(get_gpos(self), vxy(0, 8)));
		reparent(ring, root);
	}
}

#define TOOL_CENTER -0.785398163397
#define TOOL_RANGE (PI)

#define TOOL_LEFT (PI * 0.6)
#define TOOL_RIGHT (-PI * 0.6)

#define TOOL_DECENTER (PI * 0.3)

/*float tool_rotation(float t) {
	if(t < 0.3) {
		return lerp(0.0, TOOL_LEFT, (t / 0.3));
	}
	if(t < 0.5) {
		return lerp(TOOL_LEFT, TOOL_RIGHT, (t - 0.3) / (0.5 - 0.3));
	}
	return lerp(TOOL_RIGHT, -2 * PI, (t - 0.5) / 0.5);
}*/

float tool_rotation(float t) {
	t = 1 - t;
	t = t * t;
	t = 1 - t;
	return lerp(TOOL_DECENTER, TOOL_DECENTER - 2 * PI, t);
}

void update_tool_pivot(Node *pivot, Node *radius, float anim) {
	float t = 1.0 - clamp(anim / TOOL_ANIM_TIME, 0.0, 1.0);
	float offset = tool_rotation(t);

	if(anim < 0) { offset = TOOL_DECENTER; }

	vec2 pos = get_gpos(pivot);
	vec2 mouse = mouse_global();

	vec2 dir = sub(mouse, pos);
	float angle = atan2(dir.y, dir.x) + TOOL_CENTER + offset;
	set_lrot(pivot, angle);

	float extend = (length(dir) - 30) / 100;
	extend = clamp(extend, 0, 1);
	extend = sqrt(extend);
	extend = lerp(0.0, 10.0, extend);
	set_lpos(radius, vxy(extend, extend));
}

void animate_tool(Player *self, PlayerTree *tree) {

}

void update_tail(Player *self, PlayerTree *tree) {
	float extend = (length(self->velocity) - 0) / 90;
	extend = clamp(extend, 0, 1);
	extend = sqrt(extend);
	extend = lerp(0.0, 3.0, extend);
	vec2 dir = self->velocity;
	dir = norm(dir);
	dir.y *= 0.25;

	set_lpos(tree->sprite, add(vxy(0, 8), mul(dir, 1)));

	// Account for sprite flippign
	dir.x *= get_lscale(tree->sprite).x;
	set_lpos(tree->tail, mul(dir, -extend));

	
}

void draw_cable(Player *self, PlayerTree *tree, float stretch) {
	set_gpos(tree->cable_pivot, add(get_gpos(tree->tail), vxy(0, -8)));

	TexRenderer tr = {
		tree->cable_pivot, self,
		&res.player.cable_tex.loop.frames[0].texture,
		vxy(0, 0),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 0.5,
		false
	};
	render_tex_on_node(tr);

	vec2 to_center = sub(vxy(0, 0), get_gpos(tree->cable_pivot));

	//float sx = get_lscale(tree->sprite).x;

	set_lrot(tree->cable_pivot, atan2(to_center.y, to_center.x));
	set_lscale(tree->cable_pivot, vxy(length(to_center) / 16.0, lerp(1.0, 0.25, stretch)));
}

void tick_Player(Player *self, PlayerTree *tree) {

	if(upgrade_menu->visible) return;
	// Retrive state
	// set_gpos(self, self->unrounded_pos);

	update_tool_pivot(tree->tool_pivot, tree->tool_radius, self->tool_anim);

	vec2 input = get_input();
	vec2 intended_vel = mul(input, 90);
	vec2 max_acc = sub(intended_vel, self->velocity);
	vec2 acc = mul(norm(max_acc), 400 * get_dt());
	if(length(acc) > length(max_acc)) {
		acc = max_acc;
	}

	self->velocity = add(self->velocity, acc);

	float clamping = (length(get_gpos(self)) - 400) / 20;
	clamping = clamp(clamping, 0, 1.1);

	vec2 in_pull = mul(norm(get_gpos(self)), -length(self->velocity));

	ltranslate(self, mul(self->velocity, get_dt()));
	ltranslate(self, mul(in_pull, clamping * get_dt()));
	//tree->sprite->a = 0.5;

	ring_particles(self);

	if(mouse.left.just_pressed) {
		//logf_verbose("mouse presssed");
		self->tool_anim = TOOL_ANIM_TIME;
	}

	if(self->tool_anim > 0) {
		animate_tool(self, tree);
		self->tool_anim -= get_dt();
	}

	if(self->velocity.x < -3) {
		set_lscale(tree->sprite, vxy(-1, 1));
	}
	if(self->velocity.x > 3) {
		set_lscale(tree->sprite, vxy(1, 1));
	}

	update_tail(self, tree);

	if(true) {
		float stretch = length(get_gpos(self)) / 420;
		stretch = clamp(stretch, 0, 1);
		draw_cable(self, tree, stretch);
	}

	int z_index = 700 - (int)get_gpos(self).y;
	tree->sprite->z_index = z_index;
	tree->tail->z_index = z_index;

	// Save state
	// self->unrounded_pos = get_gpos(self);
	// vec2 pos = get_gpos(self);
	// set_gpos(self, vxy(ceil(pos.x), floor(pos.y)));

	//vec2 c = get_gpos(self);
	//camera_point = add(camera_point, mul(sub(c, camera_point), 0.04));
	camera_point = add(get_gpos(self), vxy(0, 30));
}

