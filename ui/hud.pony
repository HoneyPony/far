@type Hud : Node
	float battery_timer;
	int battery_charges;

@tick

@tree
	self : Hud
		$->z_index = 2005;

	hud : Sprite
		parent = self
		sprite_play($, &res.ui.hud_tex.loop);
		$->z_index = 2000;
		$->on_camera = true;

	battery : StaticSprite
		parent = hud
		set_lpos($, vxy(-8, 1));
		$->z_index = 2001;
		$->on_camera = true;
		$->snap_relative = self;
		$->texture = &res.ui.battery_tex.loop.frames[0].texture;