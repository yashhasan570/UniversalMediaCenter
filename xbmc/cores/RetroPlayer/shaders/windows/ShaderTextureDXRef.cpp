/*
 *  Copyright (C) 2019-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPD3D-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ShaderTextureDXRef.h"

#include "guilib/D3DResource.h"

using namespace UNIVERSAL MEDIA CENTER::SHADER;

CShaderTextureDXRef::CShaderTextureDXRef(CD3DTexture& texture) : m_texture(texture)
{
}

float CShaderTextureDXRef::GetWidth() const
{
  return static_cast<float>(m_texture.GetWidth());
}

float CShaderTextureDXRef::GetHeight() const
{
  return static_cast<float>(m_texture.GetHeight());
}

ID3D11ShaderResourceView* CShaderTextureDXRef::GetShaderResource() const
{
  return m_texture.GetShaderResource();
}
