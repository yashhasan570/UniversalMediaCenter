/*
 *  Copyright (C) 2018 Chris Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../OSScreenSaver.h"

class COSScreenSaverAndroid : public UNIVERSAL MEDIA CENTER::WINDOWING::IOSScreenSaver
{
public:
  explicit COSScreenSaverAndroid() = default;
  void Inhibit() override;
  void Uninhibit() override;
};
