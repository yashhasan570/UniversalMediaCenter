/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/dialogs/ok.h"

extern "C"
{

  struct AddonGlobalInterface;

  namespace ADDON
  {

  /*!
   * @brief Global gui Add-on to Universal Media Center callback functions
   *
   * To hold functions not related to a instance type and usable for
   * every add-on type.
   *
   * Related add-on header is ".//addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/OK.h"
   */
  struct Interface_GUIDialogOK
  {
    static void Init(AddonGlobalInterface* addonInterface);
    static void DeInit(AddonGlobalInterface* addonInterface);

    /*!
     * @brief callback functions from add-on to universalmediacenter
     *
     * @note For add of new functions use the "_" style to identify direct a
     * add-on callback function. Everything with CamelCase is only for the
     * usage in Universal Media Center only.
     *
     * The parameter `universalmediacenterBase` is used to become the pointer for a `CAddonDll`
     * class.
     */
    //@{
    static void show_and_get_input_single_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                               const char* heading,
                                               const char* text);
    static void show_and_get_input_line_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             const char* heading,
                                             const char* line0,
                                             const char* line1,
                                             const char* line2);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
