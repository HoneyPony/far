@type BookMenu : Node
	int current_page;
	bool was_open;

@construct
@tick

@tree
	self : BookMenu
		$->z_index = 2005;

	sprite : Sprite
		parent = self
		sprite_play($, &res.ui.book_menu_tex.loop);
		$->z_index = 2000;
		$->on_camera = true;

	book : StaticSprite
		parent = self
		set_lpos($, vxy(0, 4));
		$->z_index = 2010;
		$->on_camera = true;
		$->texture = &res.ui.manual_tex.loop.frames[0].texture;