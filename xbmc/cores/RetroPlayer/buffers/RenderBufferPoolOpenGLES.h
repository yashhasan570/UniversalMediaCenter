/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "BaseRenderBufferPool.h"
#include "IRenderBuffer.h"

#include "system_gl.h"

namespace KODI
{
namespace RETRO
{
class CRenderVideoSettings;

class CRenderBufferPoolOpenGLES : public CBaseRenderBufferPool
{
public:
  explicit CRenderBufferPoolOpenGLES(bool supportsTextureSwizzle);
  ~CRenderBufferPoolOpenGLES() override = default;

  // Implementation of IRenderBufferPool via CBaseRenderBufferPool
  bool IsCompatible(const CRenderVideoSettings& renderSettings) const override;

protected:
  // Implementation of CBaseRenderBufferPool
  IRenderBuffer* CreateRenderBuffer(void* header = nullptr) override;
  bool ConfigureInternal() override;

private:
  const bool m_supportsTextureSwizzle;

  // Configuration parameters
  GLuint m_pixelType = 0;
  GLuint m_internalFormat = 0;
  GLuint m_pixelFormat = 0;
  GLuint m_bpp = 0;
};
} // namespace RETRO
} // namespace KODI
