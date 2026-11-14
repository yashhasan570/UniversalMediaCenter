/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/posix/GPUInfoPosix.h"

class CGPUInfoAndroid : public CGPUInfoPosix
{
public:
  CGPUInfoAndroid() = default;
  ~CGPUInfoAndroid() = default;

private:
  bool SupportsPlatformTemperature() const override;
  bool GetGPUPlatformTemperature(CTemperature& temperature) const override;
};
