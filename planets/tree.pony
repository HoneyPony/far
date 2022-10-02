@type Tree : Node
	
@tick

@header
	void tree_texture(Tree *plant);

@tree
	self : Tree

	sprite : Sprite
		parent = self
		sprite_play($, &res.planets.tree1_tex.loop);
		$->z_index = 2;
		set_lpos($, vxy(0, 20));