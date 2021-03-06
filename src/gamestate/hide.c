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

#include "hide.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <caca.h>

#include "../avatar.h"
#include "../input.h"
#include "../perlin.h"
#include "../global.h"
#include "../useful.h"
#include "../glitch.h"

#include "gamestate.h"
#include "seek.h"

#include "../platform_specific.h"

// can't include "title.h" as this would create a loop
extern gamestate_t title; 

//
// Constants
// 

static char *tutorial = "Hide!";

//
// Nesting
//

typedef enum
{
  TUTORIAL, GLITCH, GAMEPLAY
} _substate_t;


//
// Attributes
//

static avatar_t avatar;

static double t;

static _substate_t state;

//
// Methods
//

static void enter(gamestate_t *this, gamestate_t *previous)
{
  // Create avatar
  create_avatar(&avatar, 0.5*WORLD_W, 0.5*WORLD_H);

  // Reset timer
  t = 0.0;

  // Reset state
  state = TUTORIAL;
}

static void leave(gamestate_t *this, gamestate_t *next)
{
  // Save hide position
  hide_position[0] = avatar.x;
  hide_position[1] = avatar.y;

  // Destroy avatar
  destroy_avatar(&avatar);
}

static void draw(gamestate_t *this, caca_canvas_t *c)
{
  if(state == TUTORIAL)
  {
    caca_set_color_ansi(c, CACA_LIGHTCYAN, CACA_BLACK);
    glitch_str(c, tutorial, rand()%canvas_w, rand()%canvas_h, 10);
  }
  else if(state == GLITCH)
  {
    glitch(c, HIDE_GLITCHES_PER_FRAME);
  }
  else if(state == GAMEPLAY)
  {
    // Draw the avatar
    draw_avatar_hide(&avatar, c);
  }

  // Reset colour
  caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);

}

static void update(gamestate_t *this, double dt)
{
  // Increment timer
  t += dt;

  // Refresh state
  if(t < HIDE_TUTORIAL_TIME)
    state = TUTORIAL;
  else if(t < HIDE_TUTORIAL_TIME + HIDE_GLITCH_TIME)
    state = GLITCH;
  else
   state = GAMEPLAY;

  // Behave according to state
  if(state == GAMEPLAY)
  {
    // Read input state
    int kx, ky; input_xy(&kx, &ky);

    // Update the avatar
    update_avatar(&avatar, dt, kx, ky, false); // hide

    // Switch to seek's turn ?
    if(input_action())
      gamestate_switch(&seek);
  }

  // Return to menu ?
  if(input_quit())
    gamestate_switch(&title);
}


//
// Global variable
//

gamestate_t hide;

void hide_init()
{
  hide.enter = enter;
  hide.leave = leave;
  hide.draw = draw;
  hide.update = update;
}
