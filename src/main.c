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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <caca.h>

#include "input.h"
#include "global.h"
#include "useful.h"

#include "gamestate/gamestate.h"
#include "gamestate/title.h"
#include "gamestate/hide.h"
#include "gamestate/seek.h"
#include "gamestate/score.h"

#include "platform_specific.h"
#include "delta_time.h"

static void reset_display_size(int new_w, int new_h)
{
  canvas_w = new_w;
  canvas_h = new_h;
  world_to_canvas_x = canvas_w / WORLD_W;
  world_to_canvas_y = canvas_h / WORLD_H;
}

int main()
{
	// Local variables
	caca_display_t *d;
	caca_canvas_t *c;
	bool stop;
	double dt;

  // Seed random number generator
  srand((unsigned int)time(0));

  // Start CACA, ASCII rendering library
  d = caca_create_display(NULL);
  c = caca_get_canvas(d);

  // Get canvas size, write to global variable
  reset_display_size(caca_get_canvas_width(c), caca_get_canvas_height(c));
 
  // Start timer
  dt_start();

  // Initialise gamestates
  title_init();
  hide_init();
  seek_init();
  score_init();

  // Enter starting gamestate
  gamestate_switch(&title);

  // Main loop
  stop = false;	
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
		    case CACA_EVENT_RESIZE: reset_display_size(event.data.resize.w, event.data.resize.h); break;
		    case CACA_EVENT_QUIT: stop = true; break;
        default: break;
      }
    }

    // Check for quit requests
    if(gamestate_is(&title) && input_quit())
      stop = true;

    // Calculate delta time
    dt = dt_get();

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
