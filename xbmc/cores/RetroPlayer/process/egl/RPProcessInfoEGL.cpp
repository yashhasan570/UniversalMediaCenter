/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoEGL.h"

#include <EGL/egl.h>

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

CRPProcessInfoEGL::CRPProcessInfoEGL(std::string platformName)
  : CRPProcessInfo(std::move(platformName))
{
}

HwProcedureAddress CRPProcessInfoEGL::GetHwProcedureAddress(const char* symbol)
{
  if (symbol == nullptr)
    return nullptr;

  return static_cast<HwProcedureAddress>(eglGetProcAddress(symbol));
}
