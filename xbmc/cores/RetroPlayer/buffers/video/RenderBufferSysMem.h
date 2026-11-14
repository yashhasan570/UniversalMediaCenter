/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/buffers/BaseRenderBuffer.h"

#include <stdint.h>
#include <vector>

extern "C"
{
#include <libavutil/pixfmt.h>
}

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderBufferSysMem : public CBaseRenderBuffer
{
public:
  CRenderBufferSysMem() = default;
  ~CRenderBufferSysMem() override = default;

  // Implementation of IRenderBuffer via CBaseRenderBuffer
  bool Allocate(AVPixelFormat format, unsigned int width, unsigned int height) override;
  size_t GetFrameSize() const override;
  uint8_t* GetMemory() override;

  // Utility functions
  static size_t GetBufferSize(AVPixelFormat format, unsigned int width, unsigned int height);

protected:
  std::vector<uint8_t> m_data;
};

} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
