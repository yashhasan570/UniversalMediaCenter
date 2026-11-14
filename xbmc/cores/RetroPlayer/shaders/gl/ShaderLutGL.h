/*
 *  Copyright (C) 2019-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/shaders/IShaderLut.h"
#include "cores/RetroPlayer/shaders/ShaderTypes.h"

#include <memory>
#include <string>

#include "system_gl.h"

namespace UNIVERSAL MEDIA CENTER::SHADER
{
class CTextureBase;
struct ShaderLut;

class CShaderLutGL : public IShaderLut
{
public:
  CShaderLutGL(std::string id, std::string path);
  ~CShaderLutGL() override = default;

  // Implementation of IShaderLut
  bool Create(const ShaderLut& lut) override;
  CTexture* GetTexture() override;
  void ReleaseTexture() override;

private:
  static std::unique_ptr<CTexture> CreateLUTTexture(const ShaderLut& lut);

  std::unique_ptr<CTexture> m_texture;
  ShaderLut m_lut;
  bool m_released{false};
};
} // namespace UNIVERSAL MEDIA CENTER::SHADER
