/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DBusUtil.h"
#include "UPowerSyscall.h"

class CConsoleUPowerSyscall : public CUPowerSyscall
{
public:
  CConsoleUPowerSyscall();
  bool Powerdown() override;
  bool Reboot() override;
  static bool HasConsoleKitAndUPower();
private:
  static bool ConsoleKitMethodCall(const char *method);
};
