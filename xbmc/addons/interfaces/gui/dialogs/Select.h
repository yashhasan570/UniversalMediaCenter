/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/dialogs/select.h"

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
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/Select.h"
   */
  struct Interface_GUIDialogSelect
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
    static int open(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                    const char* heading,
                    const char* entries[],
                    unsigned int size,
                    int selected,
                    unsigned int autoclose);
    static bool open_multi_select(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  const char* heading,
                                  const char* entryIDs[],
                                  const char* entryNames[],
                                  bool entriesSelected[],
                                  unsigned int size,
                                  unsigned int autoclose);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
