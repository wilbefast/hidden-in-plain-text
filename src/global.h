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

#define WORLD_W 1280.0
#define WORLD_H 800.0
#define FRAMES_PER_SECOND 60

extern int canvas_w;
extern int canvas_h;
extern double world_to_canvas_x;
extern double world_to_canvas_y;

extern float hide_position[2];
extern float seek_position[2];
