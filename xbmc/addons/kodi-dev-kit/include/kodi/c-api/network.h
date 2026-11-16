/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_NETWORK_H
#define C_API_NETWORK_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /*
   * For interface between add-on and universalmediacenter.
   *
   * This structure defines the addresses of functions stored inside Universal Media Center which
   * are then available for the add-on to call
   *
   * All function pointers there are used by the C++ interface functions below.
   * You find the set of them on xbmc/addons/interfaces/General.cpp
   *
   * Note: For add-on development itself this is not needed
   */
  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_network
  {
    bool (*wake_on_lan)(void* universalmediacenterBase, const char* mac);
    char* (*get_ip_address)(void* universalmediacenterBase);
    char* (*dns_lookup)(void* universalmediacenterBase, const char* url, bool* ret);
    char* (*url_encode)(void* universalmediacenterBase, const char* url);
    char* (*get_hostname)(void* universalmediacenterBase);
    bool (*is_local_host)(void* universalmediacenterBase, const char* hostname);
    bool (*is_host_on_lan)(void* universalmediacenterBase, const char* hostname, bool offLineCheck);
    char* (*get_user_agent)(void* universalmediacenterBase);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_network;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* C_API_NETWORK_H */
