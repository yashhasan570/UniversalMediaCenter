/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/GameSettings.h"
#include "cores/RetroPlayer/RetroPlayerTypes.h"
#include "threads/CriticalSection.h"

#include <memory>
#include <vector>

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class IRendererFactory;
class IRenderBufferPools;

class CRenderBufferManager
{
public:
  CRenderBufferManager() = default;
  ~CRenderBufferManager();

  void RegisterPools(IRendererFactory* factory, RenderBufferPoolVector pools);
  RenderBufferPoolVector GetPools(IRendererFactory* factory);
  std::vector<IRenderBufferPool*> GetBufferPools();
  void FlushPools();

  std::string GetRenderSystemName(IRenderBufferPool* renderBufferPool) const;

  bool HasScalingMethod(SCALINGMETHOD scalingMethod) const;

protected:
  struct RenderBufferPools
  {
    IRendererFactory* factory;
    RenderBufferPoolVector pools;
  };

  std::vector<RenderBufferPools> m_pools;
  mutable CCriticalSection m_critSection;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
