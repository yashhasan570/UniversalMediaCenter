/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RPBaseRenderer.h"
#include "cores/GameSettings.h"
#include "cores/RetroPlayer/buffers/BaseRenderBufferPool.h"
#include "cores/RetroPlayer/process/RPProcessInfo.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRendererFactoryGuiTexture : public IRendererFactory
{
public:
  ~CRendererFactoryGuiTexture() override = default;

  // Implementation of IRendererFactory
  std::string RenderSystemName() const override;
  CRPBaseRenderer* CreateRenderer(const CRenderSettings& settings,
                                  CRenderContext& context,
                                  std::shared_ptr<IRenderBufferPool> bufferPool) override;
  RenderBufferPoolVector CreateBufferPools(CRenderContext& context) override;
};

class CRenderBufferPoolGuiTexture : public CBaseRenderBufferPool
{
public:
  CRenderBufferPoolGuiTexture(SCALINGMETHOD scalingMethod);
  ~CRenderBufferPoolGuiTexture() override = default;

  // Implementation of IRenderBufferPool via CBaseRenderBufferPool
  bool IsCompatible(const CRenderVideoSettings& renderSettings) const override;

  // Implementation of CBaseRenderBufferPool
  IRenderBuffer* CreateRenderBuffer(void* header = nullptr) override;

private:
  SCALINGMETHOD m_scalingMethod;
};

class CRPRendererGuiTexture : public CRPBaseRenderer
{
public:
  CRPRendererGuiTexture(const CRenderSettings& renderSettings,
                        CRenderContext& context,
                        std::shared_ptr<IRenderBufferPool> bufferPool);
  ~CRPRendererGuiTexture() override = default;

  // Public implementation of CRPBaseRenderer
  bool Supports(RENDERFEATURE feature) const override;
  SCALINGMETHOD GetDefaultScalingMethod() const override { return SCALINGMETHOD::NEAREST; }

protected:
  // Protected implementation of CRPBaseRenderer
  void RenderInternal(uint8_t alpha) override;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
