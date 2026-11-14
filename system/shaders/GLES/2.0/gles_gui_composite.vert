/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#version 100

attribute vec2 a_pos;
attribute vec2 a_tex;
varying vec2 v_tex;
uniform mat4 u_proj;

void main()
{
  gl_Position = u_proj * vec4(a_pos, 0.0, 1.0);
  v_tex = a_tex;
}
