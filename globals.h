#pragma once

#include "my.ponygame.h"

#define ORE 0
#define PLANT 1
#define WOOD 2
#define NEBULA 3
#define METEOR 4
#define NEUTRON 5

extern bool on_planet;

extern int res_count(int kind);
extern void res_add(int kind, int amount);

#define TOOL_ANIM_BREAK_POINT 0.3

extern Player *player;
extern UpgradeMenu *upgrade_menu;

extern int engine_level;
extern int battery_level;
extern int solar_level;
extern int wrench_level;

extern int get_drop_count();

extern int ore_count;
extern int plant_count;
extern int wood_count;
extern int nebula_count;
extern int meteor_count;
extern int neutron_count;

extern AnimHandle* resource_icons[6];