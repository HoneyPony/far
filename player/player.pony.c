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

void draw_cable(Player *self, PlayerTree *tree, float stretch, float alpha) {
	set_gpos(tree->cable_pivot, add(get_gpos(tree->tail), vxy(0, -8)));

	TexRenderer tr = {
		tree->cable_pivot, self,
		&res.player.cable_tex.loop.frames[0].texture,
		vxy(0, 0),
		SNAP_EVEN,
		SNAP_EVEN,
		1, 1, 1, 0.5 * alpha,
		false
	};
	render_tex_on_node(tr);

	vec2 to_center = sub(vxy(0, 0), get_gpos(tree->cable_pivot));

	//float sx = get_lscale(tree->sprite).x;

	set_lrot(tree->cable_pivot, atan2(to_center.y, to_center.x));
	set_lscale(tree->cable_pivot, vxy(length(to_center) / 16.0, lerp(1.0, 0.25, stretch)));
}

typedef struct {
	vec2 start;
	vec2 end;
} Wall;

void raycast(vec2 from, vec2 *ray_ptr, vec2 *second, Wall w) {
	vec2 D = sub(w.end, w.start);
	float s = 0;
	float t = 0;

	vec2 ray = *ray_ptr;

	if(ray.x == 0) {
		// No intersection
		if(D.x == 0) {
			return;
		}

		s = (from.x - w.start.x) / D.x;
		t = (w.start.y + D.y * s - from.y) / ray.y;
	}
	else if(ray.y == 0) {
		if(D.y == 0) {
			return;
		}

		s = (from.y - w.start.y) / D.y;
		t = (w.start.x + D.x * s - from.x) / ray.x;
	}
	else {
		float F = ray.y / ray.x;
		float num = from.y + F * (w.start.x - from.x) - w.start.y;
		float denom = D.y - D.x * F;
		s = num / denom;
		t = (w.start.x + D.x * s - from.x) / ray.x;
	}

	//logf_verbose("s = %f t = %f", s, t);

	// ray intersection
	if(s >= 0 && s <= 1) {
		if(t >= 0 && t <= 1) {
			float scale_up = 0.3 * (90 / length(ray));
			float c = clamp((1 + scale_up) * t - scale_up, 0, 1);

			vec2 proj = mul(D, dot(ray, D) / dot(D, D));
			vec2 proj2 = mul(D, dot(*second, D) / dot(D, D));

			vec2 towards = sub(ray, proj);
			vec2 towards2 = sub(*second, proj2);

			//logf_verbose("x = %f", proj.x);
			*ray_ptr = add(proj, mul(towards, c));
			*second = add(proj2, mul(towards2, c));
		}
	}
}

Wall wall(float x, float y, float x2, float y2) {
	return (Wall){vxy(x, y), vxy(x2, y2)};
}

#define WALL(a, b, c, d)\
raycast(pos, dir, secondary, wall(a, b, c, d));

void collisions(vec2 pos, vec2 *dir, vec2 *secondary) {
	if(length(*dir) < 0.05) {
		*dir = vxy(0, 0);
		*secondary = vxy(0, 0);
		return;
	}

	WALL(-52, 27, 46, 27) // Console 1
	WALL(46, 27, 46, 50) // Console right
	WALL(-52, 27, -52, 50) // Console left
	
	WALL(159, 44, 202, 1)
	WALL(188, 17, 188, -101)
	WALL(188, -101, 334, -101)
	WALL(334, -101, 334, -17) // left nav entrance
	WALL(334, -17, 228, -1) // left nav angle
	WALL(239 + 8, -14, 239 + 8, 100) // left nav wall
	WALL(226, 31, 500, 31) // nav back
	WALL(476 - 8, 57, 476 - 8, -19) // right nav wall
	WALL(490, 4, 380, -17) // right nav angle
	WALL(380, -17, 380, -101) // right nav entrance
	WALL(380, -101, 469, -101) // wall near entrance up
	WALL(469, -101, 534, -69) // wall angle
	WALL(534, -69, 534, 105) // entrance left wall
	WALL(534, 42, 580, 42) // EXIT sign
	WALL(580, 42, 580, 200) // Ship back
	WALL(580, 200, -347, 200) // Ship back
	WALL(-347, 200, -347, -240) // ship left wall
	WALL(-347, -240, 482, -240) // ship front wall
	WALL(482, -240, 581, -191) // ship diagonal front
	WALL(581, -191, 581, -127 - 8) // ship up right
	WALL(581, -127 - 8, 477, -173 - 8) // ship diagnoal inner front
	WALL(-330, -170 - 8, 510, -170 - 8) // ship inner front
	WALL(-307, -180, -307, 180) // ship right iner wall
	WALL(-326, 126, -132, 126) // wall near book

	WALL(-155 + 2, 180, -155 + 2, 40) // left inner wall
	WALL(-155 + 2, 40, 180, 40) // wall behind upgrade console

	WALL(-237 + 2, 112, -200 + 2, 112) // Book console
	WALL(-237 + 2, 112, -237 + 2, 150) // Book console
	WALL(-200 + 2, 112, -200 + 2, 150) // Book console

	WALL(-200, -25, 142, -25) // middle thing
	WALL(142, -25, 142, -100)
	WALL(142, -100, -200, -100)
	WALL(-200, -25, -200, -100)
}

void tick_Player(Player *self, PlayerTree *tree) {

	if(upgrade_menu->visible) return;
	if(book_menu->visible) return;
	if(nav_menu->visible) return;
	// Retrive state
	// set_gpos(self, self->unrounded_pos);

	update_tool_pivot(tree->tool_pivot, tree->tool_radius, self->tool_anim);

	int max_radius = on_planet ? 400 : 800;

	vec2 input = get_input();
	vec2 intended_vel = mul(input, 90);
	vec2 max_acc = sub(intended_vel, self->velocity);
	vec2 acc = mul(norm(max_acc), 400 * get_dt());
	if(length(acc) > length(max_acc)) {
		acc = max_acc;
	}

	self->velocity = add(self->velocity, acc);

	float clamping = (length(get_gpos(self)) - max_radius) / 20;
	clamping = clamp(clamping, 0, 1.1);

	vec2 in_pull = mul(norm(get_gpos(self)), -length(self->velocity));

	vec2 translation = mul(self->velocity, get_dt());
	if(!has_won) { // Disable cable when you win
		translation = add(translation, mul(in_pull, clamping * get_dt()));
	}

	//float actual_amount = 1;
	if(!on_planet) {
		collisions(get_gpos(self), &translation, &self->velocity);
	}

	//self->velocity = mul(self->velocity, actual_amount);
	//ltranslate(self, mul(self->velocity, get_dt()));
	//ltranslate(self, mul(in_pull, clamping * get_dt()));
	ltranslate(self, translation);
	//tree->sprite->a = 0.5;

	ring_particles(self);

	if(mouse.left.just_pressed) {
		//logf_verbose("mouse presssed");
		self->tool_anim = TOOL_ANIM_TIME;
		sound_play(rand_range(0, 1) < 1 ? res.sound.swing_snd : res.sound.swing2_snd);
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

	// Completely disable cable when you win
	if(!has_won) {
		float ship_cable_alpha = clamp((length(get_gpos(self)) - 700) / 100, 0.0, 1.0);
		float cable_alpha = on_planet ? 1.0 : ship_cable_alpha;
		float stretch = length(get_gpos(self)) / (max_radius + 20);
		stretch = clamp(stretch, 0, 1);
		draw_cable(self, tree, stretch, cable_alpha);
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

	//logf_info("player pos = %f %f", get_gpos(self).x, get_gpos(self).y);
}

