#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <caca.h>

char get_char(double darkness);

void print_binary(uint16_t data);
uint16_t caca_colour(double rgb[3]);

char perlin_char(int x, int y);

void glitch_xy(caca_canvas_t *c, int x, int y);
void glitch(caca_canvas_t *c, int amount);
void glitch_all(caca_canvas_t *c);
