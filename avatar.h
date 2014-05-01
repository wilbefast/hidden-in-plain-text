#pragma once

#include <caca.h>

struct avatar_t
{
  float x, y, dx, dy;
};

void update_avatar();

void draw_avatar();
