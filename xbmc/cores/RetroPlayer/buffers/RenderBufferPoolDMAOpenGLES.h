/*
 *  Copyright (C) 2017-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RenderBufferPoolDMA.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderBufferPoolDMAOpenGLES : public CRenderBufferPoolDMA
{
public:
  CRenderBufferPoolDMAOpenGLES() = default;
  ~CRenderBufferPoolDMAOpenGLES() override = default;

protected:
  // Implementation of CBaseRenderBufferPool
  IRenderBuffer* CreateRenderBuffer(void* header = nullptr) override;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
