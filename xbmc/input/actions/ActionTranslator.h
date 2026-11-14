/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <vector>

namespace UNIVERSAL MEDIA CENTER
{
namespace ACTION
{
/*!
 * \ingroup action
 */
class CActionTranslator
{
public:
  static void GetActions(std::vector<std::string>& actionList);
  static bool IsAnalog(unsigned int actionId);
  static bool TranslateString(std::string strAction, unsigned int& actionId);
};
} // namespace ACTION
} // namespace UNIVERSAL MEDIA CENTER
