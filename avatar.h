#pragma once

#include <caca.h>

#include "useful.h"

#define AVATAR_MAXSPEED 20.0f
#define AVATAR_MAXSPEED2 SQR(AVATAR_MAXSPEED)
#define AVATAR_ACCELERATION 50.0f
#define AVATAR_FRICTION 0.9f
#define AVATAR_FRICTION_X 0.9f
#define AVATAR_FRICTION_Y 0.9f

typedef struct
{
  float x, y, dx, dy;
} avatar_t;

void create_avatar(avatar_t*, float x, float y);
void destroy_avatar(avatar_t*);
void update_avatar(avatar_t*, double dt, int input_x, int input_y);
void draw_avatar(avatar_t*, caca_canvas_t*);
