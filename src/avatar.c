#include "avatar.h"

#include <math.h>

#include "global.h"
#include "useful.h"

void create_avatar(avatar_t *a, float x, float y)
{
  a->x = x;
  a->y = y;
  a->dx = a->dy = a->speed = 0.0f;
}

void destroy_avatar(avatar_t *a)
{

}

void update_avatar(avatar_t *a, double dt, int input_x, int input_y)
{
  // Update speed from input
  a->dx += AVATAR_ACCELERATION*dt*input_x;
  a->dy += AVATAR_ACCELERATION*dt*input_y;

  // Apply friction per axis
  a->dx *= (input_x ? 1.0f : pow(1.0f - AVATAR_FRICTION_X, dt)); 
  a->dy *= (input_y ? 1.0f : pow(1.0f - AVATAR_FRICTION_Y, dt)); 

  // Calculate velocity magnitude
  a->speed = sqrt(SQR(a->dx) + SQR(a->dy));  

  // Cap speed to maximum
  if(a->speed > AVATAR_MAXSPEED)
  {
    a->dx = (a->dx / a->speed) * AVATAR_MAXSPEED;
    a->dy = (a->dy / a->speed) * AVATAR_MAXSPEED;
    a->speed = AVATAR_MAXSPEED;
  }

  // Update position from speed
  a->x += a->dx*dt;
  a->y += a->dy*dt;

  // Lap around
  a->x = lap(a->x, 0.0, WORLD_W);
  a->y = lap(a->y, 0.0, WORLD_H);
}

static float w = -1, h = -1;
static int cw = -1, ch = -1;

void draw_avatar(avatar_t *a, caca_canvas_t *c)
{
  // Save canvas size
  if(cw < 0) cw = caca_get_canvas_width(c);
  if(ch < 0) ch = caca_get_canvas_height(c);

  // Translate into screen space
  if(w < 0) w = cw / WORLD_W;
  if(h < 0) h = ch / WORLD_H;
  int x = a->x*w, y = a->y*h;

  // Swap characters
  double a_angle = rand_between(0.0, TWOPI);
  double b_angle = a_angle + PI;
  double distance = AVATAR_GLITCH_RADIUS
                    * (1 + AVATAR_GLITCH_RADIUS_MOVING - a->speed/AVATAR_MAXSPEED)
                    * (1 + rand_double());
  int a_x = lap(x + cos(a_angle)*distance*w, 0.0, cw);
  int a_y = lap(y + sin(a_angle)*distance*h, 0.0, ch);
  int b_x = lap(x + cos(b_angle)*distance*w, 0.0, cw);
  int b_y = lap(y + sin(b_angle)*distance*h, 0.0, ch);
   
  char a_char = caca_get_char(c, a_x, a_y);
  char b_char = caca_get_char(c, b_x, b_y);
  caca_put_char(c, a_x, a_y, b_char);
  caca_put_char(c, b_x, b_y, a_char);
}
