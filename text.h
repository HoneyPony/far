#pragma once

#include "my.ponygame.h"

extern float color_white[4];
extern float color_black[4];
extern float color_red[4];

void draw_number(AnyNode *on, int number, float x, float y, float color[4]);

void draw_number_rjust(AnyNode *on, int number, float x, float y, float color[4]);