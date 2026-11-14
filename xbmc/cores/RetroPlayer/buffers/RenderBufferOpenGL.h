/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/buffers/video/RenderBufferSysMem.h"

#include "system_gl.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderBufferOpenGL : public CRenderBufferSysMem
{
public:
  CRenderBufferOpenGL(GLuint pixelType, GLuint internalFormat, GLuint pixelFormat, GLuint bpp);
  ~CRenderBufferOpenGL() override;

  // Implementation of IRenderBuffer via CRenderBufferSysMem
  bool UploadTexture() override;

  GLuint TextureID() const { return m_textureId; }

private:
  // Construction parameters
  const GLuint m_pixelType;
  const GLuint m_internalFormat;
  const GLuint m_pixelFormat;
  const GLuint m_bpp;

  const GLenum m_textureTarget = GL_TEXTURE_2D; //! @todo
  GLuint m_textureId = 0;

  void CreateTexture();
  void DeleteTexture();
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
