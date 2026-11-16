/*
 *  Copyright (C) 2017-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <cstddef>

namespace UNIVERSAL MEDIA CENTER::SHADER
{
struct CUSTOMVERTEX
{
  float x;
  float y;
  float z;

  float tu;
  float tv;

  float tu2;
  float tv2;
};

static_assert(offsetof(CUSTOMVERTEX, tu2) == 5 * sizeof(float));
static_assert(sizeof(CUSTOMVERTEX) == 7 * sizeof(float));
} // namespace UNIVERSAL MEDIA CENTER::SHADER
