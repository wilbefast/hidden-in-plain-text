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

#include "seek.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include <caca.h>

#include "../avatar.h"
#include "../input.h"
#include "../perlin.h"
#include "../global.h"
#include "../useful.h"
#include "../glitch.h"

#include "gamestate.h"
#include "score.h"
#include "title.h" 

//
// Constants
// 

static char *tutorial = "Seek!";

//
// Nesting
//

typedef enum
{
  CLEAN, TUTORIAL, GAMEPLAY
} _substate_t;


//
// Attributes
//

static double t;

static avatar_t avatar;

static _substate_t state;

//
// Methods
//

static void _enter(gamestate_t *this, gamestate_t *previous)
{
  // Reset timer
  t = 0.0;

  // Initialise avatar attributes
  create_avatar(&avatar, WORLD_W*0.5, WORLD_H*0.5);

  // Reset state
  state = CLEAN;
}

static void _leave(gamestate_t *this, gamestate_t *next)
{
  // Save seek position
  seek_position[0] = avatar.x;
  seek_position[1] = avatar.y;

  // Free memory allocated by avatar
  destroy_avatar(&avatar);
}

static void _draw(gamestate_t *this, caca_canvas_t *c)
{
  if(state == CLEAN)
  {
     unglitch(c, SEEK_CLEANS_PER_FRAME);
  }
  if(state == TUTORIAL)
  {
    caca_set_color_ansi(c, CACA_YELLOW, CACA_BLACK);
    glitch_str(c, tutorial, rand()%canvas_w, rand()%canvas_h, 10);
  }
  else if(state == GAMEPLAY)
  {
    draw_avatar_seek(&avatar, c);
  }
}

static void _update(gamestate_t *this, double dt)
{
  // Increment timer
  t += dt;

  // Refresh state
  if(t < SEEK_CLEAN_TIME)
    state = CLEAN;
  else if(t < SEEK_CLEAN_TIME + SEEK_TUTORIAL_TIME)
    state = TUTORIAL;
  else
   state = GAMEPLAY;

  // Behave according to state
  if(state == GAMEPLAY)
  {
    // Read input state
    int kx, ky; input_xy(&kx, &ky);

    // Update the avatar
    update_avatar(&avatar, dt, kx, ky);

    // Has the seeker bet on a position ?
    if(input_action())
      gamestate_switch(&score);
  }

  // Return to title
  if(input_quit())
    gamestate_switch(&title);
}


//
// Global variable
//

gamestate_t seek;

void seek_init()
{
  seek.enter = _enter;
  seek.leave = _leave;
  seek.draw = _draw;
  seek.update = _update;
}
