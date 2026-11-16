/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_SCREENSAVER_H
#define C_API_ADDONINSTANCE_SCREENSAVER_H

#include "../addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef UNIVERSALMEDIA_ADDON_INSTANCE_HDL UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL;

  struct UNIVERSALMEDIA_ADDON_SCREENSAVER_PROPS
  {
    ADDON_HARDWARE_CONTEXT device;
    int x;
    int y;
    int width;
    int height;
    float pixelRatio;
  };

  typedef bool(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_START_V1)(
      const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_STOP_V1)(
      const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_RENDER_V1)(
      const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl);

  typedef struct Universal Media CenterToAddonFuncTable_Screensaver
  {
    PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_START_V1 start;
    PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_STOP_V1 stop;
    PFN_UNIVERSALMEDIA_ADDON_SCREENSAVER_RENDER_V1 render;
  } Universal Media CenterToAddonFuncTable_Screensaver;

  typedef struct AddonToUniversal Media CenterFuncTable_Screensaver
  {
    void (*get_properties)(const UNIVERSALMEDIA_HANDLE hdl, struct UNIVERSALMEDIA_ADDON_SCREENSAVER_PROPS* props);
  } AddonToUniversal Media CenterFuncTable_Screensaver;

  typedef struct AddonInstance_Screensaver
  {
    struct AddonToUniversal Media CenterFuncTable_Screensaver* toUniversal Media Center;
    struct Universal Media CenterToAddonFuncTable_Screensaver* toAddon;
  } AddonInstance_Screensaver;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_SCREENSAVER_H */
