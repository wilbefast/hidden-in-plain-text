#include "input.h"

#include <caca.h>

static bool _up = false, _down = false, _left = false, _right = false, _escape = false;

void input_set(int key, bool pressed)
{
  switch(key)
  {
    case CACA_KEY_UP: _up = pressed; break;
    case CACA_KEY_DOWN: _down = pressed; break;
    case CACA_KEY_LEFT: _left = pressed; break;
    case CACA_KEY_RIGHT: _right = pressed; break;
    case CACA_KEY_ESCAPE: _escape = pressed; break;
    default: break;
  }
}

void input_get(int *x, int *y, bool* escape)
{
  (*x) = (*y) = 0;
  if(_left) (*x)--;
  if(_right) (*x)++;
  if(_up) (*y)--;
  if(_down) (*y)++;
  (*escape) = _escape;


}
