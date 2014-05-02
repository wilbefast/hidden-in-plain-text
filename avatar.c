#include "avatar.h"

#include <math.h>

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
  /* Update speed from input */
  a->dx += AVATAR_ACCELERATION*dt*input_x;
  a->dy += AVATAR_ACCELERATION*dt*input_y;

  /* Calculate velocity magnitude */
  float speed = sqrt(SQR(a->dx) + SQR(a->dy));  

  /* Apply friction to speed */
  /*float drag = pow(1.0f - AVATAR_FRICTION, dt);
  speed *= drag;
  a->dx *= drag;
  a->dy *= drag;*/

  /* Cap speed to maximum */
  if(speed > AVATAR_MAXSPEED)
  {
    a->dx = (a->dx / speed) * AVATAR_MAXSPEED;
    a->dy = (a->dy / speed) * AVATAR_MAXSPEED;
  }

  /* Apply friction per axis */
  a->dx *= (input_x ? 1.0f : pow(1.0f - AVATAR_FRICTION_X, dt)); 
  a->dy *= (input_y ? 1.0f : pow(1.0f - AVATAR_FRICTION_Y, dt)); 

  /* Update position from speed */
  a->x += a->dx*dt;
  a->y += a->dy*dt;
}

void draw_avatar(avatar_t *a, caca_canvas_t *c)
{
  int w = caca_get_canvas_width(c), h = caca_get_canvas_height(c);
  caca_put_char(c, floorf(w*0.5f + a->x), floorf(h*0.5f + (a->y)*0.4f), '@');
}
