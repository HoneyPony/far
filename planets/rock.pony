@type Rock : Node
	
@tick

@tree
	self : Rock

	sprite : Sprite
		parent = self
		sprite_play($, &res.planets.rock1_tex.loop);
		$->z_index = 2;
		set_lpos($, vxy(0, 8));