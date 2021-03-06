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

#include "input.h"

#include <caca.h>

static bool _up = false, _down = false, _left = false, _right = false, 
            _action = false, _quit = false, _quit_prev = false;

void input_reset()
{
  _up = _down = _left = _right = _action = _quit = _quit_prev = false;
}

void input_set(int key, bool pressed)
{
  switch(key)
  {
    case CACA_KEY_UP: _up = pressed; break;
    case CACA_KEY_DOWN: _down = pressed; break;
    case CACA_KEY_LEFT: _left = pressed; break;
    case CACA_KEY_RIGHT: _right = pressed; break;
    
    case CACA_KEY_RETURN: case ' ': _action = pressed; break;
    case CACA_KEY_ESCAPE: _quit_prev = _quit; _quit = pressed; break;

    default: break;
  }
}

static void _xy(int *x, int *y, bool N, bool S, bool E, bool W)
{
  (*x) = (*y) = 0;
  if(W) (*x)--;
  if(E) (*x)++;
  if(N) (*y)--;
  if(S) (*y)++;
}

void input_xy(int *x, int *y)
{
  _xy(x, y, _up, _down, _right, _left);
}

bool input_action()
{
  return _action;
}

bool input_quit()
{
  return _quit;
}

bool input_quit_trigger()
{
  return (_quit && !_quit_prev);
}
