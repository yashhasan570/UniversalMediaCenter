/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/input/action_ids.h"

namespace ADDON
{

/*!
 * \brief Translates data types from GUI API to the corresponding format in Universal Media Center.
 *
 * This class is stateless.
 */
class CAddonGUITranslator
{
  CAddonGUITranslator() = delete;

public:
  /*!
   * \brief Translate Universal Media Center's action id's to addon
   * \param universalmediacenterId Universal Media Center's action identifier
   * \return Addon action identifier
   */
  static ADDON_ACTION TranslateActionIdToAddon(int universalmediacenterId);

  /*!
   * \brief Translate addon's action id's to Universal Media Center
   * \param addonId Addon's action identifier
   * \return Universal Media Center action identifier
   */
  static int TranslateActionIdToUniversal Media Center(ADDON_ACTION addonId);
};

} /* namespace ADDON */
