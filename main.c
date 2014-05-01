#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <caca.h>

#include "avatar.h"
#include "grid.h"
#include "input.h"

#define FRAMES_PER_SECOND 60
#define MICROSECONDS_PER_FRAME 1000000/60

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

  /* Create avatar */
  avatar_t avatar;
  create_avatar(&avatar, w*0.5f, h*0.5f);

  /* Main loop */
  bool stop = false;
  while(!stop)
  {
    /* Clear the canvas */
    caca_clear_canvas(c);

    /* Draw the grid */
    draw_grid(&grid, c);

    /* Draw the avatar */
    draw_avatar(&avatar, c);

    /* Catch events */
    caca_event_t event;
    if(caca_get_event(d, CACA_EVENT_ANY, &event, MICROSECONDS_PER_FRAME))
    {
      switch(event.type)
      {
        case CACA_EVENT_KEY_PRESS: input_set(event.data.key.ch, true); break;
        case CACA_EVENT_KEY_RELEASE: input_set(event.data.key.ch, false); break;          
        default: break;
      }
    }

    /* React based on input state */
    int kx, ky;
    input_get(&kx, &ky, &stop);

    /* Update the game world */
    update_avatar(&avatar, kx, ky);

    /* Redraw the screen */
    caca_refresh_display(d);
  }

  /* Clean up */
  caca_free_display(d);
  return EXIT_SUCCESS;
}
