/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

struct AInputEvent;

class IInputDeviceEventHandler
{
public:
  virtual ~IInputDeviceEventHandler() = default;

  virtual bool OnInputDeviceEvent(const AInputEvent* event) = 0;

protected:
  IInputDeviceEventHandler() = default;
};
