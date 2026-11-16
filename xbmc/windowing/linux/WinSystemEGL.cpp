/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "WinSystemEGL.h"

using namespace UNIVERSAL MEDIA CENTER::WINDOWING::LINUX;

CWinSystemEGL::CWinSystemEGL(EGLenum platform, std::string const& platformExtension)
  : m_eglContext{platform, platformExtension}
{
}

EGLDisplay CWinSystemEGL::GetEGLDisplay() const
{
  return m_eglContext.GetEGLDisplay();
}

EGLSurface CWinSystemEGL::GetEGLSurface() const
{
  return m_eglContext.GetEGLSurface();
}

EGLContext CWinSystemEGL::GetEGLContext() const
{
  return m_eglContext.GetEGLContext();
}

EGLConfig CWinSystemEGL::GetEGLConfig() const
{
  return m_eglContext.GetEGLConfig();
}
