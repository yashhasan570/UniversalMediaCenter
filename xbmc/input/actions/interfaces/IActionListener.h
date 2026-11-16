/*
 *  Copyright (C) 2005-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CAction;

namespace UNIVERSAL MEDIA CENTER
{
namespace ACTION
{
/*!
 * \ingroup action
 *
 * \brief Interface defining methods to handle GUI actions
 */
class IActionListener
{
public:
  virtual ~IActionListener() = default;

  /*!
   * \brief Handle a GUI action
   *
   * \param action The GUI action
   *
   * \return True if the action was handled, false otherwise
   */
  virtual bool OnAction(const CAction& action) = 0;
};
} // namespace ACTION
} // namespace UNIVERSAL MEDIA CENTER
