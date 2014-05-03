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
#include "../colour.h"

#include "gamestate.h"


//
// Attributes
//

static avatar_t avatar;


//
// Methods
//

static void _enter(gamestate_t *this, gamestate_t *previous)
{
  // Create avatar
  create_avatar(&avatar, 0.5*WORLD_W, 0.5*WORLD_H);
}

static void _leave(gamestate_t *this, gamestate_t *next)
{
  // Destroy avatar
  destroy_avatar(&avatar);
}

static void _draw(gamestate_t *this, caca_canvas_t *c)
{
  // Draw the avatar
  draw_avatar(&avatar, c);
}

static void _update(gamestate_t *this, double dt)
{
  // Read input state
  int kx, ky; input_xy(&kx, &ky);

  // Update the avatar
  update_avatar(&avatar, dt, kx, ky);
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
