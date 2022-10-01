@type Ship : Node


@tree
	self : Ship

	ship : Sprite
		parent = self
		sprite_play($, &res.spaceship.ship_tex.loop)
		$->z_index = -80;