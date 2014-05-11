/*
(C) Copyright 2014 William Dyce

All rights reserved. This program and the accompanying materials
are made available under the terms of the GNU Lesser General Public License
(LGPL) version 2.1 which accompanies this distribution, and is available at
http://www.gnu.org/licenses/lgpl-2.1.html

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
*/

#pragma once

#include <caca.h>

#include "useful.h"

#include "platform_specific.h"

#define AVATAR_MAXSPEED 200.0f
#define AVATAR_MAXSPEED2 SQR(AVATAR_MAXSPEED)
#define AVATAR_ACCELERATION_HIDE 300.0f
#define AVATAR_ACCELERATION_SEEK 1000.0f
#define AVATAR_FRICTION 0.9f
#define AVATAR_FRICTION_X 0.99f
#define AVATAR_FRICTION_Y 0.99f
#define AVATAR_GLITCH_RADIUS 0.5          // fraction of canvas width
#define AVATAR_GLITCH_RADIUS_MOVING 0.05   // fraction of base glitch radius

typedef struct
{
  float x, y, dx, dy, speed;
  double hsl[3], rgb[3];
} avatar_t;

void create_avatar(avatar_t*, float x, float y);
void destroy_avatar(avatar_t*);
void update_avatar(avatar_t*, double dt, int input_x, int input_y, bool seek);
void draw_avatar_hide(avatar_t*, caca_canvas_t*);
void draw_avatar_seek(avatar_t*, caca_canvas_t*);
