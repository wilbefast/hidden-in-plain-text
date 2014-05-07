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

#include "global.h"

int canvas_w = -1;
int canvas_h = -1;
double world_to_canvas_x = -1.0;
double world_to_canvas_y = -1.0;

float hide_position[2] = { 0.0f, 0.0f };
float seek_position[2] = { 0.0f, 0.0f };
