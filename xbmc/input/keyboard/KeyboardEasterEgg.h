/*
 *  Copyright (C) 2016-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/keyboard/_vkeys.h"
#include "input/keyboard/interfaces/IKeyboardDriverHandler.h"

#include <vector>

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYBOARD
{
/*!
 * \ingroup keyboard
 *
 * \brief Hush!!!
 */
class CKeyboardEasterEgg : public IKeyboardDriverHandler
{
public:
  ~CKeyboardEasterEgg() override = default;

  // implementation of IKeyboardDriverHandler
  bool OnKeyPress(const CKey& key) override;
  void OnKeyRelease(const CKey& key) override {}

private:
  static std::vector<VKey> m_sequence;

  unsigned int m_state = 0;
};
} // namespace KEYBOARD
} // namespace UNIVERSAL MEDIA CENTER
