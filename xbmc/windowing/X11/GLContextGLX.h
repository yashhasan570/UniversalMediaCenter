/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GLContext.h"

#include <GL/glx.h>

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace X11
{

class CGLContextGLX : public CGLContext
{
public:
  explicit CGLContextGLX(Display *dpy);
  bool Refresh(bool force, int screen, Window glWindow, bool &newContext) override;
  void Destroy() override;
  void Detach() override;
  void SetVSync(bool enable) override;
  void SwapBuffers() override;
  void QueryExtensions() override;
  GLXWindow m_glxWindow = 0;
  GLXContext m_glxContext = 0;

protected:
  bool IsSuitableVisual(XVisualInfo *vInfo);

  int (*m_glXGetVideoSyncSGI)(unsigned int*);
  int (*m_glXWaitVideoSyncSGI)(int, int, unsigned int*);
  int (*m_glXSwapIntervalMESA)(int);
  PFNGLXSWAPINTERVALEXTPROC m_glXSwapIntervalEXT;
  int m_nScreen;
  int m_iVSyncErrors;
  int m_vsyncMode;
};

}
}
}
