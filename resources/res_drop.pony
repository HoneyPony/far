@type ResDrop : Node
	float lerp_str;
	int kind;

@construct
@tick

@header
	void res_drop_set_type(ResDrop *drop, int type);

@tree
	self : ResDrop

	sprite : Sprite
		parent = self