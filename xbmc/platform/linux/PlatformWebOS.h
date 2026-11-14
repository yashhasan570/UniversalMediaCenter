/*
*  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlatformLinux.h"

class CPlatformWebOS : public CPlatformLinux
{
public:
  bool InitStageOne() override;
  bool InitStageTwo() override;
  bool InitStageThree() override;
  static CPlatform* CreateInstance();

protected:
  void RegisterPowerManagement() override;

public:
  bool IsConfigureAddonsAtStartupEnabled() override;

private:
  std::string GetHomePath();
};
