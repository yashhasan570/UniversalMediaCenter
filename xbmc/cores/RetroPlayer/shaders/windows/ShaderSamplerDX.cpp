/*
 *  Copyright (C) 2017-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ShaderSamplerDX.h"

using namespace UNIVERSAL MEDIA CENTER::SHADER;

CShaderSamplerDX::CShaderSamplerDX(ID3D11SamplerState* sampler) : m_sampler(sampler)
{
}

CShaderSamplerDX::~CShaderSamplerDX()
{
  if (m_sampler != nullptr)
    m_sampler->Release();
}
