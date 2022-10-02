@type SpaceObj : Node
	int type;

@tick

@header
	void space_obj_roll(SpaceObj *obj);

@tree
	self : SpaceObj

	sprite : Sprite
		parent = self
		sprite_play($, &res.space.neutron_s_tex.loop);
		$->z_index = -100;