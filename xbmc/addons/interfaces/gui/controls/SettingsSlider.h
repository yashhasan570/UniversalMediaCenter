/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/controls/settings_slider.h"

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
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/SettingsSlider.h"
   */
  struct Interface_GUIControlSettingsSlider
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
    static void set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool enabled);

    static void set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, const char* text);
    static void reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);

    static void set_int_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                              int start,
                              int end);
    static void set_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int value);
    static int get_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    static void set_int_interval(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                 UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                 int interval);

    static void set_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, float percent);
    static float get_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);

    static void set_float_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                float start,
                                float end);
    static void set_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, float value);
    static float get_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    static void set_float_interval(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                   float interval);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
