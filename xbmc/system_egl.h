/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#if defined(TARGET_LINUX) || defined(TARGET_FREEBSD)

#if defined(WL_EGL_PLATFORM)
#undef WL_EGL_PLATFORM
#define UNIVERSALMEDIA_WL_EGL_PLATFORM
#endif

#if defined(__GBM__)
#undef __GBM__
#define UNIVERSALMEDIA__GBM__
#endif

#if defined(USE_X11)
#undef USE_X11
#define UNIVERSALMEDIA_USE_X11
#endif

#define EGL_NO_X11
#define MESA_EGL_NO_X11_HEADERS
#endif

#include <EGL/egl.h>

#if defined(TARGET_LINUX) || defined(TARGET_FREEBSD)

#if defined(UNIVERSALMEDIA_WL_EGL_PLATFORM)
#undef UNIVERSALMEDIA_WL_EGL_PLATFORM
#define WL_EGL_PLATFORM
#endif

#if defined(UNIVERSALMEDIA__GBM__)
#undef UNIVERSALMEDIA__GBM__
#define __GBM__
#endif

#if defined(UNIVERSALMEDIA_USE_X11)
#undef UNIVERSALMEDIA_USE_X11
#define USE_X11
#endif

#endif
