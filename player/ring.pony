@type PlayerRing : Node
	float life;
	float y;

@tick
@construct

@tree
	self : PlayerRing

	sprite : Sprite
		parent = self
		sprite_play($, &res.player.ring2_tex.loop);