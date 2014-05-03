#pragma once

#include <stdbool.h>

void input_reset();
void input_set(int key, bool pressed);
void input_xy(int *x, int *y);
bool input_action();
bool input_quit();
bool input_quit_trigger();
