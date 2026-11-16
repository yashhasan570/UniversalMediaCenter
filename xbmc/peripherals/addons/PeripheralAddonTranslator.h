/*
 *  Copyright (C) 2015-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/addon-instance/Peripheral.h"
#include "input/joysticks/DriverPrimitive.h"
#include "input/joysticks/JoystickTypes.h"
#include "input/mouse/MouseTypes.h"
#include "peripherals/PeripheralTypes.h"

#include <vector>

namespace PERIPHERALS
{
/*!
 * \ingroup peripherals
 */
class CPeripheralAddonTranslator
{
public:
  static const char* TranslateError(PERIPHERAL_ERROR error);

  static PeripheralType TranslateType(PERIPHERAL_TYPE type);
  static PERIPHERAL_TYPE TranslateType(PeripheralType type);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive TranslatePrimitive(
      const universalmediacenter::addon::DriverPrimitive& primitive);
  static universalmediacenter::addon::DriverPrimitive TranslatePrimitive(
      const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive);

  static std::vector<UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive> TranslatePrimitives(
      const std::vector<universalmediacenter::addon::DriverPrimitive>& primitives);
  static std::vector<universalmediacenter::addon::DriverPrimitive> TranslatePrimitives(
      const std::vector<UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive>& primitives);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::HAT_DIRECTION TranslateHatDirection(JOYSTICK_DRIVER_HAT_DIRECTION dir);
  static JOYSTICK_DRIVER_HAT_DIRECTION TranslateHatDirection(UNIVERSAL MEDIA CENTER::JOYSTICK::HAT_DIRECTION dir);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::HAT_STATE TranslateHatState(JOYSTICK_STATE_HAT state);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::SEMIAXIS_DIRECTION TranslateSemiAxisDirection(
      JOYSTICK_DRIVER_SEMIAXIS_DIRECTION dir);
  static JOYSTICK_DRIVER_SEMIAXIS_DIRECTION TranslateSemiAxisDirection(
      UNIVERSAL MEDIA CENTER::JOYSTICK::SEMIAXIS_DIRECTION dir);

  static UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID TranslateMouseButton(JOYSTICK_DRIVER_MOUSE_INDEX button);
  static JOYSTICK_DRIVER_MOUSE_INDEX TranslateMouseButton(UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID button);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::RELATIVE_POINTER_DIRECTION TranslateRelPointerDirection(
      JOYSTICK_DRIVER_RELPOINTER_DIRECTION dir);
  static JOYSTICK_DRIVER_RELPOINTER_DIRECTION TranslateRelPointerDirection(
      UNIVERSAL MEDIA CENTER::JOYSTICK::RELATIVE_POINTER_DIRECTION dir);

  static UNIVERSAL MEDIA CENTER::JOYSTICK::FEATURE_TYPE TranslateFeatureType(JOYSTICK_FEATURE_TYPE type);
  static JOYSTICK_FEATURE_TYPE TranslateFeatureType(UNIVERSAL MEDIA CENTER::JOYSTICK::FEATURE_TYPE type);

  static universalmediacenter::addon::DriverPrimitive Opposite(const universalmediacenter::addon::DriverPrimitive& semiaxis);
};
} // namespace PERIPHERALS
