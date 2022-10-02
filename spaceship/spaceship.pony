@type Ship : Node

@tick
@construct

@tree
	self : Ship

	ship : Sprite
		parent = self
		sprite_play($, &res.spaceship.ship_tex.loop)
		$->z_index = -80;

	upgrade : UpgradePrompt
		parent = self
		set_lpos($, vxy(-3, 15));

	nav : NavPrompt
		parent = self
		set_lpos($, vxy(-3 + 362, 19 + 5));