#include <stdio.h>
#include <stdlib.h>

#include <caca.h>

#include "avatar.h"
#include "grid.h"

int main()
{
  /* Start CACA */
  caca_display_t *d = caca_create_display(NULL);
  caca_canvas_t *c = caca_get_canvas(d);

  /* Get size */
  int w = caca_get_canvas_width(c), h = caca_get_canvas_height(c);

  /* Set palette */
  caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);

  /* Create grid */
  grid_t grid;
  create_grid(&grid, w, h);

  /* Main loop */
  int stop = 0;
  while(!stop)
  {
    /* Clear the canvas */
    caca_clear_canvas(c);

    /* Draw the grid */
    draw_grid(&grid, c);

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
