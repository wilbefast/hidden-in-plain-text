#pragma once

#include <stdbool.h>

void input_set(int key, bool pressed);
void input_get(int *x1, int *y1, int *x2, int *y2,  bool *escape);
