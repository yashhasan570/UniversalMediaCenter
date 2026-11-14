/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../OSScreenSaver.h"
#include "threads/Timer.h"

#include <X11/Xlib.h>

class COSScreenSaverX11 : public UNIVERSAL MEDIA CENTER::WINDOWING::IOSScreenSaver
{
public:
  explicit COSScreenSaverX11(Display* dpy);
  void Inhibit() override;
  void Uninhibit() override;

private:
  void ResetScreenSaver();

  Display* m_dpy;
  CTimer m_screensaverResetTimer;
};
