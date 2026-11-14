/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GUIControlTypes.h"
#include "input/joysticks/JoystickTypes.h"

namespace KODI
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CGUIFeatureTranslator
{
public:
  /*!
   * \brief Get the type of button control used to map the feature
   */
  static BUTTON_TYPE GetButtonType(JOYSTICK::FEATURE_TYPE featureType);
};
} // namespace GAME
} // namespace KODI
