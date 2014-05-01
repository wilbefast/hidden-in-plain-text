#pragma once

#include <caca.h>

typedef struct
{
  float x, y, dx, dy;
} avatar_t;

void create_avatar(avatar_t*, float x, float y);
void destroy_avatar(avatar_t*);
void update_avatar(avatar_t*);
void draw_avatar(avatar_t*, caca_canvas_t*);
