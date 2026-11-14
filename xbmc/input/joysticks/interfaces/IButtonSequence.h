/*
 *  Copyright (C) 2016-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/joysticks/JoystickTypes.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace JOYSTICK
{
/*!
 * \ingroup joystick
 */
class IButtonSequence
{
public:
  virtual ~IButtonSequence() = default;

  virtual bool OnButtonPress(const FeatureName& feature) = 0;

  /*!
   * \brief Returns true if a sequence is being captured to prevent input
   *        from falling through to the application
   */
  virtual bool IsCapturing() = 0;
};
} // namespace JOYSTICK
} // namespace UNIVERSAL MEDIA CENTER
