#include <stdio.h>
#include <stdlib.h>

#include <caca.h>

#define GRID_W 160
#define GRID_H 50


int main()
{
  /* Start CACA */
  caca_display_t *d = caca_create_display(NULL);
  caca_canvas_t *c = caca_get_canvas(d);

  /* Set palette */
  caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);

  /* Create the grid */
  int grid[GRID_W][GRID_H];
  for(int x = 0; x < GRID_W; x++)
  {
    /* Set all to 0 */
    for(int y = 0; y < GRID_H; y++)
      grid[x][y] = 0;

    /* Top and bottom walls */
    grid[x][0] = 1;
    grid[x][GRID_H - 1] = 1;
  }
  for(int y = 0; y < GRID_H; y++)
  {
   grid[0][y] = 1;
   grid[GRID_W - 1][y] = 1;
  }


  /* Main loop */
  int stop = 0;
  while(!stop)
  {
    /* Clear the canvas */
    caca_clear_canvas(c);

    /* Draw the grid */
    for(int x = 0; x < GRID_W; x++)
    {
      for(int y = 0; y < GRID_H; y++)
      {
        if(grid[x][y])
          caca_put_char(c, x, y, '@');
      }
    }  

    /* Catch events */
    if(caca_get_event(d, CACA_EVENT_KEY_PRESS, NULL, 1000*1000))
      stop = 1;

    /* Redraw the screen */
    caca_refresh_display(d);
  }

  /* Clean up */
  caca_free_display(d);
  return EXIT_SUCCESS;
}
