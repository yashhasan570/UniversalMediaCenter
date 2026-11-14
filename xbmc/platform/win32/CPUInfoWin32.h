/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/CPUInfo.h"
#include "utils/Temperature.h"

class CCPUInfoWin32 : public CCPUInfo
{
public:
  CCPUInfoWin32();
  ~CCPUInfoWin32();

  int GetUsedPercentage() override;
  float GetCPUFrequency() override;
  bool GetTemperature(CTemperature& temperature) override;

private:
  // avoid inclusion of <windows.h> and others
  typedef void* HANDLE;
  typedef HANDLE PDH_HQUERY;
  typedef HANDLE PDH_HCOUNTER;

  PDH_HQUERY m_cpuQueryFreq{nullptr};
  PDH_HQUERY m_cpuQueryLoad{nullptr};
  PDH_HCOUNTER m_cpuFreqCounter{nullptr};
  std::vector<PDH_HCOUNTER> m_coreCounters;
};
