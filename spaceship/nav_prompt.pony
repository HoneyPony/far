@type NavPrompt : Node

@tick

@tree
	self : NavPrompt

	prompt : Sprite
		parent = self
		set_lpos($, vxy(0, 20));
		sprite_play($, &res.ui.nav_prompt_tex.loop);
		$->z_index = 80;