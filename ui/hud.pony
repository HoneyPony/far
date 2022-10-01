@type Hud : Node

@tick

@tree
	self : Hud
		$->z_index = 1005;

	hud : Sprite
		parent = self
		sprite_play($, &res.ui.hud_tex.loop);
		$->z_index = 1000;
		$->on_camera = true;