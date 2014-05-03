#pragma once

#include "gamestate.h"

#define SCORE_CLEAN_TIME 2.0
#define SCORE_CLEANS_PER_FRAME 400

extern gamestate_t score;
void score_init();
