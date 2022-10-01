@type Cursor : Node

@tick

@tree
	self : Cursor

	sprite : Sprite
		parent = self
		sprite_play($, &res.ui.cursor_tex.loop);