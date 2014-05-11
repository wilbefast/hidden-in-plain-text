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

#include "avatar.h"

#include <math.h>

#include "global.h"
#include "useful.h"
#include "glitch.h"

void create_avatar(avatar_t *a, float x, float y)
{
  // Position
  a->x = x;
  a->y = y;
 
  // Speed
  a->dx = a->dy = a->speed = 0.0f;
 
  // Colour 
  a->hsl[0] = rand_double();
  a->hsl[1] = 0.5;
  a->hsl[2] = 0.5;
}

void destroy_avatar(avatar_t *a)
{
  // nothing here so far ...
}

void update_avatar(avatar_t *a, double dt, int input_x, int input_y, bool seek)
{
  // Local variables
  float acceleration;
  acceleration = seek ? AVATAR_ACCELERATION_SEEK : AVATAR_ACCELERATION_HIDE;

  // Update speed from input
  a->dx = (float)(a->dx + acceleration*dt*input_x);
  a->dy = (float)(a->dy + acceleration*dt*input_y);

  // Apply friction per axis
  a->dx = (float)(a->dx * (input_x ? 1.0f : pow(1.0f - AVATAR_FRICTION_X, dt))); 
  a->dy = (float)(a->dy * (input_y ? 1.0f : pow(1.0f - AVATAR_FRICTION_Y, dt))); 

  // Calculate velocity magnitude
  a->speed = (float)sqrt(SQR(a->dx) + SQR(a->dy));  

  // Cap speed to maximum
  if(a->speed > AVATAR_MAXSPEED)
  {
    a->dx = (a->dx / a->speed) * AVATAR_MAXSPEED;
    a->dy = (a->dy / a->speed) * AVATAR_MAXSPEED;
    a->speed = AVATAR_MAXSPEED;
  }

  // Update position from speed
  a->x = (float)(a->x + a->dx*dt);
  a->y = (float)(a->y + a->dy*dt);

  // Lap around world
  a->x = (float)lap(a->x, 0.0, WORLD_W);
  a->y = (float)lap(a->y, 0.0, WORLD_H);

  // Cycle hue
  a->hsl[0] = lap(a->hsl[0] + 0.1*dt, 0.0, 1.0);

  // Brightness and saturation reflect speed
  a->hsl[1] = 0.5*(2.0 - a->speed/AVATAR_MAXSPEED);
  a->hsl[2] = 0.5*(2.0 - a->speed/AVATAR_MAXSPEED);

  // Recalculate RGB
  //hsl_to_rgb(a->hsl, a->rgb);

}

static void _canvas_xy(avatar_t *a, int *x, int *y)
{
  (*x) = (int)(a->x*world_to_canvas_x);
  (*y) = (int)(a->y*world_to_canvas_y);
}

void draw_avatar_hide(avatar_t *a, caca_canvas_t *c)
{
	// local variables
	double a_angle, b_angle, distance, nspeed;
	int a_x, a_y, b_x, b_y;
	char a_char, b_char;

  // Convert into canvas space
  int x, y; _canvas_xy(a, &x, &y);

  // normalised speed of avatar
  nspeed = (a->speed/AVATAR_MAXSPEED);

  // Set palette
  //a->hsl[0] = 0.7;
  //hsl_to_rgb(a->hsl, a->rgb);
  //caca_set_color_argb(c, caca_colour(a->rgb), 0b1111000000000000);
  caca_set_color_ansi(c, (nspeed > 0.5) ? CACA_LIGHTCYAN : CACA_WHITE, CACA_BLACK);  

  // Swap characters
  a_angle = rand_between(0.0, TWOPI);
  b_angle = a_angle + PI;
  distance = canvas_w/world_to_canvas_x //AVATAR_GLITCH_RADIUS*canvas_w
                    * (AVATAR_GLITCH_RADIUS_MOVING + 1 - nspeed)
                    * rand_double();
  a_x = (int)lap(x + cos(a_angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  a_y = (int)lap(y + sin(a_angle)*distance*world_to_canvas_y, 0.0, canvas_h);
  b_x = (int)lap(x + cos(b_angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  b_y = (int)lap(y + sin(b_angle)*distance*world_to_canvas_y, 0.0, canvas_h);
   
  a_char = caca_get_char(c, a_x, a_y);
  b_char = caca_get_char(c, b_x, b_y);
  caca_put_char(c, a_x, a_y, b_char);
  caca_put_char(c, b_x, b_y, a_char);
}

void draw_avatar_seek(avatar_t *a, caca_canvas_t *c)
{
	// local variables
	double angle, ndistance, distance;

  // Convert into canvas space
  int x, y; _canvas_xy(a, &x, &y);

  // Set palette
  //a->hsl[0] = 0.6;
  //hsl_to_rgb(a->hsl, a->rgb);
  //caca_set_color_argb(c, caca_colour(a->rgb), 0b1111000000000000);
  caca_set_color_ansi(c, CACA_YELLOW, CACA_BLACK);  

  // Create characters
	angle = rand_between(0.0, TWOPI);
  ndistance = rand_double();
  distance = 12.0 * (1 + ndistance);
  x = (int)lap(x + cos(angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  y = (int)lap(y + sin(angle)*distance*world_to_canvas_y, 0.0, canvas_h);   
  caca_put_char(c, x, y, get_char(1 - ndistance));  
}
