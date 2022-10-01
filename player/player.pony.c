#include "my.ponygame.h"

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
		set_gpos(ring, add(get_gpos(self), vxy(0, 12)));
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

void tick_Player(Player *self, PlayerTree *tree) {
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

	ltranslate(self, mul(self->velocity, get_dt()));
	//tree->sprite->a = 0.5;

	ring_particles(self);

	if(mouse.left.just_pressed) {
		logf_verbose("mouse presssed");
		self->tool_anim = TOOL_ANIM_TIME;
	}

	if(self->tool_anim > 0) {
		animate_tool(self, tree);
		self->tool_anim -= get_dt();
	}


	// Save state
	// self->unrounded_pos = get_gpos(self);
	// vec2 pos = get_gpos(self);
	// set_gpos(self, vxy(ceil(pos.x), floor(pos.y)));

	//vec2 c = get_gpos(self);
	//camera_point = add(camera_point, mul(sub(c, camera_point), 0.04));
	camera_point = get_gpos(self);
}

