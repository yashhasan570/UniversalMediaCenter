/*
 *  Copyright (C) 2019-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/shaders/ShaderTypes.h"

#include "system_gl.h"

namespace KODI::SHADER
{

class CShaderUtilsGLES
{
public:
  static GLint TranslateWrapType(WrapType wrapType);
  static std::string GetGLSLVersion(std::string& source);
};
} // namespace KODI::SHADER
