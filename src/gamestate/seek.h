#pragma once

#include "gamestate.h"

#define SEEK_CLEAN_TIME 3.0
#define SEEK_TUTORIAL_TIME 3.0
#define SEEK_CLEANS_PER_FRAME 300

extern gamestate_t seek;
void seek_init();
