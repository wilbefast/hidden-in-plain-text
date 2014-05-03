#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <caca.h>

#include "../avatar.h"
#include "../input.h"
#include "../perlin.h"
#include "../global.h"
#include "../useful.h"
#include "../colour.h"

#include "gamestate.h"


//
// Attributes
//

static char *name = "HIDDEN IN PLAIN TEXT";
static int name_length = 0;
static char *author = "@wilbefast";
static int author_length = 0;

// Methods

static void _enter(gamestate_t *this, gamestate_t *previous)
{
  
}

static void _leave(gamestate_t *this, gamestate_t *next)
{
  // nothing here so far ...
}

static void _draw(gamestate_t *this, caca_canvas_t *c)
{
  // Build/erase title
  int i = rand()%name_length, 
      x = (canvas_w - name_length)*0.5, 
      y = canvas_h*0.4;
  caca_put_char(c, x + i, y, rand()%6 ? name[i] : ' ');
  
  // Build/erase author 
  i = rand()%author_length;
  x = (canvas_w - author_length)*0.5;
  y = canvas_h*0.6;
  caca_put_char(c, x + i, y, rand()%6 ? author[i] : ' ');

  // Pick a character around the outside
  double angle = rand_between(0.0, TWOPI);
  double radius = rand_between(0.25, 1.0);
  
  // Choose a colour based on this position
  double hsl[3] = { angle / TWOPI, 0.5, 1.0 - radius }, rgb[3];
  hsl_to_rgb(hsl, rgb);
  caca_set_color_argb(c, caca_colour(rgb), 0b1111000000000000);
  
  // Place the character
  x = canvas_w*0.5 + canvas_w*radius*cos(angle);
  y = canvas_h*0.5 + canvas_h*radius*sin(angle);
  caca_put_char(c, x, y, get_char(0.5 + perlin_noise(x/(double)canvas_w, y/(double)canvas_h)));

  // Reset colour
  caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);
}

static void _update(gamestate_t *this, double dt)
{
  // Read input state
  int kx, ky; input_xy(&kx, &ky);
}

//
// Global variable
//

gamestate_t title;

void title_init()
{
  title.enter = _enter;
  title.leave = _leave;
  title.draw = _draw;
  title.update = _update;

  name_length = strlen(name);
  author_length = strlen(author);
}


