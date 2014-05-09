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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <caca.h>

#include "../avatar.h"
#include "../input.h"
#include "../perlin.h"
#include "../global.h"
#include "../useful.h"
#include "../glitch.h"

#include "gamestate.h"
#include "hide.h"

#include "../platform_specific.h"

//
// Attributes
//

static char *name = "HIDDEN IN PLAIN TEXT";
static int name_length = 0;
static char *author = "@wilbefast";
static int author_length = 0;

static double t = 0.0;

// Methods

static void enter(gamestate_t *this, gamestate_t *previous)
{
  // Reset timer
  t = 0.0;
}

static void leave(gamestate_t *this, gamestate_t *next)
{
  // nothing here so far ...
}

static void draw(gamestate_t *this, caca_canvas_t *c)
{
	// local variables
	double angle, radius, hsl[3], rgb[3];
	int x, y, i;

  // Clean up
  if(t < 1.0)
    unglitch(c, 700);

  // Erase central area
  angle = rand_between(0.0, TWOPI);
  radius = rand_between(0.0, 0.5);
  x = (int)(canvas_w*0.5 + canvas_w*radius*cos(angle));
  y = (int)(canvas_h*0.5 + canvas_h*radius*cos(angle));
  caca_put_char(c, x, y, ' ');

  // Build title
  i = rand()%name_length;
  x = (int)((canvas_w - name_length)*0.5);
  y = (int)(canvas_h*0.5);  
  caca_put_char(c, x + i, y, name[i]);
  
  // Build author 
  i = rand()%author_length;
  x = (int)((canvas_w - author_length)*0.5);
  y = (int)(canvas_h*0.6);
  caca_put_char(c, x + i, y, author[i]);

  // Pick a character around the outside
  radius = rand_between(0.25, 1.0);
  
  // Choose a colour based on this position
  hsl[0] = angle / TWOPI;
	hsl[1] = 0.5;
	hsl[2] = 1.0 - radius;
  hsl_to_rgb(hsl, rgb);
  caca_set_color_argb(c, caca_colour(rgb), 0xF000);
  
  // Place the character
  x = (int)(canvas_w*0.5 + canvas_w*radius*cos(angle));
  y = (int)(canvas_h*0.5 + canvas_h*radius*sin(angle));
  caca_put_char(c, x, y, get_char(radius));

  // Reset colour
  caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);
}

static void update(gamestate_t *this, double dt)
{
  // Read input state
  if(input_action())
    gamestate_switch(&hide);

  // Update counter
  t += dt;
}

//
// Global variable
//

gamestate_t title;

void title_init()
{
  title.enter = enter;
  title.leave = leave;
  title.draw = draw;
  title.update = update;

  name_length = strlen(name);
  author_length = strlen(author);
}


