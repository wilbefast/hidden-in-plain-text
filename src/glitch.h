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
void glitch_str(caca_canvas_t *c, char* str, int x, int y, int n_letters);
void glitch_str_flicker(caca_canvas_t *c, char* str, int x, int y, double flicker_amount);
void unglitch(caca_canvas_t *c, int amount);

void glitch_near(caca_canvas_t *c, int x, int y, double max_radius);
