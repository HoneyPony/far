#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

// void construct_Cursor(Cursor *self) { }

// void destruct_Cursor(Cursor *self) { }

void tick_Cursor(Cursor *self, CursorTree *tree) {
	set_gpos(self, mouse_global());
}

