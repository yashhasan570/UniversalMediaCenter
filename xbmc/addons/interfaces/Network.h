/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

struct AddonGlobalInterface;

extern "C"
{
namespace ADDON
{

/*!
 * @brief Global general Add-on to Universal Media Center callback functions
 *
 * To hold network functions not related to a instance type and usable for
 * every add-on type.
 *
 * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/Network.h"
 */
struct Interface_Network
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
  static bool wake_on_lan(void* universalmediacenterBase, const char* mac);
  static char* get_ip_address(void* universalmediacenterBase);
  static char* get_hostname(void* universalmediacenterBase);
  static char* get_user_agent(void* universalmediacenterBase);
  static bool is_local_host(void* universalmediacenterBase, const char* hostname);
  static bool is_host_on_lan(void* universalmediacenterBase, const char* hostname, bool offLineCheck);
  static char* dns_lookup(void* universalmediacenterBase, const char* url, bool* ret);
  static char* url_encode(void* universalmediacenterBase, const char* url);
  //@}
};

} /* namespace ADDON */
} /* extern "C" */
