/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/keymaps/interfaces/IKeyboardActionMap.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 */
class CKeyboardActionMap : public IKeyboardActionMap
{
public:
  CKeyboardActionMap() = default;

  ~CKeyboardActionMap() override = default;

  // implementation of IActionMap
  unsigned int GetActionID(const CKey& key) override;
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
