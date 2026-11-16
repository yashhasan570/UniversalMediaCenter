/*
 *  Copyright (C) 2017-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/shaders/IShaderSampler.h"

#include <d3d11.h>

namespace UNIVERSAL MEDIA CENTER::SHADER
{

class CShaderSamplerDX : public IShaderSampler
{
public:
  CShaderSamplerDX(ID3D11SamplerState* sampler);
  ~CShaderSamplerDX() override;

private:
  ID3D11SamplerState* const m_sampler;
};
} // namespace UNIVERSAL MEDIA CENTER::SHADER
