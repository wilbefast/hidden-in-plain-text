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

void update_avatar(avatar_t *a, int input_x, int input_y)
{
  /* Update speed from input */
  a->dx += 0.1f*input_x;
  a->dy += 0.1f*input_y;

  /* Cap speed to maximum */
  float speed2 = SQR(a->dx) + SQR(a->dy);
  if(speed2 > AVATAR_MAXSPEED2)
  {
    float speed = sqrt(speed2);
    a->dx *= AVATAR_MAXSPEED / speed;
    a->dy *= AVATAR_MAXSPEED / speed;
  }

  /* Apply friction to speed */

  /* Update position from speed */
  a->x += a->dx;
  a->y += a->dy;
}

void draw_avatar(avatar_t *a, caca_canvas_t *c)
{
  caca_put_char(c, floorf(a->x), floorf(a->y), '@');
}
