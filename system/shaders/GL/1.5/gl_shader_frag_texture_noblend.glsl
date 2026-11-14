/*
 *  Copyright (C) 2010-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#version 150

uniform sampler2D m_samp0;
in vec2 m_cord0;
out vec4 fragColor;

// SM_TEXTURE_NOBLEND shader
void main()
{
  fragColor = texture(m_samp0, m_cord0);
#if defined(UNIVERSAL MEDIA CENTER_LIMITED_RANGE)
  fragColor.rgb *= (235.0-16.0) / 255.0;
  fragColor.rgb += 16.0 / 255.0;
#endif
}
