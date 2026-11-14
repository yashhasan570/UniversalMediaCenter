/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/GameSettings.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CGUIGameRenderManager;

class CGUIGameVideoHandle
{
public:
  CGUIGameVideoHandle(CGUIGameRenderManager& renderManager);
  virtual ~CGUIGameVideoHandle();

  bool IsPlayingGame();
  bool SupportsRenderFeature(RENDERFEATURE feature);
  bool SupportsScalingMethod(SCALINGMETHOD method);

private:
  // Construction parameters
  CGUIGameRenderManager& m_renderManager;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
