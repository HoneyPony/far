@type Planet : Node
	int32_t seed;

@construct
@tick

@tree
	self : Planet

	pod : Sprite
		parent = self
		sprite_play($, &res.planets.pod_tex.loop);
		set_lpos($, vxy(0, 28));

	ship_prompt : Sprite
		parent = self
		sprite_play($, &res.ui.ship_prompt_tex.loop);
		set_lpos($, vxy(0, 70));