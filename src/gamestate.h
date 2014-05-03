#pragma once

#include <caca.h>

struct gamestate_t;

typedef struct gamestate_t
{
  void (*enter)(struct gamestate_t *this, struct gamestate_t *previous);
  void (*leave)(struct gamestate_t *this, struct gamestate_t *next);
  void (*update)(struct gamestate_t *this, double dt);
  void (*draw)(struct gamestate_t *this, caca_canvas_t *c);

} gamestate_t;

void gamestate_switch(gamestate_t *new_state);
void gamestate_update(double dt);
void gamestate_draw(caca_canvas_t *c);
