/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#version 150

in vec2 m_attrpos;
uniform mat4 m_matrix;

void main()
{
  gl_Position = m_matrix * vec4(m_attrpos, 0., 1.);
}
