@type Ship : Node


@tree
	self : Ship

	ship : Sprite
		parent = self
		sprite_play($, &res.spaceship.ship_tex.loop)
		$->z_index = -80;

	upgrade : UpgradePrompt
		parent = self
		set_lpos($, vxy(-3, 15));