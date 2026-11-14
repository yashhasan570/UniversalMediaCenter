/*
 *  Copyright (C) 2015-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CKey;

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYBOARD
{
/*!
 * \ingroup keyboard
 *
 * \brief Interface for handling keyboard events
 */
class IKeyboardDriverHandler
{
public:
  virtual ~IKeyboardDriverHandler() = default;

  /*!
   * \brief A key has been pressed
   *
   * \param key The pressed key
   *
   * \return True if the event was handled, false otherwise
   */
  virtual bool OnKeyPress(const CKey& key) = 0;

  /*!
   * \brief A key has been released
   *
   * \param key The released key
   */
  virtual void OnKeyRelease(const CKey& key) = 0;
};
} // namespace KEYBOARD
} // namespace UNIVERSAL MEDIA CENTER
