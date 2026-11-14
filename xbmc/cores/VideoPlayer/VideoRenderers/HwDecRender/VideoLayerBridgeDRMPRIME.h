/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/VideoPlayer/Buffers/DmaBufIdentityCache.h"
#include "cores/VideoPlayer/Interface/StreamInfo.h"
#include "windowing/gbm/VideoLayerBridge.h"

#include <memory>

#include <drm_mode.h>

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace GBM
{
class CDRMAtomic;
}
} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER

class CVideoBufferDRMPRIME;

class CVideoLayerBridgeDRMPRIME : public UNIVERSAL MEDIA CENTER::WINDOWING::GBM::CVideoLayerBridge
{
public:
  CVideoLayerBridgeDRMPRIME(std::shared_ptr<UNIVERSAL MEDIA CENTER::WINDOWING::GBM::CDRMAtomic> drm);
  ~CVideoLayerBridgeDRMPRIME() override;
  void Disable() override;

  virtual void Configure(CVideoBufferDRMPRIME* buffer);
  virtual void SetVideoPlane(CVideoBufferDRMPRIME* buffer, const CRect& destRect);
  virtual void UpdateVideoPlane();

protected:
  std::shared_ptr<UNIVERSAL MEDIA CENTER::WINDOWING::GBM::CDRMAtomic> m_DRM;

private:
  void Acquire(CVideoBufferDRMPRIME* buffer, uint32_t fbId);
  void Release(CVideoBufferDRMPRIME* buffer);
  bool PrepareBuffer(CVideoBufferDRMPRIME* buffer);
  //! \brief Convert the buffer's descriptor to a framebuffer; 0 on failure.
  uint32_t CreateFramebuffer(CVideoBufferDRMPRIME* buffer);

  static constexpr size_t MAX_FB_CACHE = 32;

  DRMPRIME::CDmaBufIdentityCache m_fbCache{MAX_FB_CACHE, "bridge-fb"};
  CVideoBufferDRMPRIME* m_buffer = nullptr;
  CVideoBufferDRMPRIME* m_prev_buffer = nullptr;
  uint32_t m_fb_id{0};
  uint32_t m_prev_fb_id{0};
};
