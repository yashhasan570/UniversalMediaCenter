/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace KODI
{
namespace GAME
{
/*!
 * \ingroup games
 *
 * \brief Types of button controls that can populate the feature list
 */
enum class BUTTON_TYPE
{
  UNKNOWN,
  BUTTON,
  ANALOG_STICK,
  RELATIVE_POINTER,
  WHEEL,
  THROTTLE,
  SELECT_KEY,
};
} // namespace GAME
} // namespace KODI
