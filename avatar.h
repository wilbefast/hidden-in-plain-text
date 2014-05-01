#pragma once

#include <caca.h>

#include "useful.h"

#define AVATAR_MAXSPEED 1.0f
#define AVATAR_MAXSPEED2 SQR(AVATAR_MAXSPEED)

typedef struct
{
  float x, y, dx, dy;
} avatar_t;

void create_avatar(avatar_t*, float x, float y);
void destroy_avatar(avatar_t*);
void update_avatar(avatar_t*, int input_x, int input_y);
void draw_avatar(avatar_t*, caca_canvas_t*);
