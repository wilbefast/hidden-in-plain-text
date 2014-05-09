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

#include <stdlib.h>

#include "grid.h"

void create_grid(grid_t *g, int w, int h)
{
	// local variables
	int x, y;
	tile_t **tiles;

  /* Allocate memory */
  tiles = (tile_t**)calloc(w, sizeof(tile_t*));
  for(x = 0; x < w; x++)
  	tiles[x] = (tile_t*)calloc(h, sizeof(tile_t));

  /* Top and bottom walls */
  for(x = 0; x < w; x++)
  {
	  tiles[x][0] = WALL;
	  tiles[x][h - 1] = WALL;
	}

  /* Left and right walls */
  for(y = 0; y < h; y++)
  {
   tiles[0][y] = WALL;
   tiles[w - 1][y] = WALL;
  }

  /* Save allocated memory in the structure */
  g->w = w;
  g->h = h;
  g->tiles = tiles;
}

void destroy_grid(grid_t *g)
{
  /* Free memory */
	int x;
  for(x = 0; x < g->w; x++)
    free(g->tiles[x]);
  free(g->tiles);
}

void draw_grid(grid_t *g, caca_canvas_t *c)
{
	int x, y;
  for(x = 0; x < g->w; x++)
  {
    for(y = 0; y < g->h; y++)
    {
      switch(g->tiles[x][y])
      {
        case WALL: 
        	caca_put_char(c, x, y, '#');
        	break;

      	default:
      		break;
      }
    }
  }
}