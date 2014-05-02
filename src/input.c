#include "input.h"

#include <caca.h>

static bool _up1 = false, _down1 = false, _left1 = false, _right1 = false, 
            _up2 = false, _down2 = false, _left2 = false, _right2 = false, 
            _escape = false;

void input_set(int key, bool pressed)
{
  switch(key)
  {
    case CACA_KEY_UP: _up1 = pressed; break;
    case CACA_KEY_DOWN: _down1 = pressed; break;
    case CACA_KEY_LEFT: _left1 = pressed; break;
    case CACA_KEY_RIGHT: _right1 = pressed; break;
    
    case 'z': case 'w': _up2 = pressed; break;
    case 's': _down2 = pressed; break;
    case 'd': _right2 = pressed; break;
    case 'q': _left2 = pressed; break;

    case CACA_KEY_ESCAPE: _escape = pressed; break;

    default: break;
  }
}

static void _getxy(int *x, int *y, bool N, bool S, bool E, bool W)
{
  (*x) = (*y) = 0;
  if(W) (*x)--;
  if(E) (*x)++;
  if(N) (*y)--;
  if(S) (*y)++;
}

void input_get(int *x1, int *y1, int *x2, int *y2, bool* escape)
{
  _getxy(x1, y1, _up1, _down1, _right1, _left1);
  _getxy(x2, y2, _up2, _down2, _right2, _left2);
  (*escape) = _escape;
}
