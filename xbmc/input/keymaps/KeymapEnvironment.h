/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/keymaps/interfaces/IKeymapEnvironment.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 */
class CKeymapEnvironment : public IKeymapEnvironment
{
public:
  ~CKeymapEnvironment() override = default;

  // implementation of IKeymapEnvironment
  int GetWindowID() const override { return m_windowId; }
  void SetWindowID(int windowId) override { m_windowId = windowId; }
  int GetFallthrough(int windowId) const override;
  bool UseGlobalFallthrough() const override { return true; }
  bool UseEasterEgg() const override { return true; }

private:
  int m_windowId = -1;
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
