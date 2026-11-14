/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RenderSystemGLES.h"

#include "platform/linux/WebOSTVPlatformConfig.h"

class CRenderSystemGLESWebOS : public CRenderSystemGLES
{
public:
  bool SupportsTextureSwizzle() const override
  {
    // on webOS 4 or less, swizzle causes graphical corruption in GUI icons
    if (WebOSTVPlatformConfig::GetWebOSVersion() <= 4)
      return false;

    return true;
  }
};
