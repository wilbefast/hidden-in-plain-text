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

#define SQR(k) ((k)*(k))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define PI 3.141592653589793
#define TWOPI (2*PI)
#define MICROSECONDS_TO_SECONDS(us) ((us)*0.000001)
#define MICROSECONDS_PER_FRAME 1000000/60

// Random
double rand_between(double min, double max);
double rand_double();

// Vector maths
double dist(double x1, double y1, double x2, double y2);

// Clamp and lap
double clamp(double k, double min, double max);
double lap(double k, double min, double max);

// Colours
void hsl_to_rgb(double hsl[3], double rgb[3]);
