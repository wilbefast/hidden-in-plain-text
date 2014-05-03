#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include <caca.h>

#include "input.h"
#include "global.h"
#include "useful.h"

#include "gamestate/gamestate.h"
#include "gamestate/title.h"
#include "gamestate/hide.h"
#include "gamestate/seek.h"

int main()
{
  // Seed random number generator
  srand(time(0));

  // Start CACA, ASCII rendering library
  caca_display_t *d = caca_create_display(NULL);
  caca_canvas_t *c = caca_get_canvas(d);

  // Get canvas size, write to global variable
  canvas_w = caca_get_canvas_width(c);
  canvas_h = caca_get_canvas_height(c);
  world_to_canvas_x = canvas_w / WORLD_W;
  world_to_canvas_y = canvas_h / WORLD_H;

  // Start timer
  struct timeval last_tick;
  gettimeofday(&last_tick, NULL);  

  // Initialise gamestates
  title_init();
  hide_init();
  seek_init();

  // Enter starting gamestate
  gamestate_switch(&title);

  // Main loop
  bool stop = false;	
  while(!stop)
  {
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

    // Check for quit requests
    stop = input_quit();

    // Calculate delta time
    struct timeval this_tick;
    gettimeofday(&this_tick, NULL);    
    double dt = MAX(0.0, MICROSECONDS_TO_SECONDS(this_tick.tv_usec - last_tick.tv_usec));
    last_tick = this_tick;

    // Update the game world
    gamestate_update(dt);

    // Redraw the game world
    gamestate_draw(c);

    // Flush the rendered characters to the screen
    caca_refresh_display(d);
  }

  // Clean up
  caca_free_display(d);

  // All done
  return EXIT_SUCCESS;
}
