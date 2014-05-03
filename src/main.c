#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include <caca.h>

#include "avatar.h"
#include "grid.h"
#include "input.h"
#include "perlin.h"
#include "global.h"
#include "useful.h"
#include "gamestate.h"
#include "colour.h"

int main()
{
  // Seed random
  srand(time(0));

  // Start CACA
  caca_display_t *d = caca_create_display(NULL);
  caca_canvas_t *c = caca_get_canvas(d);

  // Get size
  int w = caca_get_canvas_width(c), h = caca_get_canvas_height(c);

  // Set palette
  double fg_rgb[3], bg_rgb[3], fg_hsl[3] = { 0.0, 1.0, 0.65 }, bg_hsl[3] = { 0.5, 1.0, 0.0 };

  // Create grid
  grid_t grid;
  create_grid(&grid, w, h);

  // Create avatar
  avatar_t avatar;
  create_avatar(&avatar, 0.5*WORLD_W, 0.5*WORLD_H);

  // Start timer
  struct timeval last_tick;
  gettimeofday(&last_tick, NULL);  

  // Generate background
  for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
      caca_put_char(c, x, y, get_char(0.5 + perlin_noise(x/(double)w, y/(double)h))); 

  // Main loop
  bool stop = false;	
  while(!stop)
  {
    // Draw the avatar
    draw_avatar(&avatar, c);

    // Wait for events
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

    // React based on input state
    int kx, ky;
    bool action;
    input_get(&kx, &ky, &action, &stop);

    // Calculate delta time
    struct timeval this_tick;
    gettimeofday(&this_tick, NULL);    
    double dt = MAX(0.0, MICROSECONDS_TO_SECONDS(this_tick.tv_usec - last_tick.tv_usec));
    last_tick = this_tick;

    // Update the game world
    update_avatar(&avatar, dt, kx, ky);

    // Flush the rendered characters to the screen
    caca_refresh_display(d);

    // Lap hue around   
    fg_hsl[0] = lap(fg_hsl[0] + 0.1*dt, 0.0, 1.0);
    hsl_to_rgb(fg_hsl, fg_rgb);
    bg_hsl[0] = lap(fg_hsl[0] + 0.5, 0.0, 1.0);
    hsl_to_rgb(bg_hsl, bg_rgb);
    caca_set_color_argb(c, caca_colour(fg_rgb), caca_colour(bg_rgb));
  }

  // Clean up
  destroy_grid(&grid);
  destroy_avatar(&avatar);
  caca_free_display(d);

  // All done
  return EXIT_SUCCESS;
}
