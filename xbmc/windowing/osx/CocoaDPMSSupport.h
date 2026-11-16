/*
 *  Copyright (C) 2009-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "powermanagement/DPMSSupport.h"

class CCocoaDPMSSupport : public CDPMSSupport
{
public:
  CCocoaDPMSSupport();
  ~CCocoaDPMSSupport() override = default;

protected:
  bool EnablePowerSaving(PowerSavingMode mode) override;
  bool DisablePowerSaving() override;
};
