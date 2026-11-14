/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PrimitiveDetector.h"
#include "input/joysticks/JoystickTypes.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace JOYSTICK
{
class CButtonMapping;

/*!
 * \ingroup joystick
 *
 * \brief Detects when a mouse button should be mapped
 */
class CPointerDetector : public CPrimitiveDetector
{
public:
  CPointerDetector(CButtonMapping* buttonMapping);

  /*!
   * \brief Pointer position has been updated
   *
   * \param x The new x coordinate
   * \param y The new y coordinate
   *
   * \return Always true - pointer motion events are always absorbed while
   *         button mapping
   */
  bool OnPosition(int x, int y);

private:
  // Utility function
  static INPUT::INTERCARDINAL_DIRECTION GetPointerDirection(int x, int y);

  static const unsigned int MIN_FRAME_COUNT = 10;

  // State variables
  bool m_bStarted = false;
  int m_startX = 0;
  int m_startY = 0;
  unsigned int m_frameCount = 0;
};
} // namespace JOYSTICK
} // namespace UNIVERSAL MEDIA CENTER
