/*
 *  Copyright (C) 2020-2021 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
class CDialogGameSaves;

/*!
 * \ingroup games
 */
class CGUIDialogSelectSavestate
{
public:
  static bool ShowAndGetSavestate(const std::string& gamePath, std::string& savestatePath);

private:
  static CDialogGameSaves* GetDialog();
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
