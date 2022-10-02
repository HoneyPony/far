@type BookPrompt : Node

@tick

@tree
	self : BookPrompt

	prompt : Sprite
		parent = self
		set_lpos($, vxy(0, 40));
		sprite_play($, &res.ui.manual_prompt_tex.loop);
		$->z_index = 80;