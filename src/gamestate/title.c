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

// Title gamestate attributes

static avatar_t avatar;

// Title gamestate functions 

static void title_enter(gamestate_t *this, gamestate_t *previous)
{
  // Create avatar
  create_avatar(&avatar, 0.5*WORLD_W, 0.5*WORLD_H);
}

static void title_leave(gamestate_t *this, gamestate_t *next)
{
  // Destroy avatar
  destroy_avatar(&avatar);
}

static bool first = true;
static void title_draw(gamestate_t *this, caca_canvas_t *c)
{
  if(first)
  {
    // Generate background
    for(int x = 0; x < canvas_w; x++)
      for(int y = 0; y < canvas_h; y++)
        caca_put_char(c, x, y, get_char(0.5 + perlin_noise(x/(double)canvas_w, y/(double)canvas_h))); 
    // Only do this once
    first = false;
  }

  // Draw the avatar
  draw_avatar(&avatar, c);
}

static void title_update(gamestate_t *this, double dt)
{
  // Read input state
  int kx, ky; input_xy(&kx, &ky);

  // Update the avatar
  update_avatar(&avatar, dt, kx, ky);
}

// Title gamestate global variable

gamestate_t title;

void title_init()
{
  title.enter = title_enter;
  title.leave = title_leave;
  title.draw = title_draw;
  title.update = title_update;
}
