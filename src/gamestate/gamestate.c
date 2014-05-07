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

#include "gamestate.h" 

#include "../input.h"

static gamestate_t *_current_state = NULL;

void gamestate_switch(gamestate_t *new_state)
{
  if(_current_state)
    _current_state->leave(_current_state, new_state);

  if(new_state)
    new_state->enter(new_state, _current_state);

  _current_state = new_state;

  input_reset();
}

void gamestate_update(double dt)
{
  if(_current_state)
    _current_state->update(_current_state, dt);
}

void gamestate_draw(caca_canvas_t *c)
{
  if(_current_state)
    _current_state->draw(_current_state, c);
}

bool gamestate_is(gamestate_t *state)
{
  return (_current_state == state);
}
