#pragma once

#include <caca.h>

#include "useful.h"

#define AVATAR_MAXSPEED 200.0f
#define AVATAR_MAXSPEED2 SQR(AVATAR_MAXSPEED)
#define AVATAR_ACCELERATION 1000.0f
#define AVATAR_FRICTION 0.9f
#define AVATAR_FRICTION_X 0.99f
#define AVATAR_FRICTION_Y 0.99f
#define AVATAR_GLITCH_RADIUS 196.0
#define AVATAR_GLITCH_RADIUS_MOVING 0.1

typedef struct
{
  float x, y, dx, dy, speed;
  double hsl[3], rgb[3];
} avatar_t;

void create_avatar(avatar_t*, float x, float y);
void destroy_avatar(avatar_t*);
void update_avatar(avatar_t*, double dt, int input_x, int input_y);
void draw_avatar_hide(avatar_t*, caca_canvas_t*);
void draw_avatar_seek(avatar_t*, caca_canvas_t*);
