/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

namespace KODI
{
namespace HARDWARE
{
/*!
 * \ingroup hardware
 * \brief Handles events for hardware such as reset buttons on a game console
 */
class IHardwareInput
{
public:
  virtual ~IHardwareInput() = default;

  /*!
   * \brief A hardware reset button has been pressed
   */
  virtual void OnResetButton() = 0;
};
} // namespace HARDWARE
} // namespace KODI
