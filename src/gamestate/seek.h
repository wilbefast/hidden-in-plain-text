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

#define SEEK_CLEAN_TIME 1.0
#define SEEK_TUTORIAL_TIME 1.0
#define SEEK_CLEANS_PER_FRAME 800

extern gamestate_t seek;
void seek_init();
