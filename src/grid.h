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