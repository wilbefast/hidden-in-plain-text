#include "input.h"

#include <caca.h>

static bool _up = false, _down = false, _left = false, _right = false, 
            _action = false, _escape = false;

void input_set(int key, bool pressed)
{
  switch(key)
  {
    case CACA_KEY_UP: _up = pressed; break;
    case CACA_KEY_DOWN: _down = pressed; break;
    case CACA_KEY_LEFT: _left = pressed; break;
    case CACA_KEY_RIGHT: _right = pressed; break;
    
    case CACA_KEY_RETURN: case ' ': _action = pressed; break;
    
    case CACA_KEY_ESCAPE: _escape = pressed; break;

    default: break;
  }
}

static inline void _getxy(int *x, int *y, bool N, bool S, bool E, bool W)
{
  (*x) = (*y) = 0;
  if(W) (*x)--;
  if(E) (*x)++;
  if(N) (*y)--;
  if(S) (*y)++;
}

void input_get(int *x, int *y, bool* action, bool* escape)
{
  _getxy(x, y, _up, _down, _right, _left);
  (*escape) = _escape;
}
