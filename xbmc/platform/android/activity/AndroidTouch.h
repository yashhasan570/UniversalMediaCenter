/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <math.h>

#include <android/input.h>

class CAndroidTouch
{

public:
  CAndroidTouch();
  virtual ~CAndroidTouch();
  bool onTouchEvent(AInputEvent* event);

protected:
  virtual void setDPI(uint32_t dpi);

private:
  uint32_t m_dpi = 160;
};
