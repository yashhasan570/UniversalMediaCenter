/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class IInputDeviceCallbacks
{
public:
  virtual ~IInputDeviceCallbacks() = default;

  virtual void OnInputDeviceAdded(int deviceId) = 0;
  virtual void OnInputDeviceChanged(int deviceId) = 0;
  virtual void OnInputDeviceRemoved(int deviceId) = 0;

protected:
  IInputDeviceCallbacks() = default;
};
