@type Player : Node
	vec2 velocity;
	vec2 unrounded_pos;

	float ring_timer;

	float tool_anim;

@construct
@tick

@tree
	self : Player

	sprite : Sprite
		parent = self
		set_lpos($, vxy(0, 8));
		sprite_play($, &res.player.player_tex.still);
		$->snap_relative = self;
		$->z_index = 5;

	tail : Sprite
		parent = sprite
		sprite_play($, &res.player.player_tail_tex.loop);
		$->snap_relative = self;
		$->z_index = 5;

	tool_pivot : Node
		parent = self
		set_lpos($, vxy(0, 12));

	tool_radius : Node
		parent = tool_pivot
		set_lpos($, vxy(0, 0));

	wrench : Sprite
		parent = tool_radius
		$->snap_relative = self;
		set_lpos($, vxy(10, 10));
		sprite_play($, &res.tools.wrench_tex.wrench);