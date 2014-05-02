#include "avatar.h"

#include <math.h>

#include "global.h"
#include "useful.h"

void create_avatar(avatar_t *a, float x, float y)
{
  a->x = x;
  a->y = y;
  a->dx = a->dy = 0.0f;
}

void destroy_avatar(avatar_t *a)
{

}

void update_avatar(avatar_t *a, double dt, int input_x, int input_y)
{
  // Update speed from input
  a->dx += AVATAR_ACCELERATION*dt*input_x;
  a->dy += AVATAR_ACCELERATION*dt*input_y;

  // Calculate velocity magnitude
  float speed = sqrt(SQR(a->dx) + SQR(a->dy));  

  // Cap speed to maximum
  if(speed > AVATAR_MAXSPEED)
  {
    a->dx = (a->dx / speed) * AVATAR_MAXSPEED;
    a->dy = (a->dy / speed) * AVATAR_MAXSPEED;
  }

  // Apply friction per axis
  a->dx *= (input_x ? 1.0f : pow(1.0f - AVATAR_FRICTION_X, dt)); 
  a->dy *= (input_y ? 1.0f : pow(1.0f - AVATAR_FRICTION_Y, dt)); 

  // Update position from speed
  a->x += a->dx*dt;
  a->y += a->dy*dt;

  // Lap around
  a->x = lap(a->x, 0.0, WORLD_W);
  a->y = lap(a->y, 0.0, WORLD_H);
}

static float w = -1, h = -1;

void draw_avatar(avatar_t *a, caca_canvas_t *c)
{
  // Translate into screen space
  if(w < 0) w = caca_get_canvas_width(c) / WORLD_W;
  if(h < 0) h = caca_get_canvas_height(c) / WORLD_H;
  int x = a->x*w, y = a->y*h;

  // Swap characters
  double angle = rand_between(0.0, TWOPI);
  double distance = 16*(1 + rand_double());
  int swap_x = lap(x + cos(angle)*distance*w, 0.0, WORLD_W);
  int swap_y = lap(y + sin(angle)*distance*h, 0.0, WORLD_H);
  
  caca_put_char(c, swap_x, swap_y, '@');
}
