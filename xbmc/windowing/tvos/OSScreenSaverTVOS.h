/*
 *  Copyright (C) 2017-2019 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "windowing/OSScreenSaver.h"

class COSScreenSaverTVOS : public UNIVERSAL MEDIA CENTER::WINDOWING::IOSScreenSaver
{
public:
  COSScreenSaverTVOS() = default;
  void Inhibit() override;
  void Uninhibit() override;
};
