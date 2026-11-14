/*
 *  Copyright (C) 2018 Chris Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "OSScreenSaverAndroid.h"

#include "platform/android/activity/App.h"

void COSScreenSaverAndroid::Inhibit()
{
  CApp::Get().KeepScreenOn(true);
}

void COSScreenSaverAndroid::Uninhibit()
{
  CApp::Get().KeepScreenOn(false);
}
