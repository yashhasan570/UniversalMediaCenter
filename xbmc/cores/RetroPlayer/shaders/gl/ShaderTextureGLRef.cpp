/*
 *  Copyright (C) 2019-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ShaderTextureGLRef.h"

using namespace UNIVERSAL MEDIA CENTER::SHADER;

CShaderTextureGLRef::CShaderTextureGLRef(uint32_t textureWidth,
                                         uint32_t textureHeight,
                                         GLuint texture)
  : m_textureWidth(textureWidth),
    m_textureHeight(textureHeight),
    m_texture(texture)
{
}

float CShaderTextureGLRef::GetWidth() const
{
  return static_cast<float>(m_textureWidth);
}

float CShaderTextureGLRef::GetHeight() const
{
  return static_cast<float>(m_textureHeight);
}

void CShaderTextureGLRef::BindToUnit(unsigned int unit)
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
