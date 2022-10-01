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

	battery : StaticSprite
		parent = hud
		set_lpos($, vxy(-8, 1));
		$->z_index = 1001;
		$->on_camera = true;
		$->snap_relative = self;
		$->texture = &res.ui.battery_tex.loop.frames[0].texture;