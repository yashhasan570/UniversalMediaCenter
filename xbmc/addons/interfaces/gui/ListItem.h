/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/list_item.h"

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
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/ListItem.h"
   */
  struct Interface_GUIListItem
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
    static UNIVERSALMEDIA_GUI_LISTITEM_HANDLE create(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           const char* label,
                                           const char* label2,
                                           const char* path);
    static void destroy(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    static char* get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    static void set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* label);
    static char* get_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    static void set_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                           UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                           const char* label);
    static char* get_art(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* type);
    static void set_art(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                        UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                        const char* type,
                        const char* image);
    static char* get_path(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    static void set_path(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* path);
    static char* get_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                              const char* key);
    static void set_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                             const char* key,
                             const char* value);
    static void select(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, bool select);
    static bool is_selected(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    //@}
  };

  } /* namespace ADDON */
} /* extern "C" */
