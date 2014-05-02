#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#include <caca.h>

#include "avatar.h"
#include "grid.h"
#include "input.h"
#include "perlin.h"

#define FRAMES_PER_SECOND 60
#define MICROSECONDS_TO_SECONDS(us) ((us)*0.000001)
#define MICROSECONDS_PER_FRAME 1000000/60

static int palette_size = -1;
static char *palette = " .'`^,:;Il!i<>~+_-?[]{}1()|/\tfjrxnuvczXYUJCLQO0Zmwqpdbkhao*#MW&8%B@$";

char get_char(double darkness)
{
  if(palette_size < 0)
    palette_size = strlen(palette);
  return palette[(int)(palette_size*darkness)];
}

int main()
{
  /* Seed random */
  srand(time(0));

  /* Start CACA */
  caca_display_t *d = caca_create_display(NULL);
  caca_canvas_t *c = caca_get_canvas(d);

  /* Get size */
  int w = caca_get_canvas_width(c), h = caca_get_canvas_height(c);

  /* Set palette */
  caca_set_color_ansi(c, CACA_GREEN, CACA_BLACK);

  /* Create grid */
  grid_t grid;
  create_grid(&grid, w, h);

  /* Create avatar */
  avatar_t avatar;
  create_avatar(&avatar, 0.0f, 0.0f);

  /* Start timer */
  struct timeval last_tick;
  gettimeofday(&last_tick, NULL);  

  /* Generate background */
  for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
      caca_put_char(c, x, y, get_char(0.5 + perlin_noise(x/(double)w, y/(double)h))); 

  /* Main loop */
  bool stop = false;	
  while(!stop)
  {
    /* Clear the canvas */
    //caca_clear_canvas(c);

    /* Draw the grid */
    //draw_grid(&grid, c);

    /* Draw the avatar */
    draw_avatar(&avatar, c);

    /* Wait for events */
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

    /* Calculate delta time */
    struct timeval this_tick;
    gettimeofday(&this_tick, NULL);    
    double dt = MAX(0.0, MICROSECONDS_TO_SECONDS(this_tick.tv_usec - last_tick.tv_usec));
    last_tick = this_tick;

    /* Update the game world */
    update_avatar(&avatar, dt, kx, ky);

    /* Redraw the screen */
    caca_refresh_display(d);
  }

  /* Clean up */
  destroy_grid(&grid);
  destroy_avatar(&avatar);
  caca_free_display(d);
  
  /* All done */
  return EXIT_SUCCESS;
}
