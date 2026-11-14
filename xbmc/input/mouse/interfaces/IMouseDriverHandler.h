/*
 *  Copyright (C) 2016-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/mouse/MouseTypes.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace MOUSE
{
/*!
 * \ingroup mouse
 *
 * \brief Interface for handling mouse driver events
 */
class IMouseDriverHandler
{
public:
  virtual ~IMouseDriverHandler(void) = default;

  /*!
   * \brief Handle mouse position updates
   *
   * \param x  The new x coordinate of the pointer
   * \param y  The new y coordinate of the pointer
   *
   * The mouse uses a left-handed (graphics) cartesian coordinate system.
   * Positive X is right, positive Y is down.
   *
   * \return True if the event was handled, false otherwise
   */
  virtual bool OnPosition(int x, int y) = 0;

  /*!
   * \brief A mouse button has been pressed
   *
   * \param button   The index of the pressed button
   *
   * \return True if the event was handled, otherwise false
   */
  virtual bool OnButtonPress(BUTTON_ID button) = 0;

  /*!
   * \brief A mouse button has been released
   *
   * \param button   The index of the released button
   */
  virtual void OnButtonRelease(BUTTON_ID button) = 0;
};
} // namespace MOUSE
} // namespace UNIVERSAL MEDIA CENTER
