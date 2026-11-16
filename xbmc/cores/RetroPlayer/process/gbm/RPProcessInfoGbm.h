/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/process/egl/RPProcessInfoEGL.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRPProcessInfoGbm : public CRPProcessInfoEGL
{
public:
  CRPProcessInfoGbm();
  ~CRPProcessInfoGbm() override = default;

  static std::unique_ptr<CRPProcessInfo> Create();
  static void Register();
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
