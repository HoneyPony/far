@type UpgradeMenu : Node

@construct
@tick

@tree
	self : UpgradeMenu
		$->z_index = 1005;

	sprite : Sprite
		parent = self
		sprite_play($, &res.ui.upgrade_menu_tex.loop);
		$->z_index = 1000;
		$->on_camera = true;