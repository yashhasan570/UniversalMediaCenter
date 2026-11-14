/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/GpuInfo.h"

class CGPUInfoPosix : public CGPUInfo
{
protected:
  CGPUInfoPosix() = default;
  virtual ~CGPUInfoPosix() = default;

  virtual bool SupportsCustomTemperatureCommand() const override;
  virtual bool GetGPUTemperatureFromCommand(CTemperature& temperature,
                                            const std::string& cmd) const override;
};
