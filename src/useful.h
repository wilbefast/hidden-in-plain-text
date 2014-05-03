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

// Clamp and lap
double clamp(double k, double min, double max);
double lap(double k, double min, double max);

// Colours
void hsl_to_rgb(double hsl[3], double rgb[3]);
