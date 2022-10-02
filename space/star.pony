@type Star : Node

@tick

@tree
	self : Star

	sprite : Sprite
		parent = self
		sprite_play($, &res.space.star_tex.loop);
		$->z_index = -100;