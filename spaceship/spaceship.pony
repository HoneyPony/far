@type Ship : Node


@tree
	self : Ship

	ship : Sprite
		parent = self
		sprite_play($, &res.spaceship.ship2_tex.loop)