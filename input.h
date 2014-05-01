#pragma once

#include <stdbool.h>

void input_set(int key, bool pressed);
void input_get(int *x, int *y, bool *escape);
