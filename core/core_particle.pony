@type CoreParticle : Node
	float radius;
	float t;
	float rate;

@tick

@header	
	void core_par_spawn(CoreParticle *self);

@tree
	self : CoreParticle

	sprite : StaticSprite
		parent = self
		$->z_index = -200;