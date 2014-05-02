#include <stdlib.h>

#include "grid.h"

void create_grid(grid_t *g, int w, int h)
{
  /* Allocate memory */
  tile_t **tiles = calloc(w, sizeof(tile_t*));
  for(int x = 0; x < w; x++)
  	tiles[x] = calloc(h, sizeof(tile_t));

  /* Top and bottom walls */
  for(int x = 0; x < w; x++)
  {
	  tiles[x][0] = WALL;
	  tiles[x][h - 1] = WALL;
	}

  /* Left and right walls */
  for(int y = 0; y < h; y++)
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
  for(int x = 0; x < g->w; x++)
    free(g->tiles[x]);
  free(g->tiles);
}

void draw_grid(grid_t *g, caca_canvas_t *c)
{
  for(int x = 0; x < g->w; x++)
  {
    for(int y = 0; y < g->h; y++)
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