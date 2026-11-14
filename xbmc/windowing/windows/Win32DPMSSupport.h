/*
 *  Copyright (C) 2009-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "powermanagement/DPMSSupport.h"

class CWin32DPMSSupport : public CDPMSSupport
{
public:
  CWin32DPMSSupport();
  ~CWin32DPMSSupport() = default;

protected:
  bool EnablePowerSaving(PowerSavingMode mode) override;
  bool DisablePowerSaving() override;
};
