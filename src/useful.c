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

#include "useful.h"

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

#include "platform_specific.h"

// Random

double rand_between(double min, double max)
{
  return min + (rand_double()*(max - min));
}

double rand_double()
{
  return rand() / (double)RAND_MAX;
}

// Vector maths

double dist(double x1, double y1, double x2, double y2)
{
  double dx, dy;
  dx = x1 - x2;
  dy = y1 - y2;
  return sqrt(SQR(dx) + SQR(dy));
}

// Clamp and lap

double clamp(double k, double min, double max)
{
  return (k > max) ? max : ((k < min) ? min : k);
}

double lap(double k, double min, double max)
{
  return (k > max) ? (k - max) : ((k < min) ? (k + (max - min)) : k);
}


// Colour

static double _hue_to_rgb(double p, double q, double t)
{
  if(t < 0.0) t++;
  if(t > 1.0) t--;
  if(t < 1.0/6.0) return p + (q - p)*6*t;
  if(t < 1.0/2.0) return q;
  if(t < 2.0/3.0) return p + (q - p)*(2.0/3.0 - t)*6.0;
  return p;
}

void hsl_to_rgb (double hsl[3], double rgb[3])
{
  double H = hsl[0], S = hsl[1], L = hsl[2];
  
  // achromatic ?
  if(S == 0)
  {
    rgb[0] = rgb[1] = rgb[2] = L;
  }
  else
  {
    double q = (L < 0.5) ? L*(S + 1) : L + S - L*S;
    double p = 2*L - q;
    rgb[0] = _hue_to_rgb(p, q, H + 1.0/3.0);
    rgb[1] = _hue_to_rgb(p, q, H);
    rgb[2] = _hue_to_rgb(p, q, H - 1.0/3.0);
  }  
}
