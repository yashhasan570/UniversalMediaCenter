/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <memory>

#ifdef __OBJC__
@class NSOpenGLContext;
#else
struct NSOpenGLContext;
#endif

namespace KODI::RETRO
{
class IHwRenderingContext;

std::unique_ptr<IHwRenderingContext> CreateHwRenderingContextOSX(NSOpenGLContext* shareContext);
} // namespace KODI::RETRO
