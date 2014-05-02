#pragma once

#define SQR(k) ((k)*(k))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define PI 3.141592653589793
#define TWOPI (2*PI)

double rand_between(double min, double max);
double rand_double();

double clamp(double k, double min, double max);
double lap(double k, double min, double max);
