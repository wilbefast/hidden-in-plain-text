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

#include "gamestate.h"

#define HIDE_TUTORIAL_TIME 3.0
#define HIDE_GLITCH_TIME 2.0
#define HIDE_GLITCHES_PER_FRAME 200

extern gamestate_t hide;
void hide_init();
