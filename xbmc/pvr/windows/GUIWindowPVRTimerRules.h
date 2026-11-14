/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "pvr/windows/GUIWindowPVRTimersBase.h"

#include <string>

namespace PVR
{
class CGUIWindowPVRTVTimerRules : public CGUIWindowPVRTimersBase
{
public:
  CGUIWindowPVRTVTimerRules();
  ~CGUIWindowPVRTVTimerRules() override = default;

protected:
  std::string GetRootPath() override;
  std::string GetDirectoryPath() override;
};

class CGUIWindowPVRRadioTimerRules : public CGUIWindowPVRTimersBase
{
public:
  CGUIWindowPVRRadioTimerRules();
  ~CGUIWindowPVRRadioTimerRules() override = default;

protected:
  std::string GetRootPath() override;
  std::string GetDirectoryPath() override;
};
} // namespace PVR
