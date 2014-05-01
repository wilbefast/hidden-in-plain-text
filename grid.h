#pragma once

#include <caca.h>

typedef enum
{
	FLOOR, WALL
} tile_t;

typedef struct
{
	int w, h;
	tile_t **tiles;
} grid_t;

void create_grid(grid_t*, int w, int h);
void destroy_grid(grid_t*);
void draw_grid(grid_t*, caca_canvas_t*);