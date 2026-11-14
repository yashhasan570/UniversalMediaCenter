/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <stdint.h>
#include <string>

namespace tinyxml2
{
class XMLElement;
}

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 */
class CKeyboardTranslator
{
public:
  static uint32_t TranslateButton(const tinyxml2::XMLElement* pButton);
  static uint32_t TranslateString(const std::string& szButton);
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
