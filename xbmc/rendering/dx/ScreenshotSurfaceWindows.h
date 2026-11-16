/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/IScreenshotSurface.h"

#include <memory>

class CScreenshotSurfaceWindows : public IScreenshotSurface
{
public:
  static void Register();
  static std::unique_ptr<IScreenshotSurface> CreateSurface();

  bool Read(const ScreenshotContext& ctx) override;
};
