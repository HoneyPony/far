@type Fade : Node
	float t;
	int what_to_do;
	bool fired;

@tick

@header
	void fade_spec(Fade *self, int what);
	#define FADE_TO_PLANET 0
	#define FADE_TO_SHIP 1
	#define FADE_FROM_INTRO 2

@tree
	self : Fade
		$->t = 3;

	sprite : Sprite
		parent = self
		sprite_play($, &res.fader_tex.loop);
		set_lscale($, vxy(128, 128));
		$->on_camera = true;
		$->z_index = 4000;