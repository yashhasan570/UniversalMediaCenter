/*
 *  Copyright (C) 2019 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/IPlayer.h"
#include "cores/VideoPlayer/Process/ProcessInfo.h"

namespace VIDEOPLAYER
{

class CProcessInfoGBM : public CProcessInfo
{
public:
  static CProcessInfo* Create();
  static void Register();

  CProcessInfoGBM();
  EINTERLACEMETHOD GetFallbackDeintMethod() override;
  std::vector<AVPixelFormat> GetRenderFormats() override;
};

} // namespace VIDEOPLAYER
