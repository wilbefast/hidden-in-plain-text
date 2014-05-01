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

void update_avatar(avatar_t *a)
{
  a->x += a->dx;
  a->y += a->dy;
}

void draw_avatar(avatar_t *a, caca_canvas_t *c)
{
  caca_put_char(c, floorf(a->x), floorf(a->y), '@');
}
