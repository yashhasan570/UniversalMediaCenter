/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CFileItem;

namespace UNIVERSAL MEDIA CENTER::UTILS::GUILIB
{
class CGUIContentUtils
{
public:
  /*! \brief Check whether an information dialog is available for the given item.
    \param item The item to process
    \return True if an information dialog is available, false otherwise
  */
  static bool HasInfoForItem(const CFileItem& item);

  /*! \brief Show an information dialog for the given item.
    \param item The item to process
    \return True if an information dialog was displayed, false otherwise
  */
  static bool ShowInfoForItem(const CFileItem& item);
};
} // namespace UNIVERSAL MEDIA CENTER::UTILS::GUILIB
