/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../OSScreenSaver.h"

#import <IOKit/pwr_mgt/IOPMLib.h>

class COSScreenSaverOSX : public KODI::WINDOWING::IOSScreenSaver
{
public:
  COSScreenSaverOSX() = default;
  void Inhibit() override;
  void Uninhibit() override;

private:
  IOPMAssertionID m_assertionID = 0;
};
