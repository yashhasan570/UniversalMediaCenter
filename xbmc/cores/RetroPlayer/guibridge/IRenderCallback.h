/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/GameSettings.h"

namespace KODI
{
namespace RETRO
{
class IRenderCallback
{
public:
  virtual ~IRenderCallback() = default;

  virtual bool SupportsRenderFeature(RENDERFEATURE feature) const = 0;
  virtual bool SupportsScalingMethod(SCALINGMETHOD method) const = 0;
};
} // namespace RETRO
} // namespace KODI
