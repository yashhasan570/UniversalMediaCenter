/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "KeyboardSymbols.h"
#include "KeyboardTypes.h"
#include "_keysym.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYBOARD
{

/*!
 * \brief Keyboard translation utilities
 */
class CKeyboardTranslator
{
public:
  /*!
   * \brief Translate a keyboard symbol to a Universal Media Center key code
   *
   * Keyboard symbols are hardware-independent virtual key representations.
   * They are used to help facilitate keyboard mapping.
   *
   * \param symbol The key's symbol, defined in the Controller Topology Project:
   *   https://github.com/universalmediacenter-game/controller-topology-project/blob/master/Readme-Keyboard.md
   *
   * \return The layout-independent keycode associated with the key
   */
  static Key TranslateKeysym(const SymbolName& symbolName);

  /*!
   * \brief Translate a Universal Media Center key code to a keyboard symbol
   *
   * \param keycode The Universal Media Center key code
   *
   * \return The key's symbol, or an empty string if no symbol is defined for the keycode
   */
  static const char* TranslateKeycode(Key keycode);
};

} // namespace KEYBOARD
} // namespace UNIVERSAL MEDIA CENTER
