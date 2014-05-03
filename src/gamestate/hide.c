#include "hide.h"

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

static void _enter(gamestate_t *this, gamestate_t *previous)
{
  // Create avatar
  create_avatar(&avatar, 0.5*WORLD_W, 0.5*WORLD_H);

  // Reset timer
  t = 0.0;

  // Reset state
  state = TUTORIAL;
}

static void _leave(gamestate_t *this, gamestate_t *next)
{
  // Destroy avatar
  destroy_avatar(&avatar);
}

static void _draw(gamestate_t *this, caca_canvas_t *c)
{
  if(state == TUTORIAL)
  {
    glitch_str(c, tutorial, rand()%canvas_w, rand()%canvas_h, 10);
  }
  else if(state == GLITCH)
  {
    glitch(c, HIDE_GLITCHES_PER_FRAME);
  }
  else if(state == GAMEPLAY)
  {
    // Draw the avatar
    draw_avatar(&avatar, c);
  }
}

static void _update(gamestate_t *this, double dt)
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
    update_avatar(&avatar, dt, kx, ky);
  }
}


//
// Global variable
//

gamestate_t hide;

void hide_init()
{
  hide.enter = _enter;
  hide.leave = _leave;
  hide.draw = _draw;
  hide.update = _update;
}
