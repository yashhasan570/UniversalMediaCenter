/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIDialog.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CDialogGameAdvancedSettings : public CGUIDialog
{
public:
  CDialogGameAdvancedSettings();
  ~CDialogGameAdvancedSettings() override = default;

  // implementation of CGUIControl via CGUIDialog
  bool OnMessage(CGUIMessage& message) override;
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
