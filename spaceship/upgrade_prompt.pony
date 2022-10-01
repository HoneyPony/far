@type UpgradePrompt : Node

@tick

@tree
	self : UpgradePrompt

	prompt : Sprite
		parent = self
		set_lpos($, vxy(0, 20));
		sprite_play($, &res.ui.upgrade_station_prompt_tex.loop);
		$->z_index = 80;