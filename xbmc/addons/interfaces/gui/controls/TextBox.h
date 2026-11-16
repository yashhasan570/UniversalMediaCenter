/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/controls/text_box.h"

extern "C"
{

  struct AddonGlobalInterface;

  namespace ADDON
  {

  /*!
   * @brief Global gui Add-on to Universal Media Center callback functions
   *
   * To hold general gui functions and initialize also all other gui related types not
   * related to a instance type and usable for every add-on type.
   *
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/TextBox.h"
   */
  struct Interface_GUIControlTextBox
  {

    static void Init(AddonGlobalInterface* addonInterface);
    static void DeInit(AddonGlobalInterface* addonInterface);

    /*!
     * @brief callback functions from add-on to universalmediacenter
     *
     * @note To add a new function use the "_" style to directly identify an
     * add-on callback function. Everything with CamelCase is only to be used
     * in Universal Media Center.
     *
     * The parameter `universalmediacenterBase` is used to become the pointer for a `CAddonDll`
     * class.
     */
    //@{
    static void set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool visible);
    static void reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    static void set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, const char* text);
    static char* get_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    static void scroll(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, unsigned int position);
    static void set_auto_scrolling(
        UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int delay, int time, int repeat);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
