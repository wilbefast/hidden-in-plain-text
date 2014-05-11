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

static double t, distance;

static _substate_t state;

static char message[32];

static float hx, hy, sx, sy;

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
    // Local variables
    int ihx, ihy, isx, isy, dx, dy, mx, my;
    double offset;

    // Convert player position to canvas space
    ihx = (int)(world_to_canvas_x*lap(hx, 0, WORLD_W));
    ihy = (int)(world_to_canvas_y*lap(hy, 0, WORLD_H));
    isx = (int)(world_to_canvas_x*lap(sx, 0, WORLD_W));
    isy = (int)(world_to_canvas_y*lap(sy, 0, WORLD_H));
    dx = ihx - isx;
    dy = ihy - isy;

    // Draw line between players
    caca_set_color_ansi(c, CACA_WHITE, CACA_BLACK);
    //caca_draw_thin_line(c, hx, hy, sx, sy); 

    // Draw the score
    offset = 0.5 + 0.5*canvas_w/((distance < 1) ? 1 : distance);
    mx = lap((ihx + isx)/2 - dy*offset, 0, canvas_w);
    my = lap((ihy + isy)/2 + dx*offset, 0, canvas_h);
    glitch_str_flicker(c, message, mx, my, 0.1);

    // Draw hiding player position
    caca_set_color_ansi(c, CACA_LIGHTCYAN, CACA_BLACK);
    glitch_near(c, ihx, ihy, 12.0);
    glitch_str_flicker(c, "Hide", ihx, (ihy > canvas_h - 4) ? ihy - 2 : ihy + 2, 0.1);

    // Draw seeking player position
    caca_set_color_ansi(c, CACA_YELLOW, CACA_BLACK);
    glitch_near(c, isx, isy, 12.0);
    glitch_str_flicker(c, "Seek", isx, (isy > canvas_h - 4) ? isy - 2 : isy + 2, 0.1);
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
  {
    // Local variables
    int accuracy;

    // Alias coordinates
    float dx, dy;
    hx = hide_position[0];
    hy = hide_position[1];
    sx = seek_position[0];
    sy = seek_position[1];
    dx = hx - sx;
    dy = hy - sy;

    // Lap around
    if(abs(dx) > WORLD_W/2)
    {
      if(sx > hx) hx += WORLD_W;
      else sx += WORLD_W;
    }
    if(abs(dy) > WORLD_H/2)
    {
      if(sy > hy) hy += WORLD_H;
      else sy += WORLD_H;
    }

    // We need to print distance as score
    distance = dist(hx, hy, sx, sy);
    accuracy = (int)((1 - distance/(WORLD_W/2))*100);
    if(accuracy < 0) accuracy = 0;
    sprintf(message, "accuracy: %d%%", accuracy); 

    // Finally, change state
    state = DEBRIEF;
  }

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
