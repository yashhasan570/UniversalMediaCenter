/*
 *  Copyright (C) 2017-2019 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#import "OSScreenSaverTVOS.h"

#import "platform/darwin/tvos/Controller.h"

void COSScreenSaverTVOS::Inhibit()
{
  [g_Controller disableScreenSaver];
}

void COSScreenSaverTVOS::Uninhibit()
{
  [g_Controller enableScreenSaver];
}
