/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GpuInfo.h"

#include "ServiceBroker.h"
#include "settings/AdvancedSettings.h"
#include "settings/SettingsComponent.h"

bool CGPUInfo::GetTemperature(CTemperature& temperature) const
{
  // user custom cmd takes precedence over platform implementation
  if (SupportsCustomTemperatureCommand())
  {
    auto cmd = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_gpuTempCmd;
    if (!cmd.empty() && GetGPUTemperatureFromCommand(temperature, cmd))
    {
      return true;
    }
  }

  if (SupportsPlatformTemperature() && GetGPUPlatformTemperature(temperature))
  {
    return true;
  }

  temperature = CTemperature();
  temperature.SetValid(false);
  return false;
}
