/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GPUInfoWasm.h"

std::unique_ptr<CGPUInfo> CGPUInfo::GetGPUInfo()
{
  return std::make_unique<CGPUInfoWasm>();
}

bool CGPUInfoWasm::SupportsPlatformTemperature() const
{
  return false;
}

bool CGPUInfoWasm::GetGPUPlatformTemperature(CTemperature& temperature) const
{
  return false;
}
