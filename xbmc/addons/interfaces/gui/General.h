/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/general.h"

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
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/General.h"
   */
  struct Interface_GUIGeneral
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
    static void lock();
    static void unlock();

    static int get_screen_height(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static int get_screen_width(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static int get_video_resolution(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static int get_current_window_dialog_id(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static int get_current_window_id(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static ADDON_HARDWARE_CONTEXT get_hw_context(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    static AdjustRefreshRateStatus get_adjust_refresh_rate_status(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    //@}

  private:
    static int m_iAddonGUILockRef;
  };

  } /* namespace ADDON */
} /* extern "C" */
