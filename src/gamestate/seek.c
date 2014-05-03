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

static _substate_t state;

//
// Methods
//

static void _enter(gamestate_t *this, gamestate_t *previous)
{
  // Reset timer
  t = 0.0;

  // Reset state
  state = CLEAN;
}

static void _leave(gamestate_t *this, gamestate_t *next)
{
}

static void _draw(gamestate_t *this, caca_canvas_t *c)
{
  if(state == CLEAN)
  {
     unglitch(c, HIDE_CLEANS_PER_FRAME);
  }
  if(state == TUTORIAL)
  {
    glitch_str(c, tutorial, rand()%canvas_w, rand()%canvas_h, 10);
  }
  else if(state == GAMEPLAY)
  {
  }
}

static void _update(gamestate_t *this, double dt)
{
  // Increment timer
  t += dt;

  // Refresh state
  if(t < HIDE_CLEAN_TIME)
    state = CLEAN;
  else if(t < HIDE_CLEAN_TIME + HIDE_TUTORIAL_TIME)
    state = TUTORIAL;
  else
   state = GAMEPLAY;

  // Behave according to state
  if(state == GAMEPLAY)
  {
    // Read input state
    int kx, ky; input_xy(&kx, &ky);
  }
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
