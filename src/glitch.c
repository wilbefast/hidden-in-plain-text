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

#include "glitch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <caca.h>

#include "useful.h"
#include "perlin.h"
#include "global.h"

#include "platform_specific.h"

// Palette ASCII colours

static int palette_size = -1;
static char *palette = " .'`^,:;Il!i<>~+_-?[]{}1()|/\\tfjrxnuvczXYUJCLQO0Zmwqpdbkhao*#MW&8%B@$";

char get_char(double darkness)
{
  if(palette_size < 0)
    palette_size = strlen(palette);
  return palette[(int)clamp(palette_size*darkness, 0.0, palette_size - 1)];
}


// Nibble RGB colours

void print_binary(uint16_t data)
{
	// local variables
  char string[17];
	int i;
  uint16_t checker;
	
	checker = 0x0001;
	checker = checker << 16;
  for(i = 0; i < 16; i++, checker = (checker >> 1))
    string[i] = (data & checker) ? '1' : '0';
  string[16] = '\0';
  printf("%s\n", string);
}

uint16_t caca_colour(double rgb[3])
{
	uint16_t a, r, g, b;
  a = 0xF000;
  r = ((uint16_t)(15.0*rgb[0])) << 8;
  g = ((uint16_t)(15.0*rgb[1])) << 4;
  b = ((uint16_t)(15.0*rgb[0]));
  return (a | r | g | b);
}

// Writing pseudo-random characters to the screen

char perlin_char(int x, int y)
{
  return get_char(0.5 + perlin_noise(x/(double)canvas_w, y/(double)canvas_h)); 
}

void glitch_xy(caca_canvas_t *c, int x, int y)
{
  caca_put_char(c, x, y, perlin_char(x, y));
}

void glitch(caca_canvas_t *c, int amount)
{
	int i, x, y;
  for(i = 0; i < amount; i++)
  {
    x = rand()%canvas_w;
		y = rand()%canvas_h;
    glitch_xy(c, x, y);
  }
}

void glitch_all(caca_canvas_t *c)
{
	int x, y;
  for(y = 0; y < canvas_h; y++)
  {
    x = rand()%canvas_w;
    glitch_xy(c, x, y);
  }
}

void glitch_str(caca_canvas_t *c, char *str, int x, int y, int n_letters)
{
	int n, i, j, cx;
  n = strlen(str);

  for(i = 0; i < n_letters; i++)
  {
    j = rand()%n;
    cx = (int)lap(x - n/2 + j, 0.0, canvas_w);
    caca_put_char(c, cx, y, str[j]);
  }
}

void glitch_str_flicker(caca_canvas_t *c, char *str, int x, int y, double flicker_amount)
{
  int n = strlen(str);

  int j = rand()%n;
  int cx = (int)lap(x - n/2 + j, 0.0, canvas_w);
  caca_put_char(c, cx, y, (rand_double() > flicker_amount) ? str[j] : ' ');
}


// Erase text

void unglitch(caca_canvas_t *c, int amount)
{
	int i;
  for(i = 0; i < amount; i++)
    caca_put_char(c, rand()%canvas_w, rand()%canvas_h, ' ');
}


// Localised glitch

/*
void glitch_swap_near(caca_canvas_t *c, int x, int y, double radius)
{ 
  double a_angle = rand_between(0.0, TWOPI);
  double b_angle = a_angle + PI;
  int a_x = lap(x + cos(a_angle)*radius*world_to_canvas_x, 0.0, canvas_w);
  int a_y = lap(y + sin(a_angle)*radius*world_to_canvas_y, 0.0, canvas_h);
  int b_x = lap(x + cos(b_angle)*radius*world_to_canvas_x, 0.0, canvas_w);
  int b_y = lap(y + sin(b_angle)*radius*world_to_canvas_y, 0.0, canvas_h);
   
  char a_char = caca_get_char(c, a_x, a_y);
  char b_char = caca_get_char(c, b_x, b_y);
  caca_put_char(c, a_x, a_y, b_char);
  caca_put_char(c, b_x, b_y, a_char);
}
*/

void glitch_near(caca_canvas_t *c, int x, int y, double max_radius)
{
  double nradius = rand_double();
  double angle = rand_between(0.0, TWOPI);
  x = (int)lap(x + cos(angle)*max_radius*(1 + nradius)*world_to_canvas_x, 0.0, canvas_w);
  y = (int)lap(y + sin(angle)*max_radius*(1 + nradius)*world_to_canvas_y, 0.0, canvas_h);
  caca_put_char(c, x, y, get_char(1 - nradius));  
}
