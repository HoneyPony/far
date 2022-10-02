#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

// void construct_Intro(Intro *self) { }

// void destruct_Intro(Intro *self) { }

void tick_Intro(Intro *self, IntroTree *tree) {
	self->t += get_dt() * 0.6;

	#define OFF 0.2

	float t_1 = clamp(self->t - (0 + OFF), 0, 1);
	float t_2 = clamp(self->t - (2 + OFF), 0, 1);
	float t_3 = clamp(self->t - (4 + OFF), 0, 1);
	float t_4 = clamp(self->t - (6 + OFF), 0, 1);
	float t_5 = clamp((self->t - (9 + OFF)) * 5.0, 0, 1);

	tree->frame0->a = t_1;
	tree->frame1->a = t_2;
	tree->frame2->a = t_3;
	tree->frame3->a = t_4;
	tree->frame4->a = t_5;
}

