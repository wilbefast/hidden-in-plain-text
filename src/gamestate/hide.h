#pragma once

#include "gamestate.h"

#define HIDE_TUTORIAL_TIME 3.0
#define HIDE_GLITCH_TIME 2.0
#define HIDE_GLITCHES_PER_FRAME 200

extern gamestate_t hide;
void hide_init();
