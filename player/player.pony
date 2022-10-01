@type Player : Node
	vec2 velocity;
	vec2 unrounded_pos;

	float ring_timer;

@construct
@tick

@tree
	self : Player

	sprite : Sprite
		parent = self
		set_lpos($, vxy(0, 8));
		sprite_play($, &res.player.player_tex.loop);
		$->z_index = 5;