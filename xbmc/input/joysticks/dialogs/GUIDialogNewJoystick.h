/*
 *  Copyright (C) 2016-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "threads/Thread.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace JOYSTICK
{
/*!
 * \ingroup joystick
 */
class CGUIDialogNewJoystick : protected CThread
{
public:
  CGUIDialogNewJoystick();
  ~CGUIDialogNewJoystick() override = default;

  void ShowAsync();

protected:
  // implementation of CThread
  void Process() override;
};
} // namespace JOYSTICK
} // namespace UNIVERSAL MEDIA CENTER
