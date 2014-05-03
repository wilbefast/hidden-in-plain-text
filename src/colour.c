#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "global.h"
#include "useful.h"
#include "colour.h"


// Palette ASCII colours

static int palette_size = -1;
static char *palette = " .'`^,:;Il!i<>~+_-?[]{}1()|/\tfjrxnuvczXYUJCLQO0Zmwqpdbkhao*#MW&8%B@$";

char get_char(double darkness)
{
  if(palette_size < 0)
    palette_size = strlen(palette);
  return palette[(int)(palette_size*darkness)];
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
