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

  // Lap around world
  a->x = lap(a->x, 0.0, WORLD_W);
  a->y = lap(a->y, 0.0, WORLD_H);

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
  (*x) = a->x*world_to_canvas_x;
  (*y) = a->y*world_to_canvas_y;
}

void draw_avatar_hide(avatar_t *a, caca_canvas_t *c)
{
  // Convert into canvas space
  int x, y; _canvas_xy(a, &x, &y);

  // Set palette
  //a->hsl[0] = 0.7;
  //hsl_to_rgb(a->hsl, a->rgb);
  //caca_set_color_argb(c, caca_colour(a->rgb), 0b1111000000000000);
  caca_set_color_ansi(c, CACA_LIGHTCYAN, CACA_BLACK);  

  // Swap characters
  double a_angle = rand_between(0.0, TWOPI);
  double b_angle = a_angle + PI;
  double distance = AVATAR_GLITCH_RADIUS
                    * (1 + AVATAR_GLITCH_RADIUS_MOVING - a->speed/AVATAR_MAXSPEED)
                    * (1 + rand_double());
  int a_x = lap(x + cos(a_angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  int a_y = lap(y + sin(a_angle)*distance*world_to_canvas_y, 0.0, canvas_h);
  int b_x = lap(x + cos(b_angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  int b_y = lap(y + sin(b_angle)*distance*world_to_canvas_y, 0.0, canvas_h);
   
  char a_char = caca_get_char(c, a_x, a_y);
  char b_char = caca_get_char(c, b_x, b_y);
  caca_put_char(c, a_x, a_y, b_char);
  caca_put_char(c, b_x, b_y, a_char);
}

void draw_avatar_seek(avatar_t *a, caca_canvas_t *c)
{
  // Convert into canvas space
  int x, y; _canvas_xy(a, &x, &y);

  // Set palette
  //a->hsl[0] = 0.6;
  //hsl_to_rgb(a->hsl, a->rgb);
  //caca_set_color_argb(c, caca_colour(a->rgb), 0b1111000000000000);
  caca_set_color_ansi(c, CACA_YELLOW, CACA_BLACK);  

  // Create characters
  double angle = rand_between(0.0, TWOPI);
  double ndistance = rand_double();
  double distance = 12.0 * (1 + ndistance);
  x = lap(x + cos(angle)*distance*world_to_canvas_x, 0.0, canvas_w);
  y = lap(y + sin(angle)*distance*world_to_canvas_y, 0.0, canvas_h);   
  caca_put_char(c, x, y, get_char(ndistance));  
}
