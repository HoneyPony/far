@type Core : Node

@construct

@tree
	self : Core

	core : Sprite
		parent = self
		sprite_play($, &res.core.core_tex.loop)
		$->z_index = -195;