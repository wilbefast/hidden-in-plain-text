#include "glitch.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <caca.h>

#include "useful.h"
#include "perlin.h"
#include "global.h"


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
  char string[17];
  uint16_t checker = 0b1000000000000000;
  for(int i = 0; i < 16; i++, checker = (checker >> 1))
    string[i] = (data & checker) ? '1' : '0';
  string[16] = '\0';
  printf("%s\n", string);
}

uint16_t caca_colour(double rgb[3])
{
  uint16_t a = 0b1111000000000000;
  uint16_t r = ((uint16_t)(15.0*rgb[0])) << 8;
  uint16_t g = ((uint16_t)(15.0*rgb[1])) << 4;
  uint16_t b = ((uint16_t)(15.0*rgb[0]));
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
  for(int i = 0; i < amount; i++)
  {
    int x = rand()%canvas_w, y = rand()%canvas_h;
    glitch_xy(c, x, y);
  }
}

void glitch_all(caca_canvas_t *c)
{
  for(int y = 0; y < canvas_h; y++)
  {
    int x = rand()%canvas_w;
    glitch_xy(c, x, y);
  }
}

void glitch_str(caca_canvas_t *c, char *str, int x, int y, int n_letters)
{
  int n = strlen(str);

  for(int i = 0; i < n_letters; i++)
  {
    int j = rand()%n;
    int cx = (int)lap(x - n/2 + j, 0.0, canvas_w);
    caca_put_char(c, cx, y, str[j]);
  }
}


// Erase text

void unglitch(caca_canvas_t *c, int amount)
{
  for(int i = 0; i < amount; i++)
    caca_put_char(c, rand()%canvas_w, rand()%canvas_h, ' ');
}
