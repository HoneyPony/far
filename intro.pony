@type Intro : Node
	float t;

@tick

@tree
	self : Intro

	frame0 : StaticSprite
		parent = self
		$->texture = &res.intro_tex.loop.frames[0].texture;
		$->a = 0;

	frame1 : StaticSprite
		parent = self
		$->texture = &res.intro_tex.loop.frames[1].texture;
		$->a = 0;

	frame2 : StaticSprite
		parent = self
		$->texture = &res.intro_tex.loop.frames[2].texture;
		$->a = 0;

	frame3 : StaticSprite
		parent = self
		$->texture = &res.intro_tex.loop.frames[3].texture;
		$->a = 0;

	frame4 : StaticSprite
		parent = self
		$->texture = &res.intro_tex.loop.frames[4].texture;
		$->a = 0;
		$->z_index = 20;