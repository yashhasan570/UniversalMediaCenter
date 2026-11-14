/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

extern "C"
{

struct AddonGlobalInterface;
struct AddonKeyboardKeyTable;

namespace ADDON
{

/*!
 * @brief Global general Add-on to Universal Media Center callback functions
 *
 * To hold general functions not related to a instance type and usable for
 * every add-on type.
 *
 * Related add-on header is ".//addons/universalmediacenter-dev-kit/include/universalmediacenter/General.h"
 */
struct Interface_General
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
  static char* unknown_to_utf8(void* universalmediacenterBase, const char* source, bool* ret, bool failOnBadChar);
  static char* get_language(void* universalmediacenterBase, int format, bool region);
  static bool queue_notification(void* universalmediacenterBase,
                                 int type,
                                 const char* header,
                                 const char* message,
                                 const char* imageFile,
                                 unsigned int displayTime,
                                 bool withSound,
                                 unsigned int messageTime);
  static void get_md5(void* universalmediacenterBase, const char* text, char* md5);
  static char* get_region(void* universalmediacenterBase, const char* id);
  static void get_free_mem(void* universalmediacenterInstance, long* free, long* total, bool as_bytes);
  static int get_global_idle_time(void* universalmediacenterBase);
  static bool is_addon_available(void* universalmediacenterBase, const char* id, char** version, bool* enabled);
  static void universalmediacenter_version(void* universalmediacenterBase,
                           char** compile_name,
                           int* major,
                           int* minor,
                           char** revision,
                           char** tag,
                           char** tagversion);
  static char* get_current_skin_id(void* universalmediacenterBase);
  static bool change_keyboard_layout(void* universalmediacenterBase, char** layout_name);
  static bool get_keyboard_layout(void* universalmediacenterBase,
                                  char** layout_name,
                                  int modifier_key,
                                  AddonKeyboardKeyTable* c_layout);
  //@}
};

} /* namespace ADDON */
} /* extern "C" */
