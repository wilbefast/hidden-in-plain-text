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

#include "perlin.h"

#include <stdlib.h>
#include <math.h>

#include "useful.h"

#include "platform_specific.h"

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

static vector_t _gradient(vector_t position)
{
  return vector(rand_between(-1.0, 1.0), rand_between(-1.0, 1.0));
}

static inline double _interpolate(double a, double b, double amount)
{
  amount = (1.0 - cos(amount * 3.1415927))*0.5;
  return a*(1.0 - amount) + b*amount;
}

double perlin_noise(double x, double y)
{
	// local variables 
  vector_t target, corner[4];
	int ix, iy, i;
	double influence[4], top, bottom;
	
	target = vector(x, y);
  ix = (int)x;
	iy = (int)y;

  corner[0] = vector(ix, iy);
  corner[1] = vector(ix + 1, iy);
  corner[2] = vector(ix, iy + 1);
  corner[3] = vector(ix + 1, iy + 1);

  for(i = 0; i < 4; i++)
    influence[i] = dot(_gradient(corner[i]), vsub(target, corner[i]));

  top = _interpolate(influence[0], influence[1], x - ix);
  bottom = _interpolate(influence[2], influence[3], x - ix);
  return _interpolate(top, bottom, y - iy);
}
