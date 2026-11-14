/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

enum class RenderStereoView
{
  OFF,
  LEFT,
  RIGHT,
};

enum class RenderStereoMode
{
  OFF,
  SPLIT_HORIZONTAL,
  SPLIT_VERTICAL,
  ANAGLYPH_RED_CYAN,
  ANAGLYPH_GREEN_MAGENTA,
  ANAGLYPH_YELLOW_BLUE,
  INTERLACED,
  CHECKERBOARD,
  HARDWAREBASED,
  MONO,
  COUNT,

  // Pseudo modes
  AUTO = 100,
  UNDEFINED = 999,
};
