/*
 *  Copyright (C) 2017-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RenderBufferDMA.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderBufferDMAOpenGL : public CRenderBufferDMA
{
public:
  explicit CRenderBufferDMAOpenGL(int fourcc);
  ~CRenderBufferDMAOpenGL() override = default;

protected:
  // Implementation of CRenderBufferDMA
  bool UploadFromMemory() override;
  void ConfigureTexture() override;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
