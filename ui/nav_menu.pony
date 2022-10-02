@type NavMenu : Node
	int current_option;
	bool was_open;

@construct
@tick

@tree
	self : NavMenu
		$->z_index = 2005;

	sprite : Sprite
		parent = self
		sprite_play($, &res.ui.nav_menu_tex.loop);
		$->z_index = 2000;
		$->on_camera = true;

	icon : StaticSprite
		parent = self
		$->z_index = 2010;
		$->on_camera = true;