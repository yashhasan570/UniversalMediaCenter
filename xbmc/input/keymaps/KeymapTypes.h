/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <set>
#include <string>

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 *
 * \brief Action entry in joystick.xml
 */
struct KeymapAction
{
  unsigned int actionId;
  std::string actionString;
  unsigned int holdTimeMs;
  std::set<std::string> hotkeys;

  bool operator<(const KeymapAction& rhs) const { return holdTimeMs < rhs.holdTimeMs; }
};

/*!
 * \ingroup keymap
 *
 * \brief Container that sorts action entries by their holdtime
 */
struct KeymapActionGroup
{
  int windowId = -1;
  std::multiset<KeymapAction> actions;
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
