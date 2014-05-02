#include "useful.h"

#include <stdlib.h>
#include <limits.h>

// Random

inline double rand_between(double min, double max)
{
  return min + (rand_double()*(max - min));
}

inline double rand_double()
{
  return rand() / (double)RAND_MAX;
}


// Clamp and lap

inline double clamp(double k, double min, double max)
{
  return (k > max) ? max : ((k < min) ? min : k);
}

inline double lap(double k, double min, double max)
{
  return (k > max) ? (k - max) : ((k < min) ? (k + (max - min)) : k);
}
