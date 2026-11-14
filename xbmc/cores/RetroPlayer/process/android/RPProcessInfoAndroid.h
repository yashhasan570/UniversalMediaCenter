/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/process/egl/RPProcessInfoEGL.h"

namespace KODI
{
namespace RETRO
{
class CRPProcessInfoAndroid : public CRPProcessInfoEGL
{
public:
  CRPProcessInfoAndroid();

  static std::unique_ptr<CRPProcessInfo> Create();
  static void Register();
};
} // namespace RETRO
} // namespace KODI
