/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace KODI
{
namespace JOYSTICK
{
struct AxisConfiguration
{
  bool bKnown = false;
  int center = 0;
  unsigned int range = 1;
  bool bLateDiscovery = false;
};
} // namespace JOYSTICK
} // namespace KODI
