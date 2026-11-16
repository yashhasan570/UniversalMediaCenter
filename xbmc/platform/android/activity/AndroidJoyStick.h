/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <vector>

struct AInputEvent;

class CAndroidJoyStick
{
public:
  CAndroidJoyStick() = default;
  ~CAndroidJoyStick() = default;

  bool onJoyStickEvent(AInputEvent* event);
};
