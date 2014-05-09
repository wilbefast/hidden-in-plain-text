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

#include "score.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <caca.h>

#include "../input.h"
#include "../perlin.h"
#include "../global.h"
#include "../useful.h"
#include "../glitch.h"

#include "gamestate.h"
#include "title.h"

#include "../platform_specific.h"

//
// Nesting
//

typedef enum
{
  CLEAN, DEBRIEF
} _substate_t;


//
// Attributes
//

static double t;

static _substate_t state;

//
// Methods
//

static void enter(gamestate_t *this, gamestate_t *previous)
{
  // Reset timer
  t = 0.0;

  // Reset state
  state = CLEAN;
}

static void leave(gamestate_t *this, gamestate_t *next)
{
}

static void draw(gamestate_t *this, caca_canvas_t *c)
{
  if(state == CLEAN)
  {
     unglitch(c, SCORE_CLEANS_PER_FRAME);
  }
  else if(state == DEBRIEF)
  {
    int x, y;

    // Draw hiding player position
    caca_set_color_ansi(c, CACA_LIGHTCYAN, CACA_BLACK);
    x = (int)(world_to_canvas_x*hide_position[0]);
    y = (int)(world_to_canvas_y*hide_position[1]);
    glitch_near(c, x, y, 12.0);
    glitch_str_flicker(c, "Hide", x, (y > canvas_h - 8) ? y - 4 : y + 4, 0.1);

    // Draw seeking player position
    caca_set_color_ansi(c, CACA_YELLOW, CACA_BLACK);
    x = (int)(world_to_canvas_x*seek_position[0]);
    y = (int)(world_to_canvas_y*seek_position[1]);
    glitch_near(c, x, y, 12.0);
    glitch_str_flicker(c, "Seek", x, (y > canvas_h - 8) ? y - 4 : y + 4, 0.1);

  }
}

static void update(gamestate_t *this, double dt)
{
  // Increment timer
  t += dt;

  // Refresh state
  if(t < SCORE_CLEAN_TIME)
    state = CLEAN;
  else
    state = DEBRIEF;

  // Behave according to state
  if(state == DEBRIEF)
  {
    // Return to title on key-press
    if(input_action() || input_quit())
      gamestate_switch(&title);
  }
}


//
// Global variable
//

gamestate_t score;

void score_init()
{
  score.enter = enter;
  score.leave = leave;
  score.draw = draw;
  score.update = update;
}
