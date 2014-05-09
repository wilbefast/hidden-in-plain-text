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

#pragma once

#include "../platform_specific.h"

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
bool gamestate_is(gamestate_t *state);
