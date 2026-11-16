/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
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

namespace UNIVERSAL MEDIA CENTER::RETRO
{
class IHwRenderingContext;

std::unique_ptr<IHwRenderingContext> CreateHwRenderingContextOSX(NSOpenGLContext* shareContext);
} // namespace UNIVERSAL MEDIA CENTER::RETRO
