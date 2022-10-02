@type Plant : Node
	
@construct
@tick

@header
	void plant_texture(Plant *plant);

@tree
	self : Plant

	sprite : Sprite
		parent = self
		sprite_play($, &res.planets.plant1_tex.loop);
		$->z_index = 2;
		set_lpos($, vxy(0, 8));