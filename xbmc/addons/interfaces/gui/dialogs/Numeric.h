/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/dialogs/numeric.h"

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
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/Numeric.h"
   */
  struct Interface_GUIDialogNumeric
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
    static bool show_and_verify_new_password(UNIVERSALMEDIA_HANDLE universalmediacenterBase, char** password);
    static int show_and_verify_password(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        const char* password,
                                        const char* heading,
                                        int retries);
    static bool show_and_verify_input(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      const char* verify_in,
                                      char** verify_out,
                                      const char* heading,
                                      bool verify_input);
    static bool show_and_get_time(UNIVERSALMEDIA_HANDLE universalmediacenterBase, tm* time, const char* heading);
    static bool show_and_get_date(UNIVERSALMEDIA_HANDLE universalmediacenterBase, tm* date, const char* heading);
    static bool show_and_get_ip_address(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        const char* ip_address_in,
                                        char** ip_address_out,
                                        const char* heading);
    static bool show_and_get_number(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* number_in,
                                    char** number_out,
                                    const char* heading,
                                    unsigned int auto_close_ms);
    static bool show_and_get_seconds(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                     const char* time_in,
                                     char** time_out,
                                     const char* heading);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
