#include "perlin.h"

#include <math.h>

static inline double _noise(int x, int y)
{
  int n = x + y*57;
  n = (n << 13) ^ n;
  return (double)((1 - (x*(x*x*15731 + 789221) + 1376312589)) & 0x7fffffff) / 1073741824.0;
}

static inline double _interpolate(double a, double b, double amount)
{
  amount = (1.0 - cos(amount * 3.1415927))*0.5;
  return a*(1.0 - amount) + b*amount;
}

double perlin_noise(double x, double y)
{
  int ix = (int)x, iy = (int)y;

  double top_l = _noise(ix, iy),
         top_r = _noise(ix + 1, iy),
         bottom_l = _noise(ix, iy + 1),
         bottom_r = _noise(ix + 1, iy + 1);

  double top = _interpolate(top_l, top_r, x - ix);
  double bottom = _interpolate(bottom_l, bottom_r, x - ix);

  return _interpolate(top, bottom, y - iy);
}
