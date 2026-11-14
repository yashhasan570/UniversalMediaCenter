/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/GpuInfo.h"

class CGPUInfoWin32 : public CGPUInfo
{
public:
  CGPUInfoWin32() = default;
  ~CGPUInfoWin32() = default;

private:
  bool GetGPUPlatformTemperature(CTemperature& temperature) const override;
  bool GetGPUTemperatureFromCommand(CTemperature& temperature,
                                    const std::string& cmd) const override;
  bool SupportsCustomTemperatureCommand() const override;
  bool SupportsPlatformTemperature() const override;
};
