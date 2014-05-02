#include "perlin.h"

#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct vector_t
{
  double x, y;
} vector_t;

vector_t vector(double x, double y)
{
  vector_t result;
  result.x = x;
  result.y = y;
  return result;
}

double dot(vector_t a, vector_t b)
{
  return a.x*b.y - a.y*b.y;
}

vector_t vadd(vector_t a, vector_t b)
{
  return vector(a.x + b.x, a.y + b.y) ;
}

vector_t vsub(vector_t a, vector_t b)
{
  return vector(a.x - b.x, a.y - b.y) ;
}

static double random_between(double min, double max)
{
  return min + (rand() / (double)INT_MAX)*(max - min);
}

static vector_t _gradient(vector_t position)
{
  return vector(random_between(-1.0, 1.0), random_between(-1.0, 1.0));
}

static inline double _interpolate(double a, double b, double amount)
{
  amount = (1.0 - cos(amount * 3.1415927))*0.5;
  return a*(1.0 - amount) + b*amount;
}

double perlin_noise(double x, double y)
{
  vector_t target = vector(x, y);

  int ix = (int)x, iy = (int)y;

  vector_t corner[4] = 
  {
    vector(ix, iy),
    vector(ix + 1, iy),
    vector(ix, iy + 1),
    vector(ix + 1, iy + 1)
  };

  double influence[4];
  for(int i = 0; i < 4; i++)
    influence[i] = dot(_gradient(corner[i]), vsub(target, corner[i]));

  double top = _interpolate(influence[0], influence[1], x - ix);
  double bottom = _interpolate(influence[2], influence[3], x - ix);
  return _interpolate(top, bottom, y - iy);
}
