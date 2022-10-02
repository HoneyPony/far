@type UpgradeMenu : Node

@construct
@tick

@tree
	self : UpgradeMenu
		$->z_index = 2005;

	sprite : Sprite
		parent = self
		sprite_play($, &res.ui.upgrade_menu_tex.loop);
		$->z_index = 2000;
		$->on_camera = true;