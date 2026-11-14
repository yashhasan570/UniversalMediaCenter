/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_GENERAL_H
#define C_API_GUI_GENERAL_H

#include "definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  //==============================================================================
  /// @ingroup cpp__general
  /// @brief **Adjust refresh rate enum**\n
  /// Used to get the Adjust refresh rate status info.
  ///
  typedef enum AdjustRefreshRateStatus
  {
    ADJUST_REFRESHRATE_STATUS_OFF = 0,
    ADJUST_REFRESHRATE_STATUS_ALWAYS,
    ADJUST_REFRESHRATE_STATUS_ON_STARTSTOP,
    ADJUST_REFRESHRATE_STATUS_ON_START,
  } AdjustRefreshRateStatus;
  //------------------------------------------------------------------------------

  typedef struct AddonToUniversal Media CenterFuncTable__general
  {
    void (*lock)();
    void (*unlock)();
    int (*get_screen_height)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    int (*get_screen_width)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    int (*get_video_resolution)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    int (*get_current_window_dialog_id)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    int (*get_current_window_id)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    ADDON_HARDWARE_CONTEXT (*get_hw_context)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    AdjustRefreshRateStatus (*get_adjust_refresh_rate_status)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
  } AddonToUniversal Media CenterFuncTable__general;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_GENERAL_H */
